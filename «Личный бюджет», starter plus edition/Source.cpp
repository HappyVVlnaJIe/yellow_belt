#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <ctime>
#include <algorithm>
#include <numeric>
struct std::tm first_day = { 0,0,0,1, 1-1, 1700 - 1900 };
struct std::tm last_day = { 0,0,0,1, 1-1, 2100 - 1900 };
const time_t FIRST_DAY = std::mktime(&first_day);
const time_t LAST_DAY = std::mktime(&last_day);
const int SECONDS_IN_DAY = 60 * 60 * 24;
//personal budgeting system
class PBS
{
public:
	PBS(int E);
	void Run();
private:
	int Q, E;
	std::vector<uint64_t> profits;
	std::vector<uint64_t> sums;
};

time_t GetDate(int numb) {
	std::string year, month, day;
	getline(std::cin, year, '-');
	getline(std::cin, month, '-');
	if (numb==1) {
		getline(std::cin, day, ' ');
	}
	else {
		getline(std::cin, day);
	}
	struct std::tm first = { 0,0,0,std::stoi(day), std::stoi(month) - 1, std::stoi(year) - 1900 };
	return std::mktime(&first);
}

PBS::PBS(int E) {
	this->E =E;
	this->profits.resize((LAST_DAY - FIRST_DAY) / 86400, 0);
	this->sums.resize((LAST_DAY - FIRST_DAY) / 86400, 0);
}

void PBS::Run() {
	std:: string s;
	getline(std::cin, s);
	for (int i = 0; i < this->E; ++i) {
		time_t date = GetDate(1);
		std::string value;
		getline(std::cin, value);
		this->profits[(date - FIRST_DAY) / SECONDS_IN_DAY] = std::stoi(value);
	}
	std::partial_sum(this->profits.begin(), this->profits.end(), this->sums.begin());
	std::cin >> this->Q;
	for (int i = 0; i < this->Q;++i) {
		time_t date1 = GetDate(1);
		time_t date2 = GetDate(2);
		auto first_index = (date1 - FIRST_DAY) / SECONDS_IN_DAY;
		auto last_index = (date2 - FIRST_DAY) / SECONDS_IN_DAY;
		if (first_index > 0) {
			std::cout<<this->sums[last_index]-this->sums[first_index-1]<<std::endl;
		}
		else {
			std::cout << this->sums[last_index] << std::endl;
		}
	}
}

int main() {
	int Q, E;
	std::cout.precision(25);
	std::cin >> E;
	PBS pbs(E);
	pbs.Run();
	return 0;
}
	