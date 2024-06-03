#include <iostream>
#include <string>

// 模板方法：定义了一个算法的框架，将一些步骤的具体实现延迟到子类中，使得子类可以改变算法的某些特定步骤，而不改变算法的结构。
// 工厂方法就是模板方法的特例，就是将具体的创建对象过程延迟到子类

class AbastractClass{
public:
    virtual ~AbastractClass(){}
    virtual void method() final{
        step1();
        step2();
        hook();
        step3();
    }
    virtual void step1() = 0;
    virtual void step2() = 0;
    virtual void hook(){}
    virtual void step3() = 0;
};

class A : public AbastractClass{
public:
    void step1(){
        std::cout << "A run step1\n";
    }
    void step2(){std::cout << "A run step2\n";}
    void step3(){std::cout << "A run step3\n";}
};

class B : public AbastractClass{
public:
    void step1(){
        std::cout << "B run step1\n";
    }
    void hook(){
        std::cout << "B run hook\n";
    }
    void step2(){std::cout << "B run step2\n";}
    void step3(){std::cout << "B run step3\n";}
};

void client(AbastractClass* objcet){
    objcet->method();
}

int main(int argc, char const *argv[])
{
    A a;
    client(&a);
    std::cout << std::endl;
    B b;
    client(&b);
    return 0;
}
