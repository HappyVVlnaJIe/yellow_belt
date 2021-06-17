#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>


struct BusesForStopResponse {
    // ��������� ������ ��� ���������
    std::string stop;
    std::vector<std::string> buses;
};

std::ostream& operator << (std::ostream& os, const BusesForStopResponse& r);

struct StopsForBusResponse {
    // ��������� ������ ��� ���������
    std::string bus;
    std::vector<std::pair<std::string, std::vector<std::string>>> stops_to_buses;
};

std::ostream& operator << (std::ostream& os, const StopsForBusResponse& r);

struct AllBusesResponse {
    // ��������� ������ ��� ���������
    std::map<std::string, std::vector<std::string>> all_buses;
};

std::ostream& operator << (std::ostream& os, const AllBusesResponse& r);
