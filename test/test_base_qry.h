#include "test_suit_trade.h"
#include <chrono>

// TEST_F(TradeApiTest, QryTrade) {


//     EXPECT_EQ(p_api->ReqQryTrade(), 0);
//     usleep(1000000);
// }


// TEST_F(TradeApiTest, QryOrder) {


//     EXPECT_EQ(p_api->ReqQryOrder(), 0);
//     usleep(1000000);
// }

// TEST_F(TradeApiTest, QryTradingAccount) {


//     EXPECT_EQ(p_api->ReqQryTradingAccount(), 0);
//     usleep(1000000);
// }

// TEST_F(TradeApiTest, QryPositionDetail) {


//     EXPECT_EQ(p_api->ReqQryPositionDetail(), 0);
//     usleep(1000000);
// }

// TEST_F(TradeApiTest, QryMarketData) {


//     EXPECT_EQ(p_api->ReqQryDepthMarketData("IF2102"), 0);
//     usleep(1000000);
// }


TEST_F(TradeApiTest, QryInstrument) {


    EXPECT_EQ(p_api->ReqQryInstrument(), 0);
    usleep(1000000);
}


