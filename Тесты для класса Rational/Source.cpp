#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
    os << "{";
    bool first = true;
    for (const auto& x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
    os << "{";
    bool first = true;
    for (const auto& x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
    os << "{";
    bool first = true;
    for (const auto& kv : m) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << kv.first << ": " << kv.second;
    }
    return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
    if (t != u) {
        ostringstream os;
        os << "Assertion failed: " << t << " != " << u;
        if (!hint.empty()) {
            os << " hint: " << hint;
        }
        throw runtime_error(os.str());
    }
}

void Assert(bool b, const string& hint) {
    AssertEqual(b, true, hint);
}

class TestRunner {
public:
    template <class TestFunc>
    void RunTest(TestFunc func, const string& test_name) {
        try {
            func();
            cerr << test_name << " OK" << endl;
        }
        catch (exception& e) {
            ++fail_count;
            cerr << test_name << " fail: " << e.what() << endl;
        }
        catch (...) {
            ++fail_count;
            cerr << "Unknown exception caught" << endl;
        }
    }

    ~TestRunner() {
        if (fail_count > 0) {
            cerr << fail_count << " unit tests failed. Terminate" << endl;
            exit(1);
        }
    }

private:
    int fail_count = 0;
};
//
//int gcd(int a, int b)
//{
//    return (b == 0) ? a : gcd(b, a % b);
//}
//
//class Rational {
//public:
//    Rational() {
//        this->numerator = 0;
//        this->denominator = 1;
//    }
//
//    Rational(int numerator, int denominator) {
//        if (numerator == 0) {
//            this->numerator = 0;
//            this->denominator = 1;
//            return;
//        }
//        if (denominator == 0) {
//            throw std::invalid_argument("Invalid argument");
//        }
//        int nod = gcd(abs(numerator), abs(denominator));
//        int sign = (numerator / abs(numerator)) / (denominator / abs(denominator));
//        this->numerator = abs(numerator) * sign / nod;
//        this->denominator = abs(denominator) / nod;
//    }
//
//    int Numerator() const {
//        return this->numerator;
//    }
//
//    int Denominator() const {
//        return this->denominator;
//    }
//
//private:
//    int numerator;
//    int denominator;
//};
//
//Rational operator+(const Rational& a, const Rational& b) {
//    return Rational(a.Numerator() * b.Denominator() + b.Numerator() * a.Denominator(), a.Denominator() * b.Denominator());
//}
//
//Rational operator-(const Rational& a, const Rational& b) {
//    return Rational(a.Numerator() * b.Denominator() - b.Numerator() * a.Denominator(), a.Denominator() * b.Denominator());
//}
//
//Rational operator*(const Rational& a, const Rational& b) {
//    return Rational(a.Numerator() * b.Numerator(), a.Denominator() * b.Denominator());
//}
//
//Rational operator/(const Rational& a, const Rational& b) {
//    if (b.Numerator() == 0) {
//        throw domain_error("Division by zero");
//    }
//    return Rational(a.Numerator() * b.Denominator(), a.Denominator() * b.Numerator());
//}
//
//bool operator==(const Rational& a, const Rational& b) {
//    return a.Numerator() == b.Numerator() && a.Denominator() == b.Denominator();
//}
//
//bool operator<(const Rational& a, const Rational& b) {
//    return a.Numerator() * b.Denominator() < b.Numerator() * a.Denominator();
//}
//
//bool operator>(const Rational& a, const Rational& b) {
//    return a.Numerator() * b.Denominator() > b.Numerator() * a.Denominator();
//}
//
//ostream& operator<<(ostream& stream, const Rational& rational) {
//    stream << rational.Numerator() << '/' << rational.Denominator();
//    return stream;
//}
//
//istream& operator>>(istream& stream, Rational& rational) {
//    int numerator, denominator;
//    char sign;
//    bool empty = !(stream >> numerator >> sign >> denominator);
//    if (!empty && sign == '/') {
//        rational = Rational(numerator, denominator);
//    }
//    return stream;
//}

void TestConstructor() {
    Rational r;
    AssertEqual(r.Numerator(), 0);
    AssertEqual(r.Denominator(), 1);

    Rational rational(4,6);
    AssertEqual(rational.Numerator(),2);
    AssertEqual(rational.Denominator(),3);

    Rational rtnl(0,2);
    AssertEqual(rtnl.Denominator(), 1);
}

void TestSign() {
    Rational r(-2,-3);
    AssertEqual(r.Numerator(), 2);
    AssertEqual(r.Denominator(), 3);

    Rational rational(2, 3);
    AssertEqual(rational.Numerator(), 2);
    AssertEqual(rational.Denominator(), 3);

    
    Rational rtnl(-2,3);
    AssertEqual(rtnl.Numerator(), -2);
    AssertEqual(rtnl.Denominator(), 3);

    Rational q(2, -3);
    AssertEqual(q.Numerator(), -2);
    AssertEqual(q.Denominator(), 3);
}

int main() {
    TestRunner runner;
    // добавьте сюда свои тесты
    runner.RunTest(TestConstructor, "Test constructor");
    runner.RunTest(TestSign, "Test sign");
    return 0;
}