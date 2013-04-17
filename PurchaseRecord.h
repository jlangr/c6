#ifndef PurchaseRecord_h
#define PurchaseRecord_h

#include "GregorianDate.h"

struct PurchaseRecord {
   PurchaseRecord(int shares, const boost::gregorian::date& date)
      : Shares(shares)
      , Date(date) {
   }
   int Shares;
   GregorianDate Date;
};

#endif

