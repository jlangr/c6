#include "gmock/gmock.h"
#include "Portfolio.h"
#include "boost/date_time/gregorian/gregorian_types.hpp"

using namespace ::testing;
using namespace std;
using namespace boost::gregorian;

class APortfolio: public Test {
public:
   static const string IBM;
   static const string SAMSUNG;
   Portfolio portfolio_;
   static const date ArbitraryDate;

   void Purchase(
         const string& symbol, 
         unsigned int shares,
         const date& transactionDate=APortfolio::ArbitraryDate) {
      portfolio_.Purchase(symbol, shares, transactionDate);
   }
};

const date APortfolio::ArbitraryDate(2014, Sep, 5);
const string APortfolio::IBM("IBM");
const string APortfolio::SAMSUNG("SSNLF");

TEST_F(APortfolio, IsEmptyWhenCreated) {
   ASSERT_THAT(portfolio_.IsEmpty(), Eq(true));
}

TEST_F(APortfolio, IsNotEmptyAfterPurchase) {
   Purchase(IBM, 1);

   ASSERT_THAT(portfolio_.IsEmpty(), Eq(false));
}

TEST_F(APortfolio, AnswersZeroForSharesOfUnpurchasedSymbol) {
   ASSERT_THAT(portfolio_.Shares("AAPL"), Eq(0u));
}

// START:helper
TEST_F(APortfolio, AnswersSharesForPurchasedSymbol) {
// START_HIGHLIGHT
   portfolio_.Purchase(IBM, 2);
// END_HIGHLIGHT

   ASSERT_THAT(portfolio_.Shares(IBM), Eq(2u));
}
// END:helper

TEST_F(APortfolio, ThrowsOnPurchaseOfZeroShares) {
   ASSERT_THROW(Purchase(IBM, 0), InvalidPurchaseException);
}

TEST_F(APortfolio, AnswersSharesForAppropriateSymbol) {
   Purchase(IBM, 5);
   Purchase(SAMSUNG, 10);

   ASSERT_THAT(portfolio_.Shares(IBM), Eq(5u));
}

TEST_F(APortfolio, SharesReflectsAccumulatedPurchasesOfSameSymbol) {
   Purchase(IBM, 5);
   Purchase(IBM, 15);

   ASSERT_THAT(portfolio_.Shares(IBM), Eq(5u + 15));
}

// START:helper

TEST_F(APortfolio, ReducesSharesOfSymbolOnSell)  {
// START_HIGHLIGHT
   Purchase(SAMSUNG, 30);
// END_HIGHLIGHT
   
   portfolio_.Sell(SAMSUNG, 13);

   ASSERT_THAT(portfolio_.Shares(SAMSUNG), Eq(30u - 13));
}
// END:helper

TEST_F(APortfolio, ThrowsWhenSellingMoreSharesThanPurchased) {
   ASSERT_THROW(portfolio_.Sell(SAMSUNG, 1), InvalidSellException);
}

TEST_F(APortfolio, AnswersThePurchaseRecordForASinglePurchase) {
   date dateOfPurchase(2014, Mar, 17);
   Purchase(SAMSUNG, 5, dateOfPurchase);

   auto purchases = portfolio_.Purchases(SAMSUNG);

   auto purchase = purchases[0];
   ASSERT_THAT(purchase.Shares, Eq(5u));
   ASSERT_THAT(purchase.Date, Eq(dateOfPurchase));
}

