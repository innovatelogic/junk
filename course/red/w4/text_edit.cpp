#include <string>
#include "test_runner.h"
#include <list>

using namespace std;

class Editor 
{
 public:

  Editor()
  : m_pos(m_list.end())
  {}

  void Left()
  {
      if (!m_list.empty() && m_pos != m_list.begin()) {
          --m_pos;
      }
  }

  void Right()
  {
    if (!m_list.empty() && m_pos != m_list.end()) {
        ++m_pos;
    }
  }

  void Insert(char token)
  {
      if (m_list.empty() || m_pos == m_list.end())
      {
          m_list.push_back(token);
          m_pos = m_list.end();
      }
      else
      {
         m_list.insert(m_pos, token);
      }
  }

  void Cut(size_t tokens = 1)
  {
    Copy(tokens);

    auto last = m_pos;
    safe_advance(last, tokens);

    m_pos = m_list.erase(m_pos, last);
  }

  void Copy(size_t tokens = 1)
  {
    auto last = m_pos;
    safe_advance(last, tokens);

    //std::cout << std::distance(m_pos, last) << std::endl;

    m_buffer.resize(std::distance(m_pos, last));

    int i = 0;
    for (auto it = m_pos; it != last; it++){
        m_buffer[i++] = *it;
    }

    //std::cout << "Copy to buffer: [" << m_buffer << "]" << std::endl;
  }

  void Paste()
  {
      for (int i = 0; i < m_buffer.size(); ++i){
          Insert(m_buffer[i]);
      }
  }

  string GetText() const
  {
      std::string out;

      out.resize(m_list.size());
      const auto end = m_list.end();
      int i = 0;
      for (auto it = m_list.begin(); it != end; ++it){
          out[i++] = *it;
      }
      return out;
  }

  void safe_advance(std::list<char>::iterator &iter, int steps)
  {
      for (; steps > 0 && iter != m_list.end(); --steps){
          ++iter;
      }
  }

  void print() const
  {
      std::cout << '[';
      const auto end = m_list.end();
      for (auto it = m_list.begin(); it != end; ++it)
      {
          std::cout << ((m_pos == it) ? "|" : "") << *it;
      }

      if (m_pos == m_list.end()){
          std::cout << "|";
      }
      std::cout << "]" << std::endl;
  }
    
  void print(const std::list<char>::iterator &pos) const
  {
      const auto end = m_list.end();
      for (auto it = m_list.begin(); it != end; ++it)
      {
          std::cout << ((pos == it) ? "|" : "") << *it;
      }

      if (m_pos == m_list.end()){
          std::cout << "|";
      }
      std::cout << std::endl;
  }

private:
    std::list<char> m_list;
    std::list<char>::iterator m_pos;

    std::string m_buffer;
};

void TypeText(Editor& editor, const string& text) {
  for(char c : text) {
    editor.Insert(c);
  }
}

void TestEditing() {
  {
    Editor editor;

    const size_t text_len = 12;
    const size_t first_part_len = 7;
    TypeText(editor, "hello, world");

    for(size_t i = 0; i < text_len; ++i) {
      editor.Left();
    }

    editor.Cut(first_part_len);

    for(size_t i = 0; i < text_len - first_part_len; ++i) {
      editor.Right();
    }

    TypeText(editor, ", ");
    //editor.print();
    editor.Paste();
    //editor.print();
    editor.Left();
    editor.Left();
    //editor.print();

    //editor.print();

    editor.Cut(3);

    //std::cout << "22" << std::endl;

    //editor.print();
    
    ASSERT_EQUAL(editor.GetText(), "world, hello");
  }
  {
    Editor editor;
    
    TypeText(editor, "misprnit");
    editor.Left();
    editor.Left();
    editor.Left();
    editor.Cut(1);
    editor.Right();
    editor.Paste();
    
    ASSERT_EQUAL(editor.GetText(), "misprint");
  }
}

void TestReverse() {
  Editor editor;

  const string text = "esreveR";
  for(char c : text) {
    editor.Insert(c);
    editor.Left();
  }
  
  ASSERT_EQUAL(editor.GetText(), "Reverse");
}

void TestNoText() {
  Editor editor;
  ASSERT_EQUAL(editor.GetText(), "");
  
  editor.Left();
  editor.Left();
  editor.Right();
  editor.Right();
  editor.Copy(0);
  editor.Cut(0);
  editor.Paste();
  
  ASSERT_EQUAL(editor.GetText(), "");
}

void TestEmptyBuffer() {
  Editor editor;

  editor.Paste();
  TypeText(editor, "example");
  editor.Left();
  editor.Left();
  editor.Paste();
  editor.Right();
  editor.Paste();
  editor.Copy(0);
  editor.Paste();
  editor.Left();
  editor.Cut(0);
  editor.Paste();
  
  ASSERT_EQUAL(editor.GetText(), "example");
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestEditing);
  RUN_TEST(tr, TestReverse);
  RUN_TEST(tr, TestNoText);
  RUN_TEST(tr, TestEmptyBuffer);
  return 0;
}

/*
#include <list>
#include <string>

using namespace std;

class Editor {
public:
  Editor()
    : pos(text.end()) {
  }

  void Left() {
    pos = Advance(pos, -1);
  }

  void Right() {
    pos = Advance(pos, 1);
  }

  void Insert(char token) {
    text.insert(pos, token);
  }

  void Cut(size_t tokens = 1) {
    auto pos2 = Advance(pos, tokens);
    buffer.assign(pos, pos2);
    pos = text.erase(pos, pos2);
  }

  void Copy(size_t tokens = 1) {
    auto pos2 = Advance(pos, tokens);
    buffer.assign(pos, pos2);
  }

  void Paste() {
    text.insert(pos, buffer.begin(), buffer.end());
  }

  string GetText() const {
    return {text.begin(), text.end()};
  }
 
private:
  using Iterator = list<char>::iterator;
  list<char> text;
  list<char> buffer;
  Iterator pos;

  Iterator Advance(Iterator it, int steps) const {
    while (steps > 0 && it != text.end()) {
      ++it;
      --steps;
    }
    while (steps < 0 && it != text.begin()) {
      --it;
      ++steps;
    }
    return it;
  }
};
*/