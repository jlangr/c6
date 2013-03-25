#include "Portfolio.h"
#include "PurchaseRecord.h"

using namespace std;
using namespace boost::gregorian;

// START:refactor
bool Portfolio::IsEmpty() const { 
// START_HIGHLIGHT
   return 0 == purchaseRecords_.size(); 
// END_HIGHLIGHT
}
// END:refactor

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

void Portfolio::InitializePurchaseRecords(const string& symbol) {
   purchaseRecords_[symbol] = vector<PurchaseRecord>();
}

void Portfolio::Add(const string& symbol, PurchaseRecord&& record) {
   purchaseRecords_[symbol].push_back(record);
}

bool Portfolio::ContainsSymbol(const string& symbol) const {
   return purchaseRecords_.find(symbol) != purchaseRecords_.end();
}

// START:calculate
unsigned int Portfolio::Shares(const string& symbol) const {
   auto records = Find<vector<PurchaseRecord>>(purchaseRecords_, symbol);
   return accumulate(records.begin(), records.end(), 0, 
      [] (int total, PurchaseRecord record) { return total + record.Shares; });
}
// END:calculate

vector<PurchaseRecord> Portfolio::Purchases(const string& symbol) const {
   return Find<vector<PurchaseRecord>>(purchaseRecords_, symbol);
}

