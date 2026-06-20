#pragma once

#include "pch.h"

// Analytics class — COMPOSITION: owned by Store
// Tracks monthly sales, costs, and customer counts
// Supports operator overloading for comparisons, arithmetic, and stream I/O
class Analytics {
private:
    double* monthlySales;    // dynamically allocated array
    double* operatingCosts;  // dynamically allocated array
    int*    customerCounts;  // dynamically allocated array
    int     months;

public:
    Analytics(int m = 24);
    Analytics(const Analytics& other);      // deep copy constructor
    Analytics& operator=(const Analytics& other);
    ~Analytics();

    int  getMonths() const;
    void setMonthData(int index, double sales, double cost, int customers);
    double getSales(int index) const;
    double getCost(int index) const;
    int    getCustomers(int index) const;

    // Subscript operator — access monthly sales by index
    double& operator[](int index);
    double  operator[](int index) const;

    double getTotalSales() const;
    double getTotalCosts() const;
    int    getTotalCustomers() const;

    double getAnnualSales() const;
    double getAnnualCosts() const;
    double getProfit() const;
    double getAverageGrowth() const;
    double getCompositeScore() const;

    // Comparison operators — compare by composite score
    bool operator<(const Analytics& other) const;
    bool operator>(const Analytics& other) const;

    // Arithmetic — combine two analytics objects (e.g., cluster totals)
    Analytics operator+(const Analytics& other) const;

    // Pre-increment: expand tracking window by one month (adds blank month)
    Analytics& operator++();
    // Post-increment: returns copy before expanding window
    Analytics  operator++(int);

    // Pre-decrement: shrink tracking window by one month
    Analytics& operator--();
    // Post-decrement: returns copy before shrinking window
    Analytics  operator--(int);

    friend ostream& operator<<(ostream& out, const Analytics& a);
    friend istream& operator>>(istream& in, Analytics& a);
};
