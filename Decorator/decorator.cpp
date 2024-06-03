#include <iostream>
#include <string>
#include <memory>

// 动态地给一个对象添加额外的职责，同时不改变其结构。装饰器模式提供了一种灵活的替代继承方式来扩展功能。

class Shape{
public:
    virtual ~Shape(){}
    virtual void draw() const = 0;
};

class Circle : public Shape{
public:
    ~Circle() {}
    void draw() const override{
        std::cout << "Shape: Circle\n";
    }
};

class Rectangle : public Shape{
public:
    ~Rectangle() {}
    void draw() const override{
        std::cout << "Shape: Rectangle\n";
    }
};

class ShapeDecorator : public Shape{
protected:
    Shape *m_shape;
public:
    virtual ~ShapeDecorator(){}
    ShapeDecorator(Shape *shape) : m_shape(shape){}
    void draw() const override{
        m_shape->draw(); // 装饰器的核心方法，使用装饰器的基类调用被装饰组件的方法。
    }
};

class RedShapeDecorator : public ShapeDecorator{
public:
    ~RedShapeDecorator(){}
    RedShapeDecorator(Shape *shape) : ShapeDecorator(shape){}
    void draw() const override{
        ShapeDecorator::draw();
        std::cout << "color : red\n";
    }
};

class BuleShapeDecorator : public ShapeDecorator{
public:
    ~BuleShapeDecorator(){}
    BuleShapeDecorator(Shape *shape) : ShapeDecorator(shape){}
    void draw() const override{
        ShapeDecorator::draw();
        std::cout << "color : bule\n";
    }
};


void client(std::shared_ptr<Shape> shape){
    shape->draw();
}

int main(int argc, char const *argv[])
{
    std::shared_ptr<Shape> s1 = std::make_shared<Circle>();
    client(s1);
    std::cout << std::endl;
    std::shared_ptr<ShapeDecorator> d1 = std::make_shared<RedShapeDecorator>(s1.get());
    client(d1);
    std::cout << std::endl;

    std::shared_ptr<Shape> s2 = std::make_shared<Rectangle>();
    std::shared_ptr<ShapeDecorator> d2 = std::make_shared<BuleShapeDecorator>(s2.get());
    client(d2);
    return 0;
}
