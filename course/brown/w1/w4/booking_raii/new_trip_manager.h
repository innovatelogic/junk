#include "new_booking_providers.h"

#include <vector>
#include <iostream>

using namespace std;

class Trip {
public:
  vector<HotelProvider::Booking> hotels;
  vector<FlightProvider::Booking> flights;

  Trip() = default;
  Trip(const Trip&) = delete;
  Trip(Trip&&) = default;

  Trip& operator=(const Trip&) = delete;
  Trip& operator=(Trip&&) = default;

  void Cancel() {
    hotels.clear();
    flights.clear();
  }
};


class TripManager {
public:
  struct BookingData {
    string city_from;
    string city_to;
    string date_from;
    string date_to;
  };

  Trip Book(const BookingData& data) 
  {
    Trip trip;
    {

      std::cout << "A" << std::endl;
      FlightProvider::BookingData data;
      trip.flights.push_back(flight_provider.Book(data));
    }
    {
      std::cout << "B" << std::endl;
      HotelProvider::BookingData data;
      trip.hotels.push_back(hotel_provider.Book(data));
    }
    {
      std::cout << "C" << std::endl;
      FlightProvider::BookingData data;
      trip.flights.push_back(flight_provider.Book(data));
    }

    std::cout << "D" << std::endl;
    return trip;
  }

  void Cancel(Trip& trip) {
    trip.Cancel();
  }

private:
  HotelProvider hotel_provider;
  FlightProvider flight_provider;
};