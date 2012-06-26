#pragma once

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <windows.h>    // ͷ�ļ�

#include "LVS_Call.h"
#include "LVS_IPTelNoBind.h"

using namespace std;

BRIINT32 WINAPI myCallBack(BRIINT16 uChannelID,BRIUINT32 dwUserData,BRIINT32 lType,BRIINT32 lHandle,BRIINT32 lResult,BRIINT32 lParam,BRIPCHAR8 pData,BRIPCHAR8 pDataEx)
{
#if 0
	cout<<"\n\n***** in my call back ******"<<endl;
	cout<<"BRIINT16 uChannelID = "<<uChannelID<<endl;
	cout<<"BRIUINT32 dwUserData = "<<dwUserData<<endl;
	cout<<"BRIINT32 lType = "<<lType<<endl;
	cout<<"BRIINT32 lHandle = "<<lHandle<<endl;
	cout<<"BRIINT32 lResult = "<<lResult<<endl;
	cout<<"BRIINT32 lParam = "<<lParam<<endl;
	cout<<"BRIPCHAR8 pData = "<<pData<<endl;
	cout<<"Length of pData = "<<strlen(pData)<<endl;
	cout<<"BRIPCHAR8 pDataEx = "<<pDataEx<<endl;
#endif

	LVS_UINT32 ulChannelID = (LVS_UINT32)uChannelID;
	BRIUINT32 length = 0;
	switch(lType)
	{
		case BriEvent_CallIn:
            {
                char chData = *(char*)pData;
                if(1 == lResult && '0' == chData) //��һ������ʱ��ŷ��͵�����Ϣ
                {
                    printString("** ��һ������ʱ��ŷ��͵�����Ϣ **",LVS_COLOR_WHITE,0);
                    
                    LVS_MSG_INFO_STRU stMsgInfo;
                    memset(&stMsgInfo, 0, sizeof(stMsgInfo));
                    
                    stMsgInfo.ulSendPid = PID_VOICE_PROXY;
                    stMsgInfo.ulReceivePid = PID_VOICE_PROXY;
                    stMsgInfo.ulMsgType = LVS_MSG_TYPE_DRIVE;
                    stMsgInfo.ulMsgLen = sizeof(ulChannelID);
                    stMsgInfo.pMsgData = (LVS_VOID*)&ulChannelID;
                    stMsgInfo.ulMsgId = UP_MSG_TYPE_DIALOG_POP;
                    stMsgInfo.ulIsTimeConsuming = LVS_FALSE;

					/*���͵�����Ϣ*/
					unsigned long ulRet = 0;
					ulRet = LVS_SendMsg(&stMsgInfo);
        			
                }
             } break;
        case BriEvent_GetCallID:
            {
                CC_CALLER_INFO_STRU callerInfo;
                memset(&callerInfo, 0, sizeof(callerInfo));
                //callerInfo.phoneNumber = pData;//���绰������Ϣд����Ϣ��ȥ
				if(strlen(pData) > sizeof(callerInfo.phoneNumber))
				{
					length = sizeof(callerInfo.phoneNumber);
				}
				else
				{
					length = strlen(pData);
				}
				memcpy(callerInfo.phoneNumber, pData, length);

				/*������ͨ���ŵ�callerInfo�ṹ����*/
				callerInfo.telChannelId = ulChannelID;
                
                LVS_MSG_INFO_STRU stMsgInfo;
                memset(&stMsgInfo, 0, sizeof(stMsgInfo));
                
                stMsgInfo.ulSendPid = PID_VOICE_PROXY;
                stMsgInfo.ulReceivePid = PID_VOICE_PROXY;
                stMsgInfo.ulMsgType = LVS_MSG_TYPE_DRIVE;
                stMsgInfo.ulMsgLen = sizeof(callerInfo);
                stMsgInfo.pMsgData = (LVS_VOID*)&callerInfo;
                stMsgInfo.ulMsgId = UP_MSG_TYPE_CALLER_INFO;
                stMsgInfo.ulIsTimeConsuming = LVS_TRUE;

    			LVS_UINT32 ulRet = 0;
                printString("** ����������Ϣд����Ϣ������ȥ **",LVS_COLOR_WHITE,0);

				ulRet = LVS_SendMsg(&stMsgInfo);
                printString("** ������������Ϣ���� **",LVS_COLOR_WHITE,0);
                //д�����ݿ��¼

            } break;
                
        case BriEvent_StopCallIn:
            {
                //cout<<"myCallBack_1"<<endl;
                LVS_MSG_INFO_STRU stMsgInfo;
                memset(&stMsgInfo, 0, sizeof(stMsgInfo));

				//cout<<"myCallBack_2"<<endl;
                
                stMsgInfo.ulSendPid = PID_VOICE_PROXY;
                stMsgInfo.ulReceivePid = PID_VOICE_PROXY;
                stMsgInfo.ulMsgType = LVS_MSG_TYPE_DRIVE;
                stMsgInfo.ulMsgLen = sizeof(ulChannelID);
                stMsgInfo.pMsgData = (LVS_VOID*)&ulChannelID;
                stMsgInfo.ulMsgId = UP_MSG_TYPE_STOP_CALLIN;
                stMsgInfo.ulIsTimeConsuming = LVS_FALSE;

				//cout<<"myCallBack_3"<<endl;

				unsigned long ulRet = 0;

                ulRet = LVS_SendMsg(&stMsgInfo);
                printString("** ����δ�ӵ绰��Ϣ���� **",LVS_COLOR_WHITE,0);
				//cout<<"myCallBack_4,"<<ulRet<<endl;
            }
        default:
            break;
	}


	return 0;
}

#if 0
#endif

void InitDevInfo()
{
    string tmpstr;
    tmpstr = "���豸�ɹ� ͨ����";
    tmpstr.append(changeLongToString((long) QNV_DevInfo(0,QNV_DEVINFO_GETCHANNELS)));
    tmpstr.append(" �豸��=");
    tmpstr.append(changeLongToString((long) QNV_DevInfo(0,QNV_DEVINFO_GETCHIPS)));
    printString(tmpstr,LVS_COLOR_WHITE,0);
    
	int ulRet = 0;
	for(BRIINT16 i=0;i<QNV_DevInfo(-1,QNV_DEVINFO_GETCHANNELS);i++)
	{
			printf("ͨ��ID=%d �豸ID=%d ���к�=%d оƬ����=%d \t\n",
			i,
			QNV_DevInfo(i,QNV_DEVINFO_GETDEVID),
			QNV_DevInfo(i,QNV_DEVINFO_GETSERIAL),				
			QNV_DevInfo(i,QNV_DEVINFO_GETCHIPTYPE)
			);

		QNV_SetParam(i,QNV_PARAM_DTMFNUM,7);

		//QNV_SetParam(i,QNV_PARAM_DIALVOL,130);
		//QNV_SetParam(i,QNV_PARAM_HANGUPELAPSE,10000);
		//QNV_Event(i,QNV_EVENT_REGWND,(DWORD)m_hWnd,NULL,NULL,0);//ʹ�ô�����Ϣ��ʽ��ȡ�¼�

        ulRet = QNV_Event(i,QNV_EVENT_REGCBFUNC, i ,(char*) myCallBack,NULL,0);
        //ulRet = QNV_Event(i,QNV_EVENT_REGCBFUNCEX, i ,(char*) myCallBackE,NULL,0);
	    cout<<ulRet<<endl;
	}
}

LVS_UINT32 LVS_CallMsgProc(LVS_VOID *pMsg)
{
	LVS_UINT32 ulSocketNum = 0;
	SOCKET_ID_LIST *pstSocketList = LVS_NULL_PTR;
	LVS_UINT32 ulChannelID = LVS_NULL_LONG;
	
	LVS_MSG_INFO_STRU *pReqMsg = (LVS_MSG_INFO_STRU*)pMsg;
	LVS_MSG_INFO_STRU stRespMsg;
	memset(&stRespMsg, 0, sizeof(stRespMsg));
	memcpy(&stRespMsg, pReqMsg, sizeof(stRespMsg));

	LVS_UINT32 ulRet =-1;
	switch(stRespMsg.ulMsgId)
	{
		case UP_MSG_TYPE_DIALOG_POP:
			printString("��������",LVS_COLOR_WHITE,0);
			if(LVS_NULL_PTR != stRespMsg.pMsgData && sizeof(LVS_UINT32) <= stRespMsg.ulMsgLen)
			{
				memcpy(&ulChannelID, stRespMsg.pMsgData, sizeof(LVS_UINT32));
				ulRet = getSocketListByTelNo(ulChannelID,&pstSocketList,&ulSocketNum);
				if(LVS_OK != ulRet)
				{
					printString("LVS_CallMsgProc->getSocketListByTelNo Failed",LVS_COLOR_LIGHTRED,LVS_FALSE);
					return LVS_ERR;
				}
				while(LVS_NULL_PTR != pstSocketList)
				{
					stRespMsg.lSocketId = pstSocketList->lSocketId;
					packToJsonStringAndSend(&stRespMsg);
					pstSocketList = pstSocketList->pnext;
				}
			}
            //packToJsonStringAndSend(&stRespMsg);
			break;
        case UP_MSG_TYPE_CALLER_INFO:
            {
                printString("���͵绰����",LVS_COLOR_WHITE,0);
                
			    CC_CALLER_INFO_STRU callerInfo;
				memset(&callerInfo, 0, sizeof(callerInfo));
				memcpy(&callerInfo, stRespMsg.pMsgData, sizeof(callerInfo));

				stRespMsg.pMsgData = &callerInfo;
				stRespMsg.ulMsgLen = sizeof(callerInfo);

				
                /*�ȷ�һ��ֻ�е绰�������Ϣ*/
                LVS_UINT32 uChannelID = callerInfo.telChannelId;
				ulRet = getSocketListByTelNo(uChannelID,&pstSocketList,&ulSocketNum);
				if(LVS_OK != ulRet)
				{
			    	ulRet = packToJsonStringAndSend(&stRespMsg);
				}
				else 
				{
					while(LVS_NULL_PTR != pstSocketList)
					{
						stRespMsg.lSocketId = pstSocketList->lSocketId;
						ulRet = packToJsonStringAndSend(&stRespMsg);
						pstSocketList = pstSocketList->pnext;
					}
				}


                /*д�����ݿ��¼*/
                if(LVS_OK != insertTaskList(&callerInfo))
                {
                    printString("Error ** insertTaskList IN UP_MSG_TYPE_CALLER_INFO ** error!", LVS_COLOR_LIGHTRED,0);
                }
               
                /*��ѯ���ݿ�*/
                if(LVS_OK != queryCallerInfo(&callerInfo))
                {
                    printString("Error ** queryCallerInfo IN UP_MSG_TYPE_CALLER_INFO ** error!", LVS_COLOR_LIGHTRED,0);
                }

                /*������������ϸ��Ϣ*/
				ulRet = getSocketListByTelNo(uChannelID,&pstSocketList,&ulSocketNum);
				if(LVS_OK != ulRet)
				{
			    	ulRet = packToJsonStringAndSend(&stRespMsg);
				}
				else 
				{
					while(LVS_NULL_PTR != pstSocketList)
					{
						stRespMsg.lSocketId = pstSocketList->lSocketId;
						ulRet = packToJsonStringAndSend(&stRespMsg);
						pstSocketList = pstSocketList->pnext;
					}
				}

          
            }
			break;
		case BriEvent_StopCallIn:
			cout<<"�Է�ֹͣ����(����һ��δ�ӵ绰)"<<endl;
            
			break;
		default:
			break;
	}
	return LVS_OK;
}

LVS_UINT32 LVS_ClientMsgProc(LVS_VOID *pMsg)
{
	LVS_MSG_INFO_STRU *pReqMsg = (LVS_MSG_INFO_STRU*)pMsg;
	LVS_MSG_INFO_STRU stRespMsg;
	memset(&stRespMsg, 0, sizeof(stRespMsg));
	memcpy(&stRespMsg, pReqMsg, sizeof(stRespMsg));
            

	LVS_UINT32 ulRet =-1;
	switch(stRespMsg.ulMsgId)
	{
		case DOWN_MSG_TYPE_QUERY_STAFF_INFO_REQUEST:

            CC_QUERY_STAFF_KEY_INFO_STRU queryStaffInfo;
            memset(&queryStaffInfo, 0, sizeof(queryStaffInfo));
            memcpy(&queryStaffInfo, stRespMsg.pMsgData, sizeof(queryStaffInfo));

            stRespMsg.pMsgData = &queryStaffInfo;
            //stRespMsg.ulMsgLen = sizeof(queryStaffInfo);
            
			printString("����ƴ������ĸ��ѯԱ������", LVS_COLOR_WHITE,0);
            
            if(LVS_OK != queryStaffInfoUseNameSpell(&stRespMsg))
        	{
        		printString("Error ** queryStaffInfoUseNameSpell ** error!", LVS_COLOR_LIGHTRED,0);
        	}
            
            stRespMsg.ulMsgId = UP_MSG_TYPE_STAFF_INFO;            
            packToJsonStringAndSend(&stRespMsg);

            /*�ͷ��ڴ�*/
            if(LVS_NULL_PTR != stRespMsg.pMsgData)
            {
                free(stRespMsg.pMsgData);
                stRespMsg.pMsgData = LVS_NULL_PTR;
            }
            
			break;
		case DOWN_MSG_TYPE_UPDATE_CALLER_INFO:
            {
        		printString("���������߼�¼", LVS_COLOR_WHITE,0);
                
                CC_CALLER_INFO_STRU callerInfo;
                
                memset(&callerInfo, 0, sizeof(callerInfo));
                memcpy(&callerInfo, stRespMsg.pMsgData, sizeof(callerInfo));

                if(LVS_OK != insertCallerInfo(&callerInfo))
                {
                    printString("Error ** insertCallerInfo ** error!", LVS_COLOR_LIGHTRED,0);
                }
            }
			break;
            
		case DOWN_MSG_TYPE_TASK_DISPATCH:
			{
                printString("������ǲ��Ϣ", LVS_COLOR_WHITE, 0);

                CC_TASK_DISPATCH_INFO_STRU taskDispatchInfo;
                memset(&taskDispatchInfo, 0, sizeof(taskDispatchInfo));
                memcpy(&taskDispatchInfo, stRespMsg.pMsgData, sizeof(taskDispatchInfo));
                                
                if(LVS_OK != updateTaskList(&taskDispatchInfo))
                {
                    printString("Error ** updateTaskList ** error!", LVS_COLOR_LIGHTRED,0);
                }

                if(LVS_OK != insertTaskDtl(&taskDispatchInfo))
                {
                    printString("Error ** insertTaskDtl ** error!", LVS_COLOR_LIGHTRED,0);
                }

                if(1 == taskDispatchInfo.isReserve) /*�����ԤԼ��Ϣ������Ҫ����ԤԼ����״̬*/
                {
                    if(LVS_OK != updateReserveList(&taskDispatchInfo))
                    {
                        printString("Error ** updateReserveList ** error!", LVS_COLOR_LIGHTRED,0);
                    }                    
                }
            }
            break;
        case DOWN_MSG_TYPE_RESERVE_INFO:
            {
                printString("����ԤԼ��Ϣ", LVS_COLOR_WHITE, 0);
                if(LVS_NULL_PTR == stRespMsg.pMsgData)
                {
                    printString("LVS_ClientMsgProc->DOWN_MSG_TYPE_RESERVE_INFO InValid Input,It is NULL",LVS_COLOR_LIGHTRED,LVS_FALSE);
                    return LVS_ERR;
                }

                CC_TASK_DISPATCH_INFO_STRU taskDispatchInfo;
                memset(&taskDispatchInfo, 0, sizeof(taskDispatchInfo));
                memcpy(&taskDispatchInfo, stRespMsg.pMsgData, sizeof(taskDispatchInfo));

                
                if(LVS_OK != insertTaskListReserve(&taskDispatchInfo))
                {
                    printString("Error ** insertTaskListReserve in DOWN_MSG_TYPE_RESERVE_INFO error!", LVS_COLOR_LIGHTRED,0);
                }

                if(LVS_OK != insertTaskDtl(&taskDispatchInfo))
                {
                    printString("Error ** insertTaskDtl in DOWN_MSG_TYPE_RESERVE_INFO error!", LVS_COLOR_LIGHTRED,0);
                }

                if(LVS_OK != insertReserveList(&taskDispatchInfo))
                {
                    printString("Error ** insertReserveList in DOWN_MSG_TYPE_RESERVE_INFO error!", LVS_COLOR_LIGHTRED,0);
                }                

                updateReserveRestTime();
                
            }
            break;
        case DOWN_MSG_TYPE_VIEW_TASK_LIST_BETWEEN_S_AND_E:
            {
                printString("�鿴ĳ����֮�����Ϣ��¼", LVS_COLOR_WHITE, 0);

		        if(LVS_OK != quaryTaskListBetweenStartAndEnd(&stRespMsg))
		    	{
		    		printString("Error ** quaryTaskListBetweenStartAndEnd ** error!", LVS_COLOR_LIGHTRED,0);
		    	}
				stRespMsg.ulMsgId = UP_MSG_TYPE_TASK_LIST_BETWEEN_S_AND_E;
		        packToJsonStringAndSend(&stRespMsg);

		        /*�ͷ��ڴ�*/
		        if(LVS_NULL_PTR != stRespMsg.pMsgData)
		        {
		            free(stRespMsg.pMsgData);
		            stRespMsg.pMsgData = LVS_NULL_PTR;
		        }
            }
			break;
		case DOWN_MSG_TYPE_GET_TASK_INFO:
			{
				printString("���������������͸��ͻ���", LVS_COLOR_WHITE, 0);

				if(LVS_OK != quaryAllTaskTypeList(&stRespMsg))
				{
					printString("Error ** quaryAllTaskTypeList ** error!", LVS_COLOR_LIGHTRED,0);
				}
				stRespMsg.ulMsgId = UP_MSG_TYPE_GET_ALL_TASK_INFO;
				packToJsonStringAndSend(&stRespMsg);

				/*�ͷ��ڴ�*/
				if(LVS_NULL_PTR != stRespMsg.pMsgData)
				{
					free(stRespMsg.pMsgData);
					stRespMsg.pMsgData = LVS_NULL_PTR;
				}
			}
			break;
        case DOWN_MSG_TYPE_HEAT_BEAT:
			{
				stRespMsg.ulMsgId = UP_MSG_TYPE_RESP_HEAT_BEAT;
				packToJsonStringAndSend(&stRespMsg);
				/*�ͷ��ڴ�*/
				if(LVS_NULL_PTR != stRespMsg.pMsgData)
				{
					free(stRespMsg.pMsgData);
					stRespMsg.pMsgData = LVS_NULL_PTR;
				}
        	}
            break;

		default:
			break;
	}
	return LVS_OK;
}

