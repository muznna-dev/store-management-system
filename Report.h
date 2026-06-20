#pragma once

#include "pch.h"
#include "Store.h"

class Report {
private:
    Store** stores;
    int count;

public:
    Report(Store** s = nullptr, int c = 0);
    Report(const Report& other);
    Report& operator=(const Report& other);
    ~Report();

    void sortByComposite();
    void sortByProfitThenGrowth();

    friend ostream& operator<<(ostream& out, Report& r);
};
