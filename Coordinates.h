#pragma once
#include "pch.h"

// COMPOSITION: owned by Store — cannot exist independently
class Coordinates {
private:
    double latitude;
    double longitude;
public:
    Coordinates();
    Coordinates(double lat, double lon);
    Coordinates(const Coordinates& other);
    Coordinates& operator=(const Coordinates& other);

    void   setLat(double lat);
    double getLat() const;
    void   setLong(double lon);
    double getLong() const;

    void display() const;

    friend ostream& operator<<(ostream& out, const Coordinates& c);
    friend istream& operator>>(istream& in, Coordinates& c);
};
