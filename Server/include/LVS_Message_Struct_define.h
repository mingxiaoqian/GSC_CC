
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
	unsigned long telChannelId;   /*来电通道标志，0-为0通道，1-为1通道，以此类推，如果是手工输入的任务则为空。*/
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
}CC_TASK_INFO_SET_STRU;					/*为发送所有的任务种类列表而设*/


/*任务派遣信息结构体*/
typedef struct
{
	unsigned long taskId;
	char callerPhoneNumber[32];
	char userNumber[32];				  /*被派遣员工工号*/
	unsigned long taskType[16]; 	 	  /*一次派遣最多16个任务*/
	unsigned long taskState;
	unsigned long isReserve;   		 	  /*0-不是预约，1-是预约*/
	char datetime[64];
	char department[64];				  /*预约部门 add by gsc 2012-6-17 23:41:46 */
	unsigned long dispatcherId;		      /*调度员id*/
}CC_TASK_DISPATCH_INFO_STRU;

typedef struct
{
	CC_STAFF_INFO_STRU stStaffInfoList[1];
}CC_STAFF_INFO_SET_STRU;

typedef struct
{
	unsigned long reserveId;
	char callerPhoneNumber[32];
	char userNumber[32];			  /*被派遣员工工号*/
	unsigned long taskType[16];  	  /*一次派遣最多16个任务*/
	unsigned long taskState;
	char reserveTime[64];			  /*预约时间*/
	char department[64];			  /*预约部门 add by gsc 2012-6-17 23:41:46 */
}CC_RESERVE_INFO_STRU;


/*查看任务信息结构体*/
typedef struct
{	
	char datetime[64];  				/*任务来电记录时间*/
	char department[64];				/*任务派遣部门*/
	char callerPhoneNumber[32];			/*电话号码*/
	unsigned long taskType[16];  	    /*一次派遣最多16个任务*/
	char staffName[32];					/*被派遣员工姓名*/
	unsigned long taskState;			/*任务派遣情况，0-没派遣；1-已派遣；*/
	char dispatcher_name[32];			/*调度员姓名*/
}CC_VIEW_TASK_LIST_STRU;


/*查看所有的任务列表结构体*/
typedef struct
{
	CC_VIEW_TASK_LIST_STRU stViewTaskList[1];
}CC_VIEW_TASK_LIST_SET_STRU;			/*查看所有的任务列表*/


/*查看两个日期间的所有任务列表结构体*/
typedef struct
{
	char startDate[32];  				/*开始日期*/
	char endDate[32];					/*结束日期*/
}CC_VIEW_TASK_LIST_BETWEEN_START_END;   /*查看两个日期间的所有任务列表*/


#endif
