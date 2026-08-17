#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <ctime>
#include <regex>
#include <cmath>
#include "Struct.h"
#include "Global.h"

using namespace std;

void customerManagement();
bool processPayment(string bookID);

bool parseDate(const string& input, tm& dateStruct) {
    regex pattern(R"(^(\d{4})-(\d{1,2})-(\d{1,2})$|^(\d{1,2})/(\d{1,2})/(\d{4})$|^(\d{1,2})-(\d{1,2})-(\d{4})$)");
    smatch matches;

    if (!regex_match(input, matches, pattern)) {
        return false;
    }

    int year = 0, month = 0, day = 0;

    if (matches[1].matched) {
        year = stoi(matches[1]);
        month = stoi(matches[2]);
        day = stoi(matches[3]);
    }
    else if (matches[4].matched) {
        day = stoi(matches[4]);
        month = stoi(matches[5]);
        year = stoi(matches[6]);
    }
    else if (matches[7].matched) {
        day = stoi(matches[7]);
        month = stoi(matches[8]);
        year = stoi(matches[9]);
    }

    if (month < 1 || month > 12 || day < 1 || day > 31) {
        return false;
    }

    int daysInMonth[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    if (isLeapYear) {
        daysInMonth[2] = 29;
    }

    if (day > daysInMonth[month]) {
        return false;
    }

    dateStruct = tm{};
    dateStruct.tm_year = year - 1900;
    dateStruct.tm_mon = month - 1;
    dateStruct.tm_mday = day;
    dateStruct.tm_isdst = -1;

    return true;
}

void searchBooking()
{
    int choice;
    string search;

    while (true)
    {
        system("cls");

        cout << "==================================\n";
        cout << "Search Booking\n";
        cout << "==================================\n\n";

        cout << "1. Search by Booking ID\n";
        cout << "2. Search by Room ID\n";
        cout << "3. Search by Customer Name\n";
        cout << "4. Back\n\n";

        cout << "Enter choice: ";
        if (!(cin >> choice)) {
            clearInputBuffer();
            continue;
        }

        if (choice == 4)
        {
            return;
        }

        if (choice < 1 || choice > 3)
        {
            system("cls");
            cout << "+--------------------------------------+\n";
            cout << "Invalid choice!\n";
            cout << "+--------------------------------------+\n";
            system("pause");
            continue;
        }

        cout << "\nEnter search value: ";
        cin >> ws;
        getline(cin, search);

        bool found = false;

        for (int i = 0; i < bookingCount; i++)
        {
            if (bookings[i].bookingID.empty())
            {
                continue;
            }

            if ((choice == 1 && bookings[i].bookingID == search) ||
                (choice == 2 && bookings[i].roomNumber == search) ||
                (choice == 3 && bookings[i].customerName == search))
            {
                found = true;

                system("cls");
                cout << "==================================\n";
                cout << "Booking Found!\n";
                cout << "==================================\n\n";
                cout << "Booking ID: " << bookings[i].bookingID << endl;
                cout << "Customer Name: " << bookings[i].customerName << endl;
                cout << "Phone Number: " << bookings[i].phone << endl;
                cout << "Booking Room: " << bookings[i].roomNumber << endl;
                cout << "Room Type: " << bookings[i].roomType << "\n\n";
                system("pause");
                break;
            }
        }

        if (!found)
        {
            system("cls");
            cout << "\n+-----------------------------+\n";
            cout << "Bookings not found!\n";
            cout << "+-----------------------------+\n";
            system("pause");
        }
    }
}

void checkInBooking() {
    string id;
    system("cls");
    cout << "==================================\n";
    cout << "              CHECK-IN             \n";
    cout << "==================================\n\n";
    cout << "Enter Booking ID: ";
    cin >> ws;
    getline(cin, id);
    id = toUpperString(id);

    bool found = false;
    for (int i = 0; i < bookingCount; i++) {
        if (bookings[i].bookingID == id) {
            found = true;
            if (bookings[i].cancelled) {
                cout << "\nCannot check-in. This booking has been cancelled.\n";
            }
            else if (bookings[i].checkedIn && !bookings[i].checkedOut) {
                cout << "\nCannot check-in. This booking is already checked-in.\n";
            }
            else if (bookings[i].checkedOut) {
                cout << "\nCannot check-in. This booking is already completed.\n";
            }
            else {
                bookings[i].checkedIn = true;
                bookings[i].status = "Checked-In";
                cout << "\nBooking Found for " << bookings[i].customerName << " in Room " << bookings[i].roomNumber << ".\n";
                cout << "Check-in successful! Welcome.\n";
            }
            system("pause");
            return;
        }
    }

    if (!found) {
        cout << "\nBooking ID not found!\n";
        system("pause");
    }
}

void checkOutBooking() {
    string id;
    system("cls");
    cout << "==================================\n";
    cout << "             CHECK-OUT             \n";
    cout << "==================================\n\n";
    cout << "Enter Booking ID: ";
    cin >> ws;
    getline(cin, id);
    id = toUpperString(id);

    bool found = false;
    for (int i = 0; i < bookingCount; i++) {
        if (bookings[i].bookingID == id) {
            found = true;

            if (bookings[i].cancelled) {
                cout << "\nCannot check-out. This booking has been cancelled.\n";
            }
            else if (!bookings[i].checkedIn) {
                cout << "\nCannot check-out. This booking has not been checked-in yet.\n";
            }
            else if (bookings[i].checkedOut) {
                cout << "\nCannot check-out. This booking is already checked-out.\n";
            }
            else {
                for (int r = 0; r < MAX_ROOM; r++) {
                    if (rooms[r].roomID == bookings[i].roomNumber) {
                        rooms[r].available = true;
                        break;
                    }
                }
                bookings[i].checkedOut = true;
                bookings[i].status = "Complete";
                cout << "\nCheck-out successful! Room " << bookings[i].roomNumber << " is now marked available.\n";
            }
            system("pause");
            return;
        }
    }

    if (!found) {
        cout << "\nBooking ID not found!\n";
        system("pause");
    }
}

void checkInCheckOutMenu() {
    int choice;
    while (true) {
        system("cls");
        cout << "==================================\n";
        cout << "      CHECK-IN & CHECK-OUT        \n";
        cout << "==================================\n\n";
        cout << "1. Check-In\n";
        cout << "2. Check-Out\n";
        cout << "3. Back to Room Booking Menu\n\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            clearInputBuffer();
            cout << "\nInvalid choice!\n";
            system("pause");
            continue;
        }
        clearInputBuffer();

        switch (choice) {
        case 1:
            checkInBooking();
            break;
        case 2:
            checkOutBooking();
            break;
        case 3:
            return;
        default:
            cout << "\nInvalid choice!\n";
            system("pause");
        }
    }
}

void cancelBooking() {
    string id;
    system("cls");
    cout << "==================================\n";
    cout << "           CANCEL BOOKING          \n";
    cout << "==================================\n\n";
    cout << "Enter Booking ID: ";
    cin >> ws;
    getline(cin, id);

    bool found = false;
    for (int i = 0; i < bookingCount; i++) {
        if (bookings[i].bookingID == id) {
            found = true;
            if (bookings[i].cancelled) {
                system("cls");
                cout << "+=========================================+\n";
                cout << "  This booking has already been cancelled.\n";
                cout << "+=========================================+\n";
                system("pause");
                return;
            }

            while (true) {
                system("cls");
                cout << "==================================\n";
                cout << "           CANCEL BOOKING          \n";
                cout << "==================================\n\n";
                cout << "Booking ID: " << id << endl;
                cout << "Customer Name: " << bookings[i].customerName << endl;
                cout << "Phone Number: " << bookings[i].phone << endl;
                cout << "Booking Room: " << bookings[i].roomNumber << endl;
                cout << "Room Type: " << bookings[i].roomType << "\n\n";

                string confirmChoice;
                cout << "Confirm cancellation of booking " << id << "? (y/n): ";
                cin >> ws;
                getline(cin, confirmChoice);

                if (confirmChoice == "y" || confirmChoice == "Y") {
                    bookings[i].cancelled = true;
                    for (int r = 0; r < MAX_ROOM; r++) {
                        if (rooms[r].roomID == bookings[i].roomNumber) {
                            rooms[r].available = true;
                            break;
                        }
                    }
                    cout << "\nBooking " << id << " successfully cancelled and room released.\n";
                    system("pause");
                    break;
                }
                else if (confirmChoice == "n" || confirmChoice == "N") {
                    system("cls");
                    cout << "==========================\n";
                    cout << "Cancellation aborted.\n";
                    cout << "==========================\n";
                    system("pause");
                    break;
                }
                else {
                    cout << "\n+---------------------------------------+\n";
                    cout << "| Invalid choice! Enter 'y' or 'n'.     |\n";
                    cout << "+---------------------------------------+\n\n";
                    system("pause");
                    continue;
                }
            }
            return;
        }
    }

    if (!found) {
        system("cls");
        cout << "+------------------------------------+\n";
        cout << "|        Booking ID not found!       |\n";
        cout << "+------------------------------------+\n\n";
        system("pause");
    }
}

void viewBookings() {
    system("cls");

    cout << "========================================================================================================\n";
    cout << "                                              ALL BOOKINGS                                              \n";
    cout << "========================================================================================================\n";
    cout << "+------------+-----------------+----------------+----------+--------------+--------------+-------------+\n";
    cout << "| " << left << setw(10) << "Booking ID"
        << " | " << setw(15) << "Customer Name"
        << " | " << setw(14) << "Phone Number"
        << " | " << setw(8) << "Room"
        << " | " << setw(12) << "Check-In"
        << " | " << setw(12) << "Check-Out"
        << " | " << setw(11) << "Status" << " |\n";
    cout << "+------------+-----------------+----------------+----------+--------------+--------------+-------------+\n";

    bool found = false;
    for (int i = 0; i < bookingCount; i++) {
        if (!bookings[i].bookingID.empty()) {
            found = true;
            cout << "| " << left << setw(10) << bookings[i].bookingID
                << " | " << setw(15) << bookings[i].customerName
                << " | " << setw(14) << bookings[i].phone
                << " | " << setw(8) << bookings[i].roomNumber
                << " | " << setw(12) << bookings[i].checkInDate
                << " | " << setw(12) << bookings[i].checkOutDate
                << " | " << setw(11) << (bookings[i].status) << " |\n";
        }
    }
    cout << "+------------+-----------------+----------------+----------+--------------+--------------+-------------+\n";

    if (!found) {
        cout << "|                                  No booking records found.                                            |\n";
    }
    cout << "========================================================================================================\n\n";
    system("pause");
}

void bookRoom()
{
    int choice;
    string roomType;

    while (true)
    {
        system("cls");

        cout << "==================================\n";
        cout << "Book Room\n";
        cout << "==================================\n\n";

        cout << "1. Book Room\n";
        cout << "2. Back\n\n";

        cout << "Enter your choice: ";
        if (!(cin >> choice)) {
            clearInputBuffer();
            continue;
        }

        if (choice == 2)
            return;

        if (choice != 1)
        {
            cout << "\nInvalid choice!\n";
            system("pause");
            continue;
        }

        system("cls");

        cout << "==================================\n";
        cout << "Choose Room Type\n";
        cout << "==================================\n\n";

        cout << "1. Single\n";
        cout << "2. Double\n";
        cout << "3. Deluxe\n";
        cout << "4. Back\n\n";

        cout << "Enter your choice: ";
        if (!(cin >> choice)) {
            clearInputBuffer();
            continue;
        }

        if (choice == 1)
            roomType = "Single";
        else if (choice == 2)
            roomType = "Double";
        else if (choice == 3)
            roomType = "Deluxe";
        else if (choice == 4)
            continue;
        else
        {
            cout << "\nInvalid choice!\n";
            system("pause");
            continue;
        }

        string customerID;
        int customerIndex = -1;

        system("cls");

        cout << "==================================\n";
        cout << "Customer Verification\n";
        cout << "==================================\n\n";

        cout << "Enter Customer ID: ";
        cin >> customerID;

        for (int i = 0; i < customerCount; i++)
        {
            if (customers[i].customerID == customerID)
            {
                customerIndex = i;
                break;
            }
        }

        if (customerIndex == -1)
        {
            char option;

            cout << "\nCustomer not found!\n";
            cout << "Add new customer? (Y/N): ";
            cin >> option;

            if (option == 'Y' || option == 'y')
                customerManagement();

            return;
        }

        while (true) {
            system("cls");
            cout << "+---------------------------------------+\n";
            cout << "| Customer Details Found                |\n";
            cout << "+---------------------------------------+\n";
            cout << " Customer ID  : " << customers[customerIndex].customerID << "\n";
            cout << " Name         : " << customers[customerIndex].name << "\n";
            cout << " IC           : " << customers[customerIndex].ic << "\n";
            cout << " Phone Number : " << customers[customerIndex].phone << "\n";
            cout << " Member Type  : " << customers[customerIndex].memberType << "\n";
            cout << "-----------------------------------------\n\n";

            string confirmCustomer;
            cout << "Confirm this customer? (y/n): ";
            cin >> ws;
            getline(cin, confirmCustomer);

            if (confirmCustomer == "y" || confirmCustomer == "Y") {
                break;
            }
            else if (confirmCustomer == "n" || confirmCustomer == "N") {
                return;
            }
            else {
                system("cls");
                cout << "\n+---------------------------------------+\n";
                cout << "| Invalid choice! Enter 'y' or 'n'.     |\n";
                cout << "+---------------------------------------+\n\n";
                system("pause");
            }
        }

        vector<int> roomList;

        for (int i = 0; i < MAX_ROOM; i++)
        {
            if (rooms[i].roomType == roomType && rooms[i].available)
            {
                roomList.push_back(i);
            }
        }

        if (roomList.empty())
        {
            cout << "\nNo available rooms!\n";
            system("pause");
            continue;
        }

        system("cls");

        cout << "========================================\n";
        cout << roomType << " Room List\n";
        cout << "========================================\n\n";

        for (size_t i = 0; i < roomList.size(); i++)
        {
            int index = roomList[i];

            if (i + 1 < 10) {
                cout << i + 1 << ".   ";
            }
            else {
                cout << i + 1 << ".  ";
            }

            cout << left << setw(10) << rooms[index].roomID;
            cout << setw(12) << ("RM " + to_string((int)rooms[index].price));
            cout << "Available\n";
        }

        int roomChoice;

        cout << "\nEnter room choice: ";
        if (!(cin >> roomChoice)) {
            clearInputBuffer();
            continue;
        }

        if (roomChoice < 1 || roomChoice > static_cast<int>(roomList.size()))
        {
            cout << "\nInvalid room!\n";
            system("pause");
            continue;
        }

        int roomIndex = roomList[roomChoice - 1];

        string checkIn = "";
        string checkOut = "";
        string rawCheckIn, rawCheckOut;
        int totalNights;

        while (true) {
            system("cls");
            cout << "==================================\n";
            cout << "           ENTER DATES            \n";
            cout << "==================================\n\n";

            cout << "(YYYY-MM-DD or DD/MM/YYYY or DD-MM-YYYY are acceptable)\n\n";
            cout << "Enter Check-in Date: ";
            cin >> ws;
            getline(cin, rawCheckIn);

            tm inDateStruct{};
            inDateStruct.tm_isdst = -1;
            if (!parseDate(rawCheckIn, inDateStruct)) {
                cout << "\n+----------------------------------------+\n";
                cout << "| Invalid Check-in date format or value! |\n";
                cout << "+----------------------------------------+\n\n";
                system("pause");
                continue;
            }

            cout << "Enter Check-out Date: ";
            getline(cin, rawCheckOut);

            tm outDateStruct{};
            outDateStruct.tm_isdst = -1;
            if (!parseDate(rawCheckOut, outDateStruct)) {
                cout << "\n+----------------------------------------+\n";
                cout << "| Invalid Check-out date format or value! |\n";
                cout << "+----------------------------------------+\n\n";
                system("pause");
                continue;
            }

            char bufferIn[11], bufferOut[11];
            strftime(bufferIn, sizeof(bufferIn), "%Y-%m-%d", &inDateStruct);
            strftime(bufferOut, sizeof(bufferOut), "%Y-%m-%d", &outDateStruct);
            checkIn = bufferIn;
            checkOut = bufferOut;

            time_t timeIn = mktime(&inDateStruct);
            time_t timeOut = mktime(&outDateStruct);

            if (timeIn == (time_t)-1 || timeOut == (time_t)-1) {
                cout << "\n+---------------------------------------+\n";
                cout << "| Date is out of supported range!       |\n";
                cout << "+---------------------------------------+\n\n";
                system("pause");
                continue;
            }

            if (timeIn >= timeOut) {
                cout << "\n+---------------------------------------+\n";
                cout << "| Check-out must be after check-in!     |\n";
                cout << "+---------------------------------------+\n\n";
                system("pause");
                continue;
            }

            double diffSeconds = difftime(timeOut, timeIn);
            totalNights = static_cast<int>(round(diffSeconds / (60 * 60 * 24)));

            break;
        }

        char confirm;

        cout << "\nCustomer : " << customers[customerIndex].name << endl;
        cout << "Room     : " << rooms[roomIndex].roomID << endl;
        cout << "Type     : " << rooms[roomIndex].roomType << endl;
        cout << "Nights   : " << totalNights << endl;
        cout << "Price    : RM " << fixed << setprecision(2) << rooms[roomIndex].price << " per night\n";

        cout << "\nConfirm Booking (Y/N): ";
        cin >> confirm;
        clearInputBuffer();

        if (confirm != 'Y' && confirm != 'y')
        {
            cout << "\nBooking Cancelled!\n";
            system("pause");
            continue;
        }

        if (bookingCount >= MAX_BOOKINGS)
        {
            system("cls");
            cout << "\nBooking storage full!\n";
            system("pause");
            return;
        }

        string generatedBookingID = "B";
        if (bookingCount + 1 < 10)
            generatedBookingID += "00";
        else if (bookingCount + 1 < 100)
            generatedBookingID += "0";
        generatedBookingID += to_string(bookingCount + 1);

        bookings[bookingCount].bookingID = generatedBookingID;
        bookings[bookingCount].customerID = customers[customerIndex].customerID;
        bookings[bookingCount].customerName = customers[customerIndex].name;
        bookings[bookingCount].phone = customers[customerIndex].phone;
        bookings[bookingCount].roomNumber = rooms[roomIndex].roomID;
        bookings[bookingCount].roomType = rooms[roomIndex].roomType;
        bookings[bookingCount].checkInDate = checkIn;
        bookings[bookingCount].checkOutDate = checkOut;
        bookings[bookingCount].checkedIn = false;
        bookings[bookingCount].checkedOut = false;
        bookings[bookingCount].status = "Confirmed";
        bookings[bookingCount].nights = totalNights;

        bookingCount++;

        if (processPayment(generatedBookingID)) {
            rooms[roomIndex].available = false;

            system("cls");
            cout << "==================================\n";
            cout << "Booking Successful!\n";
            cout << "==================================\n\n";
            cout << "Booking ID : " << bookings[bookingCount - 1].bookingID << endl;
            cout << "Room ID    : " << bookings[bookingCount - 1].roomNumber << endl;
            cout << "==================================\n";

            system("pause");
            return;
        }
        else {
            bookingCount--;
            bookings[bookingCount] = Booking{};
            system("cls");
            cout << "\nBooking Cancelled!\n";
            system("pause");
            return;
        }
    }
}

void roomBooking() {
    int choice;

    while (true) {
        system("cls");
        cout << "==================================\n";
        cout << "Room Booking\n";
        cout << "==================================\n\n";
        cout << "1. Book Room\n";
        cout << "2. Check in/Check out\n";
        cout << "3. Cancel Booking\n";
        cout << "4. Seach Booking\n";
        cout << "5. Display Booking\n";
        cout << "6. Exit\n\n";

        cout << "Enter your choice: ";
        if (!(cin >> choice)) {
            clearInputBuffer();
            continue;
        }

        switch (choice) {
        case 1:
            bookRoom();
            break;
        case 2:
            checkInCheckOutMenu();
            break;
        case 3:
            cancelBooking();
            break;
        case 4:
            searchBooking();
            break;
        case 5:
            viewBookings();
            break;
        case 6:
            system("cls");
            return;
        default:
            system("cls");
            cout << "+-----------------------------+\n";
            cout << "Invalid choice!\n";
            cout << "+-----------------------------+\n";
            system("pause");
        }
    }
}