#include <iostream>
#include <iomanip>
#include "struct.h"
#include "Global.h"

using namespace std;

void searchRoom()
{
    int choice;
    string search;
    string status;


    while (true)
    {
        system("cls");

        cout << "==================================\n";
        cout << "Search Room\n";
        cout << "==================================\n";


        cout << "\n1. Search ";
        cout << "\n2. Exit ";
        cout << "\nEnter your choice: ";
        cin >> choice;

        if (choice == 2) {
            return;
        }
        else if (choice != 1) {
            system("cls");
            cout << "+--------------------------------------+\n";
            cout << "Invalid choice!\n";
            cout << "+--------------------------------------+\n";
            system("pause");
            continue;

        }
        

        system("cls");

        cout << "==================================\n";
        cout << "Search Room\n";
        cout << "==================================\n\n";
        
        cout << "Enter room ID: ";
        cin >> search;





        for (int i = 0; i < MAX_ROOM; i++)
        {

            if (rooms[i].roomID.empty())
            {
                continue;
            }


            if (rooms[i].roomID == search)
            {

                cout << "\nRoom Found!\n";
                cout << "----------------------------------\n";
                cout << "Room ID: " << rooms[i].roomID << "\n";
                cout << "Room Type: " << rooms[i].roomType << "\n";
                cout << "Room Price: RM " << fixed << setprecision(2) << rooms[i].price << "\n";
                cout << "Room Status: " << (rooms[i].available ? "Available" : "Occupied");
                cout << "\n";
                cout << "----------------------------------\n";

                system("pause");
                break;
            }
            else {
                system("cls");

                cout << "+-----------------------------+\n";
                cout << "Room not found!\n";
                cout << "+-----------------------------+\n";


                system("pause");
                break;
            
            }
        }
    }
    system("pause");
}

void editRoomStatus()
{
    string id;
    int choice;
    char confirm;


    system("cls");
    
    cout << "==================================\n";
    cout << "Edit Room Status\n";
    cout << "==================================\n\n";
    
    
    cout << "Enter Room ID: ";
    cin >> id;
    
    
    for (int i = 0; i < MAX_ROOM; i++)
    {
        if (rooms[i].roomID == id)
        {
    
            while (true)
            {
                system("cls");
    
    
                cout << "Current Room Status\n";
                cout << "----------------------------------\n\n";
                cout << "<Room " << rooms[i].roomID << ">\n";
    
                if (rooms[i].available) {
                    cout << "Current status: Available\n\n";
                    cout << "\nConfirm update to Occupied? (y/n): ";
                    cin >> confirm;
                }
                else {
                    cout << "Current status: Occupied\n\n";
                    cout << "\nConfirm update to Available? (y/n): ";
                    cin >> confirm;
                }
    
                
                if (confirm == 'y' || confirm == 'Y')
                {
                    rooms[i].available = false;
                    system("cls");
    
                    cout << "+--------------------------------+\n";
                    cout << "Room Status updated successfully! \n";
                    cout << "+--------------------------------+\n";
    
                    system("pause");
                    return;
                }
    
                else
                {
                    system("cls");
    
                    cout << "+--------------------------------+\n";
                    cout << "Update cancelled! \n";
                    cout << "+--------------------------------+\n";
                   
                    system("pause");
                    return;
                }
            }
        }
    }
    


    system("cls");

    cout << "+--------------------------------+\n";
    cout << "Room not found!\n";
    cout << "+--------------------------------+\n";

    system("pause");
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
        cin >> choice;


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

            cout << "+-----------------------------+\n";
            cout << "Invalid choice!\n";
            cout << "+-----------------------------+\n";


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
            cout << "|              No room found                 |\n";
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
        cin >> choice;


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

            cout << "+-----------------------------+\n";
            cout << "Invalid choice!\n";
            cout << "+-----------------------------+\n";


            system("pause");

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
            cout << "|              No room found                 |\n";
        }


        cout << "+----------------+-----------------+---------------+\n\n";

        cout << "===================================================\n";
        cout << "Total Available = " << available << "\n";
        cout << "Total Occupied = " << occupied << "\n";
        cout << "===================================================\n";


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
        cin >> choice;
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

            cout << "+-----------------------------+\n";
            cout << "Invalid choice!\n";
            cout << "+-----------------------------+\n";


            system("pause");
        }

    }

}