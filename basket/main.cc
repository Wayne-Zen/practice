#include <memory>
#include "basket.hh"
#include "quote.hh"
#include "bulk_quote.hh"

int main(int argc, char const *argv[])
{
	Basket bsk{};
	bsk.AddItem(Quote{"123", 45});
	bsk.AddItem(BulkQuote{"345", 55, 3, .15});
	for (unsigned i = 0; i != 10; ++i) {
		bsk.AddItem(BulkQuote{"4567", 35, 3, .15});
	}
	bsk.TotalReceipt(std::cout);
	return 0;
}