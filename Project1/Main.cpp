#include <iostream>
#include "Global.h"


using namespace std;

void customerManagement();
void priceManagement();
void roomManagement();
void roomBooking();
void initializeRooms();
void reporting();

static void showWelcomePage() {
	system("cls");
	cout << "+==========================================================================================+\n";
	cout << "||                                                                                        ||\n";
	cout << "||	 $$$$$$\\ $$\\   $$\\$$$$$$$\\ $$$$$$$$\\$$$$$$$\\        $$$$$$$\\ $$$$$$$$\\$$$$$$$$\\   ||\n";
	cout << "||	$$  __$$\\$$ |  $$ $$  __$$\\$$  _____$$  __$$\\       $$  __$$\\$$  _____$$  _____|  ||\n";
	cout << "||	$$ /  \\__$$ |  $$ $$ |  $$ $$ |     $$ |  $$ |      $$ |  $$ $$ |     $$ |        ||\n";
	cout << "||	\\$$$$$$\\ $$ |  $$ $$$$$$$  $$$$$\\   $$$$$$$  |      $$$$$$$\\ $$$$$\\   $$$$$\\      ||\n";
	cout << "||       \\____$$\\$$ |  $$ $$  ____/$$  __|  $$  __$$<       $$  __$$\\$$  __|  $$  __|     ||\n";
	cout << "||      $$\\   $$ $$ |  $$ $$ |     $$ |     $$ |  $$ |      $$ |  $$ $$ |     $$ |        ||\n";
	cout << "||      \\$$$$$$  \\$$$$$$  $$ |     $$$$$$$$\\$$ |  $$ |      $$$$$$$  $$$$$$$$\\$$$$$$$$\\   ||\n";
	cout << "||       \\______/ \\______/\\__|     \\________\\__|  \\__|      \\_______/\\________\\________|  ||\n";
	cout << "||                        $$\\   $$\\ $$$$$$\\$$$$$$$$\\$$$$$$$$\\$$\\                          ||\n";
	cout << "||                        $$ |  $$ $$  __$$\\__$$  __$$  _____$$ |                         ||\n";
	cout << "||                        $$ |  $$ $$ /  $$ | $$ |  $$ |     $$ |                         ||\n";
	cout << "||                        $$$$$$$$ $$ |  $$ | $$ |  $$$$$\\   $$ |                         ||\n";
	cout << "||                        $$  __$$ $$ |  $$ | $$ |  $$  __|  $$ |                         ||\n";
	cout << "||                        $$ |  $$ $$ |  $$ | $$ |  $$ |     $$ |                         ||\n";
	cout << "||                        $$ |  $$ |$$$$$$  | $$ |  $$$$$$$$\\$$$$$$$$\\                    ||\n";
	cout << "||                        \\__|  \\__|\\______/  \\__|  \\________\\________|                   ||\n";
	cout << "||                                                                                        ||\n";
	cout << "+==========================================================================================+\n";
	cout << "||                              Welcome to Super Bee Hotel                                ||\n";
	cout << "+==========================================================================================+\n" << endl;
	system("pause");
}
int main(){

	int choice;
	initializeRooms();
	showWelcomePage();

	while (true) {
		system("cls");
		cout << "==================================\n";
		cout << "HOTEL RESERVATION SYSTEM\n";
		cout << "==================================\n\n";

		cout << "1. Customer Management\n";
		cout << "2. Room Management\n";
		cout << "3. Price Management\n";
		cout << "4. Room Booking\n";
		cout << "5. Report\n";
		cout << "6. Exit\n\n";

		cout << "Enter your choice: ";
		int choice = getMenuChoice(1, 6);

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
			reporting();
			break;
		case 6:
			system("cls");
			cout << "+---------------------------------+\n";
			cout << "| Thank you for using the system! |\n";
			cout << "+---------------------------------+\n";
			return 0;
		default:
			system("cls");
			cout << "+-----------------------------+\n";
			cout << "| Invalid choice!             |\n";
			cout << "+-----------------------------+\n";
			system("pause");
		}
	}
}
