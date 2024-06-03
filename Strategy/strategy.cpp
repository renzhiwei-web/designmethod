#include <iostream>
#include <string>

// 策略设计模式：与状态设计模式相似，但是不涉及到内部状态之间的变化。
// 内部的策略不同，行为也不同

class IStrategy{
public:
    virtual std::string fightAlgorithm() = 0;
    virtual ~IStrategy(){}
};

class Knife : public IStrategy{
public:
    std::string fightAlgorithm() override{
        return "use Knife";
    }
};

class Axe : public IStrategy{
public:
    std::string fightAlgorithm() override{
        return "use Axe";
    }
};

class Hero{
private:
    IStrategy* m_weapon;
public:
    Hero(IStrategy* weapon):m_weapon(weapon){}
    void set(IStrategy* weapon){m_weapon = weapon;}
    void fight() {
        std::cout << m_weapon->fightAlgorithm() << std::endl;
    }
};

int main(int argc, char const *argv[])
{
    Knife knife;
    Hero hero(&knife);
    hero.fight();
    Axe axe;
    hero.set(&axe);
    hero.fight();
    return 0;
}
