#include <iostream>
#include <memory>
#include <unordered_map>
#include <string>


class Computer
{
private:
    std::unordered_map<std::string,std::string> m_parts;
public:
    Computer() {}
    ~Computer() {

    }
    void audio(const std::string& str){
        m_parts["audio"] = str;
    }

    void keyboard(const std::string& str){
        m_parts["keyboard"] = str;
    }

    void master(const std::string& str){
        m_parts["master"] = str;
    }

    void mouse(const std::string& str){
        m_parts["mouse"] = str;
    }

    void screen(const std::string& str){
        m_parts["screen"] = str;
    }

    void print(){
        for (std::unordered_map<std::string, std::string>::iterator it = m_parts.begin(); it != m_parts.end(); it++)
        {
            std::cout << "key = " << it->first << " value = " << it->second << std::endl;
        }
        std::cout << std::endl;
    }
};

class ComputerBuilder
{
public:
    virtual ~ComputerBuilder() {}
    virtual void buildAudio() = 0;
    virtual void buildComputer() = 0;
    virtual void buildKeyboard() = 0;
    virtual void buildMaster() = 0;
    virtual void buildMouse() = 0;
    virtual void buildScreen() = 0;
};

class HPComputerBuilder : public ComputerBuilder
{
private:
    std::shared_ptr<Computer> computer;
    // Computer *computer;
public:
    HPComputerBuilder() {}
    ~HPComputerBuilder() {}
    void buildAudio() override{
        computer->audio("惠普音响");
    }
    void buildComputer() override{
        computer = std::make_shared<Computer>();
    };
    void buildKeyboard() override{
        computer->keyboard("惠普键盘");
    };
    void buildMaster() override{
        computer->master("惠普主机");
    }
    void buildMouse() override{
        computer->mouse("惠普鼠标");
    }
    void buildScreen() override {
        computer->screen("惠普显示器");
    }

    std::shared_ptr<Computer> getComputer(){
        std::shared_ptr<Computer> result = computer;
        computer.reset();
        return result;
    }
};

class Director
{
private:
    ComputerBuilder *m_builder;
public:
    Director() {}
    ~Director() {}

    void setBuilder(ComputerBuilder *builder){
        m_builder = builder;
    }

    void constructComputer(){
        m_builder->buildComputer();
        m_builder->buildMaster();
        m_builder->buildAudio();
        m_builder->buildKeyboard();
        m_builder->buildMouse();
        m_builder->buildScreen();
    }
};

int main(int argc, char const *argv[])
{
    Director director;
    HPComputerBuilder *builder = new HPComputerBuilder();
    director.setBuilder(builder);
    director.constructComputer();
    std::shared_ptr<Computer> computer = builder->getComputer();
    computer->print();
    delete builder;
    return 0;
}
