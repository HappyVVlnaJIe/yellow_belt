#include <iostream>
#include <vector>
#include <algorithm>

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
    if (std::distance(range_begin, range_end) < 2) {
        return;
    }
    auto end_first_part = range_begin + std::distance(range_begin, range_end) / 3, end_second_part = end_first_part+ std::distance(range_begin, range_end) / 3;
    std::vector<typename RandomIt::value_type> elements1(range_begin, end_first_part);
    std::vector<typename RandomIt::value_type> elements2(end_first_part, end_second_part);
    std::vector<typename RandomIt::value_type> elements3(end_second_part, range_end);
    MergeSort(elements1.begin(), elements1.end());
    MergeSort(elements2.begin(), elements2.end());
    MergeSort(elements3.begin(), elements3.end());
    std::vector<typename RandomIt::value_type> temporary_vector;
    std::merge(elements1.begin(),
        elements1.end(),
        elements2.begin(),
        elements2.end(),
        std::back_inserter(temporary_vector));

    std::merge(temporary_vector.begin(),
        temporary_vector.end(),
        elements3.begin(),
        elements3.end(),
        range_begin);
}


int main() {
    std::vector<int> v = { 6, 4, 7, 6, 4, 4, 0, 1, 5 };
    MergeSort(begin(v), end(v));
    for (int x : v) {
        std::cout << x << " ";
    }
    std::cout << std::endl;
    return 0;
}