// MemberDetails.cpp
// Member-function definitions for class MemberDetails
#include <iostream>
using namespace std;
#include "MemberDetails.h" // MemberDetails class definition

int inputAnInteger( int begin, int end );

MemberDetails::MemberDetails( MemberDatabase &theMemberDatabase )
   : memberDatabase( theMemberDatabase )
{
}

void MemberDetails::execute( vector< Member >::iterator it )
{
	int choice;
	it->display();
	cout << "\nWhich one do you want to modify (0 ¡V not modify)? ";
	while (true)
	{
		string tmp;
		choice = inputAnInteger(0, 6);
		if (choice != 0)
		{
			cout << "Enter correct data: ";
			cin >> tmp;
		}
		switch (choice)
		{
		case 0:
			return;
		case 1:
			it->setName(tmp);
			cout << "\nSuccessful!" << endl;
			return;
		case 2:
			if (memberDatabase.existingEmail(tmp) == true)
				return;
			it->setEmail(tmp);
			cout << "\nSuccessful!" << endl;
			return;
		case 3:
			it->setPhone(tmp);
			cout << "\nSuccessful!" << endl;
			return;
		case 4:
			if (memberDatabase.existingId(tmp) == true)
				return;
			it->setIdNumber(tmp);
			cout << "\nSuccessful!" << endl;
			return;
		case 5:
			it->setPassword(tmp);
			cout << "\nSuccessful!" << endl;
			return;
		default:
			cout << "Input Error! Please try again: ";
			break;
		}
	}
}