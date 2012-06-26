#include "LVSMsgManager.h"
#include "LVS_PID_Init.h"


#define LVS_TIME_SPACE            5
#define LVS_MAX_Msg_Manager_Num   1 	/*最多消息管理者的实例个数*/


//LVS_PID_STRU g_LVS_astMsgPid[] = LVS_MESSAGE_PID_LIST;


LVS_UINT32 LVS_Message_Manager::ulCaseNum = 0;

LVS_UINT32 LVS_Message_Manager::ulMsgLock_Normal = 0;
LVS_UINT32 LVS_Message_Manager::ulMsgLock_TimeConsuming = 0;


LVS_MessageQueue* LVS_Message_Manager::pMessageQueue_Normal = LVS_NULL_PTR;
LVS_MessageQueue* LVS_Message_Manager::pMessageQueue_TimeConsuming = LVS_NULL_PTR;

LVS_PID_STRU LVS_Message_Manager::stMsgPidList[] = LVS_MESSAGE_PID_LIST;
LVS_UINT32 LVS_Message_Manager::ulListNum = sizeof(stMsgPidList)/sizeof(stMsgPidList[0]);


LVS_Message_Manager::LVS_Message_Manager()
{
    InitMemberParameter(1,1);
}

LVS_Message_Manager::LVS_Message_Manager(LVS_UINT32 fastThreadNum, LVS_UINT32 slowThreadNum)
{
    InitMemberParameter(fastThreadNum,slowThreadNum);
}

LVS_Message_Manager::~LVS_Message_Manager()
{
    for(LVS_UINT32 i = 0; i < MAX_THREAD_NUMBER; i++)
    {
        if(LVS_NULL_PTR != hThread[i])
        {
            CloseHandle(hThread[i]);
        }
    }
    
}

LVS_UINT32 LVS_Message_Manager::InitMemberParameter(LVS_UINT32 fastThreadNum, LVS_UINT32 slowThreadNum)
{
    if(fastThreadNum + slowThreadNum > MAX_THREAD_NUMBER || 0 == fastThreadNum)
    {
        /*应该记日志*/
        printf("The Thread Number parameter is InValid:%d,%d\r\n",fastThreadNum,slowThreadNum);
        ulThreadNum_Normal = 1;
        ulThreadNum_TimeConsuming = 1;
    }
    else
    {
        ulThreadNum_Normal = fastThreadNum;
        ulThreadNum_TimeConsuming = slowThreadNum;
    }
    for(LVS_UINT32 i = 0; i < MAX_THREAD_NUMBER; i++)
    {
        hThread[i] = LVS_NULL_PTR;
    }
    return LVS_OK;
}

LVS_Message_Manager* LVS_Message_Manager::CreateMsgManager(LVS_VOID)
{
    return CreateMsgManager(1,1);
}

LVS_Message_Manager* LVS_Message_Manager::CreateMsgManager(LVS_UINT32 fastThreadNum, LVS_UINT32 slowThreadNum)
{
    if (ulCaseNum >= LVS_MAX_Msg_Manager_Num)
    {
        return LVS_NULL_PTR;
    }
    LVS_Message_Manager *pMsgManager = new LVS_Message_Manager(fastThreadNum,slowThreadNum);
    if(LVS_NULL_PTR == pMsgManager)
    {
        return LVS_NULL_PTR;
    }
    if(LVS_NULL_PTR == pMessageQueue_Normal)
    {
        pMessageQueue_Normal = new LVS_MessageQueue();
    }
    if(LVS_NULL_PTR == pMessageQueue_Normal)
    {
        return LVS_NULL_PTR;
    }
    if(LVS_NULL_PTR == pMessageQueue_TimeConsuming)
    {
        pMessageQueue_TimeConsuming = new LVS_MessageQueue(); 
    }
    if(LVS_NULL_PTR == pMessageQueue_TimeConsuming)
    {
        return LVS_NULL_PTR;
    }
    ulCaseNum ++;
    pMsgManager->ulTransId = ulCaseNum;
    cout<<"Create the" <<ulCaseNum<< " Message Process Manager!   "<<sizeof(stMsgPidList)/sizeof(stMsgPidList[0])<<endl;
    return pMsgManager;
}

/*Input:VS_UINT32 ulIsTimeConsuming
             0:表示普通任务
             1:表示耗时任务
*/
LVS_VOID LVS_Message_Manager::StartProcessMsg(LVS_UINT32 ulIsTimeConsuming)
{
    if(1 < ulIsTimeConsuming)
    {
        return;
    }

    LVS_UINT32 ulRet = LVS_OK;
    LVS_MSG_INFO_STRU *pstValue = LVS_NULL_PTR;
    LVS_MessageQueue* aMsgList[2] = {pMessageQueue_Normal,pMessageQueue_TimeConsuming}; 
    LVS_UINT32* apulMsgLock[2] = {&ulMsgLock_Normal, &ulMsgLock_TimeConsuming};
    while(LVS_TRUE)
    {
        
        if(LVS_NULL_PTR == aMsgList[ulIsTimeConsuming])
        {
            printf("Error:The Message Queue %d is not initialize\r\n",ulIsTimeConsuming);
            return;
        }
        
        if((*apulMsgLock[ulIsTimeConsuming]) > 0)
        {
            Sleep(LVS_TIME_SPACE);
            continue;
        }
        
        (*apulMsgLock[ulIsTimeConsuming])++;       //锁定消息队列
        if(LVS_OK == aMsgList[ulIsTimeConsuming]->LVSMsglistIsEmpty())
        {
            (*apulMsgLock[ulIsTimeConsuming])--;   //解锁消息队列
            Sleep(LVS_TIME_SPACE);
            continue;
        }

        ulRet = aMsgList[ulIsTimeConsuming]->LVSMsglistDelete(&pstValue);
        if(LVS_OK != ulRet || LVS_NULL_PTR == pstValue)
        {
            (*apulMsgLock[ulIsTimeConsuming])--; //解锁消息队列
            Sleep(LVS_TIME_SPACE);
            continue;
        }
        (*apulMsgLock[ulIsTimeConsuming])--; //解锁消息队列

        for(LVS_UINT32 i = 0; i < ulListNum; i++)
        {
            if(pstValue->ulReceivePid == stMsgPidList[i].ulPid)
            {
                if(LVS_NULL_PTR != stMsgPidList[i].pfnMsgProc)
                {
                    stMsgPidList[i].pfnMsgProc((LVS_VOID*)pstValue);
                }
                LVS_VOID *pMsgData = (LVS_VOID *)pstValue->pMsgData;
                //printf("%d\r\n",this->ulTransId);
                if(LVS_NULL_PTR != pMsgData)
                {
                    free(pMsgData);
                    pMsgData = LVS_NULL_PTR;
                }
                break;
            }
        }
    }
}

void LVS_Message_Manager::start()
{
    for(LVS_UINT32 i = 0; i < ulThreadNum_Normal; i++)
    {
        hThread[i] = (HANDLE)_beginthread(agent__Normal, 0, (void *)this);
    }
    for(LVS_UINT32 i = ulThreadNum_Normal; i < ulThreadNum_Normal + ulThreadNum_TimeConsuming; i++)
    {
        hThread[i] = (HANDLE)_beginthread(agent__TimeConsuming, 0, (void *)this);
    }
}

void LVS_Message_Manager::agent__Normal(void *p)
{
       LVS_Message_Manager *agt = (LVS_Message_Manager *)p;
       agt->run__Normal();
}

void LVS_Message_Manager::agent__TimeConsuming(void *p)
{
       LVS_Message_Manager *agt = (LVS_Message_Manager *)p;
       agt->run__TimeConsuming();
}

void LVS_Message_Manager::run__Normal()
{
    cout << "The MSG Processer Thread Start!\r\n";
    this->StartProcessMsg(0);
}
void LVS_Message_Manager::run__TimeConsuming()
{
    cout << "The MSG Processer Thread Start!\r\n";
    this->StartProcessMsg(1);
}

LVS_UINT32 LVS_Message_Manager::sendMsg(LVS_MSG_INFO_STRU *pstValue)
{
    LVS_UINT32 ulRet = LVS_OK;
    LVS_VOID *pMsgData = LVS_NULL_PTR;
    LVS_MSG_INFO_STRU stMsg;
    if(LVS_NULL_PTR == pstValue)
    {
        printf("The msg pointor is valid\r\n");
        return LVS_ERR;
    }

    pMsgData = (LVS_VOID*)malloc(pstValue->ulMsgLen);
    if(LVS_NULL_PTR == pMsgData)
    {
        return LVS_ERR;
    }
    memcpy(pMsgData, pstValue->pMsgData, pstValue->ulMsgLen);
    
    stMsg.ulSendPid = pstValue->ulSendPid;
    stMsg.ulReceivePid = pstValue->ulReceivePid;
    stMsg.ulMsgType = pstValue->ulMsgType;
    stMsg.ulMsgId = pstValue->ulMsgId;
    stMsg.ulMsgLen = pstValue->ulMsgLen;
    stMsg.pMsgData = pMsgData;
    stMsg.ulIsTimeConsuming = pstValue->ulIsTimeConsuming;

    if(LVS_TRUE == stMsg.ulIsTimeConsuming)
    {
        ulRet = pMessageQueue_TimeConsuming->LVSMsglistlnsert(&stMsg);
    }
    else
    {
        ulRet = pMessageQueue_Normal->LVSMsglistlnsert(&stMsg);
    }
    if(LVS_OK != ulRet)
    {
        if(LVS_NULL_PTR != pMsgData)
        {
            free(pMsgData);
            pMsgData = LVS_NULL_PTR;
        }
    }
    return ulRet;
}

LVS_UINT32 LVS_SendMsg(LVS_MSG_INFO_STRU *pstValue)
{
    return LVS_Message_Manager::sendMsg(pstValue);
}

