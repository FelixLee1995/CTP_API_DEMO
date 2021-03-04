#include "apiWrapper/ctp/MyCtpSpi.h"
#include <vector>
#include <chrono>

MyCtpSpi::MyCtpSpi(MyCtpApi *api): m_api_(api) {

}


MyCtpSpi::~MyCtpSpi() {

}

std::string MyCtpSpi::ConvertOrderStatus(char orderStatus)
{

	switch (orderStatus)
	{
	case THOST_FTDC_OST_AllTraded:
		return "全部成交";
	case THOST_FTDC_OST_PartTradedQueueing:
		return "部分成交";
	case THOST_FTDC_OST_NoTradeQueueing:
		return "δ???";
	case THOST_FTDC_OST_Canceled:
		return "已撤单";
	case THOST_FTDC_OST_Unknown:
		return "未知";
	default:
		return "非法类型";
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
    typedef std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds> nanoClock_type;

    nanoClock_type tp = std::chrono::time_point_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now());

	std::cout << "OnRtnOrder timestamp: " << tp.time_since_epoch().count() << "ns" << std::endl;

    std::cout << "OnRtnOrder, instrument: " <<   pOrder->InstrumentID << " , " << pOrder->ExchangeID
        << (pOrder->Direction == '0' ?  "买" : "卖" )
        << (pOrder->CombOffsetFlag[0] == '0' ?  "开" : "平")
        << pOrder->VolumeTotalOriginal << "手, "
        << "价格: " << pOrder->LimitPrice
        << ", 成交量: " << pOrder->VolumeTraded
        << ", 订单状态: " << ConvertOrderStatus(pOrder->OrderStatus)
        << ", 状态信息: " << pOrder->StatusMsg 
        << ", OrderRef: " << pOrder->OrderRef 
        << ", OrderLocalID: " << pOrder->OrderLocalID 
        << ", OrderSysID: " << pOrder->OrderSysID
        << std::endl; 
}


void MyCtpSpi::OnErrRtnOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo)
{

    typedef std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds> nanoClock_type;

    nanoClock_type tp = std::chrono::time_point_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now());

	std::cout << "OnErrRtnOrderInsert timestamp: " << tp.time_since_epoch().count() << "ns" << std::endl;

    if (pRspInfo&& pInputOrder) {
        std::cout << "OnErrRtnOrderInsert" <<  pInputOrder->InstrumentID << " , " << pInputOrder->ExchangeID
        << (pInputOrder->Direction == '0' ?  "买" : "卖" )
        << (pInputOrder->CombOffsetFlag[0] == '0' ?  "开" : "平")
        << pInputOrder->VolumeTotalOriginal << "手, "
        << "价格: " << pInputOrder->LimitPrice
        << ", 错误码: " << pRspInfo->ErrorID
        << ", 错误信息: " << pRspInfo->ErrorMsg
        << std::endl;
    }
}


void MyCtpSpi::OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{

    typedef std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds> nanoClock_type;

    nanoClock_type tp = std::chrono::time_point_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now());

    std::cout << "OnRspOrderInsert timestamp: " << tp.time_since_epoch().count() << "ns" << std::endl;

    if (pRspInfo && pInputOrder)
    {
        std::cout << "OnRspOrderInsert" <<  pInputOrder->InstrumentID << " , " << pInputOrder->ExchangeID
        << (pInputOrder->Direction == '0' ?  "买" : "卖" )
        << (pInputOrder->CombOffsetFlag[0] == '0' ?  "开" : "平")
        << pInputOrder->VolumeTotalOriginal << "手, "
        << "价格: " << pInputOrder->LimitPrice
        << ", 错误码: " << pRspInfo->ErrorID
        << ", 错误信息: " << pRspInfo->ErrorMsg
        << std::endl;
    } 

}


void MyCtpSpi::OnRtnTrade(CThostFtdcTradeField *pTrade) 
{
     std::cout << "OnRtnTrade, instrument: " <<   pTrade->InstrumentID << " , " << pTrade->ExchangeID
        << (pTrade->Direction == '0' ?  "买" : "卖" )
        << (pTrade->OffsetFlag == '0' ?  "开" : "平")
        << "数量" << pTrade->Volume << "手, "
        << "价格: " << pTrade->Price  << std::endl; 
}

void MyCtpSpi::OnRspQryTrade(CThostFtdcTradeField *pTrade, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    if (pRspInfo && pRspInfo->ErrorID == 0)
    {
        std::cout << "OnRspQryTrade Success" << std::endl;
        if (pTrade)
        {
            std::cout << "OnRspQryTrade, instrument: " << pTrade->InstrumentID << " , " << pTrade->ExchangeID
                      << (pTrade->Direction == '0' ? "买" : "卖")
                      << (pTrade->OffsetFlag == '0' ? "开" : "平")
                      << "数量" << pTrade->Volume << "手, "
                      << "价格: " << pTrade->Price << std::endl;
        }
    }
    else
    {
        std::cout << "OnRspQryTrade Failed!" << std::endl;
    }
}

void MyCtpSpi::OnRspQryOrder(CThostFtdcOrderField *pOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    if (pRspInfo && pRspInfo->ErrorID == 0)
    {
        std::cout << "OnRspQryOrder Success" << std::endl;
        if (pOrder)
        {
            std::cout << "OnRspQryOrder, instrument: " << pOrder->InstrumentID << " , " << pOrder->ExchangeID
                      << (pOrder->Direction == '0' ? "买" : "卖")
                      << (pOrder->CombOffsetFlag[0] == '0' ? "开" : "平")
                      << pOrder->VolumeTotalOriginal << "手, "
                      << "价格: " << pOrder->LimitPrice
                      << ", 成交量: " << pOrder->VolumeTraded
                      << ", 订单状态: " << ConvertOrderStatus(pOrder->OrderStatus)
                      << ", 状态信息: " << pOrder->StatusMsg
                      << ", OrderRef: " << pOrder->OrderRef
                      << ", OrderLocalID: " << pOrder->OrderLocalID
                      << ", OrderSysID: " << pOrder->OrderSysID
                      << std::endl;
        }
    }
    else
    {
        std::cout << "OnRspQryOrder Failed!" << std::endl;
    }
}

void MyCtpSpi::OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    if (pRspInfo && pRspInfo->ErrorID == 0)
    {
        std::cout << "OnRspQryTradingAccount Success" << std::endl;
        if (pTradingAccount)
        {
            std::cout << "OnRspQryTradingAccount, AccountID: " << pTradingAccount->AccountID
                      << ", Balance: " << pTradingAccount->Balance
                      << ", available: " << pTradingAccount->Available
                      << std::endl;
        }
    }
    else
    {
        std::cout << "OnRspQryTradingAccount Failed!" << std::endl;
    }
}

void MyCtpSpi::OnRspQryInvestorPositionDetail(CThostFtdcInvestorPositionDetailField *pInvestorPositionDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    if (pRspInfo && pRspInfo->ErrorID == 0)
    {
        std::cout << "OnRspQryInvestorPositionDetail Success" << std::endl;
        if (pInvestorPositionDetail)
        {
            std::cout << "OnRspQryInvestorPositionDetail, InstrumentID: " << pInvestorPositionDetail->InstrumentID << " , " << pInvestorPositionDetail->ExchangeID
                      << (pInvestorPositionDetail->Direction == '0' ? "买" : "卖")
                      << pInvestorPositionDetail->Volume << "手, "
                      << std::endl;
        }
    }
    else
    {
        std::cout << "OnRspQryInvestorPositionDetail Failed!" << std::endl;
    }
}

void MyCtpSpi::OnRspQryDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    if (pRspInfo && pRspInfo->ErrorID == 0)
    {
        std::cout << "OnRspQryDepthMarketData Success" << std::endl;
        if (pDepthMarketData)
        {
            std::cout << "OnRspQryDepthMarketData, instrumentid: " << pDepthMarketData->InstrumentID << ", lastPrice: " << pDepthMarketData->LastPrice << ", Volume: " << pDepthMarketData->Volume << std::endl;
        }
    }
    else
    {
        std::cout << "OnRspQryDepthMarketData Failed!" << std::endl;
    }
}


void MyCtpSpi::OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{

    if (pInstrument)
    {
        char ProductClass;
        if (pInstrument->ProductClass == THOST_FTDC_PC_Futures)
        {
            ProductClass = 'F';
        }
        else   if (pInstrument->ProductClass == THOST_FTDC_PC_Options)
        {
            ProductClass = 'O';
        }
        else   if (pInstrument->ProductClass == THOST_FTDC_PC_Combination)
        {
            ProductClass = 'C';
        }
        


        std::cout << pInstrument->InstrumentID << " " <<  ProductClass << " " << pInstrument->ExpireDate << " " << pInstrument->ExchangeID << std::endl;
    }


}