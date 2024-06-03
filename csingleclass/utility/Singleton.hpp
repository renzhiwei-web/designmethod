#pragma once
#include <iostream>
using namespace std;
namespace yazi{
namespace utility{

// 这种就是线程安全的懒汉模式；
template <class T>
class Singleton
{
    
public:
    static T * instance(const string& name){
        if (m_instance == nullptr){
            m_instance = new T(name);
        }
        return m_instance;
    }
private:
    Singleton(){};
    Singleton(const Singleton<T> &);
    ~Singleton(){
        cout << "delete singleton object" << endl;
    }
    Singleton<T> & operator = (const Singleton<T>);
private:
    static T * m_instance;
};
template <class T>
T * Singleton<T>::m_instance = nullptr;

}
}