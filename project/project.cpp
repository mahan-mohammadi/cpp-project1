#include <iostream>
#include <fstream>

using namespace std;

const int NAME_LENGTH = 50;

enum Type {
	HOURLY = 1, DAILY, MOUNTHLY, SAMPLE
};

enum Acess_Level {
	ADMIN = 1, OWNER, USER
};

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

struct Resource {
	int id;
	int sec_id;
	char name[NAME_LENGTH];
	Type type;
	int price;
};

struct Person {
	int id;
	char name[NAME_LENGTH];
};

struct Admin {
	Person person;
	int phoneNumber;
};

struct User {
	Person person;
	int gov_id;
	Acess_Level level = USER;
	char password[NAME_LENGTH];
};

struct Request {
	Resource res;
	User user;
	int id;
	int number;
	int time;
	bool isApproved = false;
	char name[NAME_LENGTH];
};

void IntroMenu();
void OwnerMenu(int id);
void AddDepartementMenu();
void makeDepartement(char[], char[]);
void copyString(char[], char[]);
void printDepToFile(char[], Departement);
void intToStr(int, char[]);
void concatString(char[], char[]);
void addSectionMenu();
int getLastId(char path[]);
void printSecToFile(char[], Section);
void addResourceMenu();
void printResourceToFile(char path[], Resource res);
void userMenu(int id);
void getDepartmentsMenu(int id);
void getSectionsMenu(int id);
void getResourcesMenu(int id);
void stringForResourceType(char[], int);
void sendReqMenu(int id);
void printDepToCLI();
void printSecToCLI(int);
void logIn();
void signIn();
void printUserToFile(User);
bool isGovIDValid(int);
Request makeReq(int id, char name[], int res_id, int userID);
bool areStringsEqual(char[], char[]);
bool isPasswordValid(char str[]);

int main() {

	int choice;
	bool valid = false;
	do {
		cout << "Welcome to the Resoucre Management System!\n\n";
		cout << "do you want to:\n\n";
		cout << "\t1 - log in\n";
		cout << "\t2 - sign in\n";
		cout << "\t0 - exit\n\n";
		cout << "Enter you choice number: ";
		cin >> choice;
		switch (choice)
		{
		case 1:
			system("cls");
			logIn();
			valid = true;
			break;
		case 2:
			system("cls");
			signIn();
			valid = true;
			break;
		case 0:
			exit(0);
			break;
		default:
			system("cls");
			cout << "\ninvalid choice\n\n";
			break;
		}
	} while (!valid);

	return 0;
}

void AdminMenu() {
	int choice;

	cout << " welcome to The admin menu:\n\n";
	cout << "	1 - add department\n";
	cout << "	2 - see all Department\n";
	cout << "	3 - see all Section\n";
	cout << "	4 - see all Resource\n";
	cout << "	5 - go back\n";
	cout << "	0 - exit\n\n";
	cout << "enter your choice: ";
	cin >> choice;

	system("cls");
	switch (choice)
	{
		case 1:
			AddDepartementMenu();
			break;
		case 2:
			getDepartmentsMenu(0);
			break;
		case 3:
			getSectionsMenu(0);
			break;
		case 4:
			getResourcesMenu(0);
			break;
		case 5:
			main();
			break;
		case 0:
			exit(0);
			break;
		default:
			cout << "invalid input";
			AdminMenu();
	}
}

void signIn() {
	char path[] = "users.txt";
	User user;

	char name[NAME_LENGTH];
	cout << "what is your name: ";
	cin >> name;

	int gov_id;
	bool isNotValid = false;
	do {
		cout << "Enter your goverment id number: ";
		cin >> gov_id;
		isNotValid = !isGovIDValid(gov_id);
		if (isNotValid) {
			cout << "\nthis id already exist in our database\n\n";
		}
	} while (isNotValid);

	char password[NAME_LENGTH];

	do {
		cout << "Enter a password that is atleast 8 characthers long and has both numbers and letters: ";
		cin >> password;
	} while (!isPasswordValid(password));
	
	int id = getLastId(path)+1;

	user.person.id = id;
	copyString(user.person.name, name);
	copyString(user.password, password);
	user.gov_id = gov_id;
	

	printUserToFile(user);
	system("cls");
	cout << "your id is (" << id << "). please save it somewhere as you will need it to login\n\n";
	userMenu(id);
}

int strLen(char str[]) {
	int count = 0;
	while (*str) {
		str++;
		count++;
	}
	return count;
}

bool isAlpha(char c) {
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
		return true;
	}
	else {
		return false;
	}
}

bool isNumber(char c) {
	if (c >= '0' && c <= '9') {
		return true;
	}
	else {
		return false;
	}
}

bool isPasswordValid(char str[]) {
	bool hasAlpha = false;
	bool hasNumber = false;
	if (strLen(str) < 8) {
		return false;
	}
	while (*str) {
		if (isNumber(*str)) {
			hasNumber = true;
		}
		if (isAlpha(*str)) {
			hasAlpha = true;
		}
		str++;
	}
	
	return hasAlpha && hasNumber;
}

bool isGovIDValid(int targetID ) {
	char path[] = "users.txt";
	ifstream file(path);
	char line[256];
	bool found = false;

	while (file.getline(line, 256)) {
		int level = 0;
		int id = 0;
		for (int i = 0; line[i]; i++) {
			if (line[i] == '|') {
				level++;
				continue;
			}
			switch (level)
			{
			case 2:
				id = id * 10 + (line[i] - '0');
				break;
			}
		}
		if (id == targetID) {
			found = true;
			break;
		}
	}
	file.close();

	bool isValid = !found;
	return isValid;
}

void logIn() {
	char inputPassword[NAME_LENGTH];
	int inputID;
	bool valid = false;
	Acess_Level acessLevel;
	int acess;
	while (!valid) {
		cout << "Enter your user id: ";
		cin >> inputID;

		cout << "Enter your password: ";
		cin >> inputPassword; // Safer password input

		ifstream file("users.txt");
		if (!file) {
			cerr << "Error opening user database." << endl;
			return;
		}

		char line[256];
		while (file.getline(line, 256)) {
			char targetPassword[NAME_LENGTH] = { 0 };
			int TargetId = 0;
			int level = 0;
			int passwordIndex = 0;

			for (int i = 0; line[i]; i++) {
				if (line[i] == '|') {
					level++;
					continue;
				}
				switch (level) {
				case 0: // Parse user ID
					TargetId = TargetId * 10 + (line[i] - '0');
					break;
				case 3:
					acess = line[i] - '0';
					break;
				case 4: // Parse password
					if (passwordIndex < NAME_LENGTH - 1)
						targetPassword[passwordIndex++] = line[i];
					break;
				}
			}

			if (TargetId == inputID && areStringsEqual(inputPassword, targetPassword)) {
				valid = true;
				system("cls");
				if (acess == USER) {
					userMenu(TargetId);
				}
				else if (acess == OWNER) {
					OwnerMenu(TargetId);
				}
				break; // Exit the file reading loop if a match is found
			}
		}

		file.close();
		if (!valid) {
			cout << "Invalid ID or password. Please try again.\n" << endl;
		}
	}
}


bool areStringsEqual(char first[] , char second[]) {
	while (*first != '\0' && *second != '\0') {

		if (*first != *second)
			return false;
		first++;
		second++;
	}
	if (*first == '\0' && *second == '\0') {
		return true;
	}
	else {
		return false;
	}
}


void printUserToFile(User user) {
	char path[] = "users.txt";
	ofstream file(path, ios::app);

	file << user.person.id << '|' << user.person.name << '|' << user.gov_id << '|' << user.level <<'|' << user.password << '\n';
}

void OwnerMenu(int id) {
	int choice;

	cout << "Owner menu:\n";
	cout << "	1. Add Department\n"; // this should be removed
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
		addResourceMenu();
		break;
	case 4:
		break;
	case 5:
		break;
	case 6:
		main();
	case 0:
		exit(0);
		break;
	default:
		cout << "Invalid choice!\n\n";
		OwnerMenu(id);
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
	OwnerMenu(id);
}

void userMenu(int id) {
	int choice;

	cout << "welocme to user menu\n\n";
	cout << "	1. see all Department\n";
	cout << "	2. see all Section\n";
	cout << "	3. see all Resource\n";
	cout << "	4. send a Request\n";
	cout << "	5. Go back\n";
	cout << "	0. Exit\n";

	cout << "Enter choice: ";
	cin >> choice;
	system("cls");

	switch (choice) {
	case 1:
		getDepartmentsMenu(id);
		break;
	case 2:
		getSectionsMenu(id);
		break;
	case 3:
		getResourcesMenu(id);
		break;
	case 4:
		sendReqMenu(id);
		break;
	case 5:
		main();
		break;
	case 0:
		exit(0);
		break;
	default:
		cout << "invalid choice \n\n";
		userMenu(id);
		break;
	}
}

void addSectionMenu() {
	Section section;
	char path[] = "sections.txt";

	cout << "Welcom to the section defining menu\n\n";

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
	OwnerMenu(id);
}
// remove the unnesscary while loop here
void addResourceMenu() {
	cout << "Welcom to the resource defining menu\n\n";

	char path[] = "resources.txt";
	Resource res;
	int choice;
	bool isValid = false;

	cout << "what is the section id of this resource: ";
	cin >> res.sec_id;

	cout << "What is resource name: ";
	cin >> res.name;

	cout << "What is the type of this resource:\n\n";
	cout << "	1.HOURLY\n";
	cout << "	2.DAILY\n";
	cout << "	3.MOUNTHLY\n";
	cout << "	4.SAMPLE BASED\n\n";

	while (!isValid)
	{
		cout << "Enter your choice: ";
		cin >> choice;
		switch (choice)
		{
		case HOURLY:
			isValid = true;
			res.type = HOURLY;
			break;

		case DAILY:
			isValid = true;
			res.type = DAILY;
			break;

		case MOUNTHLY:
			isValid = true;
			res.type = MOUNTHLY;
			break;

		case SAMPLE:
			isValid = true;
			res.type = SAMPLE;
			break;

		default:
			cout << "Not a valid choice. Try again.";
			break;
		}
	}

	cout << "\nwhat is the price of this resource per time/sample: ";
	cin >> res.price;

	res.id = getLastId(path) + 1;  // get an id for the request

	printResourceToFile(path, res);
	system("cls");
	OwnerMenu(id);
}

void printResourceToFile(char path[], Resource res) {
	ofstream file(path, ios::app);
	file << res.id << "|" << res.name << "|" << res.type << "|" << res.price << "|" << res.sec_id << '\n';
	file.close();
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
	int number = 0;
	int i = 0;
	while (str[i] != '\0') {
		number = number * 10 + (str[i] - '0');
		i++;
	}
	return number;
}

void copyString(char first[], char second[]) {
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
	ifstream file(path);
	if (!file.is_open()) {
		return 0;  // If file doesn't exist or is empty, start from ID 1
	}

	char line[256];
	char lastLine[256] = "";  // The last line

	while (file.getline(line, 256)) {
		copyString(lastLine, line);  // Keep updating
	}
	file.close();

	if (lastLine[0] == '\0') {
		return 0;  // If file was empty
	}

	char id[20];
	int j = 0;
	for (int i = 0; lastLine[i] != '\0' && lastLine[i] != '|'; i++) {
		id[j] = lastLine[i]; // just get the id
		j++;
	}
	id[j] = '\0'; // so the functions work with it

	return stringToInt(id);
}

void getDepartmentsMenu(int id) {

	int Choice = 1;

	printDepToCLI();

	cout << "Enter 0 and enter to return back: ";
	while (Choice) {
		cin >> Choice;
	}

	system("cls");
	userMenu(id);
}

void getSectionsMenu(int id) {
	int Choice = 1;
	char path[] = "sections.txt";
	char line[256];

	ifstream file(path);

	cout << "list of all sections: \n\n";
	while (file.getline(line, 256)) {

		int nameIndex = 0, ownerIndex = 0, level = 0;
		int id = 0, dep_id = 0;
		char name[NAME_LENGTH] = { 0 };
		char owner[NAME_LENGTH] = { 0 };

		for (int i = 0; line[i]; i++) {
			if (line[i] == '|') {
				level++;
				continue;
			}
			switch (level)
			{
			case 0: //process id
				id = id * 10 + (line[i] - '0');
				break;
			case 1: // process Name
				if (nameIndex < NAME_LENGTH - 1)
					name[nameIndex++] = line[i];
				break;
			case 2: //process  Owner
				if (ownerIndex < NAME_LENGTH - 1)
					owner[ownerIndex++] = line[i];
				break;
			case 3:
				dep_id = dep_id * 10 + (line[i] - '0');
				break;
			}

		}
		name[nameIndex] = '\0';
		owner[ownerIndex] = '\0';

		cout << '\t' << "name: " << name << '\t' << "owner: " << owner << '\t' << "id: " << id << '\t' << "department id: " << dep_id << "\n\n";

	}
	cout << "Enter 0 and enter to return back: ";
	while (Choice) {
		cin >> Choice;
	}
	system("cls");
	userMenu(id);
}

void getResourcesMenu(int userid) {
	int Choice = 1;
	char path[] = "resources.txt";
	char line[256];

	ifstream file(path);

	cout << "list of all resources: \n\n";

	while (file.getline(line, 256)) {
		int level = 0, id = 0, nameIndex = 0, sec_id = 0, type = 0, price = 0;
		char name[NAME_LENGTH] = { 0 };
		char typestr[20];
		for (int i = 0; line[i]; i++) {
			if (line[i] == '|') {
				level++;
				continue;
			}
			switch (level)
			{
			case 0: //process id
				id = id * 10 + (line[i] - '0');
				break;
			case 1: // process Name
				if (nameIndex < NAME_LENGTH - 1)
					name[nameIndex++] = line[i];
				break;
			case 2: //process  type
				type = line[i] - '0';
				break;
			case 3:
				price = price * 10 + (line[i] - '0');
				break;
			case 4:
				sec_id = sec_id * 10 + (line[i] - '0');
				break;
			}
		}
		name[nameIndex] = '\0';
		stringForResourceType(typestr, type);
		cout << '\t' << "name: " << name << '\t' << "id: " << id << '\t' << "resource type: " << typestr << '\t' << "price: " << price << '\t' << "section id: " << sec_id << "\n\n";
	}

	cout << "Enter 0 and enter to return back: ";
	while (Choice) {
		cin >> Choice;
	}
	system("cls");
	userMenu(userid);
}

void stringForResourceType(char type[], int intType) {
	char hourly[] = "hourly";
	char daily[] = "daily";
	char mounthly[] = "mounthly";
	char sample[] = "sample based";

	switch (intType) {
	case 1:
		copyString(type, hourly);
		break;
	case 2:
		copyString(type, daily);
		break;
	case 3:
		copyString(type, mounthly);
		break;
	case 4:
		copyString(type, sample);
	}
}

void printDepToCLI() {
	char path[] = "Depatement.txt";
	char line[256];


	ifstream file(path);

	cout << "list of all departments: \n\n";

	while (file.getline(line, 256)) {

		int nameIndex = 0, ownerIndex = 0, level = 0;
		int id = 0;
		char name[NAME_LENGTH] = { 0 };
		char owner[NAME_LENGTH] = { 0 };

		for (int i = 0; line[i]; i++) {
			if (line[i] == '|') {
				level++;
				continue;
			}
			switch (level) {
			case 0: // procces ID
				id = id * 10 + (line[i] - '0');
				break;
			case 1: // peocess Name
				if (nameIndex < NAME_LENGTH - 1)
					name[nameIndex++] = line[i];
				break;
			case 2: //process  Owner
				if (ownerIndex < NAME_LENGTH - 1)
					owner[ownerIndex++] = line[i];
				break;
			}
		}
		name[nameIndex] = '\0';
		owner[ownerIndex] = '\0';

		cout << '\t' << "name: " << name << '\t' << "owner: " << owner << '\t' << "id: " << id << '\t' << "\n\n";
	}
}

void printSecToCLI(int targetDep) {
	char path[] = "sections.txt";
	char line[256];

	ifstream file(path);

	cout << "List of sections in department " << targetDep << ":\n\n";
	while (file.getline(line, 256)) {

		int nameIndex = 0, ownerIndex = 0, level = 0;
		int id = 0, dep_id = 0;
		char name[NAME_LENGTH] = { 0 };
		char owner[NAME_LENGTH] = { 0 };

		for (int i = 0; line[i]; i++) {
			if (line[i] == '|') {
				level++;
				continue;
			}
			switch (level)
			{
			case 0: //process id
				id = id * 10 + (line[i] - '0');
				break;
			case 1: // process Name
				if (nameIndex < NAME_LENGTH - 1)
					name[nameIndex++] = line[i];
				break;
			case 2: //process  Owner
				if (ownerIndex < NAME_LENGTH - 1)
					owner[ownerIndex++] = line[i];
				break;
			case 3:
				dep_id = dep_id * 10 + (line[i] - '0');
				break;
			}

		}
		name[nameIndex] = '\0';
		owner[ownerIndex] = '\0';

		if (dep_id == targetDep) {
			cout << '\t' << "name: " << name << '\t' << "owner: " << owner << '\t' << "id: " << id << '\t' << "department id: " << dep_id << "\n\n";
		}

	}
}

void printResToCLI(int targetSec) {
	char path[] = "resources.txt";
	char line[256];

	ifstream file(path);

	cout << "list of all resources: \n\n";

	while (file.getline(line, 256)) {
		int level = 0, id = 0, nameIndex = 0, sec_id = 0, type = 0, price = 0;
		char name[NAME_LENGTH] = { 0 };
		char typestr[20];
		for (int i = 0; line[i]; i++) {
			if (line[i] == '|') {
				level++;
				continue;
			}
			switch (level)
			{
			case 0: //process id
				id = id * 10 + (line[i] - '0');
				break;
			case 1: // process Name
				if (nameIndex < NAME_LENGTH - 1)
					name[nameIndex++] = line[i];
				break;
			case 2: //process  type
				type = line[i] - '0';
				break;
			case 3:
				price = price * 10 + (line[i] - '0');
				break;
			case 4:
				sec_id = sec_id * 10 + (line[i] - '0');
				break;
			}
		}
		if (targetSec == sec_id) {
			name[nameIndex] = '\0';
			stringForResourceType(typestr, type);
			cout << '\t' << "name: " << name << '\t' << "id: " << id << '\t' << "resource type: " << typestr << '\t' << "price: " << price << '\t' << "section id: " << sec_id << "\n\n";
		}
	}
}

void printRequestToFile(Request req) {
	ofstream file("requests.txt", ios::app );
	file << req.id << '|' << req.name << '|' << req.isApproved << '|' << req.res.id << '|' << req.user.person.id << '\n'; //number of request
}

Request makeReq(int id, char name[], int res_id, int userID) {
	Request req;
	req.id = id;
	req.res.id = res_id;
	req.user.person.id = userID;
	copyString(req.name, name);
	req.isApproved = false;
	return req;
}

void sendReqMenu(int userid) {
	char path[] = "requests.txt";

	printDepToCLI();
	int dep_id;
	cout << "type the wanted department id: ";
	cin >> dep_id;

	system("cls");
	printSecToCLI(dep_id);
	int sec_id;
	cout << "type the wanted section id: ";
	cin >> sec_id;

	system("cls");
	printResToCLI(sec_id);

	int res_id;
	cout << "type the wanted resorce id: ";
	cin >> res_id;

	system("cls");
	cout << "you have selected resource with id: " << res_id << "\n\n";

	char name[NAME_LENGTH];
	cout << "what is the name of this request: ";
	cin >> name;

	int id = getLastId(path) + 1;

	Request req = makeReq(id, name, res_id, userid);

	printRequestToFile(req);

	system("cls");
	userMenu(userid);
}
