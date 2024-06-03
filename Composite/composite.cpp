#include <iostream>
#include <list>

//将对象组成树形结构以表示“部分-整体”的层次结构。使得用户对单个对象和组合对象的使用具有一致性。
class Component{
protected:
    Component* m_parent;
    float m_price;
public:
    virtual ~Component(){}
    Component() = default;
    Component(float price) : m_price(price) {};
    void set_parent(Component* parent){
        m_parent = parent;
    }
    Component* get_parent(){
        return m_parent;
    }
    void set_price(float price){
        m_price = price;
    }
    float get_price(){
        return m_price;
    }
    virtual bool isComposite() const {
        return false;
    }
    virtual std::string operation() = 0;
};

class Leaf : public Component{
public:
    ~Leaf(){}
    Leaf(float price):Component(price){}
    virtual std::string operation() override{
        return "产品";
    }
};

class Composite : public Component{
protected:
    std::list<Component*> m_children;
public:
    ~Composite(){}
    Composite(){}
    bool isComposite() const override{
        return true;
    }
    void add(Component* node){
        m_children.push_back(node);
        node->set_parent(this);
        // m_price += node->get_price();
    }
    void remove(Component* node){
        m_children.remove(node);
        node->set_parent(nullptr);
        // m_price -= node->get_price();
    }
    virtual std::string operation() override{
        std::string result;
        m_price = 0;
        for(auto c : m_children){
            if (c == m_children.back())
            {
                result += c->operation();
            }else{
                result += c->operation() + '+';
            }
            m_price += c->get_price();
        }
        return "盒子（" + result + ")";
    }
};

void client(Component* node){
    std::cout << "结构:" << node->operation() << std::endl;
    std::cout << "价格:" << node->get_price();
}

int main(){
    Leaf simple(5.0f);
    client(&simple);

    std::cout << "\n\n";

    Composite tree;
    Composite branch1;
    Leaf leaf1(5.0f);
    Leaf leaf2(5.0f);
    Leaf leaf3(5.0f);
    branch1.add(&leaf1);
    branch1.add(&leaf2);
    // leaf1.set_parent(&branch1);
    // leaf2.set_parent(&branch1);
    // branch1.set_parent(&tree);
    tree.add(&branch1);
    tree.add(&leaf3);
    // leaf3.set_parent()
    client(&tree);
    std::cout << "\n\n";
}