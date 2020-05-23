#include "test_runner.h"

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

template <typename Token>
using Sentence = vector<Token>;


template <typename Token>
std::vector<size_t> PreCount(const vector<Token> &tokens)
{
    std::vector<size_t> counter;

    auto sent_begin = tokens.begin();
    auto sent_end = tokens.end();

    while (sent_begin != tokens.end())
    {
        sent_end = std::find_if(sent_begin, tokens.end(), [](auto &token) {
            return token.IsEndSentencePunctuation();
        });

        while (sent_end != tokens.end() && sent_end->IsEndSentencePunctuation()) {
            sent_end++;
        }

        counter.push_back(sent_end - sent_begin);
        sent_begin = sent_end;
    }

    size_t last = sent_end - sent_begin;
    if (sent_end - sent_begin > 0){
        counter.push_back(last);
    }

    return counter;
}

// ÐšÐ»Ð°ÑÑ Token Ð¸Ð¼ÐµÐµÑ‚ Ð¼ÐµÑ‚Ð¾Ð´ bool IsEndSentencePunctuation() const
template <typename Token>
vector<Sentence<Token>> SplitIntoSentences(vector<Token> tokens)
{
    std::vector<size_t> counter = PreCount(tokens);

    /*std::cerr << "PreCount" << std::endl;

    for (auto c : counter)
    {
        std::cout << c << ' ';
    }
    std::cout << std::endl;*/

    vector<Sentence<Token>> res(counter.size());

    size_t idx = 0;
    for (auto &r : res) {
        r.reserve(counter[idx++]);
    }

    auto sent_begin = tokens.begin();
    auto sent_end = tokens.end();

    idx = 0;
    while (sent_begin != tokens.end())
    {
        sent_end = std::find_if(sent_begin, tokens.end(), [](auto &token) {
            return token.IsEndSentencePunctuation();
        });

        while (sent_end != tokens.end() && sent_end->IsEndSentencePunctuation()) {
            sent_end++;
        }

        const size_t size = sent_end - sent_begin;

        for (int i = 0; i < size; i++)
        {
            res[idx].push_back(std::move(*(sent_begin++)));
        }
        idx++;
    }

    return res;
}

/*

template <typename TokenForwardIt>
TokenForwardIt FindSentenceEnd(TokenForwardIt tokens_begin, TokenForwardIt tokens_end) {
  const TokenForwardIt before_sentence_end =
      adjacent_find(tokens_begin, tokens_end,
                    [](const auto& left_token, const auto& right_token) {
                      return left_token.IsEndSentencePunctuation()
                          && !right_token.IsEndSentencePunctuation();
                    });
  return before_sentence_end == tokens_end
      ? tokens_end
      : next(before_sentence_end);
}

// Класс Token имеет метод bool IsEndSentencePunctuation() const
template <typename Token>
vector<Sentence<Token>> SplitIntoSentences(vector<Token> tokens) {
  vector<Sentence<Token>> sentences;
  auto tokens_begin = begin(tokens);
  const auto tokens_end = end(tokens);
  while (tokens_begin != tokens_end) {
    const auto sentence_end = FindSentenceEnd(tokens_begin, tokens_end);
    Sentence<Token> sentence;
    for (; tokens_begin != sentence_end; ++tokens_begin) {
      sentence.push_back(move(*tokens_begin));
    }
    sentences.push_back(move(sentence));
  }
  return sentences;
}

*/


struct TestToken {
  string data;
  bool is_end_sentence_punctuation = false;

  bool IsEndSentencePunctuation() const {
    return is_end_sentence_punctuation;
  }
  bool operator==(const TestToken& other) const {
    return data == other.data && is_end_sentence_punctuation == other.is_end_sentence_punctuation;
  }
};

ostream& operator<<(ostream& stream, const TestToken& token) {
  return stream << token.data;
}
/*
// Ð¢ÐµÑÑ‚ ÑÐ¾Ð´ÐµÑ€Ð¶Ð¸Ñ‚ ÐºÐ¾Ð¿Ð¸Ñ€Ð¾Ð²Ð°Ð½Ð¸Ñ Ð¾Ð±ÑŠÐµÐºÑ‚Ð¾Ð² ÐºÐ»Ð°ÑÑÐ° TestToken.
// Ð”Ð»Ñ Ð¿Ñ€Ð¾Ð²ÐµÑ€ÐºÐ¸ Ð¾Ñ‚ÑÑƒÑ‚ÑÑ‚Ð²Ð¸Ñ ÐºÐ¾Ð¿Ð¸Ñ€Ð¾Ð²Ð°Ð½Ð¸Ð¹ Ð² Ñ„ÑƒÐ½ÐºÑ†Ð¸Ð¸ SplitIntoSentences
// Ð½ÐµÐ¾Ð±Ñ…Ð¾Ð´Ð¸Ð¼Ð¾ Ð½Ð°Ð¿Ð¸ÑÐ°Ñ‚ÑŒ Ð¾Ñ‚Ð´ÐµÐ»ÑŒÐ½Ñ‹Ð¹ Ñ‚ÐµÑÑ‚.
void TestSplitting() {
  ASSERT_EQUAL(
    SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!"}})),
    vector<Sentence<TestToken>>({
        {{"Split"}, {"into"}, {"sentences"}, {"!"}}
    })
  );

  ASSERT_EQUAL(
    SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!", true}})),
    vector<Sentence<TestToken>>({
        {{"Split"}, {"into"}, {"sentences"}, {"!", true}}
    })
  );

  ASSERT_EQUAL(
    SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}, {"Without"}, {"copies"}, {".", true}})),
    vector<Sentence<TestToken>>({
        {{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}},
        {{"Without"}, {"copies"}, {".", true}},
    })
  );
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestSplitting);
  return 0;
}*/