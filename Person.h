#pragma once
#include "pch.h"

// INHERITANCE BASE CLASS: Person -> Employee -> Manager
class Person {
protected:
    string name;
    int    age;
public:
    Person();
    Person(string n, int a);
    Person(const Person& other);
    Person& operator=(const Person& other);
    virtual ~Person();

    void   setName(string n);
    string getName() const;
    void   setAge(int a);
    int    getAge() const;

    virtual void display() const;
};

// INHERITANCE: Employee derives from Person
class Employee : public Person {
protected:
    int    employeeID;
    string role;
    double salary;
public:
    Employee();
    Employee(string n, int a, int ID, string r, double s);
    Employee(const Employee& other);
    Employee& operator=(const Employee& other);
    virtual ~Employee();

    void   setEmployeeID(int id);
    int    getEmployeeID() const;
    void   setEmployeeRole(string r);
    string getEmployeeRole() const;
    void   setSalary(double s);
    double getSalary() const;

    // Pre-increment: advance employeeID by 1 (e.g., bulk ID assignment)
    Employee& operator++();
    Employee  operator++(int);
    // Pre-decrement: reduce employeeID by 1
    Employee& operator--();
    Employee  operator--(int);

    virtual void display() const override;
};

// INHERITANCE: Manager derives from Employee
class Manager : public Employee {
private:
    double bonus;
    int    teamSize;
public:
    Manager();
    Manager(string n, int a, int ID, string r, double s, double b, int sz);
    Manager(const Manager& other);
    Manager& operator=(const Manager& other);
    ~Manager();

    void   setBonus(double b);
    double getBonus() const;
    void   setTeamSize(int sz);
    int    getTeamSize() const;

    void display() const override;
};
