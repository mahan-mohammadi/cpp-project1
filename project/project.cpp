#include <iostream>
#include <fstream>

using namespace std;

const int NAME_LENGTH = 50;
const int LINE_LENGTH = 256;
const int MAX_REQUESTS = 100;
const int MIN_LENGTH_PASS = 8;
char txtExtension[] = ".txt";

enum Type {
	HOURLY = 1, DAILY, MOUNTHLY, SAMPLE
};

enum Acess_Level {
	ADMIN = 1, OWNER, USER
};

struct Person {
	int id;
	char name[NAME_LENGTH];
};

struct Time {
	int month;
	int day;
	int hour;
};

struct Owner {
	Person person;
	int phoneNumber;
	Acess_Level level = OWNER;
	char password[NAME_LENGTH];
};

struct User {
	Person person;
	int gov_id;
	Acess_Level level = USER;
	char password[NAME_LENGTH];
};

struct Departement {
	int id;
	char name[NAME_LENGTH];
	Owner owner;
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
	Resource res;
	User user;
	int id;
	bool isApproved = false;
	char name[NAME_LENGTH];
	Time time;
};

struct reqcount {
	int resid = -1;
	int count = 0;
};

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
void addSectionMenu(int id);
int getLastId(char path[]);
void printSecToFile(char[], Section);
int stringToInt(const char str[]);
void addResourceMenu(int id);
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
void AdminMenu();
void ViewNonApprovedReqMenu(int);
void getRequests(int, Request[], int& count);
int makeOwner();
void printOwnerToFile(Owner);
void printReqToCLI(Request);
int DepIDOfOwner(int);
int secIDOfRes(int);
int depIDOfsec(int);
void approveReqInFile(Request);
void ViewApprovedReqMenu(int);
void ReportMenu(int);
void sortReq(reqcount[], int);
int calculateProfitPerReq(int targetid);

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
		if (!file) {
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
	bool isNotValid = false;

	do {
		cout << "Enter your goverment id number: ";
		cin >> gov_id;
		isNotValid = !isGovIDValid(gov_id);
		if (isNotValid) {
			cout << "\n***this id already exist in our database***\n\n";
		}
	} while (isNotValid);

	char password[NAME_LENGTH];

	do {
		cout << "Enter a password that is atleast 8 characthers long and has both numbers and letters: ";
		cin >> password;
	} while (!isPasswordValid(password));

	int id = getLastId(path) + 1;

	user.person.id = id;
	copyString(user.person.name, name);
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
	cout << "===========================\n";
	cout << "	1. see all Department\n";
	cout << "	2. see all Section\n";
	cout << "	3. see all Resource\n";
	cout << "	4. send a Request\n";
	cout << "	5. view approved requests\n";
	cout << "	6. Go back\n";
	cout << "	0. Exit\n";
	cout << "===========================\n";

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
	cout << "	3 - View Requests\n";
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
	char name[NAME_LENGTH];

	cout << "Welcome to the Department defining menu\n\n";

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

	int phoneNumber;
	bool isNotValid = false;

	cout << "what is owners phone number: ";
	cin >> phoneNumber;

	char password[NAME_LENGTH];

	do {
		cout << "Enter a password that is atleast 8 characthers long and has both numbers and letters: ";
		cin >> password;
	} while (!isPasswordValid(password));

	int id = getLastId(path) + 1;

	owner.person.id = id;
	copyString(owner.person.name, name);
	copyString(owner.password, password);
	owner.phoneNumber = phoneNumber;

	printOwnerToFile(owner);

	system("cls");

	cout << "***your id is (" << id << "). please save it somewhere as you will need it to login***\n\n";
	return owner.person.id;
}

void addSectionMenu(int id) {
	Section section;
	char path[] = "sections.txt";

	cout << "Welcome to the section defining menu\n\n";

	//add a way to handle this
	cout << "what is the departement id of this section: ";
	cin >> section.dep_id;

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

	cout << "what is the section id of this resource: ";
	cin >> res.sec_id;

	cout << "What is resource name: ";
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

	cout << "\nwhat is the price of this resource per time/sample: ";
	cin >> res.price;

	cout << "\nwhat is the cost of this resource per time/sample for you?";
	cin >> res.cost;

	cout << "\nwhat is your stock of the resource";
	isValid = false;
	do {
		cin >> res.stock;
		if (res.stock > 0) {
			isValid = true;
		}
	} while (!isValid);

	res.id = getLastId(path) + 1;  // get an id for the request

	char idFileName[NAME_LENGTH];
	intToStr(res.id, idFileName); // convert the id to string
	concatString(idFileName, txtExtension);
	makeResFile(idFileName, res.type);

	printResourceToFile(path, res);

	system("cls");
	OwnerMenu(id);
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

//remove file reading from menu
void getSectionsMenu(int id) {
	int Choice = 1;
	char path[] = "sections.txt";

	ifstream file(path);

	cout << "list of all sections: \n\n";

	int sectionid = 0, dep_id = 0;

	char name[NAME_LENGTH];

	while (file >> sectionid >> name >> dep_id) {

		cout << '\t' << "section id: " << sectionid << '\t' << "name: " << name << '\t' << "department id: " << dep_id << "\n\n";
	}
	
	cout << "Enter 0 and enter to return back: ";
	while (Choice) {
		cin >> Choice;
	}
	system("cls");
	userMenu(id);
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
	bool isInStock = false;
	cout << "type the wanted resorce id: ";

	do {
		cin >> res_id;
		if (!isResInStock(res_id)) {
			cout << "***this resource is not in stock***\n";
			cout << "type the wanted resorce id: ";
		}
		else {
			isInStock = true;
		}
	} while (!isInStock);

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

bool isResInStock(int targetid) {
	ifstream file("resources.txt");

	if (!file.is_open()) {
		cerr << "***could not open the database***\n\n";
		return false;
	}

	int id, type, price, sec_id, cost, stock;
	char name[NAME_LENGTH];

	while (file >> id >> name >> type >> price >> sec_id >> cost >> stock) {
		if (id == targetid) {
			if (stock > 0) {
				file.close();
				return true;
			}
			else {
				file.close();
				return false;
			}
		}
	}
	file.close();
	return false;
}

void ViewNonApprovedReqMenu(int userid) {
	Request requests[MAX_REQUESTS];
	int count = 0;
	int depid = DepIDOfOwner(userid);
	int choice;

	getRequests(userid, requests, count);

	cout << "the list of unapproved requests:\n\n";
	for (int i = 0; i < count; i++) {

		int target = depIDOfsec(secIDOfRes(requests[i].res.id));
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
				if (requests[i].id == choice && !requests[i].isApproved ) {
					if (!isResInStock(requests[i].res.id)) {
						cout << "\n***this resource is not in stock***\n";
						
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

	cout << "list of all resources: \n\n";
	int id = 0 , sec_id = 0, price =0 , cost =0 , stock =0; 

	char name[NAME_LENGTH];
	int type;
	char typestr[NAME_LENGTH];

	while (file >> id >> name >> type >> price >> sec_id >> cost >> stock) {
		stringForResourceType(typestr, type);
		cout << '\t' << "name: " << name << '\t' << "id: " << id << '\t' << "resource type: " << typestr << '\t' << "price: " << price << '\t' << "section id: " << sec_id << '\t' << "stock: " << stock << "\n\n";
	}

	cout << "Enter 0 and enter to return back: ";
	while (Choice) {
		cin >> Choice;
	}
	system("cls");
	userMenu(userid);
}

//refactorable
void ViewApprovedReqMenu(int targetid) {
	ifstream file("requests.txt");

	bool isApproved;
	int reqid = 0, userid = 0, resid = 0;
	char name[NAME_LENGTH];
	while (file >> reqid >> name >> isApproved >> resid >> userid) {
		if(targetid == userid && isApproved == true)
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

		int target = depIDOfsec(secIDOfRes(requests[i].res.id));
		if (target == depid && requests[i].isApproved) {
			int resid = requests[i].res.id;
			bool found = false;
			// Check if resource already tracked
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
		cout << " resource id: " << requestnumber[i].resid << " had " << requestnumber[i].count << " requests." << '\n' << "it made " << calculateProfitPerReq(requestnumber[i].resid) * requestnumber[i].count << " profit.\n\n";
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

	file << user.person.id << ' ' << user.person.name << ' ' << user.gov_id << ' ' << user.level << ' ' << user.password << '\n';
	file.close();
}

int calculateProfitPerReq(int targetid) {
	ifstream file("resources.txt");

	int profit = 0;
	int price = 0, resid = 0, type = 0, secid = 0, cost = 0;
	char name[NAME_LENGTH];

	while (file >> resid >> name >> type >> price >> secid >> cost) {
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
	file << sec.id << " " << sec.name << " "  << " " << sec.dep_id << '\n';
	file.close();
}

void makeDepartement(char name[], int owner) {
	char path[] = "Depatement.txt";
	Departement newDep;

	copyString(newDep.name, name);
	newDep.owner.person.id = owner;
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

	file << dep.id << ' ' << dep.name << ' ' << dep.owner.person.id << '\n';
	file.close();
}


int getLastId(char path[]) {
	ifstream file(path);
	if (!file.is_open()) {
		return 0;  // If file doesn't exist or is empty, start from ID 1
	}

	char line[LINE_LENGTH];
	char lastLine[LINE_LENGTH] = "";  // The last line

	while (file.getline(line, 256)) {
		copyString(lastLine, line);  // Keep updating
	}
	file.close();

	if (lastLine[0] == '\0') {
		return 0;  // If file was empty
	}

	char id[20];
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

	int depID = 0 , ownerid =0;
	char name[NAME_LENGTH];
	while (file >> depID >> name >> ownerid) {
		cout << '\t' << "name: " << name << '\t' << "owner id: " << ownerid << '\t' << "id: " << depID << "\n\n";
	}
}

void printSecToCLI(int targetDep) {
	char path[] = "sections.txt";

	ifstream file(path);

	int secID = 0, depID = 0;
	char name[NAME_LENGTH];

	cout << "List of sections in department " << targetDep << ":\n\n";
	while (file >> secID >> name >> depID) {
		if (depID == targetDep) {
			cout << '\t' << "name: " << name << '\t' << "id: " << secID << '\t' << "department id: " << depID << "\n\n";
		}
	}
}

void printResToCLI(int targetSec) {
	char path[] = "resources.txt";

	ifstream file(path);

	cout << "list of all resources: \n\n";

	int resID = 0, secID = 0, price = 0, cost = 0 , type =0 , stock =0;
	char name[NAME_LENGTH];
	char typestr[NAME_LENGTH];

	while (file >> resID >> name >> type >> price >> secID >> cost >> stock) {
		stringForResourceType(typestr, type);

		if (secID == targetSec) {
			cout << '\t' << "name: " << name << '\t' << "id: " << resID << '\t' << "resource type: " << typestr << '\t' << "price: " << price << '\t' << "section id: " << secID << '\t' << "stocks: " << stock << "\n\n";
		}
	}

	file.close();
}

void printRequestToFile(Request req) {
	ofstream file("requests.txt", ios::app);
	file << req.id << ' ' << req.name << ' ' << req.isApproved << ' ' << req.res.id << ' ' << req.user.person.id << '\n'; //number of request
}

void approveReqInFile(Request req) {
	ifstream inputFile("requests.txt");

	if (!inputFile.is_open()) {
		cerr << "***Error opening user database.***" << endl;
		return;
	}

	Request requests[MAX_REQUESTS];
	int i = 0;

	while (inputFile >> requests[i].id >> requests[i].name >> requests[i].isApproved >> requests[i].res.id >> requests[i].user.person.id) {
		i++;
	}
	
	int size = i;

	inputFile.close();

	while (i >= 0) {
		if (req.id == requests[i].id) {
			requests[i].isApproved = true;
			break;
		}
		i--;
	}

	ofstream outputFile("requests.txt");
	for (int l = 0; l < size; l++) {
		outputFile << requests[l].id << ' ' << requests[i].name << ' ' << requests[i].isApproved << ' ' << requests[i].res.id << ' ' << requests[i].user.person.id << '\n';
	}

	outputFile.close();
}

void getRequests(int userid, Request requests[], int& count) {
	ifstream file("requests.txt");

	if (!file.is_open()) {
		cerr << "***Error opening user database.***" << '\n';
		return;
	}

	int i = 0;
	while (file >> requests[i].id >> requests[i].name >> requests[i].isApproved >> requests[i].res.id >> requests[i].user.person.id) {
		i++;
	}

	count = i;

	file.close();
}

void printOwnerToFile(Owner owner) {
	char path[] = "users.txt";
	ofstream file(path, ios::app);

	file << owner.person.id << ' ' << owner.person.name << ' ' << owner.phoneNumber << ' ' << owner.level << ' ' << owner.password << '\n';
	file.close();
}

void printReqToCLI(Request req) {
	cout << "id: " << req.id << '\t' << "Request title: " << req.name << '\t' << "Resource: " << req.res.id << '\t' << "Requester id: " << req.user.person.id << "\n\n";
}

void makeResFile(char path[] , Type type) {
	ofstream file(path);
	switch (type)
	{
		case HOURLY:
			for (int i = 0; i <= 8760; i++) {
				file << i << ' ' << 0 << '\n';
			}
			break;
		case DAILY:
			for (int i = 0; i <= 365; i++) {
				file << i << ' ' << 0 << '\n';
			}
			break;
		case MOUNTHLY:
			for (int i = 0; i <= 12; i++) {
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

	int resID = 0, secID = 0, price = 0, cost = 0, type = 0;
	char name[NAME_LENGTH];

	while (file >> resID >> name >> type >> price >> secID >> cost ) {
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
	
	int secID = 0, depID = 0;
	char name[NAME_LENGTH];

	while(file >> secID >> name >> depID) {
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

void sortReq(reqcount reqnumber[], int count) {
	for (int i = 0; i < count - 1; i++) {
		for(int j=0 ; j< count - 1 -i ; j++)
		if (reqnumber[j + 1].count > reqnumber[j].count) {
			reqcount swap = reqnumber[j + 1];
			reqnumber[j + 1] = reqnumber[j];
			reqnumber[j] = swap;
		}
	}
}

//check if changing so using is possible
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

Request makeReq(int id, char name[], int res_id, int userID) {
	Request req;
	req.id = id;
	req.res.id = res_id;
	req.user.person.id = userID;
	copyString(req.name, name);
	req.isApproved = false;
	return req;
}

// rewrite this with pointers
void reverseStr(char str[]) {
	int start = 0;
	int end = strLen(str) - 1;
	while (start < end) {
		char temp = str[start];
		str[start] = str[end];
		str[end] = temp;
		start++;
		end--;
	}
}

void intToStr(int number, char str[]) {
	int i = 0;
	int isNegative = 0;

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