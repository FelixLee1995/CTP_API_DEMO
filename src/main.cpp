#include <iostream>
#include <fstream>
#include "api/ctp/ThostFtdcTraderApi.h"
#include "apiWrapper/ctp/MyCtpApi.h"
#include "apiWrapper/ctp/MyMarketApi.h"
#include "spdlog/sinks/daily_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"
#include "coredump.h"
#include "plantformtools.h"




void SetLogger()
{
    auto logger = spdlog::daily_logger_mt("daily_logger", "logs/system.log");
    logger->set_level(spdlog::level::debug);

    //logger->flush_on(spdlog::level::info);

    auto console_log_ptr = spdlog::stdout_color_mt("console");
    console_log_ptr->set_pattern("[%Y-%m-%d %H:%M:%S.%f] [%t] [%l] [%s:%#(%!)] %v");

    logger->set_pattern("[%Y-%m-%d %H:%M:%S.%f] [%t] [%l] [%s:%#(%!)] %v");

    spdlog::sinks_init_list sink_list = {logger->sinks().front()};

    auto mylogger_ = std::make_shared<spdlog::logger>("my_logger", sink_list);

    mylogger_->set_level(spdlog::level::debug);

    spdlog::flush_every(std::chrono::seconds(1));

    spdlog::set_default_logger(mylogger_);

    spdlog::set_level(spdlog::level::debug);
}



int main() {

    SetLogger();

    jupiter::SetCoredump();

    std::cout << "Hello World" << std::endl;

    std::cout << "CTP API VERSION is " << CThostFtdcTraderApi::GetApiVersion() << std::endl;

    
    std::ifstream ifs("config.txt");
    if (!ifs)
    {
        std::cout << "cant find config.txt" << std::endl;
        return -1;
    }

    std::string brokerid;
    std::string userid;
    std::string pwd;
    // simnow
    //const std::string frontAddr = "tcp://180.168.146.187:10110";

    // simnow 7x24
    //const std::string frontAddr = "tcp://180.168.146.187:10130";

    std::string frontAddr;

    ifs >> frontAddr >> brokerid >> userid >> pwd;


    MyMarketApi* md_api = new MyMarketApi(brokerid, userid, pwd, frontAddr);

    md_api->Init();   
    CommonSleep(1000);
    //std::cout << "TradingDay is " << md_api->GetTradingDay() << std::endl;
    
    

    md_api->ReqUserLogin();

    CommonSleep(1000);


    std::string cmd_1;
    std::string cmd_2;



    std::vector<std::string> cmdVec;

    while(true)
    {

        std::cin >> cmd_1;
        std::cin >> cmd_2;
        std::cout << "cmd is " << cmd_1 << " " << cmd_2 << std::endl;


        if (cmd_1 == "sleep")
        {
            auto secs = atoi(cmd_2.c_str());
            CommonSleep(secs*1000);
        }
        else if (cmd_1 == "sub")
        {
            md_api->ReqSubscribeMarketData(cmd_2);
        }
        else if (cmd_1 == "unsub")
        {
            md_api->ReqUnSubscribeMarketData(cmd_2);
        }
    }



    // std::ifstream ifs_instr("instruments.txt");
    // if (!ifs_instr)
    // {
    //     std::cerr << "cant find instruments.txt" << std::endl; 
    //     return -2;
    // }

    // std::string instr;
    // while (ifs_instr >> instr)
    // {   
    //     std::cout << "sub: " << instr << std::endl;
    //     md_api->ReqSubscribeMarketData(instr);
    // }


    // std::cout << "start unsub" << std::endl;



    // usleep(1000000);
    // md_api->ReqUnSubscribeMarketData(instr);

    //std::vector<std::string> marketInstrs = {"I*"};
    //std::vector<std::string> marketInstrs = {"IF2103", "IC2105", "a2105", "cu2105", "au2101"};
    //md_api->ReqUnSubscribeMarketData("a2105");


    std::cout << "start sleep" << std::endl;




    while(true)
    {
        CommonSleep(10000);
    }


    std::cout << "return" << std::endl;

    return 0;
}