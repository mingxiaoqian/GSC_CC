#include <iostream>
#include <fstream>
#include <sstream>
#include <process.h>
#include <io.h>
#include <direct.h>
#include "LVS_define.h"
#include "LVS_log.h"

#define LOG_FILE_PATH ".\\log\\"

#define MAX_ONE_FILE_LOG_RECORD_NUMBER 10000

LVS_UINT32 m_ulLogBufferLock = 0;
stringstream m_LogInfoStringBuffer;

HANDLE m_recordLogThreadhandle = LVS_NULL_PTR;
LVS_UINT32 m_ulRecordNum = 0;
LVS_UINT32 m_ulRecordBuffLock = 0;

char* U2G(const char* utf8)
{
    int len = MultiByteToWideChar(CP_UTF8, 0, utf8, -1, NULL, 0);
    wchar_t* wstr = new wchar_t[len+1];
    memset(wstr, 0, len+1);
    MultiByteToWideChar(CP_UTF8, 0, utf8, -1, wstr, len);
    len = WideCharToMultiByte(CP_ACP, 0, wstr, -1, NULL, 0, NULL, NULL);
    char* str = new char[len+1];
    memset(str, 0, len+1);
    WideCharToMultiByte(CP_ACP, 0, wstr, -1, str, len, NULL, NULL);
    if(wstr) delete[] wstr;
    return str;
}

//GB2312µ½UTF-8µÄ×ª»»
char* G2U(const char* gb2312)
{
    int len = MultiByteToWideChar(CP_ACP, 0, gb2312, -1, NULL, 0);
    wchar_t* wstr = new wchar_t[len+1];
    memset(wstr, 0, len+1);
    MultiByteToWideChar(CP_ACP, 0, gb2312, -1, wstr, len);
    len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
    char* str = new char[len+1];
    memset(str, 0, len+1);
    WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, NULL, NULL);
    if(wstr) delete[] wstr;
    return str;
}

string getCurrentTimeNumberAsString()
{
    SYSTEMTIME systime;
    GetLocalTime( &systime ); 
    string strTime = "";
    strTime.append(changeLongToString((long) systime.wYear));
    if(10 > systime.wMonth)
    {
        strTime.append("0");
    }
    strTime.append(changeLongToString((long) systime.wMonth));
    if(10 > systime.wDay)
    {
        strTime.append("0");
    }
    strTime.append(changeLongToString((long) systime.wDay));
    if(10 > systime.wHour)
    {
        strTime.append("0");
    }
    strTime.append(changeLongToString((long) systime.wHour));
    if(10 > systime.wMinute)
    {
        strTime.append("0");
    }
    strTime.append(changeLongToString((long) systime.wMinute));
    if(10 > systime.wSecond)
    {
        strTime.append("0");
    }
    strTime.append(changeLongToString((long) systime.wSecond));
    return strTime;
}

static unsigned __stdcall writeLogInfoToFile(void *p)
{
    if ( access( LOG_FILE_PATH, 0 ) == -1 )
    {
        //cout<<"Path is not exist."<<endl;
        if (_mkdir(LOG_FILE_PATH) == 0)
        {
            //cout<<"Creat dir succeed."<<endl;
        }
    }
    else
    {
        //cout<<"Path is exist."<<endl;
    }

    ofstream ofs;
    string filename;
    while(LVS_TRUE)
    {
        filename.clear();
        filename.append(LOG_FILE_PATH);
        filename.append("log_");
        filename.append(getCurrentTimeNumberAsString());
        filename.append(".log");
        
        ofs.open(filename.c_str(),ios::app);

        //printf("Open %s\r\n",filename.c_str());
        if(!ofs)
        {
            printString(filename,LVS_COLOR_YELLOW,0);
            Sleep(1000);
            continue;
        }
        //printf("Open succeed %s\r\n",filename.c_str());

        LVS_UINT32 ulLogRecordNum = 0;

        while(LVS_TRUE)
        {            
            if(0 == m_ulRecordNum)
            {
                Sleep(1);
                continue;
            }

            string strTemp;
            //m_LogInfoStringBuffer>>strTemp;
            while(0 != m_ulRecordBuffLock)
            {
                Sleep(1);
            }
            m_ulRecordBuffLock = 1;
			m_LogInfoStringBuffer.ignore();
            getline(m_LogInfoStringBuffer, strTemp);

            //printf("C: %d\r\n",ulLogRecordNum);

            if(0 < strTemp.length())
            {
                ofs<<strTemp<<endl;
                ulLogRecordNum++;

                m_ulRecordNum--;
				//printf("%d\r\n",m_LogInfoStringBuffer.str().length());
                
                if(0 == m_ulRecordNum)
                {
                    m_LogInfoStringBuffer.clear();
                    m_LogInfoStringBuffer.str("");
                }
                
                //printf("D: %d\r\n",ulLogRecordNum);
            }
            m_ulRecordBuffLock = 0;
            //cout<<"B:"<<ulLogRecordNum<<endl;
            if(ulLogRecordNum >= MAX_ONE_FILE_LOG_RECORD_NUMBER)
            {
                break;
            }
            
        }
        ofs.close();
        //printf("Close %s\r\n",filename.c_str());
        
    }
}

LVS_UINT32 startRecordLogInfo()
{
    LVS_UINT32 ulThreadID;
    m_recordLogThreadhandle = (HANDLE)_beginthreadex(NULL,
                                                   0,
                                                   writeLogInfoToFile,
                                                   NULL,
                                                   0,
                                                   (PBEGINTHREADEX_THREADID)&ulThreadID);
    
    return LVS_OK;
}

LVS_UINT32 writeInfoToLogBuff(string strInfo)
{
    if(LVS_NULL_PTR == m_recordLogThreadhandle)
    {
        return LVS_ERR;
    }
    while(0 != m_ulRecordBuffLock)
    {
        Sleep(1);
    }
    m_ulRecordBuffLock = 1;
            
    m_LogInfoStringBuffer<<strInfo<<endl;

    m_ulRecordNum++;
    m_ulRecordBuffLock = 0;
    //cout<<"A:"<<m_ulRecordNum<<endl;
    
    return LVS_OK;
}
