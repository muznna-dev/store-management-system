#include "pch.h"
#include "Helpers.h"

int showMenu() {
    int choice;
    do {
        cout << "1. Load Existing Data\n2. Generate New Dataset\nEnter choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            choice = 0;
        }
    } while (choice != 1 && choice != 2);

    return choice;
}

string randomStoreName(int i) {
    return "UrbanEase Store " + to_string(i + 1);
}

string randomPersonName() {
    string names[] = {"Muznna", "Palwasha", "Rayyan", "Manal", "Aishmal", "Ahmad", "Abdullah"};
    return names[rand() % 7];
}

double randomDouble(double min, double max) {
    return min + (double)rand() / RAND_MAX * (max - min);
}

int randomInt(int min, int max) {
    return min + rand() % (max - min + 1);
}

Store generateOneStore(int index) {
    Coordinates loc(
        randomDouble(24.0, 37.0),
        randomDouble(67.0, 75.0)
    );

    Analytics a(24);
    for (int i = 0; i < 24; i++) {
        double sales = randomDouble(50000, 200000);
        double cost = randomDouble(20000, 100000);
        int customers = randomInt(500, 3000);
        a.setMonthData(i, sales, cost, customers);
    }

    Manager mgr(
        randomPersonName(),
        randomInt(30, 50),
        1000 + index,
        "Manager",
        randomDouble(80000, 150000),
        randomDouble(10000, 30000),
        randomInt(5, 20)
    );

    int staffCount = randomInt(3, 8);
    Employee* staff = new Employee[staffCount];

    for (int i = 0; i < staffCount; i++) {
        staff[i] = Employee(
            randomPersonName(),
            randomInt(20, 40),
            2000 + index * 10 + i,
            "Staff",
            randomDouble(30000, 60000)
        );
    }

    Store s;
    s.setStoreName(randomStoreName(index));
    s.setUniqueID(500 + index);
    s.setLocation(loc);
    s.setAnalytics(a);
    s.setManager(mgr);
    s.setStaff(staff, staffCount);

    delete[] staff;
    return s;
}

Store* generateStores(int count) {
    Store* stores = new Store[count];
    for (int i = 0; i < count; i++) {
        stores[i] = generateOneStore(i);
    }
    return stores;
}

void saveAllStores(const string& filename, Store* stores, int count) {
    ofstream out(filename.c_str());
    if (!out) {
        cout << "Error opening file for writing.\n";
        return;
    }

    out << count << endl;
    for (int i = 0; i < count; i++) {
        stores[i].saveToFile(out);
    }

    out.close();
}

Store* loadAllStores(const string& filename, int& count) {
    ifstream in(filename.c_str());
    if (!in) {
        count = 0;
        return nullptr;
    }

    in >> count;
    Store* stores = new Store[count];

    for (int i = 0; i < count; i++) {
        stores[i].loadFromFile(in);
    }

    in.close();
    return stores;
}

void showRankingReport(Store* stores, int count) {
    Store** ptrs = new Store*[count];

    for (int i = 0; i < count; i++) {
        ptrs[i] = &stores[i];
    }

    Report report(ptrs, count);
    cout << report;

    delete[] ptrs;
}

void showProfitThenGrowthReport(Store* stores, int count) {
    Store** ptrs = new Store*[count];

    for (int i = 0; i < count; i++) {
        ptrs[i] = &stores[i];
    }

    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            bool shouldSwap = false;

            if (ptrs[j]->getStoreProfit() < ptrs[j + 1]->getStoreProfit()) {
                shouldSwap = true;
            }
            else if (ptrs[j]->getStoreProfit() == ptrs[j + 1]->getStoreProfit() &&
                     ptrs[j]->getStoreGrowth() < ptrs[j + 1]->getStoreGrowth()) {
                shouldSwap = true;
            }

            if (shouldSwap) {
                Store* temp = ptrs[j];
                ptrs[j] = ptrs[j + 1];
                ptrs[j + 1] = temp;
            }
        }
    }

    cout << "\n===== PROFIT THEN GROWTH REPORT (TOP 10) =====\n";
    int limit = (count < 10) ? count : 10;
    for (int i = 0; i < limit; i++) {
        cout << i + 1 << ". "
             << ptrs[i]->getStoreName()
             << " | Profit: " << ptrs[i]->getStoreProfit()
             << " | Growth: " << ptrs[i]->getStoreGrowth() << "%\n";
    }
    cout << "=============================================\n";

    delete[] ptrs;
}
