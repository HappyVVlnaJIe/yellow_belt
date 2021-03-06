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
/*
string FindNameByYear(const map<int, string>& names, int year) {
    string name;  // ?????????? ??? ??????????

    // ?????????? ??? ??????? ?? ??????????? ????? ???????, ?? ???? ? ??????????????? ???????
    for (const auto& item : names) {
        // ???? ????????? ??? ?? ?????? ???????, ????????? ???
        if (item.first <= year) {
            name = item.second;
        }
        else {
            // ????? ???? ????????????, ??? ??? ??? ?????? ? ??? ??????????? ????????? ? ????????
            break;
        }
    }

    return name;
}

class Person {
public:
    void ChangeFirstName(int year, const string& first_name) {
        first_names[year] = first_name;
    }
    void ChangeLastName(int year, const string& last_name) {
        last_names[year] = last_name;
    }
    string GetFullName(int year) {
        // ???????? ??? ? ??????? ?? ????????? ?? ??? year
        const string first_name = FindNameByYear(first_names, year);
        const string last_name = FindNameByYear(last_names, year);

        // ???? ? ???, ? ??????? ??????????
        if (first_name.empty() && last_name.empty()) {
            return "Incognito";

            // ???? ?????????? ?????? ???
        }
        else if (first_name.empty()) {
            return last_name + " with unknown first name";

            // ???? ?????????? ?????? ???????
        }
        else if (last_name.empty()) {
            return first_name + " with unknown last name";

            // ???? ???????? ? ???, ? ???????
        }
        else {
            return first_name + " " + last_name;
        }
    }

private:
    map<int, string> first_names;
    map<int, string> last_names;
};
*/
void TestLastNameFirst() {
    Person p;
    p.ChangeFirstName(1999, "Kostya");
    p.ChangeLastName(1998,"Sitnikov");

    AssertEqual(p.GetFullName(1997), "Incognito");
    AssertEqual(p.GetFullName(1998), "Sitnikov with unknown first name");
    AssertEqual(p.GetFullName(1999), "Kostya Sitnikov");
}

void TestFirstNameFirst() {
    Person p;
    p.ChangeFirstName(1998, "Kostya");
    p.ChangeLastName(1999, "Sitnikov");

    AssertEqual(p.GetFullName(1997), "Incognito");
    AssertEqual(p.GetFullName(1998), "Kostya with unknown last name");
    AssertEqual(p.GetFullName(1999), "Kostya Sitnikov");
}

void TestChange() {
    Person p;
    p.ChangeFirstName(1990, "Kostya");
    p.ChangeLastName(1995, "Sitnikov");

    AssertEqual(p.GetFullName(1989), "Incognito");
    AssertEqual(p.GetFullName(1990), "Kostya with unknown last name");
    AssertEqual(p.GetFullName(1995), "Kostya Sitnikov");

    p.ChangeFirstName(1997, "Denis");

    AssertEqual(p.GetFullName(1995), "Kostya Sitnikov");
    AssertEqual(p.GetFullName(1997), "Denis Sitnikov");
    AssertEqual(p.GetFullName(1999), "Denis Sitnikov");

    p.ChangeLastName(1996, "Ivanov");

    AssertEqual(p.GetFullName(1996), "Kostya Ivanov");
    AssertEqual(p.GetFullName(1995), "Kostya Sitnikov");
    AssertEqual(p.GetFullName(1997), "Denis Ivanov");
}

int main() {
    TestRunner runner;
    // ???????? ???? ???? ?????
    runner.RunTest(TestChange,"Test changes");
    runner.RunTest(TestFirstNameFirst,"First name first");
    runner.RunTest(TestLastNameFirst,"Last name first");
    return 0;
}