// Booking.cpp
// Member-function definitions for class Booking
#include <iostream>
#include <iomanip>
#include "Booking.h" // Booking class definition

Booking::Booking()
{
}

void Booking::setEmail( string theEmail )
{
   int length = theEmail.size();
   length = ( length < 40 ? length : 39 );
   for( int i = 0; i < length; i++ )
      email[ i ] = theEmail[ i ];
   email[ length ] = '\0';
}

string Booking::getEmail()
{
   return string( email );
}

void Booking::setMovieCode( int theMovieCode )
{
   movieCode = ( theMovieCode > 0 ? theMovieCode : 0 );
}

int Booking::getMovieCode()
{
   return movieCode;
}

void Booking::setDateCode( int theDateCode )
{
   dateCode = ( theDateCode > 0 ? theDateCode : 0 );
}

int Booking::getDateCode()
{
   return dateCode;
}

void Booking::setSessionTimeCode( int theSessionTimeCode )
{
   sessionTimeCode = ( theSessionTimeCode > 0 ? theSessionTimeCode : 0 );
}

int Booking::getSessionTimeCode()
{
   return sessionTimeCode;
}

void Booking::setNumTickets( int theNumTickets[] )
{
   for( int i = 0; i < 4; i++ )
      numTickets[ i ] = ( theNumTickets[ i ] > 0 ? theNumTickets[ i ] : 0 );
}

int Booking::getNumTickets( int ticketType )
{
   return numTickets[ ticketType ];
}

void Booking::setSeletedSeats( string theSeletedSeats[], int numSeats )
{
   for( int i = 0; i < numSeats; i++ )
   {
      seletedSeats[ i ][ 0 ] = theSeletedSeats[ i ][ 0 ];
      seletedSeats[ i ][ 1 ] = theSeletedSeats[ i ][ 1 ];
	  seletedSeats[i][2] = '\0';
   }
}

string Booking::getSeletedSeat( int number )
{
   return seletedSeats[ number ];
}

void Booking::displayBooking( MovieDatabase &movieDatabase )
{
	cout << setw(27) << "No. of Tickets" << setw(7) << "Price" << setw(10) << "Subtotal" << endl;
	if (numTickets[0] > 0)
	{
		cout << "Adult" << setw(22) << numTickets[0] << setw(7) << movieDatabase.getMovie(movieCode).getPrice(0) << setw(10) << numTickets[0] * movieDatabase.getMovie(movieCode).getPrice(0) << endl;
	}
	if (numTickets[1] > 0)
	{
		cout << "Concession ticket" << setw(10) << numTickets[1] << setw(7) << movieDatabase.getMovie(movieCode).getPrice(1) << setw(10) << numTickets[1] * movieDatabase.getMovie(movieCode).getPrice(1) << endl;
	}
	if (numTickets[2] > 0)
	{
		cout << "Disability ticket" << setw(10) << numTickets[2] << setw(7) << movieDatabase.getMovie(movieCode).getPrice(2) << setw(10) << numTickets[2] * movieDatabase.getMovie(movieCode).getPrice(2) << endl;
	}
	if (numTickets[3] > 0)
	{
		cout << "Elderly" << setw(20) << numTickets[3] << setw(7) << movieDatabase.getMovie(movieCode).getPrice(3) << setw(10) << numTickets[3] * movieDatabase.getMovie(movieCode).getPrice(3) << endl << endl;
	}
	int total = numTickets[0] * movieDatabase.getMovie(movieCode).getPrice(0) + numTickets[1] * movieDatabase.getMovie(movieCode).getPrice(1) + numTickets[2] * movieDatabase.getMovie(movieCode).getPrice(2) + numTickets[3] * movieDatabase.getMovie(movieCode).getPrice(3);
	cout << "Total Amount For Tickets: " << total << endl;
	cout << endl;
}