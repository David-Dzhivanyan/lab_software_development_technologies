#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

//АДРЕСС
class Address {
public:
    Address(string new_street, string new_city, string new_state, int new_postal_code, string new_country) {
        street = new_street;
        city = new_city;
        state = new_state;
        postal_code = new_postal_code;
        country = new_country;
    }
protected:
    string street;
    string city;
    string state;
    int postal_code;
    string country;
};

//АДМИН
class Admin {
public:
    Admin(string name) {
        nameCategory = name;
    }
protected:
    string nameCategory;
};

//ПОДПИЩИК
class Subscriber {
public:
    Subscriber(string name, Address* new_address) {
        nameCategory = name;
        address = new_address;
    }

    Address* get_address() {
        return address;
    }
protected:
    string nameCategory;
    Address* address;
};

//КАТЕГОРИЯ
class SubscriberCategory {
public:
    SubscriberCategory(string name) {
        nameCategory = name;
    }

    string get_name () {
        return nameCategory;
    }

    Subscriber* search_subscriber(string name) {
        return subscriber_list[name];
    }

protected:
    string nameCategory;
    map<string, Subscriber*> subscriber_list;
    map<string, Admin*> admin_List;

    void new_subscriber(string name, Address* address) {
        Subscriber* subscriber = new Subscriber(name, address);

        subscriber_list.insert(make_pair(name, subscriber));
    }

    void add_admin(string name) {
        Admin* admin = new Admin(name);

        admin_List.insert(make_pair(name, admin));
    }

    void changing_subscriber_data(string name, Address* address) {
        Subscriber* subscriber = new Subscriber(name, address);

        subscriber_list[name] = subscriber;
    }
};


//САМА АДРЕСНАЯ КНИГА
class SingletonAddressBook {
protected:
    SingletonAddressBook() {}
    static SingletonAddressBook* singleton;
    map<string, SubscriberCategory*> categories;

public:
    SingletonAddressBook(SingletonAddressBook& other) = delete;
    void operator=(const SingletonAddressBook&) = delete;

    void addCategory(string name) {
        SubscriberCategory* category = new SubscriberCategory(name);

        categories.insert(make_pair(name, category));
    }

    map<string, SubscriberCategory*> get_categories() {
        return categories;
    }

    static SingletonAddressBook* instance();
};

SingletonAddressBook* SingletonAddressBook::singleton = nullptr;

SingletonAddressBook* SingletonAddressBook::instance() {
    if (singleton == nullptr) {
        singleton = new SingletonAddressBook();
    }

    return singleton;
}


//АВТОРИЗАЦИЯ
class Auth {
protected:
    Auth(string user_login) {
        login = user_login;
    }

    static Auth* singleton;
    string login;

public:
    Auth(Auth& other) = delete;
    void operator=(const Auth&) = delete;

    static Auth* instance(string user_login);

    string get_login() { return login; }
};

Auth* Auth::singleton = nullptr;

Auth* Auth::instance(string user_login) {
    if (singleton == nullptr) {
        singleton = new Auth(user_login);
    }
    return singleton;
}

int main() {
    SingletonAddressBook* addressBook = SingletonAddressBook::instance();
    addressBook->addCategory("Russia");
    addressBook->addCategory("USA");
    map<string, SubscriberCategory*> categories = addressBook->get_categories();

    for (const auto& pair : categories) {
        const string& name = pair.first;
        SubscriberCategory* age = pair.second;
        cout << "Name: " << name << ", Category: " << age << endl;
    }

    Auth* auth = Auth::instance("David");

    



    return 0;
}