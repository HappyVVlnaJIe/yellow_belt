#pragma once
#include "query.h"

std::istream& operator >> (std::istream& is, QueryType& type) {
    // Реализуйте эту функцию
    std::string s_type;
    is >> s_type;
    if (s_type == "NEW_BUS") {
        type = QueryType::NewBus;
    }
    if (s_type == "BUSES_FOR_STOP") {
        type = QueryType::BusesForStop;
    }
    if (s_type == "STOPS_FOR_BUS") {
        type = QueryType::StopsForBus;
    }
    if (s_type == "ALL_BUSES") {
        type = QueryType::AllBuses;
    }
    return is;
}

std::istream& operator >> (std::istream& is, Query& q) {
    // Реализуйте эту функцию
    is >> q.type;
    int stop_count;
    std::string stop;
    switch (q.type) {
    case QueryType::NewBus:
        is >> q.bus;
        is >> stop_count;
        q.stops.resize(stop_count);
        for (std::string& stop : q.stops) {
            is >> stop;
            //q.stops.push_back(stop);
        }
        break;

    case QueryType::BusesForStop:
        is >> q.stop;
        break;

    case QueryType::StopsForBus:
        is >> q.bus;
        break;

    case QueryType::AllBuses:
        break;
    }

    return is;
}
