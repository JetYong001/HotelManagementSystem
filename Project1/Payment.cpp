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
    cout << "          PAYMENT RECEIPT           \n";
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
    else if (customerType == "Regular") {
        return bookings[bookingIndex].nights * (roomPrice * (1.0 - regularDiscount));
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
        cout << "+------------------------------------+\n";
        cout << "| Booking ID not found for payment!  |\n";
        cout << "+------------------------------------+\n";
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
        cout << "----------------------------------\n";
        cout << "1. Cash\n";
        cout << "2. Credit Card\n";
        cout << "3. Debit Card\n";
        cout << "4. Online Banking\n";
        cout << "5. E-Wallet\n";
        cout << "6. Cancel Payment\n\n";
        cout << "Enter choice: ";

        method = getMenuChoice(1, 6);

        if (method == -1) {
            system("cls");
            cout << "+--------------------------------+\n";
            cout << "| Invalid choice!                |\n";
            cout << "+--------------------------------+\n";
            system("pause");
            continue;
        }

        if (method == 6) {
            system("cls");
            cout << "+--------------------------------+\n";
            cout << "| Payment cancelled.             |\n";
            cout << "+--------------------------------+\n\n";
            system("pause");
            return false;
        }

        if (method < 1 || method > 5) {
            system("cls");
            cout << "+--------------------------------+\n";
            cout << "| Invalid choice!                |\n";
            cout << "+--------------------------------+\n";
            system("pause");
            continue;
        }

        double change = 0.0;
        double cashPaid = 0.0;

        if (method == 1) {
            while (true) {
                system("cls");
                cout << "==================================\n";
                cout << "           CASH PAYMENT           \n";
                cout << "==================================\n\n";
                cout << "Total Amount Due: RM " << fixed << setprecision(2) << totalAmount << "\n\n";

                cout << "Paid Amount     : RM ";
                if (!(cin >> cashPaid)) {
                    cin.clear();
                    clearInputBuffer();
                    system("cls");
                    cout << "+----------------------------------------------+\n";
                    cout << "| Invalid amount. Please enter a valid number. |\n";
                    cout << "+----------------------------------------------+\n\n";
                    system("pause");
                    continue;
                }
                clearInputBuffer();

                if (cashPaid < totalAmount) {
                    system("cls");
                    cout << "+------------------------------------------------+\n";
                    cout << "| Insufficient cash. You need at least RM " << left << setw(7) << totalAmount << " |\n";
                    cout << "+------------------------------------------------+\n\n";
                    system("pause");
                }
                else {
                    change = cashPaid - totalAmount;
                    break;
                }
            }
        }
        else {
            cashPaid = totalAmount;
            change = 0.0;
        }

        bool paymentConfirmed = false;

        while (true) {
            string headerTitle = (method == 1) ? "CASH PAYMENT" : methods[method - 1] + " PAYMENT";

            system("cls");
            cout << "==================================\n";
            cout << setw((34 - headerTitle.length()) / 2 + headerTitle.length()) << headerTitle << "\n";
            cout << "==================================\n\n";
            cout << fixed << setprecision(2);
            cout << "Total Amount Due: RM " << totalAmount << "\n\n";
            cout << "Paid Amount     : RM " << cashPaid << "\n\n";
            if (method == 1) {
                cout << "Change          : RM " << change << "\n\n";
            }
            cout << "Confirm payment of RM " << totalAmount << " (y/n): ";

            string confirm;
            getline(cin >> ws, confirm);

            if (confirm == "Y" || confirm == "y") {
                paymentConfirmed = true;
                break;
            }
            else if (confirm == "N" || confirm == "n") {
                system("cls");
                cout << "+--------------------------+\n";
                cout << "| Returning to payment     |\n";
                cout << "| method selection.        |\n";
                cout << "+--------------------------+\n\n";
                system("pause");
                break;
            }
            else {
                system("cls");
                cout << "+--------------------------------+\n";
                cout << "| Invalid choice! Enter y or n.  |\n";
                cout << "+--------------------------------+\n\n";
                system("pause");
            }
        }

        if (paymentConfirmed) {
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
}
