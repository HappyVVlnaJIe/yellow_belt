#include "sum_reverse_sort.h"
#include <algorithm>
#include <functional>
#include <array>
#include <iostream>
#include <string_view>

using namespace std;

int Sum(int x, int y) {
	return x + y;
}

string Reverse(string s) {
    int n = s.length();
    string result="";
    for (int i = n-1; i > -1; i--) {
        result += s[i];
    }
    return result;
}

void Sort(vector<int>& nums) {
    sort(nums.begin(),nums.end());
}

