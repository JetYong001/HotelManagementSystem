#include "Global.h"
#include <iostream>


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

vector<Payment> payments;
vector<Report> reports;

void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

string toUpperString(string str) {
    for (char& c : str) {
        c = static_cast<char>(toupper(static_cast<unsigned char>(c)));
    }
    return str;
}

string toLowerString(string str) {
    for (int i = 0; i < str.length(); i++) {
        str[i] = tolower(str[i]);
    }
    return str;
}

int getMenuChoice(int minVal, int maxVal) {
    string input;
    getline(cin >> ws, input);

    for (char c : input) {
        if (!isdigit(c)) return -1;
    }

    if (input.empty()) return -1;

    try {
        int val = stoi(input);
        if (val < minVal || val > maxVal) return -1;
        return val;
    }
    catch (...) {
        return -1;
    }
}