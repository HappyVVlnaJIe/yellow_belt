#pragma once

#include "date.h"
#include <map>
#include <set>
#include <vector>
#include <stdexcept>
#include "storage_value.h"

class Database {
public:
	void Add(const Date& date, const std::string& event);
	void Print(std::ostream& os) const;
	template <typename TFunc> int RemoveIf(TFunc func);
	template <typename TFunc> std::vector<std::pair<Date, std::string>> FindIf(TFunc func) const;
	std::pair<Date, std::string> Last(const Date& date) const;
private:
	//std::map<Date, std::set<std::string>> uniq_storage;
	std::map<Date, StorageValue> storage;
};

template <typename TFunc> int Database::RemoveIf(TFunc func) {
	int result = 0;
	auto it = storage.begin();
	for (;it!=storage.end();) {
		auto key = it->first;
		auto& value = it->second;
		result+=value.RemoveIf([key, func](const std::string& event) {
			return func(key, event);
		});
		it = std::next(it);
		if (value.GetSize()==0) {
			storage.erase(key);
		}
	}
	return result;
}

template <typename TFunc> std::vector<std::pair<Date, std::string>> Database::FindIf(TFunc func) const{
	std::vector<std::pair<Date, std::string>> result;
	for (auto& pair : storage) {
		auto key = pair.first;
		auto value = pair.second;
		std::vector<std::pair<Date, std::string>> current_v = value.FindIf(key, [key, func](const std::string& event) {
			return func(key, event);
		});
		result.insert(result.end(),current_v.begin(),current_v.end());
	}
	return result;
}