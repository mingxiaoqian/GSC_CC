#pragma once

#ifndef _LVS_DEFINE_H
#define _LVS_DEFINE_H

#include <cstdlib>
#include <iostream>
#include "stdio.h"
#include "Windows.h"
#include "Winbase.h"
#include <string>
#include "LVS_Color.h"

using namespace std;

#define LVS_OK       0
#define LVS_ERR      1
#define LVS_TRUE     1
#define LVS_FALSE    0
//#define NULL         (0L)

#define LVS_NULL_LONG 0xffffffff
#define LVS_NULL_WORD 0xffff
#define LVS_NULL_BYTE 0xff
#define LVS_NULL_PTR  NULL

#define LVS_SEND_ALL  0xf10a0b0c

typedef unsigned long  LVS_UINT32;
typedef signed long    LVS_INT32;
typedef unsigned short LVS_UINT16;
typedef signed short   LVS_INT16;
typedef unsigned char  LVS_UINT8;
typedef signed char    LVS_INT8;
typedef void           LVS_VOID;

typedef void *HANDLE;
typedef LVS_UINT32 (*LVS_PIDMsgProc)(LVS_VOID *pMsg);

typedef unsigned (WINAPI *PBEGINTHREADEX_THREADFUNC)(LPVOID lpThreadParameter);
typedef unsigned *PBEGINTHREADEX_THREADID;


#define LVS_MSG_HEADER_SIZE     28

typedef struct
{
	LVS_INT32   lSocketId;
	LVS_UINT32  ulSendPid;
	LVS_UINT32  ulReceivePid; 
	LVS_UINT32  ulMsgType;    /*��Ϣ����*/
	LVS_UINT32  ulMsgId;		 /*��ϢID*/
	LVS_UINT32  ulIsTimeConsuming;  /*��Ϣ�Ƿ��ʱ,0 ��ʾ�����£�1 ��ʾ��ʱ*/
	LVS_UINT32  ulMsgLen;     /*��Ϣ����*/
	LVS_VOID    *pMsgData;		 /*��Ϣ��*/
	
}LVS_MSG_INFO_STRU;

typedef struct
{
	LVS_UINT32 ulPid;
	LVS_PIDMsgProc pfnMsgProc;
	
}LVS_PID_STRU;

///////////////////////////////////////////////
//*******		STRUCTURE DEFINITION		***************
///////////////////////////////////////////////
enum LVS_MESSAGE_TYPE
{
	LVS_MSG_TYPE_DRIVE,        //�����¼���Ϣ
	LVS_MSG_TYPE_USER,         //�û��Զ�����Ϣ
	LVS_MSG_TYPE_SOCKET,       //socket��Ϣ
	LVS_MSG_TYPE_Timer,		   //��ʱ����Ϣ
	LVS_MSG_TYPE_BUTT,
};

//��ǲȷ����Ϣ
#define ClientEvent_Dispatch_affirm     (LVS_UINT32)1;

//��Ա������ƴ������ĸ����Ա����Ϣ
#define ClientEvent_Query_Staff_Info 	(LVS_UINT32)2;

//����ǲ����ƴ������ĸ������ǲ����
#define ClientEvent_Query_Task_Type		(LVS_UINT32)3;


/*�ṩ��������ʹ��*/
LVS_UINT32 LVS_SendMsg(LVS_MSG_INFO_STRU *pstValue);

void printTime();
void printString(string str, unsigned short color_index, unsigned short sIsUTF8);
string changeLongToString(long iValue);
LVS_UINT32 changeStringToUlong(string str);
string getCurrentTimeAsString();
int getThePrintSwitchKey();
string allTrim(string strIpt);


#endif

