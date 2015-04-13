/*******************************Copyright (c)***********************************
*
*              Copyright (C), 1999-2015, Jointcom . Co., Ltd.
*
*------------------------------------------------------------------------------
* @file	:
* @author	:mashuai
* @version	:v2.0
* @date		:2015.3.1
* @brief	:
*------------------------------------------------------------------------------*/

// switchdemo.cpp : 定义控制台应用程序的入口点。
//V20150306001

#include "stdafx.h"
#include "com_io_ctl.h"

using namespace std;
using namespace ns_com_io_ctl;


//开关切换时间 350ms
//如果connect找出不在线，后续连接将屏蔽

int _tmain(int argc, _TCHAR* argv[])
{
	com_io_ctl *cic,cict;
	//do{
	//	com_io_ctl cicp;
	//	cic = new com_io_ctl();
	//	//cic = &cicp;
	//	//加载配置
	//	cic->LoadMap();				
	//	//连接所有模块
	//	cic->Connect();
	//	cic->DisConnect();
	//	delete cic;
	//}while(false);

	//cic = &cict;
	cic = new com_io_ctl();

	//加载配置
	if (!cic->LoadMap())
	{
		cout << "JcConfig.ini 不存在！" << endl;
	}	

	delete cic;

	cic = new com_io_ctl();

	//加载配置
	if (!cic->LoadMap())
	{
		cout << "JcConfig.ini 不存在！" << endl;
	}

CONNECT:

	//开关配置（可选项）将某个IP模块禁能
	//读取IP列表
	//cout << "正在获取开关箱在线模块..." << endl;
	map<string,com_io_ctl::stHostControl> hosts;
	cic->GetHostsCtrl(hosts);

	//显示模块在线状态  stHostControl.isOnLine 
	//for (map<string, com_io_ctl::stHostControl>::iterator itr = hosts.begin();
	//	itr != hosts.end();
	//	itr++)
	//{
	//	cout << itr->second.name << " Online = " << (itr->second.isOnline ? "TRUE" : "FALSE") << endl;
	//}	

	cout << "直接连接请键入\"#\",不在线模块默认禁能。若禁能通道700和800，请键入:700,800" << endl;

	string key;

	cin >> key;

	if (key != "#")
	{
		 vector<string> chanName = implementsetting::split(key, ",");

		 for (vector<string>::iterator itr = chanName.begin();
			 itr != chanName.end();
			 itr++
		 )
		 {
			 hosts[*itr].enable = false;
		 }
	}

	vector<string> moduleList = cic->GetModuleList();

	//hosts["700"].enable = false;	hosts[moduleList[0]].enable = false;
	//hosts["800"].enable = false;	//hosts[moduleList[1]].enable = false;
	//hosts["900"].enable = false;	//hosts[moduleList[2]].enable = false;
	//hosts["1800"].enable = false;	//hosts[moduleList[3]].enable = false;
	//hosts["1900"].enable = false;	//hosts[moduleList[4]].enable = false;
	//hosts["2100"].enable = false;	//hosts[moduleList[5]].enable = false;
	//hosts["2600"].enable = false;	//hosts[moduleList[6]].enable = false;
	//hosts["Signalswich"].enable = false;
	//hosts["Paspecumpwmt"].enable = false;

	for(map<string,com_io_ctl::stHostControl>::iterator itr = hosts.begin();
		itr != hosts.end();
		itr++)
	{
		cout<<itr->second.name<<"@"<<itr->second.ip<<"<"<<itr->second.enable<<">"<<endl;
	}

	//设置使能
	cic->SetHostsCtrl(hosts);

	//cic->Connect();
	//cic->DisConnect();

	//连接所有模块
	int conDuring = GetTickCount();
	bool resNet = cic->Connect(); //cic->Reset();
	cout << "Connect = " << GetTickCount() - conDuring << endl;
	cout << "当前网络配置连接是否成功:"<<(resNet? "true":"false")<<endl;

	//更新hosts
	cic->GetHostsCtrl(hosts);

	//打印网络连接状态
	for (map<string, com_io_ctl::stHostControl>::iterator itr = hosts.begin();
		itr != hosts.end();
		itr++)
	{
		cout << itr->second.name << " " << (itr->second.state ? "(true)" : "(false)") << endl;
	}

	//有未连接先检查网络连接，再做以下处理
	//cic.DisConnect();
	//cout<<"RESET...."<<endl;   
	//cic.Reset(); //复位所有模块
	//Sleep(1500);	
	//cic.Connect();//连接所有模块
	//for(map<string,bool>::iterator itr = cic.__socketState.begin();
	//	itr != cic.__socketState.end();
	//	itr++)
	//{
	//	cout<<"("<<itr->first<<")"<<(itr->second?"(true)":"(false)")<<endl;//显示网络连接状态
	//}

	//变量
	string	strA,
			strB,
			strC,
			strD;	

	vector<string>::iterator	itA,
								itB,
								itC,
								itD;

	string	chan1,
			chan2,
			chan3,
			chan4;

	//获取所有通道字符串名
	vector<string> nltx1 = cic->GetTx1NameList();
	vector<string> nltx2 = cic->GetTx2NameList();
	vector<string> nlpim = cic->GetPimNameList();
	vector<string> nldet = cic->GetDetNameList();

	bool result;
	int index = 0;

	while(true)
	{
		//打印列表
		index = 0;

		cout<<"[TX1]\t\t[TX2]\t\t[PIM]\t\t[Det]"<<endl;
		itA = cic->GetTx1NameList().begin();
		itB = cic->GetTx2NameList().begin(); 
		itC = cic->GetPimNameList().begin();
		itD = cic->GetDetNameList().begin(); 

		while(
			itA != cic->GetTx1NameList().end() ||  
			itB != cic->GetTx2NameList().end() ||
			itC != cic->GetPimNameList().end() ||
			itD != cic->GetDetNameList().end() 
			)
		{						
			if( itA != cic->GetTx1NameList().end() )
			{
				cout<<dec<<index<<" : "<<*itA++<<"\t";
			}
			else
				cout<<"\t\t";

			if( itB != cic->GetTx2NameList().end() )
			{
				cout<<dec<<index<<" : "<<*itB++<<"\t";
			}
			else
				cout<<"\t\t";

			if( itC != cic->GetPimNameList().end() )
			{
				cout<<dec<<index<<" : "<<*itC++<<"\t";
			}
			else
				cout<<"\t\t";
			
			if( itD != cic->GetDetNameList().end() )
			{
				cout<<dec<<index<<" : "<<*itD++;
			}
			index++;
			cout<<endl;
		}

		//等待输入
		cout << "~:进入压力测试   r:重新连接   rt:连接测试" << endl;
		cout<<">";
		cin>>strA;

		if (strA == "~")break;
		else if (strA == "r")
		{
			system("CLS");
			cic->DisConnect();
			//delete cic;
			goto CONNECT;
		}
		else if (strA == "rt")
		{
			system("CLS");

			string cycDelay;

			cout << "请输入断开重连延时，单位毫秒！" << endl << ">";

			cin >> cycDelay;

			cic->DisConnect();

			int errCntt = 0,errDelay1=-1,errDelay2=-1;
			bool cntReslut;
			int reConnetDelay=0, reConnetDelayBak=0;
			int cetAvg = 0, setAvg = 0;

			reConnetDelay = GetTickCount();

			for (size_t j = 0; j < 100; j++)
			{			
				Sleep(atoi(cycDelay.c_str()));//必须等待全部释放完成

				cntReslut = cic->Connect();

				reConnetDelay = GetTickCount() - reConnetDelay;

				if (abs(reConnetDelayBak - reConnetDelay) > 300)errDelay1++;

				reConnetDelayBak = reConnetDelay;

				if (!cntReslut)errCntt++;

				cout << "==>(" << reConnetDelay << ")连接:" << (cntReslut ? "成功" : "失败") << "  Cnt = " << j << " ERR = "<< errCntt;
				cout << "  连接不平滑 = " << errDelay1;
				cout << "  设置不平滑 = " << errDelay2 <<endl;
				cout << "  重连平均耗时 =  " << (cetAvg += reConnetDelayBak) / (j + 1);
				if (j == 0)
					cout << endl;
				else
					cout << " ms 设置平均耗时 =  " << setAvg / (14*j) <<" ms"<< endl;

				int singleDelay=0,singleDelayBak=0;

				for (size_t k = 0; k < 14; k++)
				{
					singleDelay = GetTickCount();

					cic->Clear();
					cic->SelChanTx1(nltx1[k]);
					cic->SelChanTx2(nltx2[k]);
					cic->SelChanPim(nlpim[k]);
					cic->SelChanDet(nldet[k]);
					cntReslut = cic->Excute();

					singleDelay = GetTickCount() - singleDelay;

					setAvg += singleDelay;

					if (abs(singleDelay - singleDelayBak) > 50)errDelay2++;

					singleDelayBak = singleDelay;

					cout << "<" << singleDelay << ">Switch = " << k << (cntReslut ? " = true " : " = false ") << endl;
				}

				cout << "Disconnect" << endl;

				reConnetDelay = GetTickCount();

				cic->DisConnect();

				delete cic;

				cic = new com_io_ctl();

				cic->LoadMap();				
			}

			break;			
		}

		cin>>strB;
		cin>>strC;
		cin>>strD;

		int swDuring = GetTickCount();

		//操作开关矩阵
		cic->Clear();
		if( strA != "*" )
		{
			chan1 = nltx1[ atoi(strA.c_str()) ];
			cic->SelChanTx1(chan1);
		}

		if( strB != "*" )
		{
			chan2 = nltx2[ atoi(strB.c_str()) ];
			cic->SelChanTx2(chan2);
		}

		if( strC != "*" )
		{
			chan3 = nlpim[ atoi(strC.c_str()) ];
			cic->SelChanPim(chan3);
		}

		if( strD != "*" )
		{
			chan4 = nldet[ atoi(strD.c_str()) ];
			cic->SelChanDet(chan4);
		}

		//int swDuring = GetTickCount();
		result = cic->Excute();
		cout << "Switch During = " << GetTickCount() - swDuring << endl;
		//打印操作结果
		cout<<(result?"Success!":"Failed!")<<endl;
		cin>>strC;

		//cic->DisConnect();
		cout << "Dis" << endl;

		system("CLS");
	}	

	cout << "InputDelay:" << endl;

	string delay;

	cin >> delay;

	int errCnt = 0;
	bool concResult;

	for (size_t i = 0; i < 1000; i++)
	{
		for (size_t j = 0; j < 14; j++)
		{
			int swDuring = GetTickCount();

			cic->Clear();
			cic->SelChanTx1(nltx1[j]);
			cic->SelChanTx2(nltx2[j]);
			cic->SelChanDet(nldet[j]);
			cic->SelChanPim(nlpim[j]);

			if (i == 13 && j == 13)
			{
				cout << 1 << endl;
			}

			concResult = cic->Excute();

			if (!concResult)errCnt++;

			cout << "==> " << i << ":" << j << ":" << (concResult ? "true" : "false");
			cout << "  Switch During = " << GetTickCount() - swDuring << " ms";
			cout << " ERR: " << errCnt << endl;

			Sleep(atoi(delay.c_str()));
		}
	}

	//在消毁对象前应先断开所有TCP链接
	cic->DisConnect();	

	delete cic;

	return 0;
}

