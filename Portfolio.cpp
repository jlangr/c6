#include "Portfolio.h"

#include <exception>

using namespace std;
using namespace boost::gregorian;

// START:PurchaseRecord
const date Portfolio::FIXED_PURCHASE_DATE(date(2014, Jan, 1));
// END:PurchaseRecord

bool Portfolio::IsEmpty() const { 
   return 0 == holdings_.size(); 
}

// START:PurchaseRecord

void Portfolio::Purchase(const string& symbol, unsigned int shares) {
   if (0 == shares) throw InvalidPurchaseException();
   holdings_[symbol] = shares + Shares(symbol);
// START_HIGHLIGHT
   purchases_.push_back(PurchaseRecord(shares, FIXED_PURCHASE_DATE));
// END_HIGHLIGHT
}
// END:PurchaseRecord

void Portfolio::Sell(const std::string& symbol, unsigned int shares) {
   if (shares > Shares(symbol)) throw InvalidSellException();
   holdings_[symbol] = Shares(symbol) - shares;
}

unsigned int Portfolio::Shares(const string& symbol) const {
   auto it = holdings_.find(symbol);
   if (it == holdings_.end()) return 0;
   return it->second;
}

// START:PurchaseRecord
//
std::vector<PurchaseRecord> Portfolio::Purchases(const std::string& symbol) const {
   return purchases_;
}
// END:PurchaseRecord
