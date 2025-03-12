#include <iostream>
#include <fstream>

using namespace std;

const int MAX_DEPARTMENTS = 100;
const int MAX_SECTIONS = 500;
const int MAX_RESOURCES = 1000;
const int MAX_REQUESTS = 1000;
const int NAME_LENGTH = 50;

struct Departement {
	int id;
	char name[NAME_LENGTH];
	char owner[NAME_LENGTH];
};

void IntroMenu();
void AdminMenu();
void AddDepartementMenu();
void makeDepartement(char [] , char[]);
void copyString(char[], char[]);

int main() {
	cout << "Welcome to the Resoucre Management System!\n\n";
	IntroMenu();

	return 0;
}

void IntroMenu() {
	int choice;

	cout << "1.Login as admin\n2.Login as user\n0.exit\n\nEnter number of you choice: ";
	cin >> choice;
	if (choice == 1) {
		system("cls");
		AdminMenu();
	}
	else if (choice == 2) {
		// Login as user
	}
	else if (choice == 0) {
		exit(0);
	}
	else {
		system("cls");
		cout << "Invalid choice!\n\n";
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
		system("cls");
		AddDepartementMenu();
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
		exit(0);
		break;
	default:
		system("cls");
		cout << "Invalid choice!\n\n";
		AdminMenu();
	}
}

void AddDepartementMenu() {
	char name[NAME_LENGTH];
	char ownerName[NAME_LENGTH];
	
	cout << "Welcom to the Department defining menu\n\n";

	cout << "What is the name of the Department: ";
	cin >> name;

	cout << "\nWhat is the name of the owner: ";
	cin >> ownerName;
	makeDepartement(name, ownerName);
	system("cls");
	AdminMenu();
}

//WIP
void makeDepartement(char name[], char owner[]) {
	static int i = 1;
	Departement newDep;
	
	copyString(newDep.name, name);
	copyString(newDep.owner, owner);
	newDep.id = i;
	i++;
}

void departementToString(Departement dep,char output[]) {
	
}

void copyString(char first[],char second[]) {
	int i = 0;
	while (second[i]) {
		first[i] = second[i];
		i++;
	}
	first[i] = '\0';
}

void printToFile(char path[], char string[]) {
	ofstream file(path, ios::app);
	file << string;

}