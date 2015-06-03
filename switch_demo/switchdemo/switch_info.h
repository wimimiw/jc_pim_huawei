#ifndef __SWITCH_CONFIG_H__
#define __SWITCH_CONFIG_H__
#define IO_STRING	         "[STATE]\n"\
"//铁塔POI测试平台\n"\
"//*********//\n"\
"//开关箱1\n"\
"//开关1 \n"\
"//通道1-->0\n"\
"//通道2-->1\n"\
"//通道3-->2\n"\
"//通道4-->3\n"\
"[Signal1swich]\n"\
"0=0,0,0,0,2,\n"\
"1=0,0,0,0,1,\n"\
"2=0,512,0,0,0,\n"\
"3=0,256,0,0,0,\n"\
"//开关2 \n"\
"//通道1-->10\n"\
"//通道2-->11\n"\
"//通道3-->12\n"\
"//通道4-->13\n"\
"[Signal2swich]\n"\
"10=0,0,0,16,0,\n"\
"11=0,0,0,8,0,\n"\
"12=0,0,0,4,0,\n"\
"13=0,0,0,2,0,\n"\
"//*********//\n"\
"\n"\
"//*********//\n"\
"//开关箱2\n"\
"//开关3 \n"\
"//通道1-->0\n"\
"//通道2-->1\n"\
"//通道3-->2\n"\
"//通道4-->3\n"\
"//通道5-->4\n"\
"//通道6-->5\n"\
"//通道7-->6\n"\
"[Spectrumswich]\n"\
"0=0,0,0,0,2,\n"\
"1=0,0,0,0,1,\n"\
"2=0,512,0,0,0,\n"\
"3=0,256,0,0,0,\n"\
"4=0,32,0,0,0,\n"\
"5=0,16,0,0,0,\n"\
"6=0,8,0,0,0,\n"\
"//开关4 \n"\
"//通道1-->10\n"\
"//通道2-->11\n"\
"//通道3-->12\n"\
"//通道4-->13\n"\
"//通道5-->14\n"\
"//通道6-->15\n"\
"//通道3-->16\n"\
"[Powermeterswich]\n"\
"10=0,0,0,16,0,\n"\
"11=0,0,0,8,0,\n"\
"12=0,0,0,4,0,\n"\
"13=0,0,0,2,0,\n"\
"14=0,0,0,1,0,\n"\
"15=0,0,4096,0,0,\n"\
"16=0,0,2048,0,0,\n"\
"//开关5 \n"\
"//通道1-->20\n"\
"//通道2-->21\n"\
"//通道3-->22\n"\
"//通道4-->26\n"\
"[PA2swich1]\n"\
"20=16,0,0,0,0,\n"\
"21=32,0,0,0,0,\n"\
"22=64,0,0,0,0,\n"\
"23=0,1,0,0,0,\n"\
"//开关6 \n"\
"//通道1-->23\n"\
"//通道2-->24\n"\
"//通道3-->25\n"\
"//通道4-->27\n"\
"[PA2swich2]\n"\
"23=128,0,0,0,0,\n"\
"24=0,0,16,0,0,\n"\
"25=0,0,32,0,0,\n"\
"26=0,2,0,0,0,\n"\
"//*********//\n"\
"\n"\
"//*********//\n"\
"//开关箱3\n"\
"//开关1\n"\
"//通道1-->21\n"\
"//通道2-->20\n"\
"[Couplerswich2]\n"\
"21=16,0,0,0,0,\n"\
"20=32,0,0,0,0,\n"\
"//开关2\n"\
"//通道1-->24\n"\
"//通道2-->23\n"\
"[Pimswich1]\n"\
"24=128,0,0,0,0,\n"\
"23=0,0,16,0,0,\n"\
"//开关3\n"\
"//通道1-->27\n"\
"//通道2-->26\n"\
"[Tx1swich3]\n"\
"27=0,1,0,0,0,\n"\
"26=0,2,0,0,0,\n"\
"//开关4\n"\
"//通道1-->29\n"\
"//通道2-->28\n"\
"[Tx2swich4]\n"\
"29=0,0,0,0,1024,\n"\
"28=0,0,0,0,2048,\n"\
"//开关5\n"\
"//通道1-->32\n"\
"//通道2-->31\n"\
"[Antmodeswich5]\n"\
"32=0,0,0,0,8192,\n"\
"31=0,0,0,0,16384,\n"\
"//开关6\n"\
"//通道1-->35\n"\
"//通道2-->34\n"\
"[Antmodeswich6]\n"\
"35=0,1024,0,0,0,\n"\
"34=0,2048,0,0,0,\n"\
"//*********//\n"\
"[ABC]\n"\
"//以电源输入为左边，有8芯插座一边为上方，每个插座内每芯计数从左到右\n"\
"//上排左数第1个插座（8芯）J15 1-7\n"\
"0=0,0,0,0,2,\n"\
"1=0,0,0,0,1,\n"\
"2=0,512,0,0,0,\n"\
"3=0,256,0,0,0,\n"\
"4=0,32,0,0,0,\n"\
"5=0,16,0,0,0,\n"\
"6=0,8,0,0,0,\n"\
"//上排左数第2个插座（4芯）J3 1-3\n"\
"7=0,0,0,128,0,\n"\
"8=0,0,0,64,0,\n"\
"9=0,0,0,32,0,\n"\
"//上排左数第3个插座（8芯）J16 1-7\n"\
"10=0,0,0,16,0,\n"\
"11=0,0,0,8,0,\n"\
"12=0,0,0,4,0,\n"\
"13=0,0,0,2,0,\n"\
"14=0,0,0,1,0,\n"\
"15=0,0,4096,0,0,\n"\
"16=0,0,2048,0,0,\n"\
"//上排左数第4个插座J4（4芯） 1-3\n"\
"17=0,0,1024,0,0,\n"\
"18=32768,0,0,0,0,\n"\
"19=16384,0,0,0,0,\n"\
"//下排左数第1个插座J5（4芯） 1-3\n"\
"20=16,0,0,0,0,\n"\
"21=32,0,0,0,0,\n"\
"22=64,0,0,0,0,\n"\
"//下排左数第2个插座J6（4芯） 1-3\n"\
"23=128,0,0,0,0,\n"\
"24=0,0,16,0,0,\n"\
"25=0,0,32,0,0,\n"\
"//下排左数第3个插座J7（4芯） 1-2\n"\
"26=0,1,0,0,0,\n"\
"27=0,2,0,0,0,\n"\
"//下排左数第4个插座J8（8芯） 1-3\n"\
"28=0,0,0,0,1024,\n"\
"29=0,0,0,0,2048,\n"\
"30=0,0,0,0,4096,\n"\
"//下排左数第5个插座J9（4芯） 1-3\n"\
"31=0,0,0,0,8192,\n"\
"32=0,0,0,0,16384,\n"\
"33=0,0,0,0,32768,\n"\
"//下排左数第6个插座J10（4芯） 1-2\n"\
"34=0,1024,0,0,0,\n"\
"35=0,2048,0,0,0,\n"\
"\n"\
""
#define IMPLEMENT_STRING  "[ip]\n"\
"namelist =Signalswich,Paspecumpwmt,Testmdcdmagsm,Testmdfdd18,Testmdfdd21,Testmdtdftda,Testmdtdd23\n"\
"Signalswich       =192.168.1.81:4001\n"\
"Paspecumpwmt      =192.168.1.82:4001\n"\
"Testmdcdmagsm     =192.168.1.91:4001\n"\
"Testmdfdd18       =192.168.1.92:4001\n"\
"Testmdfdd21       =192.168.1.92:4001\n"\
"Testmdtdftda      =192.168.1.93:4001\n"\
"Testmdtdd23       =192.168.1.94:4001\n"\
"\n"\
"[switch]\n"\
"namelist = Signal1swich,Signal2swich,PA2swich1,PA2swich2,Spectrumswich,Powermeterswich,Couplerswich2,Pimswich1,Tx1swich3,Tx2swich4,Antmodeswich5,Antmodeswich6\n"\
"Signal1swich =PA1in1,PA2in1,PA3in1,PA4in1\n"\
"PA1in1=1\n"\
"PA2in1=2\n"\
"PA3in1=3\n"\
"PA4in1=4\n"\
"Signal2swich =PA1in2,PA2in2,PA3in2,PA4in2\n"\
"PA1in2=1\n"\
"PA2in2=2\n"\
"PA3in2=3\n"\
"PA4in2=4\n"\
"PA2swich1    =fdd18tx1,fdd21tx1,tdftdatx1\n"\
"fdd18tx1=1\n"\
"fdd21tx1=2\n"\
"tdftdatx1=3\n"\
"PA2swich2    =fdd18tx2,fdd21tx2,tdftdatx2,tdftdatx3\n"\
"fdd18tx2=1\n"\
"fdd21tx2=2\n"\
"tdftdatx2=3\n"\
"tdftdatx3=4\n"\
"Spectrumswich    =cdmagsmpim,fdd18pim,fdd21pim,tdftdapim,bak,tdd23pim\n"\
"cdmagsmpim=1\n"\
"fdd18pim=2\n"\
"fdd21pim=3\n"\
"tdftdapim=4\n"\
"bak=5\n"\
"tdd23pim=6\n"\
"Powermeterswich  =cdmagsmpwmt,fdd18pwmt,fdd21pwmt,tdftdapwmt,tdftdapwmt2,tdd23pwmt\n"\
"cdmagsmpwmt=1\n"\
"fdd18pwmt=2\n"\
"fdd21pwmt=3\n"\
"tdftdapwmt=4\n"\
"tdftdapwmt2=5\n"\
"tdd23pwmt=6\n"\
"Couplerswich2    =nc1,no2\n"\
"Pimswich1        =nc1,no2\n"\
"Tx1swich3        =nc1,no2\n"\
"Tx2swich4        =nc1,no2\n"\
"Antmodeswich5    =nc1,no2\n"\
"Antmodeswich6    =nc1,no2\n"\
"nc1 = 1\n"\
"no2 = 2\n"\
"\n"\
"[actiontx1]\n"\
"namelist = 1Cmgsmtx1,2Cucdmatx1,3Ctfd18tx1,4Cufd18tx1,5Ctfd21tx1,6Cuw21tx1,7Cmdcstx1,8Cmtdftx1,10Cmtdetx1,11Cttdetx1\n"\
"\n"\
"1Cmgsmtx1= Signal1swich(Signalswich,PA1in1), Tx1swich3(Testmdcdmagsm , nc1)\n"\
"2Cucdmatx1= Signal1swich(Signalswich,PA1in1), Tx1swich3(Testmdcdmagsm , no2)\n"\
"3Ctfd18tx1= Signal1swich(Signalswich,PA2in1), PA2swich1(Paspecumpwmt,fdd18tx1), Tx1swich3(Testmdfdd18, nc1)   \n"\
"4Cufd18tx1= Signal1swich(Signalswich,PA2in1), PA2swich1(Paspecumpwmt,fdd18tx1), Tx1swich3(Testmdfdd18, no2)\n"\
"5Ctfd21tx1= Signal1swich(Signalswich,PA2in1), PA2swich1(Paspecumpwmt,fdd21tx1), Tx1swich3(Testmdfdd21, nc1)    \n"\
"6Cuw21tx1= Signal1swich(Signalswich,PA2in1), PA2swich1(Paspecumpwmt,fdd21tx1), Tx1swich3(Testmdfdd21 , no2)    \n"\
"7Cmdcstx1= Signal1swich(Signalswich,PA2in1), PA2swich1(Paspecumpwmt,tdftdatx1), Tx1swich3(Testmdtdftda , nc1)  \n"\
"8Cmtdftx1= Signal1swich(Signalswich,PA2in1), PA2swich1(Paspecumpwmt,tdftdatx1), Tx1swich3(Testmdtdftda , no2)  \n"\
"10Cmtdetx1= Signal1swich(Signalswich,PA3in1), Tx1swich3(Testmdtdd23, nc1),Antmodeswich6(Testmdtdd23,nc1)      \n"\
"11Cttdetx1= Signal1swich(Signalswich,PA3in1), Tx1swich3(Testmdtdd23, no2), Antmodeswich5(Testmdtdd23,nc1)      \n"\
"\n"\
"[actiontx2]\n"\
"namelist = 1Cmgsmtx2,2Cucdmatx2,3Ctfd18tx2,4Cufd18tx2,5Ctfd21tx2,6Cuw21tx2,7Cmdcstx2,8Cmtdftx2,9Cmtdatx2,10Cmtdetx2,12Cutdetx2\n"\
"\n"\
"1Cmgsmtx2= Signal2swich(Signalswich,PA1in2),  Tx2swich4(Testmdcdmagsm , nc1)   \n"\
"2Cucdmatx2= Signal2swich(Signalswich,PA1in2), Tx2swich4(Testmdcdmagsm , no2)\n"\
"3Ctfd18tx2= Signal2swich(Signalswich,PA2in2), PA2swich2(Paspecumpwmt,fdd18tx2), Tx2swich4(Testmdfdd18, nc1)    \n"\
"4Cufd18tx2= Signal2swich(Signalswich,PA2in2), PA2swich2(Paspecumpwmt,fdd18tx2), Tx2swich4(Testmdfdd18, no2) \n"\
"5Ctfd21tx2= Signal2swich(Signalswich,PA2in2), PA2swich2(Paspecumpwmt,fdd21tx2), Tx2swich4(Testmdfdd21, nc1)     \n"\
"6Cuw21tx2= Signal2swich(Signalswich,PA2in2),  PA2swich2(Paspecumpwmt,fdd21tx2), Tx2swich4(Testmdfdd21, no2)    \n"\
"7Cmdcstx2= Signal2swich(Signalswich,PA2in2),  PA2swich2(Paspecumpwmt,tdftdatx2),Tx2swich4(Testmdtdftda, nc1)   \n"\
"8Cmtdftx2= Signal2swich(Signalswich,PA2in2),  PA2swich2(Paspecumpwmt,tdftdatx2),Tx2swich4(Testmdtdftda, no2), Antmodeswich5(Testmdtdftda,nc1)\n"\
"9Cmtdatx2= Signal2swich(Signalswich,PA2in2),  PA2swich2(Paspecumpwmt,tdftdatx3)                                 \n"\
"10Cmtdetx2= Signal2swich(Signalswich,PA3in2), Tx2swich4(Testmdtdd23, nc1),Antmodeswich6(Testmdtdd23,nc1)       \n"\
"12Cutdetx2= Signal2swich(Signalswich,PA3in2), Tx2swich4(Testmdtdd23, no2)\n"\
"\n"\
"[actiondet]\n"\
"namelist = Cdmagsmcp1,Cdmagsmcp2,fdd18cp1,fdd18cp2,fdd21cp1,fdd21cp2,tdftdacp1,tdftdacp2,tdftdacp3,tde23cp1,tde23cp2\n"\
"\n"\
"Cdmagsmcp1= Powermeterswich(Paspecumpwmt,cdmagsmpwmt), Couplerswich2(Testmdcdmagsm,nc1)\n"\
"Cdmagsmcp2= Powermeterswich(Paspecumpwmt,cdmagsmpwmt), Couplerswich2(Testmdcdmagsm,no2)\n"\
"\n"\
"fdd18cp1= Powermeterswich(Paspecumpwmt,fdd18pwmt), Couplerswich2(Testmdfdd18,nc1)\n"\
"fdd18cp2= Powermeterswich(Paspecumpwmt,fdd18pwmt), Couplerswich2(Testmdfdd18,no2)\n"\
"\n"\
"fdd21cp1= Powermeterswich(Paspecumpwmt,fdd21pwmt), Couplerswich2(Testmdfdd21,nc1)\n"\
"fdd21cp2= Powermeterswich(Paspecumpwmt,fdd21pwmt), Couplerswich2(Testmdfdd21,no2)\n"\
"\n"\
"tdftdacp1= Powermeterswich(Paspecumpwmt,tdftdapwmt), Couplerswich2(Testmdtdftda,nc1)\n"\
"tdftdacp2= Powermeterswich(Paspecumpwmt,tdftdapwmt), Couplerswich2(Testmdtdftda,no2)\n"\
"\n"\
"tdftdacp3= Powermeterswich(Paspecumpwmt,tdftdapwmt2)\n"\
"\n"\
"tde23cp1= Powermeterswich(Paspecumpwmt,tdftdapwmt), Couplerswich2(Testmdtdftda,nc1)\n"\
"tde23cp2= Powermeterswich(Paspecumpwmt,tdftdapwmt), Couplerswich2(Testmdtdftda,no2)\n"\
"\n"\
"[actionpim]\n"\
"namelist = gsmpim,cdmapim,ctfd18pim,cufd18pim,ctfd21pim,cuw21pim,cmdcspim,cmtdfpim,cmtde23pim,cttde23pim\n"\
"\n"\
"gsmpim=  Spectrumswich(Paspecumpwmt,cdmagsmpim), Pimswich1(Testmdcdmagsm,nc1)\n"\
"cdmapim= Spectrumswich(Paspecumpwmt,cdmagsmpim), Pimswich1(Testmdcdmagsm,no2)\n"\
"\n"\
"ctfd18pim= Spectrumswich(Paspecumpwmt,fdd18pim), Pimswich1(Testmdfdd18,nc1)\n"\
"cufd18pim= Spectrumswich(Paspecumpwmt,fdd18pim), Pimswich1(Testmdfdd18,no2)\n"\
"\n"\
"ctfd21pim= Spectrumswich(Paspecumpwmt,fdd21pim), Pimswich1(Testmdfdd21,nc1)\n"\
"cuw21pim= Spectrumswich(Paspecumpwmt,fdd21pim), Pimswich1(Testmdfdd21,no2)\n"\
"\n"\
"cmdcspim= Spectrumswich(Paspecumpwmt,tdftdapim), Pimswich1(Testmdtdftda,nc1)\n"\
"cmtdfpim= Spectrumswich(Paspecumpwmt,tdftdapim), Pimswich1(Testmdtdftda,no2)\n"\
"\n"\
"cmtde23pim= Spectrumswich(Paspecumpwmt,tdd23pim), Pimswich1(Testmdtdd23,nc1)\n"\
"cttde23pim= Spectrumswich(Paspecumpwmt,tdd23pim), Pimswich1(Testmdtdd23,no2)\n"\
"\n"\
"\n"\
"\n"\
"\n"\
"\n"\
"\n"\
"\n"\
"\n"\
"\n"\
"\n"\
"\n"\
"\n"\
"\n"\
"\n"\
"\n"\
"\n"\
""

#endif
