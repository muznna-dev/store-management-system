#pragma once

#include "pch.h"
#include "Coordinates.h"
#include "Analytics.h"
#include "Person.h"

class Store {
private:
    string storeName;
    int uniqueID;
    Coordinates location;
    Analytics analytics;
    Manager manager;
    Employee* staff;
    int staffCount;

public:
    Store();
    Store(string n, int id, const Coordinates& loc, const Analytics& a,
          const Manager& m, Employee* s, int count);
    Store(const Store& other);
    Store& operator=(const Store& other);
    ~Store();

    void setStoreName(string n);
    void setUniqueID(int id);
    void setLocation(const Coordinates& loc);
    void setAnalytics(const Analytics& a);
    void setManager(const Manager& m);
    void setStaff(Employee* s, int count);

    string getStoreName() const;
    int getUniqueID() const;
    Coordinates getLocation() const;
    const Analytics& getAnalytics() const;
    Manager getManager() const;
    int getStaffCount() const;
    Employee getStaffMember(int index) const;

    double getStoreScore() const;
    double getStoreProfit() const;
    double getStoreGrowth() const;
    double getStoreAnnualSales() const;

    void printSummary(ostream& out = cout) const;
    void saveToFile(ofstream& out) const;
    void loadFromFile(ifstream& in);

    bool operator==(const Store& other) const;

    friend ostream& operator<<(ostream& out, const Store& s);
    friend istream& operator>>(istream& in, Store& s);
};
