#include "test_runner.h"

#include <map>
#include <string>
#include <future>
#include <functional>
#include <iostream>
#include <set>
#include <sstream>
#include <cmath>

using namespace std;


template <class Iterator>
class IteratorRange
{
public:  
    IteratorRange(Iterator begin, Iterator end)
    : _begin(begin)
    , _end(end)
    {}

    //Iterator begin() { return _begin; }
    //Iterator end() { return _end; }

    Iterator begin() const { return _begin; }
    Iterator end() const { return _end; }

    size_t size() const { return std::distance(begin(), end()); }

    Iterator _begin;
    Iterator _end;
};

template <typename Iterator>
class Paginator 
{
public:
  Paginator(Iterator begin, Iterator end, size_t page_size)
  : _begin(begin)
  , _end(end)
  , _page_size(page_size)
  {
      const size_t size = std::distance(begin, end);
      const size_t chunks = std::ceil((float)size / page_size);

      auto idx_last = size - 1;

      for (int chunk = 0; chunk < chunks; ++chunk)
      {
        auto idx_offset = chunk * page_size;
        
        Iterator first = begin + idx_offset;
        
        Iterator last = first + ((idx_offset + page_size <= idx_last) ? (page_size - 1) : idx_last - idx_offset);

        pages.push_back(IteratorRange<Iterator>(first, last + 1));
      }
  }

  auto begin() { return pages.begin(); }
  auto end() { return pages.end(); }

  //typename std::vector<IteratorRange<Iterator>>::const_iterator begin() const { return pages.begin(); }
  //typename std::vector<IteratorRange<Iterator>>::const_iterator end() const { return pages.end(); }

  size_t size() const { return pages.size(); }

private:  
  Iterator _begin;
  Iterator _end;
  size_t _page_size;

  std::vector<IteratorRange<Iterator>> pages;
};

static const std::string DELIMS = " ";

struct Stats
{
  map<string, int> word_frequences;

  void operator += (const Stats& other)
  {
      for (auto &w : other.word_frequences)
      {
          if (word_frequences.count(w.first) == 0){
              word_frequences[w.first] = w.second;
          } else {
              word_frequences[w.first] += w.second;
          }
      }
  }

  void add_word(const std::string &word)
  {
    auto iter_find = word_frequences.find(word);

    if (iter_find != word_frequences.end()) {
        iter_find->second++;
    } else {
        word_frequences[word] = 1;
    }
  }

  void print()
  {
    for (auto &w : word_frequences)
    {
        std::cout << w.first << " " << w.second << std::endl;
    }
  }
};

Stats ExploreLine(const set<string>& key_words, const string& line) 
{
    Stats out;

    size_t word_begin = line.find_first_not_of(DELIMS, 0);

    while (word_begin != std::string::npos)
    {
        auto word_end = line.find_first_of(DELIMS, word_begin);

        if (word_end == std::string::npos)
        {
             auto key = line.substr(word_begin);

             if (key_words.find(key) != key_words.end()) {
                out.add_word(key);
             }
             break;
        }
       
        auto key = line.substr(word_begin, word_end - word_begin);
      
        if (key_words.find(key) != key_words.end()) {
            out.add_word(key);
        }

        word_begin = line.find_first_not_of(DELIMS, word_end + 1);
    }

    return out;
}
/*
Stats ExploreKeyWordsSingleThread( const set<string>& key_words, Paginator<std::vector<std::string>::const_iterator> &page) 
{
  //std::istreambuf_iterator<char> eos;
  //std::string str(std::istreambuf_iterator<char>(input), eos);

  for (auto &p : page)
  {
     //return ExploreLine(key_words, *p);
  }


}*/

Stats ExploreKeyWords(const set<string>& key_words, istream& input) 
{
    Stats result;

    std::vector<std::future<Stats>> futures;
    std::vector<std::string> buffers;

    const size_t max_str = 1024;

    for (string line; getline(input, line); )
    {
        buffers.push_back(std::move(line));
    }


    Paginator<std::vector<std::string>::const_iterator> paginator(buffers.begin(), buffers.end(), 1000);

    for (const auto &page : paginator)
    {
        futures.push_back(std::async([&page, &key_words]
        {
            Stats res;

            for (const auto &p : page)
            {
                res += ExploreLine(key_words, p);
            }

            return res;
        })); //ExploreKeyWordsSingleThread, ref(key_words), page));
    }

    for (auto &f : futures)
    {
        result += f.get();
    }

/*

    for (string line; getline(input, line); )
    {
        auto &buffer_last = *(buffers.end() - 1);

        buffer_last << line << " ";

        buffer_last.seekp(0, ios::end);
        stringstream::pos_type offset = buffer_last.tellp();

        buffer_last.seekp(0, ios::cur);

        if (offset >= max_str)
        {
            futures.push_back(std::async(ExploreKeyWordsSingleThread, ref(key_words), ref(buffer_last)));
            buffers.push_back(stringstream());
        }
    }

    auto &buffer_last = *(buffers.end() - 1);

    buffer_last.seekp(0, ios::end);
    stringstream::pos_type offset = (buffer_last).tellp();
    buffer_last.seekp(0, ios::cur);

    if (offset > 0){
        //std::cout << offset << std::endl;
        futures.push_back(std::async(ExploreKeyWordsSingleThread, ref(key_words), ref(buffer_last)));
    }
   
    for (auto &f : futures)
    {
        result += f.get();
    }*/

  return result;
}
/*
void TestBasic()
{
  const set<string> key_words = {"yangle", "rocks", "sucks", "all"};

  stringstream ss;
  ss << "this new    yangle     service really rocks\n";
  ss << "It sucks when yangle isn't available\n";
  ss << "10 reasons why     yangle  is the best IT company\n";
  ss << "    yangle rocks others suck\n";
  ss << "Goondex really sucks, but yangle rocks. Use yangle\n";

  const auto stats = ExploreKeyWords(key_words, ss);
  const map<string, int> expected = {
    {"yangle", 6},
    {"rocks", 2},
    {"sucks", 1}
  };
  ASSERT_EQUAL(stats.word_frequences, expected);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestBasic);
}*/