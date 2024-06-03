#include <iostream>
// 工厂方法解决的问题是，当有新的功能需要扩展时，通过分离功能的定义与功能的创建，只需要增加具体功能类继承，已经功能创建类的继承即可。
class product{
public:
    virtual ~product(){}
    virtual void action() const = 0;
};

class productA : public product{
public:
    virtual ~productA(){}
    void action() const override{
        std::cout << "产品A在操作" << std::endl;
    }
};

class productB : public product{
public:
    virtual ~productB(){}
    void action() const override{
        std::cout << "产品B在操作" << std::endl;
    }
};

class creator{
public:
    virtual ~creator(){}
    // 工厂方法核心
    virtual product* factory_method() const = 0;
    void operation() const {
        product* p = factory_method();
        p->action();
        delete p;
    }
};

class concreteCreatorA : public creator{
public:
    virtual ~concreteCreatorA(){}
    product* factory_method() const override{
        return new productA;
    }
};

class concreteCreatorB : public creator{
public:
    virtual ~concreteCreatorB(){}
    product* factory_method() const override{
        return new productB;
    }
};

int main(int argc, char const *argv[])
{
    creator *c1 = new concreteCreatorA();
    creator *c2 = new concreteCreatorB();
    c1->operation();
    c1->operation();
    c2->operation();
    c2->operation();
    return 0;
}
