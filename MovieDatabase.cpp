// MovieDatabase.cpp
// Member-function definitions for class MovieDatabase
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace::std;
#include "MovieDatabase.h" // MovieDatabase class definition

extern char hours[ 17 ][ 8 ];

// MovieDatabase default constructor loads movies from the file Movies.dat
MovieDatabase::MovieDatabase()
{
   loadMovies();
}

// MovieDatabase destructor saves movies into the file Movies.dat
MovieDatabase::~MovieDatabase()
{
   saveMovies();
}

int MovieDatabase::getNumMovies()
{
   return movies.size();
}

Movie MovieDatabase::getMovie( int movieCode )
{
   return movies[ movieCode ];
}

void MovieDatabase::setMovieSeat( int movieCode, int dateCode, int sessionTimeCode, int row, int col )
{
   movies[ movieCode ].setOccupiedSeat( dateCode, sessionTimeCode, row, col );
}

void MovieDatabase::displaySessionTimes( char movieNames[][ 60 ], char availableDates[][ 12 ] )
{
	for (int j = 0; j < getNumMovies()-1; j++)
	{
		cout << j << ". " << "Movie: " << movieNames[j] << endl;
		cout << "\tDate: ";
		for (int i = 0; i < 4; i++)
		{
			if (movies[j].getDate(i) == 1)
			{
				cout << i << ". " << availableDates[i] << ",  ";
			}
		}
		cout << endl << "\tSession Time: ";
		for (int k = 0; k < sizeof(hours); k++)
		{
			if (movies[j].getSessionTime(k) == 1)
			{
				cout << k << ". " << hours[k] << ",  ";
			}
		}
		cout << endl;
	}
}

void MovieDatabase::loadMovies()
{
	ifstream movieFile;
	movieFile.open("Movies.dat", ios::in | ios::binary);
	if (!movieFile)
		cout << "Movies can not be opened." << endl;

	while (!movieFile.eof())
	{
		movies.resize(movies.size() + 1);
		movieFile.read(reinterpret_cast<char*>(&movies[movies.size()-1]), sizeof(Movie));
	}
	movieFile.close();
}

void MovieDatabase::saveMovies()
{
	ofstream outMovies("Movies.dat", ios::out | ios::binary);
	if (!outMovies)
		return;
	for (int i = 0; i < movies.size(); i++)
	{
		outMovies.write(reinterpret_cast<const char*>(&movies[i]), sizeof(Movie));
	}
	outMovies.close();
}