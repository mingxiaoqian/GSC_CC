#include<ctime>
#include "LVS_SocketServer.h"
#include "LVS_MessageConvert.h"
#include "LVS_IPTelNoBind.h"

LVS_Socket_Server *g_pServer;

LVS_Socket_Server::LVS_Socket_Server()
{
    pstSocketMsgList = new LVS_MessageQueue();
    handleParseMsg = startParseDownMsgThread();
}

LVS_Socket_Server::~LVS_Socket_Server()
{
    if(LVS_NULL_PTR != pstSocketMsgList)
    {
        delete pstSocketMsgList;
        pstSocketMsgList = LVS_NULL_PTR;
    }
    if(LVS_NULL_PTR != handleParseMsg)
    {
        closeParseDownMsgThread(handleParseMsg);
        handleParseMsg = LVS_NULL_PTR;
    }
}

LVS_UINT32 LVS_Socket_Server::startProcess()
{
    
	//LVS_UINT32 ulRet;
    WORD wVersionRequested;
	WSADATA wsaData;
	int err;
    string stringPrintInfo;

	wVersionRequested = MAKEWORD(1,1);
	err = WSAStartup( wVersionRequested, &wsaData );//初始化套接字
	if ( err != 0 )
	{
        stringPrintInfo = "初始化套接字失败!";
        printString(stringPrintInfo, LVS_COLOR_LIGHTRED,0);
		return LVS_ERR;
	}
	if ( LOBYTE( wsaData.wVersion ) != 1 || HIBYTE( wsaData.wVersion ) != 1 )
	{
	#if 0
	    printTime();
        set_console_color(LVS_COLOR_LIGHTRED);
        cout<<"初始化套接字错误:"<<WSAGetLastError()<<endl;
        set_console_color(LVS_COLOR_WHITE);
    #endif
        stringPrintInfo ="初始化套接字错误:";
        stringPrintInfo.append(changeLongToString((long) WSAGetLastError()));
        printString(stringPrintInfo, LVS_COLOR_LIGHTRED,0);
		WSACleanup();
		return LVS_ERR;
	}
    #if 0
    printTime();
	printf("%d,%d\r\n",wsaData.iMaxUdpDg,wsaData.iMaxSockets);
    #endif
    stringPrintInfo = "初始化套接字成功:";
    stringPrintInfo.append(changeLongToString((long) wsaData.iMaxUdpDg));
    stringPrintInfo.append(",");
    stringPrintInfo.append(changeLongToString((long) wsaData.iMaxSockets));
    printString(stringPrintInfo, LVS_COLOR_WHITE,0);

    short port=SERVER_PORT;    //端口号
    SOCKET sockSrv=socket(AF_INET,SOCK_STREAM,0);//创建套接字

    if(INVALID_SOCKET == sockSrv)
	{
        stringPrintInfo ="创建套接字失败！";
        stringPrintInfo.append(changeLongToString((long) WSAGetLastError()));
        printString(stringPrintInfo, LVS_COLOR_LIGHTRED,0);
		WSACleanup();
		return LVS_ERR;
	}

    SOCKADDR_IN addrSrv;//用来和客户端通信的套接字地址
    memset(&addrSrv,0,sizeof(addrSrv));
	addrSrv.sin_addr.S_un.S_addr=htonl(INADDR_ANY);
	addrSrv.sin_family=AF_INET;
	addrSrv.sin_port=htons(port);

	//绑定端口
	if (bind(sockSrv,(SOCKADDR*)&addrSrv,sizeof(SOCKADDR)) == SOCKET_ERROR)
	{
        stringPrintInfo ="绑定端口失败！";
        stringPrintInfo.append(changeLongToString((long) WSAGetLastError()));
        printString(stringPrintInfo, LVS_COLOR_LIGHTRED,0);
		WSACleanup();
		return LVS_ERR;
	}

	//侦听
	if(listen(sockSrv,MAX_CLIENT_CONNECTION) == SOCKET_ERROR)
	{
        stringPrintInfo ="侦听失败！";
        stringPrintInfo.append(changeLongToString((long) WSAGetLastError()));
        printString(stringPrintInfo, LVS_COLOR_LIGHTRED,0);
		WSACleanup();
		return LVS_ERR;
	}

    stringPrintInfo = "Server ";
    stringPrintInfo.append(changeLongToString((long) port));
    stringPrintInfo.append(" is listening......");
    printString(stringPrintInfo, LVS_COLOR_WHITE,0);

    stringPrintInfo = "Starting Server...!";
    printString(stringPrintInfo, LVS_COLOR_WHITE,0);
	timeval timeout={0,0}; //select等待3秒，3秒轮询，要非阻塞就置0 
	int maxfdp = 0;
	int ret;
    int lprintNonConncetionFlag = 0;

    fd_set fdSocket;        // 侦听socket所在的集合
	FD_ZERO(&fdSocket);
	fd_set fdAllSocket;            //所有套接字集合
	FD_ZERO(&fdAllSocket);

    char readBuf[MAX_READ_BUFFER_SIZE];      //接收的请求数据
    char writeBuf[MAX_WRITE_BUFFER_SIZE];    //相应的报文数据
    memset(readBuf, 0, MAX_READ_BUFFER_SIZE);
    memset(writeBuf, 0, MAX_WRITE_BUFFER_SIZE);

    while(TRUE)
    {
        Sleep(3);
        FD_ZERO(&fdSocket);
		FD_SET(sockSrv, &fdSocket);

        ret = select((int)sockSrv + 1,&fdSocket,NULL,NULL,&timeout);
        if(0 > ret)
        {
            stringPrintInfo = "无连接->Failed select(),return value:";
            stringPrintInfo.append(changeLongToString((long) ret));   
            stringPrintInfo.append(",error:");
            stringPrintInfo.append(changeLongToString((long) WSAGetLastError()));  
            printString(stringPrintInfo, LVS_COLOR_RED,0);
            continue;
        }

        if(FD_ISSET(sockSrv,&fdSocket))
        {
            sockaddr_in addrRemote;
			int nAddrLen = sizeof(addrRemote);
			SOCKET sNew = accept(sockSrv, (SOCKADDR*)&addrRemote, &nAddrLen);
            if(INVALID_SOCKET == sNew)
            {

                stringPrintInfo = "LVS_Socket_Server::startProcess-> Failed accept(),return value:";
                stringPrintInfo.append(changeLongToString((long) sNew));
                stringPrintInfo.append(",error:");
                stringPrintInfo.append(changeLongToString((long) WSAGetLastError()));  
                printString(stringPrintInfo, LVS_COLOR_LIGHTRED,0);
            }
            else
            {

                stringPrintInfo = "Socket:";
                stringPrintInfo.append(changeLongToString((long) sNew));
                stringPrintInfo.append(",Accept connection from ");
                stringPrintInfo.append(inet_ntoa(addrRemote.sin_addr));
                stringPrintInfo.append(":");
                stringPrintInfo.append(changeLongToString((long) addrRemote.sin_port));
                printString(stringPrintInfo, LVS_COLOR_WHITE,0);
                
                if(MAX_CLIENT_CONNECTION < (int)fdAllSocket.fd_count)
                {
                #if 0
                    printTime();
                    set_console_color(LVS_COLOR_LIGHTRED);
                    cout<<"Too much connections!"<<endl;
                    set_console_color(LVS_COLOR_WHITE);
				#endif
                    stringPrintInfo = "Too much connections!";
                    printString(stringPrintInfo, LVS_COLOR_LIGHTRED,0);                     
                }
                else
                {
					(LVS_VOID)bindSocketIdToTelNo((LVS_INT32) sNew,addrRemote.sin_addr.s_addr);
                    FD_SET(sNew, &fdAllSocket);
                    if(maxfdp < ((int)sNew + 1))
                    {
                        maxfdp = (int)sNew + 1;
                    }
                }
            }
        }

        fd_set fdSocket_r = fdAllSocket;
		fd_set fdSocket_w = fdAllSocket;
        
        if( SOCKET_ERROR == select(maxfdp, &fdSocket_r, &fdSocket_w, NULL,&timeout))
        {
            if(0 == lprintNonConncetionFlag)
             {
                lprintNonConncetionFlag = 1;
                stringPrintInfo = "没有客户端连接-> Failed select(),return value,error:";
                stringPrintInfo.append(changeLongToString((long) WSAGetLastError()));  
                printString(stringPrintInfo, LVS_COLOR_RED,0);
             }
            continue;
        }
        lprintNonConncetionFlag = 0;
        /*获取请求数据*/
        for(int i = 0; i < (int)fdSocket_r.fd_count; i++)
        {
            int bytes;
            memset(readBuf, 0, MAX_READ_BUFFER_SIZE);
			bytes=recv(fdSocket_r.fd_array[i],readBuf,MAX_READ_BUFFER_SIZE - 1,0);
			if (0 < bytes)
			{
				readBuf[bytes] = '\0';

                stringPrintInfo = "Receive from Socket:";
                stringPrintInfo.append(changeLongToString((long) fdSocket_r.fd_array[i]));
                stringPrintInfo.append(" : ");
                stringPrintInfo.append(readBuf);
                printString(stringPrintInfo, LVS_COLOR_GREEN,1);
                /*此处将获取的请求消息存入响应的缓存区，使用JSON 解包，*/
                /*将该socket的存入消息体 */
                /* 发给相应的模块处理*/
                receiveServerMsg(readBuf, (LVS_INT32)fdSocket_r.fd_array[i]);

			}
			else if (0 == bytes)
			{

                stringPrintInfo = "Socket:";
                stringPrintInfo.append(changeLongToString((long) fdSocket_r.fd_array[i]));
                stringPrintInfo.append(" closed. 001");
                printString(stringPrintInfo, LVS_COLOR_LIGHTRED,0);
				(LVS_VOID)unbindSocketIdToTelNo((LVS_INT32)fdSocket_r.fd_array[i]);
				closesocket(fdSocket_r.fd_array[i]);
				FD_CLR(fdSocket_r.fd_array[i],&fdAllSocket);
				
			}
            else
            {

                stringPrintInfo = "Socket:";
                stringPrintInfo.append(changeLongToString((long) fdSocket_r.fd_array[i]));
                stringPrintInfo.append(" recv fail:.");
                stringPrintInfo.append(changeLongToString((long) bytes));
                stringPrintInfo.append(" error:");
                stringPrintInfo.append(changeLongToString((long) WSAGetLastError()));
                printString(stringPrintInfo, LVS_COLOR_LIGHTRED,0);

				(LVS_VOID)unbindSocketIdToTelNo((LVS_INT32)fdSocket_r.fd_array[i]);
                closesocket(fdSocket_r.fd_array[i]);
				FD_CLR(fdSocket_r.fd_array[i],&fdAllSocket);
				
            }
            
                
        }
        /*发送响应报文*/
        if(LVS_NULL_PTR == pstSocketMsgList)
        {

            stringPrintInfo = "响应消息队列未初始化!";
            printString(stringPrintInfo, LVS_COLOR_LIGHTRED,0);
            continue;
        }
        if(LVS_OK == pstSocketMsgList->LVSMsglistIsEmpty())
        {

            //stringPrintInfo = "响应消息队列为空!";
            //printString(stringPrintInfo, LVS_COLOR_RED);
            continue;
        }

        LVS_MSG_INFO_STRU *pstMsg;
        pstSocketMsgList->LVSMsglistDelete(&pstMsg);

        if(NULL == pstMsg->pMsgData)
        {
            stringPrintInfo = "The Response message is NULL";
            printString(stringPrintInfo, LVS_COLOR_RED,0);
            continue;
        }
        for(int i = 0; i < (int)fdSocket_w.fd_count; i++)
        {
            if((pstMsg->lSocketId == (LVS_INT32)fdSocket_w.fd_array[i]) || LVS_SEND_ALL == pstMsg->lSocketId)
            //if(LVS_TRUE)
            {
                /*将响应报文拷贝到writeBuf中*/
                
                memset(writeBuf, 0, MAX_WRITE_BUFFER_SIZE);
                //memcpy(writeBuf, "Head End", 8);
                //memcpy((LVS_VOID*)&writeBuf[8], (LVS_VOID*)&(pstMsg->lSocketId), sizeof(LVS_INT32) );
				//cout<<pstMsg->lSocketId<<endl;
				memcpy(writeBuf, pstMsg->pMsgData, pstMsg->ulMsgLen);
				//cout<<writeBuf<<endl;
				stringPrintInfo = "Send Response Message to Socket:";
                stringPrintInfo.append(changeLongToString((long) fdSocket_w.fd_array[i]));
                stringPrintInfo.append(" : ");
                stringPrintInfo.append(writeBuf);
                printString(stringPrintInfo, LVS_COLOR_BLUE,1);
                /*Begin 测试代码*/
                //LVS_UINT32 *pulTt = (LVS_UINT32*)pstMsg->pMsgData;
                //cout<<*pulTt<<endl;
                /*End*/
                if (send(fdSocket_w.fd_array[i],writeBuf,pstMsg->ulMsgLen + 1,0) < 0)
                {
                    stringPrintInfo = "Socket:";
                    stringPrintInfo.append(changeLongToString((long) fdSocket_r.fd_array[i]));
                    stringPrintInfo.append(" closed. 002");
                    printString(stringPrintInfo, LVS_COLOR_LIGHTRED,0);

					(LVS_VOID)unbindSocketIdToTelNo((LVS_INT32)fdSocket_w.fd_array[i]);
    				closesocket(fdSocket_w.fd_array[i]);
    				FD_CLR(fdSocket_w.fd_array[i],&fdAllSocket);
					
                }
                
            }
            
        }
        if(LVS_NULL_PTR != pstMsg->pMsgData)
        {
            free(pstMsg->pMsgData);
            pstMsg->pMsgData = LVS_NULL_PTR;
        }
        
    }
    closesocket(sockSrv);
    WSACleanup();
    #if 0
    printTime();
    cout<<"Close Socket Server!"<<endl;
    #endif
    stringPrintInfo = "Close Socket Server!";
    printString(stringPrintInfo, LVS_COLOR_WHITE,0);
    return LVS_OK;
}

LVS_UINT32 LVS_Socket_Server::sendRespMsg(LVS_MSG_INFO_STRU *pstMsg)
{
    LVS_UINT32 ulRet = LVS_OK;
    LVS_VOID *pMsgData = LVS_NULL_PTR;
    LVS_MSG_INFO_STRU stMsg;

    memset(&stMsg, 0, sizeof(stMsg));
    
    if(LVS_NULL_PTR == pstMsg)
    {
        //printf("The msg is valid\r\n");
        string stringPrintInfo = "The msg is valid!";
        printString(stringPrintInfo, LVS_COLOR_LIGHTRED,0);
        return LVS_ERR;
    }

    if(LVS_NULL_PTR == pstSocketMsgList)
    {
        string stringPrintInfo = "Socket response message list is not initialized!";
        printString(stringPrintInfo, LVS_COLOR_LIGHTRED,0);
        return LVS_ERR;
    }

    memcpy(&stMsg, pstMsg, LVS_MSG_HEADER_SIZE);
    
    if(0 < pstMsg->ulMsgLen)
    {
        pMsgData = (LVS_VOID*)malloc(pstMsg->ulMsgLen);
        if(LVS_NULL_PTR == pMsgData)
        {
            string stringPrintInfo = "LVS_Socket_Server::sendRespMsg malloc failed!";
            printString(stringPrintInfo, LVS_COLOR_LIGHTRED,0);
            return LVS_ERR;
        }
        
        memcpy(pMsgData, pstMsg->pMsgData, pstMsg->ulMsgLen);
        stMsg.pMsgData = pMsgData;
    }
    
    ulRet= pstSocketMsgList->LVSMsglistlnsert(&stMsg);
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

LVS_UINT32 LVS_SendRespMsg(LVS_MSG_INFO_STRU *pstMsg)
{
    if(NULL == g_pServer)
    {
    #if 0
        printTime();
        set_console_color(LVS_COLOR_LIGHTRED);
        cout<<"g_pServer is null"<<endl;
        set_console_color(LVS_COLOR_WHITE);
    #endif
        string stringPrintInfo = "LVS_SendRespMsg->g_pServer is null";
        printString(stringPrintInfo, LVS_COLOR_LIGHTRED,0);
        return LVS_ERR;
    }
    return g_pServer->sendRespMsg(pstMsg);
}

LVS_UINT32 InitSocketServer()
{
    g_pServer = new LVS_Socket_Server();
    g_pServer->startProcess();

    return LVS_OK;
}


