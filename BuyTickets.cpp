// BuyTickets.cpp
// Member-function definitions for class BuyTickets
#include <iostream>
#include <iomanip>
using namespace::std;
#include "BuyTickets.h" // BuyTickets class definition

extern char hours[ 17 ][ 8 ];
extern char movieNames[ 30 ][ 60 ];
extern char availableDates[ 10 ][ 12 ];
extern int numDates;
int inputAnInteger( int begin, int end );

// BuyTickets default constructor
BuyTickets::BuyTickets( MovieDatabase &theMovieDatabase, BookingDatabase &theBookingDatabase, string theEmail )
   : movieDatabase( theMovieDatabase ),
     bookingDatabase( theBookingDatabase )
{
   int length = theEmail.size();
   for( int i = 0; i < length; i++ )
      email[ i ] = theEmail[ i ];
   email[ length ] = '\0';
}

void BuyTickets::execute()
{
	movieDatabase.displaySessionTimes(movieNames, availableDates);
	Booking newBooking;
	int moviecode, datecode, timecode;
	int ticket[4];
	while (true)
	{
		cout << "\nEnter movie code (0 - 10):";
		moviecode = inputAnInteger(0, 10);
		if (moviecode != -1)
			break;
	}
	cout << endl;
	while (true)
	{
		cout << "Enter date code (0 - 3):";
		datecode = inputAnInteger(0, 3);
		if (datecode != -1)
			break;
	}
	cout << endl;
	while (true)
	{
		cout << "Enter session time code (0 - 16):";
		timecode = inputAnInteger(0, 16);
		if (movieDatabase.getMovie(moviecode).getSessionTime(timecode) == 1 && timecode != -1)
			break;
	}
	cout << endl;
	
	cout << "Movie: " << movieNames[moviecode] << endl;
	cout << "Date: " << availableDates[datecode] << endl;
	cout << "Show Time: " << hours[timecode] << endl;
	cout << "Price: Adult-" << movieDatabase.getMovie(moviecode).getPrice(0) 
		<< ", Concession-" << movieDatabase.getMovie(moviecode).getPrice(1) 
		<< ", Disability-" << movieDatabase.getMovie(moviecode).getPrice(2) 
		<< ", Elderly-" << movieDatabase.getMovie(moviecode).getPrice(3) << endl;
	
	do
	{
		while (true)
		{
			cout << "\nEnter the number of adult tickets(0 - 6) :";
			ticket[0] = inputAnInteger(0, 6);
			if (ticket[0] != -1)
				break;
		}
		while (true)
		{
			cout << "Enter the number of concession tickets(0 - 6) :";
			ticket[1] = inputAnInteger(0, 6);
			if (ticket[1] != -1)
				break;
		}
		while (true)
		{
			cout << "Enter the number of disabilty tickets(0 - 6) :";
			ticket[2] = inputAnInteger(0, 6);
			if (ticket[2] != -1)
				break;
		}
		while (true)
		{
			cout << "Enter the number of elderly tickets(0 - 6) :";
			ticket[3] = inputAnInteger(0, 6);
			if (ticket[3] != -1)
				break;
		}
		cout << endl;
	} while (ticket[0] + ticket[1] + ticket[2] + ticket[3] == 0);

	newBooking.setEmail(email);
	newBooking.setMovieCode(moviecode);
	newBooking.setDateCode(datecode);
	newBooking.setSessionTimeCode(timecode);
	newBooking.setNumTickets(ticket);
	newBooking.displayBooking(movieDatabase);
	selectSeats(newBooking);
	bookingDatabase.addBooking(newBooking);
}

void BuyTickets::selectSeats( Booking &newBooking )
{
	int numTicket = newBooking.getNumTickets(0) + newBooking.getNumTickets(1) + newBooking.getNumTickets(2) + newBooking.getNumTickets(3);

	cout << " ";
	for (int i = 65; i < 77; i++)
	{
		cout << " " << (char)i;
	}
	cout << endl;
	for (int i = 0; i < 8; i++)
	{
		cout << i << " ";
		for (int j = 0; j < 12; j++)
		{
			cout << movieDatabase.getMovie(newBooking.getMovieCode()).getOccupiedSeat(newBooking.getDateCode(), newBooking.getSessionTimeCode(), i, j) << " ";
		}
		cout << endl;
	}

	cout << "select " << numTicket << " seats (e.g. 0A): " << endl;
	string selectSeat[24];
	for (int i = 0; i < numTicket; i++)
	{
		cout << "?";
		cin >> selectSeat[i];
		char t = selectSeat[i][0] - '0';
		char k = selectSeat[i][1] - 'A';
		if (movieDatabase.getMovie(newBooking.getMovieCode()).getOccupiedSeat(newBooking.getDateCode(), newBooking.getSessionTimeCode(), t, k) == 1)
		{
			cout << "This seat bas been occupied. Please select another seat." << endl;
			i--;
		}
		else
		{
			movieDatabase.setMovieSeat(newBooking.getMovieCode(), newBooking.getDateCode(), newBooking.getSessionTimeCode(), t, k);
		}
	}
	newBooking.setSeletedSeats(selectSeat, numTicket);
	cout << endl;
	cout << "Sucessful!" << endl;
}