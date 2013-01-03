#ifndef Portfolio_h
#define Portfolio_h

#include <string>
#include <exception>
#include <unordered_map>
#include <vector>
#include "boost/date_time/gregorian/gregorian_types.hpp"

class InvalidPurchaseException: public std::exception {
};

class InvalidSellException: public std::exception {
};

struct PurchaseRecord {
   PurchaseRecord(int shares, boost::gregorian::date date) 
   : Shares(shares) 
   , Date(date) {
   }
   int Shares;
   boost::gregorian::date Date;
};

class Portfolio {
public:
   bool IsEmpty() const;
   void Purchase(
         const std::string& symbol, 
         unsigned int shares,
         boost::gregorian::date date);
   void Sell(const std::string& symbol, 
         unsigned int shares,
         boost::gregorian::date date);
   unsigned int Shares(const std::string& symbol) const;
   std::vector<PurchaseRecord> Purchases(const std::string& symbol) const;

private:
   void Transact(const std::string& symbol, 
         int shareChange,
         boost::gregorian::date);
   void UpdateShares(const std::string& symbol, int shareChange);
   void AddPurchaseRecord(int, boost::gregorian::date);
   void ThrowIfSharesIsZero(int shareChange) const;

   std::unordered_map<std::string, unsigned int> holdings_;
   std::vector<PurchaseRecord> purchases_;
};
#endif
