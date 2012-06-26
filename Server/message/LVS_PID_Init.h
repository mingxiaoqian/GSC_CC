#pragma once
#include "LVS_define.h"
#include "Pbx.h"

/*定义PID的编号*/
#define PID_STUB_TEST         1000
#define PID_VOICE_PROXY       1001

/*申明PID的消息处理函数*/
LVS_UINT32 MsgProc_Stub(LVS_VOID *pMsg);


#ifndef LVS_MESSAGE_PID_LIST
#define LVS_MESSAGE_PID_LIST {\
							 {PID_STUB_TEST,MsgProc_Stub},\
							 {PID_VOICE_PROXY, LVS_PbxMsgProc},\
							 }
#endif

