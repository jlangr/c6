#include "Portfolio.h"

#include <exception>

using namespace std;
using namespace boost::gregorian;

bool Portfolio::IsEmpty() const { 
   return 0 == holdings_.size(); 
}

// START:transactions
// START:purchase
void Portfolio::Purchase(
      const string& symbol, unsigned int shares, const date& transactionDate) {
   int shareChange = shares;
// START_HIGHLIGHT
   if (0 == shareChange) throw SharesCannotBeZeroException();
   holdings_[symbol] = Shares(symbol) + shareChange;
   purchases_.push_back(PurchaseRecord(shareChange, transactionDate));
// END_HIGHLIGHT
}
// END:purchase

// START:sell
void Portfolio::Sell(
      const string& symbol, unsigned int shares, const date& transactionDate) {
   if (shares > Shares(symbol)) throw InvalidSellException();
   int shareChange = -shares;
// START_HIGHLIGHT
   if (0 == shareChange) throw SharesCannotBeZeroException();
   holdings_[symbol] = Shares(symbol) + shareChange;
   purchases_.push_back(PurchaseRecord(shareChange, transactionDate));
// END_HIGHLIGHT
}
// END:sell
// END:transactions

unsigned int Portfolio::Shares(const string& symbol) const {
   auto it = holdings_.find(symbol);
   if (it == holdings_.end()) return 0;
   return it->second;
}

vector<PurchaseRecord> Portfolio::Purchases(const string& symbol) const {
   return purchases_;
}

