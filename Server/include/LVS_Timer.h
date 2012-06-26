#pragma once

#ifndef _LVS_TIMER_H
#define _LVS_TIMER_H

#include "LVS_define.h"

typedef struct tagTIMER_INFO_STRU
{
    HANDLE handleTimer;     /*定时器句柄*/
    UINT uTimerid;          /*定时器ID*/
	UINT uElapse;           /*定时器时间*/
	UINT uTimerMsgId;       /*定时器消息类型*/
	UINT uIsLoop;			/*是否是循环定时器*/
	UINT uModulePid; /*模块的PID*/
	UINT uIsTimeConsuming;
    UINT uDataLength;       /*参数长度*/
	void *pTimerData;       /*参数*/
}TIMER_INFO_STRU;

LVS_UINT32 LVS_StartTimer(TIMER_INFO_STRU *pstTimerInfo);
LVS_UINT32 LVS_CloseTimer(TIMER_INFO_STRU *pstTimerInfo);


#endif

