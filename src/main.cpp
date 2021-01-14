#include <iostream>

#include "api/ctp/ThostFtdcTraderApi.h"
#include "apiWrapper/ctp/MyCtpApi.h"
#include "coredump.h"
#include <sys/unistd.h>

const std::string brokerid = "9999";
const std::string userid = "123616";
const std::string pwd = "nanase4ever";
const std::string frontAddr = "tcp://180.168.146.187:10100";
const std::string appid = "simnow_client_test";
const std::string authcode = "0000000000000000"; 



int main() {

    jupiter::SetCoredump();

    std::cout << "Hello World" << std::endl;

    std::cout << "CTP API VERSION is " << CThostFtdcTraderApi::GetApiVersion() << std::endl;

    MyCtpApi* api = new MyCtpApi(brokerid, userid, pwd, frontAddr, appid, authcode);
    api->Init();
    
    usleep(1000000);

    api->ReqAuth();

    usleep(1000000);

    api->ReqUserLogin();

    usleep(1000000);

    api->ReqQrySettlementInfoConfirm();

    usleep(1000000);

    api->ReqQrySettlementInfo();

    usleep(1000000);

    api->ReqSettlementInfoConfirm();


    getchar();

    return 0;
}