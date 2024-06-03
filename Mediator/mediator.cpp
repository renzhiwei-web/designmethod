#include <iostream>
#include <string>
using std::string;
// 中介者设计模式：通过一个中介者对象来协调多个对象之间的交互，使得对象之间的交互更加灵活和易于维护

class Staff;

class ControlTower{
public:
    virtual void notify(Staff* sender,string event) const = 0;
};

class Staff{
protected:
    string m_name;
    ControlTower* m_controlTower;
    
public:
    Staff(string& name,ControlTower* controlTower = nullptr) : m_controlTower(controlTower),m_name(name){

    }
    string name(){
        return m_name;
    }

    void setMediator(ControlTower* controlTower){
        m_controlTower = controlTower;
    }
};

class Pilot:public Staff{
public:
    Pilot(string name) : Staff(name){}
    void takeOff(){
        std::cout << name() + ":请求起飞。\n";
        m_controlTower->notify(this,"请求起飞");
    }
    void copy(){
        std::cout << name() + ":收到。\n";
    }
};

class GroundGrew:public Staff{
public:
    GroundGrew(string name) : Staff(name){}
    void takeOff(){
        std::cout << name() + ":请求维护。\n";
        m_controlTower->notify(this,"请求维护");
    }
    void copy(){
        std::cout << name() + ":收到。\n";
    }
};

class ConcreteControlTower : public ControlTower{
private:
    Pilot* m_pilot1;
    Pilot* m_pilot2;
    GroundGrew* m_groud1;
    GroundGrew* m_groud2;
public:
    ConcreteControlTower(Pilot* pilot1,Pilot* pilot2,GroundGrew* groud1,GroundGrew* groud2) :
    m_pilot1(pilot1),m_pilot2(pilot2),m_groud1(groud1),m_groud2(groud2) {
        m_pilot1->setMediator(this);
        m_pilot2->setMediator(this);
        m_groud1->setMediator(this);
        m_groud2->setMediator(this);
    }

    void notify(Staff* sender,string event) const override{
        std::cout << "控制台:收到，" + sender->name() + event + ".\n";
        if (event == "请求起飞")
        {
            m_groud1->copy();
            m_groud2->copy();
            if (sender != m_pilot1)
            {
                m_pilot1->copy();
            }
            if (sender != m_pilot2)
            {
                m_pilot2->copy();
            }
            
        }
        if (event == "请求维护")
        {
            m_pilot1->copy();
            m_pilot2->copy();
            if (sender != m_groud1)
            {
                m_groud1->copy();
            }
            if (sender != m_groud2)
            {
                m_groud2->copy();
            }
        }
    }
};
int main(int argc, char const *argv[])
{
    Pilot* p1 = new Pilot("空军一号");
    Pilot* p2 = new Pilot("空军二号");
    GroundGrew* g1 = new GroundGrew("地勤一号");
    GroundGrew* g2 = new GroundGrew("地勤二号");
    ConcreteControlTower *c1 = new ConcreteControlTower(p1,p2,g1,g2);
    p1->takeOff();
    delete c1;
    delete p1;
    delete p2;
    delete g1;
    delete g2;
    return 0;
}
