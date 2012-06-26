#pragma once

#ifndef _LVS_LOG_H
#define _LVS_LOG_H

#include "LVS_define.h"

LVS_UINT32 startRecordLogInfo();
LVS_UINT32 writeInfoToLogBuff(string strInfo);
char* U2G(const char* utf8);
char* G2U(const char* gb2312);

#endif