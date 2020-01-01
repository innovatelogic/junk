#include <iostream>
#include <vector>

using namespace std;

/*
class Incognizable
{
public:
    Incognizable() {}
    Incognizable(int a) {}
    Incognizable(int a, int b) {}

private:
    int m_a = 0;
    int m_b = 0;
};

int main() 
{
  Incognizable a;
  Incognizable b = {};
  Incognizable c = {0};
  Incognizable d = {0, 1};
  return 0;
}*/

class Weather {
public:
  Weather(const string& new_state, int new_temperature) {
    state = new_state;
    temperature = new_temperature;
    cout << 'c';
  }
  ~Weather() {
    cout << 'd';
  }
private:
  string state;
  int temperature;
};

Weather GetMayWeather(int day) {
  if (day == 9) {
    cout << 'b';
    return {"clear", 10};
  } else {
    cout << 'b';
    return {"cloudy", 10};
  }
}

int main() {
  vector<int> days(2, 1);
  for (int day : days) {
    cout << 'a';
    Weather weather = GetMayWeather(day);
    cout << 'e';
  }
  cout << 'f';
  return 0;
}