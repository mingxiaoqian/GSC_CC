#include "LVSMsgList.h"

LVS_MessageQueue::LVS_MessageQueue()
{
    sFront = 1;
    sRear = 0;
    ulMsgListOperateFlag = 0;
    for(LVS_UINT32 i = 0; i < ARRAY_SIZE; i++)
    {
        g_LVS_stMessageQueue[i].ulSendPid = LVS_NULL_LONG;
        g_LVS_stMessageQueue[i].ulReceivePid = LVS_NULL_LONG;
        g_LVS_stMessageQueue[i].ulMsgType = LVS_NULL_LONG;
        g_LVS_stMessageQueue[i].ulMsgId   = LVS_NULL_LONG;
        g_LVS_stMessageQueue[i].ulIsTimeConsuming = LVS_FALSE;
        g_LVS_stMessageQueue[i].ulMsgLen = 0;
        g_LVS_stMessageQueue[i].pMsgData = LVS_NULL_PTR;
    }
}


static LVS_UINT32 ulMsgListPrintFlag = LVS_ERR;

/*
**    insert
*/
LVS_UINT32 LVS_MessageQueue::LVSMsglistlnsert(LVS_MSG_INFO_STRU *pstValue)
{
    while (0 != ulMsgListOperateFlag)
    {
        Sleep(5);
    }
    ulMsgListOperateFlag = 1;
    if (NULL == pstValue)
    {
        ulMsgListOperateFlag = 0;
        return LVS_ERR;
    }
    if (LVS_OK == LVSMsglistIsFull())
    {
        cout<<"The Queue is Full!"<<endl;
        ulMsgListOperateFlag = 0;
        return LVS_ERR;
    }
    
    sRear = (sRear + 1) % ARRAY_SIZE;
    memcpy(&g_LVS_stMessageQueue[sRear], pstValue, sizeof(LVS_MSG_INFO_STRU));

    if(LVS_OK == ulMsgListPrintFlag)
    {
        cout<<"Insert:"<<sRear<<endl;
    }

    ulMsgListOperateFlag = 0;
    return LVS_OK;
}

/*
**    delete
*/
LVS_UINT32 LVS_MessageQueue::LVSMsglistDelete(LVS_MSG_INFO_STRU **pstValue)
{
    while (0 != ulMsgListOperateFlag)
    {
        Sleep(5);
    }
    ulMsgListOperateFlag = 1;
    if (LVS_OK != LVSMsglistFirst(pstValue))
    {
        ulMsgListOperateFlag = 0;
        return LVS_ERR;
    }
    if(LVS_OK == ulMsgListPrintFlag)
    {
        cout<<"Delete:"<<sFront<<endl;
    }
    sFront = (sFront + 1) % ARRAY_SIZE;

    ulMsgListOperateFlag = 0;
    return LVS_OK;
}

/*
**    first
*/
LVS_UINT32 LVS_MessageQueue::LVSMsglistFirst(LVS_MSG_INFO_STRU **pstValue)
{
    if (LVS_OK == LVSMsglistIsEmpty())
    {
        if(LVS_OK == ulMsgListPrintFlag)
        {
            cout<<"The Queue is empty!"<<endl;
        }
        return LVS_ERR;
    }
    //memcpy(pstValue, &g_LVS_stMessageQueue[sFront], sizeof(LVS_MSG_INFO_STRU));
    *pstValue = (LVS_MSG_INFO_STRU *)&g_LVS_stMessageQueue[sFront];

    return LVS_OK;
}

/*
**    is_empty
**    (sRear + 1) % ARRAY_SIZE == sFront
*/
LVS_UINT32 LVS_MessageQueue::LVSMsglistIsEmpty(LVS_VOID)
{
    if ((sRear + 1) % ARRAY_SIZE == sFront)
    {
        return LVS_OK;
    }
    return LVS_ERR;
}

/*
**    is_full
**    (sRear + 2) % ARRAY_SIZE == sFront
*/
LVS_UINT32 LVS_MessageQueue::LVSMsglistIsFull(LVS_VOID)
{
    if ((sRear + 2) % ARRAY_SIZE == sFront)
    {
        return LVS_OK;
    }
    return LVS_ERR;
}

/*��ȡ��ǰ��Ϣ�Ƿ��ʱ*/
LVS_UINT32 LVS_MessageQueue::LVSCurMsgIsTimeConsuming(LVS_VOID)
{
    if (LVS_OK == LVSMsglistIsEmpty())
    {
        if(LVS_OK == ulMsgListPrintFlag)
        {
            cout<<"The Queue is empty!"<<endl;
        }
        return LVS_FALSE;
    }
    return g_LVS_stMessageQueue[sFront].ulIsTimeConsuming;
}
