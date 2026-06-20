#include "pch.h"
#include "Helpers.h"

int main() {
    srand((unsigned)time(0));

    const string filename = "stores.txt";
    int     count  = 0;
    Store*  stores = nullptr;

    // --- Task 0: Startup menu ---
    int choice = showMenu();

    if (choice == 1) {
        stores = loadAllStores(filename, count);

        if (stores == nullptr) {
            cout << "File not found. Switching to dataset generation.\n";
            do {
                cout << "Enter number of stores to generate (minimum 100, recommended 500+): ";
                cin >> count;
            } while (count < 100);

            stores = generateStores(count);
            saveAllStores(filename, stores, count);
            cout << count << " stores generated and saved to " << filename << "\n";
        } else {
            cout << count << " stores loaded from " << filename << "\n";
        }
    } else {
        do {
            cout << "Enter number of stores to generate (minimum 100, recommended 500+): ";
            cin >> count;
        } while (count < 100);

        stores = generateStores(count);
        saveAllStores(filename, stores, count);
        cout << count << " stores generated and saved to " << filename << "\n";
    }

    if (count < 500) {
        cout << "Note: assignment demo recommends at least 500 stores.\n";
    }

    // --- Task 1: Show first 3 store summaries ---
    cout << "\n===== STORE SUMMARIES (first 3) =====\n";
    for (int i = 0; i < count && i < 3; i++) {
        stores[i].printSummary();
        cout << "\n";
    }

    // --- Task 3: Ranking report (top 10 + bottom 5 by composite score) ---
    showRankingReport(stores, count);

    // --- Task 3: Profit-then-growth secondary sort report ---
    showProfitThenGrowthReport(stores, count);

    // --- OOP Demo: Polymorphism (Inheritance) ---
    cout << "\n===== POLYMORPHISM DEMO =====\n";
    Person* p1 = new Employee("Ali",  28, 9001, "Sales Associate", 45000);
    Person* p2 = new Manager ("Sara", 35, 9002, "Store Manager",   95000, 20000, 10);

    p1->display(); cout << "\n\n";
    p2->display(); cout << "\n\n";

    delete p1;
    delete p2;

    // --- OOP Demo: Pre/Post Increment on Employee ---
    cout << "===== INCREMENT/DECREMENT DEMO =====\n";
    Employee emp("Zain", 25, 3000, "Cashier", 35000);
    cout << "Original Employee ID: " << emp.getEmployeeID() << "\n";

    Employee empCopy = emp++;   // post-increment: empCopy gets original ID
    cout << "After post-increment — original now: " << emp.getEmployeeID()
         << ", copy has: " << empCopy.getEmployeeID() << "\n";

    ++emp;   // pre-increment
    cout << "After pre-increment — Employee ID: " << emp.getEmployeeID() << "\n";

    emp--;   // post-decrement
    cout << "After post-decrement — Employee ID: " << emp.getEmployeeID() << "\n";

    --emp;   // pre-decrement
    cout << "After pre-decrement — Employee ID: " << emp.getEmployeeID() << "\n";

    // --- OOP Demo: Pre/Post Increment on Analytics ---
    cout << "\n===== ANALYTICS INCREMENT DEMO =====\n";
    Analytics a(3);
    a.setMonthData(0, 100000, 40000, 500);
    a.setMonthData(1, 120000, 45000, 600);
    a.setMonthData(2, 130000, 50000, 650);

    cout << "Months before increment: " << a.getMonths() << "\n";
    Analytics aCopy = a++;   // post-increment: adds a blank month, aCopy keeps original
    cout << "After post-increment — months now: " << a.getMonths()
         << ", copy has: " << aCopy.getMonths() << "\n";

    ++a;   // pre-increment
    cout << "After pre-increment — months: " << a.getMonths() << "\n";

    a--;   // post-decrement
    cout << "After post-decrement — months: " << a.getMonths() << "\n";

    --a;   // pre-decrement
    cout << "After pre-decrement — months: " << a.getMonths() << "\n";

    // --- OOP Demo: Analytics operator+ ---
    cout << "\n===== ANALYTICS operator+ DEMO =====\n";
    const Analytics& storeA = stores[0].getAnalytics();
    const Analytics& storeB = stores[1].getAnalytics();
    Analytics combined = storeA + storeB;
    cout << "Store 0 annual sales: " << storeA.getAnnualSales() << "\n";
    cout << "Store 1 annual sales: " << storeB.getAnnualSales() << "\n";
    cout << "Combined annual sales: " << combined.getAnnualSales() << "\n";

    delete[] stores;
    return 0;
}
