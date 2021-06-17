#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Human {
public:
    Human(const string& name, const string& job) : Name(name), Job(job) {}

    virtual void Walk(const string& destination) {
        cout << Job <<": " << Name << " walks to: " << destination << endl;
    }

    const string Name, Job;
};

class Student : public Human{
public:

    Student(const string& name, const string& favouriteSong) : Human(name, "Student"), FavouriteSong(favouriteSong) {}

    void Learn() {
        cout << Job <<": " << Name << " learns" << endl;
    }

    void Walk(const string& destination) override {
        Human::Walk(destination);
        SingSong();
    }

    void SingSong() {
        cout << Job <<": " << Name << " sings a song: " << FavouriteSong << endl;
    }

    const string FavouriteSong;
};


class Teacher : public Human {
public:

    Teacher(const string& name, const string& subject) : Human(name, "Teacher"), Subject(subject) {}

    void Teach() {
        cout << Job <<": " << Name << " teaches: " << Subject << endl;
    }

    const string Subject;
};


class Policeman : public Human {
public:
    Policeman(const string& name) : Human(name, "Policeman"){}

    void Check(const Human& human) {
        cout << Job <<": " << Name << " checks "<<human.Job<<". "<<human.Job<<"'s name is: " << human.Name << endl;
    }

};


void VisitPlaces(Human& human, vector<string> places) {
    for (auto p : places) {
        human.Walk(p);
    }
}




int main() {
    Teacher t("Jim", "Math");
    Student s("Ann", "We will rock you");
    Policeman p("Bob");

    VisitPlaces(t, { "Moscow", "London" });
    p.Check(s);
    VisitPlaces(s, { "Moscow", "London" });
    return 0;
}
