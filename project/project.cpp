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

struct Section {
	int id;
	int dep_id;
	char name[NAME_LENGTH];
	char owner[NAME_LENGTH];
};

void IntroMenu();
void AdminMenu();
void AddDepartementMenu();
void makeDepartement(char [] , char[]);
void copyString(char[], char[]);
void printDepToFile(char[], Departement);
void intToStr(int, char[]);
void concatString(char[], char[]);
void addSectionMenu();
int getLastId(char path[]);
void printSecToFile(char[], Section);
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
	system("cls");

	switch (choice) {
	case 1:
		AddDepartementMenu();
		break;
	case 2:
		addSectionMenu();
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		break;
	case 6:
		IntroMenu();
	case 0:
		exit(0);
		break;
	default:
		cout << "Invalid choice!\n\n";
		AdminMenu();
	}
}
// reformat this so make dep is here
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


void addSectionMenu() {
	Section section;
	char path[] = "sections.txt";

	//add a way to handle this
	cout << "what is the departement id of this section: ";
	cin >> section.dep_id;

	cout << "What is section name: ";
	cin >> section.name;

	cout << "who is the sections owner: ";
	cin >> section.owner;

	section.id = getLastId(path) + 1;
	printSecToFile(path, section);
	system("cls");
	AdminMenu();
}

void printSecToFile(char path[], Section sec) {
	ofstream file(path, ios::app);
	file << sec.id << "|" << sec.name << "|" << sec.owner << "|" << sec.dep_id << '\n';
	file.close();
}

void makeDepartement(char name[], char owner[]) {
	char path[] = "Depatement.txt";
	Departement newDep;
	
	copyString(newDep.name, name);
	copyString(newDep.owner, owner);
	newDep.id = getLastId(path) + 1; // the new id has to be +1 of the last id
	printDepToFile(path, newDep);
}

void intToStr(int number, char output[]) {
	char temp[20];
	int i = 0;
	while (number > 0) {
		int digit = number % 10;
		temp[i] = digit + '0';
		i++;
		number /= 10;
	}
	// Reverse the digits to get the order right
	int outputIndex = 0;
	for (int j = i - 1; j >= 0; --j) {
		output[outputIndex++] = temp[j];
	}

	output[outputIndex] = '\0';
}

int stringToInt(const char str[]) {
	int result = 0;
	int i = 0;
	while (str[i] != '\0') {
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return result;
}

void copyString(char first[],char second[]) {
	int i = 0;
	while (second[i]) {
		first[i] = second[i];
		i++;
	}
	first[i] = '\0';
}
//might not be needed
void concatString(char first[], char second[]) {
	int i = 0;
	int j = 0;
	while (first[i]) {
		i++;
	}
	while (second[j]) {
		first[i] = second[j];
		j++;
		i++;
	}
	first[i] = '\0';
}

void printDepToFile(char path[], Departement dep) {
	ofstream file(path, ios::app);
	file << dep.id << '|' << dep.name << '|' << dep.owner << '\n';
		file.close();
}

int getLastId(char path[]) {
	ifstream infile(path);
	if (!infile.is_open()) {
		return 0;  // If file doesn't exist or is empty, start from ID 1
	}

	char line[256];
	char lastLine[256] = "";  // The last line

	while (infile.getline(line, 256)) {
		copyString(lastLine, line);  // Keep updating
	}
	infile.close();

	if (lastLine[0] == '\0') {
		return 0;  // If file was empty
	}

	char idStr[20];
	int j = 0;
	for (int i = 0; lastLine[i] != '\0' && lastLine[i] != '|'; i++) {
		idStr[j++] = lastLine[i]; // just get the id
	}
	idStr[j] = '\0'; // so the functions work with it

	return stringToInt(idStr);
}