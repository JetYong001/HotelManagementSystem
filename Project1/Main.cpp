#include <iostream>


using namespace std;

void customerManagement();
void priceManagement();
void roomManagement();
void roomBooking();
void initializeRooms();

int main(){

	int choice;
	initializeRooms();

	while (true) {
		system("cls");
		cout << "==================================\n";
		cout << "HOTEL RESERVATION SYSTEM\n";
		cout << "==================================\n\n";

		cout << "1. Customer Management\n";
		cout << "2. Room Management\n";
		cout << "3. Price Management\n";
		cout << "4. Room Booking\n";
		cout << "5. Exit\n\n";

		cout << "Enter your choice: ";
		cin >> choice;
		switch (choice) {
		case 1:
			customerManagement();
			break;
		case 2:
			roomManagement();
			break;
		case 3:
			priceManagement();
			break;
		case 4:
			roomBooking();
			break;
		case 5:
			return 0;
		default:
			system("cls");
			cout << "+-----------------------------+\n";
			cout << "Invalid choice!\n";
			cout << "+-----------------------------+\n";

			system("pause");
		}
	}
}