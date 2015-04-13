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
2015.3.6
�������������첽����������IOConnetBegin,IOConnectEnd
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

#ifndef __COM_IO_CTL_H
#define __COM_IO_CTL_H

#include "implementsetting.hpp"
#include <Winsock2.h>
#include <mswsock.h>

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "mswsock.lib")

namespace ns_com_io_ctl{
	using  namespace std;

	#define	 DLL_HOST_NAME			"JcPimMultiBandV2.dll"		//������̬���ӿ���
	#define  CONFIG_FILE_NAME		"JcConfig.ini"				//�����ļ�����
	#define  TCP_CONNECT_TIMEOUT	(3)
	#define  TCP_SEND_TIMEOUT		(3)
	#define  TCP_RCV_TIMEOUT		(3)
	//#define  _WINSOCK_DEPRECATED_NO_WARNINGS		//�������Ԥ���붨��
	class com_io_ctl:public implementsetting	
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
			map<string, int>io;
		};

		typedef map<string, rowRun> actionMapDef;

		typedef struct actionCellc
		{
			vector<string> namelist;
			actionMapDef actionMap;
		};
		map<string, string> __ipmap;
		unsigned short __ipGpioBakArray[100][5];
		map<string, unsigned short*> __ipGpioBak;
		//����ӳ��
		vector<string> __switchNameList;
		map<string, iniSwitch> __switchMap;
		//ȫ�������б�
		actionCellc  __actionCellc[4],
			*__ac_tx1,
			*__ac_tx2,
			*__ac_pim,
			*__ac_det;
		//ioӳ��
		map<string, vector<string>>__ioInfoMap;
		//���������б�
		map<string, unsigned short*>__actionList;
		//ģ���б�
		vector<string> __moduleList;
		bool bLoadMap = false;
	protected:
		bool __logEnable = false;
		string __ioPath, __imPath, __cfgPath, __runPath;
		map<string, stHostControl> __hostCtrl;
	public:
		map<string, bool> __socketState;
		com_io_ctl(void)
		{
			__maskIO = false;

			WORD wVersionRequested = 0;
			WSADATA wsaData;

			wVersionRequested = MAKEWORD(2, 2);
			int err = WSAStartup(wVersionRequested, &wsaData);

			string info("WSAStartup function ");
			info.append(((err == NO_ERROR) ? "true" : "false"));
			log(info);
		}
		//��ʾ���û�����������	
		virtual~com_io_ctl(void)
		{
			DisConnect();				
			WSACleanup();
		}
		//�׽��ֲ���
		void socketTest()
		{
			WORD wVersionRequested;
			WSADATA wsaData;

			wVersionRequested = MAKEWORD(2, 2);
			int err = WSAStartup(wVersionRequested, &wsaData);

			SOCKET sc = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, NULL);

			SOCKADDR_IN addr;
			addr.sin_family = AF_INET;
			addr.sin_addr.s_addr = inet_addr("127.0.0.1");
			addr.sin_port = htons(1002);

			connect(sc, (struct sockaddr *)&addr, sizeof(addr));

			char buff[1024];
			ZeroMemory(buff, 1024);
			memcpy(buff, "asdfghjkpoioiuytrwqzxcvnm,", 20);

			send(sc, buff, 20, 0);

			recv(sc, buff, 1024, 0);
			cout << buff << endl;

			closesocket(sc);
		}
		//��λ��ȫ����
		virtual bool Reset(void)
		{
			bool result = true;

			for (map<string, stHostControl>::iterator itr = __hostCtrl.begin();
				itr != __hostCtrl.end();
				itr++)
			{
				if (itr->second.enable == false)continue;
				result = ResetOne(itr->second.ip);
				if (result == false)break;

				Delay(100);
			}

			return result;
		}
	private:	
		bool __maskIO;
		map<string,SOCKET> __socketClient;		
		//��ʱ����
		virtual void Delay(int mil)
		{
			Sleep(mil);
		}
		//���������麯��
		virtual bool IOConnect(const string&host)
		{
			if (__maskIO)return true;

			bool result = true;
			int iTimeOut = TCP_SEND_TIMEOUT * 1000;
			unsigned long ul = 1;			

			vector<string>hostInfo = split(host, ":");
			string ip = hostInfo[0];
			int port = atoi(hostInfo[1].c_str());

			SOCKET hSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

			if (hSocket == INVALID_SOCKET)
			{
				return false;
			}

			SOCKADDR_IN addr;
			addr.sin_family = AF_INET;
			addr.sin_addr.s_addr = inet_addr(ip.c_str());
			addr.sin_port = htons(port);

			setsockopt(hSocket, SOL_SOCKET, SO_RCVTIMEO, (char*)&iTimeOut, sizeof(iTimeOut));
			setsockopt(hSocket, SOL_SOCKET, SO_SNDTIMEO, (char*)&iTimeOut, sizeof(iTimeOut));

			ul = 1;
			ioctlsocket(hSocket, FIONBIO, &ul); //����Ϊ������ģʽ

			if (SOCKET_ERROR == connect(hSocket, (struct sockaddr *)&addr, sizeof(addr)))
			{
				int ret;
				timeval tm;
				fd_set fdwrite;

				tm.tv_sec = TCP_CONNECT_TIMEOUT;
				tm.tv_usec = 0;

				FD_ZERO(&fdwrite);
				FD_SET(hSocket, &fdwrite);

				//����һ��ʱ�䣬��ʱʱ���Զ���
				ret = select(0, NULL, &fdwrite, NULL, &tm);

				result = FD_ISSET(hSocket, &fdwrite) != 0;

				//if(ret > 0)
				//{
				//	getsockopt(hSocket, SOL_SOCKET, SO_ERROR, (char *)&error,&len);//Release print error
				//	if(error != 0) result = false;
				//} 
				//else 
				//	result = false;
			}

			ul = 0;
			ioctlsocket(hSocket, FIONBIO, &ul); //����Ϊ����ģʽ

			__socketClient[host] = hSocket;
			__socketState[host] = result;

			return result;
		}
		//����Ͽ��麯��
		virtual bool IODisConnect(const string&host)
		{
			if (__maskIO)return true;

			SOCKET hsocket = __socketClient[host];

			//����FD_CLOSE�¼�ûЧ�� 
			//������socket�������¼�  
			//WSAEVENT eventArray[WSA_MAXIMUM_WAIT_EVENTS];
			//WSAEVENT event = WSACreateEvent();
			//WSAEventSelect(hsocket, event, FD_CLOSE);

			//shutdown(hsocket, SD_BOTH);//���˻�Ӱ�������ͷ�

			//eventArray[0] = event;
			//WSAWaitForMultipleEvents(0, eventArray, TRUE, WSA_INFINITE, TRUE);

			//WSANETWORKEVENTS ne;
			//WSAEnumNetworkEvents(hsocket, event, &ne);

			//if (ne.lNetworkEvents&FD_CLOSE)
			//{
			//	cout << "close" << endl;
			//}

			struct linger so_linger;
			so_linger.l_onoff = 1;
			so_linger.l_linger = 0;  //ǿ�ƶϿ�����
			setsockopt(hsocket, SOL_SOCKET, SO_LINGER, (const char*)&so_linger, sizeof(&so_linger));
			bool result = closesocket(hsocket) != SOCKET_ERROR;
			__socketState[host] = result;

			log(host + " DisConnect  " + (result ? "Success!" : ("Failed! : " + logGetLastError())));

			return result;
		}
		//���緢���麯��
		virtual bool IOWrite(const string&host, const char*buf, int len)
		{
			if (__maskIO)return true;

			SOCKET hSocket = __socketClient[host];
			bool result = false;
			//timeval tm;
			//fd_set fdwrite;

			//tm.tv_sec = 0;
			//tm.tv_usec = 10000;

			//FD_ZERO(&fdwrite);
			//FD_SET(hSocket, &fdwrite);

			//select(0, NULL, &fdwrite, NULL, &tm);

			//if (FD_ISSET(hSocket, &fdwrite))
			//{
			result = send(hSocket, buf, len, 0) != SOCKET_ERROR;
			//}		
			log(host + " IOWrite:send  " + (result ? "Success!" : ("Failed! : " + logGetLastError())));
			//FD_CLR(hSocket, &fdwrite);
			__socketState[host] = result;

			return result;
		}
		//
		virtual bool IOWriteAsyc(const string&host, const char*buf, int len)
		{
			if (__maskIO)return true;

			SOCKET hSocket = __socketClient[host];
			bool result = false;

			timeval tm;
			fd_set fdwrite;

			tm.tv_sec = 0;
			tm.tv_usec = 10000;	

			result = send(hSocket, buf, len, 0) != SOCKET_ERROR;

			FD_ZERO(&fdwrite);
			FD_SET(hSocket, &fdwrite);

			select(0, NULL, &fdwrite, NULL, &tm);

			if (FD_ISSET(hSocket, &fdwrite))
			{

			}
			FD_CLR(hSocket, &fdwrite);

			log(host + " IOWrite:send  " + (result ? "Success!" : ("Failed! : " + logGetLastError())));
			
			__socketState[host] = result;

			return result;
		}
		//��������麯��
		virtual bool IORead(const string&host, char*buf, int*len)
		{
			if (__maskIO)return true;

			SOCKET hSocket = __socketClient[host];
			bool result = false;
			//timeval tm;
			//fd_set fdread;

			//tm.tv_sec = 0;
			//tm.tv_usec = 10000;

			//FD_ZERO(&fdread);
			//FD_SET(hSocket, &fdread);

			//select(0, &fdread, NULL, NULL, &tm);

			//if (FD_ISSET(hSocket, &fdread))
			//{
			result = recv(hSocket, buf, *len, 0) != SOCKET_ERROR;
			//}	
			log(host + " IORead:recv  " + (result ? "Success!" : ("Failed! : " + logGetLastError())));
			//FD_CLR(hSocket, &fdread);

			__socketState[host] = result;

			return result;
		}
		//INI�ļ���ȡ�麯��
		virtual string GetRowFromFile(const string&section, const string&key, const string&defaultValue, const string&fileName)
		{
			char strBuff[512] = { 0 };

			GetPrivateProfileStringA(
				section.c_str(),
				key.c_str(),
				defaultValue.c_str(),
				strBuff,
				512,
				fileName.c_str());

			return string(strBuff);
		}
		//INI�ļ���ȡ�����������е�KEYֵ
		virtual vector<string> GetSecKeyFromFile(const string&section, const string&fileName)
		{			
#define BUF_SIZE 4096
			shared_ptr<char>pbuf(new char[BUF_SIZE]);
			char *buf = pbuf.get();
			vector<string> keyList;

			int charLen = GetPrivateProfileStringA(section.c_str(), NULL, NULL, buf, BUF_SIZE, fileName.c_str());

			for (int i = 0; i < charLen; i++)
			{
				if (buf[i] == 0 && i + 1 < charLen)
				{
					keyList.push_back(&buf[i + 1]);
				}
				else if (i == 0)
				{
					keyList.push_back(&buf[i]);
				}
			}			

			return keyList;
		}
		//��ȡ�ļ�·���麯��   δ����\\���͡�//��,Linux������Ҫ�޸�
		virtual string GetRunPath() const
		{
			char strBuff[MAX_PATH] = { 0 };
			//GetCurrentDirectoryA(256,strBuff);  //Σ��
			GetModuleFileNameA(GetModuleHandleA(DLL_HOST_NAME), strBuff, MAX_PATH);
			return string(strBuff);
		}
		//ģ�鸴λһ��
		virtual bool ResetOne(const string&host)
		{
			int result = 0;
			string ip;
			const string txString = "AT+MODE=0\r\nAT+LOGIN=88888\r\nAT+RESET=88888\r\n";

			ip = split(host, ":")[0];

			SOCKET sckt = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, NULL);
			SOCKADDR_IN addr;
			addr.sin_family = AF_INET;
			addr.sin_addr.s_addr = inet_addr(ip.c_str());
			addr.sin_port = htons(3003);

			if (SOCKET_ERROR != connect(sckt, (struct sockaddr *)&addr, sizeof(addr)))
			{
				Delay(200);
				result = send(sckt, txString.c_str(), (int)txString.size(), 0);
				Delay(200);
			}
			else
			{
				result = -1;
			}

			closesocket(sckt);

			__socketState[host] = (result != SOCKET_ERROR);

			return (result != -1);
		}
		//ɾ���ļ�
		virtual void WindowsDeleteFile(const char* file)
		{
			DeleteFileA(file);
		}
		//��ȡУ��ֵ
		USHORT GetCheckSum(LPBYTE lpBuff, DWORD dwSize)
		{
			DWORD dwCheckSum = 0;
			USHORT* lpWord = (USHORT*)lpBuff;
			while (dwSize > 1)
			{
				dwCheckSum += *lpWord++;
				dwSize -= 2;
			}
			if (dwSize == 1)
				dwCheckSum += *((LPBYTE)lpBuff);
			dwCheckSum = (dwCheckSum >> 16) + (dwCheckSum & 0XFFFF);
			return (USHORT)(~dwCheckSum);
		}
		//�첽���ӿ�ʼ
		virtual bool IOConnectBegin(const string&host)
		{
			if (__maskIO)return true;

			bool result = true;
			int iTimeOut = TCP_SEND_TIMEOUT * 1000;
			unsigned long ul = 1;

			vector<string>hostInfo = split(host, ":");
			string ip = hostInfo[0];
			int port = atoi(hostInfo[1].c_str());

			SOCKET hSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

			if (hSocket == INVALID_SOCKET)
			{
				log(host + " IOConnectBegin:socket Failed! : " + logGetLastError());
				return false;
			}

			SOCKADDR_IN addr;
			addr.sin_family = AF_INET;
			addr.sin_addr.s_addr = inet_addr(ip.c_str());
			addr.sin_port = htons(port);

			result = SOCKET_ERROR != setsockopt(hSocket, SOL_SOCKET, SO_RCVTIMEO, (char*)&iTimeOut, sizeof(iTimeOut));

			log(host + " IOConnectBegin:setsockopt SO_RCVTIMEO  " + (result ? "Success!" : ("Failed! : " + logGetLastError())));

			result = SOCKET_ERROR != setsockopt(hSocket, SOL_SOCKET, SO_SNDTIMEO, (char*)&iTimeOut, sizeof(iTimeOut));

			log(host + " IOConnectBegin:setsockopt SO_SNDTIMEO  " + (result ? "Success!" : ("Failed! : " + logGetLastError())));

			ul = 1;
			result = SOCKET_ERROR != ioctlsocket(hSocket, FIONBIO, &ul); //����Ϊ������ģʽ

			log(host + " IOConnectBegin:ioctlsocket  " + (result ? "Success!" : ("Failed! : " + logGetLastError())));

			result = SOCKET_ERROR != connect(hSocket, (struct sockaddr *)&addr, sizeof(addr));

			//if (!result)log(host + " IOConnectBegin:connect Failed! ");

			__socketClient[host] = hSocket;

			return true;
		}
		//�첽���ӵȴ���
		virtual bool IOConnectEnd(const string&host,int timeout)
		{
			SOCKET hSocket = NULL;

			bool result = true;
			timeval tm;
			fd_set fdwrite;
			tm.tv_sec = TCP_CONNECT_TIMEOUT;		//�˴�����timeout
			tm.tv_usec = TCP_CONNECT_TIMEOUT * 1000 % 1000 * 1000;

			FD_ZERO(&fdwrite);
			
			for (auto itr = __socketClient.begin();
				itr != __socketClient.end();
				itr++)
			{
				FD_SET(itr->second, &fdwrite);
			}
			
			result = select(0, NULL, &fdwrite, NULL, &tm) > 0;

			for (size_t i = 0; i < 100; i++)
			{
				result = FD_ISSET(hSocket, &fdwrite) != 0;
			}

			log(host + " IOConnectEnd:select  " + (result ? "Success!" : ("Failed! : " + logGetLastError())));

			result = FD_ISSET(hSocket, &fdwrite) != 0;

			log(host + " IOConnectEnd:FD_ISSET  " + (result ? "Success!" : ("Failed! : " + logGetLastError())));

			//if (result)
			//{//�ú�����Ҫ�ã����������ӵ�����»᷵��ʧ��
			//  char error[256];
			//  int len;
			//	len = sizeof(error);
			//	result = getsockopt(hSocket, SOL_SOCKET, SO_ERROR, error, &len) == 0;			
			//}

			FD_CLR(hSocket, &fdwrite);

			unsigned long ul = 0;
			bool resICS = ioctlsocket(hSocket, FIONBIO, &ul) != SOCKET_ERROR; //����Ϊ����ģʽ

			__socketState[host] = result;

			log(host + " IOConnectEnd:ioctlsocket and Connect  " + (result ? "Success!" : ("Failed! : " + logGetLastError())));

			return result;
		}
		//�첽����
		virtual bool IOConnectAsyc(map<string,bool>&host)
		{
			if (__maskIO)return true;

			bool result = true;
			int iTimeOut = TCP_RCV_TIMEOUT * 1000;	
			int oTimeOut = TCP_SEND_TIMEOUT * 1000;

			fd_set fdwrite;
			unsigned long ul = 1;
			//���FD
			FD_ZERO(&fdwrite);
			//�����׽���
			for (auto itr = host.begin();
				itr != host.end();
				itr++)
			{
				vector<string>hostInfo = split(itr->first, ":");
				string ip = hostInfo[0];
				int port = atoi(hostInfo[1].c_str());

				SOCKET hSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

				if (hSocket == INVALID_SOCKET)
				{
					log(itr->first + " IOConnectAsyc:socket Failed! : " + logGetLastError());
					return false;
				}

				SOCKADDR_IN addr;
				addr.sin_family = AF_INET;
				addr.sin_addr.s_addr = inet_addr(ip.c_str());
				addr.sin_port = htons(port);

				result = SOCKET_ERROR != setsockopt(hSocket, SOL_SOCKET, SO_RCVTIMEO, (char*)&iTimeOut, sizeof(iTimeOut));

				log(itr->first + " IOConnectAsyc:setsockopt SO_RCVTIMEO  " + (result ? "Success!" : ("Failed! : " + logGetLastError())));

				result = SOCKET_ERROR != setsockopt(hSocket, SOL_SOCKET, SO_SNDTIMEO, (char*)&oTimeOut, sizeof(oTimeOut));

				log(itr->first + " IOConnectAsyc:setsockopt SO_SNDTIMEO  " + (result ? "Success!" : ("Failed! : " + logGetLastError())));

				ul = 1;
				result = SOCKET_ERROR != ioctlsocket(hSocket, FIONBIO, &ul); //����Ϊ������ģʽ

				log(itr->first + " IOConnectAsyc:ioctlsocket  " + (result ? "Success!" : ("Failed! : " + logGetLastError())));

				result = SOCKET_ERROR != connect(hSocket, (struct sockaddr *)&addr, sizeof(addr));

				__socketClient[itr->first] = hSocket;

				FD_SET(hSocket, &fdwrite);					
			}
			//����ʱ��ṹ
			timeval tm;
			tm.tv_sec = TCP_CONNECT_TIMEOUT;
			tm.tv_usec = TCP_CONNECT_TIMEOUT * 1000 % 1000 * 1000;
			//�ȴ�����
			result = select(0, NULL, &fdwrite, NULL, &tm) > 0;
			//��ȡ����״̬
			for (auto itr = __socketClient.begin();
				itr != __socketClient.end();
				itr++)
			{
				host[itr->first] = FD_ISSET(itr->second, &fdwrite) > 0;
				if (result)
					result = host[itr->first];
				FD_CLR(itr->second, &fdwrite);
			}

			return result;
		}
		//������������Ƿ�����
		virtual bool IOSocketIsActive(const string&host)
		{
			if (__maskIO)return true;

			SOCKET hSocket = __socketClient[host];
			bool result = true;
			int ret;
			int count;
			char buf[12] = { 0 };
			timeval tm;
			fd_set fdread;

			tm.tv_sec = 0;
			tm.tv_usec = 10000;

			FD_ZERO(&fdread);
			FD_SET(hSocket, &fdread);

			ret = select(0, &fdread, NULL, NULL, &tm);

			if (ret == 1)
			{
				count = recv(hSocket, buf, sizeof(buf), 0);
				if (count == 1 || count == 0)
				{
					result = false;
				}
			}

			__socketState[host] = result;

			return result;
		}
		//�����б�λģ��
		virtual bool IOResetWithList(vector<string>&ipList)
		{
			const char* restStr = "AT+MODE=0\r\nAT+LOGIN=88888\r\nAT+RESET=88888\r\n";
			string host;
			bool funcResult = true;

			for (vector<string>::iterator itr = ipList.begin();
				itr != ipList.end();
				itr++)
			{
				host = split(*itr, ":")[0];
				host.append(":3003");
				//����
				if (!IOConnect(host))
				{
					funcResult = false;
					IODisConnect(host);
					break;
				}
				Delay(100);
				//��λָ���
				if (!IOWrite(host, restStr, strlen(restStr)))
				{
					funcResult = false;
					IODisConnect(host);
					break;
				}
				//�Ͽ�����
				IODisConnect(host);
				Delay(200);
			}

			return funcResult;
		}
		//��ȡ��ʱ�ļ�·��
		virtual string GetTempFileInfo(const string& flagName)const
		{
			//��ȡ��ʱ�ļ�·��  
#define BUFSIZE 2048 
			char lpPathBuffer[BUFSIZE];
			char szTempName[MAX_PATH];

			GetTempPathA(BUFSIZE,
				lpPathBuffer);

			//������ʱ�ļ�  
			GetTempFileNameA(lpPathBuffer, // ��ʱ�ļ�Ŀ¼  
				flagName.c_str(),          // ��ʱ�ļ��ĵ�ǰ׺  
				0,                         // ����Ψһ������  
				szTempName);               // �������ֵĻ���  

			return string(szTempName);
			//TODO: insert return statement here
		}
		//������Ϣ
		virtual void Message(const string&info)
		{
			MessageBox(NULL, (LPCWSTR)StringToWString(info).c_str(), L"WARNING!", MB_OK);
		}
		//��ȡ�׽��ִ�����Ϣ
		string logGetLastError()
		{
			char bufs[100];
			sprintf_s(bufs, "%ld", WSAGetLastError());
			return string(bufs);
		}
		//��¼��־ 
		void log(const string& info)
		{
			if (!__logEnable)return;

			string file(__runPath);
			string text;

			file.append("\\switchlog.txt");

			SYSTEMTIME st;
			GetLocalTime(&st);
			char timeBuf[256];

			sprintf_s(timeBuf, "%d-%02d-%02d %02d:%02d:%02d",
				st.wYear,
				st.wMonth,
				st.wDay,
				st.wHour,
				st.wMinute,
				st.wSecond);

			text += "(";
			text.append(timeBuf);
			text += ")==>";
			text += info;
			text += "\n";

			ofstream ofs(file, ios_base::app);
			ofs.write(text.c_str(), text.size());
			ofs.close();
		}
		//Converting a Ansi string to WChar string  
		wstring StringToWString(const string &str)
		{
			wstring wstr(str.length(), L' ');
			copy(str.begin(), str.end(), wstr.begin());
			return wstr;
		}			
	};
}

#endif
