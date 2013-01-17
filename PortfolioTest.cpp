#include "gmock/gmock.h"
#include "Portfolio.h"
#include "boost/date_time/gregorian/gregorian_types.hpp"

using namespace ::testing;
using namespace std;
using namespace boost::gregorian;

static const date ArbitraryDate(2014, Sep, 5);

class APurchaseRecord: public Test {
public:
};

class APortfolio: public Test {
public:
   static const string IBM;
   static const string SAMSUNG;
   Portfolio portfolio_;

   void Purchase(
         const string& symbol, 
         unsigned int shares,
         const date& transactionDate=ArbitraryDate) {
      portfolio_.Purchase(symbol, shares, transactionDate);
   }

   void Sell(
         const string& symbol, 
         unsigned int shares,
         const date& transactionDate=ArbitraryDate) {
      portfolio_.Sell(symbol, shares, transactionDate);
   }

   void ASSERT_PURCHASE(
         PurchaseRecord& purchase, unsigned int shares, const date& transactionDate) {
      ASSERT_THAT(purchase.Shares, Eq(shares));
      ASSERT_THAT(purchase.Date, Eq(transactionDate));
   }
};

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
   ASSERT_THAT(portfolio_.Shares("AAPL"), Eq(0));
}

TEST_F(APortfolio, AnswersSharesForPurchasedSymbol) {
   Purchase(IBM, 2);

   ASSERT_THAT(portfolio_.Shares(IBM), Eq(2));
}

TEST_F(APortfolio, ThrowsOnPurchaseOfZeroShares) {
   ASSERT_THROW(Purchase(IBM, 0), SharesCannotBeZeroException);
}

TEST_F(APortfolio, AnswersSharesForAppropriateSymbol) {
   Purchase(IBM, 5);
   Purchase(SAMSUNG, 10);

   ASSERT_THAT(portfolio_.Shares(IBM), Eq(5));
}

TEST_F(APortfolio, SharesReflectsAccumulatedPurchasesOfSameSymbol) {
   Purchase(IBM, 5);
   Purchase(IBM, 15);

   ASSERT_THAT(portfolio_.Shares(IBM), Eq(5 + 15));
}

TEST_F(APortfolio, ReducesSharesOfSymbolOnSell)  {
   Purchase(SAMSUNG, 30);
   
   Sell(SAMSUNG, 13);

   ASSERT_THAT(portfolio_.Shares(SAMSUNG), Eq(30 - 13));
}

TEST_F(APortfolio, ThrowsWhenSellingMoreSharesThanPurchased) {
   ASSERT_THROW(Sell(SAMSUNG, 1), InvalidSellException);
}

TEST_F(APortfolio, AnswersThePurchaseRecordForASinglePurchase) {
   Purchase(SAMSUNG, 5, ArbitraryDate);

   auto purchases = portfolio_.Purchases(SAMSUNG);

   ASSERT_PURCHASE(purchases[0], 5, ArbitraryDate);
}

TEST_F(APortfolio, IncludesSalesInPurchaseRecords) {
   Purchase(SAMSUNG, 10);
   Sell(SAMSUNG, 5, ArbitraryDate);

   auto sales = portfolio_.Purchases(SAMSUNG);

   ASSERT_PURCHASE(sales[1], -5, ArbitraryDate);
}

TEST_F(APortfolio, ThrowsOnSellOfZeroShares) {
   ASSERT_THROW(Sell(IBM, 0), SharesCannotBeZeroException);
}

TEST_F(APurchaseRecord, IsEqualToAnotherWhenSharesAndDateMatch) {
   PurchaseRecord a(10, ArbitraryDate);
   PurchaseRecord b(10, ArbitraryDate);

   ASSERT_THAT(a == b, Eq(true));
}

TEST_F(APurchaseRecord, IsUnequalWhenSharesDoNotMatch) {
   PurchaseRecord a(10, ArbitraryDate);
   PurchaseRecord b(a.Shares + 1, ArbitraryDate);

   ASSERT_THAT(a != b, Eq(true));
}

TEST_F(APurchaseRecord, IsUnequalWhenDatesDoNotMatch) {
   PurchaseRecord a(10, ArbitraryDate);
   PurchaseRecord b(10, ArbitraryDate + date_duration(1));

   ASSERT_THAT(a != b, Eq(true));
}

TEST_F(APortfolio, SeparatesPurchaseRecordsBySymbol) {
   Purchase(SAMSUNG, 5, ArbitraryDate);
   Purchase(IBM, 1, ArbitraryDate);

   auto sales = portfolio_.Purchases(SAMSUNG);

   vector<PurchaseRecord> expected { PurchaseRecord(5, ArbitraryDate) };

   ASSERT_THAT(sales, Eq(expected));
}
