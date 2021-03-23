#include "apiWrapper/ctp/MyMarketSpi.h"
#include <chrono>
#include <vector>
#include "spdlog/spdlog.h"

MyMarketSpi::MyMarketSpi(MyMarketApi *api) : m_api_(api) {}

MyMarketSpi::~MyMarketSpi() {}

void MyMarketSpi::OnFrontConnected()
{
    std::cout << "TradeFront connected!" << std::endl;
    m_api_->m_front_connect_stautus.store(true);
}

void MyMarketSpi::OnFrontDisconnected(int nReason)
{
    std::cout << "TradeFront disconnected!" << std::endl;
    m_api_->m_front_connect_stautus.store(false);
}

void MyMarketSpi::OnRspUserLogin(
    CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    if (pRspInfo && pRspInfo->ErrorID == 0)
    {
        std::cout << "Login Success!" << std::endl;
        m_api_->m_login_stautus.store(true);
        return;
    }

    m_api_->m_login_stautus.store(true);
    std::cout << "Login Failed" << std::endl;
}

void MyMarketSpi::OnRspUserLogout(
    CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    if (pRspInfo && pRspInfo->ErrorID == 0)
    {
        std::cout << "Logout Success!" << std::endl;
        return;
    }

    std::cout << "Logout Failed" << std::endl;
}

void MyMarketSpi::OnRspSubMarketData(
    CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    std::cout << "OnRspSubMarketData!" << std::endl;

    if (pRspInfo && pRspInfo->ErrorID == 0)
    {
        if (pSpecificInstrument)
        {
            SPDLOG_INFO("OnRspSubMarketData, subscribe success: {}", pSpecificInstrument->InstrumentID);
        }
    }


}

void MyMarketSpi::OnRspUnSubMarketData(
    CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    std::cout << "OnRspUnSubMarketData!" << std::endl;

    if (pRspInfo && pRspInfo->ErrorID == 0)
    {
        if (pSpecificInstrument)
        {
            std::cout << "unsubscribe success: " << pSpecificInstrument->InstrumentID << std::endl;
        }
    }
}

void MyMarketSpi::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData)
{
    // typedef std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds> nanoClock_type;
    // //获取当前时间点，windows system_clock是100纳秒级别的(不同系统不一样，自己按照介绍的方法测试)，所以要转换
    // nanoClock_type tp = std::chrono::time_point_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now());


    SPDLOG_INFO("RTN, instrumentid: {}, lastPrice: {}, Volume: {}", pDepthMarketData->InstrumentID, pDepthMarketData->LastPrice, pDepthMarketData->Volume);
}
