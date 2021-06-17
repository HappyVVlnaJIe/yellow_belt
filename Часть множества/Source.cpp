#include <iostream>
#include <vector>
#include <set>
#include <string>

template <typename T>
std::vector<T> FindGreaterElements(const std::set<T>& elements, const T& border) {
    // Начнём итерироваться по множеству
    auto it = begin(elements);
    // Цель — найти первый элемент, больший border
    // Если итератор не достиг конца и указывает не туда, двигаем
    while (it != end(elements) && *it <= border) {
        ++it;
    }
    // Возвращаем вектор, созданный из элементов множества, начиная с it
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