#include <winsock.h>  
#include <iostream>  
#include <string>  
#include <mysql.h>  
#include "LVS_define.h"
#include "LVS_Message_Struct_define.h"
#include "LVS_MessageConvert.h"
#include <windows.h> 


using namespace std;  
#pragma comment(lib, "ws2_32.lib")  
#pragma comment(lib, "libmysql.lib") 


LVS_UINT32 insertTaskList(CC_CALLER_INFO_STRU *pCallerInfo);
LVS_UINT32 insertCallerInfo(CC_CALLER_INFO_STRU *pCallerInfo);
LVS_UINT32 insertStaffInfo(CC_STAFF_INFO_STRU *pStaffInfo);
LVS_UINT32 insertTaskType(CC_TASK_INFO_STRU*pTaskInfo);
LVS_UINT32 queryCallerInfo(CC_CALLER_INFO_STRU *pCallerInfo);
LVS_UINT32 queryStaffInfoUseNameSpell(LVS_MSG_INFO_STRU *pMsg);
LVS_UINT32 updateTaskList(CC_TASK_DISPATCH_INFO_STRU *pTaskDispatchInfo);
LVS_UINT32 insertTaskDtl(CC_TASK_DISPATCH_INFO_STRU *pTaskDispatchInfo);
LVS_UINT32 insertTaskListReserve(CC_TASK_DISPATCH_INFO_STRU *pTaskDispatchInfo);
LVS_UINT32 insertReserveList(CC_TASK_DISPATCH_INFO_STRU *pTaskDispatchInfo);
LVS_UINT32 insertReserveTaskDtl(CC_TASK_DISPATCH_INFO_STRU *pTaskDispatchInfo);
LVS_UINT32 updateReserveList(CC_TASK_DISPATCH_INFO_STRU *pTaskDispatchInfo);
LVS_INT32  getTheRecentReserveSeconds();
LVS_UINT32 getTheRecentReserveInfo(CC_RESERVE_INFO_STRU *pReserveInfo);
LVS_UINT32 quaryTaskListBetweenStartAndEnd(LVS_MSG_INFO_STRU *pMsg);
LVS_UINT32 quaryAllTaskTypeList(LVS_MSG_INFO_STRU *pMsg);







