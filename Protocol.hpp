#pragma once
#include<iostream>
#include<jsoncpp/json/json.h>
#include<string>
#include<functional>

//请求报文
const std::string gsep="\r\n";

class Request
{
public:
    Request(){}
    Request(int x,int y,char oper):
    _data_x(x)
    ,_data_y(y)
    ,_oper(oper){}
    bool Serialize(std::string *out){
        Json::Value root;
        root["left"]=_data_x;
        root["right"]=_data_y;
        root["oper"]=_oper;
        Json::FastWriter writer;
        *out=writer.write(root);
        return true;
    }
    bool Deserialize(std::string& in){
        Json:: Value root;
        Json::Reader reader;
        bool parsesuccess=reader.parse(in,root);
        if(!parsesuccess)return false;
        _data_x=root["left"].asInt();
        _data_y=root["right"].asInt();
        _oper=root["oper"].asInt();
        return true;
    }
    ~Request(){}
public:
    int _data_x;//数字x
    int _data_y;//数字y
    char _oper;//操作符
};
//应答报文
class Response
{
public:
    Response(){}
    Response(int result,int code):
    _result(result)
    ,_code(code)
    {}
    bool Serialize(std::string* out){
        Json::Value root;
        root["result"]=_result;
        root["code"]=_code;
        Json::FastWriter writer;
        *out=writer.write(root);
        return true;
    }
    bool Deserialize(std::string &in){
        Json::Reader reader;
        Json::Value root;
        bool parsesuccess=reader.parse(in,root);
        if(!parsesuccess)return false;
        _result=root["result"].asInt();
        _code=root["code"].asInt();
        return true;
    }
public:
    int _result;//结果
    int _code;///状态
};
using HandlerRequest_t =std::function<Response(Request&)>;
using HandlerResponse_t = std::function<void (Response &)>;
class Protocol
{
public:
    Protocol(HandlerRequest_t handler):
    _version("1.0")
    ,_handler_request(handler){}
    Protocol(HandlerResponse_t handler):
    _version("1.0")
    ,_handler_response(handler){}
    Protocol(){}
    std::string Packet(const std::string& json_string){
        return std::to_string(json_string.size())+gsep+json_string+gsep;
    }
    int Unpack(std::string& packet,std::string *json_string){
        if(packet.empty())return 0;
        if(json_string==nullptr)return -1;
        auto pos=packet.find(gsep);
        if(pos==std::string::npos)return 0;
        std::string lenstr=packet.substr(0,pos);
        int len=std::stoi(lenstr);
        int total=lenstr.size()+len+2*gsep.size();
        if(packet.size()<total)return 0;
        *json_string=packet.substr(pos+gsep.size(),len);
        packet.erase(0,total);
        return 1;
    }
    std::string ParseRequest(std::string& inbuffer){
        std::string result;
        while(true){
        std::string json_string;
        //解析出json
        int n=Unpack(inbuffer,&json_string);
        if(n<0){
           return std::string();
        }
        else if(n==0)return result;
    
        //将json拆分
        Request req;
        if(req.Deserialize(json_string))return std::string();
        //用hander_request进行计算,然后再包装成json,再讲json包装成报头返回
        Response resp;
        if(_handler_request)resp=_handler_request(req);
        std::string resp_json_string;
        resp.Serialize(&resp_json_string);
        result+=Packet(resp_json_string);
    }
}
std::string ParseResponse(std::string &inbuffer)
    {
        while (true)
        {
            std::string json_string;
            // 1. 解包
            int n = Unpack(inbuffer, &json_string);
            if (n < 0)
            {
                
                return std::string();
            }
            if (n == 0)
            {
                
                return std::string();
            }
            // 2. 反序列化
            // 得到一个完整的报文jsonstring
            Response resp;
            if (!resp.Deserialize(json_string))
                return std::string();
            
            // 3. 回调处理
            if (_handler_response)
                _handler_response(resp);
        }
    }

    ~Protocol(){}
private:
    std::string _version;
    HandlerRequest_t _handler_request;
    HandlerResponse_t _handler_response;
};