#ifndef PRINT_TOTAL_HH
#define PRINT_TOTAL_HH

#include <cstddef>
#include <iostream>
#include "quote.hh"

namespace {
double PrintTotal(std::ostream& os, const Quote& item, size_t n) {
	double ret = item.NetPrice(n);
	os << "ISBN: #" << item.isbn()
	   << "# sold: " << n << " total due: " << ret << std::endl;
	return ret;
}
}

#endif