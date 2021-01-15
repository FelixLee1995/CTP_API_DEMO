#include "test_suit.h"

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


TEST_F(TradeApiTest, Order_CFFEX_Market) {
    
    Order order;
    order.instrumentid = "IF2102";
    order.direction = '0';
    order.offsetflag = '0';
    order.volumeTotalOrigin = 2;
    
    EXPECT_EQ(p_api->ReqOrderInsert(order, OrderType::Market), SYS_OK);

    usleep(1000000);
}


TEST_F(TradeApiTest, Order_CFFEX_LimitToMarket) {
    
    Order order;
    order.instrumentid = "IF2102";
    order.direction = '0';
    order.offsetflag = '0';
    order.volumeTotalOrigin = 2;
    
    EXPECT_EQ(p_api->ReqOrderInsert(order, OrderType::LimitToMarket), SYS_OK);

    usleep(1000000);
}


TEST_F(TradeApiTest, Order_CFFEX_FAK) {
    
    Order order;
    order.instrumentid = "IF2102";
    order.direction = '0';
    order.offsetflag = '0';
    order.volumeTotalOrigin = 2;
    
    EXPECT_EQ(p_api->ReqOrderInsert(order, OrderType::FAK), SYS_OK);

    usleep(1000000);
}

TEST_F(TradeApiTest, Order_CFFEX_FOK) {
    
    Order order;
    order.instrumentid = "IF2102";
    order.direction = '0';
    order.offsetflag = '0';
    order.volumeTotalOrigin = 2;
    
    EXPECT_EQ(p_api->ReqOrderInsert(order, OrderType::FOK), SYS_OK);

    usleep(1000000);
}




//===================== SHFE =======================

TEST_F(TradeApiTest, Order_SHFE_Limit) {
    
    Order order;
    order.instrumentid = "cu2102";
    order.direction = '0';
    order.offsetflag = '0';
    order.limitPrice = 2102;
    order.volumeTotalOrigin = 2;

    
    EXPECT_EQ(p_api->ReqOrderInsert(order, OrderType::LimitPrice), SYS_OK);

    usleep(1000000);
}


TEST_F(TradeApiTest, Order_SHFE_Market) {
    
    Order order;
    order.instrumentid = "cu2102";
    order.direction = '0';
    order.offsetflag = '0';
    order.volumeTotalOrigin = 2;
    
    EXPECT_EQ(p_api->ReqOrderInsert(order, OrderType::Market), SYS_OK);

    usleep(1000000);
}


TEST_F(TradeApiTest, Order_SHFE_LimitToMarket) {
    
    Order order;
    order.instrumentid = "cu2102";
    order.direction = '0';
    order.offsetflag = '0';
    order.volumeTotalOrigin = 2;
    
    EXPECT_EQ(p_api->ReqOrderInsert(order, OrderType::LimitToMarket), SYS_OK);

    usleep(1000000);
}


TEST_F(TradeApiTest, Order_SHFE_FAK) {
    
    Order order;
    order.instrumentid = "cu2102";
    order.direction = '0';
    order.offsetflag = '0';
    order.volumeTotalOrigin = 2;
    
    EXPECT_EQ(p_api->ReqOrderInsert(order, OrderType::FAK), SYS_OK);

    usleep(1000000);
}

TEST_F(TradeApiTest, Order_SHFE_FOK) {
    
    Order order;
    order.instrumentid = "cu2102";
    order.direction = '0';
    order.offsetflag = '0';
    order.volumeTotalOrigin = 2;
    
    EXPECT_EQ(p_api->ReqOrderInsert(order, OrderType::FOK), SYS_OK);

    usleep(1000000);
}



// ================  DCE ====================

TEST_F(TradeApiTest, Order_DCE_Limit) {
    
    Order order;
    order.instrumentid = "i2102";
    order.direction = '0';
    order.offsetflag = '0';
    order.limitPrice = 2102;
    order.volumeTotalOrigin = 2;

    
    EXPECT_EQ(p_api->ReqOrderInsert(order, OrderType::LimitPrice), SYS_OK);

    usleep(1000000);
}


TEST_F(TradeApiTest, Order_DCE_Market) {
    
    Order order;
    order.instrumentid = "i2102";
    order.direction = '0';
    order.offsetflag = '0';
    order.volumeTotalOrigin = 2;
    
    EXPECT_EQ(p_api->ReqOrderInsert(order, OrderType::Market), SYS_OK);

    usleep(1000000);
}


TEST_F(TradeApiTest, Order_DCE_LimitToMarket) {
    
    Order order;
    order.instrumentid = "i2102";
    order.direction = '0';
    order.offsetflag = '0';
    order.volumeTotalOrigin = 2;
    
    EXPECT_EQ(p_api->ReqOrderInsert(order, OrderType::LimitToMarket), SYS_OK);

    usleep(1000000);
}


TEST_F(TradeApiTest, Order_DCE_FAK) {
    
    Order order;
    order.instrumentid = "i2102";
    order.direction = '0';
    order.offsetflag = '0';
    order.volumeTotalOrigin = 2;
    
    EXPECT_EQ(p_api->ReqOrderInsert(order, OrderType::FAK), SYS_OK);

    usleep(1000000);
}

TEST_F(TradeApiTest, Order_DCE_FOK) {
    
    Order order;
    order.instrumentid = "i2102";
    order.direction = '0';
    order.offsetflag = '0';
    order.volumeTotalOrigin = 2;
    
    EXPECT_EQ(p_api->ReqOrderInsert(order, OrderType::FOK), SYS_OK);

    usleep(1000000);
}


// =================== ZCE =====================

TEST_F(TradeApiTest, Order_ZCE_Limit) {
    
    Order order;
    order.instrumentid = "CF105";
    order.direction = '0';
    order.offsetflag = '0';
    order.limitPrice = 2102;
    order.volumeTotalOrigin = 2;

    
    EXPECT_EQ(p_api->ReqOrderInsert(order, OrderType::LimitPrice), SYS_OK);

    usleep(1000000);
}


TEST_F(TradeApiTest, Order_ZCE_Market) {
    
    Order order;
    order.instrumentid = "CF105";
    order.direction = '0';
    order.offsetflag = '0';
    order.volumeTotalOrigin = 2;
    
    EXPECT_EQ(p_api->ReqOrderInsert(order, OrderType::Market), SYS_OK);

    usleep(1000000);
}


TEST_F(TradeApiTest, Order_ZCE_LimitToMarket) {
    
    Order order;
    order.instrumentid = "CF105";
    order.direction = '0';
    order.offsetflag = '0';
    order.volumeTotalOrigin = 2;
    
    EXPECT_EQ(p_api->ReqOrderInsert(order, OrderType::LimitToMarket), SYS_OK);

    usleep(1000000);
}


TEST_F(TradeApiTest, Order_ZCE_FAK) {
    
    Order order;
    order.instrumentid = "CF105";
    order.direction = '0';
    order.offsetflag = '0';
    order.volumeTotalOrigin = 2;
    
    EXPECT_EQ(p_api->ReqOrderInsert(order, OrderType::FAK), SYS_OK);

    usleep(1000000);
}

TEST_F(TradeApiTest, Order_ZCE_FOK) {
    
    Order order;
    order.instrumentid = "CF105";
    order.direction = '0';
    order.offsetflag = '0';
    order.volumeTotalOrigin = 2;
    
    EXPECT_EQ(p_api->ReqOrderInsert(order, OrderType::FOK), SYS_OK);

    usleep(1000000);
}


// ==================== INE ===================

TEST_F(TradeApiTest, Order_INE_Limit) {
    
    Order order;
    order.instrumentid = "lu2104";
    order.direction = '0';
    order.offsetflag = '0';
    order.limitPrice = 2102;
    order.volumeTotalOrigin = 2;

    
    EXPECT_EQ(p_api->ReqOrderInsert(order, OrderType::LimitPrice), SYS_OK);

    usleep(1000000);
}


TEST_F(TradeApiTest, Order_INE_Market) {
    
    Order order;
    order.instrumentid = "lu2104";
    order.direction = '0';
    order.offsetflag = '0';
    order.volumeTotalOrigin = 2;
    
    EXPECT_EQ(p_api->ReqOrderInsert(order, OrderType::Market), SYS_OK);

    usleep(1000000);
}


TEST_F(TradeApiTest, Order_INE_LimitToMarket) {
    
    Order order;
    order.instrumentid = "lu2104";
    order.direction = '0';
    order.offsetflag = '0';
    order.volumeTotalOrigin = 2;
    
    EXPECT_EQ(p_api->ReqOrderInsert(order, OrderType::LimitToMarket), SYS_OK);

    usleep(1000000);
}


TEST_F(TradeApiTest, Order_INE_FAK) {
    
    Order order;
    order.instrumentid = "lu2104";
    order.direction = '0';
    order.offsetflag = '0';
    order.volumeTotalOrigin = 2;
    
    EXPECT_EQ(p_api->ReqOrderInsert(order, OrderType::FAK), SYS_OK);

    usleep(1000000);
}

TEST_F(TradeApiTest, Order_INE_FOK) {
    
    Order order;
    order.instrumentid = "lu2104";
    order.direction = '0';
    order.offsetflag = '0';
    order.volumeTotalOrigin = 2;
    
    EXPECT_EQ(p_api->ReqOrderInsert(order, OrderType::FOK), SYS_OK);

    usleep(1000000);
}
