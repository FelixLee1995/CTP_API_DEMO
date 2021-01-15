#include <iostream>
#include <gtest/gtest.h>
#include "apiWrapper/ctp/MyCtpApi.h"

const std::string brokerid = "9999";
const std::string userid = "123616";
const std::string pwd = "nanase4ever";
const std::string frontAddr = "tcp://180.168.146.187:10100";
const std::string appid = "simnow_client_test";
const std::string authcode = "0000000000000000"; 

class TradeApiTest: public testing::Test {

    protected:

    virtual void SetUp() override {

        p_api = new MyCtpApi(brokerid, userid, pwd, frontAddr, appid, authcode);
        p_api->Init();
        usleep(1000000);
        EXPECT_EQ(p_api->GetConnectStatus(), true);
        p_api->ReqAuth();
        usleep(1000000);
        EXPECT_EQ(p_api->GetAuthStatus(), true);
        p_api->ReqUserLogin();
        usleep(1000000);
        EXPECT_EQ(p_api->GetLoginStatus(), true);

        p_api->ReqSettlementInfoConfirm();

        usleep(100000);
    };

    virtual void TearDown() override {
        delete p_api;
        p_api = nullptr;
    }

    MyCtpApi * p_api;

};


TEST_F(TradeApiTest, Order_CFFEX_Limit) {
    
    Order order;
    order.instrumentid = "IF2102";
    order.direction = '0';
    order.offsetflag = '0';
    order.limitPrice = 2102;
    order.volumeTotalOrigin = 2;

    
    EXPECT_EQ(p_api->ReqOrderInsert(order, OrderType::LimitPrice), SYS_OK);

    usleep(1000000);
}


int main(){
    testing::InitGoogleTest();

    std::cout << "hello test!" << std::endl;

    return RUN_ALL_TESTS();
}