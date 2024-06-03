#include <iostream>

// 状态设计模式的思想：一个拥有内部状态的对象，在不同状态下，行为也会不同。


class Machine;

class State{
protected:
    Machine* m_machine;
public:
    virtual ~State(){}
    State(Machine* machine) : m_machine(machine){}
    virtual void insertCoin() = 0;
    virtual void selectProduct() = 0;
    virtual void dispense() = 0;
};


class NoCoinState;
class HasCoinState;
class SoldState;

class Machine{
private:
    //未投币状态
    State* m_noCoinState;
    //已投币状态
    State* m_hasCoinState;
    //出售状态
    State* m_soldState;
    //当前状态
    State* m_currentState;
public:
    ~Machine(){
        delete m_noCoinState;
        delete m_hasCoinState;
        delete m_soldState;
    }
    Machine(){}
    // Machine(State* noCoinState,State* hasCoinState,State* soldState):
    // m_noCoinState(noCoinState),m_hasCoinState(hasCoinState),m_soldState(soldState)
    // {}
    // void init(State* noCoinState,State* hasCoinState,State* soldState){
    //     m_noCoinState = noCoinState;
    //     m_hasCoinState = hasCoinState;
    //     m_soldState = soldState;
    //     m_currentState = m_noCoinState;
    // }

    void set_m_noCoinState(State* noCoinState){
        m_noCoinState = noCoinState;
        m_currentState = noCoinState;
    }

    void set_m_hasCoinState(State* hasCoinState){
        m_hasCoinState = hasCoinState;
    }

    void set_m_soldState(State* soldState){
        m_soldState = soldState;
    }
    void setState(State* state){
        m_currentState = state;
    }

    State* getNoCoinState(){
        return m_noCoinState;
    }

    State* getHasCoinState(){
        return m_hasCoinState;
    }

    State* getSoldState(){
        return m_soldState;
    }
    void insertCoin(){
        m_currentState->insertCoin();
    }
    void selectProduct(){
        m_currentState->selectProduct();
    }
    void dispense(){
        m_currentState->dispense();
    }
};

class NoCoinState : public State{
private:
    void set_machine(){
        m_machine->set_m_noCoinState(this);
    }
public:
    NoCoinState(Machine* machine) : State(machine){
        set_machine();
    }
    virtual void insertCoin() override{
        std::cout << "已投币\n";
        m_machine->setState(m_machine->getHasCoinState());
    }
    virtual void selectProduct() override{
        std::cout << "请先投币\n";
    }
    virtual void dispense() override{
        std::cout << "请先投币\n";
    }
};

class HasCoinState : public State{
private:
    void set_machine(){
        m_machine->set_m_hasCoinState(this);
    }
public:
    HasCoinState(Machine* machine) : State(machine){
        set_machine();
    }
    virtual void insertCoin() override{
        std::cout << "已投币，请勿重复投币\n";
    }
    virtual void selectProduct() override{
        std::cout << "商品已选择\n";
        m_machine->setState(m_machine->getSoldState());
    }
    virtual void dispense() override{
        std::cout << "请先选择商品\n";
    }
};

class SoldState : public State{
private:
    void set_machine(){
        m_machine->set_m_soldState(this);
    }
public:
    SoldState(Machine* machine) : State(machine){
        set_machine();
    }
    virtual void insertCoin() override{
        std::cout << "正在出售商品，请稍等\n";
    }
    virtual void selectProduct() override{
        std::cout << "正在出售商品，请稍等\n";
    }
    virtual void dispense() override{
        std::cout << "商品已发放\n";
        m_machine->setState(m_machine->getNoCoinState());
    }
};




int main(int argc, char const *argv[])
{
    Machine *machine = new Machine();
    State* m_noCoinState = new NoCoinState(machine);

    State* m_hasCoinState = new HasCoinState(machine);

    State* m_soldState = new SoldState(machine);
    // machine->init(m_noCoinState,m_hasCoinState,m_soldState);

    std::cout << "=======直接选择商品=======\n";
    machine->selectProduct();
    std::cout << "======投币--->选择商品--->发放商品=======\n";
    machine->insertCoin();
    machine->selectProduct();
    machine->dispense();

    std::cout << "=======投币--->发放商品=======\n";
    machine->insertCoin();
    machine->dispense();
    delete machine;
    return 0;
}
