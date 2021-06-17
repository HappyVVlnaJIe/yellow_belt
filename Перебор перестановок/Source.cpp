#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

void swap(vector<int>& a, int i, int j)
{
    int s = a[i];
    a[i] = a[j];
    a[j] = s;
}
bool NextSet(vector<int>& a, int n)
{
    int j = n - 2;
    while (j != -1 && a[j] >= a[j + 1])
    {
        j--;
    }
    if (j == -1) { 
        return false; // больше перестановок нет
    }
    int k = n - 1;
    while (a[j] >= a[k]) {
        k--;
    }
    swap(a, j, k);
    int l = j + 1, r = n - 1; // сортируем оставшуюся часть последовательности
    while (l < r)
        swap(a, l++, r--);
    return true;
}
string Print(vector<int> a)  // вывод перестановки
{
    string result="";
    for (auto elem : a) {
        result += to_string(elem) + ' ';
    }
    return result;
}
int main()
{
    int n;
    vector<int> a;
    cin >> n;
    for (int i = 0; i < n; i++) {
        a.push_back(i+1);
    }
    vector<string> result;
    result.push_back(Print(a));
    while (NextSet(a, n)) {
        result.push_back(Print(a));
    }
    std::sort(result.rbegin(), result.rend());
    for (auto str : result) {
        cout << str << endl;
    }
    return 0;
}
/*
int main() {
  int range_length;
  cin >> range_length;
  vector<int> permutation(range_length);

  // iota             -> http://ru.cppreference.com/w/cpp/algorithm/iota
  // Заполняет диапазон последовательно возрастающими значениями
  // Обратные итераторы позволяют заполнить его, двигаясь от конца к началу
  iota(permutation.rbegin(), permutation.rend(), 1);

  // prev_permutation ->
  //     http://ru.cppreference.com/w/cpp/algorithm/prev_permutation
  // Преобразует диапазон в предыдущую (лексикографически) перестановку,
  // если она существует, и возвращает true,
  // иначе (если не существует) - в последнюю (наибольшую) и возвращает false
  do {
    for (int num : permutation) {
      cout << num << ' ';
    }
    cout << endl;
  } while (prev_permutation(permutation.begin(), permutation.end()));

  return 0;
}
*/