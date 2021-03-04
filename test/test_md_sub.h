#ifndef _TEST_MD_SUB_H_
#define _TEST_MD_SUB_H_

#pragma once


#include "test_suit_md.h"

TEST_F(MdApiTest, Subscribe) {

    std::vector<std::string> marketInstrs = {"IF2103", "IC2105", "a2104", "cu2105", "au2101"};
    p_api->ReqSubscribeMarketData(marketInstrs);

    usleep(3000000);


}


#endif