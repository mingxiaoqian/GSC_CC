#pragma once

#ifndef _LVS_IPTELNOBIND_H
#define _LVS_IPTELNOBIND_H

#define MAX_TELPHONE_NO    256

typedef struct tagSocketIdList
{
	LVS_INT32 lSocketId;
	struct tagSocketIdList *pnext;
}SOCKET_ID_LIST;

typedef struct tagTelBindSocketInfoStru
{
	LVS_UINT32 ulTelNo;
	LVS_UINT32 ulBindSocketNum;
	SOCKET_ID_LIST *pstSocketList;

	struct tagTelBindSocketInfoStru *pnext;
}TEL_BIND_SOCKET_INFO_STRU;


typedef struct tagIpBindTelListStru
{
	LVS_UINT32 ulIpAddr;
	LVS_UINT32 ulTelNo;
	struct tagIpBindTelListStru *pnext;
}IP_BIND_TEL_LIST_STRU;


LVS_UINT32 loadConfigInfoFromConfigFile();
LVS_UINT32 bindSocketIdToTelNo(const LVS_INT32 lSocketId, const LVS_UINT32 ulIpAddr);
LVS_UINT32 unbindSocketIdToTelNo(const LVS_INT32 lSocketId);
LVS_UINT32 getSocketListByTelNo(const LVS_UINT32 ulTelNo,SOCKET_ID_LIST **ppstSocketList,LVS_UINT32 *pulSocketNum);


#endif

