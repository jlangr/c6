#include "Portfolio.h"

#include <exception>

using namespace std;

bool Portfolio::IsEmpty() const { 
   return 0 == holdings_.size(); 
}

void Portfolio::Purchase(const string& symbol, unsigned int shares) {
   if (0 == shares) throw InvalidPurchaseException();
   holdings_[symbol] = shares + Shares(symbol);
}

void Portfolio::Sell(const std::string& symbol, unsigned int shares) {
   if (shares > Shares(symbol)) throw InvalidSellException();
   holdings_[symbol] = Shares(symbol) - shares;
}

unsigned int Portfolio::Shares(const string& symbol) const {
   auto it = holdings_.find(symbol);
   if (it == holdings_.end()) return 0;
   return it->second;
}
