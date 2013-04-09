#include "gmock/gmock.h"
#include "Portfolio.h"

using namespace ::testing;
using namespace std;

class APortfolio: public Test {
public:
   static const string IBM;
   static const string SAMSUNG;
   Portfolio portfolio_;
};

const string APortfolio::IBM("IBM");
const string APortfolio::SAMSUNG("SSNLF");

// START:test
TEST_F(APortfolio, IsEmptyWhenCreated) {
// END:test
   ASSERT_THAT(portfolio_.IsEmpty(), Eq(true));
}

// START:test
TEST_F(APortfolio, IsNotEmptyAfterPurchase) {
// END:test
   portfolio_.Purchase(IBM, 1);

   ASSERT_THAT(portfolio_.IsEmpty(), Eq(false));
}

// START:test
TEST_F(APortfolio, AnswersZeroForSharesOfUnpurchasedSymbol) {
// END:test
   ASSERT_THAT(portfolio_.Shares("AAPL"), Eq(0u));
}

// START:test
TEST_F(APortfolio, AnswersSharesForPurchasedSymbol) {
// END:test
   portfolio_.Purchase(IBM, 2);

   ASSERT_THAT(portfolio_.Shares(IBM), Eq(2u));
}

// START:test
TEST_F(APortfolio, ThrowsOnPurchaseOfZeroShares) {
// END:test
   ASSERT_THROW(portfolio_.Purchase(IBM, 0), InvalidPurchaseException);
}

// START:test
TEST_F(APortfolio, AnswersSharesForAppropriateSymbol) {
// END:test
   portfolio_.Purchase(IBM, 5);
   portfolio_.Purchase(SAMSUNG, 10);

   ASSERT_THAT(portfolio_.Shares(IBM), Eq(5u));
}

// START:test
TEST_F(APortfolio, SharesReflectsAccumulatedPurchasesOfSameSymbol) {
// END:test
   portfolio_.Purchase(IBM, 5);
   portfolio_.Purchase(IBM, 15);

   ASSERT_THAT(portfolio_.Shares(IBM), Eq(5u + 15));
}

// START:test
TEST_F(APortfolio, ReducesSharesOfSymbolOnSell)  {
// END:test
   portfolio_.Purchase(SAMSUNG, 30);
   
   portfolio_.Sell(SAMSUNG, 13);

   ASSERT_THAT(portfolio_.Shares(SAMSUNG), Eq(30u - 13));
}

// START:test
TEST_F(APortfolio, ThrowsWhenSellingMoreSharesThanPurchased) {
// END:test
   ASSERT_THROW(portfolio_.Sell(SAMSUNG, 1), InvalidSellException);
}

