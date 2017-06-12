#include <iostream>
#include "ThostFtdcMdApi.h"
#include "ThostFtdcTraderApi.h"
#include "ThostFtdcUserApiDataType.h"
#include "ThostFtdcUserApiStruct.h"
#include "TdBo.h"
#include "MdBo.h"
#include <time.h>
#include <vector>
#include <string.h>
#include <Windows.h>

using namespace std;
using std::string;
using std::vector;
CThostFtdcTraderApi *pApi;
CThostFtdcMdApi *mApi;



void main()
{
	///����ǰ�õ�ַ��������ID���û�ID������
	string front_add = "tcp://127.0.0.1";
	string broker_id = "";
	string user_id = "";
	string investor_id = "";
	string password = "";
	int Vol = 1000;
	int times = 100;
	int EveryVol = 10;
	vector <float *> price;
	pApi = CThostFtdcTraderApi::CreateFtdcTraderApi("./conn/");
	mApi = CThostFtdcMdApi::CreateFtdcMdApi("./conn/");
	TdBo *pSpi = new TdBo(pApi);
	MdBo *mSpi = new MdBo(mApi);
	

	///���ӵ�������
	pSpi->Connect((char *)front_add.c_str());
	mSpi->Connect((char *)front_add.c_str());

	///��½��������
	pSpi->Login((char*)broker_id.c_str(), (char *)investor_id.c_str(), (char *)password.c_str());
	mSpi->Login((char*)broker_id.c_str(), (char *)user_id.c_str(), (char *)password.c_str());
	
	cout << "���ڻ�ȡ���飬��Ҫ��ʮ��Ļ��壬���Ժ�..." << endl;
	Sleep(300000);
	
	///ѯ�۲��ڹ涨ʱ�����Թ涨�����µ�
	while (1)
	{
		time_t now = time(0);
		tm *timer = localtime(&now);
		if (timer->tm_hour >= 10 & timer->tm_hour < 14 & mSpi->isTimeToBuy())
		{
			pSpi->ReqPrice(&EveryVol);
			//15��ͣ��Ϊ�˱����ɽ����Լ�ʵ��TWAP��ʽ��1000��
			Sleep(15000);
			Vol += pSpi->increaseVolume;
			if (pSpi->increaseVolume != -10)
			{
				EveryVol = Vol / times;
			}
			else
			{
				times -= 1;
			}
		}
		
	}

}