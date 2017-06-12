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
	///填入前置地址、代理商ID、用户ID及密码
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
	

	///连接到服务器
	pSpi->Connect((char *)front_add.c_str());
	mSpi->Connect((char *)front_add.c_str());

	///登陆到服务器
	pSpi->Login((char*)broker_id.c_str(), (char *)investor_id.c_str(), (char *)password.c_str());
	mSpi->Login((char*)broker_id.c_str(), (char *)user_id.c_str(), (char *)password.c_str());
	
	cout << "正在获取行情，需要三十秒的缓冲，请稍后..." << endl;
	Sleep(300000);
	
	///询价并在规定时间内以规定规则下单
	while (1)
	{
		time_t now = time(0);
		tm *timer = localtime(&now);
		if (timer->tm_hour >= 10 & timer->tm_hour < 14 & mSpi->isTimeToBuy())
		{
			pSpi->ReqPrice(&EveryVol);
			//15秒停顿为了报单成交，以及实现TWAP方式开1000手
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