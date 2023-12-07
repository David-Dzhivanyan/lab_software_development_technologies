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

    void print() {
        cout << "Street: " << street << endl;
        cout << "city: " << city << endl;
        cout << "state: " << state << endl;
        cout << "postal_code: " << postal_code << endl;
        cout << "country: " << country << endl;
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
protected:
    string nameSubscriber;
    Address* address;

public:
    Subscriber(string name, Address* new_address) {
        nameSubscriber = name;
        address = new_address;
    }

    Address* get_address() {
        return address;
    }

    void print() {
        cout << "Name: " << nameSubscriber << endl;
        address->print();
    }
};

//КАТЕГОРИЯ
class SubscriberCategory {
protected:
    string nameCategory;
    map<string, Subscriber*> subscriber_list;

public:
    SubscriberCategory(string name) {
        nameCategory = name;
    }

    void add_Subscriber(string name, Address* address) {
        Subscriber* subscriber = new Subscriber(name, address);

        subscriber_list.insert(make_pair(name, subscriber));
    }

    string get_name () {
        return nameCategory;
    }

    Subscriber* search_subscriber(string name) {
        return subscriber_list[name];
    }

    void print_subscriber (string name) {
        if(is_found(name)){
            subscriber_list[name]->print();
        }
    }

    bool is_found(string name) {
        if(subscriber_list[name] != 0){
            return true;
        } else {
            cout << "User not found" << endl;
            return false;
        }
    }

    void print_subscriber_list () {
        for (const auto& pair : subscriber_list) {
            const string& name = pair.first;
            cout << name << endl;
        }
    }

    void changing_subscriber_data(string name, Address* address) {
        string key;
        if(is_found(name)){
            Subscriber* subscriber = new Subscriber(name, address);
            subscriber_list[name] = subscriber;
        } else {
            cout << "Press Y to create a user with that name: " << name << endl;
            cin >> key;
            if(key == "y"){
                add_Subscriber(name, address);
            }
        }
    }
};


//САМА АДРЕСНАЯ КНИГА
class SingletonAddressBook {
protected:
    SingletonAddressBook() {}
    static SingletonAddressBook* singleton;
    map<string, SubscriberCategory*> categories;
    map<string, Admin*> admin_List;

public:
    SingletonAddressBook(SingletonAddressBook& other) = delete;
    void operator = (const SingletonAddressBook&) = delete;

    void add_admin(string name) {
        Admin* admin = new Admin(name);

        admin_List.insert(make_pair(name, admin));
    }

    bool is_admin(string login){
        if(admin_List[login] != 0) {
            return true;
        } else {
            return false;
        }
    }

    void addCategory(string name) {
        SubscriberCategory* category = new SubscriberCategory(name);

        categories.insert(make_pair(name, category));
    }

    map<string, SubscriberCategory*> get_categories() {
        return categories;
    }

    void print_categories() {
        for (const auto& pair : categories) {
            const string& name = pair.first;
            cout << name << endl;
        }
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


//ФУНКЦИИ
void add_category(SingletonAddressBook* addressBook) {
    string name;
    cout << "Enter the name of the category " << endl;
    cin >> name;
    addressBook->addCategory(name);
}

SubscriberCategory* choose_category(SingletonAddressBook* addressBook, map<string, SubscriberCategory*> categories) {
    cout << "Select an category " << endl;
    addressBook->print_categories();
    string category;
    cin >> category;
    if(categories[category] == 0) {
        cout << "Error, category does not exist" << endl;
        return nullptr;
    } else {
        cout << "You have selected the category : " << category << endl;
        return categories[category];
    }
}

Address* enter_address() {
    string street;
    string city;
    string state;
    int postal_code;
    string country;

    cout << "Enter user street :" << endl;
    cin >> street;
    cout << "Enter user city :" << endl;
    cin >> city;
    cout << "Enter user state :" << endl;
    cin >> state;
    cout << "Enter user postal_code :" << endl;
    cin >> postal_code;
    cout << "Enter user country :" << endl;
    cin >> country;

    return new Address(street, city, state, postal_code, country);
}

//street = new_street;
//city = new_city;
//state = new_state;
//postal_code = new_postal_code;
//country = new_country;

int main() {
    Address* a1 = new Address("Shevskaya", "Volgograd", "Volgogradskaya obl", 40002, "Russia");
    Address* a2 = new Address("Shevskaya", "Volgograd", "Volgogradskaya obl", 40002, "USA");
    SingletonAddressBook* addressBook = SingletonAddressBook::instance();
    addressBook->add_admin("David");
    addressBook->addCategory("Russia");
    addressBook->addCategory("USA");
    map<string, SubscriberCategory*> categories1 = addressBook->get_categories();
    categories1["Russia"]->add_Subscriber("David", a1);
    categories1["Russia"]->add_Subscriber("Sasha", a1);
    categories1["USA"]->add_Subscriber("David", a2);
    categories1["USA"]->add_Subscriber("Dima", a2);

    string login;
    cout << "Login : ";
    cin >> login;

    Auth* auth = Auth::instance(login);

    char key = '0';
    while(key != 'q') {
        map<string, SubscriberCategory*> categories = addressBook->get_categories();
        SubscriberCategory* category;
        Address* address;
        string name;

        if(addressBook->is_admin(auth->get_login())){
            cout << "You have successfully logged in as admin " << login << endl;
            cout << "Select an action " << endl;
            cout << "1: Add a category " << endl;
            cout << "2: Select an existing " << endl;
            cin >> key;
            switch (key) {
                case '1':
                    add_category(addressBook);
                    break;
                case '2':
                    category = choose_category(addressBook, categories);
                    break;
                default:
                    cout << "ERROR!";
                    continue;
            }

            cout << "Select an action " << endl;
            cout << "1: Show user list " << endl;
            cout << "2: Show user information " << endl;
            cout << "3: Add user" << endl;
            cout << "4: Change user" << endl;
            cin >> key;

            switch (key) {
                case '1':
                    category->print_subscriber_list();
                    break;
                case '2':
                    cout << "Enter user name :" << endl;
                    cin >> name;
                    category->print_subscriber(name);
                    break;
                case '3':
                    cout << "Enter user name :" << endl;
                    cin >> name;
                    address = enter_address();
                    category->add_Subscriber(name, address);
                    break;
                case '4':
                    cout << "Enter user name :" << endl;
                    cin >> name;
                    address = enter_address();
                    category->changing_subscriber_data(name, address);
                    break;
                default:
                    cout << "ERROR!";
                    continue;
            }
        } else {
            cout << "You have successfully logged in as " << login << endl;
            cout << "Select a category " << endl;
            category = choose_category(addressBook, categories);

            cout << "Select an action " << endl;
            cout << "1: Show user list " << endl;
            cout << "2: Show user information " << endl;
            cout << "3: Edit/Add your own" << endl;
            cin >> key;

            switch (key) {
                case '1':
                    category->print_subscriber_list();
                    break;
                case '2':
                    cout << "Enter user name :" << endl;
                    cin >> name;
                    category->print_subscriber(name);
                    break;
                case '3':
                    address = enter_address();
                    category->changing_subscriber_data(auth->get_login(), address);
                    break;
                default:
                    cout << "ERROR!";
                    continue;
            }
        };
    }

    return 0;
}