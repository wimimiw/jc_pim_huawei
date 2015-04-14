/*******************************Copyright (c)***********************************
*
*              Copyright (C), 1999-2015, Jointcom . Co., Ltd.
*
*------------------------------------------------------------------------------
* @file	:	com_io_ctl.h
* @author	:mashuai
* @version	:v2.0
* @date		:2015.3.1
* @brief	:
*------------------------------------------------------------------------------*/

#pragma once

#include "implementsetting.h"
#include <Winsock2.h>
#include <mswsock.h>

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "mswsock.lib")

namespace ns_com_io_ctl{
	using  namespace std;

	#define  CONNECT_TYEP			E_UDP
	#define	 DLL_HOST_NAME			"JcPimMultiBandV2.dll"		//宿主动态链接库名
	#define  TCP_CONNECT_TIMEOUT	(3)
	#define  TCP_SEND_TIMEOUT		(3)
	#define  TCP_RCV_TIMEOUT		(3)
	//#define  _WINSOCK_DEPRECATED_NO_WARNINGS		//将其放入预编译定义

	#define DEF_BUF_SIZE 1024
	#define IP_HEADER_SIZE 20
	#define ICMP_HEADER_SIZE 12

	typedef enum
	{
		E_TCP = 2, E_UDP = 3, E_COM = 4,
	}EConType;

	class com_io_ctl :
		public implementsetting
	{	
	public:
		com_io_ctl(void);		
		static void SocketTest();
		virtual bool Reset(void);		
		map<string, bool> __socketState;
	private:	
		bool __maskIO;
		EConType __conType = CONNECT_TYEP;
		map<string,SOCKET> __socketClient;	
		map<string,sockaddr_in> __addrRecver;
		virtual void Delay(int mil);
		virtual bool IOConnect(const string&host);
		virtual bool IODisConnect(const string&host);
		virtual bool IOWrite(const string&host,const char*buf,int len);
		virtual bool IORead(const string&host,char*buf,int*len);
		virtual void WindowsDeleteFile(const char* file);
		virtual string GetRunPath();
		virtual string GetRowFromFile(const string&section,const string&key,const string&defaultValue,const string&fileName);
		virtual string GetTempFileInfo(const string& flagName);
		USHORT GetCheckSum(LPBYTE lpBuff, DWORD dwSize);
	public:
		virtual~com_io_ctl(void);		
	private:
		virtual bool ResetOne(const string&host);
		virtual bool IOConnectBegin(const string&host);
		virtual bool IOConnectEnd(const string&host,int timeout);
		virtual bool IOSocketIsActive(const string&host);
		virtual bool IOResetWithList(vector<string>&ipList);		
		virtual void Message(const string&info);
		void log(const string& info);
		string logGetLastError();
		wstring StringToWString(const string &str);
	};
}
