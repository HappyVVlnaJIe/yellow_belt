#include "database.h"


void Database::Add(const Date& date, const std::string& event) {
	storage[date].Add(event);
}

void Database::Print(std::ostream& os) const {
	for (const auto& [key, value] : storage) {
		value.Print(key, os);
	}
}

std::pair<Date, std::string> Database::Last(const Date& date) const{
	if (storage.empty()) {
		throw std::invalid_argument("");
	}

	auto upper_it = storage.upper_bound(date);

	if (upper_it==storage.begin()) {
		throw std::invalid_argument("");
	}

	auto result = std::prev(upper_it);
	return { result->first,result->second.Last() };
}