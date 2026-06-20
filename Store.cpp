#include "pch.h"
#include "Store.h"

Store::Store() : analytics(24) {
    storeName = "";
    uniqueID = 0;
    staff = nullptr;
    staffCount = 0;
}

Store::Store(string n, int id, const Coordinates& loc, const Analytics& a,
             const Manager& m, Employee* s, int count)
    : analytics(a) {
    storeName = n;
    uniqueID = id;
    location = loc;
    manager = m;
    staffCount = count;

    if (staffCount > 0) {
        staff = new Employee[staffCount];
        for (int i = 0; i < staffCount; i++) {
            staff[i] = s[i];
        }
    } else {
        staff = nullptr;
    }
}

Store::Store(const Store& other)
    : analytics(other.analytics) {
    storeName = other.storeName;
    uniqueID = other.uniqueID;
    location = other.location;
    manager = other.manager;
    staffCount = other.staffCount;

    if (staffCount > 0) {
        staff = new Employee[staffCount];
        for (int i = 0; i < staffCount; i++) {
            staff[i] = other.staff[i];
        }
    } else {
        staff = nullptr;
    }
}

Store& Store::operator=(const Store& other) {
    if (this != &other) {
        delete[] staff;

        storeName = other.storeName;
        uniqueID = other.uniqueID;
        location = other.location;
        analytics = other.analytics;
        manager = other.manager;
        staffCount = other.staffCount;

        if (staffCount > 0) {
            staff = new Employee[staffCount];
            for (int i = 0; i < staffCount; i++) {
                staff[i] = other.staff[i];
            }
        } else {
            staff = nullptr;
        }
    }
    return *this;
}

Store::~Store() {
    delete[] staff;
}

void Store::setStoreName(string n) {
    storeName = n;
}

void Store::setUniqueID(int id) {
    uniqueID = id;
}

void Store::setLocation(const Coordinates& loc) {
    location = loc;
}

void Store::setAnalytics(const Analytics& a) {
    analytics = a;
}

void Store::setManager(const Manager& m) {
    manager = m;
}

void Store::setStaff(Employee* s, int count) {
    delete[] staff;
    staffCount = count;

    if (staffCount > 0) {
        staff = new Employee[staffCount];
        for (int i = 0; i < staffCount; i++) {
            staff[i] = s[i];
        }
    } else {
        staff = nullptr;
    }
}

string Store::getStoreName() const {
    return storeName;
}

int Store::getUniqueID() const {
    return uniqueID;
}

Coordinates Store::getLocation() const {
    return location;
}

const Analytics& Store::getAnalytics() const {
    return analytics;
}

Manager Store::getManager() const {
    return manager;
}

int Store::getStaffCount() const {
    return staffCount;
}

Employee Store::getStaffMember(int index) const {
    if (index >= 0 && index < staffCount) {
        return staff[index];
    }
    return Employee();
}

double Store::getStoreScore() const {
    return analytics.getCompositeScore();
}

double Store::getStoreProfit() const {
    return analytics.getProfit();
}

double Store::getStoreGrowth() const {
    return analytics.getAverageGrowth();
}

double Store::getStoreAnnualSales() const {
    return analytics.getAnnualSales();
}

void Store::printSummary(ostream& out) const {
    out << "Store ID: " << uniqueID << endl;
    out << "Store Name: " << storeName << endl;
    out << "Location: " << location << endl;
    out << "Total Sales: " << analytics.getTotalSales() << endl;
    out << "Total Costs: " << analytics.getTotalCosts() << endl;
    out << "Total Customers: " << analytics.getTotalCustomers() << endl;

    out << "Manager: ";
    manager.display();
    out << endl;

    out << "Staff Count: " << staffCount << endl;
    for (int i = 0; i < staffCount; i++) {
        out << "Staff " << i + 1 << ": ";
        staff[i].display();
        out << endl;
    }
}

void Store::saveToFile(ofstream& out) const {
    out << *this;
}

void Store::loadFromFile(ifstream& in) {
    in >> *this;
}

bool Store::operator==(const Store& other) const {
    return uniqueID == other.uniqueID;
}

ostream& operator<<(ostream& out, const Store& s) {
    out << s.uniqueID << endl;
    out << s.storeName << endl;
    out << s.location << endl;
    out << s.analytics;

    out << s.manager.getName() << endl;
    out << s.manager.getAge() << endl;
    out << s.manager.getEmployeeID() << endl;
    out << s.manager.getEmployeeRole() << endl;
    out << s.manager.getSalary() << endl;
    out << s.manager.getBonus() << endl;
    out << s.manager.getTeamSize() << endl;

    out << s.staffCount << endl;
    for (int i = 0; i < s.staffCount; i++) {
        out << s.staff[i].getName() << endl;
        out << s.staff[i].getAge() << endl;
        out << s.staff[i].getEmployeeID() << endl;
        out << s.staff[i].getEmployeeRole() << endl;
        out << s.staff[i].getSalary() << endl;
    }

    return out;
}

istream& operator>>(istream& in, Store& s) {
    in >> s.uniqueID;
    in.ignore();

    getline(in, s.storeName);
    in >> s.location;
    in >> s.analytics;

    string mName, mRole;
    int mAge, mID, mTeam;
    double mSalary, mBonus;

    in.ignore();
    getline(in, mName);
    in >> mAge >> mID;
    in.ignore();
    getline(in, mRole);
    in >> mSalary >> mBonus >> mTeam;

    s.manager = Manager(mName, mAge, mID, mRole, mSalary, mBonus, mTeam);

    delete[] s.staff;
    in >> s.staffCount;

    if (s.staffCount > 0) {
        s.staff = new Employee[s.staffCount];
        for (int i = 0; i < s.staffCount; i++) {
            string eName, eRole;
            int eAge, eID;
            double eSalary;

            in.ignore();
            getline(in, eName);
            in >> eAge >> eID;
            in.ignore();
            getline(in, eRole);
            in >> eSalary;

            s.staff[i] = Employee(eName, eAge, eID, eRole, eSalary);
        }
    } else {
        s.staff = nullptr;
    }

    return in;
}
