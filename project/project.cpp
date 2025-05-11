//add get AND SET TYPOE AND LEVEL and time
#include <iostream>
#include <fstream>

using namespace std;

const int NAME_LENGTH = 50;
const int LINE_LENGTH = 256;
const int MAX_REQUESTS = 1000;
const int MIN_LENGTH_PASS = 8;
const int DAYS_IN_YEAR = 360;
const int HOURS_IN_YEAR = 8640;
const int MONTHS_IN_YEAR = 12;
const int DAYS_IN_MONTH = 30;
const int HOURS_IN_DAY = 24;
const int MAX_RESOURCES = 1000;
char txtExtension[] = ".txt";

enum Type {
	HOURLY = 1, DAILY, MOUNTHLY, SAMPLE
};

enum Acess_Level {
	ADMIN = 1, OWNER, USER
};

class Dep {
protected:
	int Depid;
	char depName[NAME_LENGTH];
	Owner owner;
public:
	Dep();
	void setDepID(int);
	void setName(char[]);
	int getDepID();
	void getDepName(char[]);
};

void Dep::setDepID(int inputid) {
	Depid = inputid;
}

void Dep::setName(char inputname[]) {
	copyString(depName, inputname);
}

int Dep::getDepID() {
	return Depid;
}

void Dep::getDepName(char nameoutput[]) {
	copyString(nameoutput, depName);
}

class Owner :public Person {
protected:
	Acess_Level level = OWNER;

};

class User {
protected:
	Acess_Level level = USER;
};

class Person {
protected:
	int personid;
	char Personname[NAME_LENGTH];
	Acess_Level level;
	int govid;
public:
	Person();
	int getPersonID();
	int getGovID();
	void getPersonName(char[]);
	void setPersonid(int);
	void setPersonName(char[]);
	void setGovID(int);

};

int Person::getPersonID() {
	return personid;
}

int Person::getGovID() {
	return govid;
}

void Person::getPersonName(char output[]) {
	copyString(output, Personname);
}

void Person::setPersonid(int input) {
	personid = input;
}

void Person::setGovID(int input) {
	govid = input;
}

void Person::setPersonName(char input[]) {
	copyString(Personname, input);
}

class Section :public Dep {
protected:
	int sectionid;
	char secname[NAME_LENGTH];
public:
	Section();
	int getSectionID();
	void getSectionName(char[]);
	void setSectionName(char[]);
	void setSectioID(int);
};

class Resource : public Section {
protected:
	int Resourceid;
	char ResName[NAME_LENGTH];
	Type type;
	int price;
	int cost;
	int stock;
public:
	Resource();
	int getResourceID();
	int getPrice();
	int getStock();
	int getCost();

};

class Date {
private:
	int Month;
	int day;
	int hour;
public:
	Date();
	int getMonth();
	int getDay();
	int Hour();
};

class Request {
private:
	int reqid;
	Resource res;
	User user;
	bool isApproved;
	Time time;
public:
	Request();
	int getReqID();
	bool getApproval();

};

/*struct Person {
	int id;
	char name[NAME_LENGTH];
};

struct Time {
	int month;
	int day;
	int hour;
};

struct Owner {
	char name[NAME_LENGTH];
	int id;
	int govID;
	Acess_Level level = OWNER;
	char password[NAME_LENGTH];
};

struct User {
	int id;
	char name[NAME_LENGTH];
	int gov_id;
	Acess_Level level = USER;
	char password[NAME_LENGTH];
};

struct Departement {
	int id;
	char name[NAME_LENGTH];
	int ownerID;
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
	int cost;
	int stock;
};

struct Request {
	int resID;
	int userID;
	int id;
	bool isApproved = false;
	char name[NAME_LENGTH];
	Time time;
	int intTime;
};

struct reqcount {
	int resid = -1;
	int count = 0;
};*/

Time hourToTime(int);
Time dayToTime(int);
Time monthToTime(int);
bool isResInStock(int);
void makeResFile(char[], Type);
void intToStr(int, char[]);
void printRequestToFile(Request);
void printResToCLI(int);
void OwnerMenu(int id);
void AddDepartementMenu(int id);
void makeDepartement(char[], int);
void copyString(char[], char[]);
void printDepToFile(char[], Departement);
void intToStr(int, char[]);
void concatString(char[], char[]);
void addSectionMenu(int);
int getLastId(char[]);
void printSecToFile(char[], Section);
int stringToInt(const char[]);
void addResourceMenu(int);
void printResourceToFile(char[], Resource);
void userMenu(int);
void getDepartmentsMenu(int);
void getSectionsMenu(int);
void getResourcesMenu(int);
void stringForResourceType(char[], int);
void sendReqMenu(int);
void printDepToCLI();
void printSecToCLI(int);
void logIn();
void signIn();
void printUserToFile(User);
bool isGovIDValid(int);
Request makeReq(int, char[], int, int, int);
bool areStringsEqual(char[], char[]);
bool isPasswordValid(char str[]);
void AdminMenu();
void ViewNonApprovedReqMenu(int);
void getRequests(int, Request[], int&);
int makeOwner();
int getTypeOfRes(int);
void getAvailabeDates(int, bool[]);
void printTime(Time);
void printOwnerToFile(Owner);
void printReqToCLI(Request);
int DepIDOfOwner(int);
int secIDOfRes(int);
int depIDOfsec(int);
void approveReqInFile(Request);
void ViewApprovedReqMenu(int);
void ReportMenu(int);
void sortReq(reqcount[], int);
int calculateProfitPerRes(int);
void printDivider();

/*
 primary menus
*/

int main() {
	int choice;
	bool valid = false;

	do {
		cout << "Welcome to the Resoucre Management System!\n";
		cout << "==========================================\n";
		cout << "do you want to:\n\n";
		cout << "\t1 - log in\n";
		cout << "\t2 - sign in\n";
		cout << "\t3 - admin menu (temp)\n";
		cout << "\t0 - exit\n";
		cout << "==========================================\n";
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
		case 3:
			system("cls");
			AdminMenu();
			break;
		case 0:
			exit(0);
			break;
		default:
			system("cls");
			cout << "\n***invalid choice***\n\n";
			break;
		}
	} while (!valid);

	return 0;
}

void logIn() {
	char inputPassword[NAME_LENGTH];
	int inputID;
	bool valid = false;

	while (!valid) {
		cout << "Enter your user id: ";
		cin >> inputID;

		cout << "Enter your password: ";
		cin >> inputPassword;

		ifstream file("users.txt");
		if (!file.is_open()) {
			cerr << "***Error opening user database.***" << endl;
			return;
		}

		int userID = 0, govID = 0, level = 0;
		char name[NAME_LENGTH];
		char targetPassword[NAME_LENGTH];

		while (file >> userID >> name >> govID >> level >> targetPassword) {
			if (userID == inputID && areStringsEqual(inputPassword, targetPassword)) {
				file.close();
				valid = true;
				system("cls");
				if (level == USER) {
					userMenu(userID);
				}
				else if (level == OWNER) {
					OwnerMenu(userID);
				}
				break; // Exit the file reading loop if a match is found
			}
		}

		file.close();
		if (!valid) {
			cout << "***Invalid ID or password. Please try again.***\n" << endl;
		}
	}
}

void signIn() {
	char path[] = "users.txt";
	User user;

	char name[NAME_LENGTH];
	cout << "what is your name: ";
	cin >> name;

	int gov_id;
	bool isValid = false;

	do {
		cout << "Enter your goverment id number: ";
		cin >> gov_id;
		isValid = isGovIDValid(gov_id);
		if (!isValid) {
			cout << "\n***this id already exist in our database***\n\n";
		}
	} while (!isValid);

	char password[NAME_LENGTH];

	do {
		cout << "Enter a password that is atleast 8 characthers long and has both numbers and letters: ";
		cin >> password;
	} while (!isPasswordValid(password));

	int id = getLastId(path) + 1;

	user.id = id;
	copyString(user.name, name);
	copyString(user.password, password);
	user.gov_id = gov_id;


	printUserToFile(user);
	system("cls");
	cout << "***your id is (" << id << "). please save it somewhere as you will need it to login***\n\n";
	userMenu(id);
}

void AdminMenu() {
	int choice;

	cout << "welcome to The admin menu:\n";
	cout << "==========================\n";
	cout << "	1 - add department\n";
	cout << "	2 - go back\n";
	cout << "	0 - exit\n";
	cout << "==========================\n";
	cout << "enter your choice: ";
	cin >> choice;

	system("cls");
	switch (choice)
	{
	case 1:
		AddDepartementMenu(0);
		break;
	case 2:
		main();
		break;
	case 0:
		exit(0);
		break;
	default:
		cout << "\n***invalid input***\n\n";
		AdminMenu();
	}
}

void userMenu(int id) {
	int choice;

	cout << "welocme to user menu\n";
	cout << "================================\n";
	cout << "	1. see all Department\n";
	cout << "	2. see all Section\n";
	cout << "	3. see all Resource\n";
	cout << "	4. send a Request\n";
	cout << "	5. view approved requests\n";
	cout << "	6. Go back\n";
	cout << "	0. Exit\n";
	cout << "===============================\n";

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
		ViewApprovedReqMenu(id);
		break;
	case 6:
		main();
		break;
	case 0:
		exit(0);
		break;
	default:
		cout << "***invalid choice*** \n\n";
		userMenu(id);
		break;
	}
}

void OwnerMenu(int id) {
	int choice;

	cout << "Owner menu:\n";
	cout << "===========================\n";
	cout << "	1 - Add Section\n";
	cout << "	2 - Add Resource\n";
	cout << "	3 - View Non approved Requests\n";
	cout << "	4 - Generate Reports\n";
	cout << "	5 - Go back\n";
	cout << "	0 - Exit\n";
	cout << "===========================\n";
	cout << "Enter choice: ";
	cin >> choice;
	system("cls");

	switch (choice) {
	case 1:
		addSectionMenu(id);
		break;
	case 2:
		addResourceMenu(id);
		break;
	case 3:
		ViewNonApprovedReqMenu(id);
		break;
	case 4:
		ReportMenu(id);
		break;
	case 5:
		main();
		break;
	case 0:
		exit(0);
		break;
	default:
		cout << "***Invalid choice!***\n\n";
		OwnerMenu(id);
	}
}

/*
secondary menus
*/

void AddDepartementMenu(int id) {
	cout << "Welcome to the Department defining menu\n\n";

	char name[NAME_LENGTH];
	cout << "What is the name of the Department: ";
	cin >> name;

	int ownerid = makeOwner();

	makeDepartement(name, ownerid);

	int number;
	cout << "\nEnter the number 0 to go back: ";

	while (true) {
		cin >> number;
		if (number == 0) {
			break;
		}
	}

	system("cls");
	AdminMenu();
}

int makeOwner() {
	char path[] = "users.txt";
	Owner owner;

	char name[NAME_LENGTH];
	cout << "what is owner's name: ";
	cin >> name;


	int gov_id;
	bool isValid = false;

	do {
		cout << "Enter your goverment id number: ";
		cin >> gov_id;
		isValid = isGovIDValid(gov_id);
		if (!isValid) {
			cout << "\n***this id already exist in our database***\n\n";
		}
	} while (!isValid);

	char password[NAME_LENGTH];

	do {
		cout << "Enter a password that is atleast 8 characthers long and has both numbers and letters: ";
		cin >> password;
	} while (!isPasswordValid(password));

	int id = getLastId(path) + 1;

	owner.id = id;
	copyString(owner.name, name);
	copyString(owner.password, password);
	owner.govID = gov_id;

	printOwnerToFile(owner);

	system("cls");

	cout << "***your id is (" << id << "). please save it somewhere as you will need it to login***\n\n";
	return owner.id;
}

void addSectionMenu(int id) {
	Section section;
	char path[] = "sections.txt";

	cout << "Welcome to the section defining menu\n\n";

	section.dep_id = DepIDOfOwner(id);

	cout << "What is section name: ";
	cin >> section.name;

	section.id = getLastId(path) + 1;

	printSecToFile(path, section);

	system("cls");
	OwnerMenu(id);
}

void addResourceMenu(int id) {
	cout << "Welcome to the resource defining menu\n\n";

	char path[] = "resources.txt";

	Resource res;
	int choice;
	bool isValid = false;

	cout << "what is the section id of the resource you want to add : \n";
	printSecToCLI(DepIDOfOwner(id));

	cout << "Enter the section id: ";
	cin >> res.sec_id;

	cout << "What is resource name: \n";

	cin >> res.name;

	cout << "What is the type of this resource:\n";
	cout << "==================================\n";
	cout << "	1.HOURLY\n";
	cout << "	2.DAILY\n";
	cout << "	3.MOUNTHLY\n";
	cout << "	4.SAMPLE BASED\n";
	cout << "==================================\n";

	while (!isValid)
	{
		cout << "\nEnter your choice: ";
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
			cout << "***Not a valid choice. Try again.***";
			break;
		}
	}

	while (true) {
		cout << "\nwhat is the price of this resource per time/sample (it should be positive number): ";
		cin >> res.price;
		if (res.price > 0) {
			break;
		}
	}

	while (true) {
		cout << "\nwhat is the cost of this resource per time/sample for you? (it should be positive): ";
		cin >> res.cost;
		if (res.cost > 0) {
			break;
		}
	}

	cout << "\nwhat is your stock of the resource";
	isValid = false;
	do {
		cin >> res.stock;
		if (res.stock > 0) {
			isValid = true;
		}
	} while (!isValid);

	res.id = getLastId(path) + 1; 

	char idFileName[NAME_LENGTH];
	intToStr(res.id, idFileName);
	concatString(idFileName, txtExtension);
	makeResFile(idFileName, res.type);

	printResourceToFile(path, res);

	system("cls");
	OwnerMenu(id);
}

void getDepartmentsMenu(int id) {

	int Choice = 1;

	printDepToCLI();

	while (Choice) {
		cout << "Enter 0 and enter to return back: ";
		cin >> Choice;
	}

	system("cls");
	userMenu(id);
}

void getSectionsMenu(int id) {
	int Choice = 1;
	char path[] = "sections.txt";

	ifstream file(path);

	if (!file.is_open()) {
		cerr << "***Error opening user database.***" << endl;
		return;
	}

	cout << "list of all sections: \n\n";

	int sectionid = 0, dep_id = 0;

	char name[NAME_LENGTH];

	while (file >> sectionid >> name >> dep_id) {

		printDivider();
		cout << '\t' << "section id: " << sectionid << '\t' << "name: " << name << '\t' << "department id: " << dep_id << "\n";
	}
	printDivider();

	cout << "Enter 0 and enter to return back: ";
	while (Choice) {
		cin >> Choice;
	}

	system("cls");
	userMenu(id);
}

void printDivider() {
	cout << "*******************************************************\n";
}

void sendReqMenu(int userid) {
	char path[] = "requests.txt";

	printDepToCLI();
	int dep_id;
	printDivider();
	cout << "type the wanted department id: ";
	cin >> dep_id;

	system("cls");

	printSecToCLI(dep_id);
	int sec_id;
	printDivider();
	cout << "type the wanted section id: ";
	cin >> sec_id;

	system("cls");
	printResToCLI(sec_id);

	printDivider();

	int res_id;
	cout << "type the wanted resorce id: ";
	cin >> res_id;

	int type = getTypeOfRes(res_id);
	bool* availableDates = nullptr;
	int count = 0;

	switch (type) {
	case DAILY:
		availableDates = new bool[DAYS_IN_YEAR+1];
		count = DAYS_IN_YEAR;
		break;
	case HOURLY:
		availableDates = new bool[HOURS_IN_YEAR+1];
		count = HOURS_IN_YEAR;
		break;
	case MOUNTHLY:
		availableDates = new bool[MONTHS_IN_YEAR+1];
		count = MONTHS_IN_YEAR;
		break;
	}

	getAvailabeDates(res_id, availableDates);

	system("cls");
	cout << "avaiable times: \n";

	for (int i = 1; i <= count && count == DAYS_IN_YEAR; i++) {
		if (availableDates[i] == 0) {
			cout << i << " Avaiable for the time ";
			printTime(dayToTime(i));
		}
	}

	for (int i = 1; i <= count && count == MONTHS_IN_YEAR; i++) {
		if (availableDates[i] == 0) {
			cout << i << " Avaiable for the time ";
			printTime(monthToTime(i));
		}
	}

	for (int i = 1; i <= count && count == HOURS_IN_YEAR; i++) {
		if (availableDates[i] == 0) {
			cout << i << " Avaiable for the time ";
			printTime(hourToTime(i));
		}
	}

	int selectedTime;

	if (count != 0) {
		do {
			cout << "\nselect the wanted time for your request: ";
			cin >> selectedTime;
		} while (availableDates[selectedTime] == 1 || selectedTime > count);
	}
	else {
		selectedTime = -1;
	}


	system("cls");
	cout << "you have selected resource with id: " << res_id << "\n\n";

	char name[NAME_LENGTH];
	cout << "what is the name of this request: ";
	cin >> name;

	int id = getLastId(path) + 1;

	Request req = makeReq(id, name, res_id, userid, selectedTime);

	printRequestToFile(req);

	system("cls");
	userMenu(userid);
}

void printTime(Time time) {
	cout << "Month: " << time.month << '|' << " Day: " << time.day << '|' << " Hour : " << time.hour << '\n';
}

int getTypeOfRes(int targetID) {
	ifstream file("resources.txt");

	if (!file.is_open()) {
		cerr << "\n***could not open database***\n";
	}

	int id, price, sec_id, cost, stock, type;
	char name[NAME_LENGTH];

	while (file >> id >> name >> type >> price >> sec_id >> cost >> stock) {
		if (id == targetID) {
			file.close();
			return type;
		}
	}
	file.close();
	return 0;
}

void getAvailabeDates(int resID, bool availabityArr[]) {
	char filename[NAME_LENGTH];
	intToStr(resID, filename);
	concatString(filename, txtExtension);

	ifstream file(filename);

	if (!file.is_open()) {
		cerr << "***could not open the database***\n\n";
		return;
	}

	int date = 0;
	bool isInUse = false;

	while (file >> date >> isInUse) {
		if (isInUse) {
			availabityArr[date] = true;
		}
		else {
			availabityArr[date] = false;
		}
	}
}

bool isResInStock(int targetid) {
	ifstream infile("resources.txt");
	Resource resources[MAX_RESOURCES];
	bool isInStock = false;

	if (!infile.is_open()) {
		cerr << "***could not open the database***\n\n";
		return false;
	}

	int tempType;
	int i = 0;
	while (infile >> resources[i].id 
		>> resources[i].name 
		>> tempType 
		>> resources[i].price >>
		resources[i].sec_id >> 
		resources[i].cost >> 
		resources[i].stock) 
	{
		resources[i].type = static_cast<Type>(tempType);
		if (resources[i].id == targetid) {
			if (resources[i].stock > 0) {
				resources[i].stock--;
				isInStock = true;
			}
			else {
				return false;
			}
		}
		i++;
	}
	infile.close();

	ofstream ofile("resources.txt");
	
	for (int j = 0; j < i; j++) {
		ofile << resources[j].id << ' ' << resources[j].name << ' '
			<< resources[j].type << ' ' << resources[j].price << ' '
			<< resources[j].sec_id << ' ' << resources[j].cost << ' '
			<< resources[j].stock << '\n';
	}

	ofile.close();

	return isInStock;
}

void ViewNonApprovedReqMenu(int userid) {
	Request requests[MAX_REQUESTS];
	int count = 0;
	int depid = DepIDOfOwner(userid);
	int choice;

	getRequests(userid, requests, count);

	cout << "the list of unapproved requests:\n\n";
	for (int i = 0; i < count; i++) {

		int target = depIDOfsec(secIDOfRes(requests[i].resID));
		if (target == depid && requests[i].isApproved == false) {
			printReqToCLI(requests[i]);
		}
	}

	do {
		cout << "Enter the request id you want to approve or 0 to go back: ";
		cin >> choice;

		if (choice == 0) {
			system("cls");
			OwnerMenu(userid);
		}

		else {
			bool found = false;
			for (int i = 0; i < count; i++) {
				if (requests[i].id == choice && !requests[i].isApproved) {
					if (!isResInStock(requests[i].resID)) {
						cout << "\n***this resource is not in stock***\n";
						found = true;

					}
					else {
						requests[i].isApproved = true;
						found = true;

						approveReqInFile(requests[i]);

						system("cls");
						cout << "***request for id (" << requests[i].id << ") is approved***\n\n";
						ViewNonApprovedReqMenu(userid);
						break;
					}

				}
			}
			if (!found) {
				cout << "\n***id not found***\n";
			}
		}

	} while (true);
}

void getResourcesMenu(int userid) {
	int Choice = 1;
	char path[] = "resources.txt";

	ifstream file(path);

	if (!file.is_open()) {
		cerr << "***Error opening user database.***" << endl;
		return;
	}

	cout << "list of all resources: \n\n";
	int id = 0, sec_id = 0, price = 0, cost = 0, stock = 0;

	char name[NAME_LENGTH];
	int type;
	char typestr[NAME_LENGTH];

	while (file >> id >> name >> type >> price >> sec_id >> cost >> stock) {
		stringForResourceType(typestr, type);

		printDivider();

		cout << '\t' << "name: " << name << '\t'
			<< "id: " << id << '\t'
			<< "resource type: " << typestr << '\t' 
			<< "price: " << price << '\t' 
			<< "section id: " << sec_id << '\t' 
			<< "stock: " << stock << "\n\n";
	}

	printDivider();
	cout << "Enter 0 and enter to return back: ";
	while (Choice) {
		cin >> Choice;
	}
	system("cls");
	userMenu(userid);
}

void ViewApprovedReqMenu(int targetid) {
	ifstream file("requests.txt");

	if (!file.is_open()) {
		cerr << "***Error opening user database.***" << endl;
		return;
	}

	int isApproved;
	int reqid = 0, userid = 0, resid = 0;
	char name[NAME_LENGTH];
	int intTime;
	while (file >> reqid >> name >> isApproved >> resid >> userid >> intTime) {
		if (targetid == userid && isApproved == 1)
			cout << "***your request for resource with id: " << resid << " with request id: " << reqid << " was approved.***" << "\n\n";
	}

	int choice;
	bool canExit = false;

	do {
		cout << "Enter 0 to go back: ";
		cin >> choice;
		if (choice == 0) {
			canExit = true;
		}
	} while (!canExit);

	system("cls");
	userMenu(targetid);
}

void ReportMenu(int userid) {
	Request requests[MAX_REQUESTS];
	int count = 0;
	int depid = DepIDOfOwner(userid);

	getRequests(userid, requests, count);
	reqcount* requestnumber = new reqcount[count];

	for (int i = 0; i < count; ++i) {
		requestnumber[i].resid = -1; // Mark as unused initially
		requestnumber[i].count = 0;
	}

	int targetcount = 0;
	int uniqueRes = 0;

	for (int i = 0; i < count; i++) {

		int target = depIDOfsec(secIDOfRes(requests[i].resID)); 
		if (target == depid && requests[i].isApproved) { //  check if the depid of there resources are equal to our dep id we got erlier
			int resid = requests[i].resID;
			bool found = false;
			
			for (int j = 0; j < uniqueRes; ++j) {
				if (requestnumber[j].resid == resid) {
					requestnumber[j].count++;
					found = true;
					break;
				}
			}
			if (!found) {
				requestnumber[uniqueRes].resid = resid;
				requestnumber[uniqueRes].count = 1;
				uniqueRes++;
			}
		}
	}

	sortReq(requestnumber, uniqueRes);
	for (int i = 0; i < uniqueRes; i++) {
		cout << " resource id: " << requestnumber[i].resid << " had " << requestnumber[i].count << " requests." 
			<< '\n' << "it made " << calculateProfitPerRes(requestnumber[i].resid) * requestnumber[i].count << " profit.\n\n";
	}

	int menustatus = 1;

	while (menustatus) {
		cout << "Enter 0 to go back: ";
		cin >> menustatus;
	}

	system("cls");
	OwnerMenu(userid);
}

/*
io functions
*/

bool isGovIDValid(int targetID) {
	char path[] = "users.txt";
	ifstream file(path);

	if (!file.is_open()) {
		cerr << "***Error opening user database.***" << endl;
		return 0;
	}

	bool found = false;

	int userid = 0, govid = 0, level = 0;

	char name[NAME_LENGTH];
	char password[NAME_LENGTH];

	while (file >> userid >> name >> govid >> level >> password) {
		if (govid == targetID) {
			found = true;
			break;
		}
	}

	file.close();

	bool isValid = !found;
	return isValid;
}

void printUserToFile(User user) {
	char path[] = "users.txt";
	ofstream file(path, ios::app);

	if (!file.is_open()) {
		cerr << "***Error opening user database.***" << endl;
		return;
	}

	file << user.id << ' ' << user.name << ' ' << user.gov_id << ' ' << user.level << ' ' << user.password << '\n';
	file.close();
}

int calculateProfitPerRes(int targetid) {
	ifstream file("resources.txt");

	if (!file.is_open()) {
		cerr << "***Error opening user database.***" << endl;
		return 0;
	}

	int profit = 0;
	int price = 0, resid = 0, type = 0, secid = 0, cost = 0, stock =0;
	char name[NAME_LENGTH];

	while (file >> resid >> name >> type >> price >> secid >> cost >> stock) {
		if (resid == targetid) {
			profit = price - cost;
			break;
		}
	}

	file.close();

	return profit;
}

void printResourceToFile(char path[], Resource res) {
	ofstream file(path, ios::app);
	file << res.id << " " << res.name << " " << res.type << " " << res.price << " " << res.sec_id << ' ' << res.cost << ' ' << res.stock << '\n';
	file.close();
}

void printSecToFile(char path[], Section sec) {
	ofstream file(path, ios::app);
	file << sec.id << " " << sec.name << " " << sec.dep_id << '\n';
	file.close();
}

void makeDepartement(char name[], int owner) {
	char path[] = "Depatement.txt";
	Departement newDep;

	copyString(newDep.name, name);
	newDep.ownerID = owner;
	newDep.id = getLastId(path) + 1; // the new id has to be +1 of the last id

	printDepToFile(path, newDep);
	cout << "***the department with the id: " << newDep.id << " has been created***\n";
}

void printDepToFile(char path[], Departement dep) {
	ofstream file(path, ios::app);

	if (!file.is_open()) {
		cerr << "***Error opening department database.***" << endl;
		return;
	}

	file << dep.id << ' ' << dep.name << ' ' << dep.ownerID << '\n';
	file.close();
}


int getLastId(char path[]) {
	ifstream file(path);
	if (!file.is_open()) {
		return 0;  // If file doesn't exist or is empty, start from ID 1
	}

	char line[LINE_LENGTH];
	char lastLine[LINE_LENGTH] = "";  // The last line

	while (file.getline(line, LINE_LENGTH)) {
		copyString(lastLine, line);  // Keep updating
	}
	file.close();

	if (lastLine[0] == '\0') {
		return 0;  // If file was empty
	}

	char id[LINE_LENGTH];
	int j = 0;
	for (int i = 0; lastLine[i] != '\0' && lastLine[i] != ' '; i++) {
		id[j] = lastLine[i]; // just get the id
		j++;
	}
	id[j] = '\0'; // so the functions work with it

	return stringToInt(id);
}


void printDepToCLI() {
	char path[] = "Depatement.txt";

	ifstream file(path);

	cout << "list of all departments: \n\n";

	int depID = 0, ownerid = 0;
	char name[NAME_LENGTH];
	while (file >> depID >> name >> ownerid) {
		printDivider();
		cout << '\t' << "name: " << name << '\t' << "owner id: " << ownerid << '\t' << "id: " << depID << "\n\n";
	}
}

void printSecToCLI(int targetDep) {
	char path[] = "sections.txt";

	ifstream file(path);

	if (!file.is_open()) {
		cerr << "***Error opening user database.***" << endl;
		return;
	}

	int secID = 0, depID = 0;
	char name[NAME_LENGTH];

	cout << "List of sections in department " << targetDep << ":\n\n";
	while (file >> secID >> name >> depID) {
		if (depID == targetDep) {
			printDivider();
			cout << '\t' << "name: " << name << '\t' << "id: " << secID << '\t' << "department id: " << depID << "\n\n";
		}
	}
}

void printResToCLI(int targetSec) {
	char path[] = "resources.txt";

	ifstream file(path);

	if (!file.is_open()) {
		cerr << "***Error opening user database.***" << endl;
		return;
	}

	cout << "list of all resources: \n\n";

	int resID = 0, secID = 0, price = 0, cost = 0, type = 0, stock = 0;
	char name[NAME_LENGTH];
	char typestr[NAME_LENGTH];

	while (file >> resID >> name >> type >> price >> secID >> cost >> stock) {
		stringForResourceType(typestr, type);

		if (secID == targetSec) {
			printDivider();
			cout << '\t' << "name: " << name << '\t'
				<< "id: " << resID << '\t' 
				<< "resource type: " << typestr << '\t' 
				<< "price: " << price << '\t'
				<< "section id: " << secID << '\t' 
				<< "stocks: " << stock << "\n\n";
		}
	}

	file.close();
}

void printRequestToFile(Request req) {
	ofstream file("requests.txt", ios::app);

	if (!file.is_open()) {
		cerr << "***Error opening user database.***" << endl;
		return;
	}

	file << req.id << ' ' << req.name << ' ' << req.isApproved << ' ' << req.resID << ' ' << req.userID << ' ' << req.intTime << '\n'; //number of request
}


void approveReqInFile(Request req) {
	ifstream inputFile("requests.txt");

	if (!inputFile.is_open()) {
		cerr << "***Error opening user database.***" << endl;
		return;
	}

	Request requests[MAX_REQUESTS];
	int i = 0;

	while (inputFile >> requests[i].id
		>> requests[i].name
		>> requests[i].isApproved
		>> requests[i].resID
		>> requests[i].userID
		>> requests[i].intTime) {
		i++;
	}
	int size = i;
	inputFile.close();

	bool found = false;
	for (int j = size - 1; j >= 0; j--) {
		if (req.id == requests[j].id) {
			requests[j].isApproved = true;
			found = true;
			break;
		}
	}
	if (!found) {
		cerr << "***Request ID not found in file.***" << endl;
		return;
	}

	ofstream outputFile("requests.txt");
	for (int l = 0; l < size; l++) {
		outputFile << requests[l].id << ' '
			<< requests[l].name << ' '
			<< requests[l].isApproved << ' '
			<< requests[l].resID << ' '
			<< requests[l].userID << ' '
			<< requests[l].intTime << '\n';
	}
	outputFile.close();

	char filename[NAME_LENGTH];
	intToStr(req.resID, filename);
	concatString(filename, txtExtension);

	ifstream inputResFile(filename);
	int availibty[MAX_REQUESTS][2];
	int k = 1;
	while (inputResFile >> availibty[k][0] >> availibty[k][1]) {
		// When we find a matching time slot, mark it as available (set to 1).
		if (availibty[k][0] == req.intTime) {
			availibty[k][1] = 1;
		}
		k++;
	}
	inputResFile.close();

	ofstream outputResFile(filename);
	for (int o = 1; o < k; o++) {
		outputResFile << availibty[o][0] << ' ' << availibty[o][1] << '\n';
	}
	outputResFile.close();
}


void getRequests(int userid, Request requests[], int& count) {
	ifstream file("requests.txt");

	if (!file.is_open()) {
		cerr << "***Error opening user database.***" << '\n';
		return;
	}

	int i = 0;
	while (file >> requests[i].id >> requests[i].name >> requests[i].isApproved >> requests[i].resID >> requests[i].userID >> requests[i].intTime) {
		i++;
	}

	count = i;

	file.close();
}

void printOwnerToFile(Owner owner) {
	char path[] = "users.txt";
	ofstream file(path, ios::app);

	if (!file.is_open()) {
		cerr << "***Error opening user database.***" << endl;
		return;
	}

	file << owner.id << ' ' << owner.name << ' ' << owner.govID << ' ' << owner.level << ' ' << owner.password << '\n';
	file.close();
}

void printReqToCLI(Request req) {
	printDivider();
	cout << "id: " << req.id << '\t' << "Request title: " << req.name << '\t' << "Resource: " << req.resID << '\t' << "Requester id: " << req.userID <<'\t' << "time: " << req.intTime << "\n\n";
}

void makeResFile(char path[], Type type) {
	ofstream file(path);
	switch (type)
	{
	case HOURLY:
		for (int i = 1; i <= HOURS_IN_YEAR; i++) {
			file << i << ' ' << 0 << '\n';
		}
		break;
	case DAILY:
		for (int i = 1; i <= DAYS_IN_YEAR; i++) {
			file << i << ' ' << 0 << '\n';
		}
		break;
	case MOUNTHLY:
		for (int i = 1; i <= MONTHS_IN_YEAR; i++) {
			file << i << ' ' << 0 << '\n';
		}
		break;
	default:
		break;
	}
	file.close();
}

int DepIDOfOwner(int targetid) {
	ifstream file("Depatement.txt");

	if (!file.is_open()) {
		cerr << "***Error opening user database.***" << endl;
		return 0;
	}

	int userid = 0, depID = 0;
	char name[NAME_LENGTH];

	while (file >> depID >> name >> userid) {
		if (userid == targetid) {
			file.close();
			return depID;
		}
	}

	file.close();
	return 0;
}

int secIDOfRes(int targetid) {
	ifstream file("resources.txt");

	if (!file.is_open()) {
		cerr << "***Error opening user database.***" << endl;
		return 0;
	}

	int resID = 0, secID = 0, price = 0, cost = 0, type = 0, stock = 0;
	char name[NAME_LENGTH];

	while (file >> resID >> name >> type >> price >> secID >> cost >> stock) {
		if (targetid == resID) {
			file.close();
			return secID;
		}
	}

	file.close();
	return 0;
}

int depIDOfsec(int targetid) {
	ifstream file("sections.txt");

	if (!file.is_open()) {
		cerr << "***Error opening user database.***" << endl;
		return 0;
	}

	int secID = 0, depID = 0;
	char name[NAME_LENGTH];

	while (file >> secID >> name >> depID) {
		if (secID == targetid) {
			file.close();
			return depID;
		}
	}

	file.close();
	return 0;
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

	if (strLen(str) < MIN_LENGTH_PASS) {
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

bool areStringsEqual(char first[], char second[]) {
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

void sortReq(reqcount reqnumber[], int count) {
	for (int i = 0; i < count - 1; i++) {
		for (int j = 0; j < count - 1 - i; j++)
			if (reqnumber[j + 1].count > reqnumber[j].count) {
				reqcount swap = reqnumber[j + 1];
				reqnumber[j + 1] = reqnumber[j];
				reqnumber[j] = swap;
			}
	}
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

Request makeReq(int id, char name[], int res_id, int userID, int time) {
	Request req;
	req.id = id;
	req.resID = res_id;
	req.userID = userID;
	copyString(req.name, name);
	req.isApproved = false;
	req.intTime = time;
	return req;
}

void reverseStr(char str[]) {
	char* start = str;

	while (*str != '\0') {
		str++;
	}
	str--;

	while (start < str) {
		char temp = *start;
		*start = *str;
		*str = temp;
		start++;
		str--;
	}
}

void intToStr(int number, char str[]) {
	int i = 0;

	if (number == 0) {
		str[i++] = '0';
		str[i] = '\0';
		return;
	}

	while (number > 0) {
		str[i++] = (number % 10) + '0';
		number /= 10;
	}

	str[i] = '\0';  // Null terminator

	reverseStr(str);
}

Time hourToTime(int absoluteHour) {
	Time time;
	time.hour = absoluteHour % HOURS_IN_DAY;

	int totalDays = absoluteHour / HOURS_IN_DAY;

	time.day = (totalDays % DAYS_IN_MONTH) + 1;

	int totalMonths = totalDays / DAYS_IN_MONTH;
	time.month = (totalMonths % MONTHS_IN_YEAR) + 1;

	return time;
}

Time dayToTime(int absoluteDay) {
	Time time;
	time.hour = 0;

	time.day = (absoluteDay % DAYS_IN_MONTH) + 1;

	int totalMonths = absoluteDay / DAYS_IN_MONTH;
	time.month = (totalMonths % MONTHS_IN_YEAR) + 1;

	return time;
}

Time monthToTime(int month) {
	Time time;
	time.month = month;
	time.day = 0;
	time.hour = 0;
	return time;
}