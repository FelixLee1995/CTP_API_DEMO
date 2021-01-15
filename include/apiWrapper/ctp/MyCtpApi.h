#pragma once
#include "api/ctp/ThostFtdcTraderApi.h"
#include "apiWrapper/ctp/MyCtpSpi.h"
#include <iostream>
#include <cstring>
#include <atomic>

const int SYS_OK = 0;
const int SYS_FAIL = -1;

class MyCtpSpi;



struct UserInfo {
    std::string userid;
    std::string brokerid;
};

struct Order {
    std::string userid;
    std::string brokerid;
    std::string instrumentid;
    char direction;
    char offsetflag;
    int volumeTotalOrigin;
    int volumeCondition;
    int minVolume;

    char orderPriceType;
    double limitPrice;
    char timeCondition;

};

enum OrderType{
    LimitPrice = 0,
    Market = 1,
    LimitToMarket = 2,
    FOK = 3,
    FAK =4
};


struct CancelOrder {

};


class MyCtpApi {
    public:
        MyCtpApi(std::string brokerid, std::string userid, std::string pwd, std::string frontAddr, std::string appid, std::string authcode);
        ~MyCtpApi();

        void Init();
        int ReqAuth();

        int ReqUserLogin(); 

        int ReqQrySettlementInfoConfirm();
        int ReqQrySettlementInfo();
        int ReqSettlementInfoConfirm();

        int ReqOrderInsert(const Order& order, OrderType);
        int ReqOrderAction();


        void Dispose();

        bool GetConnectStatus(){ return m_front_connect_stautus.load();}
        bool GetAuthStatus(){return m_auth_stautus;}
        bool GetLoginStatus(){return m_login_stautus;}

    private:

        //reqid, increased
        int m_rid;
        std::string m_brokerid;
        std::string m_userid;
        std::string m_pwd;
        std::string m_front_addr;
        std::string m_appid;
        std::string m_authcode;

        std::atomic<bool> m_front_connect_stautus; 
        std::atomic<bool> m_auth_stautus; 
        std::atomic<bool> m_login_stautus; 


        CThostFtdcTraderApi * m_api;
        MyCtpSpi* m_spi;
        friend class MyCtpSpi;
};