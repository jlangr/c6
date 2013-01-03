#include "Portfolio.h"

#include <exception>

using namespace std;
using namespace boost::gregorian;

bool Portfolio::IsEmpty() const { 
   return 0 == holdings_.size(); 
}

// START:transactions
// START:purchase
void Portfolio::Purchase(const string& symbol, unsigned int shares, date date) {
   Transact(symbol, shares, date);
}
// END:purchase

// START:sell
void Portfolio::Sell(const std::string& symbol, unsigned int shares, date date) {
   if (shares > Shares(symbol)) throw InvalidSellException();
   Transact(symbol, shares * -1, date);
}
// END:sell

// START:transact
void Portfolio::Transact(const string& symbol, unsigned int shareChange, date date) {
   if (0 == shareChange) throw InvalidPurchaseException();
   holdings_[symbol] = Shares(symbol) + shareChange;
   purchases_.push_back(PurchaseRecord(shareChange, date));
}
// END:transact
// END:transactions

unsigned int Portfolio::Shares(const string& symbol) const {
   auto it = holdings_.find(symbol);
   if (it == holdings_.end()) return 0;
   return it->second;
}

std::vector<PurchaseRecord> Portfolio::Purchases(const std::string& symbol) const {
   return purchases_;
}

