#include <iostream>
#include <vector>
#include <algorithm>

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
    if (std::distance(range_begin, range_end)<2) {
        return;
    }
    auto middle = range_begin + std::distance(range_begin, range_end) /2 ;
    std::vector<typename RandomIt::value_type> elements1(range_begin, middle);
    std::vector<typename RandomIt::value_type> elements2(middle, range_end);
    MergeSort(elements1.begin(), elements1.end());
    MergeSort(elements2.begin(), elements2.end());
    std::merge(elements1.begin(), 
        elements1.end(), 
        elements2.begin(), 
        elements2.end(), 
        range_begin);
}


int main() {
    std::vector<int> v = { 6, 4, 7, 6, 4, 4, 0, 1 };
    MergeSort(begin(v), end(v));
    for (int x : v) {
        std::cout << x << " ";
    }
    std::cout << std::endl;
    return 0;
}
