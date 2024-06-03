#include <iostream>
#include <string>
#include <vector>

using std::string;

// 命令设计模式，将参数封装在对象中进行传递

class Kitchen{
private:
    Kitchen(){}
public:
    static Kitchen* getInstance(){
        static Kitchen* instance = new Kitchen();
        return instance;
    }

    void prepareFood(const string food){
        std::cout << "kitchen is perparing food " << food << std::endl;
    }
};

class Command{
public:
    virtual ~Command(){}
    virtual void execute() const = 0;
};

class Order : public Command{
private:
    Kitchen* m_kitchen;
    std::vector<string> m_foods;
public:
    Order(Kitchen* kitchen,std::vector<string> foods) : m_kitchen(kitchen),m_foods(foods){

    }
    virtual ~Order(){}
    virtual void execute() const override{
        std::cout << "order is need to process by kitchen\n";
        for (const auto& food : m_foods){
            m_kitchen->prepareFood(food);
        }
    }
};

class Waiter{
private:
    Command* m_command;
public:
    ~Waiter(){
        delete m_command;
    }
    void orderUp(Command* command){
        std::cout << "waiter is submit order\n";
        m_command = command;
        m_command->execute();
    }
};

class Client{
public:
    void orderFood(Waiter& waiter,std::vector<string> foods){
        waiter.orderUp(new Order(Kitchen::getInstance(),foods));
    }
};

int main(int argc, char const *argv[])
{
    Client client;
    Waiter waiter;
    client.orderFood(waiter,{"fff","000","111100"});
    return 0;
}
