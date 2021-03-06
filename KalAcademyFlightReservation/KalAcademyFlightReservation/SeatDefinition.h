#pragma once
#include "SeatCategory.h"

namespace KalAcademyFlightReservation {

	class SeatDefinition
	{
	public:
		SeatDefinition() = default;
		SeatDefinition(const int rowStart, const int rowEnd, const int seatsPerAisle, int cost, SeatCategory seatCategory);
			
		const int getRowStart() const;

		const int getRowEnd() const;

		int getCost() const;

		const int getSeatsPerAisle() const;

		const SeatCategory getSeatCategory() const;

	private:
		int mRowStart;
		int mRowEnd;
		int mSeatsPerAisle;
		int mCost;
		SeatCategory mSeatCategory;
	};
}
