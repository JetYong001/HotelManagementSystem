#ifndef STRUCT_H
#define STRUCT_H

#include <string>

using namespace std;

struct Customer {
    string customerID;
    string name;
    string phone;
    string ic;
    string memberType;
    double totalSpent = 0.0;
};

struct Room {
    string roomID;
    string roomType;
    double price = 0.0;
    bool available = true;
};

struct Booking {
    string bookingID;
    string customerID;
    string customerName;
    string phone;
    string roomNumber;
    string roomType;
    string checkInDate;
    string checkOutDate;
    string status = "";
    int nights = 0;
    bool checkedIn = false;
    bool checkedOut = false;
    bool cancelled = false;
    bool isPaid = false;
};

struct Payment {
    string paymentId;
    string bookingId;
    string customerName;
    string totalPoint;
    double totalAmount = 0.0;
    string paymentMethod;
    bool paymentStatus = false;
    double cashPaid = 0.0;
    double change = 0.0;
};

struct Report {
    int totalBookings;
    double totalRevenue;
    int totalCustomers;
    int completedPayments;
};

#endif