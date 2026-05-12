#include <iostream>
#include <cstddef>

// 1. 普通类（无虚函数）
class Normal {
    int a;
    char b;
    // 内存布局：a (4字节) + b (1字节) + padding (3字节) = 8字节（典型32位下）
};

// 2. 带虚函数的类
class WithVtable {
    int x;
    virtual void f() {}
    // 内存布局：vptr (8字节，64位系统) + x (4字节) + padding (4字节) = 16字节
};

// 3. 多继承：两个基类都有虚函数
class Base1 {
    int b1;
public:
    virtual void v1() {}
    // 大小：vptr + int = 16字节（64位）
};

class Base2 {
    int b2;
public:
    virtual void v2() {}
    // 大小：vptr + int = 16字节
};

// 多继承派生类
class Derived : public Base1, public Base2 {
    int d;
public:
    virtual void v1() override {}  // 覆盖 Base1 虚函数
    // 内存布局：[Base1子对象（含vptr + b1）] + [Base2子对象（含vptr + b2）] + d + 对齐
    // 64位下：Base1:16 + Base2:16 + d:4 = 36，对齐到8的倍数 -> 40字节
};

// 4. 虚继承（解决菱形继承）
class VBase {
    int vb;
public:
    virtual void vfunc() {}
    // 大小：vptr + int = 16字节
};

class VD1 : virtual public VBase {
    int vd1;
public:
    virtual void vfunc() override {}
    // 虚继承会产生一个指向虚基类偏移的指针（或类似结构），通常多一个 vptr 或 vbptr
    // 典型布局（64位）：vd1 vptr? 实际上每个虚继承类有自己的 vptr 用于虚函数 + 一个指向虚基类的指针（vbptr）
    // 大小较复杂，通常 VD1 自身部分（vbptr + vd1）+ 虚基类部分（单独位于对象末尾）
    // 常见大小：32字节（例子）
};

class VD2 : virtual public VBase {
    int vd2;
public:
    virtual void vfunc() override {}
};

class MultipleVirtual : public VD1, public VD2 {
    int md;
public:
    virtual void vfunc() override {}
    // 菱形继承 + 虚继承，VBase 只保留一份
    // 布局：VD1 子对象（含 vbptr + vd1），VD2 子对象（含 vbptr + vd2），自己的 md，最后是共享的 VBase 子对象
};

int main() {
    // 打印各类型大小
    std::cout << "sizeof(Normal)                = " << sizeof(Normal) << " 字节" << std::endl;
    std::cout << "sizeof(WithVtable)            = " << sizeof(WithVtable) << " 字节" << std::endl;
    std::cout << "sizeof(Base1)                 = " << sizeof(Base1) << " 字节" << std::endl;
    std::cout << "sizeof(Derived)               = " << sizeof(Derived) << " 字节" << std::endl;
    std::cout << std::endl;

    // 演示多继承下指针转换时的地址偏移
    Derived d;
    Base1* b1_ptr = &d;
    Base2* b2_ptr = &d;

    std::cout << "Derived 对象地址 = " << &d << std::endl;
    std::cout << "Base1* 指向地址  = " << b1_ptr << " (通常与派生类起始地址相同)" << std::endl;
    std::cout << "Base2* 指向地址  = " << b2_ptr << " (相对于 Derived 起始偏移了 sizeof(Base1) 字节)" << std::endl;
    std::cout << "偏移量 = " << (std::ptrdiff_t)b2_ptr - (std::ptrdiff_t)&d << " 字节" << std::endl;
    std::cout << std::endl;

    // 虚继承对象大小与布局
    std::cout << "sizeof(VBase)                 = " << sizeof(VBase) << " 字节" << std::endl;
    std::cout << "sizeof(VD1)                   = " << sizeof(VD1) << " 字节" << std::endl;
    std::cout << "sizeof(VD2)                   = " << sizeof(VD2) << " 字节" << std::endl;
    std::cout << "sizeof(MultipleVirtual)       = " << sizeof(MultipleVirtual) << " 字节" << std::endl;
    std::cout << std::endl;

    // 验证虚基类在对象中只存在一份（地址检查）
    MultipleVirtual mv;
    VD1* pvd1 = &mv;
    VD2* pvd2 = &mv;
    VBase* pbase_from_vd1 = pvd1;
    VBase* pbase_from_vd2 = pvd2;

    std::cout << "MultipleVirtual 对象地址 = " << &mv << std::endl;
    std::cout << "VD1* 指向地址          = " << pvd1 << std::endl;
    std::cout << "VD2* 指向地址          = " << pvd2 << std::endl;
    std::cout << "通过 VD1 得到的 VBase* = " << pbase_from_vd1 << std::endl;
    std::cout << "通过 VD2 得到的 VBase* = " << pbase_from_vd2 << std::endl;
    // 两个 VBase* 应指向同一地址，因为虚基类在最终派生类中只有一份拷贝
    std::cout << "虚基类地址是否相同？ " << (pbase_from_vd1 == pbase_from_vd2 ? "是" : "否") << std::endl;

    return 0;
}