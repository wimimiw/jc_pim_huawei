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
*------------------------------------------------------------------------------*/
#pragma once

namespace ns_com_io_ctl
{
	using  namespace std;
//#define __DEBUG_PRINT
#define	ACTION_MESSAGE_REPORT    (1)   //1:enable    0:disable

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
		typedef vector<string> _tp_vs;

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
			_tp_vs namelist;
			actionMapDef actionMap;	
		};	
		//IP地址映射
		_tp_vs __ipNameList;
		map<string,string> __ipmap;		
		unsigned short __ipGpioBakArray[100][5];
		map<string,unsigned short*> __ipGpioBak;
		//开关映射
		_tp_vs __switchNameList;
		map<string,iniSwitch> __switchMap;	
		//全部动作列表
		actionCellc  __actionCellc[4],
						   *__ac_tx1,
						   *__ac_tx2,
						   *__ac_pim,
						   *__ac_det;
		//io映射
		map<string,_tp_vs> __ioInfoMap; 
		//动作操作列表
		map<string,unsigned short*>__actionList;
		//作缓冲
		_tp_vs __nameList;
		//
		vector<string> __moduleList;
		bool bLoadMap = false;
	protected:
		bool __logEnable = false;
		string __ioPath,__imPath,__cfgPath,__runPath;
		map<string, stHostControl> __hostCtrl;		
	public:
		implementsetting(void);
	public:
		virtual~implementsetting(void);
	public:
		void AddSwitchActionList(int addr, int swId, int swIdx);
		void GetHostsCtrl(map<string,stHostControl>&host);
		void SetHostsCtrl(const map<string, stHostControl>&host, bool bSignal, bool bDetect);
		vector<string>&GetModuleList(void);
		vector<string>&GetTx1NameList(void);
		vector<string>&GetTx2NameList(void);
		vector<string>&GetPimNameList(void);
		vector<string>&GetDetNameList(void);
		bool LoadMap();
		bool Connect(void);
		void DisConnect(void);
		void Clear(void);
		bool Excute(void);
		void SelChanTx1(const string&chan);
		void SelChanTx2(const string&chan);
		void SelChanPim(const string&chan);
		void SelChanDet(const string&chan);		
		static void StringReplace(string&strBase, string strSrc, string strDes);
		static vector<string> split(string str,string pattern);
	protected:
		virtual string GetRunPath()=0;
		virtual string GetRowFromFile(const string&section,const string&key,const string&defaultValue,const string&fileName)=0;
		virtual string GetTempFileInfo(const string&flagName)=0;
		virtual void Delay(int mil)=0;
		virtual bool IOConnect(const string&host) = 0;
		virtual bool IODisConnect(const string&host) = 0;
		virtual bool IOWrite(const string&host, const char*buf, int len) = 0;
		virtual bool IORead(const string&host, char*buf, int*len) = 0;
		virtual void WindowsDeleteFile(const char* file)=0;
		virtual bool ResetOne(const string&host) = 0;
		virtual void Message(const string&info) = 0;
		virtual bool IOConnectBegin(const string&host) = 0;
		virtual bool IOConnectEnd(const string&host, int timeout) = 0;
		virtual bool IOSocketIsActive(const string&host) = 0;
		virtual bool IOResetWithList(vector<string>&ipList) = 0;
	private:
		vector<string>&GetNameList(string&strBase);
		void SelChan(rowRun&rr);
		void AddActionList(const string&ip,const string&sw,const int chan);
		bool ExcuteCmd(const string&ip,const string&sw,int chan);
		bool LoadParaIM(void);
		bool LoadParaIO(void);
		void GetRowRunFunc(string str,rowRun&rr);
		void LoadActionList(const string&section,actionCellc&ac);
		void LoadModuleState(const string&host);
		string GetRowFromIMFile(const string&section,const string&key,const string&defaultValue);
		string GetRowFromIOFile(const string&section,const string&key,const string&defaultValue);				
		string GetRowFromCfgFile(const string&section,const string&key,const string&defaultValue);	
};
}
