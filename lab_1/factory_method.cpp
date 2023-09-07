#include <iostream>
#include <string>
using namespace std;

class Product {
   public:
    virtual ~Product() {}
    virtual string operation() const = 0;
    void get_info() { cout << "model: " << model << "\nsize: " << size << "\ncolor: " << color << endl; }

   protected:
    string color;
    int model;
    int size;
};

class Smartphone1 : public Product {
   public:
    Smartphone1(string new_color, int new_model, int new_size) {
        color = new_color;
        model = new_model;
        size = new_size;
    }
    string operation() const override { return "Smartphone1"; }
};

class Smartphone2 : public Product {
   public:
    Smartphone2(string new_color, int new_model, int new_size) {
        color = new_color;
        model = new_model;
        size = new_size;
    }
    string operation() const override { return "Smartphone2"; }
};

class Smartphone3 : public Product {
   public:
    Smartphone3(string new_color, int new_model, int new_size) {
        color = new_color;
        model = new_model;
        size = new_size;
    }
    string operation() const override { return "Smartphone3"; }
};

class Creator {
   public:
    virtual ~Creator(){};
    virtual Product* factory_method() const = 0;
    string some_operation() const {
        Product* product = this->factory_method();
        string result = product->operation();

        delete product;
        return result;
    }

    void get_info() {
        Product* product = this->factory_method();
        product->get_info();
    }
};

class SmartphoneCreator1 : public Creator {
   public:
    Product* factory_method() const override { return new Smartphone1("red", 3310, 100); }
};

class SmartphoneCreator2 : public Creator {
   public:
    Product* factory_method() const override { return new Smartphone2("green", 2215, 110); }
};

class SmartphoneCreator3 : public Creator {
   public:
    Product* factory_method() const override { return new Smartphone3("white", 1188, 50); }
};

int main() {
    Creator* creator = new SmartphoneCreator1();
    Creator* creator2 = new SmartphoneCreator2();
    Creator* creator3 = new SmartphoneCreator3();

    creator->get_info();
    cout << endl;
    creator2->get_info();
    cout << endl;
    creator3->get_info();

    return 0;
}
