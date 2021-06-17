#include "storage_value.h"

void StorageValue::Add(std::string event) {
	if (s_events.insert(event).second) {
		v_events.push_back(event);
	}
}

int StorageValue::GetSize() {
	return v_events.size();
}

void StorageValue::Print(const Date& date, std::ostream& os) const {
	for (const auto& event : v_events) {
		os << date << " " << event<<std::endl;
	}
}

std::string StorageValue::Last() const {
	return v_events.back();
}