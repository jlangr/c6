#include "gmock/gmock.h"
#include "Portfolio.h"

using namespace ::testing;

class APortfolio: public Test {
public:
   Portfolio portfolio_;
};

TEST_F(APortfolio, IsEmptyWhenCreated) {
   ASSERT_THAT(portfolio_.IsEmpty(), Eq(true));
}

TEST_F(APortfolio, IsNotEmptyAfterPurchase) {
   portfolio_.Purchase("IBM", 1);

   ASSERT_THAT(portfolio_.IsEmpty(), Eq(false));
}

TEST_F(APortfolio, AnswersZeroForSharesOfUnpurchasedSymbol) {
   ASSERT_THAT(portfolio_.Shares("AAPL"), Eq(0u));
}

// START:DuplicateConstants
TEST_F(APortfolio, AnswersSharesForPurchasedSymbol) {
   portfolio_.Purchase("IBM", 2);

   ASSERT_THAT(portfolio_.Shares("IBM"), Eq(2u));
}
// END:DuplicateConstants

