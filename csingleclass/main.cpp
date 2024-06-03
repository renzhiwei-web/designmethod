#include <iostream>
using namespace std;

#include "./person.h"
#include "./utility/Singleton.hpp"
using namespace yazi::utility;

int main(){
    Singleton<Person>::instance("yxg")->show();
}