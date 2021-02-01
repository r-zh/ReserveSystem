//
//  COEN244, Winter 2020
//  Assignment 2
//
//  Created by Mohammed Altahat on 02/20/20.
//
//	ReservationRequest.h


#pragma once

#include "Person.h"

enum Station {
	Montreal = 0,
	Dorval = 1,
	Brockville = 2,
	Kingston = 3,
	Belleville = 4,
	Toronto = 5,
	NotSet = -1
};

class ReservationRequest
{
private:
	Person* person;
	static int reservationRequestCounter;
	int reservationRequestNumber;
	Date* travellingDate;
	Station startingStation; //0: Montreal, 1: Dorval, 2:Brockville, 3: Kingston, 4: Belleville, 5:Toronto
	Station destinationStation;
	int numSeatsRequested;

	string GetCityName(Station stationName);

public:
	//ReservationRequest();
	ReservationRequest(Person* person, Date* travellingDate, Station startingStation, Station destinationStation, int numSeatsRequested);
	ReservationRequest(const ReservationRequest& reservationRequest);
	Person* GetPerson();
	int GetReservationRequestNumber();
	Date* GetTravellingDate();
	int GetStartingStation();
	int GetDestinationStation();
	int GetNumSeatsRequested();
	void Print();
};