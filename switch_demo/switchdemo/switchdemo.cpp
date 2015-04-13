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

// switchdemo.cpp : �������̨Ӧ�ó������ڵ㡣
//V20150306001

#include "stdafx.h"
#include "com_io_ctl.h"

using namespace std;
using namespace ns_com_io_ctl;


//�����л�ʱ�� 350ms
//���connect�ҳ������ߣ��������ӽ�����

int _tmain(int argc, _TCHAR* argv[])
{
	com_io_ctl *cic,cict;
	//do{
	//	com_io_ctl cicp;
	//	cic = new com_io_ctl();
	//	//cic = &cicp;
	//	//��������
	//	cic->LoadMap();				
	//	//��������ģ��
	//	cic->Connect();
	//	cic->DisConnect();
	//	delete cic;
	//}while(false);

	//cic = &cict;
	cic = new com_io_ctl();

	//��������
	if (!cic->LoadMap())
	{
		cout << "JcConfig.ini �����ڣ�" << endl;
	}	

	delete cic;

	cic = new com_io_ctl();

	//��������
	if (!cic->LoadMap())
	{
		cout << "JcConfig.ini �����ڣ�" << endl;
	}

CONNECT:

	//�������ã���ѡ���ĳ��IPģ�����
	//��ȡIP�б�
	//cout << "���ڻ�ȡ����������ģ��..." << endl;
	map<string,com_io_ctl::stHostControl> hosts;
	cic->GetHostsCtrl(hosts);

	//��ʾģ������״̬  stHostControl.isOnLine 
	//for (map<string, com_io_ctl::stHostControl>::iterator itr = hosts.begin();
	//	itr != hosts.end();
	//	itr++)
	//{
	//	cout << itr->second.name << " Online = " << (itr->second.isOnline ? "TRUE" : "FALSE") << endl;
	//}	

	cout << "ֱ�����������\"#\",������ģ��Ĭ�Ͻ��ܡ�������ͨ��700��800�������:700,800" << endl;

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

	//����ʹ��
	cic->SetHostsCtrl(hosts);

	//cic->Connect();
	//cic->DisConnect();

	//��������ģ��
	int conDuring = GetTickCount();
	bool resNet = cic->Connect(); //cic->Reset();
	cout << "Connect = " << GetTickCount() - conDuring << endl;
	cout << "��ǰ�������������Ƿ�ɹ�:"<<(resNet? "true":"false")<<endl;

	//����hosts
	cic->GetHostsCtrl(hosts);

	//��ӡ��������״̬
	for (map<string, com_io_ctl::stHostControl>::iterator itr = hosts.begin();
		itr != hosts.end();
		itr++)
	{
		cout << itr->second.name << " " << (itr->second.state ? "(true)" : "(false)") << endl;
	}

	//��δ�����ȼ���������ӣ��������´���
	//cic.DisConnect();
	//cout<<"RESET...."<<endl;   
	//cic.Reset(); //��λ����ģ��
	//Sleep(1500);	
	//cic.Connect();//��������ģ��
	//for(map<string,bool>::iterator itr = cic.__socketState.begin();
	//	itr != cic.__socketState.end();
	//	itr++)
	//{
	//	cout<<"("<<itr->first<<")"<<(itr->second?"(true)":"(false)")<<endl;//��ʾ��������״̬
	//}

	//����
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

	//��ȡ����ͨ���ַ�����
	vector<string> nltx1 = cic->GetTx1NameList();
	vector<string> nltx2 = cic->GetTx2NameList();
	vector<string> nlpim = cic->GetPimNameList();
	vector<string> nldet = cic->GetDetNameList();

	bool result;
	int index = 0;

	while(true)
	{
		//��ӡ�б�
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

		//�ȴ�����
		cout << "~:����ѹ������   r:��������   rt:���Ӳ���" << endl;
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

			cout << "������Ͽ�������ʱ����λ���룡" << endl << ">";

			cin >> cycDelay;

			cic->DisConnect();

			int errCntt = 0,errDelay1=-1,errDelay2=-1;
			bool cntReslut;
			int reConnetDelay=0, reConnetDelayBak=0;
			int cetAvg = 0, setAvg = 0;

			reConnetDelay = GetTickCount();

			for (size_t j = 0; j < 100; j++)
			{			
				Sleep(atoi(cycDelay.c_str()));//����ȴ�ȫ���ͷ����

				cntReslut = cic->Connect();

				reConnetDelay = GetTickCount() - reConnetDelay;

				if (abs(reConnetDelayBak - reConnetDelay) > 300)errDelay1++;

				reConnetDelayBak = reConnetDelay;

				if (!cntReslut)errCntt++;

				cout << "==>(" << reConnetDelay << ")����:" << (cntReslut ? "�ɹ�" : "ʧ��") << "  Cnt = " << j << " ERR = "<< errCntt;
				cout << "  ���Ӳ�ƽ�� = " << errDelay1;
				cout << "  ���ò�ƽ�� = " << errDelay2 <<endl;
				cout << "  ����ƽ����ʱ =  " << (cetAvg += reConnetDelayBak) / (j + 1);
				if (j == 0)
					cout << endl;
				else
					cout << " ms ����ƽ����ʱ =  " << setAvg / (14*j) <<" ms"<< endl;

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

		//�������ؾ���
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
		//��ӡ�������
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

	//�����ٶ���ǰӦ�ȶϿ�����TCP����
	cic->DisConnect();	

	delete cic;

	return 0;
}

