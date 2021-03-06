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

bool IsPalindrom(string s) {

    // ????????? ??? ??????? s[i] ?? ?????? ???????? ??????
    for (size_t i = 0; i < s.size() / 2; ++i) {
        // s[s.size() - i - 1] ? ??????, ???????????? ??????? s[i]
        if (s[i] != s[s.size() - i - 1]) {
            return false;  // ???? ??? ?? ?????????, ?????? ????? ?? ?????????
        }
    }

    // ???? ??? ???? ???????? ?????????, ?????? ? ?????????
    return true;
}

void TestSimplePalindrom() {
   
    AssertEqual(IsPalindrom(""), true);
    AssertEqual(IsPalindrom("q"), true);
    AssertEqual(IsPalindrom("  "), true);
    AssertEqual(IsPalindrom("   "), true);
}

void Test() {
    AssertEqual(IsPalindrom("qweewq"), true);
    AssertEqual(IsPalindrom("qwewq"), true);
    AssertEqual(IsPalindrom("qwerty"), false);
    AssertEqual(IsPalindrom("qwew"), false);
    AssertEqual(IsPalindrom("wewq"), false);
    AssertEqual(IsPalindrom("wew "), false);
    AssertEqual(IsPalindrom(" wew"), false);
    AssertEqual(IsPalindrom("we w"), false);
    AssertEqual(IsPalindrom("ww!"), false);
}

int main() {
    TestRunner runner;
    // ???????? ???? ???? ?????
    runner.RunTest(TestSimplePalindrom, "Simple palindrom test");
    runner.RunTest(Test, "just test");
    return 0;
}