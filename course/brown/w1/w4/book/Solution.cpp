#include "Common.h"

using namespace std;

class LruCache : public ICache 
{
public:
  LruCache(
      shared_ptr<IBooksUnpacker> books_unpacker,
      const Settings& settings
  ) : m_settings(settings)
  {
    // реализуйте метод
  }

  BookPtr GetBook(const string& book_name) override
  {
    return nullptr;
  }

    std::list<IBook> m_cache_rank;
    std::unordered_map<std::string, IBook> m_cache;

    Settings m_settings;
    shared_ptr<IBooksUnpacker> m_books_unpacker;
};


unique_ptr<ICache> MakeCache(
    shared_ptr<IBooksUnpacker> books_unpacker,
    const ICache::Settings& settings
)
{
    return std::make_shared<LruCache>(books_unpacker, settings);
}