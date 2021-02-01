


#include "Person.h"

#include <iostream>
using namespace std;

Person::Person()
{
	this->name = "";
	this->dateOfBirth = new Date();
}

Person::Person(string name, Date* dateOfBirth)
{
	this->name = name;
	this->dateOfBirth = new Date(*dateOfBirth);
}

Person::Person(const Person& person)
{
	this->name = person.name;
	this->dateOfBirth = new Date(*(person.dateOfBirth));
}

void Person::SetName(string name)
{
	this->name = name;
}

void Person::SetDateOfBirth(Date* dateOfBirth)
{
	this->dateOfBirth->SetDate(dateOfBirth->GetMonth(), dateOfBirth->GetDay(), dateOfBirth->GetYear());
}

void Person::Print()
{
	cout << "Name: " << this->name << ", Date of birth: ";
	this->dateOfBirth->Print();
}

string Person::GetName()
{
	return this->name;
}

Date Person::GetDateOfBirth()
{
	return *(this->dateOfBirth);
}
