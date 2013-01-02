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

// START:PurchaseRecord
struct PurchaseRecord {
   PurchaseRecord(unsigned int shares, boost::gregorian::date date) 
   : Shares(shares) 
   , Date(date) {
   }
   unsigned int Shares;
   boost::gregorian::date Date;
};

class Portfolio {
public:
// START_HIGHLIGHT
   static const boost::gregorian::date FIXED_PURCHASE_DATE;
// END_HIGHLIGHT
   bool IsEmpty() const;
   void Purchase(const std::string& symbol, unsigned int shares);
   void Sell(const std::string& symbol, unsigned int shares);
   unsigned int Shares(const std::string& symbol) const;
// START_HIGHLIGHT
   std::vector<PurchaseRecord> Purchases(const std::string& symbol) const;
// END_HIGHLIGHT

private:
   std::unordered_map<std::string, unsigned int> holdings_;
// START_HIGHLIGHT
   std::vector<PurchaseRecord> purchases_;
// END_HIGHLIGHT
};
// END:PurchaseRecord
#endif
