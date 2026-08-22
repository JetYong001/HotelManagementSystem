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

void addCustomer();
bool processPayment(string bookID);

bool parseDate(const string& input, tm& dateStruct) {
    regex pattern(R"(^(\d{4})([/-])(\d{1,2})\2(\d{1,2})$|^(\d{1,2})([/-])(\d{1,2})\6(\d{4})$)");
    smatch matches;

    if (!regex_match(input, matches, pattern)) {
        return false;
    }

    int year = 0, month = 0, day = 0;

    if (matches[1].matched) {
        year = stoi(matches[1]);
        month = stoi(matches[3]);
        day = stoi(matches[4]);
    }
    else if (matches[5].matched) {
        day = stoi(matches[5]);
        month = stoi(matches[7]);
        year = stoi(matches[8]);
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

string generateBookingID() {
    string generatedBookingID = "B";
    if (bookingCount + 1 < 10)
        generatedBookingID += "00";
    else if (bookingCount + 1 < 100)
        generatedBookingID += "0";
    generatedBookingID += to_string(bookingCount + 1);

    return generatedBookingID;
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
        int choice = getMenuChoice(1, 4);

        if (choice == -1) {
            system("cls");
            cout << "+--------------------------------+\n";
            cout << "| Invalid choice!                |\n";
            cout << "+--------------------------------+\n";
            system("pause");
            continue;
        }

        if (choice == 4)
        {
            return;
        }

        if (choice < 1 || choice > 3)
        {
            system("cls");
            cout << "+--------------------------------+\n";
            cout << "| Invalid choice!                |\n";
            cout << "+--------------------------------+\n";
            system("pause");
            continue;
        }

        cout << "\nEnter search value: ";
        getline(cin >> ws, search);

        search = toUpperString(search);
        bool found = false;

        system("cls");
        cout << "======================================\n";
        cout << "Search Results\n";
        cout << "======================================\n\n";

        for (int i = 0; i < bookingCount; i++)
        {
            if (bookings[i].bookingID.empty())
            {
                continue;
            }

            bool match = false;

            if (choice == 1 && bookings[i].bookingID == search)
            {
                match = true;
            }
            else if (choice == 2 && bookings[i].roomNumber == search)
            {
                match = true;
            }
            else if (choice == 3)
            {
                string storedName = toLowerString(bookings[i].customerName);
                string queryName = toLowerString(search);

                if (storedName.find(queryName) != string::npos)
                    match = true;
            }

            if (match)
            {
                found = true;

                cout << "Booking ID   : " << bookings[i].bookingID << "\n";
                cout << "Customer Name: " << bookings[i].customerName << "\n";
                cout << "Phone Number : " << bookings[i].phone << "\n";
                cout << "Booking Room : " << bookings[i].roomNumber << "\n";
                cout << "Room Type    : " << bookings[i].roomType << "\n";
                cout << "Status       : " << bookings[i].status << "\n";
                cout << "-------------------------------------\n\n";
                system("pause");
            }
        }

        if (!found)
        {
            system("cls");
            cout << "+-----------------------------+\n";
            cout << "| Booking not found!          |\n";
            cout << "+-----------------------------+\n";
            system("pause");
        }
    }
}

void checkInBooking() {
    string id;

    while (true)
    {
        system("cls");
        cout << "==================================\n";
        cout << "              CHECK-IN             \n";
        cout << "==================================\n\n";
        cout << "Enter Booking ID: ";
        getline(cin >> ws, id);

        id = toUpperString(id);

        bool found = false;
        bool success = false;

        for (int i = 0; i < bookingCount; i++) {
            if (bookings[i].bookingID == id) {
                found = true;

                if (bookings[i].cancelled) {
                    system("cls");
                    cout << "+--------------------------------------------------------+\n";
                    cout << "| Cannot check-in. This booking has been cancelled.      |\n";
                    cout << "+--------------------------------------------------------+\n";
                    system("pause");
                }
                else if (bookings[i].checkedIn && !bookings[i].checkedOut) {
                    system("cls");
                    cout << "+--------------------------------------------------------+\n";
                    cout << "| Cannot check-in. This booking is already checked-in.   |\n";
                    cout << "+--------------------------------------------------------+\n";
                    system("pause");
                }
                else if (bookings[i].checkedOut) {
                    system("cls");
                    cout << "+--------------------------------------------------------+\n";
                    cout << "| Cannot check-in. This booking is already completed.    |\n";
                    cout << "+--------------------------------------------------------+\n";
                    system("pause");
                }
                else {
                    bookings[i].checkedIn = true;
                    bookings[i].status = "Checked-In";
                    system("cls");
                    cout << "Booking Found for " << bookings[i].customerName << " in Room " << bookings[i].roomNumber << ".\n\n";
                    cout << "+----------------------------------------------+\n";
                    cout << "| Check-in successful! Welcome.                |\n";
                    cout << "+----------------------------------------------+\n";
                    system("pause");
                    success = true;
                }

                cout << endl;
                break;
            }
        }

        if (!found) {
            system("cls");
            cout << "+------------------------------------+\n";
            cout << "|        Booking ID not found!       |\n";
            cout << "+------------------------------------+\n\n";
            system("pause");
        }
        else if (success) {
            return;
        }

    }
}

void checkOutBooking() {
    string id;

    while (true)
    {
        system("cls");
        cout << "==================================\n";
        cout << "             CHECK-OUT             \n";
        cout << "==================================\n\n";
        cout << "Enter Booking ID: ";
        getline(cin >> ws, id);

        id = toUpperString(id);

        bool found = false;
        bool success = false;
        
        for (int i = 0; i < bookingCount; i++) {
            if (bookings[i].bookingID == id) {
                found = true;

                if (bookings[i].cancelled) {
                    system("cls");
                    cout << "+-------------------------------------------------------------+\n";
                    cout << "| Cannot check-out. This booking has been cancelled.          |\n";
                    cout << "+-------------------------------------------------------------+\n";
                    system("pause");
                }
                else if (!bookings[i].checkedIn) {
                    system("cls");
                    cout << "+-------------------------------------------------------------+\n";
                    cout << "| Cannot check-out. This booking has not been checked-in yet. |\n";
                    cout << "+-------------------------------------------------------------+\n";
                    system("pause");
                }
                else if (bookings[i].checkedOut) {
                    system("cls");
                    cout << "+-------------------------------------------------------------+\n";
                    cout << "| Cannot check-out. This booking is already checked-out.      |\n";
                    cout << "+-------------------------------------------------------------+\n";
                    system("pause");
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
                    system("cls");
                    cout << "+-------------------------------------------------------------+\n";
                    cout << "| Check-out successful! Room " << bookings[i].roomNumber << " is now available.     |\n";
                    cout << "+-------------------------------------------------------------+\n";
                    system("pause");
                    success = true;
                }

                cout << endl;
                break;
            }
        }

        if (!found) {
            system("cls");
            cout << "+------------------------------------+\n";
            cout << "|        Booking ID not found!       |\n";
            cout << "+------------------------------------+\n\n";
            system("pause");
        }
        else if (success) {
            return;
        }

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
        cout << "3. Back\n\n";

        cout << "Enter your choice: ";
        choice = getMenuChoice(1, 3);

        if (choice == -1) {
            system("cls");
            cout << "+--------------------------------+\n";
            cout << "| Invalid choice!                |\n";
            cout << "+--------------------------------+\n";
            system("pause");
            continue;
        }

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
            system("cls");
            cout << "+--------------------------------+\n";
            cout << "| Invalid choice!                |\n";
            cout << "+--------------------------------+\n";
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
    getline(cin >> ws, id);

    id = toUpperString(id);
    bool found = false;

    for (int i = 0; i < bookingCount; i++) {
        if (bookings[i].bookingID == id) {
            found = true;
            if (bookings[i].cancelled) {
                system("cls");
                cout << "+------------------------------------------+\n";
                cout << "| This booking has already been cancelled! |\n";
                cout << "+------------------------------------------+\n";
                system("pause");
                return;
            }

            while (true) {
                system("cls");
                cout << "==================================\n";
                cout << "           CANCEL BOOKING          \n";
                cout << "==================================\n\n";
                cout << "Booking ID   : " << id << endl;
                cout << "Customer Name: " << bookings[i].customerName << endl;
                cout << "Phone Number : " << bookings[i].phone << endl;
                cout << "Booking Room : " << bookings[i].roomNumber << endl;
                cout << "Room Type    : " << bookings[i].roomType << "\n\n";

                string confirmChoice;
                cout << "Confirm cancellation of booking " << id << "? (y/n): ";
                getline(cin >> ws, confirmChoice);

                if (confirmChoice == "y" || confirmChoice == "Y") {
                    bookings[i].cancelled = true;
					bookings[i].status = "Cancelled";
                    for (int r = 0; r < MAX_ROOM; r++) {
                        if (rooms[r].roomID == bookings[i].roomNumber) {
                            rooms[r].available = true;
                            break;
                        }
                    }
                    system("cls");
                    cout << "+----------------------------------------------------------+\n";
                    cout << "| Booking " << id << " successfully cancelled and room released. |\n";
                    cout << "+----------------------------------------------------------+\n";
                    system("pause");
                    break;
                }
                else if (confirmChoice == "n" || confirmChoice == "N") {
                    system("cls");
                    cout << "+--------------------------------+\n";
                    cout << "| Cancellation aborted!          |\n";
                    cout << "+--------------------------------+\n";
                    system("pause");
                    break;
                }
                else {
                    system("cls");
                    cout << "+--------------------------------+\n";
                    cout << "| Invalid choice! Enter y or n.  |\n";
                    cout << "+--------------------------------+\n";
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
    if (bookingCount >= MAX_BOOKINGS)
    {
        system("cls");
        cout << "+--------------------------------+\n";
        cout << "| Booking storage is full!       |\n";
        cout << "+--------------------------------+\n\n";
        system("pause");
        return;
    }

    int choice;
    string roomType;

    while (true)
    {
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
            system("cls");
            cout << "+--------------------------------+\n";
            cout << "| Invalid choice!                |\n";
            cout << "+--------------------------------+\n";
            system("pause");
            continue;
        }
        clearInputBuffer();

        if (choice == 1)
            roomType = "Single";
        else if (choice == 2)
            roomType = "Double";
        else if (choice == 3)
            roomType = "Deluxe";
        else if (choice == 4)
            return;
        else
        {
            system("cls");
            cout << "+--------------------------------+\n";
            cout << "| Invalid choice!                |\n";
            cout << "+--------------------------------+\n";
            system("pause");
            continue;
        }

        string customerID;
        int customerIndex = -1;
        bool customerConfirmed = false;
        bool backToRoomMenu = false;

        while (!customerConfirmed) {
            system("cls");
            cout << "==================================\n";
            cout << "Customer Verification\n";
            cout << "==================================\n\n";

            cout << "(Type x to return)\n\n";

            cout << "Enter Customer ID: ";
            getline(cin >> ws, customerID);
            customerID = toUpperString(customerID);

            if (customerID == "x" || customerID == "X") {
                backToRoomMenu = true;
                break;
            }

            customerIndex = -1;
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
                while (true) {
                    string option;
                    cout << "\nCustomer not found!\n";
                    cout << "Add new customer? (y/n): ";
                    getline(cin >> ws, option);

                    if (option == "Y" || option == "y") {
                        addCustomer();
                        for (int i = 0; i < customerCount; i++) {
                            if (customers[i].customerID == customerID) {
                                customerIndex = i;
                                break;
                            }
                        }
                        break;
                    }
                    else if (option == "N" || option == "n") {
                        break;
                    }
                    else {
                        system("cls");
                        cout << "+--------------------------------+\n";
                        cout << "| Invalid choice! Enter y or n.  |\n";
                        cout << "+--------------------------------+\n";
                        system("pause");

                        system("cls");
                        cout << "==================================\n";
                        cout << "Customer Verification\n";
                        cout << "==================================\n\n";

                        cout << "(Type x to return)\n\n";

                        cout << "Enter Customer ID: " << customerID << "\n";
                    }
                }

                if (customerIndex == -1) {
                    continue;
                }
            }

            while (customerIndex != -1) {
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
                getline(cin >> ws, confirmCustomer);

                if (confirmCustomer == "y" || confirmCustomer == "Y") {
                    customerConfirmed = true;
                    break;
                }
                else if (confirmCustomer == "n" || confirmCustomer == "N") {
                    customerIndex = -1;
                    break;
                }
                else {
                    system("cls");
                    cout << "+------------------------------------+\n";
                    cout << "| Invalid choice! Enter y or n.      |\n";
                    cout << "+------------------------------------+\n\n";
                    system("pause");
                }
            }
        }

        if (backToRoomMenu) {
            continue;
        }

        if (!customerConfirmed) {
            continue;
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
            system("cls");
            cout << "+--------------------------+\n";
            cout << "| No available room!       |\n";
            cout << "+--------------------------+\n\n";
            system("pause");
            continue;
        }

        int roomChoice;
        int roomIndex = -1;

        while (true) {
            system("cls");
            cout << "=====================================================\n";
            cout << "                  " << roomType << " ROOM LIST                  \n";
            cout << "=====================================================\n";
            cout << "+-----+---------------+-----------------+-----------+\n";
            cout << "| " << left << setw(4) << "No."
                << "| " << setw(14) << "Room ID"
                << "| " << setw(16) << "Price/Night"
                << "| " << setw(9) << "Status" << " |\n";
            cout << "+-----+---------------+-----------------+-----------+\n";

            for (size_t i = 0; i < roomList.size(); i++)
            {
                int index = roomList[i];
                string priceStr = "RM " + to_string((int)rooms[index].price);
                string statusStr = rooms[index].available ? "Available" : "Occupied";

                cout << "| " << left << setw(4) << (i + 1)
                    << "| " << setw(14) << rooms[index].roomID
                    << "| " << setw(16) << priceStr
                    << "| " << setw(9) << statusStr << " |\n";
            }
            cout << "+-----+---------------+-----------------+-----------+\n\n";

            cout << "Enter room choice : ";
            roomChoice = getMenuChoice(1, static_cast<int>(roomList.size()));

            if (roomChoice == -1) {
                system("cls");
                cout << "+--------------------------------+\n";
                cout << "| Invalid input or room choice!  |\n";
                cout << "+--------------------------------+\n";
                system("pause");
                continue;
            }

            roomIndex = roomList[roomChoice - 1];
            break;
        }

        string checkIn = "";
        string checkOut = "";
        string rawCheckIn, rawCheckOut;
        int totalNights;

        while (true) {
            system("cls");
            cout << "===============================================\n";
            cout << "                  ENTER DATES                  \n";
            cout << "===============================================\n\n";

            cout << "(YYYY/MM/DD or YYYY-MM-DD or DD/MM/YYYY or DD-MM-YYYY are acceptable)\n\n";
            cout << "Enter Check-in Date: ";
            getline(cin >> ws, rawCheckIn);

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
            getline(cin >> ws, rawCheckOut);

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
                cout << endl;
                cout << "+---------------------------------------+\n";
                cout << "| Date is out of supported range!       |\n";
                cout << "+---------------------------------------+\n\n";
                system("pause");
                continue;
            }

            if (timeIn >= timeOut) {
                cout << endl;
                cout << "+---------------------------------------+\n";
                cout << "| Check-out must be after check-in!     |\n";
                cout << "+---------------------------------------+\n\n";
                system("pause");
                continue;
            }

            double diffSeconds = difftime(timeOut, timeIn);
            totalNights = static_cast<int>(round(diffSeconds / (60 * 60 * 24)));

            break;
        }

        string confirm;
        bool validConfirmation = false;

        while (!validConfirmation) {
            system("cls");
            cout << "==================================\n";
            cout << "       BOOKING CONFIRMATION       \n";
            cout << "==================================\n\n";
            cout << "Customer     : " << customers[customerIndex].name << endl;
            cout << "Room ID      : " << rooms[roomIndex].roomID << endl;
            cout << "Room Type    : " << rooms[roomIndex].roomType << endl;
            cout << "Check-in     : " << checkIn << endl;
            cout << "Check-out    : " << checkOut << endl;
            cout << "Total Nights : " << totalNights << endl;
            cout << "Price        : RM " << fixed << setprecision(2) << rooms[roomIndex].price << " per night\n";
            cout << "==================================\n\n";

            cout << "Confirm Booking (y/n): ";
            getline(cin >> ws, confirm);

            if (confirm == "Y" || confirm == "y") {
                validConfirmation = true;
                break;
            }
            else if (confirm == "N" || confirm == "n") {
                system("cls");
                cout << "+--------------------------------+\n";
                cout << "|       Booking Cancelled!       |\n";
                cout << "+--------------------------------+\n\n";
                system("pause");
                validConfirmation = false;
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

        if (!validConfirmation) {
            continue;
        }

        Booking newBooking;
        newBooking.bookingID = generateBookingID();
        newBooking.customerID = customers[customerIndex].customerID;
        newBooking.customerName = customers[customerIndex].name;
        newBooking.phone = customers[customerIndex].phone;
        newBooking.roomNumber = rooms[roomIndex].roomID;
        newBooking.roomType = rooms[roomIndex].roomType;
        newBooking.checkInDate = checkIn;
        newBooking.checkOutDate = checkOut;
        newBooking.checkedIn = false;
        newBooking.checkedOut = false;
        newBooking.status = "Confirmed";
        newBooking.nights = totalNights;
        newBooking.isPaid = false;

        bookings[bookingCount] = newBooking;
        bookingCount++;

        if (processPayment(newBooking.bookingID)) {
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
            cout << "+--------------------------------+\n";
            cout << "|       Booking Cancelled!       |\n";
            cout << "+--------------------------------+\n\n";
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
        cout << "4. Search Booking\n";
        cout << "5. Display Booking\n";
        cout << "6. Exit\n\n";

        cout << "Enter your choice: ";
        choice = getMenuChoice(1, 6);

        if (choice == -1) {
            system("cls");
            cout << "+--------------------------------+\n";
            cout << "| Invalid choice!                |\n";
            cout << "+--------------------------------+\n";
            system("pause");
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
            cout << "+--------------------------------+\n";
            cout << "| Invalid choice!                |\n";
            cout << "+--------------------------------+\n";
            system("pause");
        }
    }
}