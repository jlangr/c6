#include "Portfolio.h"

#include <exception>
#include "PurchaseRecord.h"

using namespace std;
using namespace boost::gregorian;

// START:r7
bool Portfolio::IsEmpty() const { 
// START_HIGHLIGHT
//   return 0 == purchaseRecords_.size(); 
   return 0 == holdings_.size(); 
// END_HIGHLIGHT
}
// END:r7

void Portfolio::Purchase(
      const string& symbol, unsigned int shares, const date& transactionDate) {
   Transact(symbol, shares, transactionDate);
}

void Portfolio::Sell(
      const string& symbol, unsigned int shares, const date& transactionDate) {
   if (shares > Shares(symbol)) throw InvalidSellException();
   Transact(symbol, -shares, transactionDate);
}

// START:refactor
void Portfolio::Transact(
      const string& symbol, int shareChange, const date& transactionDate) {
   ThrowIfSharesIsZero(shareChange);
   AddPurchaseRecord(symbol, shareChange, transactionDate);
}
// END:refactor

void Portfolio::ThrowIfSharesIsZero(int shareChange) const {
   if (0 == shareChange) throw SharesCannotBeZeroException();
}

void Portfolio::AddPurchaseRecord(
      const string& symbol, int shareChange, const date& date) {
   if (!ContainsSymbol(symbol))
      InitializePurchaseRecords(symbol);

   Add(symbol, {shareChange, date});
}

// START:r2
void Portfolio::InitializePurchaseRecords(const string& symbol) {
   purchaseRecords_[symbol] = vector<PurchaseRecord>();
// START_HIGHLIGHT
   holdings_[symbol] = Holding();
// END_HIGHLIGHT
}
// END:r2

// START:r3
void Portfolio::Add(const string& symbol, PurchaseRecord&& record) {
   purchaseRecords_[symbol].push_back(record);
// START_HIGHLIGHT
   holdings_[symbol].Add(record);
// END_HIGHLIGHT
}
// END:r3

// START:r5
bool Portfolio::ContainsSymbol(const string& symbol) const {
//   return purchaseRecords_.find(symbol) != purchaseRecords_.end();
   return holdings_.find(symbol) != holdings_.end();
}
// END:r5

// START:r6
unsigned int Portfolio::Shares(const string& symbol) const {
//   auto records = Find<vector<PurchaseRecord>>(purchaseRecords_, symbol);
//   return accumulate(records.begin(), records.end(), 0, 
//      [] (int total, PurchaseRecord record) { return total + record.Shares; });
   return Find<Holding>(holdings_, symbol).Shares();
}
// END:r6

// START:r4
vector<PurchaseRecord> Portfolio::Purchases(const string& symbol) const {
//   return Find<vector<PurchaseRecord>>(purchaseRecords_, symbol);
   return Find<Holding>(holdings_, symbol).Purchases();
}
// END:r4

