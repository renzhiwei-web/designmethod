#include <iostream>

// 访问者设计模式：许定义一些不改变数据结构的前提下的操作。通过这种方式，可以在不修改元素类的情况下定义新的操作。访问者模式常用于对复杂对象结构进行操作，而又不希望在这些对象上破坏封装性。
// 访问者设计模式不符合开闭原则，想要修改功能，必须修改具体类的实现

class Circle;
class Rectangle;

class IVisitor{
public:
    // virtual ~IVisitor(){}
    virtual void visit(Circle *circle) = 0;
    virtual void visit(Rectangle* rectangle) = 0;
};



class IShape{
public:
    virtual void accept(IVisitor *visitor) = 0;
    virtual ~IShape(){}
};

class Circle : public IShape{
private:
    unsigned int m_radius;
public:
    Circle(unsigned int radius):m_radius(radius){}
    unsigned int getRadius(){
        return m_radius;
    }

    void accept(IVisitor* visitor) override{
        visitor->visit(this);
    }
};

class Rectangle : public IShape{
private:
    unsigned int m_width;
    unsigned int m_height;
public:
    Rectangle(unsigned int width,unsigned int height):m_width(width),m_height(height){}
    unsigned int getWidth() {
        return m_width;
    }

    unsigned int getHeight() {
        return m_height;
    }

    void accept(IVisitor* visitor) override{
        visitor->visit(this);
    }
};
class MoveVisitor : public IVisitor{
private:
    int m_deltax;
    int m_deltay;
public:
    MoveVisitor(int deltax,int deltay):m_deltax(deltax),m_deltay(deltay){}
    void visit(Circle *circle){
        std::cout << "Moving circle with radius " << circle->getRadius() << " by (" << m_deltax << ", " << m_deltay << ")" << std::endl;
    }
    void visit(Rectangle* rectangle) {
        std::cout << "Moving rectangle with width " << rectangle->getWidth() << " and height " << rectangle->getHeight() << " by (" << m_deltax << ", " << m_deltay << ")" << std::endl;
    }
};


class ScaleVisitor : public IVisitor{
private:
    double m_scaleFactor;
public:
    ScaleVisitor(double scaleFactor):m_scaleFactor(scaleFactor){}
    void visit(Circle *circle){
        std::cout << "Scaling circle with radius " << circle->getRadius() << " by factor " << m_scaleFactor << std::endl;
    }
    void visit(Rectangle* rectangle) {
        std::cout << "Scaling rectangle with width " << rectangle->getWidth() << " and height " << rectangle->getHeight() << " by factor " << m_scaleFactor << std::endl;
    }
};
int main(int argc, char const *argv[])
{
    Circle circle(5);
    Rectangle rectangle(10, 8);

    MoveVisitor moveVisitor(2, 3);
    ScaleVisitor scaleVisitor(1.5);

    // 执行移动操作
    circle.accept(&moveVisitor);
    rectangle.accept(&moveVisitor);
    std::cout << std::endl;
    // 执行缩放操作
    circle.accept(&scaleVisitor);
    rectangle.accept(&scaleVisitor);
    return 0;
}
