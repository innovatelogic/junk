#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Person
{
  public:
    Person(const string& profession, const string& name) : Profession(profession), Name(name) { }

    virtual void Walk(const string& destination) const
    {
        cout << Log() << Name << " walks to: " << destination << endl; 
    }

    string Log() const
    {
        return Profession + ": ";
    }

  public:
    const string Name;
    const string Profession;
};

class Student : public Person
{
  public:
    Student(const string& name, const string& favouriteSong) : Person("Student", name), FavouriteSong(favouriteSong) { }

    void Learn() const
    {
        cout << Log() << Name << " learns" << endl; 
    }

    void Walk(const string& destination) const override
    {
        Person::Walk(destination);
        SingSong();
    }

    void SingSong() const
    {
        cout << Log() << Name << " sings a song: " << FavouriteSong << endl;
    }

  private:
    string FavouriteSong;
};

class Teacher : public Person
{
  public:
    Teacher(const string& name, const string& subject) : Person("Teacher", name), Subject(subject) { }

    void Teach() const
    {
        cout << Log() << Name << " teaches: " << Subject << endl;
    }

  private:
    const string Subject;
};


class Policeman : public Person
{
  public:
    Policeman(const string& name) : Person("Policeman", name) { }

    void Check(const Person& p) const
    {
        cout << Log() << Name << " checks " << p.Profession << ". " << p.Profession << "'s name is: " << p.Name << endl;
    }
};

void VisitPlaces(const Person& person, const vector<string>& places)
{
    for (const auto& p : places) {
        person.Walk(p);
    }
}

int main()
{
    Student p1("Ann", "We will rock you");
    Teacher p2("Peter", "Physics");
    Policeman p3("Jake");

    p1.Learn();
    p1.Walk("New York");
    p1.SingSong();

    cout << endl;

    p2.Teach();
    p2.Walk("Boston");

    cout << endl;

    p3.Check(p1);
    p3.Walk("Moscow");

    VisitPlaces(p1, {"New York", "Beijing", "Sidney"});

    return 0;
}