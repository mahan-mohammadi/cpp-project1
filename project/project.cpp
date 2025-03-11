#include <iostream>
#include <fstream>

using namespace std;

const int MAX_DEPARTMENTS = 100;
const int MAX_SECTIONS = 500;
const int MAX_RESOURCES = 1000;
const int MAX_REQUESTS = 1000;
const int NAME_LENGTH = 50;

void IntroMenu();
void AdminMenu();

int main() {
	cout << "Welcome to the Resoucre Management System!\n";
	IntroMenu();
}

void IntroMenu() {
	int choice;

	cout << "1.Login as admin\n2.Login as user\nEnter number of you choice: ";
	cin >> choice;
	if (choice == 1) {
		system("cls");
		AdminMenu();
	}
	else if (choice == 2) {
		// Login as user
	}
	else {
		system("cls");
		cout << "Invalid choice!\n";
		IntroMenu();
	}
}

void AdminMenu() {
	int choice;

	cout << "Admin menu:\n";
	cout << "	1. Add Department\n";
	cout << "	2. Add Section\n";
	cout << "	3. Add Resource\n";
	cout << "	4. View Requests\n";
	cout << "	5. Generate Reports\n";
	cout << "	6. Go back\n";
	cout << "	0. Exit\n";
	cout << "Enter choice: ";
	cin >> choice;

	switch (choice) {
	case 1:
		// Add Department
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
		IntroMenu();
	case 0:
		break;
	default:
		system("cls");
		cout << "Invalid choice!\n";
		AdminMenu();
	}
}