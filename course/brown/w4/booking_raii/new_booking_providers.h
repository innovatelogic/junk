#pragma once

// Здесь будет подключён ваш файл с определением шаблонного класса Booking в пространстве имён RAII
#include "booking.h"

#include <stdexcept>
#include <string>
#include <iostream>

using namespace std;

class FlightProvider {
public:
  using BookingId = int;
  using Booking = RAII::Booking<FlightProvider>;
  friend Booking;  // Явно разрешаем функциям класса Booking вызывать private-функции нашего класса FlightProvider

  struct BookingData {
    string city_from;
    string city_to;
    string date;
  };

  Booking Book(const BookingData& data)
   {
    std::cerr << "FlightProvider : counter " << counter << " " << "capacity " << capacity << std::endl;

    if (counter >= capacity) {

      std::cerr << "Flight overbooking\n" << std::endl;
      throw runtime_error("Flight overbooking");
    }
    ++counter;

    std::cerr << "FlightProvider 2 : counter " << counter << " " << "capacity " << capacity << std::endl;

    return {this, counter};
  }

private:
  // Скрываем эту функцию в private, чтобы её мог позвать только соответствующий friend-класс Booking
  void CancelOrComplete(const Booking& booking) {
    --counter;
  }

public:
  static int capacity;
  static int counter;
};


class HotelProvider {
public:
  using BookingId = int;
  using Booking = RAII::Booking<HotelProvider>;
  friend Booking;

  struct BookingData {
    string city;
    string date_from;
    string date_to;
  };

  Booking Book(const BookingData& data) {

    std::cerr << "HotelProvider : counter " << counter << " " << "capacity " << capacity << std::endl;
    if (counter >= capacity) {
      throw runtime_error("Hotel overbooking");
    }
    ++counter;
    return {this, counter};
  }

private:
  void CancelOrComplete(const Booking& booking) {
    --counter;
  }

public:
  static int capacity;
  static int counter;
};