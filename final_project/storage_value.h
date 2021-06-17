#pragma once

#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include "date.h"

class StorageValue {
public:
	void Add(std::string event);
	template <typename TFunc> int RemoveIf(TFunc func);
	int GetSize();
	void Print(const Date& date, std::ostream& os) const;
	std::string Last() const;
	template <typename TFunc> std::vector<std::pair<Date, std::string>> FindIf(const Date& date, TFunc func);
private:
	std::vector<std::string> v_events;
	std::set<std::string> s_events;
};

template <typename TFunc> int StorageValue::RemoveIf(TFunc func) {
	int result=0;
	auto begin_it = std::stable_partition(v_events.begin(), v_events.end(), func);
	for (auto it = v_events.begin(); it != begin_it;it++) {
		s_events.erase(*it);
		result++;
	}
	v_events.erase(v_events.begin(), begin_it);
	return result;
}

template <typename TFunc> std::vector<std::pair<Date, std::string>> StorageValue::FindIf(const Date& date, TFunc func) {
	std::vector<std::pair<Date, std::string>> result;
	for (const auto& event : v_events) {
		if (func(event)) {
			result.push_back({date, event});
		}
	}
	return result;
}