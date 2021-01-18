#include "test_suit.h"
#include <chrono>

TEST_F(TradeApiTest, Order_Time_Record) {
    
    Order order;
    order.instrumentid = "IF2102";
    order.direction = '0';
    order.offsetflag = '0';
    order.limitPrice = 0;
    order.volumeTotalOrigin = 2;


    auto start = std::chrono::system_clock::now();

    auto ret = p_api->ReqOrderInsert(order, OrderType::Market);

    auto end = std::chrono::system_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    std::cout << (double)(duration.count()) * std::chrono::nanoseconds::period::num / 
        std::chrono::nanoseconds::period::den  << "ns" << std::endl;
    
    EXPECT_EQ(ret, SYS_OK);
    usleep(1000000);
}


TEST_F(TradeApiTest, Order_Time_Record2) {
    
    Order order;
    order.instrumentid = "IF2102";
    order.direction = '0';
    order.offsetflag = '0';
    order.limitPrice = 0;
    order.volumeTotalOrigin = 2;


    typedef std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds> nanoClock_type;
	//获取当前时间点，windows system_clock是100纳秒级别的(不同系统不一样，自己按照介绍的方法测试)，所以要转换
	nanoClock_type tp = std::chrono::time_point_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now());

	std::cout << "beforeOrderInsert timestamp: " << tp.time_since_epoch().count() << "ns" << std::endl;

    auto ret = p_api->ReqOrderInsert(order, OrderType::Market);

    tp = std::chrono::time_point_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now());

	std::cout << "afterOrderInsert timestamp: " << tp.time_since_epoch().count() << "ns" << std::endl;
    
    EXPECT_EQ(ret, SYS_OK);
    usleep(1000000);
}


TEST_F(TradeApiTest, Order_Time_Record3) {
    
    Order order;
    order.instrumentid = "cu2102";
    order.direction = '0';
    order.offsetflag = '0';
    order.limitPrice = 1000;
    order.volumeTotalOrigin = 2;


    typedef std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds> nanoClock_type;
	//获取当前时间点，windows system_clock是100纳秒级别的(不同系统不一样，自己按照介绍的方法测试)，所以要转换
	nanoClock_type tp = std::chrono::time_point_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now());

	std::cout << "beforeOrderInsert timestamp: " << tp.time_since_epoch().count() << "ns" << std::endl;

    auto ret = p_api->ReqOrderInsert(order, OrderType::LimitPrice);

    tp = std::chrono::time_point_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now());

	std::cout << "afterOrderInsert timestamp: " << tp.time_since_epoch().count() << "ns" << std::endl;
    
    EXPECT_EQ(ret, SYS_OK);
    usleep(1000000);
}