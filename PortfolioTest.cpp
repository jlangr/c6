#include "gmock/gmock.h"
#include "Portfolio.h"
#include "boost/date_time/gregorian/gregorian_types.hpp"

using namespace ::testing;
using namespace std;
using boost::gregorian::date;

class APortfolio: public Test {
public:
   static const string IBM;
   static const string SAMSUNG;
   Portfolio portfolio_;
};

const string APortfolio::IBM("IBM");
const string APortfolio::SAMSUNG("SSNLF");

TEST_F(APortfolio, IsEmptyWhenCreated) {
   ASSERT_TRUE(portfolio_.IsEmpty());
}

TEST_F(APortfolio, IsNotEmptyAfterPurchase) {
   portfolio_.Purchase(IBM, 1);

   ASSERT_FALSE(portfolio_.IsEmpty());
}

TEST_F(APortfolio, AnswersZeroForSharesOfUnpurchasedSymbol) {
   ASSERT_THAT(portfolio_.Shares("AAPL"), Eq(0u));
}

TEST_F(APortfolio, AnswersSharesForPurchasedSymbol) {
   portfolio_.Purchase(IBM, 2);

   ASSERT_THAT(portfolio_.Shares(IBM), Eq(2u));
}

TEST_F(APortfolio, ThrowsOnPurchaseOfZeroShares) {
   ASSERT_THROW(portfolio_.Purchase(IBM, 0), InvalidPurchaseException);
}

TEST_F(APortfolio, AnswersSharesForAppropriateSymbol) {
   portfolio_.Purchase(IBM, 5);
   portfolio_.Purchase(SAMSUNG, 10);

   ASSERT_THAT(portfolio_.Shares(IBM), Eq(5u));
}

TEST_F(APortfolio, SharesReflectsAccumulatedPurchasesOfSameSymbol) {
   portfolio_.Purchase(IBM, 5);
   portfolio_.Purchase(IBM, 15);

   ASSERT_THAT(portfolio_.Shares(IBM), Eq(5u + 15));
}

TEST_F(APortfolio, ReducesSharesOfSymbolOnSell)  {
   portfolio_.Purchase(SAMSUNG, 30);
   
   portfolio_.Sell(SAMSUNG, 13);

   ASSERT_THAT(portfolio_.Shares(SAMSUNG), Eq(30u - 13));
}

TEST_F(APortfolio, ThrowsWhenSellingMoreSharesThanPurchased) {
   ASSERT_THROW(portfolio_.Sell(SAMSUNG, 1), InvalidSellException);
}

// START:PurchaseRecord
TEST_F(APortfolio, AnswersThePurchaseRecordForASinglePurchase) {
   portfolio_.Purchase(SAMSUNG, 5);

   auto purchases = portfolio_.Purchases(SAMSUNG);

   auto purchase = purchases[0];
   ASSERT_THAT(purchase.Shares, Eq(5u));
   ASSERT_THAT(purchase.Date, Eq(Portfolio::FIXED_PURCHASE_DATE));
}
// END:PurchaseRecord


