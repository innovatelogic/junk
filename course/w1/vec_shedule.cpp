#include <iostream>
#include <string>
#include <vector>


using t_shedule = std::vector<std::vector<std::string>>;

static const std::vector<int> month_count = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

void add(t_shedule &sh, size_t n, const std::string &activity)
{
    sh[n].push_back(activity);
}

std::vector<std::string> dump(t_shedule &sh, size_t n)
{
    return sh[n];
}

t_shedule next(const t_shedule &sh, size_t &curr_month)
{
    size_t next_month = curr_month + 1;
    if (next_month >= month_count.size()){
        next_month = 0;
    }

    t_shedule new_shedule(month_count[next_month]);

    size_t old_sh_size = sh.size();
    for (size_t i = 0; i < old_sh_size; ++i)
    {
        if (i < new_shedule.size())
        {
            new_shedule[i] = sh[i];
        }
        else
        {
            std::vector<std::string> &last = *(new_shedule.rbegin());
            last.insert(end(last), begin(sh[i]), end(sh[i]));

            //last +=  (!last.empty() ? std::string(" ") + sh[i] : sh[i]);
        }
    }

    curr_month = next_month;
    
    return new_shedule;
}

int main()
{
    size_t curr_month = 0;
    t_shedule shedule(month_count[curr_month]);

    size_t q = 0;
    std::cin >> q;

    std::string op;
    int n;

    for (size_t i = 0; i < q; ++i)
    {
        std::cin >> op;

        if (op == "ADD")
        {
            int n;
            std::string activity;
            std::cin >> n >> activity;

            add(shedule, n - 1, activity);
        }
        else if (op == "NEXT")
        {
            shedule = next(shedule, curr_month);
        }
        else if (op == "DUMP")
        {
            int n;
            std::cin >> n;

            std::vector<std::string> day = dump(shedule, n - 1);
            std::cout << day.size() << " ";

            for (const auto &a : day){
                std::cout << a << " ";
            }

            std::cout << std::endl;
        }
    }

}