#include <iostream>
#include <string>
#include <unordered_map>


// 享元设计模式是通过将为了解决大量相似对象占据过多内存的问题，通过将对象中相同的部分提取共用，以达到减少内存占用的目的

// 例子：设计一个游戏，游戏种有三种怪兽，SharedState描述的是怪兽之间共同的部分
// uniquestate描述的是怪兽之间不同的部分

class SharedState{
protected:
    std::string m_appearance;
    int m_health;
    int m_attack;
public:
    virtual ~SharedState(){}
    SharedState(const std::string& appearance,const int health,const int attack):m_appearance(appearance),m_health(health),m_attack(attack){}
    void display() const{
        std::cout << "Appearance: " + m_appearance << " Health " << m_health << " Attack " << m_attack << std::endl;
    }
    std::string get_appearance() const{
        return m_appearance;
    }
    int get_health() const{
        return m_health;
    }
    int get_attack() const{
        return m_attack;
    }
    virtual void attack() const = 0;
};

class GiantMonster : public SharedState{
public:
    GiantMonster():SharedState("Giant",100,20){
    }
    void attack() const override{
        std::cout << "Giant Monster is attacking\n";
    }
    ~GiantMonster(){}
};

class SkeletonMonster : public SharedState{
public:
    SkeletonMonster():SharedState("Skeleton",50,10){
    }
    void attack() const override{
        std::cout << "Skeleton Monster is attacking\n";
    }
    ~SkeletonMonster(){}
};

class SlimeMonster : public SharedState{
public:
    SlimeMonster():SharedState("Slime",20,20){
    }
    void attack() const override{
        std::cout << "Slime Monster is attacking\n";
    }
    ~SlimeMonster(){}
};

class UniqueState{
private:
    int m_ar;
    int m_mr;
public:
    ~UniqueState(){}
    UniqueState() = default;
    UniqueState(const int ar,const int mr) : m_ar(ar),m_mr(mr){}
    void display() const{
        std::cout << "armor resistance is " << m_ar << " maigc resistance is " << m_mr << std::endl;
    }
};

class Monster{
private:
    SharedState *m_sharedState;
public:
    Monster(SharedState * sharedState) : m_sharedState(sharedState){}

    void operation(const UniqueState& uniquestate){
        m_sharedState->display();
        uniquestate.display();
    }
};

class MonsterFactory{
private:
    GiantMonster* giant_monster = nullptr;
    SkeletonMonster* skeleton_monster = nullptr;
    SlimeMonster* slime_monster = nullptr;

    Monster *giant_monster_m = nullptr;
    Monster *skeleton_monster_m = nullptr;
    Monster *slime_monster_m = nullptr;


    std::unordered_map<std::string,UniqueState> giantMonsterMap;
    std::unordered_map<std::string,UniqueState> skeletonMonsterMap;
    std::unordered_map<std::string,UniqueState> slimeMonsterMap;

    std::string getKey(const int ar,const int mr){
        return std::to_string(ar) + '_' + std::to_string(mr);
    }
    void list_giant_monster(){
        std::cout << "Giant Monster\n";
        for(const auto& item : giantMonsterMap){
            giant_monster_m->operation(item.second);
        }
    }

    void list_skeleton_monster(){
        std::cout << "Skeleton Monster\n";
        for(const auto& item : skeletonMonsterMap){
            skeleton_monster_m->operation(item.second);
        }
    }

    void list_slime_monster(){
        std::cout << "Slime Monster\n";
        for(const auto& item : slimeMonsterMap){
            slime_monster_m->operation(item.second);
        }
    }
    
public:
    enum class Type{
        Giant,
        Skeleton,
        Slime
    };
    void add_monster(Type type,const int ar,const int mr){
        std::string key = getKey(ar,mr);
        switch (type)
        {
        case Type::Giant:
            if(giant_monster == nullptr){
                giant_monster = new GiantMonster();
                giant_monster_m = new Monster(giant_monster);
            }
            giantMonsterMap[key] = UniqueState(ar,mr);
            break;
        case Type::Skeleton:
            if(skeleton_monster == nullptr){
                skeleton_monster = new SkeletonMonster();
                skeleton_monster_m = new Monster(skeleton_monster);
            }
            skeletonMonsterMap[key] = UniqueState(ar,mr);
            break;
        case Type::Slime:
            if(slime_monster == nullptr){
                slime_monster = new SlimeMonster();
                slime_monster_m = new Monster(slime_monster);
            }
            slimeMonsterMap[key] = UniqueState(ar,mr);
            break;
        default:
            break;
        }
    }

    void list(){
        list_giant_monster();
        list_skeleton_monster();
        list_slime_monster();
    }

    ~MonsterFactory(){
        if (giant_monster != nullptr)
        {
            delete giant_monster;
            delete giant_monster_m;
        }
        if (skeleton_monster != nullptr)
        {
            delete skeleton_monster;
            delete skeleton_monster_m;
        }
        
        if (slime_monster != nullptr)
        {
            delete slime_monster;
            delete slime_monster_m;
        }
        
        
    }
};



int main(int argc, char const *argv[])
{
    using Type = MonsterFactory::Type;
    MonsterFactory factory;
    factory.add_monster(Type::Giant,40,20);
    factory.add_monster(Type::Skeleton,20,10);
    factory.add_monster(Type::Slime,10,10);
    factory.add_monster(Type::Giant,30,20);
    factory.list();
    return 0;
}
