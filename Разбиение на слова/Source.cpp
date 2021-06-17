#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

std::vector<std::string> SplitIntoWords(const std::string& s) {
    std::vector<std::string> result;
    auto last_it = begin(s), current_it = begin(s);
    // ���� � ����� ������ �������, ������� border
    // ���� �������� �� ������ ����� � ��������� �� ����, �������
    while(current_it != end(s))
    {
        while (current_it != end(s) && *current_it != ' ') {
            ++current_it;
        }
        result.push_back({ last_it, current_it });
        if (current_it != end(s)) {
            current_it++;
        }
        last_it = current_it;
    }
    return result;
}
/*
��������� �������
vector<string> SplitIntoWords(const string& str) {
  // ������� ������, � ������� ����� ��������� �����
  vector<string> result;

  // ��� ��� ��������� ����� ������������ ������� �� �������� ����� ������
  // str_begin ����� ��������� ������
  auto str_begin = begin(str);
  // str_end ������ ����� ��������� �� ����� ������ (������� �� �����������)
  const auto str_end = end(str);

  // � ����� ��� ������� ����������, ��� ��� ������������ ������ ��������� ��� �
  // ������� break
  while (true) {

    // ������� ������ ������ � ������� ������� ������
    auto it = find(str_begin, str_end, ' ');

    // ������������ [str_begin, it) � ��������� �����
    result.push_back(string(str_begin, it));

    if (it == str_end) {
      // ���� �������� ������ ���, ���� ���� ���������.
      // ��������� ����� ��� ���������
      break;
    } else {
      // ����� ������ ������ ����� ������� � ������ ���������� �����.
      // ���� � �������� str_begin
      str_begin = it + 1;
    }

  }

  return result;
}
*/
int main() {
    std::string s = "C Cpp Java Python";

    std::vector<std::string> words = SplitIntoWords(s);
    std::cout << words.size() << " ";
    for (auto it = begin(words); it != end(words); ++it) {
        if (it != begin(words)) {
            std::cout << "/";
        }
        std::cout << *it;
    }
    std::cout << std::endl;

    return 0;
}
