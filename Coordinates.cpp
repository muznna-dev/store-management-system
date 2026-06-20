#include "pch.h"
#include "Coordinates.h"

Coordinates::Coordinates() : latitude(0.0), longitude(0.0) {}
Coordinates::Coordinates(double lat, double lon) : latitude(lat), longitude(lon) {}
Coordinates::Coordinates(const Coordinates& other) : latitude(other.latitude), longitude(other.longitude) {}

Coordinates& Coordinates::operator=(const Coordinates& other) {
    if (this != &other) { latitude = other.latitude; longitude = other.longitude; }
    return *this;
}

void   Coordinates::setLat(double lat)  { latitude = lat; }
double Coordinates::getLat()  const     { return latitude; }
void   Coordinates::setLong(double lon) { longitude = lon; }
double Coordinates::getLong() const     { return longitude; }

void Coordinates::display() const {
    cout << "Coordinates:\nLongitude: " << longitude << "    Latitude: " << latitude << endl;
}

ostream& operator<<(ostream& out, const Coordinates& c) {
    out << c.latitude << " " << c.longitude;
    return out;
}

istream& operator>>(istream& in, Coordinates& c) {
    in >> c.latitude >> c.longitude;
    return in;
}
