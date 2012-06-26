#include <fstream>
#include <winsock2.h>
#include "LVS_define.h"
#include "LVS_IPTelNoBind.h"


#define IP_TEL_BIND_CONFIG_FILE    ".\\config\\IPTelBind.config" 
#define IP_TEL_BIND_CONFIG_FILE_EX "..\\Debug\\config\\IPTelBind.config" 
#define IP_TEL_BIND_CONFIG_BEGIN   "IP_Config:"


/*全局变量*/
/*存放配置文件中的IP和电话的绑定信息*/
IP_BIND_TEL_LIST_STRU    *m_pstConfigIpTelBindInfo = LVS_NULL_PTR;
/*存放电话绑定的socket信息*/
TEL_BIND_SOCKET_INFO_STRU  *m_pstTelSocketBindingInfoList = LVS_NULL_PTR;


/*读取配置文件，初始化配置信息*/
LVS_UINT32 loadConfigInfoFromConfigFile()
{
	ifstream ifs;
	ifs.open(IP_TEL_BIND_CONFIG_FILE,ios::in);

	if(LVS_NULL_PTR == ifs)
	{
		ifs.open(IP_TEL_BIND_CONFIG_FILE_EX,ios::in);
	}
	
	if(LVS_NULL_PTR == ifs)
	{
		printString("loadConfigInfoFromConfigFile->无法打开配置项，请确认配置项存在",LVS_COLOR_LIGHTRED,LVS_FALSE);
		return LVS_ERR;
	}

	string strConfigLine;
	string strConfigBegin = IP_TEL_BIND_CONFIG_BEGIN;
	while(getline(ifs,strConfigLine))
	{
		LVS_INT32 lEquaPos = strConfigLine.find("=");
		if(string::npos != strConfigLine.find(strConfigBegin) && string::npos != lEquaPos)
		{
			//cout<<strConfigLine<<endl;
			
			string strIpAddr = allTrim(strConfigLine.substr(strConfigBegin.length(),lEquaPos - strConfigBegin.length()));
			//cout<<strIpAddr<<endl;
			IN_ADDR addrConfig;
			addrConfig.s_addr = inet_addr(strIpAddr.c_str());
			//cout<<addrConfig.s_addr<<endl;
			//cout<<inet_ntoa(addrConfig)<<endl;
			string strTelNo = allTrim(strConfigLine.substr(lEquaPos + 1 ,strConfigLine.length() - lEquaPos));
			//cout<<strTelNo<<endl;

			LVS_UINT32 ulTelNo = changeStringToUlong(strTelNo);
			if(INADDR_NONE == addrConfig.s_addr || MAX_TELPHONE_NO <= ulTelNo)
			{
				continue;
			}

			//cout<<INADDR_NONE<<endl;
			//cout<<addrConfig.s_addr<<endl;
			//cout<<ulTelNo<<endl;

			IP_BIND_TEL_LIST_STRU *pstIpTelBindingInfo = (IP_BIND_TEL_LIST_STRU*)malloc(sizeof(IP_BIND_TEL_LIST_STRU));
			memset(pstIpTelBindingInfo, 0, sizeof(IP_BIND_TEL_LIST_STRU));
			pstIpTelBindingInfo->ulIpAddr = addrConfig.s_addr;
			pstIpTelBindingInfo->ulTelNo = ulTelNo;

			if(LVS_NULL_PTR == m_pstConfigIpTelBindInfo)
			{
				m_pstConfigIpTelBindInfo = pstIpTelBindingInfo;
			}
			else
			{
				IP_BIND_TEL_LIST_STRU *pTemp = m_pstConfigIpTelBindInfo;
				while(LVS_NULL_PTR != pTemp->pnext)
				{
					pTemp = pTemp->pnext;
				}
				pTemp->pnext = pstIpTelBindingInfo;
			}
		}
	}
	printString("Load Config File Succeed",LVS_COLOR_WHITE,LVS_FALSE);
	return LVS_OK;
}

TEL_BIND_SOCKET_INFO_STRU* findTelSocketBindingInfoByTelNo(const LVS_UINT32 ulTelNo)
{
	if(LVS_NULL_PTR == m_pstTelSocketBindingInfoList)
	{
		m_pstTelSocketBindingInfoList = (TEL_BIND_SOCKET_INFO_STRU*)malloc(sizeof(TEL_BIND_SOCKET_INFO_STRU));
		if(LVS_NULL_PTR == m_pstTelSocketBindingInfoList)
		{
			printString("findTelSocketBindingInfoByTelNo->malloc failed",LVS_COLOR_LIGHTRED,LVS_FALSE);
			return LVS_NULL_PTR;
		}
		memset(m_pstTelSocketBindingInfoList ,0,sizeof(TEL_BIND_SOCKET_INFO_STRU));
		m_pstTelSocketBindingInfoList->ulTelNo = ulTelNo;
		return m_pstTelSocketBindingInfoList;
	}
	TEL_BIND_SOCKET_INFO_STRU *pstTelSocketBinding = m_pstTelSocketBindingInfoList;
	TEL_BIND_SOCKET_INFO_STRU *pTemp = LVS_NULL_PTR;
	while(LVS_NULL_PTR != pstTelSocketBinding)
	{
		if(ulTelNo == pstTelSocketBinding->ulTelNo)
		{
			return pstTelSocketBinding;
		}
		pTemp = pstTelSocketBinding;
		pstTelSocketBinding = pstTelSocketBinding->pnext;
	}
	pstTelSocketBinding = (TEL_BIND_SOCKET_INFO_STRU*)malloc(sizeof(TEL_BIND_SOCKET_INFO_STRU));
	if(LVS_NULL_PTR == pstTelSocketBinding)
	{
		printString("findTelSocketBindingInfoByTelNo->malloc failed",LVS_COLOR_LIGHTRED,LVS_FALSE);
		return LVS_NULL_PTR;
	}
	memset(pstTelSocketBinding ,0,sizeof(TEL_BIND_SOCKET_INFO_STRU));
	pstTelSocketBinding->ulTelNo = ulTelNo;
	pTemp->pnext = pstTelSocketBinding;
	return pstTelSocketBinding;
}


/*将socket根据IP和TelNo的绑定关系绑定到具体的TelNo*/
LVS_UINT32 bindSocketIdToTelNo(const LVS_INT32 lSocketId, const LVS_UINT32 ulIpAddr)
{
	IP_BIND_TEL_LIST_STRU *pstIpTelBindingInfo = m_pstConfigIpTelBindInfo;
	while(LVS_NULL_PTR != pstIpTelBindingInfo)
	{
		if(ulIpAddr == pstIpTelBindingInfo->ulIpAddr)
		{
			LVS_UINT32 ulTelNo = pstIpTelBindingInfo->ulTelNo;
			TEL_BIND_SOCKET_INFO_STRU *pstTelSocketBinding = findTelSocketBindingInfoByTelNo(ulTelNo);
			if(LVS_NULL_PTR == pstTelSocketBinding)
			{
				printString("bindSocketIdToTelNo->findTelSocketBindingInfoByTelNo failed",LVS_COLOR_LIGHTRED,LVS_FALSE);
				goto Next_While;
			}
			if(LVS_NULL_PTR == pstTelSocketBinding->pstSocketList)
			{
				pstTelSocketBinding->pstSocketList = (SOCKET_ID_LIST*)malloc(sizeof(SOCKET_ID_LIST));
				if(LVS_NULL_PTR == pstTelSocketBinding->pstSocketList)
				{
					printString("bindSocketIdToTelNo->malloc 1 failed",LVS_COLOR_LIGHTRED,LVS_FALSE);
					goto Next_While;
				}
				memset(pstTelSocketBinding->pstSocketList, 0, sizeof(SOCKET_ID_LIST));
				pstTelSocketBinding->pstSocketList->lSocketId = lSocketId;
				pstTelSocketBinding->ulBindSocketNum++;
				goto Next_While;
			}
			SOCKET_ID_LIST *pstSocketIdListNode = pstTelSocketBinding->pstSocketList;
			SOCKET_ID_LIST *pstTempSILN = LVS_NULL_PTR;
			LVS_UINT32 ulIsBindAlready = LVS_FALSE;
			while(LVS_NULL_PTR != pstSocketIdListNode)
			{
				if(lSocketId == pstSocketIdListNode->lSocketId)
				{
					ulIsBindAlready = LVS_TRUE;
					break;
				}
				pstTempSILN = pstSocketIdListNode;
				pstSocketIdListNode = pstSocketIdListNode->pnext;
			}
			if(LVS_TRUE != ulIsBindAlready)
			{
				pstSocketIdListNode = (SOCKET_ID_LIST*)malloc(sizeof(SOCKET_ID_LIST));
				if(LVS_NULL_PTR == pstSocketIdListNode)
				{
					printString("bindSocketIdToTelNo->malloc 2 failed",LVS_COLOR_LIGHTRED,LVS_FALSE);
					goto Next_While;
				}
				memset(pstSocketIdListNode, 0, sizeof(SOCKET_ID_LIST));
				pstSocketIdListNode->lSocketId = lSocketId;
				pstTelSocketBinding->ulBindSocketNum++;
				pstTempSILN->pnext = pstSocketIdListNode;
			}
		}
Next_While:
		pstIpTelBindingInfo = pstIpTelBindingInfo->pnext;
	}
	return LVS_OK;
}

LVS_UINT32 unbindSocketIdToTelNo(const LVS_INT32 lSocketId)
{
	TEL_BIND_SOCKET_INFO_STRU *pstTelSocketBinding = m_pstTelSocketBindingInfoList;

	while(LVS_NULL_PTR != pstTelSocketBinding)
	{
		SOCKET_ID_LIST *pstSocketIdNode = pstTelSocketBinding->pstSocketList;
		SOCKET_ID_LIST *pstTempSocketIdNode = LVS_NULL_PTR;
		while(LVS_NULL_PTR != pstSocketIdNode)
		{
			if(lSocketId == pstSocketIdNode->lSocketId)
			{
				if(LVS_NULL_PTR == pstTempSocketIdNode)
				{
					pstTelSocketBinding->pstSocketList = pstSocketIdNode->pnext;
					free(pstSocketIdNode);
					pstTelSocketBinding->ulBindSocketNum--;
					pstSocketIdNode = pstTelSocketBinding->pstSocketList;
					continue;
				}
				else
				{
					pstTempSocketIdNode->pnext = pstSocketIdNode->pnext;
					free(pstSocketIdNode);
					pstTelSocketBinding->ulBindSocketNum--;
					pstSocketIdNode = pstTempSocketIdNode->pnext;
					continue;
				}
			}
			pstTempSocketIdNode = pstSocketIdNode;
			pstSocketIdNode = pstSocketIdNode->pnext;
		}
		pstTelSocketBinding = pstTelSocketBinding->pnext;
	}
	return LVS_OK;
}

LVS_UINT32 getSocketListByTelNo(const LVS_UINT32 ulTelNo,SOCKET_ID_LIST **ppstSocketList,LVS_UINT32 *pulSocketNum)
{
	if(LVS_NULL_PTR == ppstSocketList || LVS_NULL_PTR == pulSocketNum)
	{
		printString("NULL POINT ERROR, ppstSocketList or pulSocketNum is a NULL POINT!!", LVS_COLOR_LIGHTRED, 0);
		return LVS_ERR;
	}
	TEL_BIND_SOCKET_INFO_STRU *pstTelSocketBindIngInfo = m_pstTelSocketBindingInfoList;
	
	while(LVS_NULL_PTR != pstTelSocketBindIngInfo)
	{
		if(ulTelNo == pstTelSocketBindIngInfo->ulTelNo)
		{
			*ppstSocketList = pstTelSocketBindIngInfo->pstSocketList;
			*pulSocketNum = pstTelSocketBindIngInfo->ulBindSocketNum;
			return LVS_OK;
		}
		pstTelSocketBindIngInfo = pstTelSocketBindIngInfo->pnext;
	}
	
	return LVS_ERR;
}

