#pragma once

#include "LVS_define.h"
#include "Pbx_define.h"
#include "LVS_PID_Init.h"
#include <string>
#include "shpa3api.h"



BOOL IntiCtiBoard(LVS_VOID);
LVS_VOID IntiChList();
LVS_UINT32 LVS_PbxMsgProc(LVS_VOID *pMsg);
LVS_VOID UpdateChList(int nCh);
LVS_VOID UserProc(LVS_INT32 event, LVS_INT32 wParam, LVS_INT32 lParam);
LVS_VOID TrunkProc(LVS_INT32 event, LVS_INT32 wParam, LVS_INT32 lParam);
LVS_VOID ShowErrMsg(LPCTSTR lpszEventText, LPCTSTR lpszStatusText, LPCTSTR lpszFunctionText);
LVS_INT32 GetAnIdleUser();




