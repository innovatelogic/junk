#include <iostream>
#include <string>

struct Specialization
{
    explicit Specialization(const std::string &spec)
    : spec(spec)
    {}

    std::string spec;
};

struct Course
{
    explicit Course(const std::string &course)
    : course(course)
    {}

    std::string course;
};

struct Week
{
    explicit Week(const std::string &week)
    : week(week)
    {}

    std::string week;
};

struct LectureTitle 
{
  string specialization;
  string course;
  string week;

  LectureTitle(const Specialization &spec, const Course &course, const Week &week)
  : specialization(spec.spec)
  , course(course.course)
  , week(week.week)
  {}
};