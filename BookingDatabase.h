// BookingDatabase class definition
#ifndef BOOKING_DATABASE_H
#define BOOKING_DATABASE_H

#include "vector.h"
#include "Booking.h" // Booking class definition

class BookingDatabase
{
public:
   BookingDatabase(); // calls loadBookings()

   ~BookingDatabase(); // calls saveBookings()

   // adds a booking object to the end of the vector bookings
   void addBooking( Booking newBooking );

   // returns true if there is a booking object containing specified email
   bool existingBooking( string email ); 

   void displayBookings( string email, MovieDatabase &movieDatabase );
private:
   vector< Booking > bookings; // vector of the bookings

   void loadBookings(); // loads bookings from the file Bookings.dat
   void saveBookings(); // stores bookings into the file Bookings.dat
}; // end class BookingDatabase

#endif // BOOKING_DATABASE_H