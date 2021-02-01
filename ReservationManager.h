


#pragma once

#include "Date.h"
#include "ReservationRequest.h"
#include "Passenger.h"

class ReservationManager
{
private:
	Date* travelDate;
	int capacity;
	int numOfStations;
	int** reservationTable;
	ReservationRequest** reservationRequests;
	Passenger** passengers;

	bool DatesEqual(Date* date1, Date* date2);
	bool DateOlder(Date* date1, Date* date2);

public:
	ReservationManager(Date* date, int capacity, int numOfStations);
	int Reserve(ReservationRequest* reservationRequest);
	void PrintReservationTable();
	void PrintAllReservations();
	void PrintReservation(int reservationRequestNumber);
	bool CancelReservation(int reservationRequestNumber);
	bool DeleteReservationsOnDate(Date* date);
	bool DeleteOlderReservations(Passenger* passenger, Date* date);
};
