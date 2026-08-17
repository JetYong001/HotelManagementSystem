#ifndef GLOBAL_H
#define GLOBAL_H

#include "Struct.h"
#include "vector"

#define MAX_CUSTOMER 100
#define MAX_ROOM 100
#define MAX_BOOKINGS 100

extern Customer customers[MAX_CUSTOMER];
extern Room rooms[MAX_ROOM];
extern Booking bookings[100];
extern vector<Payment> payments;


extern int customerCount;
extern int bookingCount;

extern int customerIDCounter;

extern double singlePrice;
extern double doublePrice;
extern double deluxePrice;

extern double regularDiscount;
extern double premiumDiscount;
extern double vipDiscount;

extern void clearInputBuffer();
extern string toUpperString(string str);

#endif