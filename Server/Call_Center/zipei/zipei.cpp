// zipei_v3.cpp : 定义控制台应用程序的入口点。
//
//

#pragma once
#include "stdafx.h"

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <windows.h>    // 头文件

#include "LVS_Call.h"
#include "lvs_log.h"
#include "lvs_reserve.h"
#include "LVS_IPTelNoBind.h"
//#include "LVS_SocketServer.h"

using namespace std;


extern LVS_UINT32 InitSocketServer();

int _tmain(int argc, _TCHAR* argv[])
{
	
	loadConfigInfoFromConfigFile();

	startRecordLogInfo();
	getThePrintSwitchKey();

	LVS_Message_Manager *pMsgManager = LVS_Message_Manager::CreateMsgManager();
    if(LVS_NULL_PTR == pMsgManager)
    {
        return LVS_OK;
    }
    pMsgManager->start();

	long lRet=QNV_OpenDevice(ODT_LBRIDGE,0,0);
	if(lRet == ERROR_INVALIDDLL) printf("DLL不合法");
	else if(lRet <= 0 || QNV_DevInfo(0,QNV_DEVINFO_GETCHANNELS) <= 0)
	{
		printf("打开设备失败,请检查设备是否已经插入并安装了驱动,并且没有其它程序已经打开设备\r\n");
	}else
	{		
		InitDevInfo();
	}

    //InitTaskReserveService();
    InitSocketServer();
    
	system("pause");
	return 0;
}

