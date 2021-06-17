#include "date.h"

Date::Date(int year, int month, int day) : Year(year), Month(month), Day(day) {};
Date::Date() : Year(1), Month(1), Day(1) {};

//int Date::GetParam(const DateParam& param) {
//	switch (param)
//	{
//	case DateParam::YEAR:
//		return Year;
//
//	case DateParam::MONTH:
//		return Month;
//
//	case DateParam::DAY:
//		return Day;
//
//	default:
//		break;
//	}
//}

Date ParseDate(std::istream& is) {
	int year, month, day;
	is >> year;
	is.ignore(1);
	is >> month;
	is.ignore(1);
	is >> day;
	return Date(year,month, day);
}

int Date::GetYear() const{
	return Year;
}

int Date::GetMonth() const {
	return Month;
}

int Date::GetDay() const {
	return Day;
}

std::ostream& operator<<(std::ostream& os, const Date& date) {
	os << std::setfill('0');
	os << std::setw(4) << date.Year << '-' << std::setw(2) <<date.Month << '-' << std::setw(2) << date.Day;
	return os;
}

bool operator<(const Date& lhs, const Date& rhs) {
	return std::tie(lhs.Year, lhs.Month, lhs.Day) < std::tie(rhs.Year, rhs.Month, rhs.Day);
}


bool operator>(const Date& lhs, const Date& rhs) {
	return std::tie(lhs.Year, lhs.Month, lhs.Day) > std::tie(rhs.Year, rhs.Month, rhs.Day);
}

bool operator==(const Date& lhs, const Date& rhs) {
	return std::tie(lhs.Year, lhs.Month, lhs.Day) == std::tie(rhs.Year, rhs.Month, rhs.Day);
}

bool operator!=(const Date& lhs, const Date& rhs) {
	return std::tie(lhs.Year, lhs.Month, lhs.Day) != std::tie(rhs.Year, rhs.Month, rhs.Day);
}

bool operator<=(const Date& lhs, const Date& rhs) {
	return std::tie(lhs.Year, lhs.Month, lhs.Day) <= std::tie(rhs.Year, rhs.Month, rhs.Day);
}

bool operator>=(const Date& lhs, const Date& rhs) {
	return std::tie(lhs.Year, lhs.Month, lhs.Day) >= std::tie(rhs.Year, rhs.Month, rhs.Day);
}