#include <iostream>
#include <string>
using namespace std;

class Singleton {
   protected:
    Singleton(string user_login, string user_password) {
        login = user_login;
        password = user_password;
    }
    static Singleton* singleton;
    string login;
    string password;

   public:
    Singleton(Singleton& other) = delete;
    void operator=(const Singleton&) = delete;

    static Singleton* instance(string user_login, string user_password);

    string get_login() { return login; }
    string get_password() { return password; }
};

Singleton* Singleton::singleton = nullptr;

Singleton* Singleton::instance(string user_login, string user_password) {
    if (singleton == nullptr) {
        singleton = new Singleton(user_login, user_password);
    }
    return singleton;
}
int main() {
    Singleton* single1 = Singleton::instance("login", "password");
    string login = single1->get_login();
    string password = single1->get_password();
    cout << "logging in for the first time.\nlogin: " << login << "\npassword: " << password << endl;
    Singleton* single2 = Singleton::instance("new_login", "new_password");
    string new_login = single2->get_login();
    string new_password = single2->get_password();
    cout << "trying to log in a second time.\nlogin: " << new_login << "\npassword: " << new_password << endl;
    cout << "the second authorization failed and gave us back our old login and password " << endl;
    return 0;
}