#include "pch.h"
#include "Analytics.h"

Analytics::Analytics(int m) {
    months = m;
    monthlySales   = new double[months];
    operatingCosts = new double[months];
    customerCounts = new int[months];

    for (int i = 0; i < months; i++) {
        monthlySales[i]   = 0;
        operatingCosts[i] = 0;
        customerCounts[i] = 0;
    }
}

Analytics::Analytics(const Analytics& other) {
    months = other.months;
    monthlySales   = new double[months];
    operatingCosts = new double[months];
    customerCounts = new int[months];

    for (int i = 0; i < months; i++) {
        monthlySales[i]   = other.monthlySales[i];
        operatingCosts[i] = other.operatingCosts[i];
        customerCounts[i] = other.customerCounts[i];
    }
}

Analytics& Analytics::operator=(const Analytics& other) {
    if (this != &other) {
        delete[] monthlySales;
        delete[] operatingCosts;
        delete[] customerCounts;

        months = other.months;
        monthlySales   = new double[months];
        operatingCosts = new double[months];
        customerCounts = new int[months];

        for (int i = 0; i < months; i++) {
            monthlySales[i]   = other.monthlySales[i];
            operatingCosts[i] = other.operatingCosts[i];
            customerCounts[i] = other.customerCounts[i];
        }
    }
    return *this;
}

Analytics::~Analytics() {
    delete[] monthlySales;
    delete[] operatingCosts;
    delete[] customerCounts;
}

int Analytics::getMonths() const { return months; }

void Analytics::setMonthData(int index, double sales, double cost, int customers) {
    if (index >= 0 && index < months) {
        monthlySales[index]   = sales;
        operatingCosts[index] = cost;
        customerCounts[index] = customers;
    }
}

double Analytics::getSales(int index) const {
    if (index >= 0 && index < months) return monthlySales[index];
    return 0;
}

double Analytics::getCost(int index) const {
    if (index >= 0 && index < months) return operatingCosts[index];
    return 0;
}

int Analytics::getCustomers(int index) const {
    if (index >= 0 && index < months) return customerCounts[index];
    return 0;
}

double& Analytics::operator[](int index) {
    if (index < 0 || index >= months) {
        cout << "Invalid monthly sales index.\n";
        exit(1);
    }
    return monthlySales[index];
}

double Analytics::operator[](int index) const {
    if (index < 0 || index >= months) {
        cout << "Invalid monthly sales index.\n";
        exit(1);
    }
    return monthlySales[index];
}

double Analytics::getTotalSales() const {
    double total = 0;
    for (int i = 0; i < months; i++) total += monthlySales[i];
    return total;
}

double Analytics::getTotalCosts() const {
    double total = 0;
    for (int i = 0; i < months; i++) total += operatingCosts[i];
    return total;
}

int Analytics::getTotalCustomers() const {
    int total = 0;
    for (int i = 0; i < months; i++) total += customerCounts[i];
    return total;
}

double Analytics::getAnnualSales() const {
    double total = 0;
    int start = (months > 12) ? months - 12 : 0;
    for (int i = start; i < months; i++) total += monthlySales[i];
    return total;
}

double Analytics::getAnnualCosts() const {
    double total = 0;
    int start = (months > 12) ? months - 12 : 0;
    for (int i = start; i < months; i++) total += operatingCosts[i];
    return total;
}

double Analytics::getProfit() const {
    return getAnnualSales() - getAnnualCosts();
}

double Analytics::getAverageGrowth() const {
    int start = (months > 12) ? months - 12 : 1;
    if (start < 1) start = 1;

    double totalGrowth = 0;
    int count = 0;

    for (int i = start; i < months; i++) {
        if (monthlySales[i - 1] != 0) {
            double growth = ((monthlySales[i] - monthlySales[i - 1]) / monthlySales[i - 1]) * 100.0;
            totalGrowth += growth;
            ++count;   // pre-increment as required by assignment
        }
    }

    return (count == 0) ? 0 : totalGrowth / count;
}

double Analytics::getCompositeScore() const {
    double sales  = getAnnualSales();
    double profit = getProfit();
    double growth = getAverageGrowth();
    // Weights: profit 50%, sales 30%, growth 20%
    return (0.3 * sales) + (0.5 * profit) + (0.2 * growth * 1000);
}

bool Analytics::operator<(const Analytics& other) const {
    return getCompositeScore() < other.getCompositeScore();
}

bool Analytics::operator>(const Analytics& other) const {
    return getCompositeScore() > other.getCompositeScore();
}

Analytics Analytics::operator+(const Analytics& other) const {
    int limit = (months < other.months) ? months : other.months;

    Analytics temp(limit);
    for (int i = 0; i < limit; i++) {
        temp.monthlySales[i]   = monthlySales[i]   + other.monthlySales[i];
        temp.operatingCosts[i] = operatingCosts[i] + other.operatingCosts[i];
        temp.customerCounts[i] = customerCounts[i] + other.customerCounts[i];
    }
    return temp;
}

// Pre-increment: expand tracking window by one blank month
Analytics& Analytics::operator++() {
    double* newSales  = new double[months + 1];
    double* newCosts  = new double[months + 1];
    int*    newCust   = new int[months + 1];

    for (int i = 0; i < months; i++) {
        newSales[i] = monthlySales[i];
        newCosts[i] = operatingCosts[i];
        newCust[i]  = customerCounts[i];
    }
    newSales[months] = 0;
    newCosts[months] = 0;
    newCust[months]  = 0;

    delete[] monthlySales;
    delete[] operatingCosts;
    delete[] customerCounts;

    monthlySales   = newSales;
    operatingCosts = newCosts;
    customerCounts = newCust;
    ++months;

    return *this;
}

// Post-increment: returns copy before expanding window
Analytics Analytics::operator++(int) {
    Analytics temp(*this);
    ++(*this);
    return temp;
}

// Pre-decrement: shrink tracking window by one month (remove oldest)
Analytics& Analytics::operator--() {
    if (months <= 1) return *this;

    double* newSales = new double[months - 1];
    double* newCosts = new double[months - 1];
    int*    newCust  = new int[months - 1];

    for (int i = 0; i < months - 1; i++) {
        newSales[i] = monthlySales[i];
        newCosts[i] = operatingCosts[i];
        newCust[i]  = customerCounts[i];
    }

    delete[] monthlySales;
    delete[] operatingCosts;
    delete[] customerCounts;

    monthlySales   = newSales;
    operatingCosts = newCosts;
    customerCounts = newCust;
    --months;

    return *this;
}

// Post-decrement: returns copy before shrinking window
Analytics Analytics::operator--(int) {
    Analytics temp(*this);
    --(*this);
    return temp;
}

ostream& operator<<(ostream& out, const Analytics& a) {
    out << a.months << endl;
    for (int i = 0; i < a.months; i++) out << a.monthlySales[i]   << " ";
    out << endl;
    for (int i = 0; i < a.months; i++) out << a.operatingCosts[i] << " ";
    out << endl;
    for (int i = 0; i < a.months; i++) out << a.customerCounts[i] << " ";
    out << endl;
    return out;
}

istream& operator>>(istream& in, Analytics& a) {
    int m;
    in >> m;

    delete[] a.monthlySales;
    delete[] a.operatingCosts;
    delete[] a.customerCounts;

    a.months       = m;
    a.monthlySales   = new double[a.months];
    a.operatingCosts = new double[a.months];
    a.customerCounts = new int[a.months];

    for (int i = 0; i < a.months; i++) in >> a.monthlySales[i];
    for (int i = 0; i < a.months; i++) in >> a.operatingCosts[i];
    for (int i = 0; i < a.months; i++) in >> a.customerCounts[i];

    return in;
}
