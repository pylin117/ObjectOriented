// BookingDatabase.cpp
// Member-function definitions for class BookingDatabase
#include <iostream>
#include <fstream>
#include "BookingDatabase.h" // BookingDatabase class definition

extern char hours[ 17 ][ 8 ];
extern char movieNames[ 30 ][ 60 ];
extern char availableDates[ 10 ][ 12 ];

// BookingDatabase default constructor loads bookings from the file Bookings.dat
BookingDatabase::BookingDatabase()
{
   loadBookings();
}

// BookingDatabase destructor saves bookings into the file Bookings.dat
BookingDatabase::~BookingDatabase()
{
   saveBookings();
}

void BookingDatabase::addBooking( Booking newBooking )
{
   bookings.push_back( newBooking );
}

// retrieve Booking object containing specified email
bool BookingDatabase::existingBooking( string email )
{
	vector<Booking>::iterator it = bookings.begin();
	for (; it != bookings.end(); ++it)
		if (it->getEmail() == email)
			return true;
	return false;
} // end function existingBooking

void BookingDatabase::displayBookings( string email, MovieDatabase &movieDatabase )
{
	cout << "Booking History: " << endl << endl;
	bool find = false;
	for (unsigned int i = 0; i < bookings.size(); i++)
	{
		if (email == bookings[i].getEmail())
		{
			int numTicket = bookings[i].getNumTickets(0) + bookings[i].getNumTickets(1) + bookings[i].getNumTickets(2) + bookings[i].getNumTickets(3);
			cout << "Movie: " << movieNames[bookings[i].getMovieCode()] << endl;
			cout << "Date: " << availableDates[bookings[i].getDateCode()] << endl;
			cout << "Show Time: " << hours[bookings[i].getSessionTimeCode()] << endl;
			cout << "Seats: ";
			for (int j = 0; j < numTicket; j++)
			{
				cout << bookings[i].getSeletedSeat(j) << "  ";
			}
			cout << endl << endl;
			bookings[i].displayBooking(movieDatabase);
			find = true;
		}
	}
	if (!find)
		cout << "No Bookings!" << endl;
}

void BookingDatabase::loadBookings()
{
	ifstream bookingFile("Bookings.dat", ios::in | ios::binary);
	if (!bookingFile)
		cout << "Booking Histories can not be opened." << endl;
	while (!bookingFile.eof())
	{
		bookings.resize(bookings.size() + 1);
		bookingFile.read(reinterpret_cast<char*>(&bookings[bookings.size()-1]), sizeof(Booking));
	}
	bookingFile.close();
}

void BookingDatabase::saveBookings()
{
	ofstream outBooking("Bookings.dat", ios::out | ios::binary);
	if (!outBooking)
		return;

	for (unsigned int i = 0; i < bookings.size(); i++)
	{
		outBooking.write(reinterpret_cast<const char*>(&bookings[i]), sizeof(Booking));
	}
	outBooking.close();
}