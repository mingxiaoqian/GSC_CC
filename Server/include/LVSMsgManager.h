#pragma once

#include <cstdlib>
#include <windows.h>
#include <process.h>
#include "LVS_define.h"
#include "LVSMsgList.h"


#define LVS_MSG_PID_MAX_NUM       100	/*�����ע���PID ��*/
#define MAX_THREAD_NUMBER         10    /*����߳���*/



class LVS_Message_Manager
{
	private:
		LVS_UINT32 ulTransId;
		//static const LVS_UINT32 ulMaxCaseNum = LVS_MAX_Msg_Manager_Num;
		static LVS_UINT32 ulCaseNum;	/*ʵ������Message Manager ����*/
		
		static LVS_MessageQueue *pMessageQueue_Normal;        /*��Ϣ����*/
		static LVS_MessageQueue *pMessageQueue_TimeConsuming; /*��ʱ��Ϣ����*/
		static LVS_UINT32 ulMsgLock_Normal;
		static LVS_UINT32 ulMsgLock_TimeConsuming;

		static LVS_UINT32 ulListNum;    /*�Ѿ�ע���PID�ܸ���*/
		static LVS_PID_STRU stMsgPidList[];
		
		LVS_UINT32 ulThreadNum_Normal;        /*����һ����Ϣ���̸߳���*/
		LVS_UINT32 ulThreadNum_TimeConsuming; /*�����ʱ������̸߳���*/

		HANDLE hThread[MAX_THREAD_NUMBER];
		LVS_UINT32 ulThreadID[MAX_THREAD_NUMBER];
		
		LVS_Message_Manager();
		LVS_Message_Manager(LVS_UINT32 fastThreadNum, LVS_UINT32 slowThreadNum);
		LVS_UINT32 InitMemberParameter(LVS_UINT32 fastThreadNum, LVS_UINT32 slowThreadNum);
		//LVS_VOID StartProcessMsg__Normal(LVS_VOID);
		//LVS_VOID StartProcessMsg__TimeConsuming(LVS_VOID);
		LVS_VOID StartProcessMsg(LVS_UINT32 ulIsTimeConsuming);
		static unsigned __stdcall agent__Normal(void *p);
		static unsigned __stdcall agent__TimeConsuming(void *p);
	public:
		~LVS_Message_Manager();
		static LVS_Message_Manager* CreateMsgManager(LVS_VOID);
		static LVS_Message_Manager* CreateMsgManager(LVS_UINT32 fastThreadNum, LVS_UINT32 slowThreadNum);
		//static LVS_UINT32 RegisterMsgPid(LVS_PID_STRU stMsgPid);
		//static LVS_UINT32 RegisterMsgPidEx();
		void start();
	    virtual void run__Normal();
		virtual void run__TimeConsuming();
		
		void printThreadStatus();
		void waitForProcessThread();
		void waitForProcessThread(DWORD dwMillisecond);
		
		/*������Ϣ����Ϣ����Ч���ɵ����߱�֤��*/
		static LVS_UINT32 sendMsg(LVS_MSG_INFO_STRU *pstValue);
		
};


