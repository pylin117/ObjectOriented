// MemberDatabase.cpp
// Member-function definitions for class MemberDatabase
#include <iostream>
#include <fstream>
#include "MemberDatabase.h" // MemberDatabase class definition

// MemberDatabase default constructor loads members from the file Members.dat
MemberDatabase::MemberDatabase()
{
   loadMembers();
}

// MemberDatabase destructor saves members into the file Members.dat
MemberDatabase::~MemberDatabase()
{
   saveMembers();
}

vector< Member >::iterator MemberDatabase::end()
{
   return members.end();
}

// retrieve Member object containing specified id
bool MemberDatabase::existingId( string id )
{
	vector<Member>::iterator it = members.begin();
	for (; it != members.end(); ++it)
		if (it->getIdNumber() == id)
			return true;
	return false;
} // end function existingId

// retrieve Member object containing specified email
bool MemberDatabase::existingEmail( string email )
{
	vector<Member>::iterator it = members.begin();
	for (; it != members.end(); ++it)
		if (it->getEmail() == email)
			return true;
	return false;
} // end function existingEmail

void MemberDatabase::addMember( Member newMember )
{
   members.push_back( newMember );
}

vector< Member >::iterator MemberDatabase::getMember( string email, string password )
{
	vector< Member >::iterator it = members.begin();
	for (; it != members.end(); ++it)
	{
		if (email == it->getEmail() && password == it->getPassword())
			return it;
	}
	cout << "\nSorry, unrecognized email or password." << endl << endl;
	return members.end();
}

void MemberDatabase::loadMembers()
{
	ifstream memberFile("Members.dat", ios::in | ios::binary);
	if (!memberFile)
		cout << "Member Info can not be opened." << endl;

	while (!memberFile.eof())
	{
		members.resize(members.size() + 1);
		memberFile.read(reinterpret_cast<char*>(&members[members.size()-1]), sizeof(Member));
	}
	memberFile.close();
}

void MemberDatabase::saveMembers()
{
	ofstream outMemberFile("Members.dat", ios::out | ios::binary);
	if (!outMemberFile)
		return;
	for (int i = 0; i < members.size(); i++)
	{
		outMemberFile.write(reinterpret_cast<const char*>(&members[i]), sizeof(Member));
	}
	outMemberFile.close();
}