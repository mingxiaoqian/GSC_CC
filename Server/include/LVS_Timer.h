#pragma once

#ifndef _LVS_TIMER_H
#define _LVS_TIMER_H

#include "LVS_define.h"

typedef struct tagTIMER_INFO_STRU
{
    HANDLE handleTimer;     /*��ʱ�����*/
    UINT uTimerid;          /*��ʱ��ID*/
	UINT uElapse;           /*��ʱ��ʱ��*/
	UINT uTimerMsgId;       /*��ʱ����Ϣ����*/
	UINT uIsLoop;			/*�Ƿ���ѭ����ʱ��*/
	UINT uModulePid; /*ģ���PID*/
	UINT uIsTimeConsuming;
    UINT uDataLength;       /*��������*/
	void *pTimerData;       /*����*/
}TIMER_INFO_STRU;

LVS_UINT32 LVS_StartTimer(TIMER_INFO_STRU *pstTimerInfo);
LVS_UINT32 LVS_CloseTimer(TIMER_INFO_STRU *pstTimerInfo);


#endif

