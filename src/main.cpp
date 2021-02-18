#include <iostream>

#include "api/ctp/ThostFtdcTraderApi.h"
#include "apiWrapper/ctp/MyCtpApi.h"
#include "apiWrapper/ctp/MyMarketApi.h"
#include "coredump.h"
#include <sys/unistd.h>

const std::string brokerid = "9999";
const std::string userid = "123616";
const std::string pwd = "nanase4ever";
// simnow
//const std::string frontAddr = "tcp://180.168.146.187:10110";   

// simnow 7x24
//const std::string frontAddr = "tcp://180.168.146.187:10130";   

const std::string frontAddr = "tcp://127.0.0.1:17001";

const std::string appid = "simnow_client_test";
const std::string authcode = "0000000000000000"; 



int main() {

    jupiter::SetCoredump();

    std::cout << "Hello World" << std::endl;

    std::cout << "CTP API VERSION is " << CThostFtdcTraderApi::GetApiVersion() << std::endl;

    // MyCtpApi* api = new MyCtpApi(brokerid, userid, pwd, frontAddr, appid, authcode);
    // api->Init();
    
    MyMarketApi* md_api = new MyMarketApi(brokerid, userid, pwd, frontAddr);
    

    md_api->Init();   
    usleep(1000000);
    //std::cout << "TradingDay is " << md_api->GetTradingDay() << std::endl;
    
    

    md_api->ReqUserLogin();
        usleep(1000000);

    md_api->ReqSubscribeMarketData("IF2104");

    //usleep(3000000);

    //md_api->ReqUnSubscribeMarketData("IF2103");

    usleep(20000000);

    //api->ReqAuth();

    //usleep(1000000);

    // api->ReqUserLogin();

    // usleep(1000000);

    // api->ReqQrySettlementInfoConfirm();

    // usleep(1000000);

    // api->ReqQrySettlementInfo();

    // usleep(1000000);

    // api->ReqSettlementInfoConfirm();


    getchar();

    return 0;
}