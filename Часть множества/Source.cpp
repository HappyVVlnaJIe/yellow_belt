#include <iostream>
#include <vector>
#include <set>
#include <string>

template <typename T>
std::vector<T> FindGreaterElements(const std::set<T>& elements, const T& border) {
    // ������ ������������� �� ���������
    auto it = begin(elements);
    // ���� � ����� ������ �������, ������� border
    // ���� �������� �� ������ ����� � ��������� �� ����, �������
    while (it != end(elements) && *it <= border) {
        ++it;
    }
    // ���������� ������, ��������� �� ��������� ���������, ������� � it
    return { it, end(elements) };
}

int main() {
    for (int x : FindGreaterElements(std::set<int>{1, 5, 7, 8}, 5)) {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    std::string to_find = "Python";
    std::cout << FindGreaterElements(std::set<std::string>{"C", "C++"}, to_find).size() << std::endl;
    return 0;
}