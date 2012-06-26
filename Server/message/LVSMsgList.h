#pragma once

#include "LVS_define.h"

#define QUEUE_SIZE    1000    /*消息队列中元素的最大个数*/
#define ARRAY_SIZE    (QUEUE_SIZE + 1)


class LVS_MessageQueue
{
private:
	LVS_MSG_INFO_STRU g_LVS_stMessageQueue[ARRAY_SIZE];
	LVS_UINT32 sFront;
	LVS_UINT32 sRear;
	LVS_UINT32 ulMsgListOperateFlag;

public:
	LVS_MessageQueue();
	~LVS_MessageQueue();
	LVS_UINT32 LVSMsglistlnsert(LVS_MSG_INFO_STRU *pstValue);   /*Insert*/
	LVS_UINT32 LVSMsglistDelete(LVS_MSG_INFO_STRU **pstValue); /*Delete*/
	LVS_UINT32 LVSMsglistFirst(LVS_MSG_INFO_STRU **pstValue);   /*First*/
	LVS_UINT32 LVSMsglistIsEmpty(LVS_VOID);
	LVS_UINT32 LVSMsglistIsFull(LVS_VOID);
	LVS_UINT32 LVSCurMsgIsTimeConsuming(LVS_VOID);
};


