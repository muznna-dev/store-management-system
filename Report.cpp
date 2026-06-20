#include "pch.h"
#include "Report.h"

// AGGREGATION: Report holds pointers to Store objects but does NOT own them.
// Destroying a Report does NOT destroy the referenced stores.

Report::Report(Store** s, int c) {
    count = c;

    if (count > 0) {
        stores = new Store*[count];
        for (int i = 0; i < count; i++) {
            stores[i] = s[i];
        }
    } else {
        stores = nullptr;
    }
}

Report::Report(const Report& other) {
    count = other.count;

    if (count > 0) {
        stores = new Store*[count];
        for (int i = 0; i < count; i++) {
            stores[i] = other.stores[i];   // copy pointer, not the store itself
        }
    } else {
        stores = nullptr;
    }
}

Report& Report::operator=(const Report& other) {
    if (this != &other) {
        delete[] stores;   // delete pointer array only — NOT the stores themselves
        count = other.count;

        if (count > 0) {
            stores = new Store*[count];
            for (int i = 0; i < count; i++) {
                stores[i] = other.stores[i];
            }
        } else {
            stores = nullptr;
        }
    }
    return *this;
}

Report::~Report() {
    // Aggregation: only delete the pointer array, NOT the store objects
    delete[] stores;
}

void Report::sortByComposite() {
    // Bubble sort — descending by composite score
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (stores[j]->getStoreScore() < stores[j + 1]->getStoreScore()) {
                Store* tmp = stores[j];
                stores[j]     = stores[j + 1];
                stores[j + 1] = tmp;
            }
        }
    }
}

void Report::sortByProfitThenGrowth() {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            bool shouldSwap = false;

            if (stores[j]->getStoreProfit() < stores[j + 1]->getStoreProfit()) {
                shouldSwap = true;
            } else if (stores[j]->getStoreProfit() == stores[j + 1]->getStoreProfit() &&
                       stores[j]->getStoreGrowth()  < stores[j + 1]->getStoreGrowth()) {
                shouldSwap = true;
            }

            if (shouldSwap) {
                Store* tmp    = stores[j];
                stores[j]     = stores[j + 1];
                stores[j + 1] = tmp;
            }
        }
    }
}

// operator<< prints ranking report — uses pre-increment (++rank) explicitly
ostream& operator<<(ostream& out, Report& r) {
    r.sortByComposite();

    out << "\n========== STORE PERFORMANCE REPORT ==========\n";

    // --- Top 10 ---
    out << "\nTop 10 Stores (by Composite Score):\n";
    int rank = 0;
    int topLimit = (r.count < 10) ? r.count : 10;

    for (int i = 0; i < topLimit; i++) {
        out << ++rank << ". "                              // pre-increment used here
            << r.stores[i]->getStoreName()
            << " | ID: "     << r.stores[i]->getUniqueID()
            << " | Score: "  << r.stores[i]->getStoreScore()
            << " | Profit: " << r.stores[i]->getStoreProfit()
            << " | Growth: " << r.stores[i]->getStoreGrowth()
            << "%\n";
    }

    // --- Bottom 5 ---
    out << "\nBottom 5 Stores (by Composite Score):\n";
    rank = 0;
    int bottomStart = (r.count > 5) ? r.count - 5 : 0;

    for (int i = bottomStart; i < r.count; i++) {
        out << ++rank << ". "                              // pre-increment used here
            << r.stores[i]->getStoreName()
            << " | ID: "     << r.stores[i]->getUniqueID()
            << " | Score: "  << r.stores[i]->getStoreScore()
            << " | Profit: " << r.stores[i]->getStoreProfit()
            << " | Growth: " << r.stores[i]->getStoreGrowth()
            << "%\n";
    }

    out << "==============================================\n";
    return out;
}
