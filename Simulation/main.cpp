#define _CRT_SECURE_NO_WARNINGS
#include    <iostream>
#include	<fstream>
#include <string.h>
#include <sstream>
#include	"appointment.h"
#include	"schedule.h"
#include	"db.h"

using namespace std;

void setup(DB *, Schedule *);					//Loads users and appointments
void save(DB *, Schedule *);					//Saves users and appointments
User * login();									//Allows a customer access, returns pointer to a user object
User * signup(DB *db);								//Allows a user to sign up and then gain access, returns pointer to a user object
bool checkUsername(DB*, string);
bool checkPassword(char*);

int main()
{
	int choice = 1;								//originally 1 so it enters the while loop the first time
	User *u = 0;
	DB *db = new DB();
	Schedule *sch = new Schedule();
	setup(db, sch);

	cout << "Would you like to log in or sign up";
	cout << "\t1. Login";
	cout << "\t2. Sign up";
	cin >> choice;

	if (choice == 1)
		u = login();
	else
        u = signup(db);


	if (!u)										//if login/signup fails, terminate
	{
		return 0;
	}

	do
	{
		if (choice == 6)
		{
			break;								// terminate loop when the user selects 6
		}

		switch (choice)
		{
		case 3:
			{
				string d, t, r;
				bool taken = false;

				cout << "Please select the date: YY/MM/DD\n";
				cin >> d;
				cout << "Please select the time: HH:MM A(P)M\n";
				cin >> t;
				cout << "Please state the reason for your appointment:\n";
				cin >> r;
				for (vector<Appointment *>::iterator it; it != sch->getSchedule().end(); it++)
				{
					if (d.compare((*it)->getDate()) == 0 && t.compare((*it)->getTime()) == 0)
					{
						cout << "Time and date taken!";
						taken = true;
					}
				}
				if (!taken)
				{
					sch->getSchedule().push_back(new Appointment(r, d, t, u->getUsername()));
				}
				else
				{
					cout << "Unable to create appointment!";
				}
			};
			break;
		case 4:
			//viewAppointment(u);
			break;
		case 5:
			void viewUsersAppointments(User *){
				cout <"Enter username to view appointments">
					cin >> choice
					string user = User.getUsername();
				if (choice != user){}
				else (
					string reason = Appointment.getReason();
				string time = Appointment.getTime();
				string date = Appointment.getDate();
				string  ID = Appointment.getID();
				cout << "Appointment details:" reason, time, date, ID >> ;
				)

			}
			//viewAppointments(u);				//the difference here is an 's', be careful
			break;
		case 6:
			//editAppointment(u);
			break;
		case 7:
			//if (u->getPriviledge() != "1")	
			//	viewSchedule();
			break;
		case 8:
			//if (u->getPriviledge() != "1")
			//	acceptAppointment(u)
			break;
			default:break;
		}

		cout << "Please select an option to continue:\n";
		cout << "\t1. Display options\n";
		cout << "\t2. Exit\n";
		cout << "\t3. Make an appointment\n";
		cout << "\t4. View an appointment\n";
		cout << "\t5. View my appointments\n";
		cout << "\t6. Edit an appointment\n";
		if (u->getPrivilege().compare("1") == 0)			//if the user is not a customer
		{
			cout << "\t7. View schedule";
			cout << "\t8. Accept appointment";
		}

	} while (cin >> choice);
	
	//save(db, sch);
	
	return 0;
}

void setup(DB *db, Schedule *sch)
{
	//read in users and appointments from appropriate txt files
	ifstream infile_users;
	ifstream infile_appts;
	string user;
	string appt;

	string n, pw, p, un;						//User's name, password, privilege, and username
	unsigned long b;
    unsigned long e;

    infile_users.open("users.txt");				//Open users file
	if (infile_users)
	{
		while (getline(infile_users, user)){
			b = e = 0;

			e = user.find(':');					//Colon as delimiter
			n = user.substr(b, e - 1);
			b = e + 1;
			user = user.substr(e + 1);

			e = user.find(':');
			pw = user.substr(b, e - 1);
			b = e + 1;
			user = user.substr(e + 1);

			p = user[e];						//Privilege is one charactor
			b = e + 2;

			//un = user.substr(b);

			db->users.push_back(new User(n, pw, p, un));
		}
	}
	else										//The program will not crash if the file isn't found.
	{
		cerr << "File could not be found.\n";
	}
	infile_users.close();

	string r, d, t, id, u;						//Appointment reason, date, time, id, username

	infile_appts.open("appts.txt");				//Open file
	if (infile_appts)
	{
		while (getline(infile_appts, appt)){
			b = e = 0;

			e = user.find("^#$");				//^#$ as delimiter
			r = user.substr(b, e - 1);
			b = e + 1;
			user = user.substr(e + 1);

			e = user.find("^#$");
			d = user.substr(b, e - 1);
			b = e + 1;
			user = user.substr(e + 1);

			e = user.find("^#$");
			t = user.substr(b, e - 1);
			b = e + 1;
			user = user.substr(e + 1);

			e = user.find("^#$");
			u = user.substr(b, e - 1);
			b = e + 1;
			user = user.substr(e + 1);

			id = user.substr(b);

			sch->add(new Appointment(r, d, t, u, id));
		}
	}
	else
	{
		cerr << "File could not be found.\n";
	}
	infile_users.close();
}

void save(DB *db, Schedule *sch)
{
	ofstream outfile_users;
	outfile_users.open("users.txt");
	vector<User *>::iterator it;
	for (it = db->users.begin(); it != db->users.end(); it++)
	{
		outfile_users << (*it)->getName() << ":" << (*it)->getPassword() << ":" << (*it)->getPrivilege() << ":" << (*it)->getUsername() << "\n";
	}
	outfile_users.close();

	ofstream outfile_appts;
	outfile_appts.open("appts.txt");
	vector<Appointment *>::iterator iter;
	for (iter = sch->getSchedule().begin(); iter != sch->getSchedule().end(); iter++)
	{
		outfile_appts << (*iter)->getReason() << "^#$" << (*iter)->getDate() << "^#$" << (*iter)->getTime() << "^#$" << (*iter)->getCustomer() << (*iter)->getID() << "\n";
	}
	outfile_appts.close();
}

User * login()
{
    string name;
    string username;
    string password;
    string privilege;

    cout << "Please enter your username" << endl;
    cin >> username;
    cout << "Please enter your password" << endl;
    cin >> password;

    if (username.empty() || password.empty()) {
        cout << "Invalid username/password" << endl;
        exit(0);
    }

    ifstream file;
    // Need to change the file path to whatever location you have the users.txt saved.
    file.open("/home/circleupx/ClionProjects/pose/Simulation/users.txt");
    string line;

    while (getline(file, line)) {
        stringstream linestream(line);
        string foundusername;
        string foundpassword;
        string value;

        while (getline(linestream, value, ':')) {
            if (value == password) {
                foundpassword = value;
            }
            if (value == username) {
                foundusername = value;
            }
        }
        if (foundusername == "" || foundpassword == "") {
            cout << "Invalid user information, closing program" << endl;
            return 0;
        }
        else
            cout << "\nWelcome " << foundusername << '\n' << endl;
        cout << "Please select one of the following option to continue\n" << endl;

    }
    file.close();

    User *something;
    return something;


}

User * signup(DB* db)
{
	bool valid = false;
	bool isTaken = false;
	char *password = (char *) "";
	string name, username, spassword, privledge = "1";
	cout << "Please type in your full name." << endl;
	cin.ignore();
	getline(cin, name);
	do {
		cout << "Please type in your desired username." << endl;
		cin >> username;
		isTaken = checkUsername(db, username);
		if (username.find('\\') != std::string::npos)
		{
			cout << "Your username contains an invalid character! (\\)" << endl;
			isTaken = true;
		}
	} while (isTaken);
	do {
		cout << "Please type in your desired password. \nYour password must contain at least 5 characters and must \n"
                        "consist of at least one lower case letter, one uppercase letter, and one number." << endl;
		password = new char[30];
		cin >> password;
		valid = checkPassword(password);
	} while (!valid);
	spassword = string(password);
	User* newUser = new User(name, username, spassword, privledge);
	db->users.push_back(newUser);
	cout << "Welcome! You have been added to our database." << endl;
	delete[] password;
	return newUser;
}

bool checkUsername(DB* db, string username)
{
	bool isTaken = false;
	vector<User *>::iterator it;
	for (it = db->users.begin(); it != db->users.end(); it++)
	{
		if (username == (*it)->getUsername())
		{
			cout << "That username is already taken. Please select another.";
			isTaken = true;
			return isTaken;
		}
	}
	isTaken = false;
	return isTaken;
}

bool checkPassword(char* password)
{
	bool validlen = false, aUpper = false, aLower = false, aDigit = false;	
	size_t length;
	length = strlen(password);
    validlen = length >= 5;
	for (int i = 0; password[i]; i++)
	{
		if (isupper(password[i]))
		{
			aUpper = true;
		}
		else if (islower(password[i]))
		{
			aLower = true;
		}
		else if (isdigit(password[i]))
		{
			aDigit = true;
		}
	}
	if (aUpper && aLower && aDigit && validlen)
	{
		return true;
	}
	else
	{
		if (!validlen)
		{
			cout << "Your password is not a valid length!" << endl;
		}
		if (!aUpper)
		{
			cout << "Your password does not contain an uppercase letter!" << endl;
		}
		if (!aLower)
		{
			cout << "Your password does not contain a lower case letter!" << endl;
		}
		if (!aDigit)
		{
			cout << "Your password does not contain a number!" << endl;
		}
		return false;
	}
}
