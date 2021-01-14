#include "apiWrapper/ctp/MyCtpApi.h"

MyCtpApi::MyCtpApi(std::string brokerid, std::string userid, std::string pwd, std::string frontAddr, std::string appid, std::string authcode):   
    m_rid(1),
    m_brokerid(brokerid),
    m_userid(userid),
    m_pwd(pwd), 
    m_front_addr(frontAddr),
    m_appid(appid),
    m_authcode(authcode),
    m_api(nullptr),
    m_front_connect_stautus(false),
    m_auth_stautus(false),
    m_login_stautus(false)
{
    
}


void MyCtpApi::Init() {
    m_api = CThostFtdcTraderApi::CreateFtdcTraderApi();
    MyCtpSpi* spi = new MyCtpSpi(this);
    m_api->RegisterSpi(spi);

    m_api->RegisterFront(const_cast<char *>(m_front_addr.c_str()));
    m_api->SubscribePrivateTopic(THOST_TERT_QUICK);
    m_api->SubscribePublicTopic(THOST_TERT_QUICK);

    m_api->Init();
}

int MyCtpApi::ReqAuth() {

    auto check_flag = m_front_connect_stautus.load();

    if (!check_flag) 
    {
        std::cout << "please connect front fisrt!" << std::endl;
        return SYS_FAIL;
    }


    CThostFtdcReqAuthenticateField pReqAuthenticateField = {};
    memcpy(&pReqAuthenticateField.BrokerID, m_brokerid.c_str(), sizeof(pReqAuthenticateField.BrokerID));
    memcpy(&pReqAuthenticateField.UserID, m_userid.c_str(), sizeof(pReqAuthenticateField.UserID));
    memcpy(&pReqAuthenticateField.AppID, m_appid.c_str(), sizeof(pReqAuthenticateField.AppID));
    memcpy(&pReqAuthenticateField.AuthCode, m_authcode.c_str(), sizeof(pReqAuthenticateField.AuthCode));

    m_api->ReqAuthenticate(&pReqAuthenticateField, m_rid++);

    return SYS_OK;
}

int MyCtpApi::ReqUserLogin() {

    auto check_flag = m_auth_stautus.load();

    if (!check_flag) 
    {
        std::cout << "please auth fisrt!" << std::endl;
        return SYS_FAIL;
    }

    CThostFtdcReqUserLoginField reqUserLoginField = {};
    memcpy(&reqUserLoginField.BrokerID, m_brokerid.c_str(), sizeof(reqUserLoginField.BrokerID));
    memcpy(&reqUserLoginField.UserID, m_userid.c_str(), sizeof(reqUserLoginField.UserID));
    memcpy(&reqUserLoginField.Password, m_pwd.c_str(), sizeof(reqUserLoginField.Password));

    m_api->ReqUserLogin(&reqUserLoginField, m_rid++);

    return SYS_OK;
}

int MyCtpApi::ReqQrySettlementInfoConfirm() {
     auto check_flag = m_login_stautus.load();

    if (!check_flag) 
    {
        std::cout << "please login fisrt!" << std::endl;
        return SYS_FAIL;
    }

    CThostFtdcQrySettlementInfoConfirmField field = {};
    memcpy(&field.BrokerID, m_brokerid.c_str(), sizeof(field.BrokerID));
    memcpy(&field.InvestorID, m_userid.c_str(), sizeof(field.InvestorID));

    m_api->ReqQrySettlementInfoConfirm(&field, m_rid++);

    return SYS_OK;
}

int MyCtpApi::ReqQrySettlementInfo() {
     auto check_flag = m_login_stautus.load();

    if (!check_flag) 
    {
        std::cout << "please login fisrt!" << std::endl;
        return SYS_FAIL;
    }

    CThostFtdcQrySettlementInfoField field = {};
    memcpy(&field.BrokerID, m_brokerid.c_str(), sizeof(field.BrokerID));
    memcpy(&field.InvestorID, m_userid.c_str(), sizeof(field.InvestorID));

    m_api->ReqQrySettlementInfo(&field, m_rid++);

    return SYS_OK;
}


int MyCtpApi::ReqSettlementInfoConfirm() {
     auto check_flag = m_login_stautus.load();

    if (!check_flag) 
    {
        std::cout << "please login fisrt!" << std::endl;
        return SYS_FAIL;
    }

    CThostFtdcSettlementInfoConfirmField field = {};
    memcpy(&field.BrokerID, m_brokerid.c_str(), sizeof(field.BrokerID));
    memcpy(&field.InvestorID, m_userid.c_str(), sizeof(field.InvestorID));

    m_api->ReqSettlementInfoConfirm(&field, m_rid++);

    return SYS_OK;
}