#ifndef _MY_MARKET_API_H_
#define _MY_MARKET_API_H_

#pragma once
#include "api/ctp/ThostFtdcMdApi.h"
#include "apiWrapper/ctp/MyMarketSpi.h"
#include <iostream>
#include <cstring>
#include <atomic>

class MyMarketSpi;


class MyMarketApi {
    public:
        MyMarketApi(std::string brokerid, std::string userid, std::string pwd, std::string frontAddr);
        ~MyMarketApi();

        void Init();
        int ReqAuth();

        int ReqUserLogin(); 

        int ReqSubscribeMarketData(const std::string& instrumentID);
        int ReqUnSubscribeMarketData(const std::string& instrumentID);

        void Dispose();

        bool GetConnectStatus(){ return m_front_connect_stautus.load();}
        bool GetLoginStatus(){return m_login_stautus;}

        const char* GetTradingDay();

    private:
        const int SYS_OK = 0;
        const int SYS_FAIL = -1;
        //reqid, increased
        int m_rid;
        std::string m_brokerid;
        std::string m_userid;
        std::string m_pwd;
        std::string m_front_addr;
        std::atomic<bool> m_front_connect_stautus; 
        std::atomic<bool> m_login_stautus; 


        CThostFtdcMdApi * m_api;
        MyMarketSpi* m_spi;
        friend class MyMarketSpi;
};

#endif