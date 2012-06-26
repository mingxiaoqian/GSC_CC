#include "Pbx.h"
#include "LVSMsgManager.h"
#include <iostream>

using namespace std;

CH_INFO ChInfo[MAX_CH];
LVS_INT32 nMaxCh;

int CALLBACK MyCallback (WORD wEvent, int nReference, DWORD dwParam, DWORD dwUser)
{
	LVS_MSG_INFO_STRU stMsgInfo;
    PARA_INFO stParaInfo;

    memset(&stMsgInfo, 0, sizeof(stMsgInfo));
    memset(&stParaInfo, 0, sizeof(stParaInfo));

    stParaInfo.wParam = (LVS_INT32)nReference;
    stParaInfo.lParam = (LVS_INT32)dwParam;
    stParaInfo.dwUser = (LVS_INT32)dwUser;

    stMsgInfo.ulSendPid = PID_VOICE_PROXY;
    stMsgInfo.ulReceivePid = PID_VOICE_PROXY;
    stMsgInfo.ulMsgType = PBX_MSG_TYPE_DRIVE;
    stMsgInfo.ulMsgId = (LVS_UINT32)wEvent;
    stMsgInfo.ulIsTimeConsuming = LVS_FALSE;
    stMsgInfo.ulMsgLen = sizeof(stParaInfo);
    stMsgInfo.pMsgData = (LVS_VOID*)&stParaInfo;

    return LVS_SendMsg(&stMsgInfo);
    
}


BOOL IntiCtiBoard(LVS_VOID)
{
    char szCurPath[MAX_PATH];		//current path
	char szShIndex[MAX_PATH];		//path of file ShIndex.ini
	char szShConfig[MAX_PATH];		//path of file ShConfig.ini
	string CErrMsg;			//error message

	GetCurrentDirectory(MAX_PATH, szCurPath);
	strcpy(szShIndex, szCurPath);
	strcpy(szShConfig, szCurPath);
	strcat(szShIndex, "\\ShIndex.ini");
	strcat(szShConfig, "\\ShConfig.ini");
	
	//load configuration file and initialize system 
	if (SsmStartCti(szShConfig, szShIndex) == -1)
	{
		//SsmGetLastErrMsg(CErrMsg.GetBuffer(300));	//300-character buffer at minimum
		//AfxMessageBox(CErrMsg, MB_OK);
		//CErrMsg.ReleaseBuffer();
		return FALSE;
	}
	
	//to judge whether number of voice board initialized successfully equials that of 
	//voice board set in configuration file. 
	if(SsmGetMaxUsableBoard() != SsmGetMaxCfgBoard())
	{
		//SsmGetLastErrMsg(CErrMsg.GetBuffer(300));	//300-character buffer at minimum 
		//AfxMessageBox(CErrMsg, MB_OK);
		//CErrMsg.ReleaseBuffer();
		return FALSE;
	}

    //设置驱动程序抛出事件的模式
	EVENT_SET_INFO EventMode;
	EventMode.dwWorkMode = EVENT_CALLBACK; 				//事件回调模式
	EventMode.lpHandlerParam = (void*)MyCallback; 			//注册回调函数
	SsmSetEvent(0xffff,-1,true, &EventMode);

	return TRUE;
}
LVS_VOID IntiChList()
{
    char szChNum[10];       //channel number 
    char szChType[100];     //channel type
    int  nIndex;            //list index 

    char szPhoneNumConfig[MAX_PATH];
    char KeyName[50];
    LPCTSTR lpAppName = "USERNUM";
    GetCurrentDirectory(MAX_PATH, szPhoneNumConfig);
    strcat(szPhoneNumConfig, "\\pbx.ini");
    
    nIndex =0;
    #if 0
    //to initialize list 
    //LV_COLUMN lvcChList[MAX_CHLIST_ITEM];
    LIST_PARA MainList[MAX_CHLIST_ITEM] = 
        {
            {24 ,"Ch"},
            {130 ,"ChType"},
            {130 ,"Status"},
            {80 ,"CallerId"},
            {80 ,"CalleeId"},
            {100 ,"DTMFBuffer"},
        };

    
    for(int i=0; i<MAX_CHLIST_ITEM; i++)
    {
        lvcChList[i].mask = LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM | LVCF_FMT;
        lvcChList[i].iSubItem = i;
        lvcChList[i].pszText  = MainList[i].szText;
        lvcChList[i].cx       = MainList[i].ColumnWidth;
        lvcChList[i].fmt      = LVCFMT_RIGHT;
        m_ChList.InsertColumn(i, &lvcChList[i]);    
    }
    
    m_ChList.SetExtendedStyle(m_ChList.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
    #endif

    nMaxCh = SsmGetMaxCh();     //to retrieve max channel number set in configuration file 

    //to initialize each on-board channel 
    if(nMaxCh >= 0)
    {
        for(int ch=0, i=1; ch<nMaxCh; ch++)
        {
            ChInfo[ch].nLinkToCh  = -1;
            ChInfo[ch].nIndex = -1;
            ChInfo[ch].nTimer = -1;
            ChInfo[ch].nSaveSubmiteCh = -1;
            ChInfo[ch].bPressFlag = FALSE;
            ChInfo[ch].bSubmiteChHookFlag = FALSE;
            memset(ChInfo[ch].szCallerId, '\0', sizeof(char)*NUM_LENGTH);       //to clear CallerId buffer 
            memset(ChInfo[ch].szCalleeId, '\0', sizeof(char)*NUM_LENGTH);       //to clear CalledId buffer
            
            //to retrive channel type information 
            if( (ChInfo[ch].nChType = SsmGetChType(ch)) == -1 )
            {
                /*记日志，输出错误信息*/
                //AfxMessageBox(_T("Call of function SsmGetChType() failed at initialization"));
            }

            //to judge whether a channel is analog station or trunk channel 
            if(ChInfo[ch].nChType != 0 && ChInfo[ch].nChType !=2) 
            {
                continue;
            }

            //to clear DTMF buffer 
            if(SsmClearRxDtmfBuf(ch) == -1)
            {
                /*记日志，输出错误信息*/
                //AfxMessageBox(_T("Call of function SsmClearRxDtmfBuf() failed at initialization "));
            }
            
            //m_ChList.InsertItem(ch, _itoa(ch,szChNum,10));

            switch(ChInfo[ch].nChType)
            {
            case 0:
                ChInfo[ch].nStatus = TRUNK_IDLE;
                wsprintf(szChType, "Trunk");
                ChInfo[ch].nIndex = nIndex;
                break;
            case 2:
                ChInfo[ch].nStatus = USER_IDLE;
                wsprintf(szChType, "Station");
                ChInfo[ch].nIndex = nIndex;
                
                wsprintf(KeyName, "UserChPhoNum[%d]", i);
                
                GetPrivateProfileString(lpAppName, KeyName, "XXXXXXXX", ChInfo[ch].CUserNum, 16, szPhoneNumConfig);
                wsprintf(szChType,"Station %s",ChInfo[ch].CUserNum);
                //itoa(nPhoneNum, ChInfo[ch].CUserNum.GetBuffer(10), 10);
                if(SsmSetASDT(ch, 1) == -1)
                {
                    /*记日志，输出错误信息*/
                    //AfxMessageBox(_T("Call of function SsmSetASDT() failed at initialization "));
                }

                i++;
                //nPhoneNum++;
                break;
            default:
                break;
            }

            nIndex++;
        }
    }
    else
    {
        if(nMaxCh == -1)
        {
            /*记日志，输出错误信息*/
            //AfxMessageBox(_T("Call of function SsmGetMaxCh() failed at initialization "));
        }
    }

}

LVS_VOID SendMessage(LVS_INT32 ulEventId, LVS_INT32 wParam, LVS_INT32 lParam)
{
	LVS_MSG_INFO_STRU stMsgInfo;
    PARA_INFO stParaInfo;

    memset(&stMsgInfo, 0, sizeof(stMsgInfo));
    memset(&stParaInfo, 0, sizeof(stParaInfo));
    
    stMsgInfo.ulSendPid = PID_VOICE_PROXY;
    stMsgInfo.ulReceivePid = PID_VOICE_PROXY;
    stMsgInfo.ulMsgType = PBX_MSG_TYPE_USER;
    stMsgInfo.ulMsgLen = sizeof(stParaInfo);
    stMsgInfo.pMsgData = (LVS_VOID*)&stParaInfo;

    stMsgInfo.ulMsgId = ulEventId;
    stParaInfo.wParam = wParam;
    stParaInfo.lParam = lParam;
    LVS_SendMsg(&stMsgInfo);

}


LVS_UINT32 LVS_PbxMsgProc(LVS_VOID *pMsg)
{
    /* TODO: Add your specialized code here and/or call the base class */
    
	LVS_INT32 nCh;			//channel number
	LVS_INT32 nCheckChNum;
    LVS_INT32 wParam;
    LVS_INT32 lParam;
    PARA_INFO *pstParaInfo;
    
    if(LVS_NULL_PTR == pMsg)
    {
        /*记日志*/
        return LVS_ERR;
    }
    
    LVS_MSG_INFO_STRU *pstReqMsg = (LVS_MSG_INFO_STRU*)pMsg;

    if(sizeof(PARA_INFO) < pstReqMsg->ulMsgLen)
    {
        /*记日志*/
        return LVS_ERR;
    }
    pstParaInfo = (PARA_INFO*)pstReqMsg->pMsgData;
    wParam = pstParaInfo->wParam;
    lParam = pstParaInfo->lParam;
    
    switch(pstReqMsg->ulMsgId)
    {
        case E_SYS_TIMEOUT:
			//to identify channel number according to timer ID 
			for(nCheckChNum=0; nCheckChNum<nMaxCh; nCheckChNum++)
			{
				if(wParam == (LVS_INT32)ChInfo[nCheckChNum].nTimer)
				{
					nCh = nCheckChNum;
					break;
				}
			}
			
			if(nCheckChNum == nMaxCh)
			{
			    /*记日志*/
				return LVS_ERR;
			}
			break;
		case E_CHG_HookState:
		case E_CHG_RcvDTMF:
		case E_CHG_FlashCount:
		case E_CHG_ChState:
		case E_US_SEIZURE:
		case E_US_RELEASE:
		case E_US_SEIZURE_ACK_IDLE:
		case E_US_SEIZURE_ACK_BUSY:
		case E_US_PICKUP:
		case E_US_SEIZURE_TK:
		case E_TK_SEIZURE_TK_ACK_IDLE:
		case E_TK_SEIZURE_TK_ACK_BUSY:
		case E_TK_RELEASE:
		case E_US_DTMF2TK:
		case E_TK_DIAL_OK:
		case E_TK_DIAL_FAIL:
		case E_TK_REMOTE_NOANSWER:
		case E_TK_REMOTE_PICKUP:
		case E_MSG_RELEASE:
		case E_MSG_FLASH:
		case E_MSG_CONNECT:
		case E_MSG_HANGUP:
		case F_US_SEIZURE:
			nCh = wParam;
			break;
		default:
            /*此处记日志*/
			return LVS_ERR;
			break;
    }
    //analog station or trunk channel 
	switch(ChInfo[nCh].nChType)
	{
	case 0:
		TrunkProc(pstReqMsg->ulMsgId, nCh, lParam);
		//UpdateChList(nCh);
		break;
	case 2:
		UserProc(pstReqMsg->ulMsgId, nCh, lParam);
		//UpdateChList(nCh);
		break;
	default:
		break;
	}
    
}


#if 0
LVS_VOID UpdateChList(int nCh)
{
    CString CNewState;			//new channel state 
	char	szTmpStr[201];		//DTMF buffer 
	
	switch(ChInfo[nCh].nStatus)
	{
	case USER_IDLE:					CNewState = "Idle";					break;
	case USER_LOCAL_RING:			CNewState = "Ringing";					break;
	case USER_GET_1STDTMF:			CNewState = "Select call type";			break;
	case USER_GET_DTMF:				CNewState = "Wait DTMF";		break;
	case USER_REQ_USER:				CNewState = "Wait response";				break;
	case USER_RING_BACK:			CNewState = "Ring back";					break;
	case USER_REQ_TRUNK:			CNewState = "Station request trunk";			break;
	case USER_DIALOUT:				CNewState = "Send Dtmf to trunk";			break;
	case USER_WAIT_REMOTE_PICKUP:	CNewState = "Wait called party's answer";			break;
	case USER_TALKING:				CNewState = "Talking";					break;
	case USER_WAIT_HANGUP:			CNewState = "Wait hangup";				break;
	case TRUNK_IDLE:				CNewState = "Idle";					break;
	case TRUNK_WAIT_1STNUM:			CNewState = "Wait dialing";				break;
	case TRUNK_DIALING:				CNewState = "Dialing";				break;
	case TRUNK_WAIT_REMOTE_PICKUP:	CNewState = "Ring back";					break;
	case TRUNK_WAIT_ACTUAL_PICKUP:	CNewState = "Ringing";					break;
	case TRUNK_WAIT_SELECTION:		CNewState = "Dial extension";				break;
	case TRUNK_REQ_USER:			CNewState = "Wait dial-up result";			break;
	case TRUNK_RING_BACK:			CNewState = "Play backgroun music";				break;
	case TRUNK_CONNECTED:			CNewState = "Talking";					break;
	case USER_F_GET_DTMF:			CNewState = "Dial number of extension to be transferred";			break;
	case USER_F_REQ_USER:			CNewState = "Wait extension's response";			break;
	case USER_F_RING_BACK:			CNewState = "Ring back";					break;
	case USER_F_TALKING:			CNewState = "Talking";			break;
	case USER_F_OPERATE:			CNewState = "Wait next step";		break;
	case USER_F_WAIT_TALK:			CNewState = "Wait connection with destination phone";	break;
	case TRUNK_FLASHING:			CNewState = "wait connection with destination phone";	break;
	default:
		break;
	}
	
	//to retrieve DTMF, size of dtmf buffer can be set in configuration file, with default value of 200 characters 
	if(SsmGetDtmfStr(nCh, szTmpStr) == -1)
	{
		AfxMessageBox(_T("call of functino SsmGetDtmfStr() failed in function UpdateChList()"));
	}

	//update channel information in list 
	m_ChList.SetItemText(ChInfo[nCh].nIndex, ITEM_ChState, CNewState);					//display channel number 
	m_ChList.SetItemText(ChInfo[nCh].nIndex, ITEM_CallerId, ChInfo[nCh].szCallerId);	//display CallerId 
	m_ChList.SetItemText(ChInfo[nCh].nIndex, ITEM_CalleeId, ChInfo[nCh].szCalleeId);	//display CalledId	
	m_ChList.SetItemText(ChInfo[nCh].nIndex, ITEM_RxDTMF, szTmpStr);					//display DTMF

	return;
}
#endif
LVS_VOID UserProc(LVS_INT32 event, LVS_INT32 wParam, LVS_INT32 lParam)
{
    int nCh;						//number of station channel 
	DWORD dwDtmfLen;				//length of DTMF received
	UCHAR dwDtmfNum;				// DTMF received
	LONG nHook;						//nHook:0---station channel go on-hook; 1---station channel go off-hook 
	char szVoicePath[MAX_PATH];		//sound file 
	int nToneType = -2;				//tone type
	int nToneChResult;				//tone detection result
	int nPlayResult;				//return value of function SsmCheckPlay()

    
	nCh = wParam;
        
    switch(event)
    {
	/*+++++++++driver message +++++++++*/
	case E_CHG_HookState:		//station hook change event
		nHook = lParam;
		if(nHook == 0)			//station channel go on-hook 
		{
			switch(ChInfo[nCh].nStatus)
			{
			case USER_GET_1STDTMF:
				//close T1
				if(SsmStopTimer(ChInfo[nCh].nTimer) == -1)	
				{
					ShowErrMsg("E_CHG_HookState", "USER_GET_1STDTMF", "SsmStopTimer");
				}
				break;
			case USER_GET_DTMF:
				//close T2
				if(SsmStopTimer(ChInfo[nCh].nTimer) == -1)	
				{
					ShowErrMsg("E_CHG_HookState", "USER_GET_DTMF", "SsmStopTimer");
				}
				break;
			case USER_REQ_USER:
				//send E_US_RELEASE
				SendMessage(E_US_RELEASE, ChInfo[nCh].nLinkToCh, nCh);
				break;
			case USER_RING_BACK:
				//send E_US_RELEASE to channel Ch-k
				SendMessage(E_US_RELEASE, ChInfo[nCh].nLinkToCh, nCh);
				break;
			case USER_TALKING:
				//tear down bus connection 
				if(SsmStopTalkWith(nCh, ChInfo[nCh].nLinkToCh) == -1)		
				{
					ShowErrMsg("E_CHG_HookState", "USER_TALKING", "SsmStopTalkWith");
				}
				//to send E_MSG_RELEASE to channel connected 
				SendMessage(E_MSG_RELEASE, ChInfo[nCh].nLinkToCh, nCh);
				break;
			case USER_WAIT_HANGUP:
				break;
			case USER_REQ_TRUNK:
				break;
			case USER_DIALOUT:
				//close T3
				if(SsmStopTimer(ChInfo[nCh].nTimer) == -1)	
				{
					ShowErrMsg("E_CHG_HookState", "USER_DIALOUT", "SsmStopTimer");
				}
				//send E_TK_RELEASE
				SendMessage(E_TK_RELEASE, ChInfo[nCh].nLinkToCh, nCh);
				break;
			case USER_WAIT_REMOTE_PICKUP:
				//send E_TK_RELEASE
				SendMessage(E_TK_RELEASE, ChInfo[nCh].nLinkToCh, nCh);
				break;
			case USER_F_WAIT_TALK:
				//stop playback of background music 
				nPlayResult = SsmCheckPlay(nCh);
				if(nPlayResult != -1)
				{
					if(nPlayResult == 0)
					{
						if(SsmStopPlayFile(nCh) == -1)
						{
							ShowErrMsg("E_CHG_HookState", "USER_F_WAIT_TALK", "SsmStopPlayFile");
						}
					}
				}
				else
				{
					ShowErrMsg("E_CHG_HookState", "USER_F_WAIT_TALK", "SsmCheckPlay");
				}
				//E_MSG_HANGUP→ch1
				SendMessage(E_MSG_HANGUP, ChInfo[nCh].nLinkToCh, nCh);
				break;
			case USER_F_GET_DTMF:
				//close T4
				if(SsmStopTimer(ChInfo[nCh].nTimer) == -1)	
				{
					ShowErrMsg("E_CHG_HookState", "USER_F_GET_DTMF", "SsmStopTimer");
				}
				//E_MSG_RELEASE→ch0
				if(!ChInfo[nCh].bSubmiteChHookFlag)
				{
					SendMessage(E_MSG_RELEASE, ChInfo[nCh].nSaveSubmiteCh, nCh);
				}
				break;
			case USER_F_REQ_USER:
				//E_MSG_RELEASE→ch0
				if(!ChInfo[nCh].bSubmiteChHookFlag)
				{
					SendMessage(E_MSG_RELEASE, ChInfo[nCh].nSaveSubmiteCh, nCh);
				}
				break;
			case USER_F_RING_BACK:
				//masked by wangfeng for sc-1007(闪断接续问题), 2008.06.03
				/*

				//E_US_RELEASE→ch2
				SendMessage(WM_USER+E_US_RELEASE, ChInfo[nCh].nLinkToCh, nCh);	
				//E_MSG_RELEASE→ch0
				if(!ChInfo[nCh].bSubmiteChHookFlag)
				{
					SendMessage(WM_USER+E_MSG_RELEASE, ChInfo[nCh].nSaveSubmiteCh, nCh);	

				}*/
				//masked by wangfeng for sc-1077(闪断接续问题), 2008.06.03
				//added by wangfeng for sc-1077(闪断接续问题), 2008.06.03
				if(!ChInfo[nCh].bSubmiteChHookFlag)
				{
					ChInfo[ChInfo[nCh].nLinkToCh].nLinkToCh = ChInfo[nCh].nSaveSubmiteCh;
					SendMessage(E_MSG_CONNECT,ChInfo[nCh].nSaveSubmiteCh,ChInfo[nCh].nLinkToCh);
					/*if(SsmTalkWith(ChInfo[nCh].nSaveSubmiteCh, ChInfo[nCh].nLinkToCh) == -1)
					{
						ShowErrMsg("E_CHG_HookState", "USER_F_TALKING", "SsmTalkWith");
					}*/
					
					ChInfo[ChInfo[nCh].nLinkToCh].bPressFlag = FALSE;
				}
				//added by wangfeng for sc-1077(闪断接续问题), 2008.06.03
				break;
			case USER_F_TALKING:
				//tear down bus connection between ch1 and ch2
				if(SsmStopTalkWith(nCh, ChInfo[nCh].nLinkToCh) == -1)
				{
					ShowErrMsg("E_CHG_HookState", "USER_F_TALKING", "SsmStopTalkWith");
				}
				
				if(!ChInfo[nCh].bSubmiteChHookFlag)	//Ch0 go off-hook, Flag==0?
				{
					ChInfo[ChInfo[nCh].nLinkToCh].nLinkToCh = ChInfo[nCh].nSaveSubmiteCh;
					
					//E_MSG_CONNECT→ch0
					SendMessage(E_MSG_CONNECT, ChInfo[nCh].nSaveSubmiteCh, ChInfo[nCh].nLinkToCh);

					//to link original calling party and extenion transferred (ch0,ch2)
					if(SsmTalkWith(ChInfo[nCh].nSaveSubmiteCh, ChInfo[nCh].nLinkToCh) == -1)
					{
						ShowErrMsg("E_CHG_HookState", "USER_F_TALKING", "SsmTalkWith");
					}

					ChInfo[ChInfo[nCh].nLinkToCh].bPressFlag = FALSE;
				}
				else
				{
					//E_MSG_RELEASE→ch2
					SendMessage(E_MSG_RELEASE, ChInfo[nCh].nLinkToCh, nCh);
				}
				break;
			case USER_F_OPERATE:
				if(!ChInfo[nCh].bSubmiteChHookFlag)
				{
					//E_MSG_RELEASE→ch0
					SendMessage(E_MSG_RELEASE, ChInfo[nCh].nSaveSubmiteCh, nCh);
				}
				break;
			default:
				break;
			}//end of switch for ChInfo[nCh].nStatus

			//clear DTMF buffer 
			if(SsmClearRxDtmfBuf(nCh) == -1)
			{
				ShowErrMsg("E_CHG_HookState", "USER_F_OPERATE", "SsmClearRxDtmfBuf");
			}

			//initialize channel concerned parameters 
			ChInfo[nCh].nStatus = USER_IDLE;
			ChInfo[nCh].bPressFlag = FALSE;
			ChInfo[nCh].bSubmiteChHookFlag = FALSE;
			ChInfo[nCh].nSaveSubmiteCh = -1;
			ChInfo[nCh].nTimer = -1;
			ChInfo[nCh].nLinkToCh = -1;
			memset(ChInfo[nCh].szCallerId, '\0', sizeof(char)*NUM_LENGTH);		//clear CallerId
			memset(ChInfo[nCh].szCalleeId, '\0', sizeof(char)*NUM_LENGTH);		//clear CalledID	
		}
		else if(nHook == 1)	//station goes off-hook
		{
			switch(ChInfo[nCh].nStatus)
			{
			case USER_IDLE:
				memset(ChInfo[nCh].szPhoneNumBuf, '\0', sizeof(char)*NUM_LENGTH);
				ChInfo[nCh].nStatus = USER_GET_1STDTMF;

				//clear DTMF buffer 
				if(SsmClearRxDtmfBuf(nCh) == -1)
				{
					ShowErrMsg("E_CHG_HookState", "USER_IDLE", "SsmClearRxDtmfBuf");
				}

				//start T1: 7 seconds
				if( (ChInfo[nCh].nTimer = SsmStartTimer(7000, 1)) == -1)	
				{
					ShowErrMsg("E_CHG_HookState", "USER_IDLE", "SsmStartTimer");
				}
				break;
			case USER_LOCAL_RING:
				//stop ringing 
				if(SsmStopRing(nCh) == -1)
				{
					ShowErrMsg("E_CHG_HookState", "USER_LOCAL_RING", "SsmStopRing");
				}
				ChInfo[nCh].nStatus = USER_TALKING;
				//send E_US_PICKUP
				SendMessage(E_US_PICKUP, ChInfo[nCh].nLinkToCh, nCh);
				break;
			default:
				break;
			}			
		}
		break;
	case E_CHG_RcvDTMF:		//dtmf event is detected by station channel 
		dwDtmfLen = lParam >> 16;
		dwDtmfNum = lParam & 0xFFFF;
		
		switch(ChInfo[nCh].nStatus)
		{
		case USER_GET_1STDTMF:
			//close T1
			if(SsmStopTimer(ChInfo[nCh].nTimer) == -1)	
			{
				ShowErrMsg("E_CHG_RcvDTMF", "USER_GET_1STDTMF", "SsmStopTimer");
			}
			ChInfo[nCh].nTimer = -1;

			//retrieve first DTMF
			ChInfo[nCh].szPhoneNumBuf[dwDtmfLen-1] = dwDtmfNum;

			switch(dwDtmfNum)
			{
			case '0':
				memset(ChInfo[nCh].szPhoneNumBuf, '\0', sizeof(char)*NUM_LENGTH);
				//search for idle analog trunk channel 
				ChInfo[nCh].nLinkToCh = SsmSearchIdleCallOutCh(1, 0);
				if(ChInfo[nCh].nLinkToCh >= 0)
				{					
					if(SsmClearRxDtmfBuf(nCh) == -1)
					{
						ShowErrMsg("E_CHG_RcvDTMF", "USER_GET_1STDTMF", "SsmClearRxDtmfBuf");
					}
					ChInfo[nCh].nStatus = USER_REQ_TRUNK;
					//send E_US_SEIZURE_TK
					SendMessage(E_US_SEIZURE_TK, ChInfo[nCh].nLinkToCh, nCh);
				}
				else
				{
					//note: if value "-1" is returned by function SsmSearchIdleCallOutCh(), then it is due to failed call of this function or 
					// no idle channel is found 
					if(ChInfo[nCh].nLinkToCh == -1)
					{
						ShowErrMsg("E_CHG_RcvDTMF", "USER_GET_1STDTMF", "SsmSearchIdleCallOutCh");
					}

					if(SsmSendTone(nCh, 1) == -1)
					{
						ShowErrMsg("E_CHG_RcvDTMF", "USER_GET_1STDTMF", "SsmSendTone");
					}
					ChInfo[nCh].nStatus = USER_WAIT_HANGUP;
				}
				break;
			case '2':
				ChInfo[nCh].nStatus = USER_GET_DTMF;
				//start T2:8 seconds
				if( (ChInfo[nCh].nTimer = SsmStartTimer(8000, 1)) == -1)
				{
					ShowErrMsg("E_CHG_RcvDTMF", "USER_GET_1STDTMF", "SsmStartTimer");
				}
				break;
			default:
				//send busy tone to station channel 
				if(SsmSendTone(nCh, 1) == -1)
				{
					ShowErrMsg("E_CHG_RcvDTMF", "USER_GET_1STDTMF", "SsmSendTone");
				}
				ChInfo[nCh].nStatus = USER_WAIT_HANGUP;
				break;
			}
			break;
		case USER_GET_DTMF:
			if(dwDtmfLen == MAX_USER_DTMFLEN)
			{
				ChInfo[nCh].szPhoneNumBuf[dwDtmfLen-1] = dwDtmfNum;
				//close T2
				if(SsmStopTimer(ChInfo[nCh].nTimer) == -1)	
				{
					ShowErrMsg("E_CHG_RcvDTMF", "USER_GET_DTMF", "SsmStopTimer");
				}
			
				ChInfo[nCh].szPhoneNumBuf[MAX_USER_DTMFLEN] = '\0';
				for(int i=0; i<nMaxCh; i++)
				{
					//to identify channel number Ch-k according to extension number 
					if ( (ChInfo[i].nChType == 2)
						&& (strcmp(ChInfo[nCh].szPhoneNumBuf, ChInfo[i].CUserNum) == 0 ) && i != nCh)
					{
						ChInfo[nCh].nLinkToCh = i;
						ChInfo[nCh].nStatus = USER_REQ_USER;
						//send E_US_SEIZURE
						SendMessage(E_US_SEIZURE, ChInfo[nCh].nLinkToCh, nCh);	//send seizure reqest to called party channel	
					}
				}
				
				if(ChInfo[nCh].nLinkToCh == -1)
				{
					//send busy tone to station channel 
					if(SsmSendTone(nCh, 1) == -1)
					{
						ShowErrMsg("E_CHG_RcvDTMF", "USER_GET_DTMF", "SsmSendTone");
					}
					ChInfo[nCh].nStatus = USER_WAIT_HANGUP;
				}
			}//end of first if
			else
			{
				ChInfo[nCh].szPhoneNumBuf[dwDtmfLen-1] = dwDtmfNum;

				//close and restart T2 in order to reset T2 
				if(SsmStopTimer(ChInfo[nCh].nTimer) == -1)	
				{
					ShowErrMsg("E_CHG_RcvDTMF", "USER_GET_DTMF", "SsmStopTimer");
				}
				if( (ChInfo[nCh].nTimer = SsmStartTimer(8000, 1)) == -1)
				{
					ShowErrMsg("E_CHG_RcvDTMF", "USER_GET_DTMF", "SsmStartTimer");
				}
			}
			break;
		case USER_DIALOUT:			
			//close and restart T3 in order to reset T3 
			if(SsmStopTimer(ChInfo[nCh].nTimer) == -1)	
			{
				ShowErrMsg("E_CHG_RcvDTMF", "USER_DIALOUT", "SsmStopTimer");
			}
			if( (ChInfo[nCh].nTimer = SsmStartTimer(18000, 1)) == -1)
			{
				ShowErrMsg("E_CHG_RcvDTMF", "USER_DIALOUT", "SsmStartTimer");
			}
			
			//Send E_US_DTMF2TK
			SendMessage(E_US_DTMF2TK, ChInfo[nCh].nLinkToCh, lParam);		//post dtmf event to trunk channel 
			break;
		case USER_F_GET_DTMF:
			if(dwDtmfLen == MAX_USER_DTMFLEN)
			{
				ChInfo[nCh].szPhoneNumBuf[dwDtmfLen-1] = dwDtmfNum;
				//close T4
				if(SsmStopTimer(ChInfo[nCh].nTimer) == -1)	
				{
					ShowErrMsg("E_CHG_RcvDTMF", "USER_F_GET_DTMF", "SsmStopTimer");
				}

				ChInfo[nCh].szPhoneNumBuf[MAX_USER_DTMFLEN] = '\0';

				for(int i=0; i<nMaxCh; i++)
				{
					//station channel rule judge 
					if( (ChInfo[i].nChType == 2)
						&&(strcmp(ChInfo[nCh].szPhoneNumBuf, ChInfo[i].CUserNum) ==0) && i != nCh )
					{
						ChInfo[nCh].nLinkToCh = i;
						ChInfo[nCh].nStatus = USER_F_REQ_USER;
						//F_US_ SEIZURE→ch2
						SendMessage(F_US_SEIZURE, ChInfo[nCh].nLinkToCh, nCh);	//post seizure event to station channel 
					}
				}
				
				if(ChInfo[nCh].nLinkToCh == -1)
				{
					//send busy tone to station channel 
					if(SsmSendTone(nCh, 1) == -1)
					{
						ShowErrMsg("E_CHG_RcvDTMF", "USER_F_GET_DTMF", "SsmSendTone");
					}

					ChInfo[nCh].nStatus = USER_F_OPERATE;
				}
			}//end of first if
			else
			{
				ChInfo[nCh].szPhoneNumBuf[dwDtmfLen-1] = dwDtmfNum;
				//close and restart T4 in order to reset T4
				if(SsmStopTimer(ChInfo[nCh].nTimer) == -1)	
				{
					ShowErrMsg("E_CHG_RcvDTMF", "USER_F_GET_DTMF", "SsmStopTimer");
				}
				if( (ChInfo[nCh].nTimer = SsmStartTimer(8000, 1)) == -1)
				{
					ShowErrMsg("E_CHG_RcvDTMF", "USER_F_GET_DTMF", "SsmStartTimer");
				}
			}
			break;
		case USER_REQ_USER:
			break;
		case USER_RING_BACK:
			break;
		case USER_TALKING:
			break;
		case USER_WAIT_HANGUP:
			break;
		case USER_LOCAL_RING:
			break;
		case USER_REQ_TRUNK:
			break;
		case USER_WAIT_REMOTE_PICKUP:
			break;
		case USER_F_REQ_USER:
			break;
		case USER_F_RING_BACK:
			break;
		case USER_F_TALKING:
			break;
		case USER_F_OPERATE:
			break;
		default:
			break;
		}
		break;//end of switch for E_CHG_RcvDTMF
	case E_CHG_FlashCount:

		switch(ChInfo[nCh].nStatus)
		{
		case USER_TALKING:
			if(!ChInfo[nCh].bPressFlag)	//flash Flag==0?
			{
				//tear down bus connection between ch0 and ch1
				if(SsmStopTalkWith(nCh, ChInfo[nCh].nLinkToCh) == -1)
				{
					ShowErrMsg("E_CHG_FlashCount", "USER_TALKING", "SsmStopTalkWith");
				}
				//E_MSG _FLASH→ch0
				SendMessage(E_MSG_FLASH, ChInfo[nCh].nLinkToCh, nCh);
				//falsh Flag=1
				ChInfo[nCh].bPressFlag = TRUE;
				//clear DTMF buffer 
				if(SsmClearRxDtmfBuf(nCh) == -1)
				{
					ShowErrMsg("E_CHG_FlashCount", "USER_TALKING", "SsmClearRxDtmfBuf");
				}
				//send dial tone
				if(SsmSendTone(nCh, 0) == -1)
				{
					ShowErrMsg("E_CHG_FlashCount", "USER_TALKING", "SsmSendTone");
				}

				ChInfo[nCh].nSaveSubmiteCh = ChInfo[nCh].nLinkToCh;			
				ChInfo[nCh].nStatus =USER_F_GET_DTMF;
				ChInfo[nCh].nLinkToCh = -1;

				//start T4:8 seconds
				if( (ChInfo[nCh].nTimer = SsmStartTimer(8000, 1)) == -1)
				{
					ShowErrMsg("E_CHG_FlashCount", "USER_TALKING", "SsmStartTimer");
				}
			}
			break;
		case USER_F_GET_DTMF:			
			//close T4
			if(SsmStopTimer(ChInfo[nCh].nTimer) == -1)	
			{
				ShowErrMsg("E_CHG_FlashCount", "USER_F_GET_DTMF", "SsmStopTimer");
			}
			//stop dial tone
			nToneType = -2;
			nToneChResult = SsmChkSendTone(nCh,&nToneType);
			if(nToneChResult == -1)
			{
				ShowErrMsg("E_CHG_FlashCount", "USER_F_GET_DTMF", "SsmChkSendTone");
			}
			else
			{
				if(nToneChResult == 1)
				{
					if(SsmStopSendTone(nCh) == -1)
					{
						ShowErrMsg("E_CHG_FlashCount", "USER_F_GET_DTMF", "SsmStopSendTone");
					}
				}
			}
			
			// on-hook Flag==0? on Ch0
			if(ChInfo[nCh].bSubmiteChHookFlag)
			{
				if(SsmSendTone(nCh, 3) == -1)
				{
					ShowErrMsg("E_CHG_FlashCount", "USER_F_GET_DTMF", "SsmSendTone");
				}
				ChInfo[nCh].nStatus = USER_WAIT_HANGUP;
			}
			else								
			{
				ChInfo[nCh].nStatus = USER_TALKING;	
				ChInfo[nCh].nLinkToCh = ChInfo[nCh].nSaveSubmiteCh;
				//E_MSG_CONNECT→ch0
				SendMessage(E_MSG_CONNECT, ChInfo[nCh].nLinkToCh, nCh);	
				//flash Flag=0
				ChInfo[nCh].bPressFlag = FALSE;
				ChInfo[nCh].nSaveSubmiteCh = -1;
				
				//build bus connection 
				if(SsmTalkWith(nCh, ChInfo[nCh].nLinkToCh) == -1)
				{
					ShowErrMsg("E_CHG_FlashCount", "USER_F_GET_DTMF", "SsmTalkWith");
				}
				//clear DTMF buffer
				if(SsmClearRxDtmfBuf(nCh) == -1)
				{
					ShowErrMsg("E_CHG_FlashCount", "USER_F_GET_DTMF", "SsmClearRxDtmfBuf");
				}
			}
			break;
		case USER_F_REQ_USER:
			//on-hook Flag==0?
			if(ChInfo[nCh].bSubmiteChHookFlag)
			{
				if(SsmSendTone(nCh, 3) == -1)
				{
					ShowErrMsg("E_CHG_FlashCount", "USER_F_REQ_USER", "SsmSendTone");
				}
				ChInfo[nCh].nStatus = USER_WAIT_HANGUP;
			}
			else								
			{
				ChInfo[nCh].nLinkToCh = ChInfo[nCh].nSaveSubmiteCh;
				ChInfo[nCh].nStatus = USER_TALKING;
				//E_MSG_CONNECT→ch0
				SendMessage(E_MSG_CONNECT, ChInfo[nCh].nLinkToCh, nCh);
				//flash Flag=0
				ChInfo[nCh].bPressFlag = FALSE;
				ChInfo[nCh].nSaveSubmiteCh = -1;
				
				//build bus connectin between ch0 and ch1
				if(SsmTalkWith(nCh, ChInfo[nCh].nLinkToCh) == -1)
				{
					ShowErrMsg("E_CHG_FlashCount", "USER_F_REQ_USER", "SsmTalkWith");
				}
				//clear DTMF buffer 
				if(SsmClearRxDtmfBuf(nCh) == -1)
				{
					ShowErrMsg("E_CHG_FlashCount", "USER_F_REQ_USER", "SsmClearRxDtmfBuf");
				}
			}
			break;
		case USER_F_OPERATE:
			if(SsmStopSendTone(nCh) == -1)
			{
				ShowErrMsg("E_CHG_FlashCount", "USER_F_OPERATE", "SsmStopSendTone");
			}
			//on-hook Flag==0? on Ch0
			if(ChInfo[nCh].bSubmiteChHookFlag)
			{
				//play howler tone 
				if(SsmSendTone(nCh, 3) == -1)
				{
					ShowErrMsg("E_CHG_FlashCount", "USER_F_OPERATE", "SsmSendTone");
				}

				ChInfo[nCh].nStatus = USER_WAIT_HANGUP;
			}
			else
			{
				ChInfo[nCh].nLinkToCh = ChInfo[nCh].nSaveSubmiteCh;
				//E_MSG_CONNECT→ch0
				SendMessage(E_MSG_CONNECT, ChInfo[nCh].nLinkToCh, nCh);
				
				//build bus connection between ch0 and ch1
				if(SsmTalkWith(nCh, ChInfo[nCh].nLinkToCh) == -1)
				{
					ShowErrMsg("E_CHG_FlashCount", "USER_F_OPERATE", "SsmTalkWith");
				}
				//clear DTMF
				if(SsmClearRxDtmfBuf(nCh) == -1)
				{
					ShowErrMsg("E_CHG_FlashCount", "USER_F_OPERATE", "SsmClearRxDtmfBuf");
				}
				
				ChInfo[nCh].nStatus = USER_TALKING;
				ChInfo[nCh].nSaveSubmiteCh = -1;
				ChInfo[nCh].bPressFlag = FALSE;
			}
			break;
		case USER_GET_1STDTMF:
			break;
		case USER_GET_DTMF:
			break;
		case USER_REQ_USER:
			break;
		case USER_RING_BACK:
			break;
		case USER_WAIT_HANGUP:
			break;
		case USER_REQ_TRUNK:
			break;
		case USER_DIALOUT:
			break;
		case USER_WAIT_REMOTE_PICKUP:
			break;
		case USER_F_RING_BACK:
			break;
		case USER_F_TALKING:
			break;
		default:
			break;
		}
		break;
	case E_SYS_TIMEOUT:		//timer Timeout event 

		switch(ChInfo[nCh].nStatus)
		{
		case USER_GET_1STDTMF:
			//close T1
			if(SsmStopTimer(ChInfo[nCh].nTimer) == -1)	
			{
				ShowErrMsg("E_SYS_TIMEOUT", "USER_F_GET_DTMF", "SsmStopTimer");
			}
			
			nToneType = 0;
			nToneChResult = SsmChkSendTone(nCh,&nToneType);
			if(nToneChResult != -1)
			{
				if(nToneChResult == 1)
				{
					if(SsmStopSendTone(nCh) == -1)
					{
						ShowErrMsg("E_SYS_TIMEOUT", "USER_GET_1STDTMF", "SsmStopSendTone");
					}
				}
			}
			else
			{
				ShowErrMsg("E_SYS_TIMEOUT", "USER_GET_1STDTMF", "SsmChkSendTone");
			}
			
			//play busy tone
			if(SsmSendTone(nCh, 1) == -1)
			{
				ShowErrMsg("E_SYS_TIMEOUT", "USER_F_GET_DTMF", "SsmSendTone");
			}
			
			ChInfo[nCh].nStatus = USER_WAIT_HANGUP;
			break;
		case USER_DIALOUT:
			//detect whether it is dialing or not
			nToneType = 0;
			nToneChResult = SsmChkSendTone(nCh,&nToneType);
			if(nToneChResult != -1)
			{
				if(nToneChResult == 1)
				{
					if(SsmStopSendTone(nCh) == -1)
					{
						ShowErrMsg("E_SYS_TIMEOUT", "USER_DIALOUT", "SsmStopSendTone");
					}
				}
			}
			else
			{
				ShowErrMsg("E_SYS_TIMEOUT", "USER_DIALOUT", "SsmChkSendTone");
			}
			
			//send E_TK_RELEASE
			ChInfo[nCh].nStatus = USER_WAIT_HANGUP;
			SendMessage(E_TK_RELEASE, ChInfo[nCh].nLinkToCh, nCh);

			//close TX
			if(SsmStopTimer(ChInfo[nCh].nTimer) == -1)	
			{
				ShowErrMsg("E_SYS_TIMEOUT", "USER_DIALOUT", "SsmStopTimer");
			}
			//play busy tone
			if(SsmSendTone(nCh, 1) == -1)
			{
				ShowErrMsg("E_SYS_TIMEOUT", "USER_DIALOUT", "SsmSendTone");
			}

			break;
		case USER_F_GET_DTMF:
			//close T4
			if(SsmStopTimer(ChInfo[nCh].nTimer) == -1)	
			{
				ShowErrMsg("E_SYS_TIMEOUT", "USER_F_GET_DTMF", "SsmStopTimer");
			}
			
			nToneType = 0;
			nToneChResult = SsmChkSendTone(nCh,&nToneType);
			if(nToneChResult != -1)
			{
				if(nToneChResult == 1)
				{
					if(SsmStopSendTone(nCh) == -1)
					{
						ShowErrMsg("E_SYS_TIMEOUT", "USER_F_GET_DTMF", "SsmStopSendTone");
					}
				}
			}
			else
			{
				ShowErrMsg("E_SYS_TIMEOUT", "USER_F_GET_DTMF", "SsmChkSendTone");
			}
			
			//play busy tone
			if(SsmSendTone(nCh, 1) == -1)
			{
				ShowErrMsg("E_SYS_TIMEOUT", "USER_F_GET_DTMF", "SsmSendTone");
			}

			ChInfo[nCh].nStatus = USER_F_OPERATE;
			break;
		default:
			//close TX
			if(SsmStopTimer(ChInfo[nCh].nTimer) == -1)	
			{
				ShowErrMsg("E_SYS_TIMEOUT", "default", "SsmStopTimer");
			}

			//play busy tone
			if(SsmSendTone(nCh, 1) == -1)
			{
				ShowErrMsg("E_SYS_TIMEOUT", "default", "SsmSendTone");
			}
			ChInfo[nCh].nStatus = USER_WAIT_HANGUP;
			break;
		}
		break;
			/*+++++++++define station channel message +++++++++*/
	case E_US_SEIZURE:
		if(USER_IDLE == ChInfo[nCh].nStatus)
		{	
			ChInfo[nCh].nStatus = USER_LOCAL_RING;
			//send E_US_SEIZURE_ACK_IDLE
			SendMessage(E_US_SEIZURE_ACK_IDLE, lParam, nCh);
			//send ringing tone
			if(SsmStartRing(nCh) == -1)
			{
				ShowErrMsg("E_US_SEIZURE", "USER_IDLE", "SsmStartRing");
			}

			ChInfo[nCh].nLinkToCh = lParam;

			//retrieve CallerId
			if(ChInfo[ChInfo[nCh].nLinkToCh].nChType == 0)
			{
				if(SsmGetCallerId(ChInfo[nCh].nLinkToCh, ChInfo[nCh].szCallerId) == -1)
				{
					ShowErrMsg("E_US_SEIZURE", "USER_IDLE", "SsmGetCallerId");
				}
			}
			else
			{
				strcpy(ChInfo[nCh].szCallerId, ChInfo[ChInfo[nCh].nLinkToCh].CUserNum);
			}
		}
		else
		{
			//send E_US_SEIZURE_ACK_BUSY			
			SendMessage(E_US_SEIZURE_ACK_BUSY, lParam, nCh);
		}
		break;
	case E_US_SEIZURE_ACK_IDLE:			//it is detected that station channel is seizured successfully
		
		switch(ChInfo[nCh].nStatus)
		{
		case USER_REQ_USER:
			//play ringback tone
			if(SsmSendTone(nCh, 2) == -1)
			{
				ShowErrMsg("E_US_SEIZURE_ACK_IDLE", "USER_REQ_USER", "SsmSendTone");
			}
			
			//retrieve CalledId
			strcpy(ChInfo[nCh].szCalleeId, ChInfo[nCh].szPhoneNumBuf);

			ChInfo[nCh].nLinkToCh = lParam;
			ChInfo[nCh].nStatus = USER_RING_BACK;			
			break;
		case USER_F_REQ_USER:			// extension in call transfer is seized successfully  
			//play ringback tone
			if(SsmSendTone(nCh, 2) == -1)
			{
				ShowErrMsg("E_US_SEIZURE_ACK_IDLE", "USER_F_REQ_USER", "SsmSendTone");
			}

			//retrieve CalledId
			strcpy(ChInfo[nCh].szCalleeId, ChInfo[nCh].szPhoneNumBuf);

			ChInfo[nCh].nLinkToCh = lParam;
			ChInfo[nCh].nStatus = USER_F_RING_BACK;
			break;
		default:
			break;
		}
		break;
	case E_US_SEIZURE_ACK_BUSY:			//failed to seize designatedstation channel  
		
		switch(ChInfo[nCh].nStatus)
		{
		case USER_REQ_USER:
			//play busy tone
			if(SsmSendTone(nCh, 1) == -1)
			{
				ShowErrMsg("E_US_SEIZURE_ACK_IDLE", "USER_REQ_USER", "SsmSendTone");
			}

			ChInfo[nCh].nStatus = USER_WAIT_HANGUP;
			break;
		case USER_F_REQ_USER:
			//play busy tone
			if(SsmSendTone(nCh, 1) == -1)
			{
				ShowErrMsg("E_US_SEIZURE_ACK_IDLE", "USER_F_REQ_USER", "SsmSendTone");
			}
			
			ChInfo[nCh].nStatus = USER_F_OPERATE;
			break;
		default:
			break;
		}
		break;
	case E_US_PICKUP:
		//Called party go off-hook
		switch(ChInfo[nCh].nStatus)
		{
		case USER_RING_BACK:
			//stop sending of rinback tone
			if(SsmStopSendTone(nCh) == -1)
			{
				ShowErrMsg("E_US_PICKUP", "USER_RING_BACK", "SsmStopSendTone");
			}
			//build bus connection 
			if(SsmTalkWith(nCh, ChInfo[nCh].nLinkToCh) == -1)
			{
				ShowErrMsg("E_US_PICKUP", "USER_RING_BACK", "SsmTalkWith");
			}

			ChInfo[nCh].nStatus = USER_TALKING;
			break;
		case USER_F_RING_BACK:
			//stop sending of ringback tone
			if(SsmStopSendTone(nCh) == -1)
			{
				ShowErrMsg("E_US_PICKUP", "USER_F_RING_BACK", "SsmStopSendTone");
			}
			//build bus connection between ch1 and ch2
			if(SsmTalkWith(nCh, ChInfo[nCh].nLinkToCh) == -1)
			{
				ShowErrMsg("E_US_PICKUP", "USER_F_RING_BACK", "SsmTalkWith");
			}

			ChInfo[nCh].nStatus = USER_F_TALKING;
			break;
		}
		break;
	case E_US_RELEASE:
		//stop ringing 
		if(SsmStopRing(nCh) == -1)
		{
			ShowErrMsg("E_US_RELEASE", NULL, "SsmStopRing");
		}

		ChInfo[nCh].nLinkToCh = -1;
		ChInfo[nCh].bPressFlag = FALSE;
		ChInfo[nCh].nStatus = USER_IDLE;
		memset(ChInfo[nCh].szCallerId, '\0', sizeof(char)*NUM_LENGTH);		//clear CalledId
		break;
	case F_US_SEIZURE:
		if(USER_IDLE == ChInfo[nCh].nStatus)
		{			
			//send ringing 
			if(SsmStartRing(nCh) == -1)
			{
				ShowErrMsg("F_US_SEIZURE", "USER_IDLE", "SsmStartRing");
			}

			ChInfo[nCh].nStatus = USER_LOCAL_RING;
			ChInfo[nCh].nLinkToCh = lParam;
			ChInfo[nCh].bPressFlag = TRUE;
			strcpy(ChInfo[nCh].szCallerId, ChInfo[ChInfo[nCh].nLinkToCh].CUserNum);
			//send E_US_SEIZURE_ACK_IDLE
			SendMessage(E_US_SEIZURE_ACK_IDLE, lParam, nCh);
		}
		else
		{
			//send E_US_SEIZURE_ACK_BUSY
			SendMessage(E_US_SEIZURE_ACK_BUSY, lParam, nCh);
		}
		break;
	/*+++++++++define analog trunk channel message +++++++++*/
	case E_TK_SEIZURE_TK_ACK_IDLE:			//trunk channel is seized successfully
		//send dial tone
		if(SsmSendTone(nCh, 0) == -1)
		{
			ShowErrMsg("E_TK_SEIZURE_TK_ACK_IDLE", NULL, "SsmSendTone");
		}
		//start T3:18 seconds
		if( (ChInfo[nCh].nTimer = SsmStartTimer(18000, 1)) == -1)
		{
			ShowErrMsg("E_TK_SEIZURE_TK_ACK_IDLE", NULL, "SsmStartTimer");
		}

		ChInfo[nCh].nLinkToCh =lParam;
		ChInfo[nCh].nStatus = USER_DIALOUT;
		break;
	case E_TK_SEIZURE_TK_ACK_BUSY:			//failed to seize designated trunk channel
		//play busy tone
		if(SsmSendTone(nCh, 1) == -1)
		{
			ShowErrMsg("E_TK_SEIZURE_TK_ACK_BUSY", NULL, "SsmSendTone");
		}

		ChInfo[nCh].nStatus = USER_WAIT_HANGUP;
		break;
	case E_TK_DIAL_OK:
		//close T3
		if(SsmStopTimer(ChInfo[nCh].nTimer) == -1)
		{
			ShowErrMsg("E_TK_DIAL_OK", NULL, "SsmStopTimer");
		}
		//play ringback tone
		if(SsmSendTone(nCh, 2) == -1)
		{
			ShowErrMsg("E_TK_DIAL_OK", NULL, "SsmSendTone");
		}
		
		//retrieve CalledId
		if (SsmGetDtmfStr(nCh,ChInfo[nCh].szCalleeId) == -1)
		{
			ShowErrMsg("E_TK_DIAL_OK", NULL, "SsmGetDtmfStr");
		}

		ChInfo[nCh].nStatus = USER_WAIT_REMOTE_PICKUP;
		break;
	case E_TK_DIAL_FAIL:
		//detect whether dial tone is present
		nToneType = 0;
		nToneChResult = SsmChkSendTone(nCh,&nToneType);
		if(nToneChResult != -1)
		{
			if(nToneChResult == 1)
			{
				if(SsmStopSendTone(nCh) == -1)
				{
					ShowErrMsg("E_TK_DIAL_FAIL", NULL, "SsmStopSendTone");
				}
			}
		}
		else
		{
			ShowErrMsg("E_TK_DIAL_FAIL", NULL, "SsmChkSendTone");
		}
		//close T3
		if(SsmStopTimer(ChInfo[nCh].nTimer) == -1)
		{
			ShowErrMsg("E_TK_DIAL_FAIL", NULL, "SsmStopTimer");
		}
		//play busy tone
		if(SsmSendTone(nCh, 1) == -1)
		{
			ShowErrMsg("E_TK_DIAL_FAIL", NULL, "SsmSendTone");
		}
		ChInfo[nCh].nStatus = USER_WAIT_HANGUP;
		break;
	case E_TK_REMOTE_NOANSWER:		//trunk channel does not answer
		//stop sending of ringback tone
		if(SsmStopSendTone(nCh) == -1)
		{
			ShowErrMsg("E_TK_REMOTE_NOANSWER", NULL, "SsmStopSendTone");
		}

		//play busy tone
		if(SsmSendTone(nCh, 1) == -1)
		{
			ShowErrMsg("E_TK_REMOTE_NOANSWER", NULL, "SsmSendTone");
		}
		
		ChInfo[nCh].nStatus = USER_WAIT_HANGUP;
		break;
	case E_TK_REMOTE_PICKUP:	//remote end go off-hook
		switch(ChInfo[nCh].nStatus)
		{
		case USER_DIALOUT:
			//close T3
			if(SsmStopTimer(ChInfo[nCh].nTimer) == -1)
			{
				ShowErrMsg("E_TK_REMOTE_PICKUP", "USER_DIALOUT", "SsmStopTimer");
			}
			//build bus connection between station and trunk channel 
			if(SsmTalkWith(nCh, ChInfo[nCh].nLinkToCh) == -1)
			{
				ShowErrMsg("E_TK_REMOTE_PICKUP", "USER_DIALOUT", "SsmTalkWith");
			}
			ChInfo[nCh].nStatus = USER_TALKING;
			break;
		case USER_WAIT_REMOTE_PICKUP:
			//stop sending of ringback tone
			if(SsmStopSendTone(nCh) == -1)
			{
				ShowErrMsg("E_TK_REMOTE_NOANSWER", NULL, "SsmStopSendTone");
			}
			//build bus connection 
			if(SsmTalkWith(nCh, ChInfo[nCh].nLinkToCh) == -1)
			{
				ShowErrMsg("E_TK_REMOTE_PICKUP", "USER_WAIT_REMOTE_PICKUP", "SsmTalkWith");
			}

			ChInfo[nCh].nStatus = USER_TALKING;
			break;
		default:
			break;
		}
		
		//retrieve CalledId
		if (SsmGetDtmfStr(nCh,ChInfo[nCh].szCalleeId) == -1)
		{
			ShowErrMsg("E_TK_DIAL_OK", NULL, "SsmGetDtmfStr");
		}
		break;
	/*+++++++++define public message +++++++++*/
	case E_MSG_RELEASE:
		switch(ChInfo[nCh].nStatus)
		{
		case USER_TALKING:
			//play howler tone
			if(SsmSendTone(nCh, 3) == -1)
			{
				ShowErrMsg("E_MSG_RELEASE", "USER_TALKING", "SsmSendTone");
			}

			ChInfo[nCh].nStatus = USER_WAIT_HANGUP;
			break;
		case USER_F_WAIT_TALK:
			//stop playback of background music 
			nPlayResult = SsmCheckPlay(nCh);
			if(nPlayResult != -1)
			{
				if(nPlayResult == 0)
				{
					if(SsmStopPlayFile(nCh) == -1)
					{
						ShowErrMsg("E_MSG_RELEASE", "USER_F_TALKING", "SsmStopPlayFile");
					}
				}
			}
			else
			{
				ShowErrMsg("E_MSG_RELEASE", "USER_F_TALKING", "SsmCheckPlay");
			}
			
			//call transfer failed and send howler tone to original calling party 
			if(SsmSendTone(nCh, 3) == -1)
			{
				ShowErrMsg("E_MSG_RELEASE", "USER_F_TALKING", "SsmSendTone");
			}
			
			ChInfo[nCh].nStatus = USER_WAIT_HANGUP;
			break;
		case USER_F_TALKING:
			//play howler tone
			if(SsmSendTone(nCh, 3) == -1)
			{
				ShowErrMsg("E_MSG_RELEASE", "USER_F_TALKING", "SsmSendTone");
			}
			
			ChInfo[nCh].nLinkToCh = -1;
			ChInfo[nCh].nStatus = USER_F_OPERATE;
			break;
		default:
			break;
		}
		break;
	case E_MSG_FLASH:
		GetCurrentDirectory(MAX_PATH, szVoicePath);
		strcat(szVoicePath, "\\bgmusic.wav");

		//play background music 
		if(SsmPlayFile(nCh, szVoicePath, -1, 0, 0xffffffff) == -1)
		{
			ShowErrMsg("E_MSG_FLASH", NULL, "SsmPlayFile");
		}

		ChInfo[nCh].nStatus = USER_F_WAIT_TALK;
		break;
	case E_MSG_CONNECT:
		ChInfo[nCh].nLinkToCh = lParam;
		//stop playback of background music 
		nPlayResult = SsmCheckPlay(nCh);
		if(nPlayResult != -1)
		{
			if(nPlayResult == 0)
			{
				if(SsmStopPlayFile(nCh) == -1)
				{
					ShowErrMsg("E_MSG_CONNECT", NULL, "SsmStopPlayFile");
				}
			}
		}
		else
		{
			ShowErrMsg("E_MSG_CONNECT", NULL, "SsmCheckPlay");
		}

		ChInfo[nCh].nStatus = USER_TALKING;
		break;
	case E_MSG_HANGUP:
		ChInfo[nCh].bSubmiteChHookFlag = TRUE;			//origial calling party go on-hook 
		break;
	default:
		break;
	}
}
LVS_VOID TrunkProc(LVS_INT32 event, LVS_INT32 wParam, LVS_INT32 lParam)
{
    int nCh;                        //trunk channel number 
    DWORD dwDtmfLen;                // lenght of DTMF received
    UCHAR dwDtmfNum;                // DTMF received
    char szVoicePath[MAX_PATH];     //sound file path
    DWORD nChState;                 //current statt of trunk channel 
    int nPlayResult;                //return value of function SsmCheckPlay()

    nCh = wParam;

    switch(event)
    {
    /*+++++++++driver message +++++++++*/
    case E_CHG_ChState:
        nChState = lParam & 0xffff;
        switch(ChInfo[nCh].nStatus)
        {
        case TRUNK_IDLE:
            if(nChState == S_CALL_RINGING)
            {
                //go off-hook
                if(SsmPickup(nCh) == -1)
                {
                    ShowErrMsg("E_CHG_ChState", "TRUNK_IDLE", "SsmPickup");
                }
                //retrieve CallerId 
                if(SsmGetCallerId(nCh, ChInfo[nCh].szCallerId) == -1)
                {
                    ShowErrMsg("E_CHG_ChState", "TRUNK_IDLE", "SsmGetDtmfStr");         
                }
                ChInfo[nCh].nStatus = TRUNK_WAIT_ACTUAL_PICKUP;
                ChInfo[nCh].nLinkToCh = -1;     //added by lgr for SC-243 2007.11.14
            }
            break;
        case TRUNK_WAIT_ACTUAL_PICKUP:
            if(nChState == S_CALL_TALKING)              //play welcome
            {       
                GetCurrentDirectory(MAX_PATH, szVoicePath);
                strcat(szVoicePath, "\\Select.pcm");

                //play welcome
                if(SsmPlayFile(nCh, szVoicePath, -1, 0, 0xffffffff) == -1)
                {
                    ShowErrMsg("E_CHG_ChState", "TRUNK_WAIT_ACTUAL_PICKUP", "SsmPlayFile");
                }
                //set DTMF-STOP-PLAY switch 
                if(SsmSetDtmfStopPlay(nCh, 1) == -1)
                {
                    ShowErrMsg("E_CHG_ChState", "TRUNK_WAIT_ACTUAL_PICKUP", "SsmSetDtmfStopPlay");
                }

                ChInfo[nCh].nTimer = SsmStartTimer(15000,1);
                ChInfo[nCh].nStatus = TRUNK_WAIT_SELECTION;
            }
            else
            {   
                //clear DTMF
                if(SsmClearRxDtmfBuf(nCh) == -1)
                {
                    ShowErrMsg("E_CHG_ChState", "TRUNK_WAIT_ACTUAL_PICKUP", "SsmClearRxDtmfBuf");
                }
                //go on-hook 
                if(SsmHangup(nCh) == -1)
                {
                    ShowErrMsg("E_CHG_ChState", "TRUNK_WAIT_ACTUAL_PICKUP", "SsmHangup");
                }
                memset(ChInfo[nCh].szCallerId,'\0',sizeof(char)*NUM_LENGTH);        //clear CallerId
                memset(ChInfo[nCh].szCalleeId,'\0',sizeof(char)*NUM_LENGTH);        //clear CalledId            
                ChInfo[nCh].nStatus = TRUNK_IDLE;
            }
            break;
        case TRUNK_DIALING:
            
            switch(nChState)
            {
            case S_CALL_WAIT_REMOTE_PICKUP:
                //retrieve CalledId
                strcpy(ChInfo[nCh].szCalleeId, ChInfo[nCh].szPhoneNumBuf);

                ChInfo[nCh].nStatus = TRUNK_WAIT_REMOTE_PICKUP;
                //send E_TK_DIAL_OK
                SendMessage(E_TK_DIAL_OK, ChInfo[nCh].nLinkToCh, nCh);
                break;
            case S_CALL_TALKING:
                //retrieve calledId
                strcpy(ChInfo[nCh].szCalleeId, ChInfo[nCh].szPhoneNumBuf);
                ChInfo[nCh].nStatus = TRUNK_CONNECTED;
                //send E_TK_REMOTE_PICKUP
                SendMessage(E_TK_REMOTE_PICKUP, ChInfo[nCh].nLinkToCh, nCh);
                break;
            case S_CALL_PENDING:            
                //send E_TK_DIAL_FAIL
                SendMessage(E_TK_DIAL_FAIL, ChInfo[nCh].nLinkToCh, nCh);
                //go on-hook
                if(SsmHangup(nCh) == -1)
                {
                    ShowErrMsg("E_CHG_ChState", "TRUNK_DIALING", "SsmHangup");
                }
                //clear DTMF buffer
                if(SsmClearRxDtmfBuf(nCh) == -1)
                {
                    ShowErrMsg("E_CHG_ChState", "TRUNK_DIALING", "SsmClearRxDtmfBuf");
                }
                memset(ChInfo[nCh].szCallerId, '\0', sizeof(char)*NUM_LENGTH);      //clear CallerId
                memset(ChInfo[nCh].szCalleeId, '\0', sizeof(char)*NUM_LENGTH);      //Clear CalledId
            
                ChInfo[nCh].nStatus = TRUNK_IDLE;
                break;
            default:
                break;
            }
            break;
        case TRUNK_WAIT_REMOTE_PICKUP:
            if(nChState == S_CALL_TALKING)          //called trunk channel answer the call
            {   
                ChInfo[nCh].nStatus = TRUNK_CONNECTED;
                //send E_TK_REMOTE_PICKUP
                SendMessage(E_TK_REMOTE_PICKUP, ChInfo[nCh].nLinkToCh, nCh);
            }
            else                                    //called trunk channel does not answer the call
            {               
                //clear DTMF buffer
                if(SsmClearRxDtmfBuf(nCh) == -1)
                {
                    ShowErrMsg("E_CHG_ChState", "TRUNK_WAIT_REMOTE_PICKUP", "SsmClearRxDtmfBuf");
                }
                //go on-hook
                if(SsmHangup(nCh) == -1)
                {
                    ShowErrMsg("E_CHG_ChState", "TRUNK_WAIT_REMOTE_PICKUP", "SsmHangup");
                }
                //send E_TK_REMOTE_NOANSWER
                SendMessage(E_TK_REMOTE_NOANSWER, ChInfo[nCh].nLinkToCh, nCh);  
                memset(ChInfo[nCh].szCalleeId, '\0', sizeof(char)*NUM_LENGTH);      //callerId
                memset(ChInfo[nCh].szCallerId, '\0', sizeof(char)*NUM_LENGTH);      //CalledId
                ChInfo[nCh].nStatus = TRUNK_IDLE;
            }
            break;
        case TRUNK_REQ_USER:
            if(nChState == S_CALL_PENDING)
            {
                //clear DTmf buffer
                if(SsmClearRxDtmfBuf(nCh) == -1)
                {
                    ShowErrMsg("E_CHG_ChState", "TRUNK_REQ_USER", "SsmClearRxDtmfBuf");
                }
                //go on-hook
                if(SsmHangup(nCh) == -1)
                {
                    ShowErrMsg("E_CHG_ChState", "TRUNK_REQ_USER", "SsmHangup");
                }
                
                memset(ChInfo[nCh].szCallerId, '\0', sizeof(char)*NUM_LENGTH);      //clear CallerId
                memset(ChInfo[nCh].szCalleeId, '\0', sizeof(char)*NUM_LENGTH);      //clear CalledId
                
                ChInfo[nCh].nStatus = TRUNK_IDLE;
            }
            break;
        case TRUNK_RING_BACK:
            if(nChState == S_CALL_PENDING)
            {
                //stop background music 
                nPlayResult = SsmCheckPlay(nCh);
                if(nPlayResult != -1)
                {
                    if(nPlayResult == 0)
                    {
                        if(SsmStopPlayFile(nCh) == -1)
                        {
                            ShowErrMsg("E_CHG_ChState", "TRUNK_RING_BACK", "SsmStopPlayFile");
                        }
                    }
                }
                else
                {
                    ShowErrMsg("E_CHG_ChState", "TRUNK_RING_BACK", "SsmCheckPlay");
                }

                //clear DTMF buffer 
                if(SsmClearRxDtmfBuf(nCh) == -1)
                {
                    ShowErrMsg("E_CHG_ChState", "TRUNK_RING_BACK", "SsmClearRxDtmfBuf");
                }
                //go on-hook
                if(SsmHangup(nCh) == -1)
                {
                    ShowErrMsg("E_CHG_ChState", "TRUNK_RING_BACK", "SsmHangup");
                }

                //send E_US_RELEASE
                SendMessage(E_US_RELEASE, ChInfo[nCh].nLinkToCh, nCh);

                memset(ChInfo[nCh].szCallerId, '\0', sizeof(char)*NUM_LENGTH);      //clear CallerId
                memset(ChInfo[nCh].szCalleeId, '\0', sizeof(char)*NUM_LENGTH);      //clear CalledId            
                ChInfo[nCh].nStatus = TRUNK_IDLE;               
            }
            break;
        case TRUNK_CONNECTED:
            if(nChState ==S_CALL_PENDING)
            {
                //send E_MSG_RELEASE to channel connected
                SendMessage(E_MSG_RELEASE, ChInfo[nCh].nLinkToCh, nCh);
                //tear down bus connection 
                if(SsmStopTalkWith(nCh, ChInfo[nCh].nLinkToCh) == -1)
                {
                    ShowErrMsg("E_CHG_ChState", "TRUNK_CONNECTED", "SsmStopTalkWith");
                }
                //clear DTMF buffer
                if(SsmClearRxDtmfBuf(nCh) == -1)
                {
                    ShowErrMsg("E_CHG_ChState", "TRUNK_CONNECTED", "SsmClearRxDtmfBuf");
                }
                //go on-hook
                if(SsmHangup(nCh) == -1)
                {
                    ShowErrMsg("E_CHG_ChState", "TRUNK_CONNECTED", "SsmHangup");
                }

                memset(ChInfo[nCh].szCallerId, '\0', sizeof(char)*NUM_LENGTH);      //clear CallerId
                memset(ChInfo[nCh].szCalleeId, '\0', sizeof(char)*NUM_LENGTH);      //clear CalledId

                ChInfo[nCh].nStatus = TRUNK_IDLE;               
            }
            break;
        case TRUNK_WAIT_SELECTION:
            if(nChState ==S_CALL_PENDING)
            {
                //close T1:8 seconds
                if(SsmStopTimer(ChInfo[nCh].nTimer) == -1)
                {
                    ShowErrMsg("E_CHG_ChState", "TRUNK_WAIT_SELECTION", "SsmStopTimer");
                }
                //clear DTMF buffer
                if(SsmClearRxDtmfBuf(nCh) == -1)
                {
                    ShowErrMsg("E_CHG_ChState", "TRUNK_WAIT_SELECTION", "SsmClearRxDtmfBuf");
                }
                //go on-hook 
                if(SsmHangup(nCh) == -1)
                {
                    ShowErrMsg("E_CHG_ChState", "TRUNK_WAIT_SELECTION", "SsmHangup");
                }

                memset(ChInfo[nCh].szCallerId, '\0', sizeof(char)*NUM_LENGTH);      //clear CallerId            
                memset(ChInfo[nCh].szCalleeId, '\0', sizeof(char)*NUM_LENGTH);      //clear CalledId            

                ChInfo[nCh].nStatus = TRUNK_IDLE;
            }
            break;
        case TRUNK_FLASHING:
            if(nChState ==S_CALL_PENDING)
            {
                //stop background music
                nPlayResult = SsmCheckPlay(nCh);
                if(nPlayResult != -1)
                {
                    if(nPlayResult == 0)
                    {
                        if(SsmStopPlayFile(nCh) == -1)
                        {
                            ShowErrMsg("E_CHG_ChState", "TRUNK_FLASHING", "SsmStopPlayFile");
                        }
                    }
                }
                else
                {
                    ShowErrMsg("E_CHG_ChState", "TRUNK_FLASHING", "SsmCheckPlay");
                }
                
                SendMessage(E_MSG_HANGUP, ChInfo[nCh].nLinkToCh, nCh);

                //add for SC-6355 by fr 2011.8.3
                if(SsmHangup(nCh) == -1)
                {
                    ShowErrMsg("E_CHG_ChState", "TRUNK_FLASHING", "SsmHangup");
                }

                memset(ChInfo[nCh].szCallerId, '\0', sizeof(char)*NUM_LENGTH);      //clear CallerId            
                memset(ChInfo[nCh].szCalleeId, '\0', sizeof(char)*NUM_LENGTH);      //clear CalledId            

                ChInfo[nCh].nStatus = TRUNK_IDLE;
                //end add for SC-6355 by fr 2011.8.3
            }
            break;
        default:
            break;
        }
        break;
    case E_CHG_RcvDTMF:
        dwDtmfLen = lParam >> 16;
        dwDtmfNum = lParam & 0xFFFF;

        switch(ChInfo[nCh].nStatus)
        {
        case TRUNK_WAIT_ACTUAL_PICKUP:
            //clear DTMF buffer
            if(SsmClearRxDtmfBuf(nCh) == -1)
            {
                ShowErrMsg("E_CHG_RcvDTMF", "TRUNK_WAIT_ACTUAL_PICKUP", "SsmClearRxDtmfBuf");
            }
            break;
        case TRUNK_WAIT_SELECTION:
            //close T1
            if(SsmStopTimer(ChInfo[nCh].nTimer) == -1)
            {
                ShowErrMsg("E_CHG_RcvDTMF", "TRUNK_WAIT_SELECTION", "SsmStopTimer");
            }
            
            if(dwDtmfLen == MAX_USER_DTMFLEN)
            {
                ChInfo[nCh].szPhoneNumBuf[dwDtmfLen-1] = dwDtmfNum;

                ChInfo[nCh].szPhoneNumBuf[MAX_USER_DTMFLEN] = '\0';

                for(int i=0; i<nMaxCh; i++)
                {
                    if( (ChInfo[i].nChType == 2)
                        && (strcmp(ChInfo[nCh].szPhoneNumBuf, ChInfo[i].CUserNum) == 0) && i != nCh )
                    {
                        ChInfo[nCh].nLinkToCh = i;
                    }               
                }

                if(ChInfo[nCh].nLinkToCh == -1) //invalid extension number
                {
                    //clear DTMF buffer
                    if(SsmClearRxDtmfBuf(nCh) == -1)
                    {
                        ShowErrMsg("E_CHG_RcvDTMF", "TRUNK_WAIT_SELECTION", "SsmClearRxDtmfBuf");
                    }
                    
                    GetCurrentDirectory(MAX_PATH, szVoicePath);
                    strcat(szVoicePath, "\\Error.pcm"); 
                    //play message indicating invalid extension is dialed. 
                    if(SsmPlayFile(nCh, szVoicePath, -1, 0, 0xffffffff) == -1)
                    {
                        ShowErrMsg("E_CHG_RcvDTMF", "TRUNK_WAIT_SELECTION", "SsmPlayFile");
                    }
                    ChInfo[nCh].nTimer = SsmStartTimer(15000, 1);
                    
                }
                else
                {
                    ChInfo[nCh].nStatus = TRUNK_REQ_USER;
                    SendMessage(E_US_SEIZURE, ChInfo[nCh].nLinkToCh, nCh);
                }
            }
            else    //clear Timer T1 to wait for next number
            {
                ChInfo[nCh].szPhoneNumBuf[dwDtmfLen-1] = dwDtmfNum;

                if( (ChInfo[nCh].nTimer = SsmStartTimer(8000, 1)) == -1)
                {
                    ShowErrMsg("E_CHG_RcvDTMF", "TRUNK_WAIT_SELECTION", "SsmStartTimer");
                }
            }
            break;
        case TRUNK_CONNECTED:
            break;
        default:
            break;
        }
        break;
    case E_SYS_TIMEOUT:
        //close T1
        if(SsmStopTimer(ChInfo[nCh].nTimer) == -1)
        {
            ShowErrMsg("E_SYS_TIMEOUT", NULL, "SsmStopTimer");
        }
        //clear DTMF buffer
        if(SsmClearRxDtmfBuf(nCh) == -1)
        {
            ShowErrMsg("E_SYS_TIMEOUT", NULL, "SsmClearRxDtmfBuf");
        }
        //go on-hook
        if(SsmHangup(nCh) == -1)
        {
            ShowErrMsg("E_SYS_TIMEOUT", NULL, "SsmHangup");
        }

        memset(ChInfo[nCh].szCallerId, '\0', sizeof(char)*NUM_LENGTH);      //clear CallerId    
        memset(ChInfo[nCh].szCalleeId, '\0', sizeof(char)*NUM_LENGTH);      //clear CalledId

        ChInfo[nCh].nStatus = TRUNK_IDLE;
        break;
    /*+++++++++define trunk channel message +++++++++*/
    case E_US_SEIZURE_TK:
        ChInfo[nCh].nLinkToCh = lParam;
        //go off-hook successfully？
        if( SsmPickup(nCh) == 0 )
        {           
            //send E_TK_SEIZURE_TK_ACK_IDLE
            SendMessage(E_TK_SEIZURE_TK_ACK_IDLE, ChInfo[nCh].nLinkToCh, nCh);
            ChInfo[nCh].nStatus = TRUNK_WAIT_1STNUM;
        }
        else
        {
            //send E_TK_SEIZURE_TK_ACK_BUSY
            SendMessage(E_TK_SEIZURE_TK_ACK_BUSY, ChInfo[nCh].nLinkToCh, nCh);
        }
        break;
    case E_TK_RELEASE:
        ChInfo[nCh].nLinkToCh = lParam;
        //clear DTMF buffer
        if(SsmClearRxDtmfBuf(nCh) == -1)
        {
            ShowErrMsg("E_TK_RELEASE", NULL, "SsmClearRxDtmfBuf");
        }
        //go on-hook
        if(SsmHangup(nCh) == -1)
        {
            ShowErrMsg("E_TK_RELEASE", NULL, "SsmHangup");
        }

        memset(ChInfo[nCh].szCallerId, '\0', sizeof(char)*NUM_LENGTH);      //clear CallerId
        memset(ChInfo[nCh].szCalleeId, '\0', sizeof(char)*NUM_LENGTH);      //clear CalledId

        ChInfo[nCh].nStatus = TRUNK_IDLE;
        break;
    case E_US_DTMF2TK:
        dwDtmfLen = lParam >> 16;
        dwDtmfNum = lParam & 0xFFFF;
        
        switch(ChInfo[nCh].nStatus)
        {
        case TRUNK_WAIT_1STNUM:         //auto dial
            //clean szPhoneNumBuf
            memset(ChInfo[nCh].szPhoneNumBuf, '\0', sizeof(char)*NUM_LENGTH);   
            //retrieve DTMF
            ChInfo[nCh].szPhoneNumBuf[dwDtmfLen-1] = dwDtmfNum;
            //retrieve length of DTMF
            ChInfo[nCh].nPhoNumLen = dwDtmfLen;

            //audo dial
            if(SsmAutoDial(nCh, ChInfo[nCh].szPhoneNumBuf) == -1)
            {
                ShowErrMsg("E_US_DTMF2TK", "TRUNK_WAIT_1STNUM", "SsmAutoDial");
            }

            ChInfo[nCh].nStatus = TRUNK_DIALING;
            break;
        case TRUNK_DIALING:             
            //retrieve DTMF
            ChInfo[nCh].szPhoneNumBuf[dwDtmfLen-1] = dwDtmfNum;
            ChInfo[nCh].szPhoneNumBuf[dwDtmfLen] = '\0';
            
            if(dwDtmfLen > (DWORD)ChInfo[nCh].nPhoNumLen)           //append number
            {
                //append number 
                if(SsmAppendPhoNum(nCh, &ChInfo[nCh].szPhoneNumBuf[ChInfo[nCh].nPhoNumLen]) == -1)
                {
                    ShowErrMsg("E_US_DTMF2TK", "TRUNK_DIALING", "SsmAppendPhoNum");
                }
                ChInfo[nCh].nPhoNumLen = dwDtmfLen;
            }
            break;
        default:
            break;
        }
        break;
    case E_US_SEIZURE_ACK_IDLE:
        ChInfo[nCh].nLinkToCh = lParam;
        GetCurrentDirectory(MAX_PATH, szVoicePath);
        strcat(szVoicePath, "\\bgmusic.wav");   
        
        //play background music
        if(SsmPlayFile(nCh, szVoicePath, -1, 0, 0xffffffff) == -1)
        {
            ShowErrMsg("E_US_SEIZURE_ACK_IDLE", NULL, "SsmPlayFile");
        }

        ChInfo[nCh].nStatus = TRUNK_RING_BACK;
        break;
    case E_US_SEIZURE_ACK_BUSY:
        //clear DTMF buffer 
        if(SsmClearRxDtmfBuf(nCh) == -1)
        {
            ShowErrMsg("E_US_SEIZURE_ACK_BUSY", NULL, "SsmClearRxDtmfBuf");
        }
        //go on-hook 
        if(SsmHangup(nCh) == -1)
        {
            ShowErrMsg("E_US_SEIZURE_ACK_BUSY", NULL, "SsmHangup");
        }

        memset(ChInfo[nCh].szCallerId, '\0', sizeof(char)*NUM_LENGTH);      //clear CallerId
        memset(ChInfo[nCh].szCalleeId, '\0', sizeof(char)*NUM_LENGTH);      //clear CalledId

        ChInfo[nCh].nLinkToCh = -1;
        ChInfo[nCh].nStatus = TRUNK_IDLE;
        break;
    case E_US_PICKUP:           //called station go off-hook
        //stop playback of background music 
        nPlayResult = SsmCheckPlay(nCh);

        if(nPlayResult != -1)
        {
            if(nPlayResult == 0)
            {
                if(SsmStopPlayFile(nCh) == -1)
                {
                    ShowErrMsg("E_US_PICKUP", NULL, "SsmStopPlayFile");
                }
            }
        }
        else
        {
            ShowErrMsg("E_US_PICKUP", NULL, "SsmCheckPlay");
        }

        //build bus connection 
        if(SsmTalkWith(nCh, ChInfo[nCh].nLinkToCh) == -1)
        {
            ShowErrMsg("E_US_PICKUP", NULL, "SsmTalkWith");
        }

        ChInfo[nCh].nStatus = TRUNK_CONNECTED;
        break;
    case E_MSG_RELEASE:
        if(ChInfo[nCh].nStatus == TRUNK_FLASHING)
        {
            //stop playback of background music 
            nPlayResult = SsmCheckPlay(nCh);
            
            if(nPlayResult != -1)
            {
                if(nPlayResult == 0)
                {
                    if(SsmStopPlayFile(nCh) == -1)
                    {
                        ShowErrMsg("E_MSG_RELEASE", "TRUNK_FLASHING", "SsmStopPlayFile");
                    }
                }
            }
            else
            {
                ShowErrMsg("E_MSG_RELEASE", "TRUNK_FLASHING", "SsmCheckPlay");
            }
        }
        
        //clear DTMF buffer 
        if(SsmClearRxDtmfBuf(nCh) == -1)
        {
            ShowErrMsg("E_MSG_RELEASE", NULL, "SsmClearRxDtmfBuf");
        }
        //go on-hook 
        if(SsmHangup(nCh) == -1)
        {
            ShowErrMsg("E_MSG_RELEASE", NULL, "SsmHangup");
        }

        memset(ChInfo[nCh].szCallerId, '\0', sizeof(char)*NUM_LENGTH);      //clear CallerId
        memset(ChInfo[nCh].szCalleeId, '\0', sizeof(char)*NUM_LENGTH);      //clear CalledId

        ChInfo[nCh].nLinkToCh = -1;
        ChInfo[nCh].nStatus = TRUNK_IDLE;
        break;
    case E_MSG_FLASH:
        GetCurrentDirectory(MAX_PATH, szVoicePath);
        strcat(szVoicePath, "\\bgmusic.wav");
        
        //play background music in call transfer waiting
        if(SsmPlayFile(nCh, szVoicePath, -1, 0, 0xffffffff) == -1)
        {
            ShowErrMsg("E_MSG_FLASH", NULL, "SsmPlayFile");
        }
        
        ChInfo[nCh].nStatus = TRUNK_FLASHING;
        break;
    case E_MSG_CONNECT:
        //stop playback of background music 
        ChInfo[nCh].nLinkToCh = lParam;
        nPlayResult = SsmCheckPlay(nCh);

        if(nPlayResult != -1)
        {
            if(nPlayResult == 0)
            {
                if(SsmStopPlayFile(nCh) == -1)
                {
                    ShowErrMsg("E_MSG_CONNECT", NULL, "SsmStopPlayFile");
                }
            }
        }
        else
        {
            ShowErrMsg("E_MSG_CONNECT", NULL, "SsmCheckPlay");
        }

        ChInfo[nCh].nStatus = TRUNK_CONNECTED;
        break;
    default:
        break;
    }
}

LVS_VOID ShowErrMsg(string lpszEventText, string lpszStatusText, string lpszFunctionText)
{
    //printf("%s,%s,%s\r\n",lpszEventText,lpszStatusText,lpszFunctionText);
    cout<<lpszEventText<<";"<<lpszStatusText<<";"<<lpszFunctionText<<"."<<endl;
}


