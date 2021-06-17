#include "database.h"
#include "date.h"
#include "condition_parser.h"
#include "node.h"
#include "test_db.h"

#include <iostream>
#include <stdexcept>


using namespace std;

//std::ostream& operator<<(ostream& os, std::pair<Date, std::string> pr) {
//    os << pr.first << " " << pr.second;
//    return os;
//}

string ParseEvent(istream& is) {
    std::string result;
    std::getline(is, result);
    auto it = result.begin();
    for (; it < result.end();) {
        if (*it == ' ') {
            it++;
        }
        else {
            break;
        }
    }
    result = string(it,result.end());
    return result;
}

void TestAll();

int main() {
    TestAll();

    Database db;

    for (string line; getline(cin, line); ) {
        istringstream is(line);

        string command;
        is >> command;
        if (command == "Add") {
            const auto date = ParseDate(is);
            const auto event = ParseEvent(is);
            db.Add(date, event);
        }
        else if (command == "Print") {
            db.Print(cout);
        }
        else if (command == "Del") {
            auto condition = ParseCondition(is);
            auto predicate = [condition](const Date& date, const string& event) {
                return condition->Evaluate(date, event);
            };
            int count = db.RemoveIf(predicate);
            cout << "Removed " << count << " entries" << endl;
        }
        else if (command == "Find") {
            auto condition = ParseCondition(is);
            auto predicate = [condition](const Date& date, const string& event) {
                return condition->Evaluate(date, event);
            };

            const auto entries = db.FindIf(predicate);
            for (const auto& entry : entries) {
                cout << entry << endl;
            }
            cout << "Found " << entries.size() << " entries" << endl;
        }
        else if (command == "Last") {
            try {
                cout << db.Last(ParseDate(is)) << endl;
            }
            catch (invalid_argument&) {
                cout << "No entries" << endl;
            }
        }
        else if (command.empty()) {
            continue;
        }
        else {
            throw logic_error("Unknown command: " + command);
        }
    }

    return 0;
}

void TestParseEvent() {
    {
        istringstream is("event");
        AssertEqual(ParseEvent(is), "event", "Parse event without leading spaces");
    }
    {
        istringstream is("   sport event ");
        AssertEqual(ParseEvent(is), "sport event ", "Parse event with leading spaces");
    }
    {
        istringstream is("  first event  \n  second event");
        std::vector<std::string> events;
        events.push_back(ParseEvent(is));
        events.push_back(ParseEvent(is));
        AssertEqual(events, std::vector<std::string>{"first event  ", "second event"}, "Parse multiple events");
    }
}

void TestLast() {
    {
        Database db;
        Date date(2018,1,1);
        db.Add(date,"event");
        try {
            cout << db.Last(date) << endl;
        }
        catch (invalid_argument&) {
            cout << "No entries" << endl;
        }
        db.Add(date, "event 1");
        try {
            cout << db.Last(date) << endl;
        }
        catch (invalid_argument&) {
            cout << "No entries" << endl;
        }
        istringstream is(R"(date == 2018-1-1 AND event == "event 1")");
        auto condition = ParseCondition(is);
        auto predicate = [condition](const Date& date, const string& event) {
            return condition->Evaluate(date, event);
        };
        db.RemoveIf(predicate);
        try {
            cout << db.Last(date) << endl;
        }
        catch (invalid_argument&) {
            cout << "No entries" << endl;
        }
        stringstream is1(R"(date == 2018-1-1 AND event == "event")");
        condition = ParseCondition(is1);
        auto predicate1 = [condition](const Date& date, const string& event) {
            return condition->Evaluate(date, event);
        };
        db.RemoveIf(predicate1);
        try {
            cout << db.Last(date) << endl;
        }
        catch (invalid_argument&) {
            cout << "No entries" << endl;
        }
    }
}

void TestAll() {
    TestRunner tr;
    tr.RunTest(TestParseEvent, "TestParseEvent");
    tr.RunTest(TestParseCondition, "TestParseCondition");
    //tr.RunTest(TestLast, "TestLast");
    tr.RunTest(TestEmptyNode, "Тест 2 из Coursera");
    tr.RunTest(TestDbAdd, "Тест 3(1) из Coursera");
    tr.RunTest(TestDbFind, "Тест 3(2) из Coursera");
    tr.RunTest(TestDbLast, "Тест 3(3) из Coursera");
    tr.RunTest(TestDbRemoveIf, "Тест 3(4) из Coursera");
    tr.RunTest(TestInsertionOrder, "Тест на порядок вывода");
    tr.RunTest(TestsMyCustom, "Мои тесты");
    tr.RunTest(TestDatabase, "Тест базы данных с GitHub");
    tr.RunTest(TestDateOutput, "TestDateOutput");
    tr.RunTest(TestParseDate, "TestParseDate");

    tr.RunTest(TestDatabaseAddAndPrint, "TestDatabaseAddAndPrint");
    tr.RunTest(TestDatabaseFind, "TestDatabaseFind");
    tr.RunTest(TestDatabaseRemove, "TestDatabaseRemove");

    tr.RunTest(TestDatabaseLast, "TestDatabaseLast");
    tr.RunTest(TestDateComparisonNode, "TestDateComparisonNode");
    tr.RunTest(TestEventComparisonNode, "TestEventComparisonNode");
    tr.RunTest(TestLogicalOperationNode, "TestLogicalOperationNode");
}