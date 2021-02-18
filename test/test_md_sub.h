#ifndef _TEST_MD_SUB_H_
#define _TEST_MD_SUB_H_

#pragma once


#include "test_suit.h"

TEST_F(MdApiTest, Subscribe) {

    std::cout << "before ReqSubscribeMarketData"  << std::endl;
    EXPECT_EQ(p_api->ReqSubscribeMarketData("IF2102"), 0);

    usleep(3000000);

    EXPECT_EQ(p_api->ReqUnSubscribeMarketData("IF2102"), 0);

    usleep(3000000);
}


#endif