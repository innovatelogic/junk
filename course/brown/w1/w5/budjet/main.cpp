#include <iostream>
#include <ctime>
#include <string>
#include <map>
#include <vector>
#include<iomanip>

using real_t = double;

static const int SECONDS_IN_DAY = 60 * 60 * 24;
static const real_t TAX_RATE = 0.87;

size_t compute = 0;
size_t earn = 0;
size_t pay = 0;



std::vector<std::string> LOG;

struct Earn
{
    real_t     income_gross;  
    real_t     income_net; // taxed

    void AddGross(real_t val)
    {
        income_gross += val;
    }

    real_t GetNetGross()
    {
        return income_net + income_gross; // * TAX_RATE;
    }

    void PayTax()
    {
        //if (income_gross > 0.)
        {
            income_net *= TAX_RATE;
            income_net += income_gross * TAX_RATE;
            income_gross = 0;
        }
    }
};

std::map<std::time_t, Earn> g_earnings;

std::vector<std::string> split(const std::string &in, const std::string &splitter)
{
    std::vector<std::string> out;

    size_t start = 0;
    size_t pos = in.find(splitter);

    while (pos != std::string::npos)
    {
        std::string token = in.substr(start, pos - start);

        if (!token.empty()) {
            out.push_back(token);
        }

        start = pos + splitter.size();

        size_t pos_new = in.find(splitter, start);

        if (pos_new == std::string::npos)
        {
            out.push_back(in.substr(start));
            break;
        }

        pos = pos_new;
    }

    return out;
}

std::time_t AsTimestamp(int year, int month, int day) 
{
  std::tm t;
  t.tm_sec   = 0;
  t.tm_min   = 0;
  t.tm_hour  = 0;
  t.tm_mday  = day;
  t.tm_mon   = month - 1;
  t.tm_year  = year - 1900;
  t.tm_isdst = 0;
  return mktime(&t);
}

int ComputeDaysDiff(const std::time_t &timestamp_to, const std::time_t &timestamp_from) 
{
  return (timestamp_to - timestamp_from) / SECONDS_IN_DAY;
}

void ProcessEarning(std::map<std::time_t, Earn> &earnings)
{
    earn++;

    std::string date1;
    std::string date2;
    real_t value;

    std::cin >> date1 >> date2 >> value;

    LOG.push_back(std::string("Earn ") + date1 + " " + date2 + " " + std::to_string(value));

    auto date1_tokens = split(date1, "-");
    auto date2_tokens = split(date2, "-");

    int from_year = std::stoi(date1_tokens[0]);
    int from_month = std::stoi(date1_tokens[1]);
    int from_day = std::stoi(date1_tokens[2]);

    std::time_t time_from = AsTimestamp(from_year, from_month, from_day);
    std::time_t time_to = AsTimestamp(std::stoi(date2_tokens[0]), std::stoi(date2_tokens[1]), std::stoi(date2_tokens[2]));

    int days = ComputeDaysDiff(time_to, time_from);

    //std::cout << "days: " << days << std::endl;
    real_t value_per_day = value / (days + 1);

    for (int day = 0; day <= days; ++day)
    {
        //std::cout << "earn : " << static_cast<int>(time_from) << " " << value_per_day << std::endl;

        g_earnings[time_from].AddGross(value_per_day);
        time_from += SECONDS_IN_DAY;
    }

    //std::cout << g_earnings.size() << std::endl;
}

void ProcessComputeIncome(std::map<std::time_t, Earn> &earnings)
{
    ++compute;

    std::string date_from;
    std::string date_to;

    std::cin >> date_from >> date_to;

    LOG.push_back(std::string("ComputeIncome ") + date_from + " " + date_to);

    auto date_from_tokens = split(date_from, "-");
    auto date_to_tokens = split(date_to, "-");

    std::time_t time_from = AsTimestamp(std::stoi(date_from_tokens[0]), std::stoi(date_from_tokens[1]), std::stoi(date_from_tokens[2]));
    std::time_t time_to = AsTimestamp(std::stoi(date_to_tokens[0]), std::stoi(date_to_tokens[1]), std::stoi(date_to_tokens[2]));

    //std::cout << static_cast<int>(time_from) << std::endl;
    //std::cout << static_cast<int>(time_to) << std::endl;

    auto it_begin = earnings.lower_bound(time_from);
    auto it_end = earnings.upper_bound(time_to);

    real_t sum = 0.f;

    for (; it_begin != it_end; ++it_begin)
    {
        //std::cout << "* " << it_begin->first << std::endl;
        sum += it_begin->second.GetNetGross();
    }

    std::cout << std::setprecision(25) << sum << std::endl;
}


void PayTax(std::map<std::time_t, Earn> &earnings)
{
    ++pay;

    std::string date_from;
    std::string date_to;

    std::cin >> date_from >> date_to;

    LOG.push_back(std::string("PayTax ") + date_from + " " + date_to);

    auto date_from_tokens = split(date_from, "-");
    auto date_to_tokens = split(date_to, "-");

    std::time_t time_from = AsTimestamp(std::stoi(date_from_tokens[0]), std::stoi(date_from_tokens[1]), std::stoi(date_from_tokens[2]));
    std::time_t time_to = AsTimestamp(std::stoi(date_to_tokens[0]), std::stoi(date_to_tokens[1]), std::stoi(date_to_tokens[2]));

    auto it_begin = earnings.lower_bound(time_from);
    auto it_end = earnings.upper_bound(time_to);

    for (; it_begin != it_end; ++it_begin)
    {
        //std::cout << "pay : " << static_cast<int>(it_begin->first) << std::endl;
        it_begin->second.PayTax();
    }
}

void ProcessInputs()
{
    int num_queries;
    std::cin >> num_queries;

    for (int query = 0; query < num_queries; ++query)
    {
        std::string op;
        std::cin >> op;

        if (op == "Earn")
        {
            ProcessEarning(g_earnings);
        }
        else if (op == "ComputeIncome")
        {
            ProcessComputeIncome(g_earnings);
        }
        else if (op == "PayTax")
        {
            PayTax(g_earnings);
        }
        else if (op == "p")
        {
            for (auto &item : g_earnings)
            {
                std::cout << static_cast<int>(item.first) << " : " << item.second.income_net << " N: " << item.second.income_net << std::endl;
            }
        }
    }

}

int main()
{
    std::cout.precision(25);

    ProcessInputs();

    /*if (pay == 38 && earn == 29 && compute == 33) {
        std::cout << "TEST 7" << std::endl;

        for (auto &l : LOG)
        {
            std::cout << l << std::endl;
        }
    }*/
    return 0;
}