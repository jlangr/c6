#include "Portfolio.h"

#include <exception>

using namespace std;
using namespace boost::gregorian;

bool Portfolio::IsEmpty() const { 
   return 0 == holdings_.size(); 
}

void Portfolio::Purchase(
      const string& symbol, unsigned int shares, date transactionDate) {
   Transact(symbol, shares, transactionDate);
}

void Portfolio::Sell(
      const string& symbol, unsigned int shares, date transactionDate) {
   if (shares > Shares(symbol)) throw InvalidSellException();
   Transact(symbol, -shares, transactionDate);
}

// START:Transact
void Portfolio::Transact(
      const string& symbol, int shareChange, date transactionDate) {
   ThrowIfSharesIsZero(shareChange);
   UpdateShares(symbol, shareChange);
   AddPurchaseRecord(shareChange, transactionDate);
}

void Portfolio::ThrowIfSharesIsZero(int shareChange) const {
   if (0 == shareChange) throw InvalidPurchaseException();
}

void Portfolio::UpdateShares(const string& symbol, int shareChange) {
   holdings_[symbol] = Shares(symbol) + shareChange;
}

void Portfolio::AddPurchaseRecord(int shareChange, date date) {
   purchases_.push_back(PurchaseRecord(shareChange, date));
}
// END:Transact

unsigned int Portfolio::Shares(const string& symbol) const {
   auto it = holdings_.find(symbol);
   if (it == holdings_.end()) return 0;
   return it->second;
}

vector<PurchaseRecord> Portfolio::Purchases(const string& symbol) const {
   return purchases_;
}

