#include "Portfolio.h"

#include <exception>
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

void Portfolio::Transact(
      const string& symbol, int shareChange, const date& transactionDate) {
   ThrowIfSharesIsZero(shareChange);
   UpdateShares(symbol, shareChange);
   AddPurchaseRecord(symbol, shareChange, transactionDate);
}

void Portfolio::ThrowIfSharesIsZero(int shareChange) const {
   if (0 == shareChange) throw SharesCannotBeZeroException();
}

void Portfolio::UpdateShares(const string& symbol, int shareChange) {
   holdings_[symbol] = Shares(symbol) + shareChange;
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

unsigned int Portfolio::Shares(const string& symbol) const {
   auto it = holdings_.find(symbol);
   if (it == holdings_.end()) return 0;
   return it->second;
}

vector<PurchaseRecord> Portfolio::Purchases(const string& symbol) const {
   auto it = purchaseRecords_.find(symbol);
   if (it == purchaseRecords_.end()) return vector<PurchaseRecord>();
   return it->second;
}

