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
   Transact(symbol, shares, transactionDate);
}
// END:purchase

// START:newname
void Portfolio::Sell(
      const string& symbol, unsigned int shares, const date& transactionDate) {
   if (shares > Shares(symbol)) throw InsufficientSharesException();
   Transact(symbol, -shares, transactionDate);
}
// END:newname

// START:transact
void Portfolio::Transact(
      const string& symbol, int shareChange, const date& transactionDate) {
   if (0 == shareChange) throw SharesCannotBeZeroException();
   holdings_[symbol] = Shares(symbol) + shareChange;
   purchases_.push_back(PurchaseRecord(shareChange, transactionDate));
}
// END:transact
// END:transactions

unsigned int Portfolio::Shares(const string& symbol) const {
   auto it = holdings_.find(symbol);
   if (it == holdings_.end()) return 0;
   return it->second;
}

vector<PurchaseRecord> Portfolio::Purchases(const string& symbol) const {
   return purchases_;
}

