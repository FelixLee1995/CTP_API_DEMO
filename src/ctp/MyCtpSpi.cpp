#include "apiWrapper/ctp/MyCtpSpi.h"
#include <vector>

MyCtpSpi::MyCtpSpi(MyCtpApi *api): m_api_(api) {

}


MyCtpSpi::~MyCtpSpi() {

}

std::string MyCtpSpi::ConvertOrderStatus(char orderStatus)
{

	switch (orderStatus)
	{
	case THOST_FTDC_OST_AllTraded:
		return "ȫ���ɽ�";
	case THOST_FTDC_OST_PartTradedQueueing:
		return "���ֳɽ�";
	case THOST_FTDC_OST_NoTradeQueueing:
		return "δ�ɽ�";
	case THOST_FTDC_OST_Canceled:
		return "�ѳ���";
	case THOST_FTDC_OST_Unknown:
		return "δ֪";
	default:
		return "�Ƿ���״̬";
	}
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


void MyCtpSpi::OnRtnOrder(CThostFtdcOrderField *pOrder) 
{
    std::cout << "OnRtnOrder, instrument: " <<   pOrder->InstrumentID << " , " << pOrder->ExchangeID
        << (pOrder->Direction == '0' ?  "��" : "��" )
        << (pOrder->CombOffsetFlag[0] == '0' ?  "��" : "ƽ")
        << pOrder->VolumeTotalOriginal << "��, "
        << "�۸�: " << pOrder->LimitPrice
        << ", �ѳɽ�����: " << pOrder->VolumeTraded
        << ", ״̬:" << ConvertOrderStatus(pOrder->OrderStatus)
        << ", ����״̬��Ϣ: " << pOrder->StatusMsg 
        << ", OrderRef: " << pOrder->OrderRef 
        << ", OrderLocalID: " << pOrder->OrderLocalID 
        << ", OrderSysID: " << pOrder->OrderSysID
        << std::endl; 
}


void MyCtpSpi::OnErrRtnOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo)
{
    if (pRspInfo&& pInputOrder) {
        std::cout << "OnErrRtnOrderInsert" <<  pInputOrder->InstrumentID << " , " << pInputOrder->ExchangeID
        << (pInputOrder->Direction == '0' ?  "��" : "��" )
        << (pInputOrder->CombOffsetFlag[0] == '0' ?  "��" : "ƽ")
        << pInputOrder->VolumeTotalOriginal << "��, "
        << "�۸�: " << pInputOrder->LimitPrice
        << ", ������: " << pRspInfo->ErrorID
        << ", ������Ϣ: " << pRspInfo->ErrorMsg
        << std::endl;
    }
}


void MyCtpSpi::OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
       if (pRspInfo&& pInputOrder) {
        std::cout << "OnRspOrderInsert" <<  pInputOrder->InstrumentID << " , " << pInputOrder->ExchangeID
        << (pInputOrder->Direction == '0' ?  "��" : "��" )
        << (pInputOrder->CombOffsetFlag[0] == '0' ?  "��" : "ƽ")
        << pInputOrder->VolumeTotalOriginal << "��, "
        << "�۸�: " << pInputOrder->LimitPrice
        << ", ������: " << pRspInfo->ErrorID
        << ", ������Ϣ: " << pRspInfo->ErrorMsg
        << std::endl;
    } 

}


void MyCtpSpi::OnRtnTrade(CThostFtdcTradeField *pTrade) 
{
     std::cout << "OnRtnTrade, instrument: " <<   pTrade->InstrumentID << " , " << pTrade->ExchangeID
        << (pTrade->Direction == '0' ?  "��" : "��" )
        << (pTrade->OffsetFlag == '0' ?  "��" : "ƽ")
        << "�ɽ�" << pTrade->Volume << "��, "
        << "�۸�: " << pTrade->Price  << std::endl; 
}