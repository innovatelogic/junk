
#include <iostream>

namespace RAII
{

template<class Provider>
class Booking
{
public:
    Booking(Provider *provider, int &count)
    : m_provider(provider)
    , m_counter(&count)
    {}

    Booking(Booking&) = delete;
    
    Booking& operator=(const Booking& other) = delete;



    Booking(Booking &&other)
    {

        //std::cerr << "move ctor." << std::endl;

        m_provider = other.m_provider;
        m_counter = other.m_counter;

        other.m_provider = nullptr;
        other.m_counter = nullptr;
    }

    Booking& operator=(Booking &&other)
    {
        m_provider = other.m_provider;
        m_counter = other.m_counter;

        other.m_provider = nullptr;
        other.m_counter = nullptr;

        return *this;
    }

    ~Booking()
    {
        //std::cerr << "dtor:" << std::endl;
      //  --(*m_counter);
        if (m_counter && *m_counter > 0){
            m_provider->CancelOrComplete(*this);
        }
    }

private:
    Provider *m_provider;
    int *m_counter;

};

}

/*
#pragma once

#include <utility>

namespace RAII {

  template <typename Provider>
  class Booking {
  private:
    using BookingId = typename Provider::BookingId;

    Provider* provider;
    BookingId booking_id;

  public:
    Booking(Provider* p, const BookingId& id)
      : provider(p),
        booking_id(id)
    {
    }

    Booking(const Booking&) = delete;

    Booking(Booking&& other)
      : provider(other.provider),
        booking_id(other.booking_id)
    {
      other.provider = nullptr;
    }

    Booking& operator = (const Booking&) = delete;

    Booking& operator = (Booking&& other) {
      std::swap(provider, other.provider);
      std::swap(booking_id, other.booking_id);
      return *this;
    }

    // Эта функция не требуется в тестах, но в реальной программе она может быть нужна
    BookingId GetId() const {
      return booking_id;
    }

    ~Booking() {
      if (provider != nullptr) {
        provider->CancelOrComplete(*this);
      }
    }
  };

}

*/