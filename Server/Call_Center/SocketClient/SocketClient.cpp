// SocketClient.cpp : 定义控制台应用程序的入口点。
//

#include <WINSOCK2.H>
#include <stdio.h>
#include "json\json.h"
#include <string>
#include <sstream>
#include <iostream>
#include "stdafx.h"

#pragma comment(lib,"ws2_32.lib")

using namespace std;

#define SC_ERROR -1
#define SC_OK     0

#define MSG_HEAD "HEAD"
#define MSG_END  "END"
#define MSG_HEAD_SIZE 4
#define MSG_END_SIZE  3
#define MSG_LENGSTRING_SIZE 4

#define MSG_TYPE_KEY_STRING         "msgType"
#define MSG_TYPE_PHONE_NUMBER       "phoneNumber"
#define MSG_TYPE_USERID      		"userId"
#define MSG_TYPE_DEPARTMENT 		"department"
#define MSG_TYPE_DATETIME 			"datetime"
#define MSG_TYPE_USER_NUMBER 		"userNumber"
#define MSG_TYPE_NAME 				"name"
#define MSG_TYPE_POST 				"post"
#define MSG_TYPE_CALL_NUMBER 		"callNumber"
#define MSG_TYPE_STAFF_STATE 		"staffState"
#define MSG_TYPE_NAMESPELL 			"nameSpell"
#define MSG_TYPE_TASK_ID            "taskId"
#define MSG_TYPE_TASK_NAME			"taskName"
#define MSG_TYPE_TASK_TYPE 			"taskType"
#define MSG_TYPE_TASK_INFO			"taskInfo"
#define MSG_TYPE_TASK_STATE 		"taskState"
#define MSG_TYPE_STAFF_INFO         "staffInfo"
#define MSG_TYPE_IS_RESERVE			"isReserve"
#define MSG_TYPE_RESERVE_TIME		"reserveTime"
#define MSG_TYPE_TASK_TIME			"taskTime"
#define MSG_TYPE_STAFF_NAME			"staffName"
#define MSG_TYPE_DISPATCHER_ID		"dispatcherId"
#define MSG_TYPE_DISPATCHER_NAME	"dispatcherName"
#define MSG_TYPE_VIEW_TASK_LIST		"viewTaskList"
#define MSG_TYPE_START_DATE         "startDate"
#define MSG_TYPE_END_DATE           "endDate"


/*将最大4位10进制正整数转换成string*/
string parseIntToString(int iValue)
{
	string tmp;
	int tmpValue = iValue;
	if(9999 <= tmpValue || 0 > tmpValue)
	{
		//string stringPrintInfo = "parseIntToString->The int value to be parse to string is invalid,";
		//stringPrintInfo.append(changeLongToString((long)iValue ));
		//printString(stringPrintInfo, LVS_COLOR_LIGHTRED,0);
		cout<<"Error Input Value!"<<endl;
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

int _tmain(int argc, _TCHAR* argv[])
{
	int err;
	WORD versionRequired;
	WSADATA wsaData;
	versionRequired=MAKEWORD(1,1);
	err=WSAStartup(versionRequired,&wsaData);//协议库的版本信息
	if (!err)
	{
		printf("客户端嵌套字已经打开!\n");
	}
	else
	{
		printf("客户端的嵌套字打开失败!\n");
		system("pause");
		return SC_ERROR;//结束
	}
	SOCKET clientSocket=socket(AF_INET,SOCK_STREAM,0);
	SOCKADDR_IN clientsock_in;
	clientsock_in.sin_addr.S_un.S_addr=inet_addr("192.168.1.100");
	clientsock_in.sin_family=AF_INET;
	clientsock_in.sin_port=htons(6789);
	//bind(clientSocket,(SOCKADDR*)&clientsock_in,strlen(SOCKADDR));//注意第三个参数
	//listen(clientSocket,5);
	//开始连接
	if(SOCKET_ERROR == connect(clientSocket,(SOCKADDR*)&clientsock_in,sizeof(SOCKADDR)))
	{
		cout<<"Connect Error"<<endl;
		WSACleanup();
		system("pause");
		return SC_ERROR;
	}

	char receiveBuf[1200];

	string strMsgHead = MSG_HEAD;
	string strMsgTail = MSG_END;

	int tempA;
	cin>>tempA;
	
	int i = 1;
	while (true)
	{
		memset(receiveBuf,0,sizeof(receiveBuf));
		
		//cin>>msgType;
		int msgType = 2000 + i;
		//msgType = 2005;
		i++;
		if (10 < i)
		{
			i -= 10;
		}
		
		

		Json::FastWriter fast_writer;
		Json::Value root;

		if (tempA != msgType && 1234 != tempA)
		{
			goto Next_While;
		}
		cout<<msgType<<endl;

		root[MSG_TYPE_KEY_STRING] = Json::Value(msgType);

		

		switch(msgType)
		{
		case 2001:
			root[MSG_TYPE_NAMESPELL] = Json::Value("l");
			break;
		case 2002:
			root[MSG_TYPE_PHONE_NUMBER] = Json::Value("18768163484");
			root[MSG_TYPE_NAME] = Json::Value("QIANMING");
			root[MSG_TYPE_DEPARTMENT] = Json::Value("WAIKE");
			break;
		case 2003:
			root[MSG_TYPE_TASK_ID] = Json::Value(58);
			root[MSG_TYPE_PHONE_NUMBER] = Json::Value("18768163484");
			root[MSG_TYPE_USER_NUMBER] = Json::Value("0102");
			root[MSG_TYPE_DEPARTMENT] = Json::Value("houqing");
			root[MSG_TYPE_IS_RESERVE] = Json::Value(1);
			root[MSG_TYPE_TASK_STATE] = Json::Value(1);
			root[MSG_TYPE_DISPATCHER_ID] = Json::Value(1);
			root[MSG_TYPE_TASK_TYPE].append(1);
			root[MSG_TYPE_TASK_TYPE].append(3);
			root[MSG_TYPE_TASK_TYPE].append(4);
			break;
		case 2004:
			//root[MSG_TYPE_TASK_ID] = Json::Value(58);
			root[MSG_TYPE_PHONE_NUMBER] = Json::Value("18768163484");
			root[MSG_TYPE_USER_NUMBER] = Json::Value("0102");
			root[MSG_TYPE_DEPARTMENT] = Json::Value("houqing");
			root[MSG_TYPE_IS_RESERVE] = Json::Value(0);
			root[MSG_TYPE_TASK_STATE] = Json::Value(1);
			root[MSG_TYPE_DATETIME] = Json::Value("2012-06-23 23:50:55");
			root[MSG_TYPE_TASK_TYPE].append(1);
			root[MSG_TYPE_TASK_TYPE].append(3);
			root[MSG_TYPE_TASK_TYPE].append(4);
			break;
		case 2005:
			root[MSG_TYPE_START_DATE] = Json::Value("2012-06-22");
			root[MSG_TYPE_END_DATE] = Json::Value("2012-06-22");
			break;
		case 2006:
			break;
		case 2007:
			root[MSG_TYPE_TASK_NAME] = Json::Value("Blood");
			root[MSG_TYPE_TASK_TYPE] = Json::Value("1");
			break;
		case 2008:
			break;
		default:
			//goto Next_While;
			break;

		}
		/*发送消息过程*/
		{
			string jsonstr ;
			if(Json::nullValue != root.type())
			{
				jsonstr = fast_writer.write(root);
			}
			string strRespMsg = strMsgHead + parseIntToString(jsonstr.length() - 1) + jsonstr.substr(0, jsonstr.length() - 1) + strMsgTail;

			if (send(clientSocket,strRespMsg.c_str(),strRespMsg.length(),0) > 0)
			{
				cout<<"Send Ok:"<<strRespMsg<<endl;
			}
			else
			{
				cout<<"Send Failed."<<endl;
			}
		}


		if (2010 == msgType)
		{
			Sleep(10000);
			cout<<"+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
		}
		else
		{
			Sleep(1000);
		}
Next_While:		
		continue;

		if(recv(clientSocket,receiveBuf,101,0)>0)
		{
			printf("Receive OK:%s\r\n",receiveBuf);
		}
		else
		{
			printf("Receive Failed.\r\n");
		}
		//printf("%s\n",receiveBuf);
		//send(clientSocket,"hello,this is client",strlen("hello,this is client")+1,0);
		cout<<"+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
		//Sleep(1000*60);
	}
	


	closesocket(clientSocket);
	WSACleanup();

	system("pause");
	return 0;
}

