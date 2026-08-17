#include <iostream>
#include <iomanip>
#include <ctime>
#include <limits>
#include <string>
#include <sstream>
#include "Global.h"

using namespace std;

const string methods[] = { "Cash", "Credit Card", "Debit Card", "Online Banking", "E-Wallet" };

void generateReceipt() {
    if (payments.empty()) {
        cout << "No payment record found.\n";
        return;
    }

    Payment lastPayment = payments.back();

    cout << "====================================\n";
    cout << "          PAYMENT RECEIPT\n";
    cout << "====================================\n";
    cout << "Payment ID     : " << lastPayment.paymentId << "\n";
    cout << "Booking ID     : " << lastPayment.bookingId << "\n";
    cout << "Payment Method : " << lastPayment.paymentMethod << "\n";
    cout << "Customer Name  : " << lastPayment.customerName << "\n";
    cout << "Point          : " << lastPayment.totalPoint << "\n";
    cout << fixed << setprecision(2);
    cout << "Total Amount   : RM " << lastPayment.totalAmount << "\n";

    if (lastPayment.paymentMethod == "Cash") {
        cout << "Cash Paid      : RM " << lastPayment.cashPaid << "\n";
        cout << "Change         : RM " << lastPayment.change << "\n";
    }

    cout << "====================================\n";
}

double calculateTotalAmount(int bookingIndex) {
    string customerType = "Normal";
    double roomPrice = 0.0;

    if (bookings[bookingIndex].roomType == "Single") {
        roomPrice = singlePrice;
    }
    else if (bookings[bookingIndex].roomType == "Double") {
        roomPrice = doublePrice;
    }
    else {
        roomPrice = deluxePrice;
    }

    for (int i = 0; i < customerCount; i++) {
        if (customers[i].customerID == bookings[bookingIndex].customerID) {
            customerType = customers[i].memberType;
            break;
        }
    }

    if (customerType == "Premium") {
        return bookings[bookingIndex].nights * (roomPrice * (1.0 - premiumDiscount));
    }
    else if (customerType == "VIP") {
        return bookings[bookingIndex].nights * (roomPrice * (1.0 - vipDiscount));
    }
    else {
        return bookings[bookingIndex].nights * roomPrice;
    }
}

bool processPayment(string bookingID) {
    int bookIndex = -1;

    for (int i = 0; i < bookingCount; i++) {
        if (bookings[i].bookingID == bookingID) {
            bookIndex = i;
            break;
        }
    }

    if (bookIndex == -1) {
        cout << "\nError: Booking ID not found for payment!\n";
        system("pause");
        return false;
    }

    double totalAmount = calculateTotalAmount(bookIndex);

    while (true) {
        system("cls");
        int method;
        cout << "==================================\n";
        cout << "Payment Info\n";
        cout << "==================================\n\n";
        cout << fixed << setprecision(2);
        cout << "Customer : " << bookings[bookIndex].customerName << "\n";
        cout << "Room     : " << bookings[bookIndex].roomType << "\n";
        cout << "Nights   : " << bookings[bookIndex].nights << "\n";
        cout << "Total    : RM " << totalAmount << "\n";
        cout << "==================================\n\n";

        cout << "Payment Method:\n";
        cout << "1. Cash\n";
        cout << "2. Credit Card\n";
        cout << "3. Debit Card\n";
        cout << "4. Online Banking\n";
        cout << "5. E-Wallet\n";
        cout << "Enter choice: ";

        if (!(cin >> method)) {
            clearInputBuffer();
            cout << "\nInvalid payment method.\n";
            system("pause");
            continue;
        }
        if (method < 1 || method > 5) {
            cout << "\nInvalid payment method.\n";
            system("pause");
            continue;
        }

        double change = 0.0;
        double cashPaid = 0.0;

        if (method == 1) {
            while (true) {
                cout << "\nEnter Cash Amount (RM): ";
                if (!(cin >> cashPaid)) {
                    clearInputBuffer();
                    cout << "Invalid amount. Please enter a valid number.\n";
                    continue;
                }

                if (cashPaid < totalAmount) {
                    cout << "Insufficient cash. You need at least RM " << totalAmount << "\n";
                }
                else {
                    change = cashPaid - totalAmount;
                    break;
                }
            }
        }

        char confirm;
        cout << "\nConfirm payment of RM " << totalAmount << " (Y/N): ";
        cin >> confirm;
        if (confirm != 'Y' && confirm != 'y') {
            cout << "\nPayment cancelled.\n";
            system("pause");
            return false;
        }

        double currentTotalSpent = 0.0;
        bool customerFound = false;

        for (int i = 0; i < customerCount; i++) {
            if (customers[i].customerID == bookings[bookIndex].customerID) {
                customers[i].totalSpent += totalAmount;
                currentTotalSpent = customers[i].totalSpent;
                customerFound = true;

                if (customers[i].totalSpent >= 5000) {
                    customers[i].memberType = "VIP";
                }
                else if (customers[i].totalSpent >= 500) {
                    customers[i].memberType = "Premium";
                }
                break;
            }
        }

        if (!customerFound) {
            currentTotalSpent = totalAmount;
        }

        int nextPaymentNum = static_cast<int>(payments.size()) + 1;
        string payID = "P";
        if (nextPaymentNum < 10) payID += "00";
        else if (nextPaymentNum < 100) payID += "0";
        payID += to_string(nextPaymentNum);

        Payment payment;
        payment.paymentId = payID;
        payment.bookingId = bookings[bookIndex].bookingID;
        payment.customerName = bookings[bookIndex].customerName;
        payment.totalPoint = to_string(static_cast<int>(currentTotalSpent));
        payment.totalAmount = totalAmount;
        payment.paymentMethod = methods[method - 1];
        payment.paymentStatus = true;
        payment.cashPaid = cashPaid;
        payment.change = change;

        payments.push_back(payment);
        bookings[bookIndex].isPaid = true;

        system("cls");
        generateReceipt();
        system("pause");
        return true;
    }
}