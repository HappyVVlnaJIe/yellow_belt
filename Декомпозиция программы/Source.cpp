#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>

using namespace std;

enum class QueryType {
    NewBus,
    BusesForStop,
    StopsForBus,
    AllBuses
};

struct Query {
    QueryType type;
    string bus;
    string stop;
    vector<string> stops;
};

istream& operator >> (istream& is, QueryType& type) {
    // Реализуйте эту функцию
    string s_type;
    is >> s_type;
    if (s_type=="NEW_BUS") {
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

istream& operator >> (istream& is, Query& q) {
    // Реализуйте эту функцию
    is >> q.type;
    int stop_count;
    string stop;
    switch (q.type) {
    case QueryType::NewBus:
        is >> q.bus;
        is >> stop_count;
        q.stops.resize(stop_count);
        for (string& stop : q.stops) {
            is >> stop;
            //q.stops.push_back(stop);
        }
        break;

    case QueryType::BusesForStop:
        is >> q.stop;
        break;

    case QueryType::StopsForBus:
        is>>q.bus;
        break;

    case QueryType::AllBuses:
        break;
    }
    
    return is;
}

struct BusesForStopResponse {
    // Наполните полями эту структуру
    string stop;
    vector<string> buses;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
    // Реализуйте эту функцию
    if (r.stop=="") {
        os << "No stop"<<endl;
    }
    else {
        for (int i = 0; i < r.buses.size();++i) {
            os << r.buses[i];
            if (i != r.buses.size()) {
                os << ' ';
            }
            else {
                os << endl;
            }
        }
    }
    return os;
}

struct StopsForBusResponse {
    // Наполните полями эту структуру
    string bus;
    vector<pair<string,vector<string>>> stops_to_buses;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
    // Реализуйте эту функцию
    if (r.bus=="") {
        os << "No bus";
    }
    else {
        for (auto [stop, buses] : r.stops_to_buses) {
            os <<"Stop "<< stop <<": ";
            if (buses.size()==1) {
                os << "no interchange";
            }
            else {
                for (auto other_bus : buses) {
                    if (other_bus !=r.bus) {
                        cout << other_bus << " ";
                    }
                }
            }
            cout << endl;
        }
    }
    return os;
}

struct AllBusesResponse {
    // Наполните полями эту структуру
    map<string, vector<string>> all_buses;
};

ostream& operator << (ostream& os, const AllBusesResponse& r) {
    // Реализуйте эту функцию
    if (r.all_buses.size()==0) {
        os << "No buses";
    }
    else {
        for (auto [bus, stops] : r.all_buses) {
            os << "Bus " << bus << ":";
            for (auto stop : stops) {
                os <<' '<< stop;
            }
            os << endl;
        }

    }
    return os;
}

class BusManager {
public:
    void AddBus(const string& bus, const vector<string>& stops) {
        // Реализуйте этот метод
        buses_to_stops[bus] = stops;
        for (auto stop : stops) {
            stops_to_buses[stop].push_back(bus);
        }
    }

    BusesForStopResponse GetBusesForStop(const string& stop) const {
        // Реализуйте этот метод
        BusesForStopResponse result;
        if (stops_to_buses.find(stop)==stops_to_buses.end()) {
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

    StopsForBusResponse GetStopsForBus(const string& bus) const {
        // Реализуйте этот метод
        StopsForBusResponse result;
        if (buses_to_stops.find(bus) == buses_to_stops.end()) {
            result.bus = "";
        }
        else {
            result.bus = bus;
            for (auto stop : buses_to_stops.at(bus)) {
                result.stops_to_buses.push_back(pair<string, vector<string>>{stop, stops_to_buses.at(stop)});
            }
        }
        return result;
    }

    AllBusesResponse GetAllBuses() const {
        // Реализуйте этот метод
        AllBusesResponse result;
        result.all_buses = buses_to_stops;
        return result;
    }

private:
    map<string, vector<string>> buses_to_stops, stops_to_buses;
};

// Не меняя тела функции main, реализуйте функции и классы выше

int main() {
    int query_count;
    Query q;

    cin >> query_count;

    BusManager bm;
    for (int i = 0; i < query_count; ++i) {
        cin >> q;
        switch (q.type) {
        case QueryType::NewBus:
            bm.AddBus(q.bus, q.stops);
            break;
        case QueryType::BusesForStop:
            cout << bm.GetBusesForStop(q.stop) << endl;
            break;
        case QueryType::StopsForBus:
            cout << bm.GetStopsForBus(q.bus) << endl;
            break;
        case QueryType::AllBuses:
            cout << bm.GetAllBuses() << endl;
            break;
        }
    }

    return 0;
}