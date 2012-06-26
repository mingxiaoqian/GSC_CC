#include <process.h>
#include <windows.h> 
#include "LVS_Timer.h"

LVS_UINT32 TimerProcFunc(TIMER_INFO_STRU *pstTimerPara)
{
    LVS_MSG_INFO_STRU stMsgInfo;
    memset(&stMsgInfo, 0, sizeof(stMsgInfo));

    stMsgInfo.ulSendPid =(LVS_UINT32) pstTimerPara->uModulePid;
    stMsgInfo.ulReceivePid =(LVS_UINT32) pstTimerPara->uModulePid;
    stMsgInfo.ulMsgType = LVS_MSG_TYPE_Timer;
    stMsgInfo.ulMsgId = (LVS_UINT32)pstTimerPara->uTimerMsgId;
    stMsgInfo.ulIsTimeConsuming =(LVS_UINT32) pstTimerPara->uIsTimeConsuming;
    stMsgInfo.ulMsgLen = (LVS_UINT32)pstTimerPara->uDataLength;
    stMsgInfo.pMsgData = pstTimerPara->pTimerData;

    LVS_SendMsg(&stMsgInfo);
    
    return LVS_OK;
}

static unsigned __stdcall timerCreatOneInstance(void *p)
{
    if (NULL == p)
	{
	    string stringPrintInfo = "timerCreatOneInstance failed,p is NULL";
        printString(stringPrintInfo,LVS_COLOR_LIGHTRED,0);
		return LVS_ERR;
	}

    TIMER_INFO_STRU *pstTimerPara = (TIMER_INFO_STRU*)p;

	MSG  msg;   
	PeekMessage(&msg,NULL,WM_USER,WM_USER,PM_NOREMOVE);  

	pstTimerPara->uTimerid = SetTimer(NULL,1,pstTimerPara->uElapse,NULL); 

    BOOL  bRet;
    while(   (bRet = GetMessage(&msg,NULL,0,0))!=   0)   
    {
        if(bRet==-1)   
		{   
			//   handle   the   error   and   possibly   exit   
			continue;
		} 
        else if(msg.message==WM_TIMER)  
        {
            if (msg.wParam == pstTimerPara->uTimerid)
            {
                TimerProcFunc(pstTimerPara);
                if(LVS_FALSE == pstTimerPara->uIsLoop)
                {
                    break;
                }
            }
        }
    }
    KillTimer(NULL,pstTimerPara->uTimerid);
    pstTimerPara->uTimerid = 0;
	return 0;
}

LVS_UINT32 LVS_StartTimer(TIMER_INFO_STRU *pstTimerInfo)
{
    unsigned int ulThreadID;
    pstTimerInfo->handleTimer = (HANDLE)_beginthreadex(NULL,
            											0,
            											timerCreatOneInstance,
            											(void*)pstTimerInfo,
            											0,
            											&ulThreadID);
    return LVS_OK;
}

LVS_UINT32 LVS_CloseTimer(TIMER_INFO_STRU *pstTimerInfo)
{
    if(0 != pstTimerInfo->uTimerid)
    {
        KillTimer(NULL,pstTimerInfo->uTimerid);
        pstTimerInfo->uTimerid = 0;
    }
    if(LVS_NULL_PTR != pstTimerInfo->handleTimer)
    {
        CloseHandle(pstTimerInfo->handleTimer);
        pstTimerInfo->handleTimer = LVS_NULL_PTR;
    }
    if(LVS_NULL_PTR != pstTimerInfo->pTimerData)
    {
        free(pstTimerInfo->pTimerData);
        pstTimerInfo->pTimerData = LVS_NULL_PTR;
    }
    memset(pstTimerInfo, 0, sizeof(TIMER_INFO_STRU));
    return LVS_OK;
}
