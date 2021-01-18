#pragma once
#include "api/ctp/ThostFtdcMdApi.h"
#include "apiWrapper/ctp/MyMarketApi.h"
#include <iostream>

class MyMarketApi;



class MyMarketSpi: public CThostFtdcMdSpi {

    public:

		MyMarketSpi(MyMarketApi * api);

		~MyMarketSpi();

        void OnFrontConnected() override;
        void OnFrontDisconnected(int nReason) override;

        void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) override;

	    void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) override;

        	///��������Ӧ��
	    void OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) override;

	///ȡ����������Ӧ��
	    void OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) override;
	///�������֪ͨ
	    void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData) override;


    private:
        MyMarketApi* m_api_;
};