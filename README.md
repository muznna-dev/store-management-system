# Store Management System (UrbanEase)

A C++ console-based store analytics and management system built as part of an OOP course assignment at FAST University.

## About

UrbanEase is a fictional fast-growing fashion retail brand expanding across Pakistan. This system helps manage and analyse hundreds of store outlets by tracking sales history, staff, performance rankings, and persistent data storage.

## Features

* Load existing store data from file or generate a new dataset
* Data representation for 500+ stores with sales history, staff, and manager details
* Composite performance scoring and store ranking system
* Top 10 and bottom 5 store reports
* Persistent storage — data saves and loads across program runs

## OOP Concepts Applied

* Encapsulation (all data members private)
* Inheritance (Person → Employee → Manager hierarchy)
* Polymorphism (virtual functions)
* Composition (Store owns geographic coordinates and analytics data)
* Aggregation (Report references stores without owning them)
* Operator Overloading (+, >, <, ==, <<, [])
* Dynamic memory management with new and delete
* Deep copy constructors

## Technologies Used

* C++
* File Handling (text-based persistent storage)

## How to Run
1. Clone the repository
2. Open the project in Visual Studio
3. Build the solution (Ctrl + Shift + B)
4. Run the executable (Ctrl + F5)

## Project Structure

* Store management and analytics system
* Persistent file-based storage
* Ranking and reporting modules
* Employee and manager hierarchy

## Author

Developed by Muznna Majid.
