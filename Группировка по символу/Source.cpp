#include <iostream>
#include <string>
#include <vector>
#include <algorithm>


//часть 1
//template <typename RandomIt>
//std::pair<RandomIt, RandomIt> FindStartsWith(
//    RandomIt range_begin, RandomIt range_end,
//    char prefix) {
//    RandomIt first_it = std::lower_bound(range_begin, range_end, std::string(1,prefix));
//    char next_prefix = static_cast<char>(static_cast<int>(prefix) + 1);
//    RandomIt end_it = std::lower_bound(range_begin, range_end, std::string(1, next_prefix));
//    return std::make_pair(first_it, end_it);
//}
//
//int main() {
//    const std::vector<std::string> sorted_strings = { "moscow", "murmansk", "vologda" };
//
//    const auto m_result =
//        FindStartsWith(begin(sorted_strings), end(sorted_strings), 'm');
//    for (auto it = m_result.first; it != m_result.second; ++it) {
//        std::cout << *it << " ";
//    }
//    std::cout << std::endl;
//
//    const auto p_result =
//        FindStartsWith(begin(sorted_strings), end(sorted_strings), 'p');
//    std::cout << (p_result.first - begin(sorted_strings)) << " " <<
//        (p_result.second - begin(sorted_strings)) << std::endl;
//
//    const auto z_result =
//        FindStartsWith(begin(sorted_strings), end(sorted_strings), 'z');
//    std::cout << (z_result.first - begin(sorted_strings)) << " " <<
//        (z_result.second - begin(sorted_strings)) << std::endl;
//
//    return 0;
//}


//часть 2
template <typename RandomIt>
std::pair<RandomIt, RandomIt> FindStartsWith(
    RandomIt range_begin, RandomIt range_end,
    const std::string& prefix) {
    RandomIt first_it = std::lower_bound(range_begin, range_end, prefix);
    std::string next_prefix = prefix;
    next_prefix[next_prefix.size() - 1] = static_cast<char>(static_cast<int>(next_prefix[next_prefix.size() - 1])+1);
    RandomIt end_it = std::lower_bound(range_begin, range_end, next_prefix);
    return std::make_pair(first_it, end_it);
}

int main() {
    const std::vector<std::string> sorted_strings = { "moscow", "motovilikha", "murmansk" };

    const auto mo_result =
        FindStartsWith(begin(sorted_strings), end(sorted_strings), "mo");
    for (auto it = mo_result.first; it != mo_result.second; ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    const auto mt_result =
        FindStartsWith(begin(sorted_strings), end(sorted_strings), "mt");
    std::cout << (mt_result.first - begin(sorted_strings)) << " " <<
        (mt_result.second - begin(sorted_strings)) << std::endl;

    const auto na_result =
        FindStartsWith(begin(sorted_strings), end(sorted_strings), "na");
    std::cout << (na_result.first - begin(sorted_strings)) << " " <<
        (na_result.second - begin(sorted_strings)) << std::endl;

    return 0;
}
