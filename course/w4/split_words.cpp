#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

std::vector<std::string> SplitIntoWords(const std::string &s)
{
    std::vector<std::string> out;

    auto it_find = std::find(s.begin(), s.end(), ' ');
    auto it_prev = s.begin();

    while (it_find != s.end())
    {
        out.push_back(std::string(it_prev, it_find));

        it_prev = it_find + 1;
        it_find = std::find(it_prev, s.end(), ' ');
    }

    out.push_back(std::string(it_prev, s.end()));

    return out;
}


vector<string> __SplitIntoWords(const string& str) {
  // Готовим вектор, в который будем сохранять слова
  vector<string> result;

  // Эти два итератора будут ограничивать текущую не разбитую часть строки
  // str_begin будет двигаться вправо
  auto str_begin = begin(str);
  // str_end всегда будет указывать на конец строки (поэтому он константный)
  const auto str_end = end(str);

  // У цикла нет условия завершения, так что единственный способ закончить его —
  // сделать break
  while (true) {
    
    // Находим первый пробел в текущем «хвосте» строки
    auto it = find(str_begin, str_end, ' ');
    
    // Полуинтервал [str_begin, it) — очередное слово
    result.push_back(string(str_begin, it));
    
    if (it == str_end) {
      // Если пробелов больше нет, цикл пора завершить.
      // Последнее слово уже добавлено
      break;
    } else {
      // Иначе первый символ после пробела — начало очередного слова.
      // Туда и подвинем str_begin
      str_begin = it + 1;
    }
    
  }

  return result;
}

/*
int main()
{
    std::string s = "C Cpp Java Python";

    std::vector<std::string> words = SplitIntoWords(s);
    std::cout << words.size() << " ";
    for (auto it = std::begin(words); it != std::end(words); ++it) {
        if (it != std::begin(words)) {
            std::cout << "/";
        }
        std::cout << *it;
    }
    std::cout << std::endl;
  
    return 0;
}*/