#pragma once

#include "LVS_mysql.h"
#include "LVS_Message_Struct_define.h"

#ifndef _LVS_RESERVE_H
#define _LVS_RESERVE_H

#define LVS_LONGEST_TIME  60*60*24*365

typedef enum
{
	RESERVE_MSG_TYPE_TIMER = 3001,
	RESERVE_MSG_TYPE_NEW_RESERVE = 3002,
	RESERVE_MSG_TYPE_BUTT	
}LVS_TASK_RESERVE_MSG_ID;

unsigned long InitTaskReserveService();
unsigned long updateReserveRestTime();

/*���������ԤԼ�Լ���ȡ�´�ԤԼʱ��*/
/*ulIsGetTimeOnly Ϊ0 ʱ��ֻ��ѯʱ��*/
/*ulIsGetTimeOnly Ϊ1 ʱ������ԤԼ����ѯʱ��*/
unsigned long procCurReserveAndGetNextReserveRestTime(LVS_UINT32 ulIsGetTimeOnly);



#endif

