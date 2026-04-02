.PHONY:all
all:server_tcp client_tcp
server_tcp:NetCalServer.cc
	g++ -o $@ $^ -std=c++14 -ljsoncpp
client_tcp:NetCalClient.cc
	g++ -o $@ $^ -std=c++14 -ljsoncpp
.PHONY:clean
clean:
	rm -f  server_tcp client_tcp