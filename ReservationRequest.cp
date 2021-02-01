


#include "ReservationRequest.h"

#include <iostream>
using namespace std;

int ReservationRequest::reservationRequestCounter = 0;

ReservationRequest::ReservationRequest(Person* person, Date* travellingDate, Station startingStation, Station destinationStation, int numSeatsRequested)
{
	if (numSeatsRequested > 0 && numSeatsRequested < 4)
	{
		this->person = new Person(*person);
		this->travellingDate = new Date(*travellingDate);
		this->startingStation = startingStation;
		this->destinationStation = destinationStation;
		this->numSeatsRequested = numSeatsRequested;
		
		//increment reservation counter and assign it to reservation request number
		this->reservationRequestNumber = ++this->reservationRequestCounter;
		
	}
	else
	{
		cout << "Reservation Request cannot be created" << endl;
		this->person = nullptr;
		this->travellingDate = nullptr;
		this->startingStation = NotSet;
		this->destinationStation = NotSet;
		this->numSeatsRequested = NULL;
		this->reservationRequestNumber = NULL;
	}
}

ReservationRequest::ReservationRequest(const ReservationRequest& reservationRequest)
{
	this->person = new Person(*(reservationRequest.person));
	this->travellingDate = new Date(*(reservationRequest.travellingDate));
	this->startingStation = reservationRequest.startingStation;
	this->destinationStation = reservationRequest.destinationStation;
	this->numSeatsRequested = reservationRequest.numSeatsRequested;
	this->reservationRequestNumber = reservationRequest.reservationRequestNumber;
}

Person* ReservationRequest::GetPerson()
{
	return this->person;
}

int ReservationRequest::GetReservationRequestNumber()
{
	return this->reservationRequestNumber;
}

Date* ReservationRequest::GetTravellingDate()
{
	return this->travellingDate;
}

int ReservationRequest::GetStartingStation()
{
	return this->startingStation;
}

int ReservationRequest::GetDestinationStation()
{
	return this->destinationStation;
}

int ReservationRequest::GetNumSeatsRequested()
{
	return this->numSeatsRequested;
}

void ReservationRequest::Print()
{
	//cout << "Print Reservation Request:" << endl;
	cout << "\tReservation Request Number: " << reservationRequestNumber << endl;
	cout << "\t\tPassenger: ";
	this->person->Print();

	cout << "\n\t\tTravelling date: ";
	this->travellingDate->Print();

	cout << "\n\t\tStarting Station: " << GetCityName(startingStation) << endl;
	
	cout << "\t\tDestination Station: " << GetCityName(destinationStation) << endl;
	
	cout << "\t\tNumber of seats requested: " << numSeatsRequested << endl;
}

string ReservationRequest::GetCityName(Station stationName)
{
	switch (stationName)
	{
		case Montreal: return "Montreal";
		case Dorval: return "Dorval";
		case Brockville: return "Brockville";
		case Kingston: return "Kingston";
		case Belleville: return "Belleville";
		case Toronto: return "Toronto";
		case NotSet: return "Station Not Set";
	}
}
