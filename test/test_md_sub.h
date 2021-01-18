#pragma once

#include "test_suit.h"

TEST_F(MdApiTest, Subscribe) {
    
    EXPECT_EQ(p_api->ReqSubscribeMarketData("IF2102"), 0);

    usleep(10000000);

    EXPECT_EQ(p_api->ReqUnSubscribeMarketData("IF2102"), 0);

    usleep(1000000);
}

