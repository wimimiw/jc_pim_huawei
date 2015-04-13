/*******************************Copyright (c)***********************************
*
*              Copyright (C), 1999-2015, Jointcom . Co., Ltd.
*
*------------------------------------------------------------------------------
* @file	:	implementsetting.h
* @author	:mashuai
* @version	:v2.0
* @date		:2015.3.1
* @brief	:
2015.3.6
�Ľ����ݣ�1���첽���ӣ�������ĳЩģ�鲻���߶������ͬ��������ʱʱ��ĵ��ӡ�
2�������ӣ�����쳣ģ�飬���Ը�λģ�鲢��������
3�������������������в����κ���ʱ

�������⣺���������У�Ӳ�����쳣���ߣ����������·���ڣ�ż���޷���λģ�顣����취
���ε���DisConnect��Connet������
2015.3.20
�޸����ݣ�
1������ʱ�첽���ӵ�һ̨�����ó�ʱ�ȴ���Ȼ��ÿ̨�ֱ�ʱ�ȴ�500ms,�8��
�����в����ߣ�
2���������������صĿ���ʹ��
*------------------------------------------------------------------------------*/

#ifndef __IMPLEMENT_H
#define __IMPLEMENT_H

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <memory>
#include <bitset>
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <map>
#include <regex>
#include "switch_info.h"
//#include <Windows.h>

namespace ns_com_io_ctl
{
	using  namespace std;
//#define __DEBUG_PRINT
#define	ACTION_MESSAGE_REPORT    (0)   //1:enable    0:disable

	class implementsetting
	{
	public:
		typedef struct stHostControl
		{
			string name;
			string ip;
			bool enable;
			bool state;
			bool isOnline;		//�Ƿ�����
		};
	private:
		typedef struct iniFunc
		{
			string swName;
			string ip;
			int swIdx;		
		};

		typedef vector<iniFunc> rowRun;

		typedef struct iniSwitch
		{
			string name;
			map<string,int>io;
		};

		typedef map<string,rowRun> actionMapDef;	

		typedef struct actionCellc
		{
			vector<string> namelist;
			actionMapDef actionMap;	
		};	
		map<string,string> __ipmap;		
		unsigned short __ipGpioBakArray[100][5];
		map<string,unsigned short*> __ipGpioBak;
		//����ӳ��
		vector<string> __switchNameList;
		map<string,iniSwitch> __switchMap;	
		//ȫ�������б�
		actionCellc  __actionCellc[4],
						   *__ac_tx1,
						   *__ac_tx2,
						   *__ac_pim,
						   *__ac_det;
		//ioӳ��
		map<string, vector<string>>__ioInfoMap;
		//���������б�
		map<string,unsigned short*>__actionList;
		//ģ���б�
		vector<string> __moduleList;
		bool bLoadMap = false;
	protected:
		bool __logEnable = false;
		string __ioPath,__imPath,__cfgPath,__runPath;
		map<string, stHostControl> __hostCtrl;		
	public:
		//���캯��
		implementsetting(void)
		{
			//virtual table not build,do not call the virtual function
			__ac_tx1 = &__actionCellc[0];
			__ac_tx2 = &__actionCellc[1];
			__ac_pim = &__actionCellc[2];
			__ac_det = &__actionCellc[3];
		}
		//��������
		virtual ~implementsetting(void)
		{
			//������������ʼ����ʱ�����麯����ָ������麯����
			//������캯��ʱδ�����麯���������������
			//DisConnect();
		}
	//��̬����
	public:
		//�ַ����滻
		static void StringReplace(string &strBase,const string&strSrc,const string&strDes)
		{
			string::size_type pos = 0;
			string::size_type srcLen = strSrc.size();
			string::size_type desLen = strDes.size();
			pos = strBase.find(strSrc, pos);
			while ((pos != std::string::npos))
			{
				strBase.replace(pos, srcLen, strDes);
				pos = strBase.find(strSrc, (pos + desLen));
			}
		}
		//�ַ����ָ�
		static vector<string>split(string str, const string&pattern)
		{
			string::size_type pos = 0;
			vector<string> result;
			str += pattern;//��չ�ַ����Է������   
			int size = (int)str.size();

			for (int i = 0; i<size; i++)
			{
				pos = str.find(pattern, i);
				if (pos<(string::size_type)size)
				{
					string s = str.substr(i, pos - i);
					result.push_back(s);
					i = (int)(pos + pattern.size() - 1);
				}
			}

			return result;
		}
	public:
		//����ӳ���
		bool LoadMap(void)
		{
			bool result = true;
			string iopath = GetRunPath();
			string impath(iopath.c_str());
			string cfgpath(iopath.c_str());

			cfgpath = cfgpath.substr(0, cfgpath.rfind('\\'));

			__runPath.assign(cfgpath);

			iopath.assign(GetTempFileInfo("~io"));
			impath.assign(GetTempFileInfo("~im"));

			cfgpath.append("\\JcConfig.ini");

			__ioPath = iopath;
			__imPath = impath;
			__cfgPath = cfgpath;

			ofstream ofio(iopath);
			ofstream ofimplt(impath);

			string fstr;

			fstr.assign(IO_STRING);
			ofio.write(fstr.c_str(), fstr.size());
			fstr.assign(IMPLEMENT_STRING);
			ofimplt.write(fstr.c_str(), fstr.size());

			ofio.close();
			ofimplt.close();

			if (LoadParaIM() == false)
			{
				result = false;
			}
			else
			{
				LoadParaIO();
			}

			__logEnable = (0 != atoi(GetRowFromFile("ip", "log", "0", __cfgPath).c_str()));

			WindowsDeleteFile(iopath.c_str());
			WindowsDeleteFile(impath.c_str());

			bLoadMap = result;

			return result;
		}
		//��ȡ����������Ϣ
		void GetHostsCtrl(map<string, stHostControl>&host)
		{
			string ip;

			for (map<string, stHostControl>::iterator itr = __hostCtrl.begin();
				itr != __hostCtrl.end();
				itr++)
			{
				ip = split(itr->second.ip, ":")[0];
			}

			host = __hostCtrl;
		}
		//��������������Ϣ
		//�����������������ʹ������(�ź�Դ���أ���⿪����)
		void SetHostsCtrl(const map<string, stHostControl>&host, bool bSignal, bool bDetect)
		{
			__hostCtrl = host;
			__hostCtrl["Signalswich"].enable = bSignal;
			__hostCtrl["Paspecumpwmt"].enable = bDetect;
		}
		//��ȡTX1�����б�
		vector<string>&GetTx1NameList(void)
		{
			return __ac_tx1->namelist;
		}
		//��ȡTX2�����б�
		vector<string>&GetTx2NameList(void)
		{
			return __ac_tx2->namelist;
		}
		//��ȡPIM�����б�
		vector<string>&GetPimNameList(void)
		{
			return __ac_pim->namelist;
		}
		//��ȡDet�����б�
		vector<string>&GetDetNameList(void)
		{
			return __ac_det->namelist;
		}
		//��ȡģ���б�
		vector<string>&GetModuleList(void)
		{
			list<int> listTmp;
			int flag = 0;
			char str[10] = { 0 };

			__moduleList.clear();

			for (map<string, stHostControl>::iterator itr = __hostCtrl.begin();
				itr != __hostCtrl.end();
				itr++)
			{
				flag = atoi(itr->first.c_str());

				if (flag != 0)
					listTmp.push_front(flag);
			}

			listTmp.sort();

			for (list<int>::iterator itr = listTmp.begin();
				itr != listTmp.end();
				itr++
				)
			{
				_itoa_s(*itr, str, 10);
				__moduleList.push_back(str);
			}

			return __moduleList;
		}
		//ѡ��ͨ��TX1
		void SelChanTx1(const string&chan)
		{
			SelChan(__ac_tx1->actionMap[chan]);
		}
		//ѡ��ͨ��TX2
		void SelChanTx2(const string&chan)
		{
			SelChan(__ac_tx2->actionMap[chan]);
		}
		//ѡ��ͨ��PIM
		void SelChanPim(const string&chan)
		{
			SelChan(__ac_pim->actionMap[chan]);
		}
		//ѡ��ͨ��DET
		void SelChanDet(const string&chan)
		{
			SelChan(__ac_det->actionMap[chan]);
		}
		//����
		bool Connect(void)
		{
			if (!bLoadMap)
			{
				if (ACTION_MESSAGE_REPORT == 1)
					Message("SWITCH::Connet failed::load map failed!");
				return false;
			}

			bool result = true;
			regex pattern("\\d{1,4}");
			smatch mat;
			map<string, bool>hostMap;

			for (map<string, string>::iterator hostIter = __ipmap.begin();
				hostIter != __ipmap.end();
				hostIter++)
			{
				regex_search(hostIter->first, mat, pattern);

				string strTemp(mat[0].str());

				if (strTemp != "")
				{
					__hostCtrl[strTemp].state = __hostCtrl[strTemp].enable;
				}
				else
				{
					strTemp = hostIter->first;
				}

				if (!__hostCtrl[strTemp].enable)continue;

				hostMap[hostIter->second] = true;
			}

			IOConnectAsyc(hostMap);

			return true;// && hasHost;
		}
		//�Ͽ�
		void DisConnect(void)
		{
			if (!bLoadMap)return;

			for (map<string, stHostControl>::iterator itr = __hostCtrl.begin();
				itr != __hostCtrl.end();
				itr++)
			{
				if (itr->second.enable)
				{
					IODisConnect(itr->second.ip);
				}
			}
		}
		//ִ�ж���
		bool Excute(void)
		{
			if (!bLoadMap)
			{
				if (ACTION_MESSAGE_REPORT == 1)
					Message("SWITCH::Excute failed::load map failed!");
				return false;
			}

			bool funcResult = true;
			unsigned char txBuf[12] = { 0 }, rxBuf[12] = { 0 };
			unsigned char checkValue = 0;
			unsigned short *gpioBak = NULL;
			string ip;
			int replyCnt = 0; //���Դ���
			map<string, bool>hostIPEnableList;
			vector<string> actionQueue;

			txBuf[0] = 'W';

			//��������ʹ�ܶ���
			for (map<string, stHostControl>::iterator itr = __hostCtrl.begin();
				itr != __hostCtrl.end();
				itr++)
			{
				hostIPEnableList[itr->second.ip] = itr->second.enable;
			}

			for (map<string, unsigned short*>::iterator actionIter = __actionList.begin();
				actionIter != __actionList.end();
				actionIter++)
			{
				if (!hostIPEnableList[actionIter->first])continue;
				actionQueue.push_back(actionIter->first);
			}

			replyCnt = 0;

			while (true)
			{
				//�·�����ָ�����
				for (map<string, unsigned short*>::iterator actionIter = __actionList.begin();
					actionIter != __actionList.end();
					actionIter++)
				{
					ip = actionIter->first;
					gpioBak = actionIter->second;

					if (!hostIPEnableList[ip])continue;

					checkValue = 0;
					for (int i = 1, j = 0; i < 11; j++)
					{
						txBuf[i] = gpioBak[j] % 256;
						checkValue ^= txBuf[i];
						i++;
						txBuf[i] = gpioBak[j] / 256;
						checkValue ^= txBuf[i];
						i++;
					}

					txBuf[11] = checkValue;

#ifdef __DEBUG_PRINT
					cout << "<" << ip << ">";
					for (int i = 0; i<12; i++)
					{
						cout << uppercase << hex << static_cast<int>(txBuf[i]) << " ";
					}
					cout << endl;
#endif

					bool wrResult = false;
					int len = 12;

					for (int i = 0; i < 1; i++)
					{
						funcResult = wrResult = IOWrite(ip, (char*)txBuf, sizeof(txBuf));

						if (wrResult == false)break;

						funcResult = wrResult = IORead(ip, (char*)rxBuf, &len);

						if (wrResult == false)break;

						for (int j = 0; j < sizeof(txBuf); j++)
						{
							if (rxBuf[j] != txBuf[j])
							{
								wrResult = false; break;
							}
						}

						funcResult = wrResult;
						if (wrResult == true)break;
					}

					if (!funcResult)break;
				}

				if (replyCnt > 1 || funcResult)break;

				replyCnt++;

				//�Ͽ�����
				for (vector<string>::iterator itr = actionQueue.begin();
					itr != actionQueue.end();
					itr++)
				{
					IODisConnect(*itr);
				}

				//��λ
				funcResult = IOResetWithList(actionQueue);

				//����
				for (vector<string>::iterator itr = actionQueue.begin();
					itr != actionQueue.end();
					itr++)
				{
					IOConnectBegin(*itr);
				}

				bool wait = true;
				funcResult = true;

				for (vector<string>::iterator itr = actionQueue.begin();
					itr != actionQueue.end();
					itr++)
				{
					if (!IOConnectEnd(*itr, wait ? 1000 : 100))
					{
						funcResult = false;
					}
					wait = false;
					//if (!funcResult)break;
					//LoadModuleState(*itr);
				}

				if (!funcResult)
				{
					if (ACTION_MESSAGE_REPORT == 1)
					{
						string info("SWITCH::Excute::IP(");

						for (vector<string>::iterator itr = actionQueue.begin();
							itr != actionQueue.end();
							itr++)
						{
							info.append(itr->c_str());
							info.append("/");
						}

						info.append(")::Failed after reset");
						Message(info);
					}

					break;
				}

				Delay(500);
			}

			return funcResult;
		}
		//��������б�
		void Clear(void)
		{
			__actionList.clear();
		}
	private:
		//��ȡ�����б�
		vector<string>GetNameList(const string&strBase)
		{
			string tmpStr(strBase);
			vector<string> nameVector;
			nameVector.clear();
			StringReplace(tmpStr," ", "");
			nameVector = split(tmpStr, ",");
			//���þ��Ƕ���ı���
			return nameVector;
		}
		//ѡ��ͨ��
		void SelChan(rowRun&rr)
		{
			for (rowRun::iterator swList = rr.begin();
				swList != rr.end();
				swList++)
			{
				AddActionList(swList->ip, swList->swName, swList->swIdx);
			}
		}
		//��Ӷ����б�
		void AddActionList(const string&ip, const string&sw, int chan)
		{
			string str;
			vector<string>gpioValueStr;
			unsigned short *gpioBak = __ipGpioBak[ip],
				port[5] = { 0 };

			for (auto itr = __ioInfoMap[sw].begin();
				itr != __ioInfoMap[sw].end();
				itr++)
			{
				gpioValueStr = split(*itr, ",");
				for (int i = 0; i<sizeof(port) / sizeof(short); i++)
				{
					port[i] |= atoi(gpioValueStr[i].c_str());
				}
			}

			str = __ioInfoMap[sw][chan - 1];
			gpioValueStr = split(str, ",");

			for (int i = 0; i<sizeof(port) / sizeof(short); i++)
			{
				gpioBak[i] &= ~port[i];
				gpioBak[i] |= atoi(gpioValueStr[i].c_str());
			}

			__actionList[ip] = gpioBak;
		}
		//����IM����
		bool LoadParaIM(void)
		{
			string strValue;
			vector<string> ipNameList;
			//ip
			ipNameList = GetSecKeyFromFile("ip",__imPath);

			for (int i = 0; i<(int)ipNameList.size(); i++)
			{
				__ipmap[ipNameList[i]] = GetRowFromIMFile("ip", ipNameList[i], "");
				strValue = GetRowFromCfgFile("ip", ipNameList[i], "");
				if (strValue != "")
				{
					__ipmap[ipNameList[i]] = strValue;
				}
				else
				{
					return false;
				}
				__ipGpioBak[__ipmap[ipNameList[i]]] = __ipGpioBakArray[i];
			}

			//switch
			__switchNameList = GetNameList(GetRowFromIMFile("switch","namelist", ""));

			for (int i = 0; i<(int)__switchNameList.size(); i++)
			{
				iniSwitch is;
				is.name = __switchNameList[i];
				vector<string>&temp = GetNameList(GetRowFromIMFile("switch", __switchNameList[i], ""));
				for (int j = 0; j<(int)temp.size(); j++)
				{
					string&index = GetRowFromIMFile("switch", temp[j], "0");
					is.io[temp[j]] = atol(index.c_str());
				}
				__switchMap[__switchNameList[i]] = is;
			}

			//ACTION
			LoadActionList("actiontx1", *__ac_tx1);
			LoadActionList("actiontx2", *__ac_tx2);
			LoadActionList("actionpim", *__ac_pim);
			LoadActionList("actiondet", *__ac_det);

			const regex pattern("\\d{1,4}");
			smatch mat;
			stHostControl stHC;

			for (map<string, string>::iterator itr = __ipmap.begin();
				itr != __ipmap.end();
				itr++)
			{
				stHC.enable = true;
				stHC.name = itr->first;
				stHC.ip = itr->second;
				regex_search(itr->first, mat, pattern);
				//__hostCtrl.push_back(stHC);
				if (mat[0].str() != "")
					__hostCtrl[mat[0].str()] = stHC;
				else
					__hostCtrl[stHC.name] = stHC;
			}

			for (map<string, unsigned short*> ::iterator it = __ipGpioBak.begin();
				it != __ipGpioBak.end();
				it++
				)
			{
				memset((void*)it->second, 0, 10);
			}

			return true;
		}
		//����IO����
		bool LoadParaIO(void)
		{
			string strBuff;
			char pBuf[10] = { 0 };

			for (vector<string>::iterator swName = __switchNameList.begin();
				swName != __switchNameList.end();
				swName++)
			{
				for (int i = 0, j = 0; i<100; i++)
				{
					_itoa_s(i, pBuf, 10);
					strBuff = GetRowFromIOFile(*swName, pBuf, "");
					if (strBuff != "")
					{
						__ioInfoMap[*swName].push_back(strBuff);
						j++;
						if (j >= (int)__switchMap[*swName].io.size())break;
					}
				}
			}

			return true;
		}
		//��ȡ�к����б�
		void GetRowRunFunc(string str, rowRun&rr)
		{
			StringReplace(str, " ", "");
			vector<string>&temp = split(str, "),");

			iniFunc ifc;
			string buff;

			for (int j = 0; j<(int)temp.size(); j++)
			{
				buff = split(temp[j], "(")[1];
				StringReplace(buff, ")", "");
				vector<string>&parav = split(buff, ",");

				ifc.swName = split(temp[j], "(")[0];
				ifc.ip = __ipmap[parav[0]];
				ifc.swIdx = __switchMap[ifc.swName].io[parav[1]];
				rr.push_back(ifc);
			}
		}
		//����IO����
		void LoadActionList(const string&section, actionCellc&ac)
		{
			ac.namelist = GetSecKeyFromFile(section,__imPath);

			for (int i = 0; i<(int)ac.namelist.size(); i++)
			{
				string&funcStr = GetRowFromIMFile(section, ac.namelist[i], "");
				rowRun rr;
				GetRowRunFunc(funcStr, rr);
				ac.actionMap[ac.namelist[i]] = rr;
			}
		}
		//����ģ����Ϣ
		void LoadModuleState(const string&host)
		{
			unsigned char txBuf[12] = { 0 }, rxBuf[12] = { 0 };
			unsigned char checkValue = 0;
			unsigned short *gpioBak = NULL;
			int len = 0;

			gpioBak = __ipGpioBak[host];

			txBuf[0] = 'R';

			for (int i = 1; i<11; i++)
			{
				checkValue ^= txBuf[i];
			}

			txBuf[11] = checkValue;

			IOWrite(host, (char*)txBuf, (int)sizeof(txBuf));
			len = (int)sizeof(txBuf);
			IORead(host, (char*)rxBuf, &len);

			if (rxBuf[0] != 'R')return;

			checkValue = 0;

			for (int i = 1; i<11; i++)
			{
				checkValue ^= rxBuf[i];
			}

			//if(checkValue != rxBuf[11])return;//�˴���Ҫ����

			for (int i = 1, j = 0; i<11; j++)
			{
				gpioBak[j] = rxBuf[i];
				i++;
				gpioBak[j] += rxBuf[i] * 256;
				i++;
			}
		}
		//���������ļ�
		string GetRowFromCfgFile(const string&section, const string&key, const string&defaultValue)
		{
			return GetRowFromFile(section, key, defaultValue, __cfgPath);
		}
		//����IM�ļ�
		string GetRowFromIMFile(const string&section, const string&key, const string&defaultValue)
		{
			return GetRowFromFile(section, key, defaultValue, __imPath);
		}
		//����IO�ļ�
		string GetRowFromIOFile(const string&section, const string&key, const string&defaultValue)
		{
			return GetRowFromFile(section, key, defaultValue, __ioPath);
		}
	protected:
		virtual string GetRunPath()const = 0;
		virtual string GetRowFromFile(const string&section, const string&key, const string&defaultValue, const string&fileName) = 0;
		virtual vector<string> GetSecKeyFromFile(const string&section, const string&fileName) = 0;
		virtual string GetTempFileInfo(const string&flagName)const = 0;
		virtual void Delay(int mil) = 0;
		virtual bool IOConnect(const string&host) = 0;
		virtual bool IODisConnect(const string&host) = 0;
		virtual bool IOWrite(const string&host, const char*buf, int len) = 0;
		virtual bool IORead(const string&host, char*buf, int*len) = 0;
		virtual void WindowsDeleteFile(const char* file) = 0;
		virtual bool ResetOne(const string&host) = 0;
		virtual void Message(const string&info) = 0;
		virtual bool IOConnectBegin(const string&host) = 0;
		virtual bool IOConnectEnd(const string&host,int timeout) = 0;
		virtual bool IOConnectAsyc(map<string, bool>&host) = 0;
		virtual bool IOSocketIsActive(const string&host) = 0;
		virtual bool IOResetWithList(vector<string>&ipList) = 0;
	};
}

#endif