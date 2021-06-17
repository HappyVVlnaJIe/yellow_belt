#include "phone_number.h"
#include <iostream>
enum class PhoneStates {
	CountryCode,
	CityCode,
	LocalNumber
};

PhoneNumber::PhoneNumber(const string& international_number) {
	PhoneStates current_state = PhoneStates::CountryCode;
	if (international_number[0]!='+') {
		throw std::invalid_argument("first symbol isn't '+'");
	}
	for (int i = 1; i < international_number.size();++i) {
		switch (current_state)
		{
		case PhoneStates::CountryCode:
			if (international_number[i]=='-') {
				current_state = PhoneStates::CityCode;
			}
			else {
				country_code_ += international_number[i];
			}
			break;

		case PhoneStates::CityCode:
			if (international_number[i] == '-') {
				current_state = PhoneStates::LocalNumber;
			}
			else {
				city_code_+= international_number[i];
			}
			break;

		case PhoneStates::LocalNumber:
			local_number_+= international_number[i];
			break;

		default:
			break;
		}
	}
	if (country_code_.size()<1 || city_code_.size()<1 || local_number_.size()<1) {
		throw std::invalid_argument("wrong format");
	}
}

string PhoneNumber::GetCountryCode() const{
	return country_code_;
}

string PhoneNumber::GetCityCode() const {
	return city_code_;
}

string PhoneNumber::GetLocalNumber() const {
	return local_number_;
}

string PhoneNumber::GetInternationalNumber() const {
	return '+'+country_code_+ '-' + city_code_ + '-' +local_number_;
}

