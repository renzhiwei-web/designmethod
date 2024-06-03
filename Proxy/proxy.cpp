#include <iostream>

// 代理设计模式：通过使用代理设计模式，隐藏真实的提供服务者并且服务前的各种检验等

class ServiceInterface{
public:
    virtual ~ServiceInterface(){}
    virtual void request() = 0;
};

class Service : public ServiceInterface{
public:
    void request() override{
        std::cout << "请求..." << std::endl;
    }
};


class Proxy : public ServiceInterface{
private:
    Service* m_service;
    bool check(){
        std::cout << "checking request\n";
        return true;
    }
public:
    Proxy(Service* service) : m_service(service){
        
    }

    void request() override{
        check();
        m_service->request();
    }
};

int main(int argc, char const *argv[])
{
    Service s;
    Proxy p(&s);
    p.request();
    return 0;
}
