#pragma once
#include <iostream>
#include "ThostFtdcTraderApi.h"
#include "ThostFtdcUserApiDataType.h"
#include "ThostFtdcUserApiStruct.h"
#include <vector>

using namespace std;
using std::vector;

class TdBo :public CThostFtdcTraderSpi
{
public:

	///���캯��
	TdBo(CThostFtdcTraderApi *pApi) {};

	///����
	void Connect(char * front_Addr);

	///��½
	void Login(char * Broker_Id, char *User_Id, char *password);

	void OnFrontConnected();

	void OnFrontDisconnected();

	///����֪ͨ
	void OnRtnOrder(CThostFtdcOrderField *pOrder) {};

	///�ɽ�֪ͨ
	void OnRtnTrade(CThostFtdcTradeField *pTrade) {};


	///��½������Ӧ
	virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///����¼��������Ӧ
	void OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///��������������Ӧ
	virtual void OnRspOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///��ѯ��󱨵�������Ӧ
	virtual void OnRspQueryMaxOrderVolume(CThostFtdcQueryMaxOrderVolumeField *pQueryMaxOrderVolume, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///Ͷ���߽�����ȷ����Ӧ
	virtual void OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///ѯ��¼��������Ӧ
	virtual void OnRspForQuoteInsert(CThostFtdcInputForQuoteField *pInputForQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///����¼��������Ӧ
	virtual void OnRspQuoteInsert(CThostFtdcInputQuoteField *pInputQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///���۲���������Ӧ
	virtual void OnRspQuoteAction(CThostFtdcInputQuoteActionField *pInputQuoteAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///������������������Ӧ
	virtual void OnRspBatchOrderAction(CThostFtdcInputBatchOrderActionField *pInputBatchOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///���۵�
	void ReqPrice(int * Volume);


	int increaseVol();
	int increaseVolume;

private:
	int myreqId;
	CThostFtdcTraderApi *pApi;
	char * Broker_Id;
	char * User_Id;
	char * password;
	int VolumeTraded = 0;
	int VolumeUnTraded = 0;
};