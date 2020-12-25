#include "Common.h"
#include <mutex>
#include <list>
#include <string>
#include <iostream>
#include <assert.h>

using namespace std;

class LruCache : public ICache
{
struct CacheData
{
BookPtr book;
std::string name;
size_t content_size;
};

public:
LruCache(
shared_ptr<IBooksUnpacker> books_unpacker,
const Settings& settings
)
: m_books_unpacker(books_unpacker)
, m_settings(settings)
, m_alloc_size(0)
{
// реализуйте метод
}

BookPtr GetBook(const string& book_name) override
{
BookPtr out = nullptr;

//sstd::cout << "========" << std::endl;

std::lock_guard<std::mutex> lock(m_mutex);

//std::cout << "A-01" << std::endl;

for (std::list<CacheData>::iterator it = m_cache_rank.begin(); it != m_cache_rank.end(); ++it)
{
auto cache_data = *it;

if (cache_data.name == book_name)
{
auto book = *it;

m_cache_rank.erase(it);

m_cache_rank.push_front(cache_data);

return cache_data.book;
}
}

//std::cout << "B-01" << std::endl;

//if (!out)
{
auto new_book = m_books_unpacker->UnpackBook(book_name);

if (!new_book){
return nullptr;
}

const std::string new_book_name = new_book->GetName();
const size_t new_book_size = new_book->GetContent().size();
//std::cout << new_book->GetName() << " " << new_book->GetContent() << " " << new_book->GetContent().size() << std::endl;

auto new_size = m_alloc_size;

//std::cout << "A-01" << std::endl;
std::list<CacheData>::reverse_iterator it = m_cache_rank.rbegin();

for (; it != m_cache_rank.rend(); ++it)
{
auto &cache_data = *it;
if (new_size + new_book_size > m_settings.max_memory)
{
new_size -= cache_data.content_size;
continue;
}

break;
}
//std::cout << "B-01" << std::endl;

if (new_size < m_alloc_size)
{
if (it == m_cache_rank.rend())
{
//std::cerr << "A-C" << std::endl;
m_cache_rank.clear();
m_alloc_size = 0;

//std::cerr << "B-C" << std::endl;
}
else
{
auto it_erase = ((it).base());

//std::cout << "erase: " << (*it_erase).name << std::endl;
//std::cerr << "A" << std::endl;
m_cache_rank.erase(it_erase, m_cache_rank.end());

//std::cerr << "B" << std::endl;
m_alloc_size = new_size;
}
}

if (m_alloc_size + new_book_size <= m_settings.max_memory)
{
//std::cerr << "AA-01" << std::endl;

m_cache_rank.push_front({std::move(new_book), new_book_name, new_book_size});

m_alloc_size += new_book_size;

out = m_cache_rank.begin()->book;

//std::cerr << "BB-01" << std::endl;
}
else
{
out = std::move(new_book);
}
}
/*
std::cout << "[cache]:" << std::endl;
for (auto it : m_cache_rank)
{
std::cout << it->GetName() << " " << it->GetContent().size() << std::endl;
}
std::cout << "alloc size: " << m_alloc_size << std::endl;
*/
return out;
}


std::list<CacheData> m_cache_rank;
size_t m_alloc_size;

Settings m_settings;
shared_ptr<IBooksUnpacker> m_books_unpacker;

std::mutex m_mutex;
};


unique_ptr<ICache> MakeCache(
shared_ptr<IBooksUnpacker> books_unpacker,
const ICache::Settings& settings
)
{
return std::make_unique<LruCache>(books_unpacker, settings);
}

/*

#include "Common.h"

#include <algorithm>
#include <cassert>
#include <future>
#include <mutex>
#include <numeric>
#include <random>
#include <sstream>
#include <unordered_map>


using namespace std;

class LruCache : public ICache {
public:
LruCache(
std::shared_ptr<IBooksUnpacker> books_unpacker,
const Settings& settings
)
: books_unpacker_(move(books_unpacker))
, settings_(settings)
{}

BookPtr GetBook(const string& book_name) override {
lock_guard guard(mutex_);

auto it = books_.find(book_name);

if (it == books_.end()) {
Entry entry;
entry.book = books_unpacker_->UnpackBook(book_name);

auto book_size = entry.book->GetContent().size();

while (!books_.empty() && cache_size_ + book_size > settings_.max_memory) {
RemoveLruEntry();
}
assert(!books_.empty() || cache_size_ == 0);

if (book_size > settings_.max_memory) {
return move(entry.book);
}

it = AddEntry(book_name, move(entry));
}

it->second.rank = current_rank_++;

return it->second.book;
}

private:
struct Entry {
BookPtr book;
int rank = 0;
};

using Entries = unordered_map<string, Entry>;

private:
void RemoveLruEntry() {
assert(!books_.empty());

auto it = min_element(
books_.begin(), books_.end(),
[](const Entries::value_type& lhs, const Entries::value_type& rhs) {
return lhs.second.rank < rhs.second.rank;
}
);

cache_size_ -= it->second.book->GetContent().size();
books_.erase(it);
}

Entries::iterator AddEntry(const string& book_name, Entry entry) {
assert(0 == books_.count(book_name));
cache_size_ += entry.book->GetContent().size();
return books_.insert({book_name, move(entry)}).first;
}

private:
std::shared_ptr<IBooksUnpacker> books_unpacker_;
const Settings settings_;

mutex mutex_;
Entries books_;
int current_rank_ = 0;
size_t cache_size_ = 0;
};


unique_ptr<ICache> MakeCache(
std::shared_ptr<IBooksUnpacker> books_unpacker,
const ICache::Settings& settings
) {
return make_unique<LruCache>(move(books_unpacker), settings);
}



*/