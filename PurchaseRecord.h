#ifndef PurchaseRecord_h
#define PurchaseRecord_h

#include "boost/date_time/gregorian/gregorian_types.hpp"

struct PurchaseRecord {
   PurchaseRecord(int shares, const boost::gregorian::date& date)
      : Shares(shares)
      , Date(date) {
   }
   int Shares;
   boost::gregorian::date Date;
};

#endif

