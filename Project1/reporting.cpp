#include <iostream>
#include <iomanip>
#include <set>
#include <limits>
#include "Global.h"

using namespace std;

Report generateReport(const vector<Booking>& bookingRecords, const vector<Payment>& paymentRecords) {
    Report report{ 0, 0.0, 0, 0 };
    set<string> customerIds;

    for (const Payment& payment : paymentRecords) {
        if (payment.paymentStatus) {
            ++report.completedPayments;
            report.totalRevenue += payment.totalAmount;
        }
    }
    for (const Booking& booking : bookingRecords) {
        if (!booking.cancelled) {
            ++report.totalBookings;
            if (!booking.customerID.empty()) customerIds.insert(booking.customerID);
        }
    }
    report.totalCustomers = static_cast<int>(customerIds.size());
    return report;
}

void displayReport(const Report& report) {
    cout << "\n==================================\n";
    cout << "       MANAGEMENT REPORT\n";
    cout << "==================================\n";
    cout << "Total bookings       : " << report.totalBookings << "\n";
    cout << "Total customers      : " << report.totalCustomers << "\n";
    cout << "Completed payments   : " << report.completedPayments << "\n";
    cout << fixed << setprecision(2);
    cout << "Total revenue        : RM " << report.totalRevenue << "\n";
    cout << "==================================\n";
}

void reporting() {
    vector<Booking> bookingRecords(bookings, bookings + bookingCount);
    if (bookingRecords.empty() && payments.empty()) {
        system("cls");
        cout << "+--------------------------------------------------------+\n";
        cout << "| No booking or payment records available for reporting. |\n";
        cout << "+--------------------------------------------------------+\n\n";
        system("pause");
        return;
    }

    Report report = generateReport(bookingRecords, payments);
    reports.push_back(report);
    system("cls");
    displayReport(report);
    system("pause");
}
