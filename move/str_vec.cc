#include "str_vec.hh"

#include <string>
#include <memory>
#include <utility>

namespace {
std::allocator<std::string> StrVec::alloc{};

StrVec::StrVec() 
    : elements(nullptr)
    , first_free(nullptr)
    , cap(nullptr) {}

StrVec::StrVec(const StrVec& s) {
  // call alloc_n_copy to allocate exactly as many as elements as in s
  auto newdata = alloc_n_copy(s.begin(), s.end());
  elements = newdata.first;
  first_free = cap = newdata.second;
}

StrVec::StrVec(StrVec&& s) noexcept 
    // member initializer take over ther resources in s
    : elements(s.elements)
    , first_free(s.first_free)
    , cap(s.cap) {
  s.elements = s.first_free = s.cap = nullptr;
}

StrVec& StrVec::operator=(const StrVec& rhs) {
  // call alloc_n_copy to allocate exactly as many as elements as in rhs
  // prevent self-assignment by copy first
  auto data = alloc_n_copy(rhs.begin(), rhs.end());
  free();
  elements = data.first;
  first_free = cap = data.second;
  return *this;
}

StrVec& StrVec::operator=(StrVec&& rhs) noexcept {
  // direct test for self-assignment
  if (this != &rhs) {
    free();
    elements = rhs.elements;
    first_free = rhs.first_free;
    cap = rhs.cap;
    // leave rhs in a destructible state
    rhs.elements = rhs.first_free = rhs.cap = nullptr;
  }
  return *this;
}

StrVec::~StrVec() { free(); }

void StrVec::free() {
  // if elements is 0, there's no work to do
  // elemets may be set in move constructor
  if (elements) {
    // destroy the old elements in reverse order
    for (auto p = first_free; p != elements; /* empty */) {
      alloc.destroy(--p);
    }
    alloc.deallocate(elements, cap - elements);
  }
}

void StrVec::push_back(const std::string& s) {
  chk_n_alloc(); // ensure that there is room for another element
  // construct a copy of s in the element to which first_free points
  alloc.construct(first_free++, s);
}

std::pair<std::string* , std::string*> 
StrVec::alloc_n_copy(const std::string* b, const std::string* e) {
  // allocate space to hold as many elements as are in the range
  auto data = alloc.allocate(e - b);
  // initialize and return a pair constructed from data
  // and the value returned by uninitialized_copy
  return {data, uninitialized_copy(b, e, data)};
}

void StrVec::reallocate() {
  // we'll allocate space for twice as many elements as the current size
  auto newcapacity = size() ? 2 * size() : 1;
  // allocate new memory
  auto newdata = alloc.allocate(newcapacity);
  // move the data from old memory to the new
  auto dest = newdata;  // points to the next free position in the new array
  auto elem = elements; // points to the next element in the old array
  for (size_t i = 0; i != size(); ++i) {
    alloc.construct(dest++, std::move(*elem++));
  }
  free(); // free old space
  // update
  elements = newdata;
  first_free = dest;
  cap = elements + newcapacity;
}
} // end namespace

// main function should go to global namespace
int main(int argc, char const *argv[]) {
  /* code */
  return 0;
}