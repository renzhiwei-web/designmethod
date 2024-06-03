#include<iostream>
#include<vector>
#include<string>

// 创建者设计模式适用于构建复杂的对象
// 将一个复杂对象的构建和它的表示分离，使得同样的构建过程可以创建不同的表示。
class SimpleHouse{
public:
    std::vector<std::string> m_parts;
    void printParts() const{
        std::cout << "SimpleHouse include: \n";
        for(int i = 0;i < m_parts.size();i++){
            std::cout << m_parts[i] << "\n";
        }
        std::cout << "-------------------\n";
    }
};

class Builder{
public:
    virtual ~Builder(){}
    virtual void reset() = 0;
    virtual void makeBaseHouse() = 0;
    virtual void makeGarage() = 0;
    virtual void makePool() = 0;
};

class SimpleHouseBuilder : public Builder{
private:
    SimpleHouse* m_simplehouse;
public:

    SimpleHouseBuilder(){
        reset();
    }
    virtual void reset() override{
        m_simplehouse = new SimpleHouse();
    }
    virtual void makeBaseHouse() override{
        m_simplehouse->m_parts.push_back("BaseHouse");
    }

    virtual void makeGarage() override{
        m_simplehouse->m_parts.push_back("garage");
    }

    virtual void makePool() override{
        m_simplehouse->m_parts.push_back("pool");
    }

    SimpleHouse* getResult(){
        SimpleHouse* result = m_simplehouse;
        reset();
        return result;
    }

    virtual ~SimpleHouseBuilder(){
        delete m_simplehouse;
    }
};

class Director
{
private:
    Builder* m_builder;
public:
    Director() {
    }

    ~Director() {}

    void setBuilder(Builder* builder){
        m_builder = builder;
    }

    void makeSimpleHouse(){
        m_builder->makeBaseHouse();
        m_builder->makeGarage();
    }

    void makefullfuncHouse(){
        this->makeSimpleHouse();
        m_builder->makePool();
    }
};

int main()
{
    Director director;
    SimpleHouseBuilder *builder = new SimpleHouseBuilder();
    director.setBuilder(builder);
    director.makeSimpleHouse();
    SimpleHouse *simpleHouse = builder->getResult();
    simpleHouse->printParts();
    delete simpleHouse;
    builder = new SimpleHouseBuilder();
    director.setBuilder(builder);
    director.makefullfuncHouse();
    simpleHouse = builder->getResult();
    simpleHouse->printParts();
    delete simpleHouse;
    delete builder;
    return 0;
}
