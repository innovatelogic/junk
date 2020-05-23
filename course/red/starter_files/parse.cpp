#include "parse.h"

#include <iostream>

string_view Strip(string_view s) {
  while (!s.empty() && isspace(s.front())) {
    s.remove_prefix(1);
  }
  while (!s.empty() && isspace(s.back())) {
    s.remove_suffix(1);
  }
  return s;
}

vector<string_view> SplitBy(string_view s, char sep) 
{
  vector<string_view> result;
  while (!s.empty()) {
    size_t pos = s.find(sep);
    result.push_back(s.substr(0, pos));
    s.remove_prefix(pos != s.npos ? pos + 1 : s.size());
  }
  return result;
}

std::vector<std::string_view> split_str(const std::string_view &str, char splitter)
{
  std::vector<std::string_view> out;

  if (str.empty()){
    return {};
  }

  size_t start = str.find_first_not_of(splitter);
  size_t end = str.npos;

  //  "c  d e f   ";

  while (start != std::string::npos)
  {
    size_t end = str.find(splitter, start + 1);

    //std::cout << start << ' ' << split_pos << std::endl;

    out.push_back((end == std::string::npos) ?
          str.substr(start) :
          str.substr(start, end - start));
    
    start = str.find_first_not_of(splitter, end);
  }

  return out;


}

