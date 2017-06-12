#include <iostream>
#include "MdBo.h"
#include "ThostFtdcMdApi.h"
#include "ThostFtdcUserApiDataType.h"
#include "ThostFtdcUserApiStruct.h"
#include <vector>
#include <string.h>

using namespace std;
using std::vector;
using std::string;

MdBo::MdBo(CThostFtdcMdApi *mApi)
{
	this->reqId = 1;
	this->mApi = mApi;
}

void MdBo::Connect(char * Front_Addr)
{
	cout << "�����������������" << endl;
	this->mApi->RegisterSpi(this);
	this->mApi->RegisterFront(Front_Addr);
	this->mApi->Init();

}

void MdBo::OnFrontConnected()
{
	cout << "��������������ɹ���" << endl;
}

void MdBo::OnFrontDisconnected()
{
	cout << "���������������ʱ!" << endl;
}

void MdBo::Login(char *Broker_Id, char *User_Id, char * password)
{
	cout << "�������ڵ�½" << endl;
	this->Broker_Id = Broker_Id;
	this->User_Id = User_Id;
	this->password = password;
	CThostFtdcReqUserLoginField * loginFiled = new CThostFtdcReqUserLoginField();
	strcpy(loginFiled->BrokerID, this->Broker_Id);
	strcpy(loginFiled->UserID, this->User_Id);
	strcpy(loginFiled->Password, this->password);
	int ret = this->mApi->ReqUserLogin(loginFiled, this->reqId);
	this->reqId += 1;
	if (ret != 0)
	{
		cout << "��½�����������ʱ��" << endl;
	}
	else
	{
		cout << "��½����ɹ���" << endl;
	}
}

void MdBo::AskPrice(char * InsId[])
{
	int ret = (this->mApi->SubscribeMarketData(InsId, 1));
	if (ret == 0)
	{
		cout << "���鶩�ĳɹ���" << endl;
	}
	else
	{
		cout << "���鶩�ĳ�ʱ��" << endl;
	}
}

void MdBo::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData)
{
	this->price.push_back((float)pDepthMarketData->LastPrice);
}

bool MdBo::isTimeToBuy()
{
	float avg = (this->price.back() + this->price.at(this->price.size() - 2) + this->price.at(this->price.size() - 3) + this->price.at(this->price.size() - 4) + this->price.at(this->price.size() - 5)) / 5;
	if (avg >= this->price.back())
	{
		return false;
	}
	else
	{
		return true;
	}
}