#pragma once

#include "shpa3api.h"
#include "Pbx_define.h"
#include "LVS_define.h"
#include "LVS_PID_Init.h"
#include <string>


BOOL IntiCtiBoard(LVS_VOID);
LVS_VOID IntiChList();
LVS_UINT32 LVS_PbxMsgProc(LVS_VOID *pMsg);
LVS_VOID UpdateChList(int nCh);
LVS_VOID UserProc(LVS_INT32 event, LVS_INT32 wParam, LVS_INT32 lParam);
LVS_VOID TrunkProc(LVS_INT32 event, LVS_INT32 wParam, LVS_INT32 lParam);
LVS_VOID ShowErrMsg(string lpszEventText, string lpszStatusText, string lpszFunctionText);







