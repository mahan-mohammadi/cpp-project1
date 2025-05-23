// time  check if time ints are correct  add printtofile to classes functions like depid of owner need to be classified
#include <iostream>
#include <fstream>

void intToStr(int, char[]);
void concatString(char[], char[]);

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

void copyString(char[], char[]);

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
	int ownerid;

public:
	Dep() : Depid(0), ownerid(0) {
		depName[0] = '\0';
	}
	Dep(int id, char name[], int ownId) : Depid(id), ownerid(ownId) {
		copyString(depName, name);
	}

	void setDepID(int);
	void setName(char[]);
	void setOwnerid(int);
	int getOwnerid();
	int getDepID();
	void getDepName(char[]);
	void printDepToFile();
	void displayDetails() {
		cout << "Department ID: " << Depid << ", Name: " << depName
			<< ", Owner ID: " << ownerid << '\n';
	}
};

void Dep::printDepToFile() {
	ofstream file("Depatement.txt", ios::app);

	if (!file.is_open()) {
		cerr << "***Error opening department database.***" << endl;
		return;
	}

	file << Depid << ' ' << depName << ' ' << ownerid << '\n';
	file.close();
}

int Dep::getOwnerid() {
	return ownerid;
}

void Dep::setOwnerid(int id) {
	ownerid = id;
}

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
bool isPasswordValid(char[]);

class Person {
protected:
	int personid;
	char Personname[NAME_LENGTH];
	Acess_Level level;
	int govid;
	char password[NAME_LENGTH];
public:
	Person();
	Person(int, char[], Acess_Level, int, char[]);
	void getPass(char[]);
	int getPersonID();
	int getGovID();
	void getPersonName(char[]);
	void setPass(char[]);
	void setPersonid(int);
	void setPersonName(char[]);
	void setGovID(int);
	void setLevel(int);
	void setLevel(Acess_Level);
	Acess_Level getLevel();
	void printDetails();
	void printPersonToFile();
};

void Person::printPersonToFile() {
	char path[] = "users.txt";
	ofstream file(path, ios::app);

	if (!file.is_open()) {
		cerr << "***Error opening user database.***" << endl;
		return;
	}

	file << personid << ' ' << Personname << ' ' << govid << ' ' << level << ' ' << password << '\n';
	file.close();
}

void Person::printDetails() {
	cout << "ID: " << personid << ", Name: " << Personname
		<< ", Gov ID: " << govid << ", Level: " << level;
}

Acess_Level Person::getLevel() {
	return level;
}

void Person::setLevel(int level) {
	switch (level)
	{
	case ADMIN:
		this->level = ADMIN;
		break;
	case OWNER:
		this->level = OWNER;
		break;
	case USER:
		this->level = USER;
		break;
	default:
		cout << "not valid \n";
		break;
	}
}

void Person::setLevel(Acess_Level level) {
	switch (level)
	{
	case ADMIN:
		this->level = ADMIN;
		break;
	case OWNER:
		this->level = OWNER;
		break;
	case USER:
		this->level = USER;
		break;
	default:
		cout << "not valid \n";
		break;
	}
}

Person::Person(int id, char name[], Acess_Level level, int gid, char pass[]) {
	personid = id, this->level = level, govid = gid;
	copyString(password, pass);
	copyString(Personname, name);
}

Person::Person() {
	personid = 0, govid = 0, Personname[0] = '\0', password[0] = '\0';
}

void Person::getPass(char output[]) {
	copyString(output, password);
}

void Person::setPass(char input[]) {
	if (isPasswordValid(input)) {
		copyString(password, input);
	}
	else {
		cout << "***Password does not meet criteria. Not set.***" << '\n';
	}
}

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

class Owner :public Person {
public:
	Owner() : Person() {
		level = OWNER;
	}
	Owner(int id, char name[], int gid, char pass[])
		: Person(id, name, OWNER, gid, pass) {
	}
	void displayOwner();

};

void Owner::displayOwner() {
	cout << "Owner Details - ";
	cout << "ID: " << personid << ", Name: " << Personname
		<< ", Gov ID: " << govid << ", Level: " << level;
	cout << '\n';
}

class User : public Person {
public:
	User() : Person() {
		level = USER;
	};
	User(int id, char name[], int gid, char pass[]) : Person(id, name, USER, gid, pass) {};
	void displayUser();
};

void User::displayUser() {
	cout << "User Details - ";
	cout << "ID: " << personid << ", Name: " << Personname
		<< ", Gov ID: " << govid << ", Level: " << level;
	cout << '\n';

}
	
class Section {
protected:
	int sectionid;
	char secname[NAME_LENGTH];
	int depid;
public:
	Section();
	Section(int, char[], int);
	int getSectionID();
	void getSectionName(char[]);
	void setSectionName(char[]);
	void setSectionID(int);
	int getdepid();
	void setdepid(int);
	void display();
	void printSecToFile();
};

void Section::printSecToFile() {
	ofstream file("sections.txt", ios::app);

	file << sectionid << " " << secname << " " << depid << '\n';
	file.close();
}

Section::Section(int secid, char name[], int depid) {
	sectionid = secid;
	copyString(secname, name);
	this->depid = depid;
}

void Section::setdepid(int depid) {
	this->depid = depid;

}

int Section::getdepid() {
	return depid;
}

Section::Section() {
	sectionid = 0;
	depid = 0;
	secname[0] = '\0';
}

void Section::display() {
	cout << "Section ID: " << sectionid << ", Name: " << secname
		<< ", Department ID: " << depid << endl;
}

int Section::getSectionID() {
	return sectionid;
}

void Section::setSectionID(int input) {
	sectionid = input;
}

void Section::getSectionName(char output[]) {
	copyString(output, secname);
}

void Section::setSectionName(char input[]) {
	copyString(secname, input);
}

class Resource {
protected:
	int resourceid;
	char ResName[NAME_LENGTH];
	Type type;
	int price;
	int cost;
	int stock;
	int sectionid;
public:
	Resource();
	Resource(int, Type, char[], int, int, int, int);
	void getResName(char[]);
	int getResourceID();
	int getPrice();
	int getStock();
	int getCost();
	void setResourceID(int);
	void setPrice(int);
	void setStock(int);
	void setCost(int);
	void setResname(char[]);
	Type getType();
	void setType(int);
	void setType(Type);
	void setSectionid(int);
	int getSectionid();
	int profitPerRes();
	bool isAvaiable();
	void buy();
	void display();
	void operator=(Resource);
	void printResToFIle();
};

void Resource::printResToFIle() {
	ofstream file("resources.txt", ios::app);
	file << resourceid << " " << ResName << " " << type << " " << price << " " << sectionid << ' ' << cost << ' ' << stock << '\n';
	file.close();
}

void Resource::operator=(Resource next) {
	 resourceid = next.getResourceID();
	 char temp[NAME_LENGTH];
	 next.getResName(temp);
	 copyString(ResName , temp);
	 type = next.getType();
	 price = next.getPrice();
	 cost = next.getCost();
	 stock = next.getStock();
	 sectionid = next.getSectionid();
}

void Resource::display() {
	cout << "Resource ID: " << resourceid << ", Name: " << ResName
		<< ", Type: " << type << ", Price: " << price << ", Cost: " << cost
		<< ", Stock: " << stock << ", Section ID: " << sectionid << endl;
}

void Resource::buy() {
	if (stock > 0) {
		stock--;
	}
	else {
		cout << "notavaiable";
	}
}

int Resource::profitPerRes() {
	return price - cost;
}

bool Resource::isAvaiable() {
	if (stock > 0) {
		return true;
	}
	else {
		return false;
	}
}

void Resource::setType(Type type) {
	this->type = type;
}

void Resource::setSectionid(int id) {
	sectionid = id;
}

int Resource::getSectionid() {
	return sectionid;
}

Type Resource::getType() {
	return type;
}

void Resource::setType(int type) {
	switch (type)
	{
	case DAILY:
		this->type = DAILY;
		break;
	case MOUNTHLY:
		this->type = MOUNTHLY;
		break;
	case HOURLY:
		this->type = HOURLY;
		break;
	case SAMPLE:
		this->type = SAMPLE;
		break;
	default:
		cout << "invalid";
		break;
	}
}

Resource::Resource() {
	resourceid = 0, type = SAMPLE, price = 0, cost = 0, stock = 0, sectionid = 0;
	ResName[0] = '\0';
}

Resource::Resource(int resid, Type type, char name[], int price, int cost, int stock, int secid) {
	resourceid = resid, this->type = type, this->price = price, this->cost = cost, this->stock = stock, this->sectionid = secid;
	copyString(ResName, name);
}

void Resource::getResName(char output[]) {
	copyString(output, ResName);
}

void Resource::setResname(char input[]) {
	copyString(ResName, input);
}

int Resource::getResourceID() {
	return resourceid;
}

int Resource::getPrice() {
	return price;
}

int Resource::getStock() {
	return stock;
}

int Resource::getCost() {
	return cost;
}

void Resource::setResourceID(int input) {
	resourceid = input;
}

void Resource::setCost(int input) {
	cost = input;
}

void Resource::setPrice(int input) {
	price = input;
}

void Resource::setStock(int input) {
	stock = input;
}

class Date {
private:
	int Month;
	int day;
	int hour;
public:
	Date();
	Date(int,int,int);
	int getMonth();
	int getDay();
	int getHour();
	void setMonth(int);
	void setDay(int);
	void setHour(int);
	void print();
};

void Date::print() {
	cout << "Month: " << Month << "| Day: " << day << "| Hour : " << hour << '\n';
}

Date::Date() {
	Month = 0, day = 0, hour = 0;
}

Date::Date(int Month, int day, int hour) {
	this->Month = Month, this->day = day, this->hour = hour;
}

int Date::getDay() {
	return day;
}

int Date::getHour() {
	return hour;
}

int Date::getMonth() {
	return Month;
}

void Date::setMonth(int input) {
	Month = input;
}

void Date::setHour(int input) {
	hour = input;
}

void Date::setDay(int input) {
	day = input;
}

Date dayToDate(int);
Date hourToDate(int);
Date monthToDate(int);

class Request {
private:
	int reqid;
	char reqname[NAME_LENGTH];
	int resid;
	int userid;
	bool isApproved;
	int timeint;
public:
	Request();
	Request(int, char[], int, int, int);
	int getReqID();
	int getResid();
	int getUserid();
	int getTimeInt();
	void getReqName(char[]);
	void setReqName(char[]);
	void setResid(int);
	void setUserid(int);
	void setTimeint(int);
	bool getApproval();
	void setReqid(int);
	void Approve();
	void display();
	void setApproval(bool);
	void printRes();
};

void Request::printRes() {
	ofstream file("requests.txt", ios::app);

	if (!file.is_open()) {
		cerr << "***Error opening user database.***" << endl;
		return;
	}

	file << reqid << ' ' << reqname << ' ' << isApproved << ' ' << resid << ' ' << userid << ' ' << timeint << '\n';
}

void Request::setApproval(bool approval) {
	isApproved = approval;
}

void Request::display() {
	cout << "Request ID: " << reqid << ", Name: " << reqname
		<< ", Resource ID: " << resid << ", User ID: " << userid
		<< ", Approved: " << (isApproved ? "Yes" : "No")
		<< ", Time Value: " << timeint << endl;
}

void Request::setReqName(char input[]) {
	copyString(reqname, input);
}

void Request::setResid(int id) {
	resid = id;
}

void Request::setUserid(int id) {
	userid = id;
}

void Request::setTimeint(int time) {
	timeint = time;
}

int Request::getResid() {
	return resid;
}

int Request::getUserid() {
	return userid;
}

int Request::getTimeInt() {
	return timeint;
}

void Request::getReqName(char output[]) {
	copyString(output, reqname);
}

Request::Request() {
	reqid = 0, resid = 0, userid = 0, isApproved = false, timeint = 0;
	reqname[0] = '\0';
}

Request::Request(int id , char name[], int userid, int resid, int timeint) {
	reqid = id, this->userid = userid, this->resid = resid, this->timeint = timeint;
	copyString(reqname, name);
	isApproved = false;
}

void Request::setReqid(int input) {
	reqid = input;
}

int Request::getReqID() {
	return reqid;
}

bool Request::getApproval() {
	return isApproved;
}

void Request::Approve() {
	ifstream inputFile("requests.txt");

	if (!inputFile.is_open()) {
		cerr << "***Error opening user database.***" << endl;
		return;
	}

	Request requests[MAX_REQUESTS];
	int i = 0;

	int id, resid, userid, inttime;
	bool isapproved;
	char name[NAME_LENGTH];
	while (inputFile >> id
		>> name
		>> isapproved
		>> resid
		>> userid
		>> inttime) {

		requests[i] = Request(id, name, userid, resid, inttime);
		requests[i].setApproval(isapproved);
		i++;
	}
	int size = i;
	inputFile.close();

	bool found = false;
	for (int j = size - 1; j >= 0; j--) {
		if (reqid == requests[j].getReqID()) {
			requests[j].setApproval(true);
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
		char name[NAME_LENGTH];
		requests[l].getReqName(name);
		outputFile << requests[l].getReqID() << ' '
			<< name << ' '
			<< requests[l].getApproval() << ' '
			<< requests[l].getResid() << ' '
			<< requests[l].getUserid() << ' '
			<< requests[l].getTimeInt() << '\n';
	}
	outputFile.close();

	char filename[NAME_LENGTH];
	intToStr(reqid, filename);
	concatString(filename, txtExtension);

	ifstream inputResFile(filename);
	int availibty[MAX_REQUESTS][2];
	int k = 1;
	while (inputResFile >> availibty[k][0] >> availibty[k][1]) {
		// When we find a matching time slot, mark it as available (set to 1).
		if (availibty[k][0] == timeint) {
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

struct reqcount {
	int resid = -1;
	int count = 0;
};

void printTime(Date);
bool isResInStock(int);
void makeResFile(char[], Type);
void printResToCLI(int);
void OwnerMenu(int id);
void AddDepartementMenu(int id);
void makeDepartement(char[], int);
void copyString(char[], char[]);
void addSectionMenu(int);
int getLastId(char[]);
int stringToInt(const char[]);
void addResourceMenu(int);
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
bool isGovIDValid(int);
bool areStringsEqual(char[], char[]);
bool isPasswordValid(char str[]);
void AdminMenu();
void ViewNonApprovedReqMenu(int);
void getRequests(int, Request[], int&);
int makeOwner();
int getTypeOfRes(int);
void getAvailabeDates(int, bool[]);
void printReqToCLI(Request);
int DepIDOfOwner(int);
int secIDOfRes(int);
int depIDOfsec(int);
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
		cout << "Welcome to the Resoucre Management System!\n\n";
		printDivider();
		cout << "\ndo you want to:\n\n";
		cout << "\t1 - log in\n";
		cout << "\t2 - sign in\n";
		cout << "\t3 - admin menu (temp)\n";
		cout << "\t0 - exit\n\n";
		printDivider();
		cout << "\nEnter you choice number: ";
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
			valid = true;
			break;
		case 0:
			exit(0);
			valid = true;
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
	Person p;
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

	User user(id, name, gov_id, password);

	user.printPersonToFile();
	system("cls");
	cout << "***your id is (" << id << "). please save it somewhere as you will need it to login***\n\n";
	userMenu(id);
}

void AdminMenu() {
	int choice;

	cout << "welcome to The admin menu:\n";
	printDivider();
	cout << "	1 - add department\n";
	cout << "	2 - go back\n";
	cout << "	0 - exit\n";
	printDivider();
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
	cout << "your user id is " << id << endl;
	printDivider();
	cout << "	1. see all Department\n";
	cout << "	2. see all Section\n";
	cout << "	3. see all Resource\n";
	cout << "	4. send a Request\n";
	cout << "	5. view approved requests\n";
	cout << "	6. Go back\n";
	cout << "	0. Exit\n";
	printDivider();

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

	cout << "Owner menu: (Owner id is " << id << ')' << "\n";
	printDivider();
	cout << "	1 - Add Section\n";
	cout << "	2 - Add Resource\n";
	cout << "	3 - View Non approved Requests\n";
	cout << "	4 - Generate Reports\n";
	cout << "	5 - Go back\n";
	cout << "	0 - Exit\n";
	printDivider();
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

	char depname[NAME_LENGTH];
	cout << "What is the name of the Department: ";
	cin >> depname;

	int ownerid = makeOwner();

	makeDepartement(depname, ownerid);

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

	Owner owner(id, name, gov_id, password);
	owner.printPersonToFile();

	system("cls");

	cout << "***your id is (" << id << "). please save it somewhere as you will need it to login***\n\n";
	return owner.getPersonID();
}

void addSectionMenu(int id) {
	Section section;
	char path[] = "sections.txt";
	char name[NAME_LENGTH];

	cout << "Welcome to the section defining menu\n\n";

	section.setdepid(DepIDOfOwner(id));

	cout << "What is section name: ";
	cin >> name;

	section.setSectionName(name);

	section.setSectionID(getLastId(path) + 1);

	section.printSecToFile();

	system("cls");
	OwnerMenu(id);
}

void addResourceMenu(int id) {
	cout << "Welcome to the resource defining menu\n\n";
	cout << "Sections in your Department (ID: " << id << "):\n";

	char path[] = "resources.txt";
	char name[NAME_LENGTH];
	Resource res;
	int choice;
	bool isValid = false;
	int sec_id;

	cout << "what is the section id of the resource you want to add : \n";
	printSecToCLI(DepIDOfOwner(id));
	

	cout << "Enter the section id: ";
	cin >> sec_id;

	res.setSectionid(sec_id);

	cout << "What is resource name: \n";
	cin >> name;

	res.setResname(name);

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
			res.setType(HOURLY);
			break;

		case DAILY:
			isValid = true;
			res.setType(DAILY);
			break;

		case MOUNTHLY:
			isValid = true;
			res.setType(MOUNTHLY);
			break;

		case SAMPLE:
			isValid = true;
			res.setType(SAMPLE);
			break;

		default:
			cout << "***Not a valid choice. Try again.***";
			break;
		}
	}

	while (true) {
		cout << "\nwhat is the price of this resource per time/sample (it should be positive number): ";
		int price;
		cin >> price;
		if (price > 0) {
			res.setPrice(price);
			break;
		}
	}

	while (true) {
		cout << "\nwhat is the cost of this resource per time/sample for you? (it should be positive): ";
		int cost;
		cin >> cost;
		if (cost > 0) {
			res.setCost(cost);
			break;
		}
	}

	cout << "\nwhat is your stock of the resource";
	isValid = false;
	int stock;
	do {
		cin >> stock;
		if (stock > 0) {
			isValid = true;
		}
	} while (!isValid);
	res.setStock(stock);

	res.setResourceID(getLastId(path) + 1);

	char idFileName[NAME_LENGTH];
	intToStr(res.getResourceID(), idFileName);
	concatString(idFileName, txtExtension);
	makeResFile(idFileName, res.getType());

	res.printResToFIle();

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
			printTime(dayToDate(i));
		}
	}

	for (int i = 1; i <= count && count == MONTHS_IN_YEAR; i++) {
		if (availableDates[i] == 0) {
			cout << i << " Avaiable for the time ";
			printTime(monthToDate(i));
		}
	}

	for (int i = 1; i <= count && count == HOURS_IN_YEAR; i++) {
		if (availableDates[i] == 0) {
			cout << i << " Avaiable for the time ";
			printTime(hourToDate(i));
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

	Request req(id, name, res_id, userid, selectedTime);

	req.printRes();

	system("cls");
	userMenu(userid);
}

void printTime(Date date) {
	cout << "Month: " << date.getMonth() << '|' << " Day: " << date.getDay() << '|' << " Hour : " << date.getHour() << '\n';
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

	int id, price, sec_id, cost, stock;
	int tempType;
	char name[NAME_LENGTH];
	int i = 0;
	while (infile >> id 
		>> name 
		>> tempType 
		>> price
		>> sec_id 
		>> cost
		>> stock) {

		Type type = static_cast<Type>(tempType);
		resources[i] = Resource(id, type , name , price , cost , stock , sec_id );
		if (resources[i].getResourceID() == targetid) {
			if (resources[i].getStock() > 0) {
				resources[i].buy();
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
		char name[NAME_LENGTH];
		resources[j].getResName(name);
		ofile << resources[j].getResourceID() << ' ' << name << ' '
			<< resources[j].getType() << ' ' << resources[j].getPrice() << ' '
			<< resources[j].getSectionid() << ' ' << resources[j].getCost() << ' '
			<< resources[j].getStock() << '\n';
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

		int target = depIDOfsec(secIDOfRes(requests[i].getResid()));
		if (target == depid && requests[i].getApproval() == false) {
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
				if (requests[i].getReqID() == choice && !requests[i].getApproval()) {
					if (!isResInStock(requests[i].getResid())) {
						cout << "\n***this resource is not in stock***\n";
						found = true;

					}
					else {
						requests[i].Approve();
						found = true;

						system("cls");
						cout << "***request for id (" << requests[i].getReqID() << ") is approved***\n\n";
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

	printDivider();

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
	if (depid == 0) { 
		OwnerMenu(userid);
		return;
	}
	cout << "report for the department id : " << depid << endl;
	printDivider();

	getRequests(userid, requests, count);
	reqcount* requestnumber = new reqcount[count];

	for (int i = 0; i < count; ++i) {
		requestnumber[i].resid = -1; // Mark as unused initially
		requestnumber[i].count = 0;
	}

	int targetcount = 0;
	int uniqueRes = 0;

	for (int i = 0; i < count; i++) {

		int target = depIDOfsec(secIDOfRes(requests[i].getResid())); 
		if (target == depid && requests[i].getApproval()) { //  check if the depid of there resources are equal to our dep id we got erlier
			int resid = requests[i].getResid();
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

void makeDepartement(char name[], int owner) {
	char path[] = "Depatement.txt";
	Dep newDep;

	newDep.setName(name);
	newDep.setOwnerid(owner);
	newDep.setDepID(getLastId(path) + 1);

	newDep.printDepToFile();
	cout << "***the department with the id: " << newDep.getDepID() << " has been created***\n";
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

void getRequests(int userid, Request requests[], int& count) {
	ifstream file("requests.txt");

	if (!file.is_open()) {
		cerr << "***Error opening user database.***" << '\n';
		return;
	}

	int i = 0;
	int id, resid, userID, inttime;
	bool isapproved;
	char name[NAME_LENGTH];
	while (file >> id >> name >> isapproved >> resid >> userID >> inttime) {

		requests[i] = Request(id, name , userID , resid , inttime );
		requests[i].setApproval(isapproved);
		i++;
	}

	count = i;

	file.close();
}

void printReqToCLI(Request req) {
	char name[NAME_LENGTH];
	req.getReqName(name);
	printDivider();
	cout << "id: " << req.getReqID() << '\t' << "Request title: " << name << '\t' << "Resource: " << req.getResid() << '\t' << "Requester id: " << req.getUserid() <<'\t' << "time: " << req.getTimeInt() << "\n\n";
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

Date hourToDate(int absoluteHour) {
	int h = absoluteHour % HOURS_IN_DAY;
	int totalDays = absoluteHour / HOURS_IN_DAY;
	int d = (totalDays % DAYS_IN_MONTH) + 1;
	int totalMonths = totalDays / DAYS_IN_MONTH;
	int m = (totalMonths % MONTHS_IN_YEAR) + 1;
	return Date(m, d, h);
}

Date dayToDate(int absoluteDay) {
	if (absoluteDay <= 0) {
		return Date(0, 0, 0);
	}
	int zeroIndexedDay = absoluteDay - 1;
	int d = (zeroIndexedDay % DAYS_IN_MONTH) + 1;
	int totalMonths = zeroIndexedDay / DAYS_IN_MONTH;
	int m = (totalMonths % MONTHS_IN_YEAR) + 1;
	return Date(m, d, 0);
}

Date monthToDate(int monthNum) { 
	if (monthNum < 1 || monthNum > MONTHS_IN_YEAR) {
		return Date(0, 0, 0); 
	}
	return Date(monthNum, 1, 0); 
}
