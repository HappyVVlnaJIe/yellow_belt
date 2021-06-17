#include <iostream>

using namespace std;

class Animal {
public:
    Animal(const string& Name) : Name(Name) {

    }
    const string Name;
};


class Dog: public Animal {
public:
    Dog(std::string Name) : Animal(Name) {

    }
    void Bark() {
        cout << Name << " barks: woof!" << endl;
    }
};

//int main() {
//    Dog dog("god");
//    dog.Bark();
//    return 0;
//}