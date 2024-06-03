#include <iostream>

// 责任链设计模式，定义一个责任链，链上的每个对象会根据请求的难度来选择是否处理该请求
// 若请求已经被处理，则请求不会在链上继续传导。否则，请求会继续传导，知道找到权限最大的对象。
// 责任链上的对象是按照权限从小到大排序

class BaseHandler{
private:
    BaseHandler* m_nextHandler;
public:
    virtual ~BaseHandler(){}
    BaseHandler* set_nextHandler(BaseHandler* handler){
        m_nextHandler = handler;
        return m_nextHandler;
    }
    virtual std::string handle(int days){
        if(m_nextHandler){
            return m_nextHandler->handle(days);
        }
        return "";
    }
};

class Monitor : public BaseHandler{
public:
    std::string handle(int days) override{
        if (days <= 1)
        {
            return "days <= 1,monitor has right to handle\n";
        }else{
            return BaseHandler::handle(days);
        }
    }
};

class President : public BaseHandler{
public:
    std::string handle(int days) override{
        return "President has right to handle\n";
    }
};

class Teacher : public BaseHandler{
public:
    std::string handle(int days) override{
        if (days <= 3)
        {
            return "days <= 3,Teacher has right to handle\n";
        }else{
            return BaseHandler::handle(days);
        }
    }
};

int main(int argc, char const *argv[])
{
    Monitor m;
    Teacher t;
    President p;
    m.set_nextHandler(&t)->set_nextHandler(&p);
    std::cout << m.handle(1) << std::endl;
    std::cout << m.handle(2) << std::endl;
    std::cout << m.handle(10) << std::endl;
    return 0;
}
