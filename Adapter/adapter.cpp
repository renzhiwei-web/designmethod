#include <iostream>
// 对象适配器模型
class MicroUsb
{
private:
public:
    virtual ~MicroUsb() {}
    virtual void charge() const{
        std::cout << "MicroUsb connecting and charging" << std::endl;
    }
};

class TypeC
{
private:
public:
    virtual ~TypeC() {}
    virtual void charge() const{
        std::cout << "TypeC connecting and charging" << std::endl;
    }
};

// 将Typec接口转为microusb接口
class Adapter : public MicroUsb{
private:
    TypeC* m_usb;
public:
    Adapter(TypeC* usb): m_usb(usb){}
    void charge() const override{
        m_usb->charge();
    }
};

// 手机只支持microusb接口
void client(MicroUsb* usb){
    usb->charge();
}



int main(int argc, char const *argv[])
{
    MicroUsb mUsb;
    client(&mUsb);
    TypeC tUsb;
    Adapter adapter(&tUsb);
    client(&adapter);
    return 0;
}
