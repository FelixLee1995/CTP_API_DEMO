#include "apiWrapper/ctp/MyCtpSpi.h"
#include <vector>

MyCtpSpi::MyCtpSpi(MyCtpApi *api): m_api_(api) {

}


MyCtpSpi::~MyCtpSpi() {

}


void MyCtpSpi::OnFrontConnected() {
    std::cout << "TradeFront connected!" << std::endl;
    m_api_->m_front_connect_stautus.store(true);
}


void MyCtpSpi::OnFrontDisconnected(int nReason){
    std::cout << "TradeFront disconnected!" << std::endl;
    m_api_->m_front_connect_stautus.store(false);

}


void MyCtpSpi::OnRspAuthenticate(CThostFtdcRspAuthenticateField *pRspAuthenticateField, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    if (pRspInfo&& pRspInfo->ErrorID == 0) {
        std::cout << "Auth Success!" << std::endl;
        m_api_->m_auth_stautus.store(true);
        return;
    }
    m_api_->m_auth_stautus.store(false);
    std::cout << "Auth Failed" << std::endl;  

}

void MyCtpSpi::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    if (pRspInfo&& pRspInfo->ErrorID == 0) {
        std::cout << "Login Success!" << std::endl;
        m_api_->m_login_stautus.store(true);
        return;
    }

    m_api_->m_login_stautus.store(true);
    std::cout << "Login Failed" << std::endl;  
}

void MyCtpSpi::OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    if (pRspInfo&& pRspInfo->ErrorID == 0) {
        std::cout << "Logout Success!" << std::endl;
        return;
    }

    std::cout << "Logout Failed" << std::endl; 
}

void MyCtpSpi::OnRspQrySettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{

    if (!pRspInfo) {
        std::cout << "failed to QrySettlementInfoConfirm " << std::endl;
        return;
    }

    if (pRspInfo->ErrorID == 0) {
        std::cout << "QrySettlementInfoConfirm success" << std::endl;
    }
    else {
        
        std::cout << "QrySettlementInfoConfirm failed, errorid: " << pRspInfo->ErrorID << " errormsg: " << pRspInfo->ErrorMsg << std::endl;
        return;
    }

    std:: cout << "confirm data: " << pSettlementInfoConfirm->ConfirmDate << " time: " << pSettlementInfoConfirm->ConfirmTime << std::endl;
}


void MyCtpSpi::OnRspQrySettlementInfo(CThostFtdcSettlementInfoField *pSettlementInfo, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    static std::vector<char> settlementInfo;
    if (pRspInfo&& pRspInfo->ErrorID == 0) {
        settlementInfo.insert(settlementInfo.end(), pSettlementInfo->Content, pSettlementInfo->Content+ sizeof(pSettlementInfo->Content));
    }


    if (bIsLast) {
        for (char &c : settlementInfo) {
            std::cout << c;
        }
        
        std::cout << "\nend of settlementInfo." << std::endl;
        settlementInfo.clear();
    }
}


void MyCtpSpi::OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{

    if (pRspInfo&& pRspInfo->ErrorID == 0) {
        std::cout << "SettlementInfoConfirm success!" << std::endl;
    }
    else {
        std::cout << "Failed to settlementInfoConfirm" << std::endl;
    }

    



}