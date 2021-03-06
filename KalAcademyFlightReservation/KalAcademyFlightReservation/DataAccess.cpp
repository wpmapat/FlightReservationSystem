#include "stdafx.h"
#include "DataAccess.h"

namespace KalAcademyFlightReservation
{
	DataAccess::DataAccess()
	{
		if (fileExists())
		{
			mFlights = ReadFlights();
		}
	}

	std::vector<Flight*>& DataAccess::getFlights()
	{
		return mFlights;
	}

	Passenger* DataAccess::GetPassengerInformation(string passportId)
	{
		for (vector<Flight*>::const_iterator iterator = mFlights.begin(); iterator != mFlights.end(); ++iterator)
		{
			Flight* flight = *iterator;

			for (vector<Ticket*>::iterator ticketIterator = flight->getTickets().begin(); ticketIterator != flight->getTickets().end(); ++ticketIterator)
			{
				const Ticket* ticket = *ticketIterator;
				Passenger* passenger = ticket->getPassenger();
				if (passenger != NULL && passenger->getPassportId() == passportId)
				{
					return passenger;
				}
			}
		}

		return nullptr;
	}

	void DataAccess::SaveFlights()
	{
		ofstream flightFile;
		flightFile.open(filename);

		flightFile << "LastTicketNumber;" << Ticket::lastTicketNumber << "\n";

		for (vector<Flight*>::const_iterator iterator = mFlights.begin(); iterator != mFlights.end(); ++iterator)
		{
			Flight* flight = *iterator;

			flightFile << "Flight;";
			flightFile << flight->getFlightNumber() << ";";
			flightFile << flight->getCompany() << ";";
			flightFile << flight->getDepartureDateTime() << ";";
			flightFile << flight->getArrivalDateTime() << ";";
			flightFile << flight->getOrigin() << ";";
			flightFile << flight->getDestination() << ";";
			flightFile << "\n";

			for (vector<SeatDefinition*>::iterator seatDefinitionIterator = flight->getSeatDefinitions().begin(); seatDefinitionIterator != flight->getSeatDefinitions().end(); ++seatDefinitionIterator)
			{
				const SeatDefinition* seatDefinition = *seatDefinitionIterator;

				flightFile << "SeatDefinition;";
				flightFile << seatDefinition->getRowStart() << ";";
				flightFile << seatDefinition->getRowEnd() << ";";
				flightFile << seatDefinition->getSeatsPerAisle() << ";";
				flightFile << seatDefinition->getCost() << ";";
				flightFile << seatDefinition->getSeatCategory() << ";";
				flightFile << "\n";
			}

			for (vector<Ticket*>::iterator ticketIterator = flight->getTickets().begin(); ticketIterator != flight->getTickets().end(); ++ticketIterator)
			{
				const Ticket* ticket = *ticketIterator;

				flightFile << "TicketSeat;";
				const Seat& seat = *(ticket->getSeat());

				flightFile << seat.getRow() << ";";
				flightFile << seat.getAisle() << ";";
				flightFile << seat.getCost() << ";";
				flightFile << seat.getClass() << ";";
				flightFile << "\n";

				flightFile << "TicketPassenger;";
				const Passenger& passenger = *(ticket->getPassenger());

				flightFile << passenger.getFirstName() << ";";
				flightFile << passenger.getLastName() << ";";
				flightFile << passenger.getDateOfBirth() << ";";
				flightFile << passenger.getGender() << ";";
				flightFile << passenger.getAddress() << ";";
				flightFile << passenger.getPhone() << ";";
				flightFile << passenger.getEmail() << ";";
				flightFile << passenger.getPassportId() << ";";
				flightFile << "\n";

				flightFile << "Ticket;";
				flightFile << (*ticket).getTicketNumber() << ";";
				flightFile << "\n";
			}
		}

		flightFile.close();
	}

	vector<Flight*> DataAccess::ReadFlights()
	{
		vector<Flight*> flights;
		string line;
		ifstream flightFile(filename);
		if (flightFile.is_open())
		{
			Flight* flight = NULL;
			Seat* seat = NULL;
			Passenger* passenger = NULL;
			while (getline(flightFile, line))
			{
				vector<string> parts = split(line, ';');
				if (parts[0] == "Flight")
				{
					flight = new Flight(parts[1], parts[2], parts[3], parts[4], parts[5], parts[6]);
					flights.push_back(flight);
				}
				else
				{
					if (parts[0] == "SeatDefinition")
					{
						int rowStart = stoi(parts[1]);
						int rowEnd = stoi(parts[2]);
						int seatsPerAisle = stoi(parts[3]);
						int cost = stoi(parts[4]);
						SeatCategory seatClass = (SeatCategory)(stoi(parts[5]));
						SeatDefinition* seatDefinition = new SeatDefinition(rowStart, rowEnd, seatsPerAisle, cost, seatClass);
						flight->getSeatDefinitions().push_back(seatDefinition);
					}
					else
					{
						if (parts[0] == "TicketSeat")
						{
							int row = stoi(parts[1]);
							int aisle = stoi(parts[2]);
							int cost = stoi(parts[3]);
							SeatCategory seatClass = (SeatCategory)(stoi(parts[4]));

							seat = new Seat(row, aisle, cost, seatClass);
						}
						else
						{
							if (parts[0] == "TicketPassenger")
							{
								passenger = new Passenger(parts[1], parts[2], parts[3], parts[4], parts[5], parts[6], parts[7], parts[8]);
							}
							else
							{
								if (parts[0] == "Ticket")
								{
									Ticket* ticket = new Ticket(seat, passenger, parts[1]);
									flight->getTickets().push_back(ticket);
								}
								else
								{
									if (parts[0] == "LastTicketNumber")
									{
										Ticket::lastTicketNumber = stoi(parts[1]);
									}
								}
							}
						}
					}
				}
			}
			flightFile.close();
		}

		return flights;
	}

	vector<string> DataAccess::split(const string& str, const char& delim)
	{
		vector<string>result;

		size_t len = str.length();
		for (int j = 0, k = 0; j < len; j++)
		{
			if (str[j] == delim)
			{
				string ch = str.substr(k, j - k);
				k = j + 1;
				result.push_back(ch);
			}
			if (j == len - 1)
			{
				string ch = str.substr(k, j - k + 1);
				result.push_back(ch);
			}
		}
		return result;
	}

	bool DataAccess::fileExists()
	{
		ifstream file(filename);
		return file.good();
	}

	vector<Flight*> DataAccess::GetFlightSchedule(string origin, string destination, string date) const
	{
		vector<Flight*> result;

		for (vector<Flight*>::const_iterator iterator = mFlights.begin(); iterator != mFlights.end(); ++iterator)
		{
			Flight* flight = *iterator;

			if (_stricmp(flight->getOrigin().c_str(), origin.c_str()) == 0 && _stricmp(flight->getDestination().c_str(), destination.c_str()) == 0 && _stricmp(flight->getDepartureDateTime().c_str(), date.c_str()) == 0)
			{
				result.push_back(flight);
			}
		}

		return result;
	}

	//Flight* GetFlightInformation(int flightNumber);
	Flight* DataAccess::GetFlightInformation(string flightNumber) const
	{
		//Flight*  result;

		for (vector<Flight*>::const_iterator iterator = mFlights.begin(); iterator != mFlights.end(); ++iterator)
		{
			Flight* flight = *iterator;

			if (_stricmp(flight->getFlightNumber().c_str(),flightNumber.c_str()) == 0)  // _stricmp returns 0 if two strings are identical
			{
				return flight;
			}
		}

		return nullptr;
	}

	Ticket* DataAccess::GetTicketInformation(const string ticketNumber) const
	{
		for (vector<Flight*>::const_iterator iterator = mFlights.begin(); iterator != mFlights.end(); ++iterator)
		{
			Flight* flight = *iterator;
			for (vector<Ticket*>::iterator ticketIterator = flight->getTickets().begin(); ticketIterator != flight->getTickets().end(); ++ticketIterator)
			{
				Ticket* ticket = *ticketIterator;
				if (_stricmp(ticket->getTicketNumber().c_str(), ticketNumber.c_str()) == 0)
					return ticket;
			}
		}

		return nullptr;
	}
}
