#include <iostream>
#include <iomanip>
#include "struct.h"
#include "Global.h"

using namespace std;

void searchRoom()
{
    string search;

    while (true)
    {
        system("cls");
        cout << "==================================\n";
        cout << "Search Room\n";
        cout << "==================================\n\n";

        cout << "Enter room ID (or x to go back): ";
        getline(cin >> ws, search);

        if (search == "X" || search == "x") {
            return;
        }

        search = toUpperString(search);
        bool found = false;

        for (int i = 0; i < MAX_ROOM; i++)
        {
            if (!rooms[i].roomID.empty() && rooms[i].roomID == search)
            {
                found = true;
                break;
            }
        }

        system("cls");

        if (found)
        {
            cout << "==================================\n";
            cout << "Search Results\n";
            cout << "==================================\n\n";

            for (int i = 0; i < MAX_ROOM; i++)
            {
                if (rooms[i].roomID == search)
                {
                    cout << "Room Found!\n";
                    cout << "----------------------------------\n";
                    cout << "Room ID    : " << rooms[i].roomID << "\n";
                    cout << "Room Type  : " << rooms[i].roomType << "\n";
                    cout << "Room Price : RM " << fixed << setprecision(2) << rooms[i].price << "\n";
                    cout << "Room Status: " << (rooms[i].available ? "Available" : "Occupied") << "\n";
                    cout << "----------------------------------\n\n";
                }
            }
        }
        else
        {
            cout << "+--------------------------------+\n";
            cout << "| Room not found!                |\n";
            cout << "+--------------------------------+\n\n";
        }

        system("pause");
    }
}


void editRoomStatus()
{
    string id;
    char confirm;

    system("cls");
    cout << "==================================\n";
    cout << "Edit Room Status\n";
    cout << "==================================\n\n";

    cout << "Enter Room ID (or x to go back): ";
    getline(cin >> ws, id);

    if (id == "X" || id == "x") {
        return;
    }

    id = toUpperString(id);
    bool found = false;

    for (int i = 0; i < MAX_ROOM; i++)
    {
        if (rooms[i].roomID == id)
        {
            found = true;

            while (true)
            {
                system("cls");
                cout << "Current Room Status\n";
                cout << "----------------------------------\n\n";
                cout << "<Room " << rooms[i].roomID << ">\n";

                if (rooms[i].available) {
                    cout << "Current status: Available\n\n";
                    cout << "Confirm update to Occupied? (y/n): ";
                }
                else {
                    cout << "Current status: Occupied\n\n";
                    cout << "Confirm update to Available? (y/n): ";
                }

                if (!(cin >> confirm)) {
                    clearInputBuffer();
                    system("cls");
                    cout << "+--------------------------------+\n";
                    cout << "| Invalid input!                 |\n";
                    cout << "+--------------------------------+\n";
                    system("pause");
                    continue;
                }
                clearInputBuffer();

                if (confirm == 'y' || confirm == 'Y')
                {
                    rooms[i].available = !rooms[i].available;

                    system("cls");
                    cout << "+-----------------------------------+\n";
                    cout << "| Room Status updated successfully! |\n";
                    cout << "+-----------------------------------+\n";
                    system("pause");
                    return;
                }
                else if (confirm == 'n' || confirm == 'N')
                {
                    system("cls");
                    cout << "+--------------------------------+\n";
                    cout << "| Update cancelled!              |\n";
                    cout << "+--------------------------------+\n";
                    system("pause");
                    return;
                }
                else
                {
                    system("cls");
                    cout << "+--------------------------------+\n";
                    cout << "| Invalid input!                 |\n";
                    cout << "+--------------------------------+\n";
                    system("pause");
                }
            }
        }
    }

    if (!found)
    {
        system("cls");
        cout << "+--------------------------------+\n";
        cout << "| Room not found!                |\n";
        cout << "+--------------------------------+\n";
        system("pause");
    }
}


void viewAvailableRoom()
{
    int choice;
    string type;

    system("cls");

    while (true) {
        int available = 0;
        int occupied = 0;

        system("cls");
        cout << "==============================\n";
        cout << "     VIEW AVAILABLE ROOM     \n";
        cout << "==============================\n\n";

        cout << "1. Single\n";
        cout << "2. Double\n";
        cout << "3. Deluxe\n";
        cout << "4. Back\n\n";

        cout << "Enter choice: ";
        choice = getMenuChoice(1, 4);

        if (choice == -1) {
            system("cls");
            cout << "+--------------------------------+\n";
            cout << "| Invalid choice!                |\n";
            cout << "+--------------------------------+\n";
            system("pause");
            continue;
        }

        switch (choice)
        {
        case 1:
            type = "Single";
            break;
        case 2:
            type = "Double";
            break;
        case 3:
            type = "Deluxe";
            break;
        case 4:
            return;
        default:
            system("cls");
            cout << "+--------------------------------+\n";
            cout << "| Invalid choice!                |\n";
            cout << "+--------------------------------+\n";
            system("pause");
            continue;
        }

        system("cls");

        cout << "====================================================\n";
        cout << "                 " << type << " ROOM\n";
        cout << "====================================================\n";

        cout << "+----------------+-----------------+---------------+\n";
        cout << "| Room ID        | Price (RM)      | Status        |\n";
        cout << "+----------------+-----------------+---------------+\n";

        bool found = false;

        for (int i = 0; i < MAX_ROOM; i++)
        {
            if (rooms[i].roomType == type && rooms[i].available)
            {
                found = true;
                available++;
                cout << "| "
                    << left << setw(14) << rooms[i].roomID
                    << " | "
                    << "RM " << setw(12) << fixed << setprecision(2) << rooms[i].price
                    << " | "
                    << setw(13)
                    << (rooms[i].available ? "Available" : "Occupied")
                    << " |\n";
            }
        }

        if (!found)
        {
            cout << "|                     No room found                 |\n";
        }

        cout << "+----------------+-----------------+---------------+\n\n";

        cout << "====================================================\n";
        cout << "Total Available = " << available << "\n";
        cout << "====================================================\n";
      
        system("pause");
        system("cls");
    }
}


void viewRoomDetails()
{
    int choice;
    string type;

    system("cls");

    while (true) {
        int available = 0;
        int occupied = 0;

        system("cls");
        cout << "==============================\n";
        cout << "      VIEW ROOM DETAILS\n";
        cout << "==============================\n\n";

        cout << "1. Single\n";
        cout << "2. Double\n";
        cout << "3. Deluxe\n";
        cout << "4. Back\n\n";

        cout << "Enter choice: ";
        choice = getMenuChoice(1, 4);

        if (choice == -1) {
            system("cls");
            cout << "+--------------------------------+\n";
            cout << "| Invalid choice!                |\n";
            cout << "+--------------------------------+\n";
            system("pause");
            continue;
        }

        switch (choice)
        {
        case 1:
            type = "Single";
            break;
        case 2:
            type = "Double";
            break;
        case 3:
            type = "Deluxe";
            break;
        case 4:
            return;
        default:
            system("cls");
            cout << "+--------------------------------+\n";
            cout << "| Invalid choice!                |\n";
            cout << "+--------------------------------+\n";
            system("pause");
            continue;
        }

        system("cls");
        cout << "====================================================\n";
        cout << "                 " << type << " ROOM\n";
        cout << "====================================================\n";

        cout << "+----------------+-----------------+---------------+\n";
        cout << "| Room ID        | Price (RM)      | Status        |\n";
        cout << "+----------------+-----------------+---------------+\n";

        bool found = false;

        for (int i = 0; i < MAX_ROOM; i++)
        {
            if (rooms[i].roomType == type)
            {
                found = true;
               
                cout << "| "
                    << left << setw(14) << rooms[i].roomID
                    << " | "
                    << "RM " << setw(12) << fixed << setprecision(2) << rooms[i].price
                    << " | "
                    << setw(13)
                    << (rooms[i].available ? "Available" : "Occupied")
                    << " |\n";

                if (rooms[i].available) {
                    available ++;
                }
                else {
                    occupied++;
                }
            }
        }

        if (!found)
        {
            cout << "|                     No room found                 |\n";
        }

        cout << "+----------------+-----------------+---------------+\n\n";

        cout << "====================================================\n";
        cout << "Total Available = " << available << "\n";
        cout << "Total Occupied = " << occupied << "\n";
        cout << "====================================================\n";

        system("pause");
        system("cls");
    }
}


void roomManagement() {

    int choice;

    while (true) {
        system("cls");
        cout << "==================================\n";
        cout << "Room Management\n";
        cout << "==================================\n\n";
        cout << "1. View All Room Details\n";
        cout << "2. View Available Room\n";
        cout << "3. Edit Room Status\n";
        cout << "4. Search Room\n";
        cout << "5. Exit\n\n";

        cout << "Enter your choice: ";
        choice = getMenuChoice(1, 5);

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
            viewRoomDetails();
            break;
        case 2:
            viewAvailableRoom();
            break;
        case 3:
            editRoomStatus();
            break;
        case 4:
            searchRoom();
            break;
        case 5:
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