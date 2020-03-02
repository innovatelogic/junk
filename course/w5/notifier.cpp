/*#include <iostream>
#include <string>


void SendSms(const std::string& number, const std::string& message) {
    std::cout << "Send '" << message << "' to number " << number << std::endl;
}

void SendEmail(const std::string& email, const std::string& message) {
    std::cout << "Send '" << message << "' to e-mail "  << email << std::endl;
}*/

struct INotifier
{
public:
    virtual void Notify(const std::string&) const = 0;
protected:
private:

};

struct EmailNotifier : public INotifier
{
public:
    EmailNotifier(const std::string &email)
    : m_email(email)
    {}

    void Notify(const std::string &message) const override
    {
        SendEmail(m_email, message);
    }

private:
    std::string m_email;
};

struct SmsNotifier : public INotifier
{
public:
    SmsNotifier(const std::string &number)
    : m_number(number)
    {}

    void Notify(const std::string &message) const override
    {
        SendSms(m_number, message);
    }

private:
    std::string m_number;
};
/*
void Notify(INotifier& notifier, const std::string& message)
{
  notifier.Notify(message);
}

int main()
{
  
  EmailNotifier email{"na-derevnyu@dedushke.ru"};
  SmsNotifier sms{"+7-495-777-77-77"};

  Notify(sms, "I have White belt in C++");
  Notify(email, "And want a Yellow one");
  return 0;
}*/