#include <sstream>
#include "LVS_MessageConvert.h"
#include "LVS_Message_Struct_define.h"
#include "LVS_PID_Init.h"

extern LVS_UINT32 LVS_SendMsg(LVS_MSG_INFO_STRU *pstValue);
extern LVS_UINT32 LVS_SendRespMsg(LVS_MSG_INFO_STRU *pstMsg);

hash_map<LVS_INT32, string> m_hmServerMsgBuf;
LVS_UINT32 m_ulMsgBufferLock = 0;


/*将最大4位10进制正整数转换成string*/
string parseIntToString(int iValue)
{
    string tmp;
	int tmpValue = iValue;
	if(9999 <= tmpValue || 0 > tmpValue)
	{
	#if 0
	    printTime();
        set_console_color(LVS_COLOR_LIGHTRED);
		cout<<"The int value to be parse to string is invalid,"<<iValue<<endl;
        set_console_color(LVS_COLOR_WHITE);
    #endif
        string stringPrintInfo = "parseIntToString->The int value to be parse to string is invalid,";
        stringPrintInfo.append(changeLongToString((long)iValue ));
        printString(stringPrintInfo, LVS_COLOR_LIGHTRED,0);
		tmpValue = 0;
	}
	stringstream intTostr;
	
	for (int i = 1000; i > 0; i = i/10)
	{
		intTostr <<(tmpValue/i);
		tmpValue=tmpValue%i;
	}
	intTostr>>tmp;
	return tmp;
}

LVS_UINT32 parseStringToInt(string str)
{
	stringstream strToInt;
	LVS_UINT32 tmp;
    if(4 < str.length())
    {
        string stringPrintInfo = "parseStringToInt->The int value to be parse to string is invalid,";
        stringPrintInfo.append(str);
        printString(stringPrintInfo, LVS_COLOR_LIGHTRED,0);
        return 0;
    }
	strToInt<<str;
	strToInt>>tmp;

	return tmp;
}


LVS_UINT32 receiveServerMsg(const char *acMsgBuff,  LVS_INT32 socketId)
{
    while(0 != m_ulMsgBufferLock)
    {
        Sleep(10);
    }
    
    m_ulMsgBufferLock = 1;
    if(m_hmServerMsgBuf.find(socketId) != m_hmServerMsgBuf.end())
    {
        m_hmServerMsgBuf[socketId].append(acMsgBuff);
    }
    else
    {
        m_hmServerMsgBuf[socketId] = acMsgBuff;
    }
    m_ulMsgBufferLock = 0;
    return LVS_OK;
}
/*将JSON string解析出来，并将消息请求放到消息队列中去*/
LVS_UINT32 unpackJsonMsg(LVS_INT32 lSocketId,string stJsonMsg)
{
    printString("unpackJsonMsg->" + stJsonMsg,LVS_COLOR_GREEN,1);
    Json::Reader reader;
	Json::Value json_object;
    if (!reader.parse(stJsonMsg, json_object))
	{
   
        string stringPrintInfo = "unpackJsonMsg->Parse string to JSON failed,";
        stringPrintInfo.append(stJsonMsg);
        printString(stringPrintInfo, LVS_COLOR_LIGHTRED,1);
		return LVS_ERR;
	}
    
    if(Json::nullValue == json_object[MSG_TYPE_KEY_STRING].type())
    {
 
        string stringPrintInfo = "unpackJsonMsg->Can not find Message type,";
        stringPrintInfo.append(stJsonMsg);
        printString(stringPrintInfo, LVS_COLOR_LIGHTRED,1);
        return LVS_ERR;
    }
    else if(Json::intValue != json_object[MSG_TYPE_KEY_STRING].type())
    {

        string stringPrintInfo = "unpackJsonMsg->Message type is inValid,";
        stringPrintInfo.append(stJsonMsg);
        printString(stringPrintInfo, LVS_COLOR_LIGHTRED,1);
        return LVS_ERR;
    }
    LVS_UINT32 ulMsgType = json_object[MSG_TYPE_KEY_STRING].asInt();

    LVS_MSG_INFO_STRU stMsgInfo;
    memset(&stMsgInfo, 0, sizeof(stMsgInfo));
    stMsgInfo.lSocketId = lSocketId;
    stMsgInfo.ulSendPid = PID_SOCKET_MSG_PROXY;
    stMsgInfo.ulReceivePid = PID_SOCKET_MSG_PROXY;
    stMsgInfo.ulMsgType = LVS_MSG_TYPE_SOCKET;
    stMsgInfo.ulMsgId = ulMsgType;
    stMsgInfo.ulIsTimeConsuming = LVS_TRUE;

	LVS_UINT32 len = 0;
    
    switch(ulMsgType)
    {
        case DOWN_MSG_TYPE_QUERY_STAFF_INFO_REQUEST:
            /*按查询请求消息体解析*/
            {
                CC_QUERY_STAFF_KEY_INFO_STRU stQueryStaffKeyInfo;
                memset(&stQueryStaffKeyInfo, 0, sizeof(stQueryStaffKeyInfo));
                
                string strTemp = json_object[MSG_TYPE_NAMESPELL].asString();
                len = sizeof(stQueryStaffKeyInfo.nameSpell) - 1;
                len = (len > strTemp.length()) ? strTemp.length() : len;
                memcpy((void*)stQueryStaffKeyInfo.nameSpell, (void*)strTemp.c_str(), len);
                stMsgInfo.ulMsgLen = sizeof(stQueryStaffKeyInfo);
                stMsgInfo.pMsgData = (void*)&stQueryStaffKeyInfo;
                
                break;
            }
        case DOWN_MSG_TYPE_UPDATE_CALLER_INFO:
            /*按来电者消息体解析*/
            {
                CC_CALLER_INFO_STRU stCallerInfo;
                memset(&stCallerInfo, 0,sizeof(stCallerInfo));

                string strTemp;
                strTemp = json_object[MSG_TYPE_PHONE_NUMBER].asString();
                len = sizeof(stCallerInfo.phoneNumber) - 1;
                len = (len > strTemp.length()) ? strTemp.length() : len;
                memcpy((void*)stCallerInfo.phoneNumber, (void*)strTemp.c_str(),len);

                strTemp = json_object[MSG_TYPE_NAME].asString();
                len = sizeof(stCallerInfo.name) - 1;
                len = (len > strTemp.length()) ? strTemp.length() : len;
                memcpy((void*)stCallerInfo.name, (void*)strTemp.c_str(),len);

                strTemp = json_object[MSG_TYPE_DEPARTMENT].asString();
                len = sizeof(stCallerInfo.department) - 1;
                len = (len > strTemp.length()) ? strTemp.length() : len;
                memcpy((void*)stCallerInfo.department, (void*)strTemp.c_str(),len);

                stMsgInfo.ulMsgLen = sizeof(stCallerInfo);
                stMsgInfo.pMsgData = (void*)&stCallerInfo;
                
                break;
            }
        case DOWN_MSG_TYPE_TASK_DISPATCH:
            /*按任务派遣信息解析*/
            {
                CC_TASK_DISPATCH_INFO_STRU stTaskDispatchInfo;
                memset(&stTaskDispatchInfo, 0, sizeof(stTaskDispatchInfo));

                stTaskDispatchInfo.taskId = json_object[MSG_TYPE_TASK_ID].asUInt();
                stTaskDispatchInfo.taskState = json_object[MSG_TYPE_TASK_STATE].asUInt();
                
                string strTempCallPhoneNumber = json_object[MSG_TYPE_PHONE_NUMBER].asString();
                len = sizeof(stTaskDispatchInfo.callerPhoneNumber) - 1;
                len = (len > strTempCallPhoneNumber.length()) ? strTempCallPhoneNumber.length() : len;
                memcpy((void*)stTaskDispatchInfo.callerPhoneNumber, (void*)strTempCallPhoneNumber.c_str(), len);
                
                string strTempUserNumer = json_object[MSG_TYPE_USER_NUMBER].asString();
                len = sizeof(stTaskDispatchInfo.userNumber) - 1;
                len = (len > strTempUserNumer.length()) ? strTempUserNumer.length() : len;
                memcpy((void*)stTaskDispatchInfo.userNumber, (void*)strTempUserNumer.c_str(), len);

				string strTempDepartment = json_object[MSG_TYPE_DEPARTMENT].asString();
				len = sizeof(stTaskDispatchInfo.department) - 1;
				len = (len > strTempDepartment.length()) ? strTempDepartment.length() : len;
				memcpy((void*)stTaskDispatchInfo.department, (void*)strTempDepartment.c_str(),len);

                if(Json::arrayValue == json_object[MSG_TYPE_TASK_TYPE].type())
                {
                    LVS_UINT32 ulsize = (LVS_UINT32)json_object[MSG_TYPE_TASK_TYPE].size();
                    if(ulsize > sizeof(stTaskDispatchInfo.taskType)/sizeof(stTaskDispatchInfo.taskType[0]))
                    {
                        ulsize = sizeof(stTaskDispatchInfo.taskType)/sizeof(stTaskDispatchInfo.taskType[0]);
                    }
                    for(LVS_UINT32 ulIndex = 0; ulIndex < ulsize; ulIndex++)
                    {
                        stTaskDispatchInfo.taskType[ulIndex] = (unsigned long)json_object[MSG_TYPE_TASK_TYPE][ulIndex].asInt();
                    }
                }

                stTaskDispatchInfo.isReserve = json_object[MSG_TYPE_IS_RESERVE].asUInt();
				stTaskDispatchInfo.dispatcherId = json_object[MSG_TYPE_DISPATCHER_ID].asUInt();

                stMsgInfo.ulMsgLen = sizeof(stTaskDispatchInfo);
                stMsgInfo.pMsgData = (void*)&stTaskDispatchInfo;
                
                break;
            }

        case DOWN_MSG_TYPE_RESERVE_INFO:
            /*解析预约任务信息*/
            {
                CC_TASK_DISPATCH_INFO_STRU stTaskDispatchInfo;
                memset(&stTaskDispatchInfo, 0, sizeof(stTaskDispatchInfo));

                stTaskDispatchInfo.taskId = json_object[MSG_TYPE_TASK_ID].asUInt();
                stTaskDispatchInfo.taskState = json_object[MSG_TYPE_TASK_STATE].asUInt();
                
                string strTempCallPhoneNumber = json_object[MSG_TYPE_PHONE_NUMBER].asString();
                len = sizeof(stTaskDispatchInfo.callerPhoneNumber) - 1;
                len = (len > strTempCallPhoneNumber.length()) ? strTempCallPhoneNumber.length() : len;
                memcpy((void*)stTaskDispatchInfo.callerPhoneNumber, (void*)strTempCallPhoneNumber.c_str(), len);
                
                string strTempUserNumer = json_object[MSG_TYPE_USER_NUMBER].asString();
                len = sizeof(stTaskDispatchInfo.userNumber) - 1;
                len = (len > strTempUserNumer.length()) ? strTempUserNumer.length() : len;
                memcpy((void*)stTaskDispatchInfo.userNumber, (void*)strTempUserNumer.c_str(), len);

				string strTempDepartment = json_object[MSG_TYPE_DEPARTMENT].asString();
				len = sizeof(stTaskDispatchInfo.department) - 1;
				len = (len > strTempDepartment.length()) ? strTempDepartment.length() : len;
				memcpy((void*)stTaskDispatchInfo.department, (void*)strTempDepartment.c_str(),len);

                if(Json::arrayValue == json_object[MSG_TYPE_TASK_TYPE].type())
                {
                    LVS_UINT32 ulsize = (LVS_UINT32)json_object[MSG_TYPE_TASK_TYPE].size();
                    if(ulsize > sizeof(stTaskDispatchInfo.taskType)/sizeof(stTaskDispatchInfo.taskType[0]))
                    {
                        ulsize = sizeof(stTaskDispatchInfo.taskType)/sizeof(stTaskDispatchInfo.taskType[0]);
                    }
                    for(LVS_UINT32 ulIndex = 0; ulIndex < ulsize; ulIndex++)
                    {
                        stTaskDispatchInfo.taskType[ulIndex] = (unsigned long)json_object[MSG_TYPE_TASK_TYPE][ulIndex].asInt();
                    }
                }

                stTaskDispatchInfo.isReserve = json_object[MSG_TYPE_IS_RESERVE].asUInt();
                
                string strTempReserveTime = json_object[MSG_TYPE_DATETIME].asString();
                len = sizeof(stTaskDispatchInfo.datetime) - 1;
                len = (len > strTempReserveTime.length()) ? strTempReserveTime.length() : len;
                memcpy((void*)stTaskDispatchInfo.datetime, (void*)strTempReserveTime.c_str(), len);

                stMsgInfo.ulMsgLen = sizeof(stTaskDispatchInfo);
                stMsgInfo.pMsgData = (void*)&stTaskDispatchInfo;
                
                break;
            }
        case DOWN_MSG_TYPE_VIEW_TASK_LIST_BETWEEN_S_AND_E:
			{
				/*查看某两天之间的所有任务记录，S-start, E-end*/
				CC_VIEW_TASK_LIST_BETWEEN_START_END stViewTaskListReq;
				memset(&stViewTaskListReq, 0, sizeof(stViewTaskListReq));

				string strTemp = json_object[MSG_TYPE_START_DATE].asString();
				len = sizeof(stViewTaskListReq.startDate) - 1;
				len = (len > strTemp.length()) ? strTemp.length() : len;
				memcpy((void*)stViewTaskListReq.startDate, (void*)strTemp.c_str(),len);

				strTemp = json_object[MSG_TYPE_END_DATE].asString();
				len = sizeof(stViewTaskListReq.endDate) - 1;
				len = (len > strTemp.length()) ? strTemp.length() : len;
				memcpy((void*)stViewTaskListReq.endDate, (void*)strTemp.c_str(),len);

				stMsgInfo.ulMsgLen = sizeof(stViewTaskListReq);
				stMsgInfo.pMsgData = (void*)&stViewTaskListReq;
				
				break;
        	}
		case DOWN_MSG_TYPE_GET_TASK_INFO:
			{
				/*请求所有任务信息*/
				break;
			}
		case DOWN_MSG_TYPE_ADD_ONE_TASK_INFO:
			{
				/*新增一个任务种类信息*/
				CC_TASK_INFO_STRU stTaskInfo;
				memset(&stTaskInfo, 0, sizeof(stTaskInfo));

				string strTemp  = json_object[MSG_TYPE_TASK_NAME].asString();
				len = sizeof(stTaskInfo.taskName) - 1;
				len = (len > strTemp.length()) ? strTemp.length() : len;
				memcpy((void*)&stTaskInfo.taskName, (void*)strTemp.c_str(), len);

				strTemp  = json_object[MSG_TYPE_TASK_TYPE].asString();
				len = sizeof(stTaskInfo.taskType)- 1;
				len = (len > strTemp.length()) ? strTemp.length() : len;
				memcpy((void*)&stTaskInfo.taskType, (void*)strTemp.c_str(), len);

				stMsgInfo.ulMsgLen = sizeof(stTaskInfo);
				stMsgInfo.pMsgData = (void*)&stTaskInfo;
				
				break;
			}	
        case DOWN_MSG_TYPE_HEAT_BEAT:
			{
            	/*按心跳消息体解析*/
            	break;
        	}
        default:
            break;
    }

    if(LVS_OK != LVS_SendMsg(&stMsgInfo))
    {
        string stringPrintInfo = "unpackJsonMsg->LVS_SendMsg failed,";
        stringPrintInfo.append(stJsonMsg);
        printString(stringPrintInfo, LVS_COLOR_LIGHTRED,1);
        return LVS_ERR;
    }
    
	return LVS_OK;
}

static unsigned __stdcall parseDownMessage(void *p)
{
    //cout<<"Begin parseDownMessage"<<endl;
    printString("Begin parseDownMessage", LVS_COLOR_WHITE,1);
    LVS_UINT32 ulRet = LVS_OK;
    while(TRUE)
    {
        hash_map<LVS_INT32,string>::iterator it; 
        for(it = m_hmServerMsgBuf.begin(); it != m_hmServerMsgBuf.end(); )
        {
            while(0 != m_ulMsgBufferLock)
            {
                Sleep(10);
            }
            m_ulMsgBufferLock = 1;
            LVS_INT32 lSocketId = (LVS_INT32)it->first;
            
            string strTemp = it->second;
            #if 0
            if(0 != strTemp.length())
            {
                string stringPrintInfo = "Socket : ";
                stringPrintInfo.append(changeLongToString((long) lSocketId));
                stringPrintInfo.append(", msgBuff is ");
                stringPrintInfo.append(strTemp);
                printString(stringPrintInfo,LVS_COLOR_LIGHTGREEN);
            }
            #endif
            LVS_INT32 beginIndex = -1;
            LVS_INT32 beginIndexII = 0;
            LVS_INT32 endIndex = 0;
            if("" == strTemp)
            {
                m_hmServerMsgBuf.erase(it++);
                m_ulMsgBufferLock = 0;
                continue;
            }
            /*若消息缓存中找不到消息头，则认为该消息无效，清除掉*/
            if(string::npos == strTemp.find(MSG_HEAD))
            {
                (it->second).clear();
                m_ulMsgBufferLock = 0;
                it++;
                continue;
            }
            endIndex = strTemp.find(MSG_END);
            if(string::npos == endIndex)
            {
                m_ulMsgBufferLock = 0;
                it++;
                continue;
            }
            while(string::npos != beginIndexII)
            {
                beginIndexII = strTemp.find(MSG_HEAD,beginIndex + 1);
                if((beginIndexII < endIndex) && (string::npos != beginIndexII))
                {
                    beginIndex = beginIndexII;
                }
                else
                {
                    break;
                }
            }

            /*更新消息缓存*/
            string strTempII = it->second;
            it->second = strTempII.substr(endIndex + MSG_END_SIZE, strTempII.length() - endIndex - MSG_END_SIZE);
            m_ulMsgBufferLock = 0;
            
            if(-1 == beginIndex)
            {
                it++;
                continue;
            }
            
            string strMsg =  strTemp.substr((beginIndex + MSG_HEAD_SIZE), (endIndex - beginIndex - MSG_HEAD_SIZE));
            
            /*处理消息*/
            string strMsgLen = strMsg.substr(0 ,MSG_LENGSTRING_SIZE);
            LVS_UINT32 lMsgLength = parseStringToInt(strMsgLen);

            if(strMsg.length() >= lMsgLength + MSG_LENGSTRING_SIZE)
            {
                string strMsgBody = strMsg.substr(MSG_LENGSTRING_SIZE,lMsgLength);
                ulRet = unpackJsonMsg(lSocketId,strMsgBody);
                if(LVS_OK != ulRet)
                {
                #if 0
                    printTime();
                    set_console_color(LVS_COLOR_LIGHTRED);
                    cout<<"parseDownMessage ->unpackJsonMsg failed,"<<strMsgBody<<endl;
                    set_console_color(LVS_COLOR_WHITE);
                #endif
                    string stringPrintInfo = "parseDownMessage ->unpackJsonMsg failed,";
                    stringPrintInfo.append(strMsgBody);
                    printString(stringPrintInfo, LVS_COLOR_LIGHTRED,1);
                }
            }
            it++;

        }
    }
    
}
HANDLE startParseDownMsgThread()
{
    HANDLE handle;
    LVS_UINT32 ulThreadID;
    handle = (HANDLE)_beginthreadex(NULL,
                                   0,
                                   parseDownMessage,
                                   NULL,
                                   0,
                                   (PBEGINTHREADEX_THREADID)&ulThreadID);
    return handle;
}

LVS_UINT32 closeParseDownMsgThread(HANDLE handle)
{
    CloseHandle(handle);
    return LVS_OK;
}

LVS_UINT32 packToJsonStringAndSend(LVS_MSG_INFO_STRU *pstMsg)
{
    LVS_UINT32 ulRet = 0;
    LVS_MSG_INFO_STRU stJsonMsg;
    Json::FastWriter fast_writer;
	Json::Value root;

    string strMsgHead = MSG_HEAD;
    string strMsgTail = MSG_END;
    
    memcpy(&stJsonMsg, pstMsg, LVS_MSG_HEADER_SIZE);

    root[MSG_TYPE_KEY_STRING] = Json::Value((unsigned int)pstMsg->ulMsgId);
    
    switch(pstMsg->ulMsgId)
    {
        case UP_MSG_TYPE_DIALOG_POP:
            /*弹窗信息*/
            {
                break;
            }
        case UP_MSG_TYPE_PHONE_NUMBER:
            /*来电号码*/
            {
                if(LVS_NULL_PTR == pstMsg->pMsgData)
                {
                    string stringPrintInfo = "packToJsonStringAndSend->pstMsg->pMsgData is NULL,msgId is ";
                    stringPrintInfo.append(changeLongToString((long) pstMsg->ulMsgId));
                    printString(stringPrintInfo,LVS_COLOR_LIGHTRED,0);
                    return LVS_ERR;
                }
                CC_PHONE_NUMBER_INFO_STRU *pstPhoneInfo = (CC_PHONE_NUMBER_INFO_STRU*)pstMsg->pMsgData;
                root[MSG_TYPE_PHONE_NUMBER] = Json::Value(pstPhoneInfo->phoneNumber);
                break;
            }
        case UP_MSG_TYPE_CALLER_INFO:
            /*来电者信息*/
            {
                if(LVS_NULL_PTR == pstMsg->pMsgData)
                {
                    string stringPrintInfo = "packToJsonStringAndSend->pstMsg->pMsgData is NULL,msgId is ";
                    stringPrintInfo.append(changeLongToString((long) pstMsg->ulMsgId));
                    printString(stringPrintInfo,LVS_COLOR_LIGHTRED,0);
                    return LVS_ERR;
                }
                CC_CALLER_INFO_STRU *pstCallerInfo = (CC_CALLER_INFO_STRU*)pstMsg->pMsgData;
                root[MSG_TYPE_USERID] = Json::Value((unsigned int)pstCallerInfo->userId);
                root[MSG_TYPE_PHONE_NUMBER] = Json::Value(pstCallerInfo->phoneNumber);
                root[MSG_TYPE_NAME] = Json::Value(pstCallerInfo->name);
                root[MSG_TYPE_DEPARTMENT] = Json::Value(pstCallerInfo->department);
                root[MSG_TYPE_DATETIME] = Json::Value(pstCallerInfo->datetime);
                root[MSG_TYPE_TASK_ID] = Json::Value((unsigned int)pstCallerInfo->taskId);
                break;
            }
        case UP_MSG_TYPE_STAFF_INFO:
            /*员工信息*/
            {
                if(LVS_NULL_PTR == pstMsg->pMsgData)
                {
                    string stringPrintInfo = "packToJsonStringAndSend->pstMsg->pMsgData is NULL,msgId is ";
                    stringPrintInfo.append(changeLongToString((long) pstMsg->ulMsgId));
                    printString(stringPrintInfo,LVS_COLOR_LIGHTRED,0);
                    return LVS_ERR;
                }
                CC_STAFF_INFO_SET_STRU *pstStaffInfoSet = (CC_STAFF_INFO_SET_STRU*)pstMsg->pMsgData;
                LVS_UINT32 ulStaffNum = pstMsg->ulMsgLen / sizeof(CC_STAFF_INFO_STRU);
                for(LVS_UINT32 i = 0; i < ulStaffNum; i++)
                {
                    CC_STAFF_INFO_STRU *pstStaffInfoSetTemp = (pstStaffInfoSet->stStaffInfoList + i);
                    Json::Value staffJsonValue;
                    staffJsonValue[MSG_TYPE_USER_NUMBER] = Json::Value(pstStaffInfoSetTemp->userNumber);
                    staffJsonValue[MSG_TYPE_NAME] = Json::Value(pstStaffInfoSetTemp->name);
                    staffJsonValue[MSG_TYPE_POST] = Json::Value(pstStaffInfoSetTemp->post);
                    staffJsonValue[MSG_TYPE_CALL_NUMBER] = Json::Value(pstStaffInfoSetTemp->callNumber);
                    staffJsonValue[MSG_TYPE_PHONE_NUMBER] = Json::Value(pstStaffInfoSetTemp->phoneNumber);
                    staffJsonValue[MSG_TYPE_STAFF_STATE] = Json::Value((unsigned int)pstStaffInfoSetTemp->state);
                    root[MSG_TYPE_STAFF_INFO].append(staffJsonValue);
                }
                break;
            }
		case UP_MSG_TYPE_STOP_CALLIN:
			{
				break;
			}
		case UP_MSG_TYPE_TASK_LIST_BETWEEN_S_AND_E:
			/*某两天之间所有的任务信息*/
			{
                if(LVS_NULL_PTR == pstMsg->pMsgData)
                {
                    string stringPrintInfo = "packToJsonStringAndSend->pstMsg->pMsgData is NULL,msgId is ";
                    stringPrintInfo.append(changeLongToString((long) pstMsg->ulMsgId));
                    printString(stringPrintInfo,LVS_COLOR_LIGHTRED,0);
                    return LVS_ERR;
                }
				CC_VIEW_TASK_LIST_SET_STRU *pstViewTaskListSet = (CC_VIEW_TASK_LIST_SET_STRU*)pstMsg->pMsgData;
				LVS_UINT32 ulTaskListNum = pstMsg->ulMsgLen / sizeof(CC_VIEW_TASK_LIST_STRU);
				CC_VIEW_TASK_LIST_STRU *pstViewTaskList;
				for(LVS_UINT32 i = 0; i < ulTaskListNum; i++)
				{
					pstViewTaskList = (pstViewTaskListSet->stViewTaskList + i);
					Json::Value viewTaskListJsonValue;
					viewTaskListJsonValue[MSG_TYPE_TASK_TIME] = Json::Value(pstViewTaskList->datetime);
					viewTaskListJsonValue[MSG_TYPE_DEPARTMENT] = Json::Value(pstViewTaskList->department);
					viewTaskListJsonValue[MSG_TYPE_PHONE_NUMBER] = Json::Value(pstViewTaskList->callerPhoneNumber);
					for(LVS_UINT32 j = 0; j < sizeof(pstViewTaskList->taskType)/sizeof(pstViewTaskList->taskType[0]); j++)
					{
						LVS_UINT32 ulTaskType = pstViewTaskList->taskType[j];
						if(0 != ulTaskType)
						{
							viewTaskListJsonValue[MSG_TYPE_TASK_TYPE].append((unsigned int)ulTaskType);
						}
					}
					viewTaskListJsonValue[MSG_TYPE_STAFF_NAME] = Json::Value(pstViewTaskList->staffName);
					viewTaskListJsonValue[MSG_TYPE_TASK_STATE] = Json::Value((unsigned int)pstViewTaskList->taskState);
					viewTaskListJsonValue[MSG_TYPE_DISPATCHER_NAME] = Json::Value(pstViewTaskList->dispatcher_name);
					root[MSG_TYPE_VIEW_TASK_LIST].append(viewTaskListJsonValue);
				}
			}
			break;
		case UP_MSG_TYPE_RESERVE_INFO:
			{
				if(LVS_NULL_PTR == pstMsg->pMsgData || sizeof(CC_RESERVE_INFO_STRU) > pstMsg->ulMsgLen)
                {
                    string stringPrintInfo = "packToJsonStringAndSend->pstMsg->pMsgData is InValid,msgId is ";
                    stringPrintInfo.append(changeLongToString((long) pstMsg->ulMsgId));
                    printString(stringPrintInfo,LVS_COLOR_LIGHTRED,0);
                    return LVS_ERR;
                }
				CC_RESERVE_INFO_STRU *pstReserveInfo = (CC_RESERVE_INFO_STRU*)pstMsg->pMsgData;
				root[MSG_TYPE_RESERVE_ID] = Json::Value((unsigned int)pstReserveInfo->reserveId);
				root[MSG_TYPE_PHONE_NUMBER] = Json::Value(pstReserveInfo->callerPhoneNumber);
				root[MSG_TYPE_USER_NUMBER] = Json::Value(pstReserveInfo->userNumber);
				root[MSG_TYPE_DEPARTMENT] = Json::Value(pstReserveInfo->department);
				root[MSG_TYPE_TASK_STATE] = Json::Value((unsigned int)pstReserveInfo->taskState);
				root[MSG_TYPE_DATETIME] = Json::Value(pstReserveInfo->reserveTime);
				for(LVS_UINT32 j = 0; j < sizeof(pstReserveInfo->taskType)/sizeof(pstReserveInfo->taskType[0]); j++)
				{
					LVS_UINT32 ulTaskType = pstReserveInfo->taskType[j];
					if(0 != ulTaskType)
					{
						root[MSG_TYPE_TASK_TYPE].append((unsigned int)ulTaskType);
					}
				}
				break;
			}
		case UP_MSG_TYPE_GET_ALL_TASK_INFO:
			{
                if(LVS_NULL_PTR == pstMsg->pMsgData)
                {
                    string stringPrintInfo = "packToJsonStringAndSend->pstMsg->pMsgData is NULL,msgId is ";
                    stringPrintInfo.append(changeLongToString((long) pstMsg->ulMsgId));
                    printString(stringPrintInfo,LVS_COLOR_LIGHTRED,0);
                    return LVS_ERR;
                }
				CC_TASK_INFO_SET_STRU *pstTaskInfoSet = (CC_TASK_INFO_SET_STRU*)pstMsg->pMsgData;
				CC_TASK_INFO_STRU *pstTaskInfo = LVS_NULL_PTR;
				LVS_UINT32 ulTaskInfoNum = pstMsg->ulMsgLen / sizeof(CC_TASK_INFO_STRU);
				for(LVS_UINT32 i = 0; i < ulTaskInfoNum; i++)
				{
					pstTaskInfo = (pstTaskInfoSet->stTaskInfo + i);
					Json::Value taskInfoJsonValue;
					taskInfoJsonValue[MSG_TYPE_TASK_ID] = Json::Value((unsigned int)pstTaskInfo->taskId);
					taskInfoJsonValue[MSG_TYPE_TASK_NAME] = Json::Value(pstTaskInfo->taskName);
					taskInfoJsonValue[MSG_TYPE_TASK_TYPE] = Json::Value((unsigned int)pstTaskInfo->taskType);
					root[MSG_TYPE_TASK_INFO].append(taskInfoJsonValue);
				}
			}
			break;
        case UP_MSG_TYPE_RESP_HEAT_BEAT:
            /*响应心跳信息*/
            {
                break;
            }
        default:
            {
                string stringPrintInfo = "packToJsonStringAndSend, msgId is invalid:";
                stringPrintInfo.append(changeLongToString((long)pstMsg->ulMsgId ));
                printString(stringPrintInfo, LVS_COLOR_LIGHTRED,0);
                return LVS_ERR;
            }
    }
    string jsonstr ;
    if(Json::nullValue != root.type())
    {
        jsonstr = fast_writer.write(root);
    }

    string strRespMsg = strMsgHead + parseIntToString(jsonstr.length() - 1) + jsonstr.substr(0, jsonstr.length() - 1) + strMsgTail;
    stJsonMsg.pMsgData = (void*)strRespMsg.c_str();
    stJsonMsg.ulMsgLen = strRespMsg.length();

    printString("packToJsonStringAndSend->" + strRespMsg, LVS_COLOR_BLUE,1);

    ulRet = LVS_SendRespMsg(&stJsonMsg);
    if(LVS_OK != ulRet)
    {
        string stringPrintInfo = "packToJsonStringAndSend ->LVS_SendRespMsg failed:";
        stringPrintInfo.append(changeLongToString((long)ulRet ));
        printString(stringPrintInfo, LVS_COLOR_LIGHTRED,0);
    }
    return ulRet;
    
}

