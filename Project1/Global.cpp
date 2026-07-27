#include "Global.h"


Customer customers[MAX_CUSTOMER];
Room rooms[MAX_ROOM];
Booking bookings[MAX_BOOKINGS];


int customerCount = 0;
int bookingCount = 0;

int customerIDCounter = 1;

double singlePrice = 120;
double doublePrice = 180;
double deluxePrice = 250;

double regularDiscount = 0.0;
double premiumDiscount = 0.1;
double vipDiscount = 0.2;