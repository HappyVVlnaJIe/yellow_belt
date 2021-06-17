#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>


struct BusesForStopResponse {
    // Наполните полями эту структуру
    std::string stop;
    std::vector<std::string> buses;
};

std::ostream& operator << (std::ostream& os, const BusesForStopResponse& r);

struct StopsForBusResponse {
    // Наполните полями эту структуру
    std::string bus;
    std::vector<std::pair<std::string, std::vector<std::string>>> stops_to_buses;
};

std::ostream& operator << (std::ostream& os, const StopsForBusResponse& r);

struct AllBusesResponse {
    // Наполните полями эту структуру
    std::map<std::string, std::vector<std::string>> all_buses;
};

std::ostream& operator << (std::ostream& os, const AllBusesResponse& r);
