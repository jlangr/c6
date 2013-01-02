#include "gmock/gmock.h"
#include "Portfolio.h"

using namespace ::testing;
using namespace std;

// START:const
class APortfolio: public Test {
public:
// START_HIGHLIGHT
   static const string IBM;
// END_HIGHLIGHT
   Portfolio portfolio_;
};
// START_HIGHLIGHT
const string APortfolio::IBM("IBM");
// END_HIGHLIGHT
// ...
// END:const
TEST_F(APortfolio, IsEmptyWhenCreated) {
   ASSERT_THAT(portfolio_.IsEmpty(), Eq(true));
}

// START:const
TEST_F(APortfolio, IsNotEmptyAfterPurchase) {
   portfolio_.Purchase(IBM, 1);

   ASSERT_THAT(portfolio_.IsEmpty(), Eq(false));
}
// ...
// END:const
TEST_F(APortfolio, AnswersZeroForSharesOfUnpurchasedSymbol) {
   ASSERT_THAT(portfolio_.Shares("AAPL"), Eq(0));
}

// START:const
TEST_F(APortfolio, AnswersSharesForPurchasedSymbol) {
   portfolio_.Purchase(IBM, 2);

   ASSERT_THAT(portfolio_.Shares(IBM), Eq(2));
}

TEST_F(APortfolio, ThrowsOnPurchaseOfZeroShares) {
   ASSERT_THROW(portfolio_.Purchase(IBM, 0), InvalidPurchaseException);
}
// END:const

