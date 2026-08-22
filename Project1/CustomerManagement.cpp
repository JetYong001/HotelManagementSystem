#include <iostream>
#include <iomanip>
#include "struct.h"
#include "Global.h"

using namespace std;

string capitalizeName(string name) {
    bool newWord = true;
    for (size_t i = 0; i < name.length(); i++) {
        if (isspace(static_cast<unsigned char>(name[i]))) {
            newWord = true;
        }
        else if (newWord) {
            name[i] = static_cast<char>(toupper(static_cast<unsigned char>(name[i])));
            newWord = false;
        }
        else {
            name[i] = static_cast<char>(tolower(static_cast<unsigned char>(name[i])));
        }
    }
    return name;
}

bool isValidName(const string& name) {
    if (name.empty()) return false;

    bool hasLetter = false;
    for (char c : name) {
        if (!isalpha(static_cast<unsigned char>(c)) && !isspace(static_cast<unsigned char>(c))) {
            return false;
        }
        if (isalpha(static_cast<unsigned char>(c))) {
            hasLetter = true;
        }
    }
    return hasLetter;
}

bool isNumber(const string& input)
{
    for (char c : input)
    {
        if (!isdigit(c))
        {
            return false;
        }
    }

    return true;
}

bool checkDuplicateIC(const string& ic)
{
    for (int i = 0; i < MAX_CUSTOMER; i++)
    {
        if (!customers[i].customerID.empty())
        {
            if (customers[i].ic == ic)
            {
                return true;
            }
        }
    }

    return false;
}

bool checkDuplicatePhone(const string& phone)
{
    for (int i = 0; i < MAX_CUSTOMER; i++)
    {
        if (!customers[i].customerID.empty())
        {
            if (customers[i].phone == phone)
            {
                return true;
            }
        }
    }

    return false;
}

void generateCustomerID(Customer& c)
{
    string id = "C";

    if (customerIDCounter < 10) {
        id += "00";
    }
    else if (customerIDCounter < 100) {
        id += "0";
    }
    id += to_string(customerIDCounter);

    customerIDCounter++;

    c.customerID = id;
}

bool displayCustomerTable() {
    bool hasCustomers = false;
    for (int i = 0; i < MAX_CUSTOMER; i++) {
        if (!customers[i].customerID.empty()) {
            hasCustomers = true;
            break;
        }
    }

    if (!hasCustomers) {
        cout << "+------------------------------------+\n";
        cout << "| No customer records available!     |\n";
        cout << "+------------------------------------+\n\n";
        return false;
    }

    string tableBorder = "+------------+---------------------------+------------------+------------------+--------------+";

    cout << tableBorder << "\n";
    cout << "| " << left << setw(10) << "ID"
        << " | " << setw(25) << "Name"
        << " | " << setw(16) << "IC Number"
        << " | " << setw(16) << "Phone Number"
        << " | " << setw(12) << "Type"
        << " |\n";
    cout << tableBorder << "\n";

    for (int i = 0; i < MAX_CUSTOMER; i++) {
        if (!customers[i].customerID.empty()) {
            cout << "| " << left << setw(10) << customers[i].customerID
                << " | " << setw(25) << customers[i].name
                << " | " << setw(16) << customers[i].ic
                << " | " << setw(16) << customers[i].phone
                << " | " << setw(12) << customers[i].memberType
                << " |\n";
        }
    }
    cout << tableBorder << "\n\n";
    return true;
}


void searchCustomer()
{
    int choice;
    string search;

    while (true)
    {
        system("cls");
        cout << "==================================\n";
        cout << "Search Customer\n";
        cout << "==================================\n\n";

        cout << "1. Search by Customer ID\n";
        cout << "2. Search by IC\n";
        cout << "3. Search by Name\n";
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

        if (choice == 1) {
            search = toUpperString(search);
        }

        bool found = false;

        system("cls");
        cout << "======================================\n";
        cout << "Search Results\n";
        cout << "======================================\n\n";

        for (int i = 0; i < MAX_CUSTOMER; i++)
        {
            if (customers[i].customerID.empty())
            {
                continue;
            }

            bool match = false;

            if (choice == 1 && customers[i].customerID == search)
            {
                    match = true;
            }
            else if (choice == 2 && customers[i].ic == search)
            {
                    match = true;
            }
            else if (choice == 3)
            {
                string storedName = toLowerString(customers[i].name);
                string queryName = toLowerString(search);

                if (storedName.find(queryName) != string::npos)
                    match = true;
            }

            if (match)
            {
                found = true;

                cout << "Customer ID   : " << customers[i].customerID << "\n";
                cout << "Customer Name : " << customers[i].name << "\n";
                cout << "Customer IC   : " << customers[i].ic << "\n";
                cout << "Customer Phone: " << customers[i].phone << "\n";
                cout << "-------------------------------------\n\n";
            }
        }

        if (!found)
        {
            cout << "+-----------------------------+\n";
            cout << "| Customer not found!         |\n";
            cout << "+-----------------------------+\n\n";
        }

        system("pause");
    }
}


void editCustomer()
{
    string id, name, phone, ic;
    char confirm;

    while (true)
    {
        system("cls");
        cout << "=======================================\n";
        cout << "Edit Customer\n";
        cout << "=======================================\n\n";

        cout << "Enter customer ID (or x to go back): ";
        getline(cin >> ws, id);
        clearInputBuffer();

        if (id == "X" || id == "x") {
            return;
        }

        id = toUpperString(id);
        bool found = false;

        for (int i = 0; i < MAX_CUSTOMER; i++)
        {
            if (customers[i].customerID == id)
            {
                found = true;

                while (true)
                {
                    system("cls");
                    cout << "=======================================\n";
                    cout << "Current customer details\n";
                    cout << "=======================================\n";
                    cout << "Customer ID          : " << customers[i].customerID << "\n";
                    cout << "Customer Name        : " << customers[i].name << "\n";
                    cout << "Customer IC          : " << customers[i].ic << "\n";
                    cout << "Customer Phone Number: " << customers[i].phone << "\n\n";

                    cout << "Edit? (y/n): ";
                    if (!(cin >> confirm)) {
                        clearInputBuffer();
                        cout << "+-----------------------------+\n";
                        cout << "| Invalid input!              |\n";
                        cout << "+-----------------------------+\n";
                        system("pause");
                        continue;
                    }
                    clearInputBuffer();

                    if (confirm == 'n' || confirm == 'N')
                    {
                        break;
                    }
                    else if (confirm == 'y' || confirm == 'Y')
                    {
                        while (true)
                        {
                            system("cls");
                            cout << "=======================================\n";
                            cout << "Current customer details\n";
                            cout << "=======================================\n";
                            cout << "Customer ID          : " << customers[i].customerID << "\n";
                            cout << "Customer Name        : " << customers[i].name << "\n";
                            cout << "Customer IC          : " << customers[i].ic << "\n";
                            cout << "Customer Phone Number: " << customers[i].phone << "\n\n\n";

                            cout << "Enter new name        : ";
                            getline(cin >> ws, name);

                            if (!isValidName(name)) {
                                cout << endl;
                                cout << "+----------------------------------------------------------+\n";
                                cout << "| Invalid name! Name must contain letters and spaces only. |\n";
                                cout << "+----------------------------------------------------------+\n";
                                system("pause");
                                continue;
                            }
                            break;
                        }

                        while (true)
                        {
                            system("cls");
                            cout << "=======================================\n";
                            cout << "Current customer details\n";
                            cout << "=======================================\n";
                            cout << "Customer ID          : " << customers[i].customerID << "\n";
                            cout << "Customer Name        : " << customers[i].name << "\n";
                            cout << "Customer IC          : " << customers[i].ic << "\n";
                            cout << "Customer Phone Number: " << customers[i].phone << "\n\n\n";

                            cout << "Enter new name        : " << name << "\n";
                            cout << "Enter new IC          : ";
                            getline(cin >> ws, ic);

                            if (ic.length() != 12)
                            {
                                cout << endl;
                                cout << "+----------------------------+\n";
                                cout << "| IC must contain 12 digits! |\n";
                                cout << "+----------------------------+\n";
                                system("pause");
                                continue;
                            }

                            if (!isNumber(ic))
                            {
                                cout << endl;
                                cout << "+-------------------------------+\n";
                                cout << "| IC must contain numbers only! |\n";
                                cout << "+-------------------------------+\n";
                                system("pause");
                                continue;
                            }

                            if (checkDuplicateIC(ic) && ic != customers[i].ic)
                            {
                                cout << endl;
                                cout << "+--------------------+\n";
                                cout << "| IC already exists! |\n";
                                cout << "+--------------------+\n";
                                system("pause");
                                continue;
                            }

                            break;
                        }

                        while (true)
                        {
                            system("cls");
                            cout << "=======================================\n";
                            cout << "Current customer details\n";
                            cout << "=======================================\n";
                            cout << "Customer ID          : " << customers[i].customerID << "\n";
                            cout << "Customer Name        : " << customers[i].name << "\n";
                            cout << "Customer IC          : " << customers[i].ic << "\n";
                            cout << "Customer Phone Number: " << customers[i].phone << "\n\n\n";

                            cout << "Enter new name        : " << name << "\n";
                            cout << "Enter new IC          : " << ic << "\n";
                            cout << "Enter new phone number: ";
                            getline(cin >> ws, phone);

                            if (!isNumber(phone))
                            {
                                cout << endl;
                                cout << "+-----------------------------------------+\n";
                                cout << "| Phone number must contain numbers only! |\n";
                                cout << "+-----------------------------------------+\n";
                                system("pause");
                                continue;
                            }

                            if (phone.length() != 10 && phone.length() != 11)
                            {
                                cout << endl;
                                cout << "+-------------------------------------+\n";
                                cout << "| Phone must contain 10 or 11 digits! |\n";
                                cout << "+-------------------------------------+\n";
                                system("pause");
                                continue;
                            }

                            if (checkDuplicatePhone(phone) && phone != customers[i].phone)
                            {
                                cout << endl;
                                cout << "+------------------------------+\n";
                                cout << "| Phone number already exists! |\n";
                                cout << "+------------------------------+\n";
                                system("pause");
                                continue;
                            }

                            break;
                        }

                        system("cls");
                        cout << "=======================================\n";
                        cout << "Updated customer details preview\n";
                        cout << "=======================================\n";
                        cout << "Customer ID          : " << customers[i].customerID << "\n";
                        cout << "Customer Name        : " << capitalizeName(name) << "\n";
                        cout << "Customer IC          : " << ic << "\n";
                        cout << "Customer Phone Number: " << phone << "\n\n";

                        cout << "Confirm update? (y/n): ";
                        if (!(cin >> confirm)) {
                            clearInputBuffer();
                            cout << "+-----------------------------+\n";
                            cout << "| Invalid input!              |\n";
                            cout << "+-----------------------------+\n";
                            system("pause");
                            break;
                        }
                        clearInputBuffer();

                        if (confirm == 'y' || confirm == 'Y')
                        {
                            customers[i].name = capitalizeName(name);
                            customers[i].ic = ic;
                            customers[i].phone = phone;

                            system("cls");
                            cout << "+--------------------------------+\n";
                            cout << "| Customer updated successfully! |\n";
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
                        break;
                    }
                    else
                    {
                        cout << "+-----------------------------+\n";
                        cout << "| Invalid input!              |\n";
                        cout << "+-----------------------------+\n";
                        system("pause");
                    }
                }
                break;
            }
        }

        if (!found)
        {
            system("cls");
            cout << "+-----------------------------+\n";
            cout << "| Customer not found!         |\n";
            cout << "+-----------------------------+\n";
            system("pause");
        }
    }
}


void deleteCustomer()
{
    string id;
    char choice;


    system("cls");

    cout << "==================================\n";
    cout << "Delete Customer\n";
    cout << "==================================\n\n";

    displayCustomerTable();

    cout << "Enter customer ID: ";
    cin >> id;
    clearInputBuffer();
    id = toUpperString(id);


    for (int i = 0; i < MAX_CUSTOMER; i++)
    {

        if (customers[i].customerID == id)
        {
            while(true)
            {
                system("cls");
                cout << "=======================================\n";
                cout << "Selected customer details\n";
                cout << "=======================================\n";
                cout << "Customer ID          : " << customers[i].customerID << "\n";
                cout << "Customer Name        : " << customers[i].name << "\n";
                cout << "Customer IC          : " << customers[i].ic << "\n";
                cout << "Customer Phone Number: " << customers[i].phone << "\n";
                cout << "Customer Member Type : " << customers[i].memberType << "\n\n";

                cout << "Confirm delete this customer (y/n): ";
                if (!(cin >> choice)) {
                    clearInputBuffer();
                    system("cls");
                    cout << "+--------------------------------+\n";
                    cout << "| Invalid input!                 |\n";
                    cout << "+--------------------------------+\n";
                    system("pause");
                    continue;
                }
                clearInputBuffer();


                if (choice == 'y' || choice == 'Y')
                {


                    for (int j = i; j < customerCount - 1; j++)
                    {
                        customers[j] = customers[j + 1];
                    }


                    customers[customerCount - 1].customerID = "";
                    customers[customerCount - 1].name = "";
                    customers[customerCount - 1].ic = "";
                    customers[customerCount - 1].phone = "";
                    customers[customerCount - 1].memberType = "";
                    customers[customerCount - 1].totalSpent = 0.0;

                    customerCount--;


                    system("cls");
                    cout << "+--------------------------------+\n";
                    cout << "| Customer deleted successfully! |\n";
                    cout << "+--------------------------------+\n";
                    system("pause");

                    return;
                }


                else if (choice == 'n' || choice == 'N')
                {
                    system("cls");
                    cout << "+-----------------------------+\n";
                    cout << "| Delete cancelled!           |\n";
                    cout << "+-----------------------------+\n";
                    system("pause");

                    return;
                }


                else
                {
                    system("cls");
                    cout << "+-----------------------------+\n";
                    cout << "| Invalid input!              |\n";
                    cout << "+-----------------------------+\n";
                    system("pause");
                }
            }
        }
    }

    system("cls");
    cout << "+-----------------------------+\n";
    cout << "| Customer not found!         |\n";
    cout << "+-----------------------------+\n";
    system("pause");
}


void displayAllCustomer() {
    system("cls");
    cout << "===============================================================================================\n";
    cout << "                                        Customers List\n";
    cout << "===============================================================================================\n\n";

    displayCustomerTable();

    system("pause");
}


void addCustomer() {

    Customer c;
    c.memberType = "Regular";
    char choice;

    while(true)
    {
        system("cls");
        cout << "==================================\n";
        cout << "Add Customer\n";
        cout << "==================================\n\n";

        cout << "Enter customer name: ";
        getline(cin >> ws, c.name);


        if (!isValidName(c.name)) {
            cout << endl;
            cout << "+----------------------------------------------------------+\n";
            cout << "| Invalid name! Name must contain letters and spaces only. |\n";
            cout << "+----------------------------------------------------------+\n";
            system("pause");
            continue;
        }

        break;
    }

    while (true)
    {
        system("cls");
        cout << "==================================\n";
        cout << "Add Customer\n";
        cout << "==================================\n\n";

        cout << "Enter customer name: " << c.name << "\n";
        cout << "Enter customer ic: ";
        getline(cin >> ws, c.ic);


        if (c.ic.length() != 12)
        {
            cout << endl;
            cout << "+----------------------------+\n";
            cout << "| IC must contain 12 digits! |\n";
            cout << "+----------------------------+\n";
            system("pause");
            continue;
        }


        if (!isNumber(c.ic))
        {
            cout << endl;
            cout << "+-------------------------------+\n";
            cout << "| IC must contain numbers only! |\n";
            cout << "+-------------------------------+\n";
            system("pause");
            continue;
        }


        if (checkDuplicateIC(c.ic))
        {
            cout << endl;
            cout << "+--------------------+\n";
            cout << "| IC already exists! |\n";
            cout << "+--------------------+\n";
            system("pause");
            continue;
        }

        break;
    }

    while (true)
    {
        system("cls");
        cout << "==================================\n";
        cout << "Add Customer\n";
        cout << "==================================\n\n";

        cout << "Enter customer name: " << c.name << "\n";
        cout << "Enter customer ic: " << c.ic << "\n";
        cout << "Enter customer phone number: ";
        getline(cin >> ws, c.phone);


        if (c.phone.length() != 10 && c.phone.length() != 11)
        {
            cout << endl;
            cout << "+-------------------------------------+\n";
            cout << "| Phone must contain 10 or 11 digits! |\n";
            cout << "+-------------------------------------+\n";
            system("pause");
            continue;
        }


        if (!isNumber(c.phone))
        {
            cout << endl;
            cout << "+-----------------------------------------+\n";
            cout << "| Phone number must contain numbers only! |\n";
            cout << "+-----------------------------------------+\n";
            system("pause");
            continue;
        }


        if (checkDuplicatePhone(c.phone))
        {
            cout << endl;
            cout << "+------------------------------+\n";
            cout << "| Phone number already exists! |\n";
            cout << "+------------------------------+\n";
            system("pause");
            continue;
        }

        break;
    }

    c.name = capitalizeName(c.name);

    for (int i = 0; i < MAX_CUSTOMER; i++) {

        if (customers[i].customerID.empty()) {

            while (true) {
                string previewID = "C";
                if (customerIDCounter < 10) {
                    previewID += "00";
                }
                else if (customerIDCounter < 100) {
                    previewID += "0";
                }
                previewID += to_string(customerIDCounter);

                system("cls");
                cout << "=======================================\n";
                cout << "Customer details\n";
                cout << "=======================================\n";
                cout << "Customer ID          : " << previewID << "\n";
                cout << "Customer Name        : " << c.name << "\n";
                cout << "Customer IC          : " << c.ic << "\n";
                cout << "Customer Phone Number: " << c.phone << "\n";
                cout << "Customer Member Type : " << c.memberType << "\n\n";

                cout << "Confirm that customer info correct (y/n): ";
                if (!(cin >> choice)) {
                    clearInputBuffer();
                    cout << "+--------------------------------+\n";
                    cout << "| Invalid choice!                |\n";
                    cout << "+--------------------------------+\n";
                    system("pause");
                    continue;
                }
                clearInputBuffer();

                if (choice == 'y' || choice == 'Y'){

                    generateCustomerID(c);

                    customers[i] = c;
                    customerCount++;

                    system("cls");
                    cout << "+------------------------------+\n";
                    cout << "| Customer added successfully! |\n";
                    cout << "+------------------------------+\n";
                    system("pause");

                    return;

                }
                else if (choice == 'n' || choice == 'N') {

                    system("cls");
                    cout << "+---------------------------------+\n";
                    cout << "| Customer information cancelled! |\n";
                    cout << "+---------------------------------+\n";
                    system("pause");

                    return;
                }
                else {
                    system("cls");
                    cout << "+--------------------------------+\n";
                    cout << "| Invalid input!                 |\n";
                    cout << "+--------------------------------+\n";
                    system("pause");
                    continue;
                }

                system("pause");
                return;
            }
        }
    }

    cout << "+-----------------+\n";
    cout << "| No empty slot!  |\n";
    cout << "+-----------------+\n";
}




void customerManagement() {

    int choice;

    while (true) {
        system("cls");
        cout << "==================================\n";
        cout << "Customer Management\n";
        cout << "==================================\n\n";
        cout << "1. Add Customer\n";
        cout << "2. Delete Customer\n";
        cout << "3. Display All Customer\n";
        cout << "4. Edit Customer\n";
        cout << "5. Search Customer\n";
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
            addCustomer();
            break;
        case 2:
            deleteCustomer();
            break;
        case 3:
            displayAllCustomer();
            break;
        case 4:
            editCustomer();
            break;
        case 5:
            searchCustomer();
            break;
        case 6:
            system("cls");
            return;
        default:
            system("cls");
            cout << "+--------------------------------------+\n";
            cout << "| Invalid choice!                      |\n";
            cout << "+--------------------------------------+\n";
            system("pause");
        }
    }
}