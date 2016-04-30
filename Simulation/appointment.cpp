#include "appointment.h"
#include "user.h"
#include "schedule.h"
#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

int Appointment::count = 0;

Appointment::Appointment(string r, string d, string t, string u, string i)
{
	reason = r;
	date = d;
	time = t;
	id = i;
	customer = u;
	count++;
}

Appointment::Appointment(string r, string d, string t, string u)
{
	reason = r;
	date = d;
	time = t;
	customer = u;
	id = to_string(count);
	count++;
}

void Appointment::edit(User *)
{
	
	int choice; 
	fstream sch; 
	sch.open("schedule.txt"); 

	cout << "Enter Appointment ID. \n"; 
	cin >> ID; 

	size_t pos; 
	while (sch.good())
	{
		
		getline(sch, line);				//Get ID from text file
		pos = line.find(ID); 
		if (pos != string::npos)		//if not found, string::npos is returned
		{
			cout << "Appointment Found!" << endl; 
			cout << "Please select the date: YY/MM/DD\n";
			cin >> date;
			a.date = date;
			cout << "Please select the time: HH:MM A(P)M\n";
			cin >> time;
			a.time = time;
			cout << "Please state the reason for your appointment:\n";
			cin >> reason;
			a.reason = reason;
			//Check for conflicts in the schedule with new date and time. 
			sch << "\n" << a.id << "\t" << a.date << "\t" << a.time << "\t" << a.reason << endl;
			cout << "Appointment Updated." << endl; 
			sch.close(); 
		}
	}

}

void Appointment::view()
{
}

void Appointment::accept()
{
}

string Appointment::getReason()
{
	return string();
}

string Appointment::getTime()
{
	return string();
}

string Appointment::getDate()
{
	return string();
}

string Appointment::getID()
{
	return string();
}
