#include "Portfolio.h"

#include <exception>

using namespace std;
using namespace boost::gregorian;

const date Portfolio::FIXED_PURCHASE_DATE(date(2014, Jan, 1));

bool Portfolio::IsEmpty() const { 
   return 0 == holdings_.size(); 
}

void Portfolio::Purchase(const string& symbol, unsigned int shares, date date) {
   if (0 == shares) throw InvalidPurchaseException();
   holdings_[symbol] = shares + Shares(symbol);
   purchases_.push_back(PurchaseRecord(shares, date));
}

void Portfolio::Sell(const std::string& symbol, unsigned int shares, date date) {
   if (shares > Shares(symbol)) throw InvalidSellException();
   holdings_[symbol] = Shares(symbol) - shares;
   purchases_.push_back(PurchaseRecord(shares * -1, date));
}

unsigned int Portfolio::Shares(const string& symbol) const {
   auto it = holdings_.find(symbol);
   if (it == holdings_.end()) return 0;
   return it->second;
}

std::vector<PurchaseRecord> Portfolio::Purchases(const std::string& symbol) const {
   return purchases_;
}

