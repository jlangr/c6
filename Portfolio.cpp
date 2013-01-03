#include "Portfolio.h"

#include <exception>

using namespace std;
using namespace boost::gregorian;

bool Portfolio::IsEmpty() const { 
   return 0 == holdings_.size(); 
}

void Portfolio::Purchase(const string& symbol, unsigned int shares, date date) {
   Transact(symbol, shares, date);
}

void Portfolio::Sell(const std::string& symbol, unsigned int shares, date date) {
   if (shares > Shares(symbol)) throw InvalidSellException();
   Transact(symbol, shares * -1, date);
}

// START:Transact
void Portfolio::Transact(const string& symbol, int shareChange, date date) {
   ThrowIfSharesIsZero(shareChange);
   UpdateShares(symbol, shareChange);
   AddPurchaseRecord(shareChange, date);
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

std::vector<PurchaseRecord> Portfolio::Purchases(const std::string& symbol) const {
   return purchases_;
}

