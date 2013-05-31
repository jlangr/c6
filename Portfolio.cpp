#include "Portfolio.h"
#include "PurchaseRecord.h"

using namespace std;
using namespace boost::gregorian;

bool Portfolio::IsEmpty() const { 
   return 0 == holdings_.size(); 
}

void Portfolio::Purchase(
      const string& symbol, unsigned int shares, const date& transactionDate) {
   Transact(symbol, shares, transactionDate);
}

void Portfolio::Sell(
      const string& symbol, unsigned int shares, const date& transactionDate) {
   if (shares > Shares(symbol)) throw InvalidSellException();
   Transact(symbol, -shares, transactionDate);
}

// START:multipleSymbols
void Portfolio::Transact(
      const string& symbol, int shareChange, const date& transactionDate) {
   ThrowIfSharesIsZero(shareChange);
   UpdateShares(symbol, shareChange);
// START_HIGHLIGHT
   AddPurchaseRecord(symbol, shareChange, transactionDate);
// END_HIGHLIGHT
}
// END:multipleSymbols

void Portfolio::ThrowIfSharesIsZero(int shareChange) const {
   if (0 == shareChange) throw SharesCannotBeZeroException();
}

void Portfolio::UpdateShares(const string& symbol, int shareChange) {
   holdings_[symbol] = Shares(symbol) + shareChange;
}
// START:multipleSymbols

void Portfolio::AddPurchaseRecord(
      const string& symbol, int shareChange, const date& date) {
   purchases_.push_back(PurchaseRecord(shareChange, date));

// START_HIGHLIGHT
   auto it = purchaseRecords_.find(symbol);
   if (it == purchaseRecords_.end())
      purchaseRecords_[symbol] = vector<PurchaseRecord>();
   purchaseRecords_[symbol].push_back(PurchaseRecord(shareChange, date));
// END_HIGHLIGHT
}

unsigned int Portfolio::Shares(const string& symbol) const {
   auto it = holdings_.find(symbol);
   if (it == holdings_.end()) return 0;
   return it->second;
}

vector<PurchaseRecord> Portfolio::Purchases(const string& symbol) const {
// START_HIGHLIGHT
//   return purchases_;
   return purchaseRecords_.find(symbol)->second;
// END_HIGHLIGHT
}
// END:multipleSymbols

