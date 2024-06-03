#include <iostream>
#include <string>

// 桥接模式就是将类的抽象部分与它的实现部分进行分离，使它们都可以进行独立的变化
// 类的抽象就是调用类中成员方法功能，类的实现就是类中成员方法的定义
// 具体例子就是：控制器就是抽象，而电视就是实现。
class Device{
public:
    virtual ~Device(){}
    virtual std::string turnOn() const = 0;
    virtual std::string turnOff() const = 0;
    virtual std::string mute() const = 0;
};

class TV : public Device{
public:
    ~TV(){};
    TV(){};
    std::string turnOn() const override{
        return "TV:turn on\n"; 
    }

    std::string turnOff() const override{
        return "TV:turn off\n"; 
    }

    std::string mute() const override{
        return "TV:mute\n"; 
    }
};

class Audio : public Device{
public:
    ~Audio(){};
    Audio(){};
    std::string turnOn() const override{
        return "Audio:turn on\n"; 
    }

    std::string turnOff() const override{
        return "Audio:turn off\n"; 
    }

    std::string mute() const override{
        return "Audio:mute\n"; 
    }
};

class BaseController{
private:
    BaseController() = delete;
protected:
    Device *m_device;
public:
    virtual ~BaseController() {}
    BaseController(Device *device) : m_device(device){}
    virtual std::string sendTurnOn(){
        return "base controller " + m_device->turnOn();
    }
    virtual std::string sendTurnOff(){
        return "base controller " + m_device->turnOff();
    }
};

class AdvancedController : public BaseController{
public:
    ~AdvancedController(){}
    AdvancedController(Device* device) : BaseController(device){}

    virtual std::string sendTurnOn() override{
        return "advanced controller " + m_device->turnOn();
    }
    virtual std::string sendTurnOff() override{
        return "advanced controller " + m_device->turnOff();
    }

    std::string sendMute(){
        return "advanced controller " + m_device->mute();
    }
};

int main(int argc, char const *argv[])
{
    TV tv;
    Audio audio;
    BaseController bcontroller(&audio);
    AdvancedController acontroller(&tv);
    std::cout << bcontroller.sendTurnOn();
    std::cout << bcontroller.sendTurnOff();
    std::cout << std::endl;
    std::cout << acontroller.sendTurnOn();
    std::cout << acontroller.sendMute();
    std::cout << acontroller.sendTurnOff();
    return 0;
}
