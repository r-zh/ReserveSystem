


#include "ReservationManager.h"

#include <iostream>
using namespace std;

ReservationManager::ReservationManager(Date* date, int capacity, int numOfStations)
{
	if (capacity > 0 && numOfStations > 0) {
		this->travelDate = new Date(*date);
		this->capacity = capacity;
		this->numOfStations = numOfStations;
	
		this->reservationTable = new int*[capacity];
		
		for (int i = 0; i < capacity; i++)
			reservationTable[i] = new int[numOfStations];

		//initialize table arrays to 0
		for (int i = 0; i < capacity; i++)
			for (int j = 0; j < numOfStations; j++)
			reservationTable[i][j] = 0;

		this->reservationRequests = new ReservationRequest*[capacity];
		
		for (int i = 0; i < capacity; i++)
			reservationRequests[i] = nullptr;

		this->passengers = new Passenger* [capacity];

		for (int i = 0; i < capacity; i++)
			passengers[i] = nullptr;

	}
	else
	{
		cout << "Cannot create this Reservation Manager..." << endl;
		this->travelDate = nullptr;
		this->capacity = NULL;
		this->numOfStations = NULL;
	}	
}

int ReservationManager::Reserve(ReservationRequest* reservationRequest)
{

	//The solution does not require that in multiple seat requests seats  
	//should be adjacent to each other

	//create temporary array for seats numbers to reserve
	int* seats = new int[reservationRequest->GetNumSeatsRequested()];

	//initialize all seats to -1
	for (int i = 0; i < reservationRequest->GetNumSeatsRequested(); i++)
		seats[i] = -1;

	//find available seats to reserve
	for (int i = 0; i < reservationRequest->GetNumSeatsRequested(); i++)
	{
		//counter j satrts from the seat next to the previous assigned seat
		int j = (i == 0) ? 0 : seats[i - 1] + 1;

		for (j; j < this->capacity; j++)
		{
			//check if this seat is available for this route
			bool available = true;

			for (int k = reservationRequest->GetStartingStation(); k < reservationRequest->GetDestinationStation(); k++)
				if (reservationTable[j][k] != 0)
				{
					available = false;
					break;
				}

			if (available) //can reserve in this seat record
			{
				seats[i] = j;
				break;
			}
		}
	}

	//check if all seats are assigned
	for (int i = 0; i < reservationRequest->GetNumSeatsRequested(); i++)
		if (seats[i] == -1)
		{
			cout << "\nCannot process this reservation request: " << reservationRequest->GetReservationRequestNumber() << ", No available seats.\n" << endl;
			return 0;
		}

	//add reservation request number to reservation table (seats numbers in seats array)
	for (int i = 0; i < reservationRequest->GetNumSeatsRequested(); i++)
		for (int k = reservationRequest->GetStartingStation(); k < reservationRequest->GetDestinationStation(); k++)
			reservationTable[seats[i]][k] = reservationRequest->GetReservationRequestNumber();

	//Delete temporary seats array
	delete [] seats;

	//add reservation request to array (add to the first null pointer)		
	for (int i = 0; i < capacity; i++)
		if (reservationRequests[i] == nullptr)
		{
			reservationRequests[i] = new ReservationRequest(*reservationRequest);
			break;
		}

	//add passenger to array
	//check if passenger exists, add reservation request number
	for (int i = 0; i < capacity; i++)
	{
		if (passengers[i] != nullptr && passengers[i]->GetName().compare(reservationRequest->GetPerson()->GetName()) == 0)
		{
			passengers[i]->AddReservationRequest(reservationRequest->GetReservationRequestNumber());
			return reservationRequest->GetReservationRequestNumber();
		}
	}

	//passenger does not exist, add a new passenger object and add reservation request number to it
	for (int i = 0; i < capacity; i++)
	{
		if (passengers[i] == nullptr)
		{
			passengers[i] = new Passenger(reservationRequest->GetPerson());
			passengers[i]->AddReservationRequest(reservationRequest->GetReservationRequestNumber());
			return reservationRequest->GetReservationRequestNumber();
		}
	}

	cout << "\nCannot process this reservation request: " << reservationRequest->GetReservationRequestNumber() << ", No available seats.\n" << endl;
	return 0;
}

void ReservationManager::PrintReservationTable()
{
	cout << "\n------------------------------------------------------------------------------------------------------------------\n";

	cout << "Reservation Table:" << endl;

	cout << "\tSeat No.\tMontreal\tDorval  \tBrockville\tKingston\tBelleville\tToronto" << endl;
	for (int i = 0; i < this->capacity; i++)
	{
		cout << "\t" << i << "\t";
		for (int j = 0; j < this->numOfStations; j++)
			cout << "\t" << reservationTable[i][j] << "\t";
		cout << endl;
	}

	cout << "\n------------------------------------------------------------------------------------------------------------------\n";
}

void ReservationManager::PrintAllReservations()
{
	cout << "\n-----------------------------------------------------------------------------------\n";

	cout << endl << "Printing Reservation Requests:" << endl;
	for (int i = 0; i < this->capacity; i++)
		if (this->reservationRequests[i] != nullptr)
		{			
			reservationRequests[i]->Print();
			cout << endl << endl;
		}

	cout << "\n-----------------------------------------------------------------------------------\n";
}

void ReservationManager::PrintReservation(int reservationRequestNumber)
{
	cout << "\n-----------------------------------------------------------------------------------\n";

	bool found = false;

	for (int i = 0; i < this->capacity; i++)
		if (this->reservationRequests[i] != nullptr && this->reservationRequests[i]->GetReservationRequestNumber() == reservationRequestNumber)
		{
			found = true;
			cout << endl << "Printing Reservation Request:" << endl;
			reservationRequests[i]->Print();
			cout << endl;
		}

	//Print only seat numbers with this reservation request number
	cout << "\t\tSeats Reserved:";

	bool foundInTableRecord = false;

	for (int i = 0; i < this->capacity; i++)
	{
		//search if this record contains this reservation request number
		for (int j = 0; j < this->numOfStations; j++)
			if (reservationTable[i][j] == reservationRequestNumber)
			{
				foundInTableRecord = true;
				break;
			}

		if (foundInTableRecord)
		{
			foundInTableRecord = false;
			cout << " " << i << ", ";
		}

		//cout << endl;
	}

	if (!found)
		cout << "Reservation Request number: " << reservationRequestNumber << " Not Found." << endl;


	cout << "\n\n-----------------------------------------------------------------------------------\n";
}

bool ReservationManager::CancelReservation(int reservationRequestNumber)
{
	bool deletedFromReservations = false;
	
	//Delete from reservations array
	for (int i = 0; i < this->capacity; i++)
		if (this->reservationRequests[i] != nullptr && this->reservationRequests[i]->GetReservationRequestNumber() == reservationRequestNumber)
		{
			delete this->reservationRequests[i];
			this->reservationRequests[i] = nullptr;
			deletedFromReservations = true;			
		}

	//Delete from reservation table
	bool deletedFromReservationsTable = false;

	if (deletedFromReservations)
	{
		for (int i = 0; i < this->capacity; i++)
		{
			//search if this record contains this reservation request number
			for (int j = 0; j < this->numOfStations; j++)
				if (reservationTable[i][j] == reservationRequestNumber)
				{
					reservationTable[i][j] = 0;
					deletedFromReservationsTable = true;
				}
		}
	}	
	
	return (deletedFromReservationsTable);
}

bool ReservationManager::DeleteReservationsOnDate(Date* date)
{
	bool deleted = false;
	int reservationRequestNumber = 0;

	//Delete from reservations array
	for (int i = 0; i < this->capacity; i++)
		if (this->reservationRequests[i] != nullptr && DatesEqual(this->reservationRequests[i]->GetTravellingDate(), date))
		{			
			reservationRequestNumber = this->reservationRequests[i]->GetReservationRequestNumber();
			deleted = CancelReservation(reservationRequestNumber);
			
			if (deleted)
			{
				cout << "\nReservation Request Number: " << reservationRequestNumber << " deleted\n";
			}
		}

	return deleted;
}

bool ReservationManager::DeleteOlderReservations(Passenger* passenger, Date* date)
{
	bool deleted = false;
	int reservationRequestNumber = 0;

	//Delete from reservations array
	for (int i = 0; i < this->capacity; i++)
		if (this->reservationRequests[i] != nullptr
			&& this->reservationRequests[i]->GetPerson()->GetName().compare(passenger->GetName()) == 0
			&& DateOlder(this->reservationRequests[i]->GetTravellingDate(), date))
		{
			reservationRequestNumber = this->reservationRequests[i]->GetReservationRequestNumber();
			deleted = CancelReservation(this->reservationRequests[i]->GetReservationRequestNumber());
			
			if (deleted)
				cout << "\nReservation Request Number: " << reservationRequestNumber << " deleted\n";
		}

	return deleted;
}

bool ReservationManager::DatesEqual(Date* date1, Date* date2)
{
	if (date1->GetYear() == date2->GetYear() && date1->GetMonth() == date2->GetMonth() 
		&& date1->GetDay() == date2->GetDay())
		return true;
	else
		return false;
}

bool ReservationManager::DateOlder(Date* date1, Date* date2)
{
	if (date1->GetYear() < date2->GetYear())
		return true;
	else if (date1->GetYear() == date2->GetYear() && date1->GetMonth() < date2->GetMonth())
		return true;
	else if (date1->GetYear() == date2->GetYear() && date1->GetMonth() == date2->GetMonth()
		&& date1->GetDay() < date2->GetDay())
		return true;
	else
		return false;
}
