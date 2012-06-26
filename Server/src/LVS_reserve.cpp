#include "LVS_Timer.h"
#include "Lvs_PID_Init.h"
#include "LVS_reserve.h"

TIMER_INFO_STRU m_stReserveTaskTimer = {0};

/*在系统初始化的时候调用,方案变更,无需调用,应废弃*/
LVS_UINT32 InitTaskReserveService()
{
    if(LVS_NULL_PTR != m_stReserveTaskTimer.handleTimer)
    {
        string strPrintInfo = "InitTaskReserveService has been inited.";
        printString(strPrintInfo,LVS_COLOR_WHITE,0);
        LVS_CloseTimer(&m_stReserveTaskTimer);
    }

    LVS_UINT32 ulRet;
    
    m_stReserveTaskTimer.uElapse = 10000;
    m_stReserveTaskTimer.uTimerMsgId = RESERVE_MSG_TYPE_TIMER;
    m_stReserveTaskTimer.uModulePid = PID_TASK_TESERVE_PROXY;
    m_stReserveTaskTimer.uIsLoop = LVS_FALSE;
    m_stReserveTaskTimer.uIsTimeConsuming = LVS_TRUE;

    ulRet = LVS_StartTimer(&m_stReserveTaskTimer);
    
    return ulRet;
}

/*处理最近的预约以及获取下次预约时间*/
/*ulIsGetTimeOnly 为0 时，只查询时间*/
/*ulIsGetTimeOnly 为1 时，处理预约并查询时间*/
/*返回值为最近一次预约与当前时间的时间差，如果表中没有记录，则返回24*60*60*30 */
LVS_UINT32 procCurReserveAndGetNextReserveRestTime(LVS_UINT32 ulIsGetTimeOnly)
{
    LVS_INT32 theRecentReserveSeconds = LVS_LONGEST_TIME;
    if(0 == ulIsGetTimeOnly)
    {
        printString("更新下次预约时间",LVS_COLOR_WHITE,0);
        theRecentReserveSeconds = getTheRecentReserveSeconds();
        if(-1 == theRecentReserveSeconds)
        {
            printString("getTheRecentReserveSeconds error!!",LVS_COLOR_LIGHTRED,0);
            theRecentReserveSeconds = LVS_LONGEST_TIME;
        }
    }
    else
    {
        printString("处理预约、更新下次预约时间",LVS_COLOR_WHITE,0);

        CC_RESERVE_INFO_STRU reserveInfo;
        memset(&reserveInfo, 0, sizeof(reserveInfo));
        
        if(-1 == getTheRecentReserveInfo(&reserveInfo))
        {
            printString("getTheRecentReserveInfo error!!",LVS_COLOR_LIGHTRED,0);
        }
        else {
            /*预约时间到了，发送预约消息给客户端*/
        	LVS_MSG_INFO_STRU stMsg;
        	memset(&stMsg, 0, sizeof(stMsg));

            stMsg.ulSendPid = PID_VOICE_PROXY;
            stMsg.ulReceivePid = PID_VOICE_PROXY;
            stMsg.ulMsgType = LVS_MSG_TYPE_USER;
            stMsg.ulMsgLen = sizeof(reserveInfo);
            stMsg.pMsgData = &reserveInfo;
            stMsg.ulMsgId = UP_MSG_TYPE_RESERVE_INFO;
            stMsg.ulIsTimeConsuming = LVS_FALSE;
			stMsg.lSocketId = LVS_SEND_ALL;

            /*发送给预约信息给客户端*/
            packToJsonStringAndSend(&stMsg);

            /*重新计算最近预约时间*/
            theRecentReserveSeconds = getTheRecentReserveSeconds();
            if(-1 == theRecentReserveSeconds)
            {
                printString("getTheRecentReserveSeconds error!!",LVS_COLOR_LIGHTRED,0);
                theRecentReserveSeconds = LVS_LONGEST_TIME;
            }
        }
    }
    return theRecentReserveSeconds;
}
/*当插入新的预约的时候，调用此接口通知更新定时器下次预约的时间*/
LVS_UINT32 updateReserveRestTime()
{
    LVS_MSG_INFO_STRU stMsgInfo;
    memset(&stMsgInfo, 0, sizeof(stMsgInfo));

    stMsgInfo.ulSendPid = PID_TASK_TESERVE_PROXY;
    stMsgInfo.ulReceivePid = PID_TASK_TESERVE_PROXY;
    stMsgInfo.ulMsgType = LVS_MSG_TYPE_USER;
    stMsgInfo.ulMsgId = RESERVE_MSG_TYPE_NEW_RESERVE;
    stMsgInfo.ulIsTimeConsuming = LVS_TRUE;

    LVS_SendMsg(&stMsgInfo);
    
    return LVS_OK;
}

LVS_UINT32 TaskReserveMsgProc(LVS_VOID *pMsg)
{
    if(LVS_NULL_PTR == pMsg)
    {
        string strPrintInfo = "TaskReserveMsgProc,pMsg is NULL";
        printString(strPrintInfo,LVS_COLOR_LIGHTRED,0);
        return LVS_ERR;
    }
    LVS_MSG_INFO_STRU *pReqMsg = (LVS_MSG_INFO_STRU*)pMsg;
    if(LVS_MSG_TYPE_Timer == pReqMsg->ulMsgType || LVS_MSG_TYPE_USER == pReqMsg->ulMsgType)
    {
        LVS_UINT32 ulIsGetTimeOnly = 0;
        /*处理定时器消息*/
        switch (pReqMsg->ulMsgId)
        {
            case RESERVE_MSG_TYPE_TIMER:
                ulIsGetTimeOnly = 1;
            case RESERVE_MSG_TYPE_NEW_RESERVE:
                /*定时处理预约*/
                /*获取最近的一次预约的时间*/
                LVS_CloseTimer(&m_stReserveTaskTimer);
                m_stReserveTaskTimer.uElapse = procCurReserveAndGetNextReserveRestTime(ulIsGetTimeOnly);
                m_stReserveTaskTimer.uTimerMsgId = RESERVE_MSG_TYPE_TIMER;
                m_stReserveTaskTimer.uModulePid = PID_TASK_TESERVE_PROXY;
                m_stReserveTaskTimer.uIsLoop = LVS_FALSE;
                m_stReserveTaskTimer.uIsTimeConsuming = LVS_TRUE;
                
                LVS_StartTimer(&m_stReserveTaskTimer);
                break;
            
            default:
                break;
        }
    }


    return LVS_OK;
}

