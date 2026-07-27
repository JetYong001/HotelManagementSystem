#include <iostream>
#include <iomanip>
#include <vector>
#include "Struct.h"
#include "Global.h"

using namespace std;

void customerManagement();

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
        cin >> choice;


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
        cin >> choice;


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

            continue;
        }



        vector<int> roomList;


        for (int i = 0; i < MAX_ROOM; i++)
        {
            if (rooms[i].roomType == roomType &&
                rooms[i].available)
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


        for (int i = 0; i < roomList.size(); i++)
        {
            int index = roomList[i];

            if (i + 1 < 10) {
                cout << i + 1 << ".   ";
            }
            else {
                cout << i + 1 << ".  ";
            }

            cout << left << setw(10)
                << rooms[index].roomID;

            cout << setw(12)
                << ("RM " + to_string((int)rooms[index].price));

            cout << "Available";

            cout << endl;
        }



        int roomChoice;

        cout << "\nEnter room choice: ";
        cin >> roomChoice;


        if (roomChoice < 1 ||
            roomChoice > roomList.size())
        {
            cout << "\nInvalid room!\n";
            system("pause");
            continue;
        }


        int roomIndex = roomList[roomChoice - 1];



        string checkIn;
        string checkOut;


        cout << "\nCheck In Date : ";
        cin >> checkIn;

        cout << "Check Out Date: ";
        cin >> checkOut;



        char confirm;


        cout << "\nCustomer : "
            << customers[customerIndex].name << endl;

        cout << "Room     : "
            << rooms[roomIndex].roomID << endl;

        cout << "Type     : "
            << rooms[roomIndex].roomType << endl;

        cout << "Price    : RM "
            << fixed << setprecision(2)
            << rooms[roomIndex].price << endl;


        cout << "\nConfirm Booking (Y/N): ";
        cin >> confirm;


        if (confirm != 'Y' && confirm != 'y')
        {
            cout << "\nBooking Cancelled!\n";
            system("pause");
            continue;
        }



        if (bookingCount >= MAX_BOOKINGS)
        {
            cout << "\nBooking storage full!\n";
            system("pause");
            return;
        }



        bookings[bookingCount].bookingID = "B";


        if (bookingCount + 1 < 10)
            bookings[bookingCount].bookingID += "00";
        else if (bookingCount + 1 < 100)
            bookings[bookingCount].bookingID += "0";


        bookings[bookingCount].bookingID += to_string(bookingCount + 1);



        bookings[bookingCount].customerName =
            customers[customerIndex].name;


        bookings[bookingCount].phone =
            customers[customerIndex].phone;


        bookings[bookingCount].roomNumber =
            rooms[roomIndex].roomID;


        bookings[bookingCount].roomType =
            rooms[roomIndex].roomType;


        bookings[bookingCount].checkInDate = checkIn;

        bookings[bookingCount].checkOutDate = checkOut;


        bookings[bookingCount].checkedIn = false;

        bookings[bookingCount].checkedOut = false;

        bookings[bookingCount].cancelled = false;



        rooms[roomIndex].available = false;


        bookingCount++;



        system("cls");

        cout << "==================================\n";
        cout << "Booking Successful!\n";
        cout << "==================================\n\n";

        cout << "Booking ID : "
            << bookings[bookingCount - 1].bookingID
            << endl;

        cout << "Room ID    : "
            << bookings[bookingCount - 1].roomNumber
            << endl;


        cout << "==================================\n";


        system("pause");
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
        cin >> choice;
        switch (choice) {
        case 1:
            bookRoom();
            break;
        case 2:
           
            break;
        case 3:
            
            break;
        case 4:
           
            break;
        case 5:
          
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