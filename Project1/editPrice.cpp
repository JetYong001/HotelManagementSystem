#include <iostream>
#include <iomanip>
#include "struct.h"
#include "Global.h"

using namespace std;

void displayRoomPriceTable() {
    cout << "+-------------------+--------------+\n";
    cout << "| Room Type         | Price (RM)   |\n";
    cout << "+-------------------+--------------+\n";
    cout << "| Single Room       | RM " << setw(9) << fixed << setprecision(2) << singlePrice << " |\n";
    cout << "| Double Room       | RM " << setw(9) << fixed << setprecision(2) << doublePrice << " |\n";
    cout << "| Deluxe Room       | RM " << setw(9) << fixed << setprecision(2) << deluxePrice << " |\n";
    cout << "+-------------------+--------------+\n";
}

void displayDiscountTable() {
    cout << "+-------------------+--------------+\n";
    cout << "| Membership Type   |  Discount %  |\n";
    cout << "+-------------------+--------------+\n";
    cout << "| VIP               | " << setw(10) << fixed << setprecision(2) << (vipDiscount * 100) << " % |\n";
    cout << "| Premium           | " << setw(10) << fixed << setprecision(2) << (premiumDiscount * 100) << " % |\n";
    cout << "| Regular           | " << setw(10) << fixed << setprecision(2) << (regularDiscount * 100) << " % |\n";
    cout << "+-------------------+--------------+\n";
}


void viewRoomPrice() {
    system("cls");
    cout << "====================================\n";
    cout << "View Room Price\n";
    cout << "====================================\n\n";

    displayRoomPriceTable();
    cout << "\n";

    system("pause");
}


void viewDiscount() {
    system("cls");
    cout << "====================================\n";
    cout << "View Discount\n";
    cout << "====================================\n\n";

    displayDiscountTable();
    cout << "\n";

    system("pause");
}


void editDiscount()
{
    int choice;
    double currentDiscount, newDiscount;
    string memberType;
    char confirm;

    while (true) {
        system("cls");
        cout << "==================================\n";
        cout << "Edit Discount\n";
        cout << "==================================\n\n";
        cout << "1. VIP Discount\n";
        cout << "2. Premium Discount\n";
        cout << "3. Regular Discount\n";
        cout << "4. Exit\n\n";

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
            currentDiscount = vipDiscount;
            memberType = "VIP";
            break;
        case 2:
            currentDiscount = premiumDiscount;
            memberType = "Premium";
            break;
        case 3:
            currentDiscount = regularDiscount;
            memberType = "Regular";
            break;
        case 4:
            return;
        default:
            cout << "+--------------------------------+\n";
            cout << "| Invalid choice!                |\n";
            cout << "+--------------------------------+\n";
            system("pause");
            continue;
        }

        while (true) {
            system("cls");
            cout << "==================================\n";
            cout << "Edit Discount (" << memberType << ")\n";
            cout << "==================================\n\n";
            cout << "Current Discount: " << fixed << setprecision(2) << (currentDiscount * 100) << " %\n\n";

            cout << "Enter new discount (e.g., 10 for 10%): ";
            if (!(cin >> newDiscount)) {
                clearInputBuffer();
                system("cls");
                cout << "+--------------------------------+\n";
                cout << "| Invalid input!                 |\n";
                cout << "+--------------------------------+\n";
                system("pause");
                continue;
            }
            clearInputBuffer();

            if (newDiscount < 0 || newDiscount > 100) {
                system("cls");
                cout << "+---------------------------------+\n";
                cout << "| Discount must be between 0-100! |\n";
                cout << "+---------------------------------+\n";
                system("pause");
                continue;
            }

            break;
        }

        cout << "\nChange discount from " << (currentDiscount * 100) << "% to " << newDiscount << "% ?\n";
        cout << "Confirm (y/n): ";
        if (!(cin >> confirm)) {
            clearInputBuffer();
            system("cls");
            cout << "+--------------------------------+\n";
            cout << "| Invalid choice!                |\n";
            cout << "+--------------------------------+\n";
            system("pause");
            continue;
        }
        clearInputBuffer();

        if (confirm == 'y' || confirm == 'Y')
        {
            if (memberType == "VIP") {
                vipDiscount = newDiscount / 100.0;
            }
            else if (memberType == "Premium") {
                premiumDiscount = newDiscount / 100.0;
            }
            else if (memberType == "Regular") {
                regularDiscount = newDiscount / 100.0;
            }

            system("cls");
            cout << "+--------------------------------+\n";
            cout << "| Discount updated successfully! |\n";
            cout << "+--------------------------------+\n";
            system("pause");
        }
        else
        {
            system("cls");
            cout << "+-----------------------------+\n";
            cout << "| Update cancelled!           |\n";
            cout << "+-----------------------------+\n";
            system("pause");
        }
    }
}


void editRoomPrice()
{
    int choice;
    string roomType;
    double currentPrice = 0;
    double newPrice;
    char confirm;

    while (true) {
        system("cls");
        cout << "==================================\n";
        cout << "Edit Room Price\n";
        cout << "==================================\n\n";

        cout << "1. Edit Single Room\n";
        cout << "2. Edit Double Room\n";
        cout << "3. Edit Deluxe Room\n";
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
            roomType = "Single";
            currentPrice = singlePrice;
            break;
        case 2:
            roomType = "Double";
            currentPrice = doublePrice;
            break;
        case 3:
            roomType = "Deluxe";
            currentPrice = deluxePrice;
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

        while (true) {
            system("cls");
            cout << "==================================\n";
            cout << "Edit " << roomType << " Room Price\n";
            cout << "==================================\n\n";

            cout << "Current Price: RM " << fixed << setprecision(2) << currentPrice << "\n\n";

            cout << "Enter new price (RM): ";
            if (!(cin >> newPrice)) {
                clearInputBuffer();
                system("cls");
                cout << "+--------------------------------+\n";
                cout << "| Invalid input!                 |\n";
                cout << "+--------------------------------+\n";
                system("pause");
                continue;
            }
            clearInputBuffer();

            if (newPrice < 0) {
                system("cls");
                cout << "+--------------------------------+\n";
                cout << "| Price cannot be negative!      |\n";
                cout << "+--------------------------------+\n";
                system("pause");
                continue;
            }

            break;
        }

        cout << "\nChange price from RM "<< currentPrice << " to RM " << newPrice << "?\n";

        cout << "Confirm (y/n): ";
        if (!(cin >> confirm)) {
            clearInputBuffer();
            system("cls");
            cout << "+--------------------------------+\n";
            cout << "| Invalid choice!                |\n";
            cout << "+--------------------------------+\n";
            system("pause");
            continue;
        }
        clearInputBuffer();

        if (confirm == 'y' || confirm == 'Y')
        {
            for (int i = 0; i < MAX_ROOM; i++)
            {
                if (rooms[i].roomType == roomType)
                {
                    rooms[i].price = newPrice;
                }
            }

            if (roomType == "Single") {
                singlePrice = newPrice;
            }
            else if (roomType == "Double") {
                doublePrice = newPrice;
            }
            else if (roomType == "Deluxe") {
                deluxePrice = newPrice;
            }

            system("cls");
            cout << "+-----------------------------+\n";
            cout << "| Price updated successfully! |\n";
            cout << "+-----------------------------+\n";
            system("pause");

        }
        else
        {
            system("cls");
            cout << "+-----------------------------+\n";
            cout << "| Update cancelled!           |\n";
            cout << "+-----------------------------+\n";
            system("pause");
        }
    }
}


void priceManagement() {
    int choice;

    while (true) {
        system("cls");
        cout << "==================================\n";
        cout << "Edit Price\n";
        cout << "==================================\n\n";
        cout << "1. Edit room price\n";
        cout << "2. Edit discount\n";
        cout << "3. Display room price\n";
        cout << "4. Display discount\n";
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
            editRoomPrice();
            break;
        case 2:
            editDiscount();
            break;
        case 3:
            viewRoomPrice();
            break;
        case 4:
            viewDiscount();
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