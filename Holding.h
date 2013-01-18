#ifndef Holding_h
#define Holding_h

#include "PurchaseRecord.h"

class Holding {
public:
// START:r3
   void Add(PurchaseRecord& record) {
      purchaseRecords_.push_back(record);
   }

// END:r3
// START:r4

   std::vector<PurchaseRecord> Purchases() const {
      return purchaseRecords_;
   }
// END:r4
// START:r6

   unsigned int Shares() const {
      return accumulate(purchaseRecords_.begin(), purchaseRecords_.end(), 0, 
         [] (int total, PurchaseRecord record) { return total + record.Shares; });
   }
// END:r6

private:
// START:r3
   std::vector<PurchaseRecord> purchaseRecords_;
// END:r3
};
#endif
