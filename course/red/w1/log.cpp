#include "test_runner.h"
#include <sstream>
#include <string>
using namespace std;

class Logger 
{
public:
    explicit Logger(ostream& output_stream) 
    : os(output_stream)
    {
    }

    void SetLogLine(bool value) { log_line = value; }
    void SetLogFile(bool value) { log_file = value; }

    bool get_line() const { return log_line; }
    bool get_file() const { return log_file; }

    template<class T>
    Logger& operator << (const T &v)
    {
        os << v;
        return *this;
    }

private:
  ostream& os;
  bool log_line = false;
  bool log_file = false;
};

#define LOG(logger, message) \
{ \
    bool prefix = false; \
    if (logger.get_file()) { logger << __FILE__; prefix = true; }  \
    if (logger.get_line()) { logger << (logger.get_file() ? ":" : "Line ") << std::to_string(__LINE__); prefix = true; } \
    logger << (prefix ? " " : "") << message << "\n"; \
}

void TestLog() {

#line 1 "logger.cpp"

  ostringstream logs;
  Logger l(logs);
  LOG(l, "hello");

  l.SetLogFile(true);
  LOG(l, "hello");

  l.SetLogLine(true);
  LOG(l, "hello");

  l.SetLogFile(false);
  LOG(l, "hello");

  string expected = "hello\n";
  expected += "logger.cpp hello\n";
  expected += "logger.cpp:10 hello\n";
  expected += "Line 13 hello\n";
  ASSERT_EQUAL(logs.str(), expected);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestLog);
}