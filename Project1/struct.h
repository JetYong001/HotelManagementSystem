#ifndef STRUCT_H
#define STRUCT_H

#include <string>

using namespace std;


struct Customer
{
    string customerID;
    string name;
    string phone;
    string ic;
    string memberType;
    double totalSpent;
};


struct Room
{
    string roomID;
    string roomType;
    double price;
    bool available;
};


struct Booking {
    string bookingID;
    string customerName;
    string phone;
    string roomNumber;
    string roomType;
    string checkInDate;
    string checkOutDate;
    bool checkedIn;
    bool checkedOut;
    bool cancelled;
};


#endif