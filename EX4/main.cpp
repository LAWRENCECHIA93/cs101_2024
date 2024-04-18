#include <iostream>
#include <string>
using namespace std;

class car {
protected:
    string m_DriveMode;
private:
    int m_MaxSeating;
    int m_price;
    void m_UpdatePrice(int base = 500000) {
        m_price = m_MaxSeating * base;
    }
public:
    string m_brand;
    string m_model;
    int m_year;

    car(string x, string y, int z, int s) {
        m_brand = x;
        m_model = y;
        m_year = z;
        m_MaxSeating = s;
        m_DriveMode = "No-wheel";
    }
    int get_MaxSeating() {
        return this->m_MaxSeating;
    }
    int get_price() {
        return this->m_price;
    }
    string get_DriveMode() {
        return this->m_DriveMode;
    }
};

class BMW_Car : public car {
public:
    BMW_Car(string y, int z, int s) : car("BMW", y, z, s) {
        cout << "Constructing BMW_Car\n";
        m_DriveMode = "Front-wheel";
    }
    string get_DriveMode() {
        return this->m_DriveMode;
    }
};

class BENZ_Car : public car {
public:
    BENZ_Car(string y, int z, int s) : car("BENZ", y, z, s) {
        cout << "Constructing BENZ_Car\n";
        m_DriveMode = "Front-wheel";
    }
    string get_DriveMode() {
        return this->m_DriveMode;
    }
};

int main()
{
    BMW_Car car1("model1", 2020, 5);
    cout << "BMW : Drive Mode = " << car1.get_DriveMode() << endl;
    BENZ_Car car2("model2", 2021, 8);
    cout << "BENZ : Drive Mode = " << car2.get_DriveMode() << endl;
    BENZ_Car car3("model3", 2022, 2);
    cout << "BENZ : Drive Mode = " << car3.get_DriveMode() << endl;

    return 0;
}
