#pragma once
#include <vector>
#include "ThostFtdcMdApi.h"
#include "ThostFtdcUserApiDataType.h"
#include "ThostFtdcUserApiStruct.h"

using namespace std;
using std::vector;

class MdBo :public CThostFtdcMdSpi
{
public:
	MdBo(CThostFtdcMdApi * mApi);
	void Connect(char * Front_Addr);

	void OnFrontConnected();

	void OnFrontDisconnected();

	void Login(char * Broker_Id, char * User_Id, char * password);

	void AskPrice(char * InsId[]);

	void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData);

	bool isTimeToBuy();


	
private:
	int reqId;
	CThostFtdcMdApi * mApi;
	char * User_Id;
	char * Broker_Id;
	char * password;
	vector <float> price;
};