#include <iostream>
// 系统的产品有多于一个的产品族，而系统只消费其中某一族的产品。
// 当一大堆功能需要扩展时使用
// 工厂方法是抽象工厂的一个特例
class Button{
public:

    virtual ~Button(){}
    virtual void click() const = 0;
};

class Button_win : public Button{
public:
    virtual ~Button_win(){};
    void click() const override{
        std::cout << "点击Win系统按钮" << std::endl;
    }
};

class Button_mac : public Button{
public:
    virtual ~Button_mac(){};
    void click() const override{
        std::cout << "点击Mac系统按钮" << std::endl;
    }
};

class Text{
public:
    virtual ~Text(){}
    virtual void input() const = 0;
};

class Text_win : public Text{
    virtual ~Text_win(){}
    void input() const override {
        std::cout << "创建Win系统文本框" << std::endl;
    }
};

class Text_mac : public Text{
    virtual ~Text_mac(){}
    void input() const override {
        std::cout << "创建Mac系统文本框" << std::endl;
    }
};

class Factory{
public:
    virtual ~Factory(){}
    virtual Text* get_text() = 0;
    virtual Button* get_button() = 0;
};

class Factory_win : public Factory{
public:
    virtual Text* get_text() override{
        return new Text_win();
    }
    virtual Button* get_button() override{
        return new Button_win();
    }
};

class Factory_mac : public Factory{
public:
    virtual Text* get_text() override{
        return new Text_mac();
    }
    virtual Button* get_button() override{
        return new Button_mac();
    }
};

class GUI{
private:
    Factory* factory;
public:
    void build(){
        Button* b = factory->get_button();
        Text* t =  factory->get_text();
        b->click();
        t->input();
    }

    void set(Factory* f){
        factory = f;
    }
};


int main(){
    GUI g;
    Factory_mac fm;
    g.set(&fm);
    g.build();
    Factory_win fw;
    g.set(&fw);
    g.build();
    return 0;
}