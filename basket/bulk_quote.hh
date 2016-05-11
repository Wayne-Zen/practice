#ifndef BULK_QUOTE_HH
#define BULK_QUOTE_HH

#include <cstddef>
#include <string>
#include "Quote.hh"

namespace {
class BulkQuote : public Quote {
 public:
	BulkQuote() = default;
	BulkQuote(const std::string& isbn, double price, size_t min_qty, double discount)
			: Quote{isbn, price}, min_qty_{min_qty}, discount_{discount} {}

	virtual BulkQuote* clone() const & override { return new BulkQuote(*this); } 
 	virtual BulkQuote* clone() && override { 
 		return new BulkQuote(std::move(*this)); 
 	}

	double NetPrice(size_t cnt) const override {
		if (cnt >= min_qty_) {
			return cnt * (1 - discount_) * price_;
		} else {
			return cnt * price_;
		}
	}
 private:
 	size_t min_qty_{0};
 	double discount_{0.0};
};
}

#endif