#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

class Person
{
public:
    Person(const std::string &name, const std::string &title)
    : name(name)
    , title(title)
    {}

    std::string Name() const { return name; }
    std::string Title() const { return title; }

    std::string Info() const { return Title() + ": " + Name(); }

    virtual void Walk(const string &destination) const 
    {
        cout << Info() << " walks to: " << destination << endl;
    }

private:
    const std::string name;
    const std::string title;
};

class Student : public Person
{
public:

    Student(const string &name, const string &favouriteSong)
    : Person(name, "Student")
    , FavouriteSong(favouriteSong)
    {}

    void Learn() const {
        cout << Info() << " learns" << endl;
    }

    void Walk(const string& destination) const override
     {
        Person::Walk(destination);
        SingSong();
    }

    void SingSong() const {
        cout << Info() << " sings a song: " << FavouriteSong << endl;
    }

public:
    const string FavouriteSong;
};


class Teacher : public Person
{
public:
    Teacher(const string &name, const string &subject)
    : Person(name, "Teacher")
    , Subject(subject)
    {}

    void Teach() const 
    {
        cout << Info() << " teaches: " << Subject << endl;
    }

public:
    const string Subject;
};


class Policeman : public Person {
public:
    Policeman(const string &name) 
    : Person(name, "Policeman")
    {}

    void Check(const Person &person) const
    {
        std::string title = person.Title();
        cout << Info() << " checks " << title << ". " << title << "'s name is: " << person.Name() << endl;
    }
};


void VisitPlaces(const Person &person, const vector<string> &places) {
    for (const auto &p : places) {
        person.Walk(p);
    }
}

int main() 
{
    Teacher t("Jim", "Math");
    Student s("Ann", "We will rock you");
    Policeman p("Bob");

    VisitPlaces(t, {"Moscow", "London"});
    p.Check(s);
    VisitPlaces(s, {"Moscow", "London"});
    return 0;
}