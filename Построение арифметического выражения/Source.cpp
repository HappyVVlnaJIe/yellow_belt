#include <iostream>
#include <string>
#include <sstream>
#include <set>
#include <vector>
#include <algorithm>

int main() {
	int n, k=0;
	std::string numb, res;
	std::ostringstream result;
	char current_sign, last_sign=' ';
	std::cin>>res;
	result << res;
	//result.resize(1000);
	std::cin >> n;
	for (int i = 0; i < n;++i) {
		std::cin >> current_sign >> numb;
		if ((current_sign=='/'||current_sign=='*') && last_sign!=' ' && last_sign!='/' && last_sign!='*') {
			result << ") " << current_sign << " " << numb;
			k++;
		}
		else {
			result << " " << current_sign << ' ' << numb;
		}
		last_sign = current_sign;
	}
	std::string s(k,'(');
	std::cout<<s << result.str();
	return 0;
}

//#include <iostream>
//#include <iterator>
//#include <vector>
//#include <algorithm>
//#include <numeric>
//#include <deque>
//#include <string>
//using namespace std;
//
//
//// ќпределим структуру дл€ удобной организации данных
//struct Operation {
//    // ѕараметры по умолчанию нужны дл€ конструировани€ вектора
//    // ненулевого размера, см. (*)
//    char type = 0;
//    int number = 0;
//};
//
//
//// ‘ункци€ дл€ проверки выполнени€ требований постановки скобок
//bool NeedBrackets(char last, char current) {
//    return (last == '+' || last == '-') && (current == '*' || current == '/');
//}
//
//
//int main() {
//    int initial_number;
//    cin >> initial_number;
//
//    int number_of_operations;
//    cin >> number_of_operations;
//    vector<Operation> operations(number_of_operations);  // (*)
//    for (int i = 0; i < number_of_operations; ++i) {
//        cin >> operations[i].type;
//        cin >> operations[i].number;
//    }
//
//    deque<string> expression;
//    expression.push_back(to_string(initial_number));
//    // первое число никогда не обрамл€етс€ скобками
//    char last_type = '*';
//    for (const auto& operation : operations) {
//        // ≈сли услови€ удовлетворены, обрамл€ем последовательность скобками
//        if (NeedBrackets(last_type, operation.type)) {
//            expression.push_front("(");
//            expression.push_back(")");
//        }
//        expression.push_back(" ");
//        expression.push_back(string(1, operation.type));
//        expression.push_back(" ");
//        expression.push_back(to_string(operation.number));
//
//        last_type = operation.type;
//    }
//
//    for (const string& s : expression) {
//        cout << s;
//    }
//
//    return 0;
//}
