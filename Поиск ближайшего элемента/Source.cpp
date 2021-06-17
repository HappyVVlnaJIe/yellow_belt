#include <iostream>
#include <set>
#include <iterator>

std::set<int>::const_iterator FindNearestElement(
    const std::set<int>& numbers, int border) {

    const auto lb_it = numbers.lower_bound(border);

    if (lb_it==numbers.begin()) {
        return lb_it;
    }

    const auto prev_lb_it = prev(lb_it);

    if (lb_it==numbers.end()) {
        return prev_lb_it;
    }
    bool fl = (border - *prev_lb_it <= *lb_it - border);
    return fl ? prev_lb_it : lb_it;
}
//
//#include <iterator>
//#include <set>
//using namespace std;
//set<int>::const_iterator FindNearestElement(const set<int>& numbers,
//    int border) {
//    // ����������� �������� �� ������ �������, �� ������� border;
//    // ���� ������ �������� ���, �� �� ������� numbers.end()
//    // set::lower_bound ->
//    // http://ru.cppreference.com/w/cpp/container/set/lower_bound
//    const auto first_not_less = numbers.lower_bound(border);
//
//    // ���� ��������� ����� ��� �� ������� �������� �� ������ border
//    // ��� ���������, �� �� ��� �������� �����
//    if (first_not_less == numbers.begin()) {
//        return first_not_less;
//    }
//
//    // ���� ���������, �� ������� border, ��� � set �� ����, �� ���������� �����
//    // �������� �� ��������� �������, ������� border
//    // prev -> http://ru.cppreference.com/w/cpp/iterator/prev
//    const auto last_less = prev(first_not_less);
//    if (first_not_less == numbers.end()) {
//        return last_less;
//    }
//
//    // ���������� ��� ���������-��������� � ������� ���,
//    // ��� ������� ����� � ��������
//    const bool is_left = (border - *last_less <= *first_not_less - border);
//    return is_left ? last_less : first_not_less;
//}


int main() {
    std::set<int> numbers = { 1, 4, 6 };
    std::cout <<
        *FindNearestElement(numbers, 0) << " " <<
        *FindNearestElement(numbers, 3) << " " <<
        *FindNearestElement(numbers, 5) << " " <<
        *FindNearestElement(numbers, 6) << " " <<
        *FindNearestElement(numbers, 100) << std::endl;

    std::set<int> empty_set;

    std::cout << (FindNearestElement(empty_set, 8) == end(empty_set)) << std::endl;
    return 0;
}