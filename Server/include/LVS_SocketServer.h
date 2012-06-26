#pragma once

#ifndef _LVS_SOCKET_SERVER_H
#define _LVS_SOCKET_SERVER_H

#include <cstdlib>
#include <winsock2.h>
#include <stdio.h>
#include <windows.h>
#include <iostream>
#include <process.h>
#include "LVS_define.h"
#include "LVSMsgList.h"

using namespace std;

#pragma comment(lib,"ws2_32.lib")

#define MAX_CLIENT_CONNECTION    256       /*���������*/
#define SERVER_PORT              6789	   /*����˿�*/
#define MAX_READ_BUFFER_SIZE     4096      /*����������С*/
#define MAX_WRITE_BUFFER_SIZE    4096      /*д��������С*/

class LVS_Socket_Server
{
	private:
		LVS_MessageQueue *pstSocketMsgList;
		HANDLE handleParseMsg;
		
	public:
		LVS_Socket_Server();
		~LVS_Socket_Server();
		LVS_UINT32 startProcess();
		LVS_UINT32 sendRespMsg(LVS_MSG_INFO_STRU *pstMsg);
};

extern LVS_Socket_Server *g_pServer;

LVS_UINT32 LVS_SendRespMsg(LVS_MSG_INFO_STRU *pstMsg);
LVS_UINT32 InitSocketServer();

#endif

