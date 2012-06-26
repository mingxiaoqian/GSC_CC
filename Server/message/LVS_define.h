#pragma once

#include <iostream>
#include "stdio.h"
#include "Windows.h"
#include "Winbase.h"
#include <string.h>

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

typedef unsigned long  LVS_UINT32;
typedef signed long    LVS_INT32;
typedef unsigned short LVS_UINT16;
typedef signed short   LVS_INT16;
typedef unsigned char  LVS_UINT8;
typedef signed char    LVS_INT8;
typedef void           LVS_VOID;

typedef void *HANDLE;
typedef LVS_UINT32 (*LVS_PIDMsgProc)(LVS_VOID *pMsg);


#define LVS_MSG_HEADER_SIZE     24

typedef struct
{
	LVS_UINT32  ulSendPid;
	LVS_UINT32  ulReceivePid; 
	LVS_UINT32  ulMsgType;    /*消息类型*/
	LVS_UINT32  ulMsgId;		 /*消息ID*/
	LVS_UINT32  ulIsTimeConsuming;  /*消息是否耗时*/
	LVS_UINT32  ulMsgLen;     /*消息长度*/
	LVS_VOID    *pMsgData;		 /*消息体*/
	
}LVS_MSG_INFO_STRU;

typedef struct
{
	LVS_UINT32 ulPid;
	LVS_PIDMsgProc pfnMsgProc;
	
}LVS_PID_STRU;




