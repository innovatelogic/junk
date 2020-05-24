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

SearchServer::~SearchServer()
{
  for (auto &t : joints){
    t.get();
  }
}

SearchServer::SearchServer(istream& document_input) 
: index(document_input)
{
}

void UpdateIndex(istream& document_input, SearchServer &self)
{
    InvertedIndex new_index(document_input);
    std::swap(self._index().GetAccess().ref_to_value, new_index);
}

void SearchServer::UpdateDocumentBase(istream& document_input) 
{
    joints.push_back(std::async(UpdateIndex, std::ref(document_input), std::ref(*this)));
}

struct Node { 
    int value = 0; 
};

void ProcessQueue(istream& query_input, ostream& search_results_output, SearchServer &self)
{
  std::vector<std::pair<size_t, size_t>> search_results;

  for (string current_query; getline(query_input, current_query); )
  {
    const auto words = split_str(current_query, ' ');

    std::map<std::string_view, Node> doc_words;

    for (const auto& word : words)
    {
       doc_words[word].value++;
    }

    {
        auto access = self._index().GetAccess();

        const size_t sz = access.ref_to_value.size();
        if (search_results.size() != sz) {
            search_results.resize(sz, {0, 0});
        }
        else{
            std::fill(search_results.begin(), search_results.end(), std::pair<size_t, size_t>({0,0}));
        }

        for (const auto& word : doc_words)
        {
            const auto &docs_in = access.ref_to_value.Lookup(word.first);

            for (const size_t docid : docs_in) 
            {
                search_results[docid].first = docid;
                search_results[docid].second += word.second.value;
            }
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
    });

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
    search_results_output << '\n';
  }
}

void SearchServer::AddQueriesStream(istream& query_input, ostream& search_results_output)
{
    joints.push_back(std::async(ProcessQueue, std::ref(query_input), std::ref(search_results_output), std::ref(*this)));
}

InvertedIndex::InvertedIndex(istream &document_input) 
{
    for (string current_document; getline(document_input, current_document);) 
    {
        docs.push_back(move(current_document));

        size_t docid = docs.size() - 1;

        for (string_view word : split_str(docs.back(), ' ')) 
        {
            auto &docids = index[word];

            docids.push_back(docid);
        }
    }
}

void InvertedIndex::Add(string& document)
{
  docs.push_back(std::move(document));

  const size_t docid = docs.size() - 1;

  for (auto &word : SplitIntoWords(docs[docid]))
  {
    //std::cerr << word << std::endl;

    auto iter_find = index.find(word);

    if (iter_find != index.end())
    {
      iter_find->second.push_back(docid);
    }
    else
    {
      index[word] = {docid};
    }
  }
}

static const std::vector<size_t> empty_list = {};

const std::vector<size_t>& InvertedIndex::Lookup(const string_view& word) const 
{
  auto iter_find = index.find(word);

  return iter_find != index.end() ? iter_find->second : empty_list;
}
