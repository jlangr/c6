#include "Portfolio.h"

#include <exception>

using namespace std;
using namespace boost::gregorian;

bool Portfolio::IsEmpty() const { 
   return 0 == holdings_.size(); 
}

// START:transactions
void Portfolio::Purchase(
      const string& symbol, unsigned int shares, date transactionDate) {
   if (0 == shares) throw InvalidPurchaseException();
   holdings_[symbol] = shares + Shares(symbol);
   purchases_.push_back(PurchaseRecord(shares, transactionDate));
}

void Portfolio::Sell(
      const string& symbol, unsigned int shares, date transactionDate) {
   if (shares > Shares(symbol)) throw InvalidSellException();
   holdings_[symbol] = Shares(symbol) - shares;
   purchases_.push_back(PurchaseRecord(shares * -1, transactionDate));
}
// END:transactions

unsigned int Portfolio::Shares(const string& symbol) const {
   auto it = holdings_.find(symbol);
   if (it == holdings_.end()) return 0;
   return it->second;
}

vector<PurchaseRecord> Portfolio::Purchases(const string& symbol) const {
   return purchases_;
}

