#include <iostream>
#include <iomanip>
#include <set>
#include <ctime>
#include <cctype>
#include <string>
#include "Global.h"

using namespace std;

const string monthNames[] = {
    "January", "February", "March", "April", "May", "June",
    "July", "August", "September", "October", "November", "December"
};

bool getBookingYearAndMonth(const Booking& booking, int& year, int& month) {
    const string& date = booking.checkInDate;
    if (date.length() != 10 || date[4] != '-' || date[7] != '-') 
        return false;

    for (size_t i = 0; i < date.length(); ++i) {
        if (i != 4 && i != 7 && !isdigit(static_cast<unsigned char>(date[i]))) 
            return false;
    }

    try {
        year = stoi(date.substr(0, 4));
        month = stoi(date.substr(5, 2));
    }
    catch (...) {
        return false;
    }
    return month >= 1 && month <= 12;
}

Report generateReport(const vector<Booking>& bookingRecords, const vector<Payment>& paymentRecords) {
    Report report{ 0, 0.0, 0, 0 };

    for (const Payment& payment : paymentRecords) {
        if (payment.paymentStatus) {
            ++report.completedPayments;
            report.totalRevenue += payment.totalAmount;
        }
    }
    for (const Booking& booking : bookingRecords) {
        if (!booking.cancelled) {
            ++report.totalBookings;
        }
    }
    report.totalCustomers = customerCount;
    return report;
}

void displayReport(const Report& report, const string& title) {
    cout << "\n==================================\n";
    cout << setw(static_cast<int>((34 + title.length()) / 2)) << title << "\n";
    cout << "==================================\n";
    cout << "Total bookings       : " << report.totalBookings << "\n";
    cout << "Total customers      : " << report.totalCustomers << "\n";
    cout << "Completed payments   : " << report.completedPayments << "\n";
    cout << fixed << setprecision(2);
    cout << "Total revenue        : RM " << report.totalRevenue << "\n";
    cout << "==================================\n";
}

void displayMessage(const string& message) {
    system("cls");
    cout << "+---------------------------------------------------------------+\n";
    cout << "| " << left << setw(46) << message << " |\n";
    cout << "+---------------------------------------------------------------+\n\n";
    system("pause");
}

void displayFilteredReport(const vector<Booking>& selectedBookings, const string& title) {
    set<string> selectedBookingIds;
    for (const Booking& booking : selectedBookings) 
        selectedBookingIds.insert(booking.bookingID);

    vector<Payment> selectedPayments;
    for (const Payment& payment : payments) {
        if (selectedBookingIds.count(payment.bookingId) > 0) 
            selectedPayments.push_back(payment);
    }

    Report report = generateReport(selectedBookings, selectedPayments);
    reports.push_back(report);
    system("cls");
    displayReport(report, title);
    system("pause");
}

int getCurrentYear() {
    time_t now = time(nullptr);
    tm localTime{};
    localtime_s(&localTime, &now);
    return localTime.tm_year + 1900;
}

void searchReportByMonth() {
    const int currentYear = getCurrentYear();

    while (true) {
        system("cls");
        cout << "==================================\n";
        cout << "      SEARCH REPORT BY MONTH\n";
        cout << "          Year: " << currentYear << "\n";
        cout << "==================================\n\n";
        for (int month = 1; month <= 12; ++month) 
            cout << month << ". " << monthNames[month - 1] << "\n";
        cout << "13. Exit\n\n";
        cout << "Enter choice: ";

        int choice = getMenuChoice(1, 13);
        if (choice == -1) {
            displayMessage("Invalid choice! Please enter a number from 1 to 13.          ");
            continue;
        }
        if (choice == 13) return;

        vector<Booking> selectedBookings;
        for (int i = 0; i < bookingCount; ++i) {
            int bookingYear, bookingMonth;
            if (getBookingYearAndMonth(bookings[i], bookingYear, bookingMonth) &&
                bookingYear == currentYear && bookingMonth == choice) {
                selectedBookings.push_back(bookings[i]);
            }
        }

        displayFilteredReport(selectedBookings, monthNames[choice - 1] + " " + to_string(currentYear) + " REPORT");
        return;
    }
}

void searchReportByYear() {
    int minimumYear = 0;
    int maximumYear = 0;
    for (int i = 0; i < bookingCount; ++i) {
        int bookingYear, bookingMonth;
        if (!getBookingYearAndMonth(bookings[i], bookingYear, bookingMonth)) 
            continue;
        if (minimumYear == 0 || bookingYear < minimumYear) 
            minimumYear = bookingYear;
        if (bookingYear > maximumYear) 
            maximumYear = bookingYear;
    }

    if (minimumYear == 0) {
        displayMessage("No booking dates are available for a yearly report.          ");
        return;
    }

    while (true) {
        system("cls");
        cout << "==================================\n";
        cout << "       SEARCH REPORT BY YEAR\n";
        cout << "==================================\n\n";
        cout << "Available booking years: " << minimumYear << " - " << maximumYear << "\n";
        cout << "Enter a year (0 to exit): ";

        int selectedYear = getMenuChoice(0, maximumYear);
        if (selectedYear == 0) 
            return;
        if (selectedYear == -1 || selectedYear < minimumYear) {
            displayMessage("Invalid year! Please enter a year within the displayed range.");
            continue;
        }

        vector<Booking> selectedBookings;
        for (int i = 0; i < bookingCount; ++i) {
            int bookingYear, bookingMonth;
            if (getBookingYearAndMonth(bookings[i], bookingYear, bookingMonth) && bookingYear == selectedYear) {
                selectedBookings.push_back(bookings[i]);
            }
        }

        displayFilteredReport(selectedBookings, to_string(selectedYear) + " YEARLY REPORT");
        return;
    }
}

void displayOverallReport() {
    vector<Booking> bookingRecords(bookings, bookings + bookingCount);
    if (bookingRecords.empty() && payments.empty() && customerCount == 0) {
        displayMessage("No booking or payment records are available for reporting.   ");
        return;
    }

    Report report = generateReport(bookingRecords, payments);
    reports.push_back(report);
    system("cls");
    displayReport(report, "OVERALL REPORT");
    system("pause");
}

void reporting() {
    while (true) {
        system("cls");
        cout << "==================================\n";
        cout << "             REPORT\n";
        cout << "==================================\n\n";
        cout << "1. Search by Month\n";
        cout << "2. Search by Year\n";
        cout << "3. Overall Report\n";
        cout << "4. Exit\n\n";
        cout << "Enter choice: ";

        int choice = getMenuChoice(1, 4);
        if (choice == -1) {
            displayMessage("Invalid choice! Please enter a number from 1 to 4.           ");
            continue;
        }

        switch (choice) {
        case 1: searchReportByMonth(); 
            break;
        case 2: searchReportByYear(); 
            break;
        case 3: displayOverallReport(); 
            break;
        case 4: 
            return;
        default:
            displayMessage("Invalid choice! Please enter a number from 1 to 4.           ");
        }
    }
}
