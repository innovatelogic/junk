#include <algorithm>
#include <string>
#include <vector>
#include <set>
#include <iostream>
#include <sstream>

using namespace std;

class Learner {
 private:
  std::set<std::string> dict;

 public:
    int Learn(const vector<string>& words)
    {
        size_t count_prev = dict.size();

        for (const auto& word : words) {
            dict.insert(word);
        }

        size_t count_new = dict.size();
        return count_new - count_prev;
    }

    std::vector<std::string> KnownWords()
    {
        return {dict.begin(), dict.end()};
    }
};


/*
int main() {
  Learner learner;
  string line;
  while (getline(cin, line)) {
    vector<string> words;
    stringstream ss(line);
    string word;
    while (ss >> word) {
      words.push_back(word);
    }
    cout << learner.Learn(words) << "\n";
  }
  cout << "=== known words ===\n";
  for (auto word : learner.KnownWords()) {
    cout << word << "\n";
  }
}*/