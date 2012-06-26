#include <sstream>
#include <process.h>
#include "LVS_define.h"
#include "LVS_log.h"

using namespace std;

#define PRINT_SWITCH_ON "9527"
#define PRINT_SWITCH_OFF "250"

LVS_UINT32 m_ulPrintStringLock = 0;
LVS_UINT32 m_ulPrintSwitch = 0;

string getCurrentTimeAsString()
{
    SYSTEMTIME systime;
    GetLocalTime( &systime ); 
    string strTime = "";
    strTime.append(changeLongToString((long) systime.wYear));
    strTime.append("/");
    if(10 > systime.wMonth)
    {
        strTime.append("0");
    }
    strTime.append(changeLongToString((long) systime.wMonth));
    strTime.append("/");
    if(10 > systime.wDay)
    {
        strTime.append("0");
    }
    strTime.append(changeLongToString((long) systime.wDay));
    strTime.append(" ");
    if(10 > systime.wHour)
    {
        strTime.append("0");
    }
    strTime.append(changeLongToString((long) systime.wHour));
    strTime.append(":");
    if(10 > systime.wMinute)
    {
        strTime.append("0");
    }
    strTime.append(changeLongToString((long) systime.wMinute));
    strTime.append(":");
    if(10 > systime.wSecond)
    {
        strTime.append("0");
    }
    strTime.append(changeLongToString((long) systime.wSecond));
    return strTime;
}

void printTime()
{
    cout<<getCurrentTimeAsString()<<" ";
    return;
}


/*sIsUTF8 为LVS_TRUE 时，表明传进来的字符串是UTF8 编码的*/
void printString(string str, unsigned short color_index, unsigned short sIsUTF8)
{
    char *pch_GBK = NULL;
    
    while(0 < m_ulPrintStringLock)
    {
        Sleep(1);
    }
    
    m_ulPrintStringLock = 1;

    if(m_ulPrintSwitch > 0 || LVS_COLOR_LIGHTRED == color_index)
    {
        set_console_color(LVS_COLOR_WHITE);
        printTime();
        set_console_color(color_index);

        if(LVS_TRUE == sIsUTF8)
        {
            
            pch_GBK = U2G(str.c_str());
            printf("%s\r\n",pch_GBK);
            if(NULL != pch_GBK)
            {
                delete[] pch_GBK;
                pch_GBK = NULL;
            }
        }
        else
        {
            printf("%s\r\n",str.c_str());
        }
        
        set_console_color(LVS_COLOR_WHITE);
    }

    
    string strLogInfo = "";
    strLogInfo.append(getCurrentTimeAsString());
    strLogInfo.append(" ");
    if(LVS_COLOR_LIGHTRED == color_index)
    {
        strLogInfo.append("[Error:]");
    }
    if(LVS_TRUE == sIsUTF8)
    {
        pch_GBK = U2G(str.c_str());
        strLogInfo.append(pch_GBK);
        if(NULL != pch_GBK)
        {
            delete[] pch_GBK;
            pch_GBK = NULL;
        }
    }
    else
    {
        strLogInfo.append(str);
    }
    (LVS_VOID)writeInfoToLogBuff(strLogInfo);
    m_ulPrintStringLock = 0;
    
}

string changeLongToString(long iValue)
{
    stringstream intTostr;
    string tmpStr;

    intTostr << iValue;
    intTostr >> tmpStr;

    return tmpStr;
}

LVS_UINT32 changeStringToUlong(string str)
{
	stringstream strToInt;
	LVS_UINT32 tmp;

	strToInt<<str;
	strToInt>>tmp;

	return tmp;
}

static unsigned __stdcall controlPrintSwitch(void *p)
{
    string strSwitchKey;
    while(cin>>strSwitchKey)
    {
        //cout<<strSwitchKey<<endl;
        if(string::npos != strSwitchKey.find(PRINT_SWITCH_ON))
        {
            m_ulPrintSwitch = 1;
            continue;
        }
        if(string::npos != strSwitchKey.find(PRINT_SWITCH_OFF))
        {
            m_ulPrintSwitch = 0;
            continue;
        }
    }

    return 0;
}

int getThePrintSwitchKey()
{
    HANDLE handle;
    LVS_UINT32 ulThreadID;
    handle = (HANDLE)_beginthreadex(NULL,
                                   0,
                                   controlPrintSwitch,
                                   NULL,
                                   0,
                                   (PBEGINTHREADEX_THREADID)&ulThreadID);

    if(NULL == handle)
    {
        printString("getThePrintSwitchKey Failed!",LVS_COLOR_LIGHTRED,0);
        return 1;
    }
    return 0;
}

string allTrim(string strIpt)
{
	stringstream ss;
	string strOpt;
	const char *pch = strIpt.c_str();
	for(LVS_UINT32 i = 0; i < strIpt.length(); i++)
	{
		char ch = *(pch + i);
		if(' ' != ch)
		{
			ss<<ch;
		}
	}
	ss>>strOpt;
	return strOpt;
}
