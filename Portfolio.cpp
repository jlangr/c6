#include "Portfolio.h"

using namespace std;

Portfolio::Portfolio() 
   : isEmpty_{true} 
   , shares_{0} {
}

bool Portfolio::IsEmpty() const { 
   return isEmpty_; 
}

void Portfolio::Purchase(const string& symbol, unsigned int shares) {
   isEmpty_ = false;
   shares_ = shares;
}

unsigned int Portfolio::Shares(const string& symbol) const {
   return shares_;
}
