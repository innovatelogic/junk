#pragma once

#include <cstdlib>
#include <cstring>

template <typename T>
class SimpleVector {
public:
  SimpleVector()
  : m_data(nullptr)
  , m_end(nullptr)
  , m_capacity(0)
  {
  }

  explicit SimpleVector(size_t size)
  {
      if (size > 0){
          m_data = new T [size];
      }

        m_capacity = size;
        m_end = m_data + size;
  }

  ~SimpleVector()
  {
      delete [] m_data;
  }

  T& operator[](size_t index) { return m_data[index]; }

  T* begin() { return m_data; }
  T* end() { return m_end; }

  size_t Size() const { return m_end - m_data; }

  size_t Capacity() const { return m_capacity; }
    
  void PushBack(const T& value)
  {
      if (m_data == nullptr)
      {
          m_data = new T[1];
          *m_data = value;
          m_capacity = 1;
          m_end = m_data + 1;
      }
      else
      {
          if (m_end == m_data + m_capacity)
          {
            size_t new_capacity = m_capacity * 2;
            
            T *new_data = new T[new_capacity];

            std::memcpy(new_data, m_data, sizeof(T) * m_capacity);

            delete [] m_data;

            m_data = new_data;

            m_end = m_data + m_capacity;

            m_capacity = new_capacity;
          }

          *(m_end++) = value;
      }
      
  }

private:
    T *m_data;
    T *m_end;
    size_t m_capacity;
};