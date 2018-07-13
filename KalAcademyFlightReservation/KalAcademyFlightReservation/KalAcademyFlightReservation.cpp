// KalAcademyFlightReservation.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Flight.h"
#include "DataAccess.h"
#include "Controller.h"
#include<time.h>
#include <windows.h> 
#include <iostream>
#include <string>

using namespace std;


using namespace KalAcademyFlightReservation;

int selection = 0;
string origin = "0";
string destination = "0",passportId,flight;
tm date ;
int traveler = 0,ticket;
string class1 = "ec",address;
char op = '0';
bool flag;
void menu();
void Reserve();
void UserInfo();
void UserRegistration();
void flightSchedule();
void flightDetail();
void TicketInformation();
void Exit();
void gotoxy(int x, int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void date_times()
{
	int aday, amonth, ayear, ahour, amin, asec;
	SYSTEMTIME t;		//pre defined in time.h header

	GetLocalTime(&t);

	aday = t.wDay, amonth = t.wMonth, ayear = t.wYear, ahour = t.wHour, amin = t.wMinute, asec = t.wSecond;
	cout << aday << ":" << amonth << ":" << ayear << ":" << ahour << ":" << amin << ":" << asec << endl;
}
Controller controller;
void TestDataAccess()
{
/*	DataAccess dataAccess;
	vector<Flight*>& flights = dataAccess.getFlights();

	flights.clear();

	Flight* flight = new Flight("Delta Airline", "7/13/2018 8:00:00", "7/13/2018 12:00:00", "NY", "Dallas");
	flights.push_back(flight);

	vector<SeatDefinition*> seatDefinitions;
	seatDefinitions.push_back(new SeatDefinition(1, 10, 5, 100, SeatCategory::Business));
	seatDefinitions.push_back(new SeatDefinition(11, 30, 5, 10, SeatCategory::Economy));
	flight->setSeatDefinitions(seatDefinitions);

	dataAccess.SaveFlights();

	bool isSeatAvailable = flight->IsSeatAvailable(1, 1, SeatCategory::Business);
	if (isSeatAvailable)
	{
		Passenger* passenger = new Passenger("firstName1", "lastName1", "dateOfBirth1", "gender1", "address1", "phone1", "email1", "passportId1");
		flight->ReserveSeat(1, 1, SeatCategory::Business, passenger);
	}
	isSeatAvailable = flight->IsSeatAvailable(1, 1, SeatCategory::Business);

	isSeatAvailable = flight->IsSeatAvailable(1, 1, SeatCategory::Economy);
	isSeatAvailable = flight->IsSeatAvailable(11, 2, SeatCategory::Economy);
	if (isSeatAvailable)
	{
		Passenger* passenger = new Passenger("firstName2", "lastName2", "dateOfBirth2", "gender2", "address2", "phone2", "email2", "passportId2");
		flight->ReserveSeat(11, 2, SeatCategory::Economy, passenger);
	}
	isSeatAvailable = flight->IsSeatAvailable(11, 2, SeatCategory::Economy);

	isSeatAvailable = flight->IsSeatAvailable(31, 1, SeatCategory::Economy);

	dataAccess.SaveFlights();

	Passenger* passenger = dataAccess.GetPassengerInformation("passportId1");
	passenger = dataAccess.GetPassengerInformation("passportId111");   */
}

int main()
{
	DataAccess dataAccess;
	vector<Flight*>& flights = dataAccess.getFlights();

	flights.clear();

	Flight* flight = new Flight("Delta Airline", "7/13/2018 8:00:00", "7/13/2018 12:00:00", "NY", "Dallas");
	flights.push_back(flight);
//	TestDataAccess();
	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int k = 3;               //color number
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;                   // Width of each character in the font
	cfi.dwFontSize.Y = 24;
	cfi.FontFamily = FF_MODERN;
	//cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = 700;

	//cfi.FontWeight = FW_NORMAL;
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);

	gotoxy(40, 1);
	date_times();
	system("color 8E");
	//SetConsoleTextAttribute(hConsole, k);
	//void locate(int x, int y);
	gotoxy(40, 5);
	cout << " Flight Reservation System" << endl;
	//system("color cc");
	gotoxy(40, 6);
	cout << "............................." << endl;



	cout << endl;
	//	passengertest();
	menu();

}

void menu()
{
	//system("cls");
	flag = true;
	cout << endl;
	selection = 0;
	cout << " Please choose from the following options - \n";
	cout << "\n\n";
	cout << " 1. Reserve a seat.\n";
	cout << " 2. Flight Schedule.\n";
	cout << " 3. Display Passenger Information.\n";
	cout << " 4. Flight Detail.\n";
	cout << " 5. User Ticket Info.\n";

	cout << " 6. Exit.\n";
	cout << "\t";
	cin >> selection;
	while (flag != false)
	{

		switch (selection)
		{
		case 1:

			Reserve();
		case 2:

			flightSchedule();

		case 3:

			UserInfo();
		case 4:

			flightDetail();
		case 5:

			TicketInformation();
		case 6:
			Exit();
		default:
			cerr << "Unknown Command" << endl;
			break;
		}
	}
}

void Reserve()
{
	system("cls");
	gotoxy(50, 10);
	//dataAccess.ReadRecord("Delta Airline");
	cout << "Book a flight " << endl;
//	PassengerDatabase passengerDatabase;
	gotoxy(10, 12);
	cout << " Please enter origin: " << endl;
	cin >> origin;
	cout << " Please enter destination - " <<endl;
	cin >> destination;
	cout << " Please enter departure date - "<< endl;

	cout << "string or tm we have to find out" << endl;
	//cin >> date;
	cout << " Please enter number of travelers: ";
	cin >> traveler;
	cout << " Please enter class: ";
	cout << "not connected to any db so put some random char" << endl;
	cin >> class1;
	cout << "list of avalaible flights \n";
	cout <<"controller.GetFlightSchedule(origin, destination, date)" <<endl;
	cout << "which flight you want to book";
	//cin<<
	cout << " Do want to continue:" <<endl; 
	cout<< " y to continue n:back to main menu" <<endl;
	cin >> op;
	if (op == 'y')
	{
		system("cls");
		UserRegistration();
	}
	else if (op == 'n')
	{
		menu();
	}
	else
		Exit();
}
 void UserRegistration()
{
	 string Fname, Lname;
	 string passportId;
	 int phoneno;

	 cout << " Please enter user First name - ";
	 cin >> Fname;
	 cout << " Please enter user Last name - ";
	 cin >> Lname;
	 cout << " Please enter Address - ";
	 cin >> address;
	 cout << " Please enter unique id/passport - ";
	 cin >> passportId;

	 if (Fname == "0" | passportId == "0") //make sure a username/password has been set
	 {
		 cout << " Invalid name/passport ";
		 Sleep(4);
		 menu();
	 }
	 else
	 {
		 cout << "  USERNAME AND PASSPORT SET.";
		cout <<" db.addPassenger(Fname, Lname, passportId, phoneno) ";
		Sleep(4);
		system("cls");
		menu();

	 }

}
 void flightSchedule()
 {
	 system("cls");
	 gotoxy(50, 10);
	 //dataAccess.ReadRecord("Delta Airline");
	 cout << "Flight Schedule: " << endl;
	 gotoxy(50, 20);
	 cout << "list of all flights \n";
	 cout << "controller.GetFlightSchedule(origin, destination, date)";
	 system("cls");
	 menu();
 }

void  UserInfo()
 {
	system("cls");
	int b;
	gotoxy(50, 10);
	//dataAccess.ReadRecord("Delta Airline");
	cout << "Inter your passport Number" << endl;
	cin >> passportId;
	gotoxy(50, 20);
	cout << "User Information: \n";
	controller.GetPassengerInformation(passportId);
	cout << "back to main menu Press 1 or to exit press any key:"<< endl;
	cin >> b;
	if (b ==1)
	{
		menu();
	}
	else
		Exit();

}
void flightDetail()
{
	system("cls");
	gotoxy(50, 10);
	cout << "Inter your flight Number" << endl;
	cin >> flight;
	cout << "controller.GetFlightInformation(flight)  need all the detail related to that flight";

}
void TicketInformation()
{
	system("cls");
	gotoxy(50, 10);
	cout << "Inter your ticket number" << endl;
	cin >> ticket;
	
	controller.GetTicketInformation(ticket);
}
void Exit()
{
	Sleep(50);
	system("color 8E");
	cout << " Thankyou for visiting !\n";
	Sleep(800);
	
	flag = false;
	
}