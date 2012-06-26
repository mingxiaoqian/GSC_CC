#pragma once

#ifndef _LVS_CALL_H_1234
#define _LVS_CALL_H_1234

#ifndef WINAPI
#define WINAPI _stdcall
#endif

#include "BriSDKLib.h"
#include "BriChipErr.h"
#include "LVSMsgManager.h"
#include "LVS_PID_Init.h"
#include "LVS_MessageConvert.h"
#include "LVS_Message_Struct_define.h"
#include "LVS_Mysql.h"
#include "LVS_reserve.h"

#pragma comment(lib,"qnviccub.lib")

BRIINT32 WINAPI myCallBack(BRIINT16 uChannelID,BRIUINT32 dwUserData,BRIINT32 lType,BRIINT32 lHandle,BRIINT32 lResult,BRIINT32 lParam,BRIPCHAR8 pData,BRIPCHAR8 pDataEx);
//BRIINT32 WINAPI myCallBack(PBRI_EVENT pEvent);
void InitDevInfo();

LVS_UINT32 LVS_CallMsgProc(LVS_VOID *pMsg);

#endif