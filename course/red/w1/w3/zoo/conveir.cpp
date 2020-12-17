#include "test_runner.h"
#include <functional>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <list>

using namespace std;


struct Email {
  string from;
  string to;
  string body;
};


class Worker
{
public:
  virtual ~Worker() = default;
  virtual void Process(unique_ptr<Email> email) = 0;
  virtual void Run() {
    // только первому worker-у в пайплайне нужно это имплементировать
    throw logic_error("Unimplemented");
  }

protected:
  // реализации должны вызывать PassOn, чтобы передать объект дальше
  // по цепочке обработчиков
  void PassOn(unique_ptr<Email> email) const
  {
      if (m_next_worker){
          m_next_worker->Process(std::move(email));
      }
  }

public:
  void SetNext(unique_ptr<Worker> next)
  {
      m_next_worker = std::move(next);
  }

  std::unique_ptr<Worker> m_next_worker;
};


class Reader : public Worker
{
public:
  explicit Reader(istream& in)
  {
      bool b_from = false;
      bool b_to = false;
      bool b_data = false;

       while (in) 
       {
            auto email = std::make_unique<Email>();

            getline(in, email->from);

            if (in.peek() == EOF){
                break;
            }

            getline(in, email->to);

            if (in.peek() == EOF){
                break;
            }

            getline(in, email->body);

           m_emails.push_back(std::move(email));

           b_from = b_to = b_data = false;
       }
  }

  void Run() override
  {
      while (!m_emails.empty())
      {
          auto local = std::move(m_emails.front());
          m_emails.erase(m_emails.begin());

          Process(std::move(local));
      }
  }

  void Process(unique_ptr<Email> email)
  {
    PassOn(std::move(email));
  }

  std::list<std::unique_ptr<Email>> m_emails;
};


class Filter : public Worker {
public:
  using Function = function<bool(const Email&)>;

public:

    Filter(Function func)
    : m_filter(func)
    {

    }
    void Process(unique_ptr<Email> email)
    {
        if (m_next_worker && m_filter(*email.get())) {
            PassOn(std::move(email));
        }
    }

  Function m_filter;
};


class Copier : public Worker {
public:

    Copier(const string &recipient)
    : m_recipient(recipient)
    {
    }

    void Process(unique_ptr<Email> email)
    {
        if (m_recipient != email->to)
        {
            auto copy = std::make_unique<Email>();

            copy->to = m_recipient;
            copy->from = email->from;
            copy->body = email->body;

            PassOn(std::move(email));
            PassOn(std::move(copy));
        }
        else
        {
            PassOn(std::move(email));
        }
    }

    std::string m_recipient;
};


class Sender : public Worker {
public:
    // реализуйте класс
    Sender(ostream &out)
    : m_out(out)
    {}

    void Process(unique_ptr<Email> email)
    {
        m_out << email->from << '\n';
        m_out << email->to << '\n';
        m_out << email->body << '\n';

        //std::cerr << email->from << std::endl;
        //std::cerr << email->to << std::endl;
        //std::cerr << email->body << std::endl;

        PassOn(std::move(email));
    }

   ostream &m_out;
};


// реализуйте класс
class PipelineBuilder {
public:
  // добавляет в качестве первого обработчика Reader
  explicit PipelineBuilder(istream& in)
  {
      m_head = std::make_unique<Reader>(in);
      m_last = m_head.get();
  }

  // добавляет новый обработчик Filter
  PipelineBuilder& FilterBy(Filter::Function f)
  {
        auto filter = std::make_unique<Filter>(f);

        auto filter_ptr = filter.get();

        m_last->SetNext(std::move(filter));

        m_last = filter_ptr;

        return *this;
  }

  // добавляет новый обработчик Copier
  PipelineBuilder& CopyTo(string recipient)
  {
        auto copier = std::make_unique<Copier>(recipient);

        auto copier_ptr = copier.get();

        m_last->SetNext(std::move(copier));

        m_last = copier_ptr;

        return *this;
  }

  // добавляет новый обработчик Sender
  PipelineBuilder& Send(ostream& out)
  {
        auto sender = std::make_unique<Sender>(out);

        auto sender_ptr = sender.get();

        m_last->SetNext(std::move(sender));

        m_last = sender_ptr;

        return *this;
  }

  // возвращает готовую цепочку обработчиков
  unique_ptr<Worker> Build()
  {
      return std::move(m_head);
  }

  std::unique_ptr<Worker> m_head;
  Worker *m_last;
};


void TestSanity() {
  string input = (
    "erich@example.com\n"
    "richard@example.com\n"
    "Hello there\n"

    "erich@example.com\n"
    "ralph@example.com\n"
    "Are you sure you pressed the right button?\n"

    "ralph@example.com\n"
    "erich@example.com\n"
    "I do not make mistakes of that kind\n"
  );
  istringstream inStream(input);
  ostringstream outStream;

  PipelineBuilder builder(inStream);
  builder.FilterBy([](const Email& email) {
    return email.from == "erich@example.com";
  });
  builder.CopyTo("richard@example.com");
  builder.Send(outStream);
  auto pipeline = builder.Build();

  pipeline->Run();

  string expectedOutput = (
    "erich@example.com\n"
    "richard@example.com\n"
    "Hello there\n"

    "erich@example.com\n"
    "ralph@example.com\n"
    "Are you sure you pressed the right button?\n"

    "erich@example.com\n"
    "richard@example.com\n"
    "Are you sure you pressed the right button?\n"
  );

  ASSERT_EQUAL(expectedOutput, outStream.str());
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestSanity);
  return 0;
}


/*
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <functional>

using namespace std;


struct Email {
  string from;
  string to;
  string body;
};


class Worker {
public:
  virtual ~Worker() = default;
  virtual void Process(unique_ptr<Email> email) = 0;
  virtual void Run() {
    // только первому worker-у в пайплайне нужно это имплементировать
    throw logic_error("Unimplemented");
  }

protected:
  // реализации должны вызывать PassOn, чтобы передать объект дальше
  // по цепочке обработчиков
  void PassOn(unique_ptr<Email> email) const {
    if (next_) {
      next_->Process(move(email));
    }
  }

public:
  void SetNext(unique_ptr<Worker> next) {
    next_ = move(next);
  }

private:
  unique_ptr<Worker> next_;
};


class Reader : public Worker {
public:
  explicit Reader(istream& in)
    : in_(in)
  {}

  void Process(unique_ptr<Email>) override {
    // не делаем ничего
  }

  void Run() override {
    for (;;) {
      auto email = make_unique<Email>();
      getline(in_, email->from);
      getline(in_, email->to);
      getline(in_, email->body);
      if (in_) {
        PassOn(move(email));
      } else {
        // в реальных программах здесь стоит раздельно проверять badbit и eof
        break;
      }
    }
  }

private:
  istream& in_;
};


class Filter : public Worker {
public:
  using Function = function<bool(const Email&)>;

public:
  explicit Filter(Function func)
    : func_(move(func))
  {}

  void Process(unique_ptr<Email> email) override {
    if (func_(*email)) {
      PassOn(move(email));
    }
  }

private:
  Function func_;
};


class Copier : public Worker {
public:
  explicit Copier(string to)
    : to_(move(to))
  {}

  void Process(unique_ptr<Email> email) override {
    if (email->to != to_) {
      auto copy = make_unique<Email>(*email);
      copy->to = to_;
      PassOn(move(email));
      PassOn(move(copy));
    } else {
      PassOn(move(email));
    }
  }

private:
  string to_;
};


class Sender : public Worker {
public:
  explicit Sender(ostream& out)
    : out_(out)
  {}

  void Process(unique_ptr<Email> email) override {
    out_
      << email->from << endl
      << email->to << endl
      << email->body << endl;
    PassOn(move(email));  // never forget
  }
private:
  ostream& out_;
};


class PipelineBuilder {
public:
  explicit PipelineBuilder(istream& in) {
    workers_.push_back(make_unique<Reader>(in));
  }

  PipelineBuilder& FilterBy(Filter::Function filter) {
    workers_.push_back(make_unique<Filter>(move(filter)));
    return *this;
  }

  PipelineBuilder& CopyTo(string recipient) {
    workers_.push_back(make_unique<Copier>(move(recipient)));
    return *this;
  }

  PipelineBuilder& Send(ostream& out) {
    workers_.push_back(make_unique<Sender>(out));
    return *this;
  }

  unique_ptr<Worker> Build() {
    for (size_t i = workers_.size() - 1; i > 0; --i) {
      workers_[i - 1]->SetNext(move(workers_[i]));
    }
    return move(workers_[0]);
  }

private:
  vector<unique_ptr<Worker>> workers_;
};

*/