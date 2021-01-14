#pragma once
#include "api/ctp/ThostFtdcTraderApi.h"
#include "apiWrapper/ctp/MyCtpSpi.h"
#include <iostream>
#include <cstring>
#include <atomic>

const int SYS_OK = 0;
const int SYS_FAIL = -1;


// CThostFtdcInputOrderField ord;
// memset(&ord, 0, sizeof(ord));


// strcpy(ord.BrokerID, “2030”);
// strcpy(ord.InvestorID, “023526”);

// strcpy(ord.InstrumentID, “rb1601”);
// strcpy(ord.OrderRef, “”);

// ord.Direction = THOST_FTDC_D_Buy;
// ord.CombOffsetFlag[0] = THOST_FTDC_OF_Open;
// ord.CombHedgeFlag[0] = THOST_FTDC_HF_Speculation;
// ord.VolumeTotalOriginal = 1;
// ord.ContingentCondition = THOST_FTDC_CC_Immediately;
// ord.VolumeCondition = THOST_FTDC_VC_AV;
// ord.MinVolume = 1;
// ord.ForceCloseReason = THOST_FTDC_FCC_NotForceClose;
// ord.IsAutoSuspend = 0;
// ord.UserForceClose = 0;


struct UserInfo {

};

struct Order {

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

        int ReqOrderInsert();
        int ReqOrderAction();

        void Dispose();


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
        friend class MyCtpSpi;
};