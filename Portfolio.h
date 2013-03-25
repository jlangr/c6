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

// START:signed
struct PurchaseRecord {
// START_HIGHLIGHT
   PurchaseRecord(int shares, const boost::gregorian::date& date) 
// END_HIGHLIGHT
      : Shares(shares) 
      , Date(date) {}
// START_HIGHLIGHT
   int Shares;
// END_HIGHLIGHT
   boost::gregorian::date Date;
};
// END:signed

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
   std::unordered_map<std::string, unsigned int> holdings_;
   std::vector<PurchaseRecord> purchases_;
};
#endif

