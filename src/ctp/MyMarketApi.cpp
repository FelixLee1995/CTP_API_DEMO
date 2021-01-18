#include "apiWrapper/ctp/MyMarketApi.h"

MyMarketApi::MyMarketApi(std::string brokerid, std::string userid, std::string pwd, std::string frontAddr):   
    m_rid(1),
    m_brokerid(brokerid),
    m_userid(userid),
    m_pwd(pwd), 
    m_front_addr(frontAddr),
    m_api(nullptr),
    m_spi(nullptr),
    m_front_connect_stautus(false),
    m_login_stautus(false)
{
    
}


void MyMarketApi::Dispose() {

}


MyMarketApi::~MyMarketApi() {
    std::cout <<  "MyMarketApi deConstruction!" << std::endl;

    if (m_api)
    {
        m_api->RegisterSpi(nullptr);
        m_api->Release();
        m_api = nullptr;
    }

    if (m_spi)
    {
        delete m_spi;
        m_spi = nullptr;
    }
}


void MyMarketApi::Init() {
    m_api = CThostFtdcMdApi::CreateFtdcMdApi();
    m_spi = new MyMarketSpi(this);
    m_api->RegisterSpi(m_spi);

    m_api->RegisterFront(const_cast<char *>(m_front_addr.c_str()));

    m_api->Init();
}


int MyMarketApi::ReqUserLogin() {

    auto check_flag = m_front_connect_stautus.load();

    if (!check_flag) 
    {
        std::cout << "please connect fisrt!" << std::endl;
        return SYS_FAIL;
    }

    CThostFtdcReqUserLoginField reqUserLoginField = {};
    memcpy(&reqUserLoginField.BrokerID, m_brokerid.c_str(), sizeof(reqUserLoginField.BrokerID));
    memcpy(&reqUserLoginField.UserID, m_userid.c_str(), sizeof(reqUserLoginField.UserID));
    memcpy(&reqUserLoginField.Password, m_pwd.c_str(), sizeof(reqUserLoginField.Password));

    m_api->ReqUserLogin(&reqUserLoginField, m_rid++);

    return SYS_OK;
}


int MyMarketApi::ReqSubscribeMarketData(const std::string& instrumentID) {
    int res = SYS_FAIL;
    char ** instrument = new char*[1];
    instrument[0] = new char[31];
    std::memcpy(instrument[0], instrumentID.c_str(), sizeof(instrument[0]));
    res = m_api->SubscribeMarketData(instrument, 1);


    delete []instrument[0];
    delete []instrument;
    return res;
}


int MyMarketApi::ReqUnSubscribeMarketData(const std::string& instrumentID) {
    int res = SYS_FAIL;
    char **instrument = new char*[1];
    instrument[0] = new char[31];
    std::memcpy(instrument[0], instrumentID.c_str(), sizeof(instrument[0]));
    res = m_api->UnSubscribeMarketData(instrument, 1);
    
    delete []instrument[0];
    delete []instrument;

    return res;
}