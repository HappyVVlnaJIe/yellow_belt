#pragma once

#include <iomanip>
#include <sstream>
#include <tuple>
//enum class DateParam {
//	YEAR,
//	MONTH,
//	DAY
//};

class Date {
public:
	Date(int year, int month, int day);
	Date();
	int GetYear() const;
	int GetMonth() const;
	int GetDay() const;
	/*int GetParam(const DateParam& param);*/
private:
	int Year, Month, Day;
	friend std::ostream& operator<<(std::ostream& os, const Date& date);
	friend bool operator<(const Date& lhs, const Date& rhs);
	friend bool operator>(const Date& lhs, const Date& rhs);
	friend bool operator==(const Date& lhs, const Date& rhs);
	friend bool operator!=(const Date& lhs, const Date& rhs);
	friend bool operator>=(const Date& lhs, const Date& rhs);
	friend bool operator<=(const Date& lhs, const Date& rhs);
};

Date ParseDate(std::istream& is);



