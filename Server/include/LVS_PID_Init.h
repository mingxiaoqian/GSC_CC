#pragma once
#include "LVS_define.h"


/*定义PID的编号*/
#define PID_STUB_TEST             1000
#define PID_VOICE_PROXY           1001
#define PID_SOCKET_MSG_PROXY      1002
#define PID_TASK_TESERVE_PROXY    1003

/*申明PID的消息处理函数*/
LVS_UINT32 MsgProc_Stub(LVS_VOID *pMsg);

extern LVS_UINT32 LVS_CallMsgProc(LVS_VOID *pMsg);
extern LVS_UINT32 LVS_ClientMsgProc(LVS_VOID *pMsg);
extern LVS_UINT32 TaskReserveMsgProc(LVS_VOID *pMsg);

#ifndef LVS_MESSAGE_PID_LIST
#define LVS_MESSAGE_PID_LIST {\
							 {PID_VOICE_PROXY,LVS_CallMsgProc},\
							 {PID_SOCKET_MSG_PROXY,LVS_ClientMsgProc},\
							 {PID_TASK_TESERVE_PROXY,TaskReserveMsgProc},\
							 }
#endif

