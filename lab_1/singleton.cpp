#include <iostream>
#include <string>
using namespace std;

class Singleton {
   protected:
    Singleton(string value) { message = value; }
    static Singleton* singleton;
    string message;

   public:
    Singleton(Singleton& other) = delete;
    void operator=(const Singleton&) = delete;

    static Singleton* instance(string value);

    string get() { return message; }
};

Singleton* Singleton::singleton = nullptr;

Singleton* Singleton::instance(string value) {
    if (singleton == nullptr) {
        singleton = new Singleton(value);
    }
    return singleton;
}
int main() {
    Singleton* single1 = Singleton::instance("I'm number one.");
    Singleton* single2 = Singleton::instance("I'm number two.");
    string answ1 = single1->get();
    string answ2 = single2->get();
    cout << "We've created the first object: " << answ1 << endl;
    cout << "We've created a second object: " << answ2 << endl;
    cout << "The second object does not create a new one, but returns the first one." << endl;
    return 0;
}