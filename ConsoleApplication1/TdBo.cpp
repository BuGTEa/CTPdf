#include <iostream>
#include "ThostFtdcTraderApi.h"
#include "ThostFtdcMdApi.h"
#include <time.h>
#include "TdBo.h"
#include <vector>

using namespace std;
using std::vector;

///���캯��
TdBo::TdBo(CThostFtdcTraderApi *pApi)
{
	this->myreqId = 1;
	this->pApi = pApi;
}

void TdBo::Connect(char * Front_Addr)
{
	cout << "�������ӽ��׷�����" << endl;
	this->pApi->RegisterFront(Front_Addr);
	this->pApi->RegisterSpi(this);
	this->pApi->SubscribePublicTopic(THOST_TERT_RESUME);
	this->pApi->SubscribePrivateTopic(THOST_TERT_RESUME);
	this->pApi->Init();

}

void TdBo::OnFrontConnected()
{
	cout << "���ӽ��׷������ɹ���" << endl;
}

void TdBo::OnFrontDisconnected()
{
	cout << "���ӽ��׷�����ʧ��!" << endl;
}

void TdBo::Login(char *Broker_Id, char *Investor_Id, char * password)
{
	cout << "���ڵ�½���׷�����" << endl;
	this->Broker_Id = Broker_Id;
	this->User_Id = Investor_Id;
	this->password = password;
	CThostFtdcReqUserLoginField * loginFiled = new CThostFtdcReqUserLoginField();
	strcpy(loginFiled->BrokerID,this->Broker_Id);
	strcpy(loginFiled->UserID, this->User_Id);
	strcpy(loginFiled->Password, this->password);
	int ret = this->pApi->ReqUserLogin(loginFiled, this->myreqId);
	this->myreqId += 1;
	if (ret != 0) 
	{
		cout << "��½���׷�������ʱ��" << endl;
	}
	else
	{
		cout << "��½���׷������ɹ���" << endl;
	}
}

void TdBo::ReqPrice(int *Volume)
{
	CThostFtdcInputOrderField *ord;
	memset(&ord, 0, sizeof(ord));
	strcpy(ord->BrokerID, this->Broker_Id);
	strcpy(ord->InvestorID,this->User_Id);
	strcpy(ord->InstrumentID, "cu1707");
	strcpy(ord->OrderRef, "");
	ord->Direction = THOST_FTDC_D_Buy;
	ord->CombOffsetFlag[0] = THOST_FTDC_OF_Open;
	ord->CombHedgeFlag[0] = THOST_FTDC_HF_Speculation;
	ord->VolumeTotalOriginal = * Volume;
	ord->ContingentCondition = THOST_FTDC_CC_Immediately;
	ord->VolumeCondition = THOST_FTDC_VC_AV;
	ord->MinVolume = 1;
	ord->ForceCloseReason = THOST_FTDC_FCC_NotForceClose;
	ord->IsAutoSuspend = 0;
	ord->UserForceClose = 0;
	ord->OrderPriceType = THOST_FTDC_OPT_AnyPrice;
	ord->LimitPrice = 0; // place 0 here for market order
	ord->TimeCondition = THOST_FTDC_TC_IOC; // �����ɽ�������
	int ret = this->pApi->ReqOrderInsert(ord, ++this->myreqId);
	if (ret == 0)
	{
		cout << "�����ɹ���" << endl;
	}
}

void TdBo::OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	this->VolumeUnTraded = 10;
}

void TdBo::OnRtnOrder(CThostFtdcOrderField *pOrder)
{
	this->VolumeTraded = pOrder->VolumeTraded;
	this->VolumeUnTraded = this->VolumeUnTraded + pOrder->VolumeTotal;
}

int TdBo::increaseVol()
{
	this->increaseVolume = this->VolumeUnTraded - this->VolumeTraded;
	return this->increaseVolume;
}


