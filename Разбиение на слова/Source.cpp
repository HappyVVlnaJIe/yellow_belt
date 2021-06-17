#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

std::vector<std::string> SplitIntoWords(const std::string& s) {
    std::vector<std::string> result;
    auto last_it = begin(s), current_it = begin(s);
    // Цель — найти первый элемент, больший border
    // Если итератор не достиг конца и указывает не туда, двигаем
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
ЭТАЛОННОЕ РЕШЕНИЕ
vector<string> SplitIntoWords(const string& str) {
  // Готовим вектор, в который будем сохранять слова
  vector<string> result;

  // Эти два итератора будут ограничивать текущую не разбитую часть строки
  // str_begin будет двигаться вправо
  auto str_begin = begin(str);
  // str_end всегда будет указывать на конец строки (поэтому он константный)
  const auto str_end = end(str);

  // У цикла нет условия завершения, так что единственный способ закончить его —
  // сделать break
  while (true) {

    // Находим первый пробел в текущем «хвосте» строки
    auto it = find(str_begin, str_end, ' ');

    // Полуинтервал [str_begin, it) — очередное слово
    result.push_back(string(str_begin, it));

    if (it == str_end) {
      // Если пробелов больше нет, цикл пора завершить.
      // Последнее слово уже добавлено
      break;
    } else {
      // Иначе первый символ после пробела — начало очередного слова.
      // Туда и подвинем str_begin
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
