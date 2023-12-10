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
        map<string, Subscriber*>::iterator it;
        it = subscriber_list.find(name);
        if(it != subscriber_list.end()){
            return true;
        }
        return false;
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
            cout << "User not found" << endl;
        }
    }
};


//САМА АДРЕСНАЯ КНИГА
class SingletonAddressBook {
protected:
    SingletonAddressBook() {}
    static SingletonAddressBook* singleton;
    map<string, Admin*> admin_list;

public:
    SingletonAddressBook(SingletonAddressBook& other) = delete;
    void operator = (const SingletonAddressBook&) = delete;
    map<string, SubscriberCategory*> categories;

    void add_admin(string name) {
        Admin* admin = new Admin(name);

        admin_list.insert(make_pair(name, admin));
    }

    bool is_admin(string login){
        map<string, Admin*>::iterator it;
        it = admin_list.find(login);
        if(it != admin_list.end()) {
            return true;
        }
        return false;
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

string choose_category(SingletonAddressBook* addressBook, map<string, SubscriberCategory*> categories) {
    cout << "Select an category " << endl;
    addressBook->print_categories();
    string category;
    cin >> category;
    if(categories[category] == 0) {
        cout << "Error, category does not exist" << endl;
        return "";
    } else {
        cout << "You have selected the category : " << category << endl;
        return category;
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

    cout << "You have successfully logged in as " << login << endl;

    while(key != 'q') {
        map<string, SubscriberCategory*> categories;
        string category;
        Address* address;
        string name;
        bool flag = true;

        if(addressBook->is_admin(auth->get_login())){
            cout << "Select an action " << endl;
            cout << "1: Add a category " << endl;
            cout << "2: Select an existing " << endl;
            cin >> key;
            switch (key) {
                case '1':
                    add_category(addressBook);
                    flag = false;
                    break;
                case '2':
                    categories = addressBook->get_categories();
                    category = choose_category(addressBook, categories);
                    if(category == "") flag = false;
                    break;
                default:
                    cout << "ERROR!";
                    continue;
            }
            while(flag){
                cout << "Select an action " << endl;
                cout << "1: Show user list " << endl;
                cout << "2: Show user information " << endl;
                cout << "3: Add user" << endl;
                cout << "4: Change user" << endl;
                cout << "5: Select another category" << endl;
                cin >> key;

                switch (key) {
                    case '1':
                        addressBook->categories[category]->print_subscriber_list();
                        break;
                    case '2':
                        cout << "Enter user name :" << endl;
                        cin >> name;
                        addressBook->categories[category]->print_subscriber(name);
                        break;
                    case '3':
                        cout << "Enter user name :" << endl;
                        cin >> name;
                        address = enter_address();
                        addressBook->categories[category]->add_Subscriber(name, address);
                        break;
                    case '4':
                        cout << "Enter user name :" << endl;
                        cin >> name;
                        address = enter_address();
                        addressBook->categories[category]->changing_subscriber_data(name, address);
                        break;
                    case '5':
                        flag = false;
                        break;
                    default:
                        cout << "ERROR!";
                        continue;
                }
            }
        } else {
            cout << "Select a category " << endl;
            categories = addressBook->get_categories();
            category = choose_category(addressBook, categories);
            if(category == "") flag = false;
            name = auth->get_login();

            while (flag) {
                cout << "Select an action " << endl;
                cout << "1: Show user list " << endl;
                cout << "2: Show user information " << endl;
                cout << "3: Edit/Add your own" << endl;
                cout << "4: Select another category" << endl;
                cin >> key;

                switch (key) {
                    case '1':
                        addressBook->categories[category]->print_subscriber_list();
                        break;
                    case '2':
                        cout << "Enter user name :" << endl;
                        cin >> name;
                        addressBook->categories[category]->print_subscriber(name);
                        break;
                    case '3':
                        address = enter_address();

                        if(addressBook->categories[category]->is_found(name)) {
                            addressBook->categories[category]->changing_subscriber_data(name, address);
                        } else {
                            cout << "User does not exist";
                            cout << "Press Y to create a user with that name: " << name << endl;
                            cin >> key;
                            if(key == 'y'){
                                addressBook->categories[category]->add_Subscriber(name, address);
                            }
                        }
                        break;
                    case '4':
                        flag = false;
                        break;
                    default:
                        cout << "ERROR!";
                        continue;
                }
            }
        }
    }

    return 0;
}