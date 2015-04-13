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

#ifndef __SWITCH_CONFIG_H__
#define __SWITCH_CONFIG_H__
#define IO_STRING	         "[STATE]\n"\
"//华为测试平台\n"\
"//分别控制每一个开关\n"\
"//开关序号与面板丝印一致\n"\
"//******************************************************\n"\
"//开关1和2用在了开关矩阵1中\n"\
"//\n"\
"//开关1 SP6T 只用了1-3\n"\
"[Signal1swich]\n"\
"//1通道\n"\
"0=0,0,0,0,2,\n"\
"//2通道\n"\
"1=0,0,0,0,1,\n"\
"//3通道\n"\
"2=0,512,0,0,0,\n"\
"//\n"\
"//开关2 SP6T 只用了1-3\n"\
"[Signal2swich]\n"\
"//1通道\n"\
"3=0,0,0,16,0,\n"\
"//2通道\n"\
"4=0,0,0,8,0,\n"\
"//3通道\n"\
"5=0,0,0,4,0,\n"\
"//******************************************************\n"\
"//开关3-8用在了开关矩阵2中\n"\
"[Powermeterswich]\n"\
"//\n"\
"//开关3 SP10T 只用了1-7\n"\
"//1通道\n"\
"6=0,0,0,16,0,\n"\
"//2通道\n"\
"7=0,0,0,8,0,\n"\
"//3通道\n"\
"8=0,0,0,4,0,\n"\
"//4通道\n"\
"9=0,0,0,2,0,\n"\
"//5通道\n"\
"10=0,0,0,1,0,\n"\
"//6通道\n"\
"11=0,0,4096,0,0,\n"\
"//7通道\n"\
"12=0,0,2048,0,0,\n"\
"//\n"\
"//开关4 SP10T 只用了1-7\n"\
"[Spectrumswich]\n"\
"//1通道\n"\
"13=0,0,0,0,2,\n"\
"//2通道\n"\
"14=0,0,0,0,1,\n"\
"//3通道\n"\
"15=0,512,0,0,0,\n"\
"//4通道\n"\
"16=0,256,0,0,0,\n"\
"//5通道\n"\
"17=0,32,0,0,0,\n"\
"//6通道\n"\
"18=0,16,0,0,0,\n"\
"//7通道\n"\
"19=0,8,0,0,0,\n"\
"//\n"\
"//开关5 SP3T 大功率\n"\
"[PA1swich1]\n"\
"//1通道\n"\
"20=16,0,0,0,0,\n"\
"//2通道\n"\
"21=32,0,0,0,0,\n"\
"//3通道\n"\
"22=64,0,0,0,0,\n"\
"//\n"\
"//开关6 SP3T 大功率\n"\
"[PA1swich2]\n"\
"//1通道\n"\
"23=128,0,0,0,0,\n"\
"//2通道\n"\
"24=0,0,16,0,0,\n"\
"//3通道\n"\
"25=0,0,32,0,0,\n"\
"//\n"\
"//开关7 SP3T 大功率\n"\
"[PA2swich1]\n"\
"//1通道\n"\
"26=0,0,0,0,1024,\n"\
"//2通道\n"\
"27=0,0,0,0,2048,\n"\
"//3通道\n"\
"28=0,0,0,0,4096,\n"\
"//\n"\
"//开关8 SP3T 大功率\n"\
"[PA2swich2]\n"\
"//1通道\n"\
"29=0,0,0,0,8192,\n"\
"//2通道\n"\
"30=0,0,0,0,16384,\n"\
"//3通道\n"\
"31=0,0,0,0,32768,\n"\
"//****************************************************** \n"\
"//开关9-11用在了7个不同的无源模块中\n"\
"//开关9-11都是Failsafe开关，因此1通道为实际控制电平的，2通道仅为显示LED使用\n"\
"//\n"\
"//开关9 SPDT Failsafe\n"\
"[Pimswich]\n"\
"//1通道\n"\
"32=32,0,0,0,0,\n"\
"//2通道\n"\
"33=16,0,0,0,0,\n"\
"//\n"\
"//开关10 SPDT Failsafe 大功率\n"\
"[Txoutswich]  \n"\
"//1通道\n"\
"34=0,16,0,0,0,\n"\
"//2通道\n"\
"35=0,8,0,0,0,\n"\
"//\n"\
"//开关11 SPDT Failsafe\n"\
"[Couplerswich]\n"\
"//1通道\n"\
"36=0,0,16,0,0,\n"\
"//2通道\n"\
"37=128,0,0,0,0,\n"\
"\n"\
"\n"\
""
#define IMPLEMENT_STRING  "[ip]\n"\
"Signalswich         =127.0.0.1:5000\n"\
"Paspecumpwmt        =127.0.0.1:5001\n"\
"Testmdlte700        =127.0.0.1:5002 \n"\
"Testmddd800         =127.0.0.1:5003\n"\
"Testmdgsm900        =127.0.0.1:5004\n"\
"Testmddcs1800       =127.0.0.1:5005\n"\
"Testmdpcs1900       =127.0.0.1:5006\n"\
"Testmdwcdma2100     =127.0.0.1:5007\n"\
"Testmdlte2600       =127.0.0.1:5008\n"\
"\n"\
"[switch]\n"\
"namelist	    =Signal1swich,Signal2swich,PA1swich1,PA1swich2,PA2swich1,PA2swich2,Spectrumswich,Powermeterswich,Couplerswich,Pimswich,Txoutswich\n"\
"\n"\
"Signal1swich        =PA1in1,PA2in1,PA3in1\n"\
"PA1in1=1\n"\
"PA2in1=2\n"\
"PA3in1=3\n"\
"\n"\
"Signal2swich        =PA1in2,PA2in2,PA3in2\n"\
"PA1in2=1\n"\
"PA2in2=2\n"\
"PA3in2=3\n"\
"\n"\
"PA1swich1           =MDlte700tx1,MDdd800tx1,MDgsm900tx1 \n"\
"MDlte700tx1=1\n"\
"MDdd800tx1=2\n"\
"MDgsm900tx1=3\n"\
"\n"\
"PA1swich2           =MDlte700tx2,MDdd800tx2,MDgsm900tx2\n"\
"MDlte700tx2=1\n"\
"MDdd800tx2=2\n"\
"MDgsm900tx2=3\n"\
"\n"\
"PA2swich1           =MDdcs1800tx1,MDpcs1900tx1,MDwcdma2100tx1\n"\
"MDdcs1800tx1=1\n"\
"MDpcs1900tx1=2\n"\
"MDwcdma2100tx1=3\n"\
"\n"\
"PA2swich2           =MDdcs1800tx2,MDpcs1900tx2,MDwcdma2100tx2\n"\
"MDdcs1800tx2=1\n"\
"MDpcs1900tx2=2\n"\
"MDwcdma2100tx2=3 \n"\
"\n"\
"Spectrumswich       =MDlte700pim,MDdd800tpim,MDgsm900pim,MDdcs1800pim,MDpcs1900pim,MDwcdma2100pim,MDwcdma2600pim\n"\
"MDlte700pim=1\n"\
"MDdd800tpim=2\n"\
"MDgsm900pim=3\n"\
"MDdcs1800pim=4\n"\
"MDpcs1900pim=5\n"\
"MDwcdma2100pim=6\n"\
"MDwcdma2600pim=7\n"\
"\n"\
"Powermeterswich     =MDlte700pwmt,MDdd800tpwmt,MDgsm900pwmt,MDdcs1800pwmt,MDpcs1900pwmt,MDwcdma2100pwmt,MDwcdma2600pwmt\n"\
"MDlte700pwmt=1\n"\
"MDdd800tpwmt=2\n"\
"MDgsm900pwmt=3\n"\
"MDdcs1800pwmt=4\n"\
"MDpcs1900pwmt=5\n"\
"MDwcdma2100pwmt=6\n"\
"MDwcdma2600pwmt=7\n"\
"\n"\
"Couplerswich        =Powerdettx1,Powerdettx2 \n"\
"Powerdettx1=1\n"\
"Powerdettx2=2\n"\
"\n"\
"Pimswich            =Pimdetrxa,Pimdetrxb\n"\
"Pimdetrxa=1\n"\
"Pimdetrxb=2\n"\
"\n"\
"Txoutswich          =ANTA,ANTB\n"\
"ANTA=1\n"\
"ANTB=2\n"\
"\n"\
"[actiontx1]\n"\
"lte700Atx1 	= Signal1swich(Signalswich,PA1in1) ,PA1swich1(Paspecumpwmt,MDlte700tx1),  Txoutswich(Testmdlte700 ,ANTA) \n"\
"\n"\
"Lte700Btx1 	= Signal1swich(Signalswich,PA1in1) ,PA1swich1(Paspecumpwmt,MDlte700tx1),  Txoutswich(Testmdlte700 ,ANTB) \n"\
"\n"\
"DD800Atx1  	= Signal1swich(Signalswich,PA1in1) ,PA1swich1(Paspecumpwmt,MDdd800tx1),   Txoutswich(Testmddd800 ,ANTA) \n"\
"\n"\
"DD800Btx1  	= Signal1swich(Signalswich,PA1in1) ,PA1swich1(Paspecumpwmt,MDdd800tx1),   Txoutswich(Testmddd800 ,ANTB) \n"\
"\n"\
"GSM900Atx1  	= Signal1swich(Signalswich,PA1in1) ,PA1swich1(Paspecumpwmt,MDgsm900tx1),  Txoutswich(Testmdgsm900 ,ANTA) \n"\
"\n"\
"GSM900Btx1  	= Signal1swich(Signalswich,PA1in1) ,PA1swich1(Paspecumpwmt,MDgsm900tx1),  Txoutswich(Testmdgsm900 ,ANTB) \n"\
"\n"\
"Dcs1800Atx1 	= Signal1swich(Signalswich,PA2in1) ,PA2swich1(Paspecumpwmt,MDdcs1800tx1), Txoutswich(Testmddcs1800 ,ANTA) \n"\
"\n"\
"Dcs1800Btx1 	= Signal1swich(Signalswich,PA2in1) ,PA2swich1(Paspecumpwmt,MDdcs1800tx1), Txoutswich(Testmddcs1800 ,ANTB) \n"\
"\n"\
"Pcs1900Atx1 	= Signal1swich(Signalswich,PA2in1) ,PA2swich1(Paspecumpwmt,MDpcs1900tx1), Txoutswich(Testmdpcs1900 ,ANTA) \n"\
"\n"\
"Pcs1900Btx1 	= Signal1swich(Signalswich,PA2in1) ,PA2swich1(Paspecumpwmt,MDpcs1900tx1), Txoutswich(Testmdpcs1900  ,ANTB) \n"\
"\n"\
"Wcdma2100Atx1 	= Signal1swich(Signalswich,PA2in1) ,PA2swich1(Paspecumpwmt,MDwcdma2100tx1), Txoutswich(Testmdwcdma2100 ,ANTA)\n"\
"\n"\
"Wcdma2100Btx1 	= Signal1swich(Signalswich,PA2in1) ,PA2swich1(Paspecumpwmt,MDwcdma2100tx1), Txoutswich(Testmdwcdma2100 ,ANTB) \n"\
"\n"\
"Lte2600Atx1 	= Signal1swich(Signalswich,PA3in1) , Txoutswich(Testmdlte2600  ,ANTA) \n"\
"\n"\
"Lte2600Btx1 	= Signal1swich(Signalswich,PA3in1) , Txoutswich(Testmdlte2600  ,ANTB) \n"\
"\n"\
"[actiontx2]\n"\
"\n"\
"lte700Atx2 	= Signal2swich(Signalswich,PA1in2) ,PA1swich2(Paspecumpwmt,MDlte700tx2), Txoutswich(Testmdlte700 ,ANTA) \n"\
"\n"\
"Lte700Btx2 	= Signal2swich(Signalswich,PA1in2) ,PA1swich2(Paspecumpwmt,MDlte700tx2), Txoutswich(Testmdlte700 ,ANTB) \n"\
"\n"\
"DD800Atx2  	= Signal2swich(Signalswich,PA1in2) ,PA1swich2(Paspecumpwmt,MDdd800tx2), Txoutswich(Testmddd800 ,ANTA) \n"\
"\n"\
"DD800Btx2  	= Signal2swich(Signalswich,PA1in2) ,PA1swich2(Paspecumpwmt,MDdd800tx2), Txoutswich(Testmddd800 ,ANTB)\n"\
"\n"\
"GSM900Atx2  	= Signal2swich(Signalswich,PA1in2) ,PA1swich2(Paspecumpwmt,MDgsm900tx2),Txoutswich(Testmdgsm900 ,ANTA) \n"\
"\n"\
"GSM900Btx2  	= Signal2swich(Signalswich,PA1in2) ,PA1swich2(Paspecumpwmt,MDgsm900tx2),Txoutswich(Testmdgsm900 ,ANTB) \n"\
"\n"\
"Dcs1800Atx2 	= Signal2swich(Signalswich,PA2in2) ,PA2swich2(Paspecumpwmt,MDdcs1800tx2),Txoutswich(Testmddcs1800 ,ANTA) \n"\
"\n"\
"Dcs1800Btx2 	= Signal2swich(Signalswich,PA2in2) ,PA2swich2(Paspecumpwmt,MDdcs1800tx2),Txoutswich(Testmddcs1800 ,ANTB) \n"\
"\n"\
"Pcs1900Atx2 	= Signal2swich(Signalswich,PA2in2) ,PA2swich2(Paspecumpwmt,MDpcs1900tx2),Txoutswich(Testmdpcs1900  ,ANTA) \n"\
"\n"\
"Pcs1900Btx2 	= Signal2swich(Signalswich,PA2in2) ,PA2swich2(Paspecumpwmt,MDpcs1900tx2),Txoutswich(Testmdpcs1900  ,ANTB) \n"\
"\n"\
"Wcdma2100Atx2 	= Signal2swich(Signalswich,PA2in2) ,PA2swich2(Paspecumpwmt,MDwcdma2100tx2), Txoutswich(Testmdwcdma2100 ,ANTA) \n"\
"\n"\
"Wcdma2100Btx2 	= Signal2swich(Signalswich,PA2in2) ,PA2swich2(Paspecumpwmt,MDwcdma2100tx2), Txoutswich(Testmdwcdma2100 ,ANTB) \n"\
"\n"\
"Lte2600Atx2 	= Signal2swich(Signalswich,PA3in2) ,Txoutswich(Testmdlte2600  ,ANTA) \n"\
"\n"\
"Lte2600Btx2 	= Signal2swich(Signalswich,PA3in2) ,Txoutswich(Testmdlte2600  ,ANTB) \n"\
"\n"\
"	\n"\
"\n"\
"[actionpim]\n"\
"lte700Apim 	= Spectrumswich(Paspecumpwmt,MDlte700pim),Pimswich( Testmdlte700, Pimdetrxa)\n"\
"\n"\
"Lte700Bpim 	= Spectrumswich(Paspecumpwmt,MDlte700pim),Pimswich( Testmdlte700, Pimdetrxb)\n"\
"\n"\
"DD800Apim  	= Spectrumswich(Paspecumpwmt,MDdd800tpim),Pimswich( Testmddd800, Pimdetrxa)\n"\
"\n"\
"DD800Bpim  	= Spectrumswich(Paspecumpwmt,MDdd800tpim),Pimswich( Testmddd800, Pimdetrxb)\n"\
"\n"\
"GSM900Apim  	= Spectrumswich(Paspecumpwmt,MDgsm900pim),Pimswich( Testmdgsm900, Pimdetrxa)\n"\
"\n"\
"GSM900Bpim  	= Spectrumswich(Paspecumpwmt,MDgsm900pim),Pimswich( Testmdgsm900, Pimdetrxb)\n"\
"\n"\
"Dcs1800Apim 	= Spectrumswich(Paspecumpwmt,MDdcs1800pim),Pimswich( Testmddcs1800 , Pimdetrxa)\n"\
"\n"\
"Dcs1800Bpim 	= Spectrumswich(Paspecumpwmt,MDdcs1800pim),Pimswich( Testmddcs1800 , Pimdetrxb)\n"\
"\n"\
"Pcs1900Apim 	= Spectrumswich(Paspecumpwmt,MDpcs1900pim),Pimswich( Testmdpcs1900  , Pimdetrxa)\n"\
"\n"\
"Pcs1900Bpim	= Spectrumswich(Paspecumpwmt,MDpcs1900pim),Pimswich( Testmdpcs1900  , Pimdetrxb)\n"\
"\n"\
"Wcdma2100Apim 	= Spectrumswich(Paspecumpwmt,MDwcdma2100pim),Pimswich( Testmdwcdma2100 , Pimdetrxa)\n"\
"\n"\
"Wcdma2100Bpim 	= Spectrumswich(Paspecumpwmt,MDwcdma2100pim),Pimswich( Testmdwcdma2100 , Pimdetrxb)\n"\
"\n"\
"Lte2600Apim 	= Spectrumswich(Paspecumpwmt,MDwcdma2600pim),Pimswich( Testmdlte2600  , Pimdetrxa)\n"\
"\n"\
"Lte2600Bpim 	= Spectrumswich(Paspecumpwmt,MDwcdma2600pim),Pimswich( Testmdlte2600  , Pimdetrxb)\n"\
"\n"\
"\n"\
"[actiondet]\n"\
"lte700tx1det  	= Powermeterswich(Paspecumpwmt,MDlte700pwmt),    Couplerswich( Testmdlte700,Powerdettx1)\n"\
"\n"\
"lte700tx2det  	= Powermeterswich(Paspecumpwmt,MDlte700pwmt),    Couplerswich( Testmdlte700,Powerdettx2)\n"\
"\n"\
"DD800tx1det   	= Powermeterswich(Paspecumpwmt,MDdd800tpwmt),    Couplerswich( Testmddd800,Powerdettx1)\n"\
"\n"\
"DD800tx2det   	= Powermeterswich(Paspecumpwmt,MDdd800tpwmt),    Couplerswich( Testmddd800,Powerdettx2)\n"\
"\n"\
"GSM900tx1det  	= Powermeterswich(Paspecumpwmt,MDgsm900pwmt),    Couplerswich( Testmdgsm900,Powerdettx1)\n"\
"\n"\
"GSM900tx2det  	= Powermeterswich(Paspecumpwmt,MDgsm900pwmt),    Couplerswich( Testmdgsm900,Powerdettx2)\n"\
"\n"\
"Dcs1800tx1det  	= Powermeterswich(Paspecumpwmt,MDdcs1800pwmt),   Couplerswich( Testmddcs1800,Powerdettx1)\n"\
"\n"\
"Dcs1800tx2det  	= Powermeterswich(Paspecumpwmt,MDdcs1800pwmt),   Couplerswich( Testmddcs1800,Powerdettx2)\n"\
"\n"\
"Pcs1900tx1det  	= Powermeterswich(Paspecumpwmt,MDpcs1900pwmt),   Couplerswich( Testmdpcs1900,Powerdettx1)\n"\
"\n"\
"Pcs1900tx2det  	= Powermeterswich(Paspecumpwmt,MDpcs1900pwmt),   Couplerswich( Testmdpcs1900,Powerdettx2)\n"\
"\n"\
"Wcdma2100tx1det	= Powermeterswich(Paspecumpwmt,MDwcdma2100pwmt), Couplerswich( Testmdwcdma2100,Powerdettx1)\n"\
"\n"\
"Wcdma2100tx2det	= Powermeterswich(Paspecumpwmt,MDwcdma2100pwmt), Couplerswich( Testmdwcdma2100,Powerdettx2)\n"\
"\n"\
"Lte2600tx1det 	= Powermeterswich(Paspecumpwmt,MDwcdma2600pwmt), Couplerswich( Testmdlte2600,Powerdettx1)\n"\
"\n"\
"Lte2600tx2det 	= Powermeterswich(Paspecumpwmt,MDwcdma2600pwmt), Couplerswich( Testmdlte2600,Powerdettx2)\n"\
""

#endif
