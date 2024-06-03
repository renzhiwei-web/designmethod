#include <iostream>
#include <vector>
#include <ctime>
#include <string>

// 备忘录设计模式：在不破坏封装性的前提下，捕获一个对象的内部状态。并在该对象之外保留这个状态。
// 这样以后就可以将该对象恢复到原先保存的状态



class Memento{
    friend class Hero;
private:
    unsigned int m_state;
    
public:

    std::string m_date;

    Memento(unsigned int state):m_state(state){
        std::time_t now = std::time(0);
        m_date = std::ctime(&now);
    }

    std::string get_date(){
        return m_date;
    }
};

class Hero{
private:
    unsigned int m_state;
public:
    Hero(int state):m_state(state){
        std::cout << "Init state is " << state << std::endl;
    }

    void fight(){
        std::cout << "attacked\n";
        m_state -= rand() % 20;
        std::cout << "current state is " << m_state << std::endl;
    }

    Memento* save(){
        return new Memento(m_state);
    }

    void restore(Memento* memento){
        m_state = memento->m_state;
        std::cout << "current state is " << m_state << std::endl;
    }
};


class Caretaker{
private:
    Hero* m_hero;
    std::vector<Memento*> m_mementos;
public:
    Caretaker(Hero* hero):m_hero(hero){}
    ~Caretaker(){
        for(auto item : m_mementos){
            delete item;
        }
    }

    void backup(){
        std::cout << "saving state...\n";
        m_mementos.push_back(m_hero->save());
    }

    void undo(){
        if (!m_mementos.size())
        {
            std::cout << "there is not archive\n";
            return;
        }

        Memento* memento =  m_mementos.back();
        m_mementos.pop_back();
        std::cout << "current state is restored to " << memento->get_date() << "\n";
        m_hero->restore(memento);
        delete memento;
    }
};

int main(int argc, char const *argv[])
{
    std::srand(static_cast<unsigned int>(std::time(NULL)));
    Hero* hero = new Hero(100);
    Caretaker* caretaker = new Caretaker(hero);
    caretaker->backup();
    hero->fight();
    caretaker->backup();
    hero->fight();
    caretaker->undo();
    delete hero;
    delete caretaker;
    return 0;
}
