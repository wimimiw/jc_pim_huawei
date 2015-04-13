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
改进内容：1、异步连接：减少因某些模块不在线而引起的同步操作超时时间的叠加。
2、重连接：针对异常模块，尝试复位模块并重新连接
3、开关正常操作过程中不加任何延时

存在问题：正常连接中，硬件因异常断线，而网络虚电路存在，偶尔无法复位模块。解决办法
依次调用DisConnect、Connet函数。
2015.3.20
修改内容：
1、连接时异步连接第一台按设置超时等待，然后每台分别超时等待500ms,最长8秒
（所有不在线）
2、增加两个主开关的控制使能
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
			bool isOnline;		//是否在线
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
		//开关映射
		vector<string> __switchNameList;
		map<string,iniSwitch> __switchMap;	
		//全部动作列表
		actionCellc  __actionCellc[4],
						   *__ac_tx1,
						   *__ac_tx2,
						   *__ac_pim,
						   *__ac_det;
		//io映射
		map<string, vector<string>>__ioInfoMap;
		//动作操作列表
		map<string,unsigned short*>__actionList;
		//模块列表
		vector<string> __moduleList;
		bool bLoadMap = false;
	protected:
		bool __logEnable = false;
		string __ioPath,__imPath,__cfgPath,__runPath;
		map<string, stHostControl> __hostCtrl;		
	public:
		//构造函数
		implementsetting(void)
		{
			//virtual table not build,do not call the virtual function
			__ac_tx1 = &__actionCellc[0];
			__ac_tx2 = &__actionCellc[1];
			__ac_pim = &__actionCellc[2];
			__ac_det = &__actionCellc[3];
		}
		//析构函数
		virtual ~implementsetting(void)
		{
			//派生类析构开始，此时基类虚函数表指向基类虚函数表，
			//这跟构造函数时未建立虚函数表有类似情况。
			//DisConnect();
		}
	//静态函数
	public:
		//字符串替换
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
		//字符串分割
		static vector<string>split(string str, const string&pattern)
		{
			string::size_type pos = 0;
			vector<string> result;
			str += pattern;//扩展字符串以方便操作   
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
		//加载映射表
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
		//获取主机控制信息
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
		//设置主机控制信息
		//设置两个主开关箱的使能配置(信号源开关，检测开关箱)
		void SetHostsCtrl(const map<string, stHostControl>&host, bool bSignal, bool bDetect)
		{
			__hostCtrl = host;
			__hostCtrl["Signalswich"].enable = bSignal;
			__hostCtrl["Paspecumpwmt"].enable = bDetect;
		}
		//获取TX1名称列表
		vector<string>&GetTx1NameList(void)
		{
			return __ac_tx1->namelist;
		}
		//获取TX2名称列表
		vector<string>&GetTx2NameList(void)
		{
			return __ac_tx2->namelist;
		}
		//获取PIM名称列表
		vector<string>&GetPimNameList(void)
		{
			return __ac_pim->namelist;
		}
		//获取Det名称列表
		vector<string>&GetDetNameList(void)
		{
			return __ac_det->namelist;
		}
		//获取模块列表
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
		//选择通道TX1
		void SelChanTx1(const string&chan)
		{
			SelChan(__ac_tx1->actionMap[chan]);
		}
		//选择通道TX2
		void SelChanTx2(const string&chan)
		{
			SelChan(__ac_tx2->actionMap[chan]);
		}
		//选择通道PIM
		void SelChanPim(const string&chan)
		{
			SelChan(__ac_pim->actionMap[chan]);
		}
		//选择通道DET
		void SelChanDet(const string&chan)
		{
			SelChan(__ac_det->actionMap[chan]);
		}
		//连接
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
		//断开
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
		//执行动作
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
			int replyCnt = 0; //尝试次数
			map<string, bool>hostIPEnableList;
			vector<string> actionQueue;

			txBuf[0] = 'W';

			//读入主机使能队列
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
				//下发开关指令队列
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

				//断开连接
				for (vector<string>::iterator itr = actionQueue.begin();
					itr != actionQueue.end();
					itr++)
				{
					IODisConnect(*itr);
				}

				//复位
				funcResult = IOResetWithList(actionQueue);

				//重连
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
		//清除动作列表
		void Clear(void)
		{
			__actionList.clear();
		}
	private:
		//获取名称列表
		vector<string>GetNameList(const string&strBase)
		{
			string tmpStr(strBase);
			vector<string> nameVector;
			nameVector.clear();
			StringReplace(tmpStr," ", "");
			nameVector = split(tmpStr, ",");
			//引用就是对象的别名
			return nameVector;
		}
		//选择通道
		void SelChan(rowRun&rr)
		{
			for (rowRun::iterator swList = rr.begin();
				swList != rr.end();
				swList++)
			{
				AddActionList(swList->ip, swList->swName, swList->swIdx);
			}
		}
		//添加动作列表
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
		//加载IM参数
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
		//加载IO参数
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
		//获取行函数列表
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
		//加载IO参数
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
		//加载模块信息
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

			//if(checkValue != rxBuf[11])return;//此处不要检验

			for (int i = 1, j = 0; i<11; j++)
			{
				gpioBak[j] = rxBuf[i];
				i++;
				gpioBak[j] += rxBuf[i] * 256;
				i++;
			}
		}
		//读入配置文件
		string GetRowFromCfgFile(const string&section, const string&key, const string&defaultValue)
		{
			return GetRowFromFile(section, key, defaultValue, __cfgPath);
		}
		//读入IM文件
		string GetRowFromIMFile(const string&section, const string&key, const string&defaultValue)
		{
			return GetRowFromFile(section, key, defaultValue, __imPath);
		}
		//读入IO文件
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