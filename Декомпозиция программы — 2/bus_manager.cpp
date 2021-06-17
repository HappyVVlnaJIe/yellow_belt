#pragma once
#include "bus_manager.h"


void BusManager::AddBus(const std::string& bus, const std::vector<std::string>& stops) {
// Реализуйте этот метод
    buses_to_stops[bus] = stops;
    for (auto stop : stops) {
        stops_to_buses[stop].push_back(bus);
    }
}

BusesForStopResponse BusManager::GetBusesForStop(const std::string& stop) const {
    // Реализуйте этот метод
    BusesForStopResponse result;
    if (stops_to_buses.find(stop) == stops_to_buses.end()) {
        result.stop = "";
    }
    else {
         result.stop = stop;
         for (auto bus : stops_to_buses.at(stop)) {
            result.buses.push_back(bus);
         }
    }
    return result;
}

StopsForBusResponse BusManager::GetStopsForBus(const std::string& bus) const {
    // Реализуйте этот метод
    StopsForBusResponse result;
    if (buses_to_stops.find(bus) == buses_to_stops.end()) {
        result.bus = "";
    }
    else {
        result.bus = bus;
        for (auto stop : buses_to_stops.at(bus)) {
            result.stops_to_buses.push_back(std::pair<std::string, std::vector<std::string>>{stop, stops_to_buses.at(stop)});
        }
    }
    return result;
}

AllBusesResponse BusManager::GetAllBuses() const {
    // Реализуйте этот метод
    AllBusesResponse result;
    result.all_buses = buses_to_stops;
    return result;
}

