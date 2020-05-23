#include "search_server.h"
#include "iterator_range.h"
#include "parse.h"

#include <algorithm>
#include <iterator>
#include <sstream>
#include <iostream>

static const size_t MAX_SIZE = 50000;


std::vector<std::string_view> SplitIntoWords(const string& line) 
{
  return split_str(line, ' ');
}

SearchServer::SearchServer()
//: docid_count(MAX_SIZE, {0, 0})
{
  /*for (int i = 0; i < MAX_SIZE; i++)
  {
    docid_count[i] = {i, 0};
  }*/
}

SearchServer::SearchServer(istream& document_input) 
: SearchServer()
{
  UpdateDocumentBase(document_input);
}

void SearchServer::UpdateDocumentBase(istream& document_input) 
{
  InvertedIndex new_index;

  for (std::string current_document; getline(document_input, current_document); )
  {
    new_index.Add(current_document);
  }

  index = move(new_index);
}

struct Node { 
    int value = 1; 
};

void SearchServer::AddQueriesStream(istream& query_input, ostream& search_results_output)
{
  std::vector<size_t> _docid_count(MAX_SIZE, 0);

  for (string current_query; getline(query_input, current_query); )
  {
    //reset();

    const auto words = SplitIntoWords(current_query);

    std::map<std::string_view, size_t> doc_words;

    for (const auto& word : words)
    {
      auto iter_find = doc_words.find(word);

      if (iter_find != doc_words.end())
      {
        iter_find->second++;
      }
      else
      {
        doc_words[word] = 1;
      }
    }

    size_t max_doc = 0;
    for (const auto& word : doc_words)
    {
      for (const size_t docid : index.Lookup(word.first)) 
      {
        _docid_count[docid] += word.second;

        max_doc = std::max<size_t>(max_doc, docid);
      }
    }

    vector<pair<size_t, size_t>> search_results; //(docid_count.begin(), docid_count.end());

    for (int idx = 0; idx <= max_doc; idx++)
    {
      auto count = _docid_count[idx];//.second;
      
      if (count > 0)
      {
        search_results.push_back({idx, count});
      }
    }

    std::partial_sort(
      begin(search_results),
      begin(search_results) + min<size_t>(5, search_results.size()),
      end(search_results),
      [](pair<size_t, size_t> &lhs, pair<size_t, size_t> &rhs)
      {
        int64_t lhs_docid = lhs.first;
        auto lhs_hit_count = lhs.second;
        int64_t rhs_docid = rhs.first;
        auto rhs_hit_count = rhs.second;
        return make_pair(lhs_hit_count, -lhs_docid) > make_pair(rhs_hit_count, -rhs_docid);
      }
    );

    //std::cout << "SORTED:" << std::endl;

    search_results_output << current_query << ':';
    for (auto &p : Head(search_results, 5)) 
    {
      if (p.second > 0)
      {
        search_results_output << " {"
          << "docid: " << p.first << ", "
          << "hitcount: " << p.second << '}';
      }
      
        //std::cout << "11:" << std::endl;
    }
    //std::cout << "QUEUED:" << std::endl;
    search_results_output << endl;

    std::fill(_docid_count.begin(), _docid_count.end(), 0);
  }
}

void SearchServer::reset()
{
 /* for (int i = 0; i < MAX_SIZE; i++)
  {
    docid_count[i] = {i, 0};
  }*/
}

void InvertedIndex::Add(string& document)
{
  docs.emplace_back(document);

  const size_t docid = docs.size() - 1;

  for (auto &word : SplitIntoWords(docs[docid]))
  {
    auto iter_find = index.find(word);

    if (iter_find != index.end())
    {
      iter_find->second.push_back(docid);
    }
    else
    {
      index[std::move(word)] = {docid};
    }
  }
}

static const std::vector<size_t> empty_list = {};

const std::vector<size_t>& InvertedIndex::Lookup(const string_view& word) const 
{
  auto iter_find = index.find(word);

  return iter_find != index.end() ? iter_find->second : empty_list;
}
