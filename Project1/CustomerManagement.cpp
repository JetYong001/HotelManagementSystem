#include <iostream>
#include "struct.h"
#include "Global.h"

using namespace std;



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
        cin >> choice;


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
        cin >> search;


        bool found = false;


        for (int i = 0; i < MAX_CUSTOMER; i++)
        {
            if (customers[i].customerID.empty())
            {
                continue;
            }


            if ((choice == 1 && customers[i].customerID == search) ||
                (choice == 2 && customers[i].ic == search) ||
                (choice == 3 && customers[i].name == search))
            {
                found = true;


                cout << "\nCustomer Found!\n";
                cout << "----------------------------------\n";
                cout << "Customer ID: " << customers[i].customerID << "\n";
                cout << "Customer Name: " << customers[i].name << "\n";
                cout << "Customer IC: " << customers[i].ic << "\n";
                cout << "Customer Phone: " << customers[i].phone << "\n";
                cout << "----------------------------------\n";

                break;
            }
        }


        if (!found)
        {
            cout << "\n+-----------------------------+\n";
            cout << "Customer not found!\n";
            cout << "+-----------------------------+\n";
        }


        system("pause");
    }
}







void editCustomer()
{
    string id;
    int choice;
    char confirm;


    system("cls");

    cout << "==================================\n";
    cout << "Edit Customer\n";
    cout << "==================================\n\n";


    cout << "Enter customer ID: ";
    cin >> id;


    for (int i = 0; i < MAX_CUSTOMER; i++)
    {
        if (customers[i].customerID == id)
        {

            while (true)
            {
                system("cls");

                cout << "Current Customer Details\n";
                cout << "----------------------------------\n";
                cout << "Customer ID: " << customers[i].customerID << "\n";
                cout << "Customer Name: " << customers[i].name << "\n";
                cout << "Customer IC: " << customers[i].ic << "\n";
                cout << "Customer Phone: " << customers[i].phone << "\n";


                cout << "\n==================================\n";
                cout << "Edit Option\n";
                cout << "==================================\n";
                cout << "1. Edit Name\n";
                cout << "2. Edit IC\n";
                cout << "3. Edit Phone\n";
                cout << "4. Edit All\n";
                cout << "5. Back\n\n";


                cout << "Enter choice: ";
                cin >> choice;


                if (choice == 1)
                {
                    cout << "Enter new name: ";
                    cin >> customers[i].name;
                }


                else if (choice == 2)
                {
                    while (true)
                    {
                        cout << "Enter new IC: ";
                        cin >> customers[i].ic;


                        if (customers[i].ic.length() != 12)
                        {
                            cout << "IC must contain 12 digits!\n";
                            continue;
                        }

                        break;
                    }
                }


                else if (choice == 3)
                {
                    while (true)
                    {
                        cout << "Enter new phone: ";
                        cin >> customers[i].phone;


                        if (customers[i].phone.length() != 10)
                        {
                            cout << "Phone must contain 10 digits!\n";
                            continue;
                        }

                        break;
                    }
                }


                else if (choice == 4)
                {
                    cout << "Enter new name: ";
                    cin >> customers[i].name;


                    while (true)
                    {
                        cout << "Enter new IC: ";
                        cin >> customers[i].ic;

                        if (customers[i].ic.length() != 12)
                        {
                            cout << "IC must contain 12 digits!\n";
                            continue;
                        }

                        break;
                    }


                    while (true)
                    {
                        cout << "Enter new phone: ";
                        cin >> customers[i].phone;

                        if (customers[i].phone.length() != 10)
                        {
                            cout << "Phone must contain 10 digits!\n";
                            continue;
                        }

                        break;
                    }
                }


                else if (choice == 5)
                {
                    return;
                }


                else
                {
                    cout << "Invalid choice!\n";
                    system("pause");
                    continue;
                }



                cout << "\nConfirm update? (y/n): ";
                cin >> confirm;


                if (confirm == 'y' || confirm == 'Y')
                {
                    system("cls");

                    cout << "+-----------------------------+\n";
                    cout << "Customer updated successfully!\n";
                    cout << "+-----------------------------+\n";

                    system("pause");
                    return;
                }

                else
                {
                    system("cls");

                    cout << "+-----------------------------+\n";
                    cout << "Update cancelled!\n";
                    cout << "+-----------------------------+\n";
                    
                    system("pause");
                    return;
                }
            }
        }
    }


    system("cls");

    cout << "+-----------------------------+\n";
    cout << "Customer not found!\n";
    cout << "+-----------------------------+\n";

    system("pause");
}



void deleteCustomer()
{
    string id;
    char choice;


    system("cls");

    cout << "==================================\n";
    cout << "Delete Customer\n";
    cout << "==================================\n\n";


    cout << "Enter customer ID: ";
    cin >> id;


    for (int i = 0; i < MAX_CUSTOMER; i++)
    {

        if (customers[i].customerID == id)
        {

            cout << "\nCustomer Details\n";
            cout << "----------------------------------\n";
            cout << "Customer ID: " << customers[i].customerID << "\n";
            cout << "Customer Name: " << customers[i].name << "\n";
            cout << "Customer IC: " << customers[i].ic << "\n";
            cout << "Customer Phone: " << customers[i].phone << "\n";
            cout << "Customer Member Type: " << customers[i].memberType << "\n";



            cout << "\nConfirm delete this customer (y/n): ";
            cin >> choice;


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

                cout << "+-----------------------------+\n";
                cout << "Customer deleted successfully!\n";
                cout << "+-----------------------------+\n";

                system("pause");

                return;
            }


            else if (choice == 'n' || choice == 'N')
            {

                system("cls");

                cout << "+-----------------------------+\n";
                cout << "Delete canceled!\n";
                cout << "+-----------------------------+\n";

                system("pause");

                return;
            }


            else
            {
                system("cls");
                cout << "+-----------------------------+\n";
                cout << "Invalid input!\n";
                cout << "+-----------------------------+\n";
               
                system("pause");
                return;
            }
        }
    }

    system("cls");
    cout << "+-----------------------------+\n";
    cout << "Customer not found!\n";
    cout << "+-----------------------------+\n";

    system("pause");
}


void displayAllCustomer() {

    system("cls");

    cout << "==================================\n";
    cout << "Display All Customer\n";
    cout << "==================================\n\n";


    bool found = false;


    for (int i = 0; i < MAX_CUSTOMER; i++) {

        if (!customers[i].customerID.empty()) {

            found = true;

            cout << "Customer " << i + 1 << "\n";
            cout << "----------------------------------\n";
            cout << "Customer ID: " << customers[i].customerID << "\n";
            cout << "Customer Name: " << customers[i].name << "\n";
            cout << "Customer IC: " << customers[i].ic << "\n";
            cout << "Customer Phone Number: " << customers[i].phone << "\n";
            cout << "\n";
        }
    }


    if (!found) {

        system("cls");
        cout << "+-----------------------------+\n";
        cout << "No customer record found!\n";
        cout << "+-----------------------------+\n";

    }


    system("pause");
}


bool isNumber(const string &input)
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

bool checkDuplicateIC(const string &ic)
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

void generateCustomerID(Customer &c)
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


void addCustomer() {

    Customer c;
    c.memberType = "Regular";
    char choice;

    system("cls");
    cout << "==================================\n";
    cout << "Add Customer\n";
    cout << "==================================\n\n";

    cout << "Enter customer name: ";
    cin >> c.name;
    while (true)
    {
        cout << "Enter customer ic: ";
        cin >> c.ic;


        if (c.ic.length() != 12)
        {
            cout << "IC must contain 12 digits!\n";
            continue;
        }


        if (checkDuplicateIC(c.ic))
        {
            cout << "IC already exists!\n";
            continue;
        }


        break;
    }

    while (true)
    {
        cout << "Enter customer phone number: ";
        cin >> c.phone;


        if (c.phone.length() != 10)
        {
            cout << "Phone number must contain 10 digits!\n";
            continue;
        }


        if (!isNumber(c.phone))
        {
            cout << "Phone number must contain numbers only!\n";
            continue;
        }

        if (checkDuplicatePhone(c.phone))
        {
            cout << "Phone Number already exists!\n";
            continue;
        }


        break;
    }


    for (int i = 0; i < MAX_CUSTOMER; i++) {

        if (customers[i].customerID.empty()) {

            generateCustomerID(c);

            while (true) {
                cout << "\n";

                cout << "==================================\n";
                cout << "Customer details\n";
                cout << "==================================\n";
                cout << "Customer ID: " << c.customerID << "\n";
                cout << "Customer Name: " << c.name << "\n";
                cout << "Customer IC: " << c.ic << "\n";
                cout << "Customer Phone Number: " << c.phone << "\n";
                cout << "Customer Member Type: " << c.memberType << "\n";

                cout << "Comfirm that customer info correct (y/n): ";
                cin >> choice;

                if (choice == 'y' || choice == 'Y'){

                    system("cls");

                    customers[i] = c;
                    customerCount++;

                    cout << "+-----------------------------+\n";
                    cout << "Customer added successfully!\n";
                    cout << "+-----------------------------+\n";

                    system("pause");

                    return;

                }
                else if (choice == 'n' || choice == 'N') {

                    system("cls");

                    cout << "+--------------------------------+\n";
                    cout << "Customer information cancelled!\n";
                    cout << "+--------------------------------+\n";

                    system("pause");

                    return;
                }
                else {
                    system("cls");

                    cout << "+--------------------------------+\n";
                    cout << "Invalid input\n";
                    cout << "+--------------------------------+\n";

                    system("pause");
                    system("cls");
                    continue;
                }


                system("pause");
                return;
            }
        }
    }

    cout << "No empty slot!\n";
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
        cin >> choice;
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
            cout << "Invalid choice!\n";
            cout << "+--------------------------------------+\n";
            system("pause");
        }

    }

}