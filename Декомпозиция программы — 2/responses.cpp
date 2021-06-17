#pragma once
#include "responses.h"

std::ostream& operator << (std::ostream& os, const BusesForStopResponse& r) {
    // Реализуйте эту функцию
    if (r.stop == "") {
        os << "No stop" << std::endl;
    }
    else {
        for (int i = 0; i < r.buses.size(); ++i) {
            os << r.buses[i];
            if (i != r.buses.size()) {
                os << ' ';
            }
            else {
                os << std::endl;
            }
        }
    }
    return os;
}

std::ostream& operator << (std::ostream& os, const StopsForBusResponse& r) {
    // Реализуйте эту функцию
    if (r.bus == "") {
        os << "No bus";
    }
    else {
        for (auto [stop, buses] : r.stops_to_buses) {
            os << "Stop " << stop << ": ";
            if (buses.size() == 1) {
                os << "no interchange";
            }
            else {
                for (auto other_bus : buses) {
                    if (other_bus != r.bus) {
                        std::cout << other_bus << " ";
                    }
                }
            }
            std::cout << std::endl;
        }
    }
    return os;
}

std::ostream& operator << (std::ostream& os, const AllBusesResponse& r) {
    // Реализуйте эту функцию
    if (r.all_buses.size() == 0) {
        os << "No buses";
    }
    else {
        for (auto [bus, stops] : r.all_buses) {
            os << "Bus " << bus << ":";
            for (auto stop : stops) {
                os << ' ' << stop;
            }
            os << std::endl;
        }

    }
    return os;
}
