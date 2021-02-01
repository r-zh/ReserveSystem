


#include "Passenger.h"
#include <iostream>
using namespace std;

Passenger::Passenger()
{
	this->person = new Person();
	reservationRequestNumbers = new int[maxReservationCount];

	for (int i = 0; i < this->maxReservationCount; i++)
		this->reservationRequestNumbers[i] = NULL;
}

Passenger::Passenger(string name, Date* dateOfBirth)
{
	this->person = new Person(name, dateOfBirth);
	reservationRequestNumbers = new int[maxReservationCount];
	
	for (int i = 0; i < this->maxReservationCount; i++)	
		this->reservationRequestNumbers[i] = NULL;
		
}

Passenger::Passenger(Person* person)
{
	this->person = new Person(*person);
	reservationRequestNumbers = new int[maxReservationCount];
	
	for (int i = 0; i < this->maxReservationCount; i++)
		this->reservationRequestNumbers[i] = NULL;
}

void Passenger::SetName(string name)
{
	this->person->SetName(name);
}

void Passenger::SetDateOfBirth(Date* dateOfBirth)
{
	this->person->SetDateOfBirth(dateOfBirth);
}

string Passenger::GetName()
{
	return this->person->GetName();
}

Date Passenger::GetDateOfBirth()
{
	return this->person->GetDateOfBirth();
}

void Passenger::Print()
{
	this->person->Print();
	cout << "Reservation Request Numbers:" << endl;

	int tempCount = 0;

	for (int i = 0; i < this->maxReservationCount; i++)
	{
		if (this->reservationRequestNumbers[i] != NULL)
		{
			cout << "\t" << this->reservationRequestNumbers[i] << endl;
			tempCount++;
		}
	}
	
	if (tempCount == 0) cout << "\tNone..." << endl;

	cout << endl;
}

bool Passenger::AddReservationRequest(int reservationRequestNumber)
{
	//search if exists

	for (int i = 0; i < this->maxReservationCount; i++)
	{
		if (this->reservationRequestNumbers[i] == reservationRequestNumber)
		{
			cout << "Cannot Add Reservation Request number: " << reservationRequestNumber << ", number is added before." << endl;
			return false;
		}
	}

	for (int i = 0; i < this->maxReservationCount; i++)
	{
		if (this->reservationRequestNumbers[i] == NULL)
		{
			this->reservationRequestNumbers[i] = reservationRequestNumber;
			return true;
		}
	}
	
	cout << "Cannot Add Reservation Request number: " << reservationRequestNumber << endl;
	return false;
}

bool Passenger::DeleteReservationRequest(int reservationRequestNumber)
{
	for (int i = 0; i < this->maxReservationCount; i++)
	{
		if (this->reservationRequestNumbers[i] == reservationRequestNumber)
		{
			this->reservationRequestNumbers[i] = NULL;
			return true;
		}
	}

	return false;
}
