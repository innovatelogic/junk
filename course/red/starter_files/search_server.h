#pragma once

#include <istream>
#include <ostream>
#include <set>
#include <list>
#include <vector>
#include <map>
#include <string>
#include <unordered_map>
#include <iostream>

using namespace std;
/*
struct LesserString
{
  bool operator() (const char *lhs, const char *rhs) const
  {
    return std::strcmp(lhs, rhs) < 0;
  }
};
*/
struct HashString
{
  std::size_t operator() (const string_view &arg) const
  {
    auto hashfn = std::hash<std::string_view> {};
    return hashfn(arg);
  }
};

struct EqualString
{
  bool operator() (const string_view &lhs, const string_view &rhs) const
  {

    //std::cout << "compare: " << std::string(lhs) << " - " << std::string(rhs) << " = " << (std::string(lhs) == std::string(rhs) ? "1" : "0") << std::endl;

    return lhs == rhs;
  }
};

class InvertedIndex 
{
public:
  InvertedIndex()
  {
    docs.reserve(50000);
  }

  void Add(string &document);
  const std::vector<size_t>& Lookup(const string_view& word) const;

  const string& GetDocument(size_t id) const {
    return docs[id];
  }

private:
  std::unordered_map<std::string_view, std::vector<size_t>> index; // , HashString, EqualString
  vector<string> docs;
};

class SearchServer 
{
public:
  SearchServer();
  explicit SearchServer(istream& document_input);
  void UpdateDocumentBase(istream& document_input);
  void AddQueriesStream(istream& query_input, ostream& search_results_output);

private:
  void reset();

private:
  InvertedIndex index;

  //std::vector<std::pair<int, int>> docid_count;
};
