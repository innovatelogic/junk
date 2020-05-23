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
  //auto words = split_str(line, ' ');
  //std::sort(std::begin(words), std::end(words));
 // words.erase(std::unique(words.begin(), words.end()), words.end());
 // return words;
}

SearchServer::SearchServer()
{
  //first_time_call = true;
}

SearchServer::~SearchServer()
{
  /*for (auto &t : joints){
    t.get();
  }*/
}

SearchServer::SearchServer(istream& document_input) 
: SearchServer()
{
  UpdateDocumentBase(document_input);
}

void SearchServer::UpdateDocumentBase(istream& document_input) 
{
  if (joints.empty())
  {
    InvertedIndex new_index;

    for (std::string current_document; getline(document_input, current_document); )
    {
      new_index.Add(current_document);
    }
    index.GetAccess().ref_to_value = move(new_index);
    
    first_time_call = false;
  }
  else
  {
    joints.push_back(std::async([&] 
    {
      InvertedIndex new_index;

      for (std::string current_document; getline(document_input, current_document); )
      {
        new_index.Add(current_document);
      }
      
      {
        std::swap(index.GetAccess().ref_to_value, new_index);
      }
    }));
  }
}

struct Node { 
    int value = 0; 
};

void SearchServer::AddQueriesStream(istream& query_input, ostream& search_results_output)
{
  std::vector<size_t> _docid_count(MAX_SIZE, 0);
  //(MAX_SIZE, {0, 0});

  for (string current_query; getline(query_input, current_query); )
  {
    const auto words = split_str(current_query, ' '); //SplitIntoWords(current_query);

    std::map<std::string_view, Node> doc_words;

    for (const auto& word : words)
    {
       doc_words[word].value++;
    }

    size_t max_doc = 0;
    {
      for (const auto& word : doc_words)
      {
        const auto &docs_in = index.GetAccess().ref_to_value.Lookup(word.first);

        for (const size_t docid : docs_in) 
        {
          _docid_count[docid] += word.second.value;

          max_doc = std::max<size_t>(max_doc, docid);
        }
      }
    }

    std::vector<std::pair<size_t, size_t>> search_results;
    for (int idx = 0; idx <= max_doc; idx++)
    {
      auto count = _docid_count[idx];
      
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
    }
    //std::cout << "QUEUED:" << std::endl;
    search_results_output << endl;

    std::fill(_docid_count.begin(), _docid_count.end(), 0);
    //std::fill(search_results.begin(), search_results.end(), std::pair<size_t, size_t>({0,0}));
  }
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
