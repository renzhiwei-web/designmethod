#pragma once
#include <iostream>
#include <string>
#include "./utility/Singleton.hpp"
using namespace yazi::utility;
class Person
{
    friend class Singleton<Person>;
private:
    string name;
private:
    Person(const string& name){
        this->name = name;
        cout << "person object is created" << endl;
    };
    Person(const Person &){}
    Person & operator = (const Person &);
    ~Person(){
        cout << "person object is deleted" << endl;
    };
public:
    void show(){
        cout << name << endl;
    }
};
