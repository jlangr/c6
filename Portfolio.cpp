#include "Portfolio.h"

#include <exception>

using namespace std;

Portfolio::Portfolio() 
   : shares_(0) {
}

// START:Empty
bool Portfolio::IsEmpty() const { 
// START_HIGHLIGHT
   return 0 == shares_; 
// END_HIGHLIGHT
}
// END:Empty

void Portfolio::Purchase(const string& symbol, unsigned int shares) {
   if (0 == shares) throw InvalidPurchaseException();
   shares_ = shares;
}

unsigned int Portfolio::Shares(const string& symbol) const {
   return shares_;
}
