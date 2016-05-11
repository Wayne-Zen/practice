#ifndef BASKET_HH
#define BASKET_HH

#include <memory>
#include <set>
#include <iostream>
#include "quote.hh"
#include "print_total.hh"

namespace {
class Basket {
 public:
 	void AddItem(const Quote& sale) {
 		items_.insert(std::shared_ptr<Quote>(sale.clone()));
 	}
 	void AddItem(Quote&& sale) {
 		items_.insert(std::shared_ptr<Quote>(std::move(sale).clone()));
 	}
 	// prints the total price for each book and the overall total for all items in the basket
 	double TotalReceipt(std::ostream& os) const {
 		double sum{0.0};
		// upper_bound returns an iterator to the element just past the end of that batch
		// skip over all the elements that match the current key
		for (auto iter = items_.cbegin(); iter != items_.cend();
			   iter = items_.upper_bound(*iter)) {
			sum += PrintTotal(os, **iter, items_.count(*iter));
		}
		os << "Total Sale: " << sum << std::endl;
		return sum;
 	}
 private:
 	// function to compare shared_ptrs needed by the multiset member
 	static bool compare(const std::shared_ptr<Quote>& lhs,
 		                  const std::shared_ptr<Quote>& rhs) {
 		return lhs->isbn() < rhs->isbn();
 	}
 	// multiset to hold nultiple quotes, ordered by the compare member
 	// pass compare function for initializing
 	std::multiset<std::shared_ptr<Quote>, decltype(compare)*> items_{compare};
};
}

#endif