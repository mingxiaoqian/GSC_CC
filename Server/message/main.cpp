#include <cstdlib>
#include <iostream>

#include "LVSMsgList.h"
#include "LVSMsgManager.h"
#include "LVS_PID_Init.h"

using namespace std;

int main(int argc, char *argv[])
{

    LVS_MSG_INFO_STRU stMsgInfo = {PID_STUB_TEST,PID_STUB_TEST,0,0, LVS_FALSE,0,LVS_NULL_PTR};

    //LVS_Message_Manager::RegisterMsgPidEx();
    LVS_Message_Manager *pMsgManager = LVS_Message_Manager::CreateMsgManager(5,1);
    if(LVS_NULL_PTR == pMsgManager)
    {
        return LVS_OK;
    }
    pMsgManager->start();

    LVS_UINT32 i = 0;
    LVS_UINT32 ultype;
    i = 0;
    while(i < 100)
    {
        ultype = i % 4;
        stMsgInfo.ulMsgType = ultype;
        if(0 == ultype)
        {
            stMsgInfo.ulIsTimeConsuming = LVS_TRUE;
        }
        else
        {
            stMsgInfo.ulIsTimeConsuming = LVS_FALSE;
        }
        LVS_SendMsg(&stMsgInfo);
        i++;
    }
    
    system("PAUSE");
    return EXIT_SUCCESS;
}
