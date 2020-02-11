#include "phone_number.h"
#include <iostream>
#include <sstream>
#include <stdexcept>

// cl /EHsc mycode.cpp

PhoneNumber::PhoneNumber(const string &international_number)
{
    istringstream is(international_number);

    char sign = is.get();
    getline(is, country_code_, '-');
    getline(is, city_code_, '-');
    getline(is, local_number_);

    if (sign != '+' || country_code_.empty() || city_code_.empty() || local_number_.empty()) {
    throw invalid_argument("Phone number must begin with '+' symbol and contain 3 parts separated by '-' symbol: " + international_number);
    }

   /* if (international_number.empty()){
        throw std::invalid_argument("empty number");
    }

    if (international_number[0] != '+'){
        throw std::invalid_argument("invalid format not starts with \'+\'");
    }

    // find country code
    size_t next = international_number.find_first_of('-', 1);
    
    if (next == std::string::npos){
        throw std::invalid_argument("invalid country code format");
    }

    country_code_ = international_number.substr(1, next - 1);
    if (country_code_.empty()){
        throw std::invalid_argument("empty country code");
    }

    // find state code
    size_t prev = next + 1;
    next = international_number.find_first_of('-', prev);
     if (next == std::string::npos){
        throw std::invalid_argument("invalid state code format");
    }

    //std::cout << prev << ' ' << next << std::endl; 

    city_code_ = international_number.substr(prev, next - prev);
    if (city_code_.empty()){
        throw std::invalid_argument("empty state code");
    }

    // find number
    for (size_t idx = next + 1; idx < international_number.size(); ++idx)
    {
        //if (international_number[idx] != '-')
        {
            local_number_ += international_number[idx];
        }
    }

    if (local_number_.empty()){
        throw std::invalid_argument("empty number");
    }*/
    
}

string PhoneNumber::GetCountryCode() const
{
    return country_code_;
}

string PhoneNumber::GetCityCode() const
{
    return city_code_;
}

string PhoneNumber::GetLocalNumber() const
{
    return local_number_;
}

string PhoneNumber::GetInternationalNumber() const
{
    return std::string("+") + GetCountryCode() 
                            + '-' + GetCityCode()
                            + '-' + GetLocalNumber();
}


void main()
{
    PhoneNumber phone("+7-495-111-22-33");

    std::cout << phone.GetCountryCode() << std::endl;
    std::cout << phone.GetCityCode() << std::endl;
    std::cout << phone.GetLocalNumber() << std::endl;
    std::cout << phone.GetInternationalNumber() << std::endl;
}