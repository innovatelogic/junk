#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

class Person
{
public:
    Person(const std::string &name)
    : name(name)
    {}

    std::string Name() const { return name; }
    virtual std::string Title() const = 0;

    std::string Info() const { return Title() + ": " + Name(); }

    virtual void Walk(const string &destination) const 
    {
        cout << Info() << " walks to: " << destination << endl;
    }

private:
    std::string name;
};

class Student : public Person
{
public:

    Student(const string &name, const string &favouriteSong)
    : Person(name)
    , FavouriteSong(favouriteSong)
    {}

    std::string Title() const override { return "Student"; }

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
    string FavouriteSong;
};


class Teacher : public Person
{
public:
    Teacher(const string &name, const string &subject)
    : Person(name)
    , Subject(subject)
    {}

    std::string Title() const override { return "Teacher"; }

    void Teach() const 
    {
        cout << Info() << " teaches: " << Subject << endl;
    }

public:
    string Subject;
};


class Policeman : public Person {
public:
    Policeman(const string &name) 
    : Person(name)
    {}

    std::string Title() const override { return "Policeman"; }

    void Check(const std::shared_ptr<Person> &person) const
    {
        std::string title = person->Title();
        cout << Info() << " checks " << title << ". " << title << "'s name is: " << person->Name() << endl;
    }
};


void VisitPlaces(const std::shared_ptr<Person> &person, const vector<string> &places) {
    for (const auto &p : places) {
        person->Walk(p);
    }
}

int main() 
{
    std::shared_ptr<Teacher> t = std::make_shared<Teacher>("Jim", "Math");
    std::shared_ptr<Student> s = std::make_shared<Student>("Ann", "We will rock you");
    std::shared_ptr<Policeman> p = std::make_shared<Policeman>("Bob");

    VisitPlaces(t, {"Moscow", "London"});
    p->Check(s);
    VisitPlaces(s, {"Moscow", "London"});
    return 0;
}