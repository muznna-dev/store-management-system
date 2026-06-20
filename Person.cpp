#include "pch.h"
#include "Person.h"

// ===== Person =====
Person::Person() : name(""), age(0) {}
Person::Person(string n, int a) : name(n), age(a) {}
Person::Person(const Person& other) : name(other.name), age(other.age) {}

Person& Person::operator=(const Person& other) {
    if (this != &other) { name = other.name; age = other.age; }
    return *this;
}

Person::~Person() {}

void   Person::setName(string n) { name = n; }
string Person::getName()  const  { return name; }
void   Person::setAge(int a)     { age = a; }
int    Person::getAge()   const  { return age; }

void Person::display() const {
    cout << "Name: " << name << "    Age: " << age;
}

// ===== Employee =====
Employee::Employee() : Person(), employeeID(0), role(""), salary(0.0) {}

Employee::Employee(string n, int a, int ID, string r, double s)
    : Person(n, a), employeeID(ID), role(r), salary(s) {}

Employee::Employee(const Employee& other)
    : Person(other), employeeID(other.employeeID), role(other.role), salary(other.salary) {}

Employee& Employee::operator=(const Employee& other) {
    if (this != &other) {
        Person::operator=(other);
        employeeID = other.employeeID;
        role       = other.role;
        salary     = other.salary;
    }
    return *this;
}

Employee::~Employee() {}

void   Employee::setEmployeeID(int id)     { employeeID = id; }
int    Employee::getEmployeeID()  const    { return employeeID; }
void   Employee::setEmployeeRole(string r) { role = r; }
string Employee::getEmployeeRole() const   { return role; }
void   Employee::setSalary(double s)       { salary = s; }
double Employee::getSalary()    const      { return salary; }

// Pre-increment: advance employeeID by 1
Employee& Employee::operator++() { ++employeeID; return *this; }
// Post-increment: return copy before advancing
Employee  Employee::operator++(int) { Employee tmp(*this); ++employeeID; return tmp; }
// Pre-decrement
Employee& Employee::operator--() { --employeeID; return *this; }
// Post-decrement
Employee  Employee::operator--(int) { Employee tmp(*this); --employeeID; return tmp; }

void Employee::display() const {
    cout << "Employee:\n";
    Person::display();
    cout << "\nEmployee ID: " << employeeID
         << "   Role: "       << role
         << "   Salary: "     << salary;
}

// ===== Manager =====
Manager::Manager() : Employee(), bonus(0.0), teamSize(0) {}

Manager::Manager(string n, int a, int ID, string r, double s, double b, int sz)
    : Employee(n, a, ID, r, s), bonus(b), teamSize(sz) {}

Manager::Manager(const Manager& other)
    : Employee(other), bonus(other.bonus), teamSize(other.teamSize) {}

Manager& Manager::operator=(const Manager& other) {
    if (this != &other) {
        Employee::operator=(other);
        bonus    = other.bonus;
        teamSize = other.teamSize;
    }
    return *this;
}

Manager::~Manager() {}

void   Manager::setBonus(double b)  { bonus = b; }
double Manager::getBonus()   const  { return bonus; }
void   Manager::setTeamSize(int sz) { teamSize = sz; }
int    Manager::getTeamSize() const { return teamSize; }

void Manager::display() const {
    cout << "Manager:\n";
    Employee::display();
    cout << "\nBonus: " << bonus << "   Team Size: " << teamSize;
}
