#include "test_runner.h"
//#include "profile.h"

#include <algorithm>
#include <numeric>
#include <vector>
#include <string>
#include <random>
#include <future>
#include <mutex>
#include <string>
#include <thread>


using namespace std;

template <typename K, typename V>
class ConcurrentMap
{
    struct Chunk
    {
        Chunk()
        {
        }

        Chunk(const Chunk &source)
        {
           data = source.data;
        }
        std::mutex mtx;
        std::map<K, V> data;
    };

public:
  static_assert(is_integral_v<K>, "ConcurrentMap supports only integer keys");

  struct Access 
  {
    std::lock_guard<std::mutex> guard;
    V& ref_to_value;
  };

  explicit ConcurrentMap(size_t bucket_count)
  {
      m_chunks.resize(bucket_count);
  }

  Access operator[](const K& key)
  {
    const int bucket_size = m_chunks.size();

    int bucket_index = std::abs(static_cast<int>(key)) % bucket_size;

    auto &chunk = m_chunks[bucket_index];

    return {std::lock_guard<std::mutex>(chunk.mtx), 
        [&]() -> V& {
          auto iter_find = chunk.data.find(key);
          return (iter_find != chunk.data.end()) ? iter_find->second : chunk.data[key];
        }()
      };
  }

  map<K, V> BuildOrdinaryMap()
  {
      map<K, V> out;

      for (size_t i = 0; i < m_chunks.size(); ++i)
      {
          auto &chunk = m_chunks[i];

          std::lock_guard<std::mutex> lock(chunk.mtx);
          out.insert(chunk.data.begin(), chunk.data.end());  
      }

      return out;
  }

private:


private:
    std::vector<Chunk> m_chunks;
};

/*
void RunConcurrentUpdates(
    ConcurrentMap<int, int>& cm, size_t thread_count, int key_count
) 
{
  auto kernel = [&cm, key_count](int seed)
  {
    vector<int> updates(key_count);
    iota(begin(updates), end(updates), -key_count / 2);
    shuffle(begin(updates), end(updates), default_random_engine(seed));

    for (int i = 0; i < 2; ++i) {
      for (auto key : updates) 
      { 
        //std::cerr << "pre update" << std::endl;
        cm[key].ref_to_value++;
        if (key % 10 == 0)
        {
          //std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
        //std::cerr << "post update" << std::endl;
      }
    }
  };

  //std::cerr << "1" << std::endl;
  vector<future<void>> futures;
  for (size_t i = 0; i < thread_count; ++i) {
    futures.push_back(async(kernel, i));
  }
}

void TestConcurrentUpdate() {
  const size_t thread_count = 3;
  const size_t key_count = 50000;

  ConcurrentMap<int, int> cm(thread_count);
  RunConcurrentUpdates(cm, thread_count, key_count);

  const auto result = cm.BuildOrdinaryMap();
  ASSERT_EQUAL(result.size(), key_count);
  for (auto& [k, v] : result) {
    AssertEqual(v, 6, "Key = " + to_string(k));
  }
}

void TestReadAndWrite() {
  ConcurrentMap<size_t, string> cm(5);

  auto updater = [&cm] {
    for (size_t i = 0; i < 50000; ++i) {
      cm[i].ref_to_value += 'a';
    }
  };
  auto reader = [&cm] {
    vector<string> result(50000);
    for (size_t i = 0; i < result.size(); ++i) {
      result[i] = cm[i].ref_to_value;
    }
    return result;
  };

  auto u1 = async(updater);
  auto r1 = async(reader);
  auto u2 = async(updater);
  auto r2 = async(reader);

  u1.get();
  u2.get();

  for (auto f : {&r1, &r2}) {
    auto result = f->get();
    ASSERT(all_of(result.begin(), result.end(), [](const string& s) {
      return s.empty() || s == "a" || s == "aa";
    }));
  }
}

void TestSpeedup() {
  {
    ConcurrentMap<int, int> single_lock(1);

    //LOG_DURATION("Single lock");
    RunConcurrentUpdates(single_lock, 4, 50000);
  }
  {
    ConcurrentMap<int, int> many_locks(100);

    //LOG_DURATION("100 locks");
    RunConcurrentUpdates(many_locks, 4, 50000);
  }
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestConcurrentUpdate);
  RUN_TEST(tr, TestReadAndWrite);
  RUN_TEST(tr, TestSpeedup);
}*/