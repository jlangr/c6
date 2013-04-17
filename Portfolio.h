#ifndef Portfolio_h
#define Portfolio_h

#include <string>
#include <exception>
#include <unordered_map>
#include <vector>
#include "boost/date_time/gregorian/gregorian_types.hpp"
#include "PurchaseRecord.h"
#include "Holding.h"

class SharesCannotBeZeroException: public std::exception {
};

class InvalidSellException: public std::exception {
};

class Portfolio {
public:
   bool IsEmpty() const;
   void Purchase(
         const std::string& symbol, 
         unsigned int shares,
         const boost::gregorian::date& transactionDate);
   void Sell(const std::string& symbol, 
         unsigned int shares,
         const boost::gregorian::date& transactionDate);
   unsigned int Shares(const std::string& symbol) const;
   std::vector<PurchaseRecord> Purchases(const std::string& symbol) const;

private:
   void Transact(const std::string& symbol, 
         int shareChange,
         const boost::gregorian::date&);
   void UpdateShares(const std::string& symbol, int shareChange);
   void AddPurchaseRecord(
         const std::string& symbol, int shares, const boost::gregorian::date&);
   void ThrowIfSharesIsZero(int shareChange) const;

   bool ContainsSymbol(const std::string& symbol) const;
   void InitializePurchaseRecords(const std::string& symbol);
   void Add(const std::string& symbol, PurchaseRecord&& record);

   template<typename T>
   T Find(std::unordered_map<std::string, T> map, const std::string& key) const {
      auto it = map.find(key);
      return it == map.end() ? T{} : it->second;
   }

// START:r7
   // no longer needed!
   std::unordered_map<std::string, std::vector<PurchaseRecord>> purchaseRecords_;
// END:r7
// START:r1
// START_HIGHLIGHT
   std::unordered_map<std::string, Holding> holdings_;
// END_HIGHLIGHT
// END:r1
};
#endif
