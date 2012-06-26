#include "LVS_define.h"
#include "LVS_PID_Init.h"
#include "LVS_Message_Struct_define.h"

LVS_UINT32 MsgProc_Stub(LVS_VOID *pMsg)
{
    LVS_MSG_INFO_STRU *pReqMsg = (LVS_MSG_INFO_STRU*)pMsg;
    switch(pReqMsg->ulMsgType)
    {
    case 1:
        Sleep(100);
        //cout<<"Cat!----1\r\n";
        printf("Cat!----1________%d\r\n",pReqMsg->ulMsgId);
        break;
    case 2:
        Sleep(300);
        //cout<<"Dog!----2\r\n";
        printf("Dog!----2________%d\r\n",pReqMsg->ulMsgId);
        break;
    case 3:
        Sleep(900);
        //cout<<"Pig!----3\r\n";
        printf("Pig!----3________%d\r\n",pReqMsg->ulMsgId);
        break;
    default:
        Sleep(5000);
        //cout<<"Chook!----other\r\n";
        printf("Chook!----other________%d\r\n",pReqMsg->ulMsgId);
        break;
    }
    return LVS_OK;
};

extern LVS_UINT32 packToJsonStringAndSend(LVS_MSG_INFO_STRU *pstMsg);
#if 0
LVS_UINT32 LVS_CallMsgProc(LVS_VOID *pMsg)
{
	LVS_MSG_INFO_STRU stInfo = {0};
	stInfo.ulMsgId = 1002;
	string phone = "18768163484";
	stInfo.pMsgData = (LVS_VOID *)phone.c_str();
	stInfo.ulMsgLen = phone.length();
	stInfo.ulSendPid = 1001;
	stInfo.ulReceivePid = 1001;
	packToJsonStringAndSend(&stInfo);

	return 0;
}
#endif
LVS_UINT32 LVS_ClientMsgProc(LVS_VOID *pMsg)
{
	return 0;
	LVS_MSG_INFO_STRU stInfo = {0};
	stInfo.ulMsgId = 1002;
	string phone = "18768163484";
	stInfo.pMsgData = (LVS_VOID *)phone.c_str();
	stInfo.ulMsgLen = phone.length();
	stInfo.ulSendPid = 1001;
	stInfo.ulReceivePid = 1001;
	packToJsonStringAndSend(&stInfo);


    CC_STAFF_INFO_SET_STRU *pstStaffInfoSet = (CC_STAFF_INFO_SET_STRU*)malloc(10*sizeof(CC_STAFF_INFO_STRU));

    if(LVS_NULL_PTR == pstStaffInfoSet)
    {
        return 0;
    }
    memset(pstStaffInfoSet, 0 ,10*sizeof(CC_STAFF_INFO_STRU));
    CC_STAFF_INFO_STRU *pstStaffInfo = LVS_NULL_PTR;
    for(int i = 0; i < 10; i++)
    {
        pstStaffInfo = (CC_STAFF_INFO_STRU*)(pstStaffInfoSet->stStaffInfoList) + i;
        memcpy(pstStaffInfo->name,"QianMing",8);
        memcpy(pstStaffInfo->nameSpell,"QM",2);
        memcpy(pstStaffInfo->userNumber,"123",3);
        memcpy(pstStaffInfo->post,"ZG",2);
        memcpy(pstStaffInfo->callNumber,"123",3);
        memcpy(pstStaffInfo->phoneNumber,"13661626834",11);
        pstStaffInfo->state = 0;
        
    }

    stInfo.ulMsgId = 1004;
    stInfo.ulSendPid = 1002;
	stInfo.ulReceivePid = 1002;
    stInfo.ulMsgLen = 10*sizeof(CC_STAFF_INFO_STRU);
    stInfo.pMsgData = (LVS_VOID *)pstStaffInfoSet;
    packToJsonStringAndSend(&stInfo);

    free(pstStaffInfoSet);
    pstStaffInfoSet = NULL;
    
	return 0;
}