#ifndef STR_VEC_HH
#define STR_VEC_HH

#include <cstddef>
#include <string>
#include <memory>
#include <utility>

namespace {
class StrVec {
 public:
  StrVec();                             // defaul constructor
  StrVec(const StrVec&);                // copy constructor
  StrVec(StrVec&&) noexcept;            // move constructor
  StrVec& operator=(const StrVec&);     // copy assignment
  StrVec& operator=(StrVec&&) noexcept; // move assignment
  ~StrVec();                            // destructor

  void push_back(const std::string&);
  size_t size() const { return first_free - elements; }
  size_t capacity() const { return cap - elements; }
  std::string* begin() const { return elements; }
  std::string* end() const { return first_free; }
 private:
  std::pair<std::string*, std::string*> alloc_n_copy(const std::string*, 
                                                     const std::string*);
  void free();              // destroy the elements and free the space
  void reallocate();        // get more space ans copy the existing elements
  void chk_n_alloc() { if (size() == capacity()) reallocate(); }

  static std::allocator<std::string> alloc;
  std::string* elements;    // pointer to the first element in the array
  std::string* first_free;  // pointer to the first free element in the array
  std::string* cap;         // pointer to on past the end of the array
};
}

#endif