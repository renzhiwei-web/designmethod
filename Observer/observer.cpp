#include <iostream>
#include <string>
#include <list>
// 观察者设计模式，察者模式通常由两个对象组成：观察者和被观察者。当被观察者状态发生改变时，它会通知所有的观察者对象，使他们能够及时做出响应，所以也被称作“发布-订阅模式”。

class ISubscriber{
public:
    virtual void update(std::string message) = 0;
};

class ISubject{
public:
    virtual void addSubscriber(ISubscriber *subscriber) = 0;
    virtual void removeSubscriber(ISubscriber *subscriber) = 0;
    virtual void notify(std::string message) = 0;
};

class Subject : public ISubject{
private:
    std::list<ISubscriber*> m_subscribers;
public:
    virtual void addSubscriber(ISubscriber *subscriber) override{
        m_subscribers.push_back(subscriber);
    }
    virtual void removeSubscriber(ISubscriber *subscriber) override{
        m_subscribers.remove(subscriber);
    }
    virtual void notify(std::string message) override{
        std::list<ISubscriber*>::iterator iter = m_subscribers.begin();
        while (iter != m_subscribers.end())
        {
            (*iter++)->update(message);
        }
        
    }
};

class Subscriber : public ISubscriber{
private:
    std::string m_name;
public:
    Subscriber(const std::string &name) : m_name(name){}
    void update(std::string message) override{
        std::cout << m_name << " accept message " << message << std::endl;
    }
};

int main(int argc, char const *argv[])
{
    ISubject *s1 = new Subject();
    ISubscriber *c1 = new Subscriber("lili");
    ISubscriber *c2 = new Subscriber("hanmeimei");
    s1->addSubscriber(c1);
    s1->addSubscriber(c2);
    s1->notify("hello everyone");
    s1->removeSubscriber(c1);
    s1->notify("jj");
    delete c2;
    delete c1;

    delete s1;
    return 0;
}
