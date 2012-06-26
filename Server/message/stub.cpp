#include "LVS_define.h"
#include "LVS_PID_Init.h"

LVS_UINT32 MsgProc_Stub(LVS_VOID *pMsg)
{
    LVS_MSG_INFO_STRU *pReqMsg = (LVS_MSG_INFO_STRU*)pMsg;
    switch(pReqMsg->ulMsgType)
    {
    case 1:
        Sleep(100);
        cout<<"Cat!----1\r\n";
        break;
    case 2:
        Sleep(300);
        cout<<"Dog!----2\r\n";
        break;
    case 3:
        Sleep(900);
        cout<<"Pig!----3\r\n";
        break;
    default:
        Sleep(5000);
        cout<<"Chook!----other\r\n";
    }
    return LVS_OK;
};

