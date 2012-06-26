
#pragma once

#ifndef _LVS_MESSAGE_STRUCT_DEFINE_H
#define _LVS_MESSAGE_STRUCT_DEFINE_H


typedef struct
{
	char phoneNumber[32];
}CC_PHONE_NUMBER_INFO_STRU;

typedef struct
{
	unsigned long userId;
	unsigned long taskId;
	char phoneNumber[32];
	char name[32];
	char department[64];
	char datetime[64];
	unsigned long telChannelId;   /*����ͨ����־��0-Ϊ0ͨ����1-Ϊ1ͨ�����Դ����ƣ�������ֹ������������Ϊ�ա�*/
}CC_CALLER_INFO_STRU;

typedef struct
{
	char userNumber[32];
	char name[32];	
	char nameSpell[32];
	char post[32];
	char callNumber[32];
	char phoneNumber[32];
	unsigned long state;
}CC_STAFF_INFO_STRU;

typedef struct
{
	char nameSpell[32];
}CC_QUERY_STAFF_KEY_INFO_STRU;

typedef struct
{
	unsigned long taskId;
	char taskName[32];
	unsigned long taskType;
}CC_TASK_INFO_STRU;

typedef struct
{
	CC_TASK_INFO_STRU stTaskInfo[1];
}CC_TASK_INFO_SET_STRU;					/*Ϊ�������е����������б����*/


/*������ǲ��Ϣ�ṹ��*/
typedef struct
{
	unsigned long taskId;
	char callerPhoneNumber[32];
	char userNumber[32];				  /*����ǲԱ������*/
	unsigned long taskType[16]; 	 	  /*һ����ǲ���16������*/
	unsigned long taskState;
	unsigned long isReserve;   		 	  /*0-����ԤԼ��1-��ԤԼ*/
	char datetime[64];
	char department[64];				  /*ԤԼ���� add by gsc 2012-6-17 23:41:46 */
	unsigned long dispatcherId;		      /*����Աid*/
}CC_TASK_DISPATCH_INFO_STRU;

typedef struct
{
	CC_STAFF_INFO_STRU stStaffInfoList[1];
}CC_STAFF_INFO_SET_STRU;

typedef struct
{
	unsigned long reserveId;
	char callerPhoneNumber[32];
	char userNumber[32];			  /*����ǲԱ������*/
	unsigned long taskType[16];  	  /*һ����ǲ���16������*/
	unsigned long taskState;
	char reserveTime[64];			  /*ԤԼʱ��*/
	char department[64];			  /*ԤԼ���� add by gsc 2012-6-17 23:41:46 */
}CC_RESERVE_INFO_STRU;


/*�鿴������Ϣ�ṹ��*/
typedef struct
{	
	char datetime[64];  				/*���������¼ʱ��*/
	char department[64];				/*������ǲ����*/
	char callerPhoneNumber[32];			/*�绰����*/
	unsigned long taskType[16];  	    /*һ����ǲ���16������*/
	char staffName[32];					/*����ǲԱ������*/
	unsigned long taskState;			/*������ǲ�����0-û��ǲ��1-����ǲ��*/
	char dispatcher_name[32];			/*����Ա����*/
}CC_VIEW_TASK_LIST_STRU;


/*�鿴���е������б�ṹ��*/
typedef struct
{
	CC_VIEW_TASK_LIST_STRU stViewTaskList[1];
}CC_VIEW_TASK_LIST_SET_STRU;			/*�鿴���е������б�*/


/*�鿴�������ڼ�����������б�ṹ��*/
typedef struct
{
	char startDate[32];  				/*��ʼ����*/
	char endDate[32];					/*��������*/
}CC_VIEW_TASK_LIST_BETWEEN_START_END;   /*�鿴�������ڼ�����������б�*/


#endif
