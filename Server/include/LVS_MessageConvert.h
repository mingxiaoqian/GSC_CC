#pragma once

#ifndef _LVS_MESSAGE_CONVERT_H
#define _LVS_MESSAGE_CONVERT_H

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <hash_map>
#include <string>
#include <process.h>

#include "json\json.h"
#include "LVS_define.h"

using namespace std;

#define MSG_HEAD "HEAD"
#define MSG_END  "END"
#define MSG_HEAD_SIZE 4
#define MSG_END_SIZE  3
#define MSG_LENGSTRING_SIZE 4

#define MSG_TYPE_KEY_STRING         "msgType"
#define MSG_TYPE_PHONE_NUMBER       "phoneNumber"
#define MSG_TYPE_USERID      		"userId"
#define MSG_TYPE_DEPARTMENT 		"department"
#define MSG_TYPE_DATETIME 			"datetime"
#define MSG_TYPE_USER_NUMBER 		"userNumber"
#define MSG_TYPE_NAME 				"name"
#define MSG_TYPE_POST 				"post"
#define MSG_TYPE_CALL_NUMBER 		"callNumber"
#define MSG_TYPE_STAFF_STATE 		"staffState"
#define MSG_TYPE_NAMESPELL 			"nameSpell"
#define MSG_TYPE_TASK_ID            "taskId"
#define MSG_TYPE_TASK_NAME			"taskName"
#define MSG_TYPE_TASK_TYPE 			"taskType"
#define MSG_TYPE_TASK_INFO			"taskInfo"
#define MSG_TYPE_TASK_STATE 		"taskState"
#define MSG_TYPE_STAFF_INFO         "staffInfo"
#define MSG_TYPE_IS_RESERVE			"isReserve"
#define MSG_TYPE_RESERVE_TIME		"reserveTime"
#define MSG_TYPE_TASK_TIME			"taskTime"
#define MSG_TYPE_STAFF_NAME			"staffName"
#define MSG_TYPE_DISPATCHER_ID		"dispatcherId"
#define MSG_TYPE_DISPATCHER_NAME	"dispatcherName"
#define MSG_TYPE_VIEW_TASK_LIST		"viewTaskList"
#define MSG_TYPE_START_DATE         "startDate"
#define MSG_TYPE_END_DATE           "endDate"
#define MSG_TYPE_RESERVE_ID			"reserveId"




/*ö�ٶ���*/
/*�ͻ��������˷��͵�������ϢID*/
typedef enum

{
	DOWN_MSG_TYPE_QUERY_STAFF_INFO_REQUEST 			= 2001,  /*��ѯԱ����Ϣ����*/
	DOWN_MSG_TYPE_UPDATE_CALLER_INFO       			= 2002,  /*������������Ϣ*/
	DOWN_MSG_TYPE_TASK_DISPATCH 		   			= 2003,  /*������ǲ��Ϣ*/
	DOWN_MSG_TYPE_RESERVE_INFO  		   			= 2004,	 /*ԤԼ������Ϣ*/
	DOWN_MSG_TYPE_VIEW_TASK_LIST_BETWEEN_S_AND_E	= 2005,  /*�鿴ĳ����֮������������¼��S-start, E-end*/
	DOWN_MSG_TYPE_GET_TASK_INFO			   			= 2006,	 /*��������������Ϣ*/
	DOWN_MSG_TYPE_ADD_ONE_TASK_INFO					= 2007,  /*����һ������������Ϣ*/
	DOWN_MSG_TYPE_HEAT_BEAT 			   			= 2008,	 /*������Ϣ*/
	
	DOWN_MSG_TYPE_BUTT
}LVS_DOWN_MESSAGE_TYPE_ID;
/*�������ͻ��˷��͵�������ϢID*/
typedef enum
{
	UP_MSG_TYPE_DIALOG_POP		 				= 1001,         /*������Ϣ*/
	UP_MSG_TYPE_PHONE_NUMBER 					= 1002,			/*�绰������Ϣ*/
	UP_MSG_TYPE_CALLER_INFO 					= 1003,			/*��������Ϣ*/
	UP_MSG_TYPE_STAFF_INFO 						= 1004,			/*Ա����Ϣ*/
	UP_MSG_TYPE_STOP_CALLIN 					= 1005,			/*���緽�һ���ֹͣ����*/
	UP_MSG_TYPE_TASK_LIST_BETWEEN_S_AND_E 		= 1006,			/*ĳ���������е�������Ϣ��S-start, E-end */
	UP_MSG_TYPE_RESERVE_INFO					= 1007,			/*ԤԼʱ�䵽�ˣ�����ԤԼ��Ϣ���ͻ���*/			
	UP_MSG_TYPE_GET_ALL_TASK_INFO				= 1008,			/*�����������������б�*/
	UP_MSG_TYPE_RESP_HEAT_BEAT 					= 1010,   	    /*��Ӧ������Ϣ*/
	UP_MSG_TYPE_BUTT											/*����*/
}LVS_UP_MESSAGE_TYPE_ID;


/*�ӿ�����*/

string parseIntToString(int iValue);
LVS_UINT32 parseStringToInt(string str);

LVS_UINT32 receiveServerMsg(const char *acMsgBuff, LVS_INT32 socketId);
HANDLE startParseDownMsgThread();
LVS_UINT32 closeParseDownMsgThread(HANDLE handle);
LVS_UINT32 packToJsonStringAndSend(LVS_MSG_INFO_STRU *pstMsg);

#endif

