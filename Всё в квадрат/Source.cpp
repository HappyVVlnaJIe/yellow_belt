#include <vector>
#include <map>
#include <iostream>

using namespace std;

template<typename T> T Sqr(T x);

template <typename First, typename Second> pair<First, Second> Sqr(pair<First, Second> p);

template <typename T> vector<T> Sqr(vector<T> v);

template <typename Key, typename Value> map<Key, Value> Sqr(map<Key, Value> m);

template<typename T> T Sqr(T x) {
	return x*x;
}

template <typename First, typename Second> pair<First, Second> Sqr(pair<First, Second> p) {
	pair<First, Second> result;
	//int f = Sqr(p.first), s = Sqr(p.second);
	result.first = Sqr(p.first);
	result.second = Sqr(p.second);
	return result;
}

template <typename T> vector<T> Sqr(vector<T> v) {
	vector<T> result;
	for (auto& elem : v) {
		result.push_back(Sqr(elem));
	}
	return result;
}

template <typename Key, typename Value> map<Key, Value> Sqr(map<Key, Value> m) {
	map<Key, Value> result;
	for (auto& elem : m) {
		result[elem.first] = Sqr(elem.second);
	}
	return result;
}

int main() {
	// ������ ������ �������
	vector<int> v = { 1, 2, 3 };
	cout << "vector:";
	for (int x : Sqr(v)) {
		cout << ' ' << x;
	}
	cout << endl;

	map<int, pair<int, int>> map_of_pairs = {
	  {4, {2, 2}},
	  {7, {4, 3}}
	};
	cout << "map of pairs:" << endl;
	for (const auto& x : Sqr(map_of_pairs)) {
		cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
	}
	return 0;
}
