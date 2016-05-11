#ifndef QUOTE_HH
#define QUOTE_HH

#include <cstddef>
#include <string>

namespace {
class Quote {
 public:
 	Quote() = default;
 	Quote(const std::string& isbn, double price)
 			: isbn_{isbn}, price_{price} {}
 	virtual ~Quote() = default;

 	virtual Quote* clone() const & { return new Quote(*this); } 
 	virtual Quote* clone() && { return new Quote(std::move(*this)); }
 	
 	std::string isbn() const { return isbn_; }
 	virtual double NetPrice(size_t n) const { return n * price_; }
 private:
 	std::string isbn_{};
 protected:
 	double price_{};
};
}

#endif