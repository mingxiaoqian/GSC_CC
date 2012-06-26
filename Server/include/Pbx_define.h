#pragma once

#include "LVS_define.h"
#include <string>


///////////////////////////////////////////////
//*******		 CONST DEFINITION		***************
///////////////////////////////////////////////
#define CHTYPE_TRUNK		0			//Analog trunk channel
#define CHTYPE_USER			2			//Station channel

#define MAX_CHLIST_ITEM		6			//Maximum column of the list control
#define MAX_CH				400			//Maximum channel

#define MAX_USER_DTMFLEN	4			//Maximum length of the DTMF
#define NUM_LENGTH			20			//Telephone number length


///////////////////////////////////////////////
//*******		STRUCTURE DEFINITION		***************
///////////////////////////////////////////////
enum PBX_MESSAGE_TYPE
{
	PBX_MSG_TYPE_DRIVE,        //驱动事件消息
	PBX_MSG_TYPE_USER,         //用户自定义消息
	PBX_MSG_TYPE_BUTT,
};
enum APP_USER_STATUS			//User-defined station channel state
{
	USER_IDLE,					//Station channel idle
	USER_LOCAL_RING,			//Station channel ringing
	USER_GET_1STDTMF,			//Press the first DTMF digit on the station channel to select the called party
	USER_GET_DTMF,				//The station channel judges if the extension number is legal
	USER_REQ_USER,				//The station channel is waiting for a result to see if the extension has been used
	USER_RING_BACK,				//The station channel is waiting for the extension to pick up the call
	USER_REQ_TRUNK,				//The station channel is waiting for a result to see if a trunk channel is used for call connection
	USER_DIALOUT,				//The station channel dials the trunk channel
	USER_WAIT_REMOTE_PICKUP,	//The station channel is waiting for the trunk channel to pick up the call
	USER_TALKING,				//The station channel is talking with the extension
	USER_WAIT_HANGUP,			//The station channel is waiting to hang up the call
	USER_F_GET_DTMF,			//The station channel judges if the extension number is legal during a call transfer.
	USER_F_REQ_USER,			//The station channel is waiting for the result of a call transfer
	USER_F_RING_BACK,			//The station channel is waiting for the target extension to which the call is transferred to pick up the call
	USER_F_TALKING,				//The station channel is talking with the target extension to which the call is transferred
	USER_F_OPERATE,				//
	USER_F_WAIT_TALK,			//The previously connected station channel is waiting for the connection with the target extension to which the call is transferred
	TRUNK_IDLE,					//Trunk channel idle
	TRUNK_WAIT_1STNUM,			//The trunk channel is waiting to dial
	TRUNK_DIALING,				//The trunk channel is dialing
	TRUNK_WAIT_REMOTE_PICKUP,	//The trunk channel is waiting for the remote end to pick up the call
	TRUNK_WAIT_ACTUAL_PICKUP,	//The trunk channel rings, picks up the call and waits for the call connection
	TRUNK_WAIT_SELECTION,		//The trunk channel judges if the number is compliant with the numbering rule when it is calling the station channel
	TRUNK_REQ_USER,				//The trunk channel requests a station channel for call connection
	TRUNK_RING_BACK,			//The trunk channel is waiting for the station channel to pick up the call
	TRUNK_CONNECTED,			//The trunk channel is connected
	TRUNK_FLASHING,				//The trunk channel is waiting for the connection with the target extension to which the call is transferred
};

enum
{
	E_US_SEIZURE = 0x0100,			//Sends a usage request to the extension
	E_US_RELEASE,					//Sends a release event to the station channel
	E_US_SEIZURE_ACK_IDLE,			//Answers that the station channel is idle
	E_US_SEIZURE_ACK_BUSY,			//Answers that the station channel is busy
	E_US_PICKUP,					//Sends an off-hook event to the calling party 
	E_US_SEIZURE_TK,				//Sends a usage request to the analog channel
	E_TK_SEIZURE_TK_ACK_IDLE,		//Answers that the analog channel is idle
	E_TK_SEIZURE_TK_ACK_BUSY,		//Answers that the analog channel is busy
	E_TK_RELEASE,					//Sends a release event to the trunk channel
	E_US_DTMF2TK,					//Sends DTMF digits to the trunk channel
	E_TK_DIAL_OK,					//The trunk channel is successful to dial
	E_TK_DIAL_FAIL,					//The trunk channel is failed to dial
	E_TK_REMOTE_NOANSWER,			//No answer from the remote end that the trunk channel is calling
	E_TK_REMOTE_PICKUP,				//The remote end that the trunk channel is calling picks up the call
	E_MSG_RELEASE,					//Sends a release event to the connected party
	E_MSG_FLASH,					//A flash event
	E_MSG_CONNECT,					//A connect event
	E_MSG_HANGUP,					//During a call transfer, the previously connected party hangs up the call and sends this event to the target party to which the call is transferred
	F_US_SEIZURE,					//Sends a request event to the station channel during a flash
};

typedef struct tagCH_INFO
{
	int nChType;					//Channel Type: 0,2	 ---Analog channel, Station channel
	int	nLinkToCh;					//The number of the target channel to be linked
	int nSaveSubmiteCh;				//The number of the channel where the previously connected party lies
	int nTimer;						//Timer ID
	char szPhoneNumBuf[NUM_LENGTH];	//The buffer storing phone numbers
	string CUserNum;				//The station channel number
	int nPhoNumLen;					//The length of the phone number, i.e. a flag which tells if it is necessary to append numbers
	int nIndex;						//Index value list
	BOOL bPressFlag;				//A hook switch flag (TRUE: Pressed; FALSE: Not pressed)
	BOOL bSubmiteChHookFlag;		//A flag used to judge if the previously connected party has hung up the phone (TRUE: On-hook; FALSE: Off-hook)
	char szCallerId[NUM_LENGTH];	//Stores the calling party number
	char szCalleeId[NUM_LENGTH];	//Stores the called party number
	APP_USER_STATUS nStatus;		//A channel state value, which is a flag to control the program flow
}CH_INFO;

typedef	struct tagLIST_PARA
{
	int ColumnWidth;
	char szText[100];
}LIST_PARA, *PLIST_PARA;

enum					//Index value list
{
	ITEM_Ch,
	ITEM_ChType,
	ITEM_ChState,
	ITEM_CallerId,
	ITEM_CalleeId,
	ITEM_RxDTMF,
};

typedef struct tagPARA_INFO
{
	LVS_INT32 wParam;
	LVS_INT32 lParam; 
	LVS_INT32 dwUser;
}PARA_INFO;

