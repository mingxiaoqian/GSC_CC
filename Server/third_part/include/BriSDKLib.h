#ifndef __BRISDKLIB_H__
#define __BRISDKLIB_H__

//---------------------------------------------------------
//USB/CC�豸�����ӿںͲ���˵��
//---------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif

#ifndef WIN32
#define BRISDKLIBAPI
#else
#define BRISDKLIBAPI	WINAPI
#endif

//2009/10/10
//#define		QNV_DLL_VER						0x0101
//#define		QNV_DLL_VER_STR					"1.01"
//2010/01/08
//#define		QNV_DLL_VER						0x0102
//#define		QNV_DLL_VER_STR					"1.02"
//2010/02/04 ����c/s socketԶ��ͨ�Žӿ�
//#define		QNV_DLL_VER						0x0103
//#define		QNV_DLL_VER_STR					"1.03"

//2010/03/05
//#define		QNV_DLL_VER						0x0104
//#define		QNV_DLL_VER_STR					"1.04"

//2010/09/20
//#define		QNV_DLL_VER						0x0105
//#define		QNV_DLL_VER_STR					"1.05"

//2010/10/29
//#define		QNV_DLL_VER							0x0106
//#define		QNV_DLL_VER_STR						"1.06"

//2011/04/18
#define		QNV_DLL_VER							0x0201
#define		QNV_DLL_VER_STR						"2.01"

#define		QNV_CC_LICENSE						"quniccub_x"	

//---------------------------------------------
typedef  __int64			BRIINT64;//���� 64bit(8�ֽ�)
typedef  __int32			BRIINT32;//���� 32bit(4�ֽ�)
typedef  unsigned __int32   BRIUINT32;//�޷��� 32bit(4�ֽ�)
typedef	 __int16			BRIINT16;//���� 16bit(2�ֽ�)
typedef	 unsigned __int16	BRIUINT16;//���� 16bit(2�ֽ�)
typedef	 unsigned char		BRIBYTE8;//�޷��� 8bit(1�ֽ�)
typedef  char				BRICHAR8;//���� 8bit(1�ֽ�)
typedef  char*				BRIPCHAR8;//�ַ���ָ��(ANSI)
typedef  short*				BRIPSHORT16;//�ַ���ָ��(UNICODE)
//---------------------------------------------

//����/¼���ص�ʱ������ظ�ֵ��ϵͳ���Զ�ɾ���ûص�ģ�飬�´ν����ᱻ�ص�
#define		CB_REMOVELIST						(-1)

//����ļ������б�ָ����
#define		MULTI_SEPA_CHAR						'|'
//�������
#define		PROXYDIAL_SIGN						0x40000000
//�������
#define		PROXYDIAL_SIGN_STRU					'P'
//�������
#define		PROXYDIAL_SIGN_STRL					'p'

#define		RING_BEGIN_SIGN_STR					"0"
#define		RING_END_SIGN_STR					"1"
#define		RING_BEGIN_SIGN_CH					'0'
#define		RING_END_SIGN_CH					'1'

#define		RINGBACK_TELDIAL_STR				"0"
#define		RINGBACK_PCDIAL_STR					"1"
#define		RINGBACK_PCDIAL_CH					'1'
#define		RINGBACK_TELDIAL_CH					'0'

//Ĭ���Ĳ�ɼ��ʱ��(ms)
#define		DEFAULT_FLASH_ELAPSE				600
//Ĭ���Ĳ�ɺ���һ��ʱ��ص��¼�ms
#define		DEFAULT_FLASHEND_ELAPSE				1000
//Ĭ�ϸ��ڲ�����/����������ʱ��ms�� 1��
#define		DEFAULT_RING_ELAPSE					1000
//Ĭ�ϸ��ڲ�����/�����������ֹͣms 4��
#define		DEFAULT_RINGSILENCE_ELAPSE			4000
//Ĭ�ϸ��������峬ʱ����,ÿ��1����4��ͣ,�ܹ�ʱ���ΪN*5��
#define		DEFAULT_RING_TIMEOUT				12
//�ܽ�ʱĬ��ʹ�ü��(ms)
#define		DEFAULT_REFUSE_ELAPSE				500
//Ĭ�ϲ����ٶ�(ms)
#define		DEFAULT_DIAL_SPEED					100
//Ĭ�Ϻ���֮�侲��ʱ��(ms)
#define		DEFAULT_DIAL_SILENCE				100
//��Ⲧ������ʱ��ǿ�ƺ���(ms)
#define		DEFAULT_CHECKDIALTONE_TIMEOUT		3000
//�������峬ʱms
#define		DEFAULT_CALLINTIMEOUT				5500

//����ʱ����֮���ӳ�1��
#define		DIAL_DELAY_SECOND					','
//����ʱ����֮���ӳ�0.5��
#define		DIAL_DELAY_HSECOND					'.'
//����ʱ�÷��ź��Զ����˳�������
#define		DIAL_CHECK_CITYCODE					':'

//CC�����ķָ�����
#define		CC_PARAM_SPLIT						','
//α����ִ��ʱ�ķָ�����
#define		EXEC_CMD_CHAR						' '

//�Զ�����¼���ļ�ʱ��Ĭ��Ŀ¼��
#define		RECFILE_DIR							"recfile"
//������Ϣ���KEY
#define		INI_QNVICC							"qnvicc"
//Ĭ�������ļ���
#define		INI_FILENAME						"cc301config.ini"
//VOIP�������
#define		CC_VOIP_SIGN						"VOIP"
//������½CC,���������Ϊ��ͬ
#define		WEB_802ID							"800002000000000000"

//֧�ֵ����USBоƬ��
#define		MAX_USB_COUNT						64
//֧�ֵ����USBͨ����
#define		MAX_CHANNEL_COUNT					128

//����������Чͨ��ID��
//0->255ΪUSB�豸ͨ����
#define		SOUND_CHANNELID						(BRIINT16)256
//Զ��httpͨ��ͨ��,HTTP�ϴ�/����
#define		REMOTE_CHANNELID					(BRIINT16)257
//CC����ͨ��
#define		CCCTRL_CHANNELID					(BRIINT16)258
//socket ��������ͨ��
#define		SOCKET_SERVER_CHANNELID				(BRIINT16)259
//socket �ն�ͨ��
#define		SOCKET_CLIENT_CHANNELID				(BRIINT16)260
//UDPͨ��
#define		SOCKET_UDP_CHANNELID				(BRIINT16)261
//ICC301����������������
#define		AUDRV_CHANNELID						(BRIINT16)262

//����CC��Ϣ����󳤶�
#define		MAX_CCMSG_LEN						400
//����CC�������󳤶�
#define		MAX_CCCMD_LEN						400
//�洢ģ��һ������ȡ�ĳ���
#define		MAX_STORAGE_LEN						1024

//ͨ������
#define		CHANNELTYPE_PHONE					0x1//phoneģ��
#define		CHANNELTYPE_LINE					0x2//lineģ��

//�豸����
#define		DEVTYPE_UNKNOW						-1//δ֪�豸
//�ڲ�ʹ��ϵ��
#define		DEVTYPE_T2F							0x100c
#define		DEVTYPE_TC2_R						0x1007
//
//cc301ϵ��
#define		DEVTYPE_T1							0x1009
#define		DEVTYPE_T2							0x1000
#define		DEVTYPE_T3							0x1008
#define		DEVTYPE_T4							0x1005
#define		DEVTYPE_T5							0x1001
#define		DEVTYPE_T6							0x1004

//8-Iϵ��/1-��·/0-Rϵ��/1-Aϵ�е�1��
#define		DEVTYPE_IR1							0x8100
#define		DEVTYPE_ID1							0x8102
//8-Iϵ��/1-��·/1-Aϵ��/1-Aϵ�е�1��
#define		DEVTYPE_IA1							0x8111
#define		DEVTYPE_IA2							0x8112
#define		DEVTYPE_IA3							0x8113
#define		DEVTYPE_IA4							0x8114
#define		DEVTYPE_IA4_F						0x8115
//8-Iϵ��/1-��·/2-Bϵ��/1-Aϵ�е�1��
#define		DEVTYPE_IB1							0x8121
#define		DEVTYPE_IB2							0x8122
#define		DEVTYPE_IB3							0x8123
#define		DEVTYPE_IB4							0x8124
//8-Iϵ��/1-��·/3-Pϵ��/1-Aϵ�е�1��
#define		DEVTYPE_IP1							0x8131
#define		DEVTYPE_IP1_F						0x8132
//2·�豸
#define		DEVTYPE_IC2_R						0x8200
#define		DEVTYPE_IC2_LP						0x8203
#define		DEVTYPE_IC2_LPQ						0x8207
#define		DEVTYPE_IC2_LPF						0x8211
//4·�豸
#define		DEVTYPE_IC4_R						0x8400
#define		DEVTYPE_IC4_LP						0x8403
#define		DEVTYPE_IC4_LPQ						0x8407
#define		DEVTYPE_IC4_LPF						0x8411
//7·�豸
#define		DEVTYPE_IC7_R						0x8700
#define		DEVTYPE_IC7_LP						0x8703
#define		DEVTYPE_IC7_LPQ						0x8707
#define		DEVTYPE_IC7_LPF						0x8711

#define		DEVTYPE_Z2							0x9001//OEMоƬ������
#define		DEVTYPE_K1							0x9101//����

//������
#define		DEVTYPE_A1							0x1100000
#define		DEVTYPE_A2							0x1200000
#define		DEVTYPE_A3							0x1300000
#define		DEVTYPE_A4							0x1400000
#define		DEVTYPE_B1							0x2100000
#define		DEVTYPE_B2							0x2200000
#define		DEVTYPE_B3							0x2300000
#define		DEVTYPE_B4							0x2400000
#define 	DEVTYPE_C4_L						0x3100000
#define 	DEVTYPE_C4_P						0x3200000
#define 	DEVTYPE_C4_LP						0x3300000
#define 	DEVTYPE_C4_LPQ						0x3400000
#define		DEVTYPE_C7_L						0x3500000	
#define		DEVTYPE_C7_P						0x3600000
#define		DEVTYPE_C7_LP						0x3700000
#define		DEVTYPE_C7_LPQ						0x3800000
#define		DEVTYPE_R1							0x4100000
#define		DEVTYPE_C4_R						0x4200000
#define		DEVTYPE_C7_R						0x4300000
//
//--------------------------------------------------------------
//�豸����ģ�鶨��
//�Ƿ�����������ȹ���
//����PC��������������/ͨ��ʱ��·����������
#define		DEVMODULE_DOPLAY					0x1
//�Ƿ���пɽ������߻�ȡ�������(FSK/DTMF˫��ʽ)/ͨ��¼������
//�������絯��/ͨ��¼��/ͨ��ʱ��ȡ�Է�����(DTMF)
#define		DEVMODULE_CALLID					0x2
//�Ƿ���пɽ��뻰������PSTNͨ������
//����ʹ�õ绰������PSTNͨ��/��ȡ���������ĺ���
#define		DEVMODULE_PHONE						0x4
//�Ƿ���м̵����л��Ͽ�/��ͨ��������
//�Ͽ����������:����ʱ����������/ʹ�û���MIC�����ɼ�¼��,�������DEVFUNC_RINGģ�������ģ����������
#define		DEVMODULE_SWITCH					0x8
//PC����������������Ͳ,���� DEVMODULE_SWITCHģ��,switch�󲥷�������������Ͳ
#define		DEVMODULE_PLAY2TEL					0x10
//�Ƿ����PCժ���󲦺�/��������·�Ĺ���
//����ʹ��PC�Զ�ժ�����в���/ͨ��ʱ���Ը��Է���������/��������/�Ⲧ֪ͨ/����IVR(������¼)
#define		DEVMODULE_HOOK						0x20
//�Ƿ���в���MIC/��������
//������MIC/��������PSTNͨ��/ʹ��MIC����¼��/PC��������������
#define		DEVMODULE_MICSPK					0x40
//�Ƿ�����ý���phone�ڵ��豸(�绰��,��������)ģ�����幦��
//��������ʱ����phone�ڵ��豸ģ����������.��:������IVR(������¼)֮����빤����ʱ���ڲ������򽻻���ģ������
#define		DEVMODULE_RING						0x80
//�Ƿ���н���/���ʹ��湦��
//���Է���ͼƬ,�ĵ����Է��Ĵ����/���Խ��ձ���Է���������͹�����ͼƬ
#define		DEVMODULE_FAX						0x100
//�Ƿ���д洢����
#define		DEVMODULE_STORAGE					0x200
//���м��Է�ת���Է�ժ���Ĺ���
//���PSTN��·�ڵ��ص��Ų���ͬʱ��ͨ�ü��Է�ת������,�Ϳ������Ⲧʱ��ȷ��⵽�Է�ժ��/�һ�
//���û�иù���,ֻ�в���ĺ�����б�׼����Ų��ܼ�⵽�Է�ժ��,���ֻ�����,IP�Ȳ����б�׼������·�Ĳ��ܼ��Է�ժ��/�һ�
#define		DEVMODULE_POLARITY					0x800
//----------------------------------------------------------------


//�����û��Զ������
//����tool�û���������д���ļ�
#define		SUD_WRITEFILE						0x1
//����
#define		SUD_ENCRYPT							0x2
//�ͷ���Դ,�´ζ�д��ʱ���¶�ȡ�ļ�
#define		SUD_UNLOAD							0x4
//

//���豸����
#define		ODT_LBRIDGE							0x0//CC301�豸
#define		ODT_SOUND							0x1//����
#define		ODT_CC								0x2//CCģ��
#define		ODT_SOCKET_CLIENT					0x4//SOCKET�ն�ģ��
#define		ODT_SOCKET_SERVER					0x8//SOCKET������ģ��
#define		ODT_SOCKET_UDP						0x10//UDPģ��
#define		ODT_AUDRV							0x20//��������ģ��
#define		ODT_ALL								0xFF//ȫ������
#define		ODT_CHANNEL							0x100//�ر�ָ��CC301ͨ��
//

//-----------------------------------------------------
//linein��·ѡ��
#define		LINEIN_ID_1							0x0//�绰���Ͽ��󻰱�¼��
#define		LINEIN_ID_2							0x1//Ĭ������״̬¼�����ɼ���������
#define		LINEIN_ID_3							0x2//hook line ��ժ����¼��,¼�����ݿ�����߶Է�������,���ͱ�������
#define		LINEIN_ID_LOOP						0x3//�ڲ���·����,�豸����ʹ��,�����û�����Ҫʹ��
//-----------------------------------------------------

#define		ADCIN_ID_MIC						0x0//mic¼��
#define		ADCIN_ID_LINE						0x1//�绰��¼��

//adc
//оƬ��2��ͨ���ĵ绰�ߵ�����������
#define		DOPLAY_CHANNEL1_ADC					0x0
//оƬ��1��ͨ���ĵ绰�ߵ�����������
#define		DOPLAY_CHANNEL0_ADC					0x1
//��оƬ��1��ͨ�����ŵ�����������
#define		DOPLAY_CHANNEL0_DAC					0x2
//��оƬ��2��ͨ�����ŵ�����������
#define		DOPLAY_CHANNEL1_DAC					0x3

//------------
#define		SOFT_FLASH							0x1//ʹ����������Ĳ����
#define		TEL_FLASH							0x2//ʹ�û����Ĳ����
//------------

#define		HOOK_VOICE							0x0//��������ժ�һ��ź�
#define		HOOK_POLARITY						0x1//��������ժ�һ��ź�
//�ܽ�ʱʹ��ģʽ
#define		REFUSE_ASYN							0x0//�첽ģʽ,���ú����������أ���������ʾ�ܽ���ɣ��ܽ���ɺ󽫽��յ�һ���ܽ���ɵ��¼�
#define		REFUSE_SYN							0x1//ͬ��ģʽ,���ú�ú������������ȴ��ܽ���ɷ��أ�ϵͳ�����оܽ���ɵ��¼�

//�Ĳ������
#define		FT_NULL								0x0
#define		FT_TEL								0x1//�����Ĳ��
#define		FT_PC								0x2//���Ĳ��
#define		FT_ALL								(FT_TEL|FT_PC)
//-------------------------------

//��������
#define		DTT_DIAL							0x0//����
#define		DTT_SEND							0x1//���η���/���巢��CALLID
//-------------------------------

//�������ģʽ
#define		CALLIDMODE_NULL						0x0//δ֪
#define		CALLIDMODE_FSK						0x1//FSK����
#define		CALLIDMODE_DTMF						0x2//DTMF����
//

//��������
#define		CTT_NULL							0x0
#define		CTT_MOBILE							0x1//�ƶ�����
#define		CTT_PSTN							0x2//��ͨ�̻�����
//------------------------------

#define		CALLT_NULL							0x0//
#define		CALLT_CALLIN						0x1//����
#define		CALLT_CALLOUT						0x2//ȥ��
//-------------------

#define		CRESULT_NULL						0x0
#define		CRESULT_MISSED						0x1//����δ��
#define		CRESULT_REFUSE						0x2//����ܽ�
#define		CRESULT_RINGBACK					0x3//���к������
#define		CRESULT_CONNECTED					0x4//��ͨ
//-------------------------------

#define		OPTYPE_NULL							0x0
//�ϴ��ɹ���ɾ�������ļ�
#define		OPTYPE_REMOVE						0x1
//���ر�����ʱ��¼,�ɹ���ɾ��,���û�ɹ����Ժ�������´�
#define		OPTYPE_SAVE							0x2

//�豸����ID
#define		DERR_READERR						0x0//��ȡ���ݴ���
#define		DERR_WRITEERR						0x1//д�����ݴ���
#define		DERR_FRAMELOST						0x2//�����ݰ�
#define		DERR_REMOVE							0x3//�豸�Ƴ�
#define		DERR_SERIAL							0x4//�豸���кų�ͻ
//--------------------------------

//����ʶ��ʱ���Ա�����
#define		SG_NULL								0x0
#define		SG_MALE								0x1//����
#define		SG_FEMALE							0x2//Ů��
#define		SG_AUTO								0x3//�Զ�
//--------------------------------

//�豸����ģʽ
#define		SM_NOTSHARE							0x0
#define		SM_SENDVOICE						0x1//��������
#define		SM_RECVVOICE						0x2//��������
//----------------------------------

//----------------------------------------------
//�������/����
#define		FAX_TYPE_NULL						0x0
#define		FAX_TYPE_SEND						0x1//���ʹ���
#define		FAX_TYPE_RECV						0x2//���մ���
//------------------------------------------------

//
#define		TTS_LIST_REINIT						0x0//���³�ʼ���µ�TTS�б�
#define		TTS_LIST_APPEND						0x1//׷��TTS�б��ļ�
//------------------------------------------------

//--------------------------------------------------------
#define		DIALTYPE_DTMF						0x0//DTMF����
#define		DIALTYPE_FSK						0x1//FSK����
//--------------------------------------------------------

//--------------------------------------------------------
#define		PLAYFILE_MASK_REPEAT				0x1//ѭ������
#define		PLAYFILE_MASK_PAUSE					0x2//Ĭ����ͣ
//--------------------------------------------------------

//�����ļ��ص���״̬
#define		PLAYFILE_PLAYING					0x1//���ڲ���
#define		PLAYFILE_REPEAT						0x2//׼���ظ�����
#define		PLAYFILE_END						0x3//���Ž���

//-----------------------------------------------------------------------------------
#define		RECORD_MASK_ECHO					0x1//���������������
#define		RECORD_MASK_AGC						0x2//�Զ������¼��
#define		RECORD_MASK_PAUSE					0x4//��ͣ

#define		CONFERENCE_MASK_DISABLEMIC			0x100//ֹͣMIC,������������Ա�����������û�˵��
#define		CONFERENCE_MASK_DISABLESPK			0x200//ֹͣSPK,��������������������Ա˵��
//------------------------------------------------------------------------------------

#define		CHECKLINE_MASK_DIALOUT				0x1//��·�Ƿ�������������(�оͿ�����������)
#define		CHECKLINE_MASK_REV					0x2//��·LINE��/PHONE�ڽ����Ƿ�����,�������ͱ�ʾ�ӷ���

#define		CHECKDIALTONE_BEGIN					0x0//��Ⲧ����
#define		CHECKDIALTONE_ENDDIAL				0x1//��⵽������׼������

#define		CHECKDIALTONE_TIMEOUTDIAL			0x2//��Ⲧ������ʱǿ���Զ�����
#define		CHECKDIALTONE_FAILED				0x3//��Ⲧ������ʱ�ͱ��沦��ʧ��,������


#define		IPMODE_NULL							0x0//��
#define		IPMODE_BROADCAST					0x1//�㲥
#define		IPMODE_LISTALL						0x2//����ȫ��IP
#define		IPMODE_LISTIP						0x4//�����̶�IP
#define		IPMODE_ALL							0xFF//ȫ��

#define		RB_RINGBACK							0x0//�����ź�
#define		RB_TIMEOUT							0x1//���ų�ʱ
#define		RB_CODEEND							0x2//���볤�ȶ�̬�������

#define		SPEECH_DEV							0x0//�豸����ʶ��
#define		SPEECH_FILE							0x1//�ļ�����ʶ��

#define		REMOTE_ASYN							0x1//�첽

#define		OUTVALUE_MAX_SIZE					260//location�ȷ��ص���󳤶�


//-----------------------------------------------

//cc ��Ϣ����
//�����������������鿴windows����ĵ�
#define		MSG_KEY_CC				"cc:" //��Ϣ��ԴCC��
#define		MSG_KEY_NAME			"name:"//��Ϣ��Դ���ƣ�����
#define		MSG_KEY_TIME			"time:"//��Ϣ��Դʱ��
#define		MSG_KEY_FACE			"face:"//��������
#define		MSG_KEY_COLOR			"color:"//������ɫ
#define		MSG_KEY_SIZE			"size:"//����ߴ�
#define		MSG_KEY_CHARSET			"charset:"//��������
#define		MSG_KEY_EFFECTS			"effects:"//����Ч��
#define		MSG_KEY_LENGTH			"length:"//��Ϣ���ĳ���
#define		MSG_KEY_CID				"cid:"//����ID
#define		MSG_KEY_IMTYPE			"imtp:"//��Ϣ����
//CC�ļ�����
#define		MSG_KEY_FILENAME		"filename:"//�ļ���
#define		MSG_KEY_FILESIZE		"filesize:"//�ļ�����
#define		MSG_KEY_FILETYPE		"filetype:"//�ļ�����
//
#define		MSG_KEY_CALLPARAM		"callparam:"//CC����ʱ�Ĳ���


#define		MSG_KEY_IP				"ip:"//���յ���UDP���ݵ�IP��ַ
#define		MSG_KEY_WEBIP			"webip:"//���յ���UDP���ݵ�web IP��ַ
#define		MSG_KEY_PORT			"port:"//���յ���UDP���ݵĶ˿�

#define		MSG_KEY_SPLIT			"\r\n"//����֮��ָ�����
#define		MSG_TEXT_SPLIT			"\r\n\r\n"//��Ϣ��������Ϣ���ݵķָ�����
//

//�¼������󱣴��������󳤶�,��Ҫ���漴ʱ��Ϣ400�ֽ����ݼӸ�����Ϣ�����550����
#define		MAX_BRIEVENT_DATA	600
//4�ֽڶ���
typedef struct tag_BriEvent_Data
{
	BRICHAR8	uVersion;//�ṹ�汾������
	BRICHAR8	uReserv;//����
	BRIINT16	uChannelID;//ͨ��ID
	BRIINT32	lEventType;//�¼�����ID �鿴BRI_EVENT.lEventType Define
	BRIINT32	lEventHandle;//�¼���ؾ��
	BRIINT32	lResult;//�¼������ֵ
	BRIINT32	lParam;//����,��չʱʹ��
	BRICHAR8	szData[MAX_BRIEVENT_DATA];//�¼��������.�磺����ʱ������������ĺ���
	BRICHAR8	szDataEx[32];//����,��չʱʹ��

}BRI_EVENT,*PBRI_EVENT;


//----------------------------------------------------------------------
//�ص�����ԭ��
//----------------------------------------------------------------------
//
//���岥�Żص�ԭ��
//uChannelID:ͨ��ID
//dwUserData:�û��Զ��������
//lHandle:����ʱ���صľ��
//lDataSize:��ǰ�������������
//lFreeSize:��ǰ����Ŀ��г���
//���� CB_REMOVELIST(-1) ����ϵͳɾ���ûص���Դ���´β��ٻص�/��������ֵ����
typedef BRIINT32 (CALLBACK *PCallBack_PlayBuf)(BRIINT16 uChannelID,BRIUINT32 dwUserData,BRIINT32 lHandle,BRIINT32 lDataSize,BRIINT32 lFreeSize);
///////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//�����ļ����Żص�ԭ��
//uChannelID:ͨ��ID
//nPlayState:�ļ����ŵ�״̬,PLAYING/REPLAY/END
//dwUserData:�û��Զ��������
//lHandle:����ʱ���صľ��
//lElapses:�ܹ����ŵ�ʱ��(��λ��)
//���� CB_REMOVELIST(-1) ϵͳ���Զ�ֹͣ���Ÿ��ļ�/��������ֵ����
typedef BRIINT32 (CALLBACK *PCallBack_PlayFile)(BRIINT16 uChannelID,BRIUINT32 nPlayState,BRIUINT32 dwUserData,BRIINT32 lHandle,BRIINT32 lElapses);

//////////////////////////////////////////////////////////////////////////////////////////
//����¼���ص�ԭ�� Ĭ�ϸ�ʽΪ8K/16λ/������/����
//uChannelID:ͨ��ID
//dwUserData:�û��Զ�������
//pBufData:��������
//lBufSize:�������ݵ��ڴ��ֽڳ���
//���� CB_REMOVELIST(-1) ����ϵͳɾ���ûص���Դ���´β��ٻص�/��������ֵ����
//ע��:��Ҫ�ڻص�������ɾ���ûص�����,������ص�����,������ڻص���ɾ���ûص�����ֻҪ�Ѹûص���������CB_REMOVELIST(-1)����
//��Ϣģʽ�ص�Ҳһ��
typedef BRIINT32 (CALLBACK *PCallBack_RecordBuf)(BRIINT16 uChannelID,BRIUINT32 dwUserData,BRIBYTE8 *pBufData,BRIINT32 lBufSize);
////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////
//�¼������ص�ԭ��
//uChannelID:ͨ��ID
//dwUserData:�û��Զ�������
//lType:�¼�����ID �鿴BRI_EVENT.lEventType Define
//lResult:�¼��������
//lParam:��������,��չʹ��
//szData:�¼��������
//pDataEx:��������,��չʹ��
/////////////////////////////////////////////////////////////////////////////////////////
typedef BRIINT32 (CALLBACK *PCallBack_Event)(BRIINT16 uChannelID,BRIUINT32 dwUserData,BRIINT32	lType,BRIINT32 lHandle,BRIINT32 lResult,BRIINT32 lParam,BRIPCHAR8 pData,BRIPCHAR8 pDataEx);

//////////////////////////////////////////////////////////////////////////////////////////
//�¼������ص�ԭ��,ʹ�ýṹ�巽ʽ
//pEvent:�¼��ṹ������
//dwUserData:�û��Զ�������
//��ע:��PCallBack_EventֻҪʹ������һ�ַ�ʽ�Ϳ�����
/////////////////////////////////////////////////////////////////////////////////////////
typedef BRIINT32 (CALLBACK *PCallBack_EventEx)(PBRI_EVENT pEvent,BRIUINT32 dwUserData);


//////////////////////////////////////////////////////////////////////
//  BRI_EVENT.lEventType Define
//  �¼����Ͷ���.ͬ����ϵͳ�����Ĵ�����Ϣ(��ѡ������һ�ַ�ʽ����)
///////////////////////////////////////////////////////////////////////


// ���ص绰��ժ���¼�
#define	BriEvent_PhoneHook						(BRIINT32)1
// ���ص绰���һ��¼�
#define BriEvent_PhoneHang						(BRIINT32)2

// ����ͨ�����������¼�
// BRI_EVENT.lResult		Ϊ�������
// BRI_EVENT.szData[0]='0'	��ʼ1������
// BRI_EVENT.szData[0]='1'	Ϊ1��������ɣ���ʼ4�뾲��
#define BriEvent_CallIn							(BRIINT32)3		

// �õ��������
// BRI_EVENT.lResult		�������ģʽ(CALLIDMODE_FSK/CALLIDMODE_DTMF
// BRI_EVENT.szData			������������
// ���¼�����������ǰ,Ҳ�����������
#define BriEvent_GetCallID						(BRIINT32)4

// �Է�ֹͣ����(����һ��δ�ӵ绰)
#define BriEvent_StopCallIn						(BRIINT32)5

// ���ÿ�ʼ���ź�ȫ�����벦�Ž���
#define BriEvent_DialEnd						(BRIINT32)6

// �����ļ������¼�
// BRI_EVENT.lEventHandle	   �����ļ�ʱ���صľ��ID 
#define BriEvent_PlayFileEnd					(BRIINT32)7		

// ���ļ����������¼�
// 
#define BriEvent_PlayMultiFileEnd				(BRIINT32)8

//�����ַ�����
#define	BriEvent_PlayStringEnd					(BRIINT32)9

// �����ļ�����׼���ظ�����
// BRI_EVENT.lEventHandle	   �����ļ�ʱ���صľ��ID 
// 
#define BriEvent_RepeatPlayFile					(BRIINT32)10

// ������PHONE�豸���������ź�ʱ���ͺ������
#define BriEvent_SendCallIDEnd					(BRIINT32)11

//������PHONE�豸���������ź�ʱ��ʱ
//Ĭ����DEFAULT_RING_TIMEOUT(12)�κ�ʱ
#define BriEvent_RingTimeOut					(BRIINT32)12

//������PHONE�豸��������
// BRI_EVENT.lResult	    �Ѿ�����Ĵ���
// BRI_EVENT.szData[0]='0'	��ʼһ������
// BRI_EVENT.szData[0]='1'	һ��������ɣ�׼������
#define BriEvent_Ringing						(BRIINT32)13

// ͨ��ʱ��⵽һ��ʱ��ľ���.Ĭ��Ϊ5��
#define BriEvent_Silence						(BRIINT32)14

// ��·��ͨʱ�յ�DTMF���¼�
// ���¼���������ͨ�����Ǳ��ػ����������ǶԷ�������������
#define BriEvent_GetDTMFChar					(BRIINT32)15

// ���ź�,���з�ժ���¼�(���¼������ο�,ԭ�����£�)
// ԭ��
// ���¼�ֻ�����ڲ����Ǳ�׼�ź����ĺ���ʱ��Ҳ���ǲ��ź���б�׼�������ĺ��롣
// �磺������ĶԷ������ǲ���(�����ֻ���)��ϵͳ��ʾ��(179xx)�����Ǳ�׼������ʱ���¼���Ч��
// 
// �����ź���ģ����·��Ψһ�ɿ����ж϶Է�ժ���ķ�����ֻ��һ������Ҫ��ͨ���иù��ܣ���һ��������Щ�ط�����ʹ����Ҳδ��������Ϊ�ù���ԭ������Թ��õ绰�Ʒѵġ�
// û�иù��ܣ������ź������ж����ݣ����ɿ��Բ�������100�����������ڱ��з�Ϊ����ʱ������ʺܵ�
// ӵ�з�������ʽһ������ŵ�PSTN��·���뿪ͨ,�÷�ʽ�����Բ�ǿ,ԭ����������
// ӵ�з�������ʽ��������һ���ֻ�sim/3g��,�ٹ���һ�������������sim/3gƽ̨�豸(200���������),���豸������һ���绰�߽��뵽USB�豸
// BRI_EVENT.lResult : 0 Ϊ�����źŷ����Ľ��
// BRI_EVENT.lResult : 1 Ϊ�������Ľ��
#define BriEvent_RemoteHook						(BRIINT32)16

// �һ��¼�
// �����·��⵽���з�ժ���󣬱��з��һ�ʱ�ᴥ�����¼�����Ȼ���з��һ���ʹ���BriEvent_Busy�¼�
// ���¼�����BriEvent_Busy�Ĵ�������ʾPSTN��·�Ѿ����Ͽ�
// ��ע�����¼��Ǹ�����·��æ���źż�⣬���û��æ���Ͳ��ᴥ�����¼�
// ����з��������Ϊ�ɿ���ʾ
// BRI_EVENT.lResult : 0 Ϊ�����źŷ����Ľ��
// BRI_EVENT.lResult : 1 Ϊ�������Ľ��
#define BriEvent_RemoteHang						(BRIINT32)17

// ��⵽æ���¼�,��ʾPSTN��·�Ѿ����Ͽ�
#define BriEvent_Busy							(BRIINT32)18

// ����ժ�����⵽������
#define BriEvent_DialTone						(BRIINT32)19

// ֻ���ڱ��ػ���ժ����û�е�����ժ��ʱ,��⵽DTMF����
// BRI_EVENT.szData �����Ѿ����ĺ���
#define BriEvent_PhoneDial						(BRIINT32)20

// �绰�����Ž��������¼���
// Ҳ��ʱ�绰�����ź���յ���׼����������15�볬ʱ
// BRI_EVENT.lResult=0 ��⵽������// ע�⣺�����·�ǲ����ǲ��ᴥ��������
// BRI_EVENT.lResult=1 ���ų�ʱ
// BRI_EVENT.lResult=2 ��̬��Ⲧ�������(�����й���½�ĺ������������ܷ����������ο�)
// BRI_EVENT.szData[0]='1' ��ժ�����Ž����������
// BRI_EVENT.szData[0]='0' �绰�������л�����
#define BriEvent_RingBack						(BRIINT32)21

// MIC����״̬
// ֻ���þ��иù��ܵ��豸
#define BriEvent_MicIn							(BRIINT32)22		
// MIC�γ�״̬
// ֻ���þ��иù��ܵ��豸
#define BriEvent_MicOut							(BRIINT32)23		

// �Ĳ��(Flash)����¼����Ĳ����ɺ���Լ�Ⲧ��������ж��β���
// BRI_EVENT.lResult=TEL_FLASH  �û�ʹ�õ绰�������Ĳ�����
// BRI_EVENT.lResult=SOFT_FLASH ����StartFlash���������Ĳ�����
#define BriEvent_FlashEnd						(BRIINT32)24		

// �ܽ����
#define BriEvent_RefuseEnd						(BRIINT32)25

// ����ʶ����� 
#define	BriEvent_SpeechResult					(BRIINT32)26

//PSTN��·�Ͽ�,��·�������״̬
//��ǰû����ժ�����һ���Ҳûժ��
#define BriEvent_PSTNFree						(BRIINT32)27

// ���յ��Է�׼�����ʹ�����ź�
#define BriEvent_RemoteSendFax					(BRIINT32)30

// ���մ������
#define BriEvent_FaxRecvFinished				(BRIINT32)31
// ���մ���ʧ��
#define BriEvent_FaxRecvFailed					(BRIINT32)32

// ���ʹ������
#define BriEvent_FaxSendFinished				(BRIINT32)33
// ���ʹ���ʧ��
#define BriEvent_FaxSendFailed					(BRIINT32)34

// ��������ʧ��
#define BriEvent_OpenSoundFailed				(BRIINT32)35

// ����һ��PSTN����/������־
#define BriEvent_CallLog						(BRIINT32)36

//��⵽�����ľ���
//ʹ��QNV_GENERAL_CHECKSILENCE�������⵽�趨�ľ�������
#define	BriEvent_RecvSilence					(BRIINT32)37

//��⵽����������
//ʹ��QNV_GENERAL_CHECKVOICE�������⵽�趨����������
#define	BriEvent_RecvVoice						(BRIINT32)38

//Զ���ϴ��¼�
// BRI_EVENT.lResult	   �����ϴ�ʱ���صı��β����ľ��
// http ���������յ����ݺ󷵻�Result:1 �ն˽����յ����¼������򷵻�ʧ��
#define	BriEvent_UploadSuccess					(BRIINT32)50

#define	BriEvent_UploadFailed					(BRIINT32)51
// Զ�������ѱ��Ͽ�
#define BriEvent_RemoteDisconnect				(BRIINT32)52

//HTTPԶ�������ļ����
//BRI_EVENT.lResult	   ��������ʱ���صı��β����ľ��
#define	BriEvent_DownloadSuccess				(BRIINT32)60
#define	BriEvent_DownloadFailed					(BRIINT32)61
//�Ⱥ򲥷�Զ������
#define	BriEvent_PlayRemoteWait					(BRIINT32)62

//��·�����
//BRI_EVENT.lResult Ϊ�������Ϣ
//1:������
//2:��·û�ӷ�
//3:�����Ŷ�����·û�ӷ�
#define	BriEvent_CheckLine						(BRIINT32)70

// Ӧ�ò������ժ��/��һ��ɹ��¼�
// BRI_EVENT.lResult=1 ��ժ��
// BRI_EVENT.lResult=0 ��һ�			
#define BriEvent_EnableHook						(BRIINT32)100
// ���ȱ��򿪻���/�ر�
// BRI_EVENT.lResult=0 �ر�
// BRI_EVENT.lResult=1 ��			
#define BriEvent_EnablePlay						(BRIINT32)101
// MIC���򿪻��߹ر�	
// BRI_EVENT.lResult=0 �ر�
// BRI_EVENT.lResult=1 ��			
#define BriEvent_EnableMic						(BRIINT32)102		
// �������򿪻��߹ر�
// BRI_EVENT.lResult=0 �ر�
// BRI_EVENT.lResult=1 ��			
#define BriEvent_EnableSpk						(BRIINT32)103		
// �绰�����绰��(PSTN)�Ͽ�/��ͨ(DoPhone)
// BRI_EVENT.lResult=0 �Ͽ�
// BRI_EVENT.lResult=1 ��ͨ		
#define BriEvent_EnableRing						(BRIINT32)104		
// �޸��������·lineͨ��
// BRI_EVENT.lResult= linein idֵ
#define BriEvent_SelectLineIn					(BRIINT32)105		
// ��ʼ�������
// BRI_EVENT.szData	׼�����ĺ���
// BRI_EVENT.lResult=0 ����ǰ׼����Ⲧ����
// BRI_EVENT.lResult=1 ��⵽��������ʼ����
// BRI_EVENT.lResult=2 δ��⵽��������ʼǿ�Ʋ���(QNV_PARAM_DIALTONERESULT=2ʱ����)
// BRI_EVENT.lResult=3 δ��⵽������,����ʧ�ܣ����ٽ��в�����(QNV_PARAM_DIALTONERESULT=3ʱ����)
#define BriEvent_DoStartDial					(BRIINT32)106
// ��������ͨ����ѡ��
// BRI_EVENT.lResult= ѡ���muxֵ
#define	BriEvent_EnablePlayMux					(BRIINT32)107
//�ı��豸����״̬
#define	BriEvent_DevCtrl						(BRIINT32)110

//��ͨ��״̬�н��յ�������
//������������������𻰻�һ��ʱ���ڼ�⵽,Ӧ�ò���Կ�����Ϊ�Ǹղŵ绰�Ѿ�δ��,�������𻰻�����ȥ��
#define	BriEvent_DialToneEx						(BRIINT32)193
// ���յ�DTMF,�������ǲ��Ż���ͨ����,���н��յ���DTMF�¼����ص�
// BRI_EVENT.szData	����
// ����һ���û�����Ҫʹ��
#define BriEvent_RecvedDTMF						(BRIINT32)194

//�豸���ܱ��ε���,Ч���൱��BriEvent_DevErr�¼�ʱ��BRI_EVENT.lResult=3
#define BriEvent_PlugOut						(BRIINT32)195
//Ӳ��������
// ����
#define	BriEvent_CallInEx						(BRIINT32)196
// ���´��豸�ɹ�
// ����
#define BriEvent_ReopenSucccess					(BRIINT32)197
// ���յ�����,����ͨ����FSK		
// BRI_EVENT.szData	����
//�������ڲ�ʹ�ã�����һ���û�����Ҫʹ��
#define BriEvent_RecvedFSK						(BRIINT32)198
//�豸�쳣����
//BRI_EVENT.lResult=3 ��ʾ�豸���ܱ��Ƴ���,����رպ����´��豸�ſ�������ʹ��
//�������Ժ��Բ�������
#define BriEvent_DevErr							(BRIINT32)199

// CCCtrl Event
// CC��������¼�
// BRI_EVENT.szData ������Ϣ�����Ϣ
// ��Ϣ�ڵĲ���������ʹ��2�����зָ�
// ÿ������ʹ��1�����зָ�
#define BriEvent_CC_ConnectFailed				(BRIINT32)200//����ʧ��
#define	BriEvent_CC_LoginFailed					(BRIINT32)201//��½ʧ��
#define	BriEvent_CC_LoginSuccess				(BRIINT32)202//��½�ɹ�
#define BriEvent_CC_SystemTimeErr				(BRIINT32)203//ϵͳʱ�����
#define	BriEvent_CC_CallIn						(BRIINT32)204//��CC��������
#define BriEvent_CC_CallOutFailed				(BRIINT32)205//����ʧ��
#define	BriEvent_CC_CallOutSuccess				(BRIINT32)206//���гɹ������ں���
#define BriEvent_CC_Connecting					(BRIINT32)207//������������
#define BriEvent_CC_Connected					(BRIINT32)208//������ͨ
#define BriEvent_CC_CallFinished				(BRIINT32)209//���н���
#define BriEvent_CC_ReplyBusy					(BRIINT32)210//�Է��ظ�æ����
#define BriEvent_CC_GetDTMF						(BRIINT32)211//���յ�DTMF
#define	BriEvent_CC_PlayFileEnd					(BRIINT32)212//�����ļ�����
#define BriEvent_CC_ReConnect					(BRIINT32)212//������������

#define BriEvent_CC_RecvedMsg					(BRIINT32)220//���յ��û���ʱ��Ϣ
#define BriEvent_CC_RecvedCmd					(BRIINT32)221//���յ��û��Զ�������
#define BriEvent_CC_RecvedIP					(BRIINT32)222//���յ��û�IP��ַ��Ϣ

#define	BriEvent_CC_RegSuccess					(BRIINT32)225//ע��CC�ɹ�
#define	BriEvent_CC_RegFailed					(BRIINT32)226//ע��CCʧ��
#define	BriEvent_CC_FindSuccess					(BRIINT32)227//����CC������IP�ɹ�
#define	BriEvent_CC_FindFailed					(BRIINT32)228//����CC������IPʧ��
#define	BriEvent_CC_FindEnd						(BRIINT32)229//����CC����������

#define	BriEvent_CC_RecvFileRequest				(BRIINT32)230//���յ��û����͵��ļ�����
#define	BriEvent_CC_TransFileFinished			(BRIINT32)231//�����ļ�����

#define BriEvent_CC_AddContactSuccess			(BRIINT32)240//���Ӻ��ѳɹ�
#define BriEvent_CC_AddContactFailed			(BRIINT32)241//���Ӻ���ʧ��
#define BriEvent_CC_InviteContact				(BRIINT32)242//���յ����Ӻú�������
#define BriEvent_CC_ReplyAcceptContact			(BRIINT32)243//�Է��ظ�ͬ��Ϊ����
#define BriEvent_CC_ReplyRefuseContact			(BRIINT32)244//�Է��ظ��ܾ�Ϊ����
#define BriEvent_CC_AcceptContactSuccess		(BRIINT32)245//���ܺ��ѳɹ�
#define BriEvent_CC_AcceptContactFailed			(BRIINT32)246//���ܺ���ʧ��
#define BriEvent_CC_RefuseContactSuccess		(BRIINT32)247//�ܾ����ѳɹ�
#define BriEvent_CC_RefuseContactFailed			(BRIINT32)248//�ܾ�����ʧ��	
#define BriEvent_CC_DeleteContactSuccess		(BRIINT32)249//ɾ�����ѳɹ�
#define	BriEvent_CC_DeleteContactFailed			(BRIINT32)250//ɾ������ʧ��
#define BriEvent_CC_ContactUpdateStatus			(BRIINT32)251//���ѵ�½״̬�ı�
#define BriEvent_CC_ContactDownendStatus		(BRIINT32)252//��ȡ�����к��Ѹı����
#define	BriEvent_CC_ModifyPwdFailed				(BRIINT32)253//�޸�����ʧ��
#define	BriEvent_CC_ModifyPwdSuccess			(BRIINT32)254//�޸�����ɹ�

//c/s socket�շ������¼�
//�ն˽��յ����¼�
#define BriEvent_Socket_C_ConnectSuccess		(BRIINT32)300//���ӳɹ�
#define BriEvent_Socket_C_ConnectFailed			(BRIINT32)301//����ʧ��
#define BriEvent_Socket_C_ReConnect				(BRIINT32)302//��ʼ��������
#define BriEvent_Socket_C_ReConnectFailed		(BRIINT32)303//��������ʧ��
#define BriEvent_Socket_C_ServerClose			(BRIINT32)304//�������Ͽ�����
#define BriEvent_Socket_C_DisConnect			(BRIINT32)305//���Ӽ��ʱ
#define BriEvent_Socket_C_RecvedData			(BRIINT32)306//���յ�����˷��͹���������
//
//�������˽��յ����¼�
#define BriEvent_Socket_S_NewLink				(BRIINT32)340//�������ӽ���
#define BriEvent_Socket_S_DisConnect			(BRIINT32)341//�ն����Ӽ��ʱ
#define BriEvent_Socket_S_ClientClose			(BRIINT32)342//�ն˶Ͽ�������
#define BriEvent_Socket_S_RecvedData			(BRIINT32)343//���յ��ն˷��͹���������
//
//UDP�¼�
#define	BriEvent_Socket_U_RecvedData			(BRIINT32)360//���յ�UDP����
#define BriEvent_Socket_U_FindUDPSuccess		(BRIINT32)361//���յ�UDP��ʽ��ѯ�������ظ�
#define BriEvent_Socket_U_FindUDPFailed			(BRIINT32)362//����UDB������ʧ��

//

#define	BriEvent_EndID							(BRIINT32)500//��ID
#define	BriEvent_UserID							(BRIINT32)1024//�û��Զ���ID


///////////////////////////////////////////////////////////////
//��Ϣ����˵��
//////////////////////////////////////////////////////////////
//Ĭ���¼���ϢID,����г�ͻ����ʹ��QNV_EVENT_SETEVENTMSGID�޸ĸ���Ϣ�ص�ֵ
//��ע���û����յ���Ϣ�ṹ��Ҫ�޸Ľṹ������
#define		BRI_EVENT_MESSAGE					(WM_USER+2000)
//Ĭ�ϻ���¼��������ϢID,����г�ͻ����ʹ��QNV_RECORD_BUF_SETCBMSGID�޸ĸ���Ϣ�ص�ֵ
#define		BRI_RECBUF_MESSAGE					(WM_USER+2001)
//

//�����ļ������ʽID
//����BRI_WAV_FORMAT_PCM8K16B�⣬������ʽ��Ҫϵͳ���������֧��
//���ϵͳ��֧���ڿ�ʼ�ļ�¼��ʱ��������BCERR_NOTSUPPORTFORMAT(-14)
#define		BRI_WAV_FORMAT_DEFAULT					(BRIUINT32)0 // BRI_AUDIO_FORMAT_PCM8K16B
#define		BRI_WAV_FORMAT_ALAW8K					(BRIUINT32)1 // 8k/s
#define		BRI_WAV_FORMAT_ULAW8K					(BRIUINT32)2 // 8k/s
#define		BRI_WAV_FORMAT_IMAADPCM8K4B				(BRIUINT32)3 // 4k/s
#define		BRI_WAV_FORMAT_PCM8K8B					(BRIUINT32)4 // 8k/s
#define		BRI_WAV_FORMAT_PCM8K16B					(BRIUINT32)5 //16k/s
#define		BRI_WAV_FORMAT_MP38K8B					(BRIUINT32)6 //~1.2k/s//����
#define		BRI_WAV_FORMAT_MP38K16B					(BRIUINT32)7 //~2.4k/s//����
#define		BRI_WAV_FORMAT_TM8K1B					(BRIUINT32)8 //~1.5k/s
#define		BRI_WAV_FORMAT_GSM6108K					(BRIUINT32)9 //~2.2k/s
#define		BRI_WAV_FORMAT_END						(BRIUINT32)255 //��ЧID
//�������256��
////////////////////////////////////////////////////////////


//----------------------------------------------------------------------------------
//�豸��Ϣ
#define		QNV_DEVINFO_GETCHIPTYPE					(BRIUINT32)1//��ȡUSBоƬģ������
#define		QNV_DEVINFO_GETCHIPS					(BRIUINT32)2//��ȡUSBģ������,��ֵ�������һ��ͨ����DEVID+1
#define		QNV_DEVINFO_GETTYPE						(BRIUINT32)3//��ȡͨ���豸����
#define		QNV_DEVINFO_GETMODULE					(BRIUINT32)4//��ȡͨ������ģ��
#define		QNV_DEVINFO_GETCHIPCHID					(BRIUINT32)5//��ȡͨ������USBоƬ���еĴ���ID(0����1)
#define		QNV_DEVINFO_GETSERIAL					(BRIUINT32)6//��ȡͨ�����к�(0-n)
#define		QNV_DEVINFO_GETCHANNELS					(BRIUINT32)7//��ȡͨ������
#define		QNV_DEVINFO_GETDEVID					(BRIUINT32)8//��ȡͨ�����ڵ�USBоƬID(0-n)
#define		QNV_DEVINFO_GETDLLVER					(BRIUINT32)9//��ȡDLL�汾��
#define		QNV_DEVINFO_GETCHIPCHANNEL				(BRIUINT32)10//��ȡ��USBģ���һ������ID���ڵ�ͨ����
#define		QNV_DEVINFO_GETCHANNELTYPE				(BRIUINT32)11//ͨ����·�����߻��ǻ�������
#define		QNV_DEVINFO_GETCHIPCHANNELS				(BRIUINT32)12//��ȡ��USBģ��ڶ�������ID���ڵ�ͨ����

#define		QNV_DEVINFO_FILEVERSION					(BRIUINT32)20//��ȡDLL���ļ��汾[�ַ�]
#define		QNV_DEVINFO_FILEVERSIONL				(BRIUINT32)21//��ȡDLL���ļ��汾[����]
//---------------------------------------------------------------------------------

//���������б�
//uParamType (����ʹ��API(QNV_GENERAL_READPARAM/QNV_GENERAL_WRITEPARAM)�Զ�����/��ȡ)
#define		QNV_PARAM_BUSY							(BRIUINT32)1//��⵽����æ���ص�
	
#define		QNV_PARAM_DTMFLEVEL						(BRIUINT32)2//dtmf���ʱ�������������(0-7)
#define		QNV_PARAM_DTMFVOL						(BRIUINT32)3//dtmf���ʱ���������(1-100)
#define		QNV_PARAM_DTMFNUM						(BRIUINT32)4//dtmf���ʱ����ĳ���ʱ��(2-10)
#define		QNV_PARAM_DTMFLOWINHIGH					(BRIUINT32)5//dtmf��Ƶ���ܳ�����Ƶֵ(Ĭ��Ϊ7)
#define		QNV_PARAM_DTMFHIGHINLOW					(BRIUINT32)6//dtmf��Ƶ���ܳ�����Ƶֵ(Ĭ��Ϊ5)

#define		QNV_PARAM_DIALSPEED						(BRIUINT32)7//���ŵ�DTMF����(1ms-60000ms)
#define		QNV_PARAM_DIALSILENCE					(BRIUINT32)8//����ʱ�ļ����������(1ms-60000ms)
#define		QNV_PARAM_DIALVOL						(BRIUINT32)9//����������С

#define		QNV_PARAM_RINGSILENCE					(BRIUINT32)10//���粻�������ʱ�䳬ʱ��δ�ӵ绰
#define		QNV_PARAM_CONNECTSILENCE				(BRIUINT32)11//ͨ��ʱ��������ʱ�侲����ص�
#define		QNV_PARAM_RINGBACKNUM					(BRIUINT32)12//�������������Ϻ�����忪ʼ��Ч//Ĭ��Ϊ2��,���𵽺��Գ��ֺ������Ļ�����
#define		QNV_PARAM_SWITCHLINEIN					(BRIUINT32)13//�Զ��л�LINEINѡ��
#define		QNV_PARAM_FLASHELAPSE					(BRIUINT32)14//�Ĳ�ɼ��
#define		QNV_PARAM_FLASHENDELAPSE				(BRIUINT32)15//�Ĳ�ɺ��ӳ�һ��ʱ���ٻص��¼�
#define		QNV_PARAM_RINGELAPSE					(BRIUINT32)16//��������ʱʱ�䳤��
#define		QNV_PARAM_RINGSILENCEELAPSE				(BRIUINT32)17//��������ʱ��������
#define		QNV_PARAM_RINGTIMEOUT					(BRIUINT32)18//��������ʱ��ʱ����
#define		QNV_PARAM_RINGCALLIDTYPE				(BRIUINT32)19//��������ʱ���ͺ���ķ�ʽdtmf/fsk
#define		QNV_PARAM_REFUSEELAPSE					(BRIUINT32)20//�ܽ�ʱ���ʱ�䳤��
#define		QNV_PARAM_DIALTONETIMEOUT				(BRIUINT32)21//��Ⲧ������ʱʱ��
#define		QNV_PARAM_MINCHKFLASHELAPSE				(BRIUINT32)22//�Ĳ�ɼ��ʱ�һ����ٵ�ʱ��ms,�һ�ʱ��С�ڸ�ֵ�Ͳ����Ĳ��
#define		QNV_PARAM_MAXCHKFLASHELAPSE				(BRIUINT32)23//�Ĳ�ɼ��ʱ�һ����ʱ��ms,�һ�ʱ����ڸ�ֵ�Ͳ����Ĳ��
#define		QNV_PARAM_HANGUPELAPSE					(BRIUINT32)24//���绰���һ�ʱ������ʱ�䳤��ms,//����һ����ʱ�����Ĳ�����ϣ����ⷢ���һ����ּ�⵽�Ĳ�
#define		QNV_PARAM_OFFHOOKELAPSE					(BRIUINT32)25//���绰��ժ��ʱ������ʱ�䳤��ms
#define		QNV_PARAM_RINGHIGHELAPSE				(BRIUINT32)26//�����������ʱ���������ʱ�䳤��ms
#define		QNV_PARAM_RINGLOWELAPSE					(BRIUINT32)27//�����������ʱ�����������ʱ�䳤��ms
#define		QNV_PARAM_DIALTONERESULT				(BRIUINT32)28//��Ⲧ������ʱ��ǿ�Ʋ��Ż�����ʾ����dostartdialʧ��

#define		QNV_PARAM_SPEECHGENDER					(BRIUINT32)30//����ʶ���Ա�
#define		QNV_PARAM_SPEECHTHRESHOLD				(BRIUINT32)31//����ʶ������
#define		QNV_PARAM_SPEECHSILENCEAM				(BRIUINT32)32//����ʶ��������
#define		QNV_PARAM_ECHOTHRESHOLD					(BRIUINT32)33//������������������޲���
#define		QNV_PARAM_ECHODECVALUE					(BRIUINT32)34//����������������������
#define		QNV_PARAM_SIGSILENCEAM					(BRIUINT32)35//�ź���/��·ͨ�������ľ�������

#define		QNV_PARAM_LINEINFREQ1TH					(BRIUINT32)40//��һ����·˫Ƶģʽ�ź���Ƶ��
#define		QNV_PARAM_LINEINFREQ2TH					(BRIUINT32)41//�ڶ�����·˫Ƶģʽ�ź���Ƶ��
#define		QNV_PARAM_LINEINFREQ3TH					(BRIUINT32)42//��������·˫Ƶģʽ�ź���Ƶ��

#define		QNV_PARAM_ADBUSYMINFREQ					(BRIUINT32)45//���æ������ʱ��СƵ��
#define		QNV_PARAM_ADBUSYMAXFREQ					(BRIUINT32)46//���æ������ʱ���Ƶ��

//�������
#define		QNV_PARAM_AM_MIC						(BRIUINT32)50//MIC����
#define		QNV_PARAM_AM_SPKOUT						(BRIUINT32)51//����spk����
#define		QNV_PARAM_AM_LINEIN						(BRIUINT32)52//��·��������
#define		QNV_PARAM_AM_LINEOUT					(BRIUINT32)53//mic����·����+��������������·����
#define		QNV_PARAM_AM_DOPLAY						(BRIUINT32)54//�����������
//
#define		QNV_PARAM_CITYCODE						(BRIUINT32)60//��������,�ʺ��й���½
#define		QNV_PARAM_PROXYDIAL						(BRIUINT32)61//������

#define		QNV_PARAM_FINDSVRTIMEOUT				(BRIUINT32)70//�����Զ�CC������ʱʱ��,����[�ڲ�ʹ��]
#define		QNV_PARAM_CONFJITTERBUF					(BRIUINT32)71//���齻���Ķ�̬�����С

#define		QNV_PARAM_RINGTHRESHOLD					(BRIUINT32)80//���������źŷ�������

#define		QNV_PARAM_DTMFCALLIDLEVEL				(BRIUINT32)100//dtmf���������ʱ�������������(0-7)
#define		QNV_PARAM_DTMFCALLIDNUM					(BRIUINT32)101//dtmf���������ʱ����ĳ���ʱ��(2-10)
#define		QNV_PARAM_DTMFCALLIDVOL					(BRIUINT32)102//dtmf���������ʱ���������Ҫ��

#define		QNV_PARAM_FSKFILTER						(BRIUINT32)110//�Ƿ���FSK�ź��˲�,�������������кܸ߸�������ʱ�����л��ò�������
#define		QNV_PARAM_FSKSPACEAM					(BRIUINT32)111//FSK�ź�ƥ�����,Ĭ��Ϊ100,��ΧΪ20-1000.200��ʾ�Ŵ�һ�����ָ���Ƶ��˥�����֣���߿ɿ���,������100-400֮��


//�豸����/״̬
//uCtrlType
#define		QNV_CTRL_DOSHARE						(BRIUINT32)1//�豸����ģʽ
#define		QNV_CTRL_DOHOOK							(BRIUINT32)2//���ժ�һ�����
#define		QNV_CTRL_DOPHONE						(BRIUINT32)3//���Ƶ绰���Ƿ����,�ɿ��ƻ�������,ʵ��Ӳ�Ĳ�ɵ�
#define		QNV_CTRL_DOPLAY							(BRIUINT32)4//���ȿ��ƿ���
#define		QNV_CTRL_DOLINETOSPK					(BRIUINT32)5//��·�������������ö���ͨ��ʱ��
#define		QNV_CTRL_DOPLAYTOSPK					(BRIUINT32)6//���ŵ�����������
#define		QNV_CTRL_DOMICTOLINE					(BRIUINT32)7//MIC˵�������绰��
#define		QNV_CTRL_ECHO							(BRIUINT32)8//��/�رջ�������
#define		QNV_CTRL_RECVFSK						(BRIUINT32)9//��/�رս���FSK�������
#define		QNV_CTRL_RECVDTMF						(BRIUINT32)10//��/�رս���DTMF
#define		QNV_CTRL_RECVSIGN						(BRIUINT32)11//��/�ر��ź������
#define		QNV_CTRL_WATCHDOG						(BRIUINT32)12//�򿪹رտ��Ź�
#define		QNV_CTRL_PLAYMUX						(BRIUINT32)13//ѡ�����ȵ�����ͨ�� line1x/pcplay ch0/line2x/pcplay ch1
#define		QNV_CTRL_PLAYTOLINE						(BRIUINT32)14//���ŵ�������line(�������û�����Ҫ�޸�)
#define		QNV_CTRL_SELECTLINEIN					(BRIUINT32)15//ѡ���������·lineͨ��
#define		QNV_CTRL_SELECTADCIN					(BRIUINT32)16//ѡ�������Ϊ��·����MIC����
#define		QNV_CTRL_PHONEPOWER						(BRIUINT32)17//��/�رո���������ʹ��,���������������,dophone�л���,������������,���жԻ����Ĳ�������Ч
#define		QNV_CTRL_RINGPOWER						(BRIUINT32)18//��������ʹ��
#define		QNV_CTRL_LEDPOWER						(BRIUINT32)19//LEDָʾ��
#define		QNV_CTRL_LINEOUT						(BRIUINT32)20//��·���ʹ��(�������û�����Ҫ�޸�)
#define		QNV_CTRL_SWITCHOUT						(BRIUINT32)21//Ӳ����������
#define		QNV_CTRL_UPLOAD							(BRIUINT32)22//��/�ر��豸�����ϴ�����,�رպ󽫽��ղ����豸��������
#define		QNV_CTRL_DOWNLOAD						(BRIUINT32)23//��/�ر��豸�������ع���,�رպ󽫲��ܷ�������/���ŵ��豸
#define		QNV_CTRL_POLARITY						(BRIUINT32)24//���ؼ��Է�תժ�����
#define		QNV_CTRL_ADBUSY							(BRIUINT32)25//�Ƿ�򿪼��æ������ʱ����(ֻ����ʹ����·��������ʱ����ͬʱ�һ��Żᴥ��æ�������ӵĻ���,��ͨ�û�����Ҫʹ��)
#define		QNV_CTRL_RECVCALLIN						(BRIUINT32)26//��/�ر����������
#define		QNV_CTRL_READFRAMENUM					(BRIUINT32)27//һ�������ȡ��USB֡������Խ��ռ��CPUԽС���ӳ�Ҳ��Խ��һ֡Ϊ4ms,���30֡��Ҳ�������÷�ΧΪ(1-30)
#define		QNV_CTRL_DTMFCALLID						(BRIUINT32)28//����DTMFģʽ�����������,Ĭ���ǿ�������
//����״̬��������(set),ֻ�ܻ�ȡ(get)
#define		QNV_CTRL_PHONE							(BRIUINT32)30//�绰��ժ�һ�״̬
#define		QNV_CTRL_MICIN							(BRIUINT32)31//mic����״̬
#define		QNV_CTRL_RINGTIMES						(BRIUINT32)32//��������Ĵ���
#define		QNV_CTRL_RINGSTATE						(BRIUINT32)33//��������״̬�������컹�ǲ���
//


//��������
//uPlayType
#define		QNV_PLAY_FILE_START						(BRIUINT32)1//��ʼ�����ļ�
#define		QNV_PLAY_FILE_SETCALLBACK				(BRIUINT32)2//���ò����ļ��ص�����
#define		QNV_PLAY_FILE_SETVOLUME					(BRIUINT32)3//���ò����ļ�����
#define		QNV_PLAY_FILE_GETVOLUME					(BRIUINT32)4//��ȡ�����ļ�����
#define		QNV_PLAY_FILE_PAUSE						(BRIUINT32)5//��ͣ�����ļ�
#define		QNV_PLAY_FILE_RESUME					(BRIUINT32)6//�ָ������ļ�
#define		QNV_PLAY_FILE_ISPAUSE					(BRIUINT32)7//����Ƿ�����ͣ����
#define		QNV_PLAY_FILE_SETREPEAT					(BRIUINT32)8//�����Ƿ�ѭ������
#define		QNV_PLAY_FILE_ISREPEAT					(BRIUINT32)9//����Ƿ���ѭ������
#define		QNV_PLAY_FILE_SEEKTO					(BRIUINT32)11//��ת��ĳ��ʱ��(ms)
#define		QNV_PLAY_FILE_SETREPEATTIMEOUT			(BRIUINT32)12//����ѭ�����ų�ʱ����
#define		QNV_PLAY_FILE_GETREPEATTIMEOUT			(BRIUINT32)13//��ȡѭ�����ų�ʱ����
#define		QNV_PLAY_FILE_SETPLAYTIMEOUT			(BRIUINT32)14//���ò����ܹ���ʱʱ��(ms)
#define		QNV_PLAY_FILE_GETPLAYTIMEOUT			(BRIUINT32)15//��ȡ�����ܹ���ʱʱ��
#define		QNV_PLAY_FILE_TOTALLEN					(BRIUINT32)16//�ܹ�ʱ��(ms)
#define		QNV_PLAY_FILE_CURSEEK					(BRIUINT32)17//��ǰ���ŵ��ļ�ʱ��λ��(ms)
#define		QNV_PLAY_FILE_ELAPSE					(BRIUINT32)18//�ܹ����ŵ�ʱ��(ms),�����ظ���,���˵�,��������ͣ��ʱ��
#define		QNV_PLAY_FILE_ISPLAY					(BRIUINT32)19//�þ���Ƿ���Ч���ž��
#define		QNV_PLAY_FILE_ENABLEAGC					(BRIUINT32)20//�򿪹ر��Զ�����
#define		QNV_PLAY_FILE_ISENABLEAGC				(BRIUINT32)21//����Ƿ���Զ�����
#define		QNV_PLAY_FILE_STOP						(BRIUINT32)22//ֹͣ����ָ���ļ�
#define		QNV_PLAY_FILE_GETCOUNT					(BRIUINT32)23//��ȡ�����ļ����ŵ�����,��������������û���˾Ϳ��Թر�����
#define		QNV_PLAY_FILE_STOPALL					(BRIUINT32)24//ֹͣ���������ļ�
#define		QNV_PLAY_FILE_REMOTEBUFFERLEN			(BRIUINT32)25//Զ�̲�����Ҫ���صĻ��峤��
#define		QNV_PLAY_FILE_REMOTEBUFFERSEEK			(BRIUINT32)26//Զ�̲����Ѿ����صĻ��峤��
//--------------------------------------------------------

#define		QNV_PLAY_BUF_START						(BRIUINT32)1//��ʼ���岥��
#define		QNV_PLAY_BUF_SETCALLBACK				(BRIUINT32)2//���û��岥�Żص�����
#define		QNV_PLAY_BUF_SETWAVEFORMAT				(BRIUINT32)3//���û��岥�������ĸ�ʽ
#define		QNV_PLAY_BUF_WRITEDATA					(BRIUINT32)4//д��������
#define		QNV_PLAY_BUF_SETVOLUME					(BRIUINT32)5//��������
#define		QNV_PLAY_BUF_GETVOLUME					(BRIUINT32)6//��ȡ����
#define		QNV_PLAY_BUF_SETUSERVALUE				(BRIUINT32)7//�����û��Զ�������
#define		QNV_PLAY_BUF_GETUSERVALUE				(BRIUINT32)8//��ȡ�û��Զ�������
#define		QNV_PLAY_BUF_ENABLEAGC					(BRIUINT32)9//�򿪹ر��Զ�����
#define		QNV_PLAY_BUF_ISENABLEAGC				(BRIUINT32)10//����Ƿ�����Զ�����
#define		QNV_PLAY_BUF_PAUSE						(BRIUINT32)11//��ͣ�����ļ�
#define		QNV_PLAY_BUF_RESUME						(BRIUINT32)12//�ָ������ļ�
#define		QNV_PLAY_BUF_ISPAUSE					(BRIUINT32)13//����Ƿ�����ͣ����
#define		QNV_PLAY_BUF_STOP						(BRIUINT32)14//ֹͣ���岥��
#define		QNV_PLAY_BUF_FREESIZE					(BRIUINT32)15//�����ֽ�
#define		QNV_PLAY_BUF_DATASIZE					(BRIUINT32)16//�����ֽ�
#define		QNV_PLAY_BUF_TOTALSAMPLES				(BRIUINT32)17//�ܹ����ŵĲ�����
#define		QNV_PLAY_BUF_SETJITTERBUFSIZE			(BRIUINT32)18//���ö�̬���峤�ȣ����������ݲ���Ϊ�պ��´β���ǰ�����ڱ�����ڸó��ȵ�����,�����ڲ����������ݰ����������綶��
#define		QNV_PLAY_BUF_GETJITTERBUFSIZE			(BRIUINT32)19//��ȡ��̬���峤��
#define		QNV_PLAY_BUF_GETCOUNT					(BRIUINT32)20//��ȡ���ڻ��岥�ŵ�����,��������������û���˾Ϳ��Թر�����
#define		QNV_PLAY_BUF_STOPALL					(BRIUINT32)21//ֹͣ���в���
//-------------------------------------------------------

#define		QNV_PLAY_MULTIFILE_START				(BRIUINT32)1//��ʼ���ļ���������
#define		QNV_PLAY_MULTIFILE_PAUSE				(BRIUINT32)2//��ͣ���ļ���������
#define		QNV_PLAY_MULTIFILE_RESUME				(BRIUINT32)3//�ָ����ļ���������
#define		QNV_PLAY_MULTIFILE_ISPAUSE				(BRIUINT32)4//����Ƿ���ͣ�˶��ļ���������
#define		QNV_PLAY_MULTIFILE_SETVOLUME			(BRIUINT32)5//���ö��ļ���������
#define		QNV_PLAY_MULTIFILE_GETVOLUME			(BRIUINT32)6//��ȡ���ļ���������
#define		QNV_PLAY_MULTIFILE_ISSTART				(BRIUINT32)7//�Ƿ������˶��ļ���������
#define		QNV_PLAY_MULTIFILE_STOP					(BRIUINT32)8//ֹͣ���ļ���������
#define		QNV_PLAY_MULTIFILE_STOPALL				(BRIUINT32)9//ֹͣȫ�����ļ���������
//--------------------------------------------------------

#define		QNV_PLAY_STRING_INITLIST				(BRIUINT32)1//��ʼ���ַ������б�
#define		QNV_PLAY_STRING_START					(BRIUINT32)2//��ʼ�ַ�����
#define		QNV_PLAY_STRING_PAUSE					(BRIUINT32)3//��ͣ�ַ�����
#define		QNV_PLAY_STRING_RESUME					(BRIUINT32)4//�ָ��ַ�����
#define		QNV_PLAY_STRING_ISPAUSE					(BRIUINT32)5//����Ƿ���ͣ���ַ�����
#define		QNV_PLAY_STRING_SETVOLUME				(BRIUINT32)6//�����ַ���������
#define		QNV_PLAY_STRING_GETVOLUME				(BRIUINT32)7//��ȡ�ַ���������
#define		QNV_PLAY_STRING_ISSTART					(BRIUINT32)8//�Ƿ������˲����ַ�
#define		QNV_PLAY_STRING_STOP					(BRIUINT32)9//ֹͣ�ַ�����
#define		QNV_PLAY_STRING_STOPALL					(BRIUINT32)10//ֹͣȫ���ַ�����
//--------------------------------------------------------

//¼������
//uRecordType
#define		QNV_RECORD_FILE_START					(BRIUINT32)1//��ʼ�ļ�¼��
#define		QNV_RECORD_FILE_PAUSE					(BRIUINT32)2//��ͣ�ļ�¼��
#define		QNV_RECORD_FILE_RESUME					(BRIUINT32)3//�ָ��ļ�¼��
#define		QNV_RECORD_FILE_ISPAUSE					(BRIUINT32)4//����Ƿ���ͣ�ļ�¼��
#define		QNV_RECORD_FILE_ELAPSE					(BRIUINT32)5//��ȡ�Ѿ�¼����ʱ�䳤��,��λ(s)
#define		QNV_RECORD_FILE_SETVOLUME				(BRIUINT32)6//�����ļ�¼������
#define		QNV_RECORD_FILE_GETVOLUME				(BRIUINT32)7//��ȡ�ļ�¼������
#define		QNV_RECORD_FILE_PATH					(BRIUINT32)8//��ȡ�ļ�¼����·��
#define		QNV_RECORD_FILE_STOP					(BRIUINT32)9//ֹͣĳ���ļ�¼��
#define		QNV_RECORD_FILE_STOPALL					(BRIUINT32)10//ֹͣȫ���ļ�¼��
#define		QNV_RECORD_FILE_COUNT					(BRIUINT32)11//��ȡ����¼��������

#define		QNV_RECORD_FILE_SETROOT					(BRIUINT32)20//����Ĭ��¼��Ŀ¼
#define		QNV_RECORD_FILE_GETROOT					(BRIUINT32)21//��ȡĬ��¼��Ŀ¼

//----------------------------------------------------------
#define		QNV_RECORD_BUF_HWND_START				(BRIUINT32)1//��ʼ����¼�����ڻص�
#define		QNV_RECORD_BUF_HWND_STOP				(BRIUINT32)2//ֹͣĳ������¼�����ڻص�
#define		QNV_RECORD_BUF_HWND_STOPALL				(BRIUINT32)3//ֹͣȫ������¼�����ڻص�
#define		QNV_RECORD_BUF_CALLBACK_START			(BRIUINT32)4//��ʼ����¼���ص�
#define		QNV_RECORD_BUF_CALLBACK_STOP			(BRIUINT32)5//ֹͣĳ������¼���ص�
#define		QNV_RECORD_BUF_CALLBACK_STOPALL			(BRIUINT32)6//ֹͣȫ������¼���ص�
#define		QNV_RECORD_BUF_SETCBSAMPLES				(BRIUINT32)7//���ûص�������,ÿ��8K,�����Ҫ20ms�ص�һ�ξ�����Ϊ20*8=160,/Ĭ��Ϊ20ms�ص�һ��
#define		QNV_RECORD_BUF_GETCBSAMPLES				(BRIUINT32)8//��ȡ���õĻص�������
#define		QNV_RECORD_BUF_ENABLEECHO				(BRIUINT32)9//�򿪹رջص��������Ƿ񾭹���������
#define		QNV_RECORD_BUF_ISENABLEECHO				(BRIUINT32)10//���ص����������������Ƿ��
#define		QNV_RECORD_BUF_PAUSE					(BRIUINT32)11//��ͣ����¼��
#define		QNV_RECORD_BUF_ISPAUSE					(BRIUINT32)12//����Ƿ���ͣ����¼��
#define		QNV_RECORD_BUF_RESUME					(BRIUINT32)13//�ָ�����¼��
#define		QNV_RECORD_BUF_SETVOLUME				(BRIUINT32)14//���û���¼������
#define		QNV_RECORD_BUF_GETVOLUME				(BRIUINT32)15//��ȡ����¼������
#define		QNV_RECORD_BUF_SETWAVEFORMAT			(BRIUINT32)16//����¼���ص������������ʽID,Ĭ��ΪBRI_WAV_FORMAT_PCM8K16B
#define		QNV_RECORD_BUF_GETWAVEFORMAT			(BRIUINT32)17//��ȡ¼���ص������������ʽID

#define		QNV_RECORD_BUF_GETCBMSGID				(BRIUINT32)100//��ѯ����¼���Ĵ��ڻص�����ϢID,Ĭ��ΪBRI_RECBUF_MESSAGE
#define		QNV_RECORD_BUF_SETCBMSGID				(BRIUINT32)101//���û���¼���Ĵ��ڻص�����ϢID,Ĭ��ΪBRI_RECBUF_MESSAGE
//--------------------------------------------------------

//�������
//uConferenceType
#define		QNV_CONFERENCE_CREATE					(BRIUINT32)1//��������
#define		QNV_CONFERENCE_ADDTOCONF				(BRIUINT32)2//����ͨ����ĳ������
#define		QNV_CONFERENCE_GETCONFID				(BRIUINT32)3//��ȡĳ��ͨ���Ļ���ID
#define		QNV_CONFERENCE_SETSPKVOLUME				(BRIUINT32)4//���û�����ĳ��ͨ����������
#define		QNV_CONFERENCE_GETSPKVOLUME				(BRIUINT32)5//��ȡ������ĳ��ͨ����������
#define		QNV_CONFERENCE_SETMICVOLUME				(BRIUINT32)6//���û�����ĳ��ͨ��¼������
#define		QNV_CONFERENCE_GETMICVOLUME				(BRIUINT32)7//��ȡ������ĳ��ͨ��¼������
#define		QNV_CONFERENCE_PAUSE					(BRIUINT32)8//��ͣĳ������
#define		QNV_CONFERENCE_RESUME					(BRIUINT32)9//�ָ�ĳ������
#define		QNV_CONFERENCE_ISPAUSE					(BRIUINT32)10//����Ƿ���ͣ��ĳ������
#define		QNV_CONFERENCE_ENABLESPK				(BRIUINT32)11//�򿪹رջ�����������
#define		QNV_CONFERENCE_ISENABLESPK				(BRIUINT32)12//���������������Ƿ��
#define		QNV_CONFERENCE_ENABLEMIC				(BRIUINT32)13//�򿪹رջ�����˵����
#define		QNV_CONFERENCE_ISENABLEMIC				(BRIUINT32)14//��������˵�����Ƿ��
#define		QNV_CONFERENCE_ENABLEAGC				(BRIUINT32)15//�򿪹ر��Զ�����
#define		QNV_CONFERENCE_ISENABLEAGC				(BRIUINT32)16//����Ƿ�����Զ�����
#define		QNV_CONFERENCE_DELETECHANNEL			(BRIUINT32)17//��ͨ���ӻ�����ɾ��
#define		QNV_CONFERENCE_DELETECONF				(BRIUINT32)18//ɾ��һ������
#define		QNV_CONFERENCE_DELETEALLCONF			(BRIUINT32)19//ɾ��ȫ������
#define		QNV_CONFERENCE_GETCONFCOUNT				(BRIUINT32)20//��ȡ��������
#define		QNV_CONFERENCE_SETJITTERBUFSIZE			(BRIUINT32)21//���û��鶯̬���峤��
#define		QNV_CONFERENCE_GETJITTERBUFSIZE			(BRIUINT32)22//��ȡ���鶯̬���峤��

#define		QNV_CONFERENCE_RECORD_START				(BRIUINT32)30//��ʼ¼��
#define		QNV_CONFERENCE_RECORD_PAUSE				(BRIUINT32)31//��ͣ¼��
#define		QNV_CONFERENCE_RECORD_RESUME			(BRIUINT32)32//�ָ�¼��
#define		QNV_CONFERENCE_RECORD_ISPAUSE			(BRIUINT32)33//����Ƿ���ͣ¼��
#define		QNV_CONFERENCE_RECORD_FILEPATH			(BRIUINT32)34//��ȡ¼���ļ�·��
#define		QNV_CONFERENCE_RECORD_ISSTART			(BRIUINT32)35//�������Ƿ��Ѿ�������¼��
#define		QNV_CONFERENCE_RECORD_STOP				(BRIUINT32)36//ָֹͣ������¼��
#define		QNV_CONFERENCE_RECORD_STOPALL			(BRIUINT32)37//ֹͣȫ������¼��
//--------------------------------------------------------


//�����㲥
#define		QNV_BROADCAST_SEND_START				(BRIUINT32)1//��ʼ�㲥
#define		QNV_BROADCAST_SEND_STOP					(BRIUINT32)2//ֹͣ�㲥
#define		QNV_BROADCAST_SEND_ADDADDR				(BRIUINT32)3//����Ŀ���ַ
#define		QNV_BROADCAST_SEND_DELETEADDR			(BRIUINT32)4//ɾ��Ŀ���ַ
#define		QNV_BROADCAST_SEND_PAUSE				(BRIUINT32)5//��ͣ�㲥
#define		QNV_BROADCAST_SEND_RESUME				(BRIUINT32)6//�ָ��㲥
#define		QNV_BROADCAST_SEND_ISPAUSE				(BRIUINT32)7//����Ƿ���ͣ�˹㲥
#define		QNV_BROADCAST_SEND_SETVOLUME			(BRIUINT32)8//���ù㲥����
#define		QNV_BROADCAST_SEND_GETVOLUME			(BRIUINT32)9//��ȡ�㲥����

#define		QNV_BROADCAST_RECV_START				(BRIUINT32)30//��ʼ����
#define		QNV_BROADCAST_RECV_STOP					(BRIUINT32)31//ֹͣ����
#define		QNV_BROADCAST_RECV_SETVOLUME			(BRIUINT32)32//���ý�������
#define		QNV_BROADCAST_RECV_GETVOLUME			(BRIUINT32)33//��ȡ��������
//

//speech����ʶ��
#define		QNV_SPEECH_CONTENTLIST					(BRIUINT32)1//����ʶ���������б�
#define		QNV_SPEECH_STARTSPEECH					(BRIUINT32)2//��ʼʶ��
#define		QNV_SPEECH_ISSPEECH						(BRIUINT32)3//����Ƿ�����ʶ��
#define		QNV_SPEECH_STOPSPEECH					(BRIUINT32)4//ֹͣʶ��
#define		QNV_SPEECH_GETRESULT					(BRIUINT32)5//��ȡʶ���Ľ��,ʹ�÷��ص�ַ��ʽ
#define		QNV_SPEECH_GETRESULTEX					(BRIUINT32)6//��ȡʶ���Ľ��,ʹ�ø����ڴ淽ʽ
#define		QNV_SPEECH_STARTSPEECHFILE				(BRIUINT32)7//ʶ���ļ�����

//------------------------------------------------------------

//����ģ��ӿ�
#define		QNV_FAX_LOAD							(BRIUINT32)1//������������ģ��
#define		QNV_FAX_UNLOAD							(BRIUINT32)2//ж�ش���ģ��
#define		QNV_FAX_STARTSEND						(BRIUINT32)3//��ʼ���ʹ���
#define		QNV_FAX_STOPSEND						(BRIUINT32)4//ֹͣ���ʹ���
#define		QNV_FAX_STARTRECV						(BRIUINT32)5//��ʼ���մ���
#define		QNV_FAX_STOPRECV						(BRIUINT32)6//ֹͣ���մ���
#define		QNV_FAX_STOP							(BRIUINT32)7//ֹͣȫ��
#define		QNV_FAX_PAUSE							(BRIUINT32)8//��ͣ
#define		QNV_FAX_RESUME							(BRIUINT32)9//�ָ�
#define		QNV_FAX_ISPAUSE							(BRIUINT32)10//�Ƿ���ͣ
#define		QNV_FAX_TYPE							(BRIUINT32)11//����״̬�ǽ��ܻ��߷���
#define		QNV_FAX_TRANSMITSIZE					(BRIUINT32)12//�Ѿ����͵�ͼ�����ݴ�С
#define		QNV_FAX_IMAGESIZE						(BRIUINT32)13//�ܹ���Ҫ����ͼ�����ݴ�С
#define		QNV_FAX_SAVESENDFILE					(BRIUINT32)14//���淢�͵Ĵ���ͼƬ
//----------------------------------------------------------

//����event
//ueventType
#define		QNV_EVENT_POP							(BRIUINT32)1//��ȡ���Զ�ɾ����ǰ�¼�,pValue->PBRI_EVENT
#define		QNV_EVENT_POPEX							(BRIUINT32)2//��ȡ���Զ�ɾ����ǰ�¼�,pValue->�ַ��ָ���ʽ:chid,type,handle,result,data
#define		QNV_EVENT_TYPE							(BRIUINT32)3//��ȡ�¼�����,��ȡ�󲻻��Զ�ɾ������ȡ�ɹ���ʹ�� QNV_EVENT_REMOVEɾ�����¼�
#define		QNV_EVENT_HANDLE						(BRIUINT32)4//��ȡ�¼��ľ����Ϣ
#define		QNV_EVENT_RESULT						(BRIUINT32)5//��ȡ�¼���ֵ
#define		QNV_EVENT_PARAM							(BRIUINT32)6//��ȡ�¼�����ֵ
#define		QNV_EVENT_DATA							(BRIUINT32)7//��ȡ�¼�����
#define		QNV_EVENT_DATAEX						(BRIUINT32)8//��ȡ�¼���������

#define		QNV_EVENT_REMOVE						(BRIUINT32)20//ɾ�����ϵ��¼�
#define		QNV_EVENT_REMOVEALL						(BRIUINT32)21//ɾ�������¼�

#define		QNV_EVENT_REGWND						(BRIUINT32)30//ע�������Ϣ�Ĵ��ھ��
#define		QNV_EVENT_UNREGWND						(BRIUINT32)31//ɾ��������Ϣ�Ĵ��ھ��
#define		QNV_EVENT_REGCBFUNC						(BRIUINT32)32//ע���¼��ص�����()
#define		QNV_EVENT_REGCBFUNCEX					(BRIUINT32)33//ע���¼��ص�����(�ṹ�巽ʽ)
#define		QNV_EVENT_UNREGCBFUNC					(BRIUINT32)34//ɾ���¼��ص�����

#define		QNV_EVENT_GETEVENTMSGID					(BRIUINT32)100//��ѯ���ڻص�����ϢID,Ĭ��ΪBRI_EVENT_MESSAGE
#define		QNV_EVENT_SETEVENTMSGID					(BRIUINT32)101//���ô��ڻص�����ϢID,Ĭ��ΪBRI_EVENT_MESSAGE
//-----------------------------------------------------------

//����general
//uGeneralType
#define		QNV_GENERAL_STARTDIAL					(BRIUINT32)1//��ʼ����
#define		QNV_GENERAL_SENDNUMBER					(BRIUINT32)2//���β���
#define		QNV_GENERAL_REDIAL						(BRIUINT32)3//�ز����һ�κ��еĺ���,�����˳���ú��뱻�ͷ�
#define		QNV_GENERAL_STOPDIAL					(BRIUINT32)4//ֹͣ����
#define		QNV_GENERAL_ISDIALING					(BRIUINT32)5//�Ƿ��ڲ���

#define		QNV_GENERAL_STARTRING					(BRIUINT32)10//phone������
#define		QNV_GENERAL_STOPRING					(BRIUINT32)11//phone������ֹͣ
#define		QNV_GENERAL_ISRINGING					(BRIUINT32)12//phone���Ƿ�������

#define		QNV_GENERAL_STARTFLASH					(BRIUINT32)20//�Ĳ��
#define		QNV_GENERAL_STOPFLASH					(BRIUINT32)21//�Ĳ��ֹͣ
#define		QNV_GENERAL_ISFLASHING					(BRIUINT32)22//�Ƿ������Ĳ��

#define		QNV_GENERAL_STARTREFUSE					(BRIUINT32)30//�ܽӵ�ǰ����
#define		QNV_GENERAL_STOPREFUSE					(BRIUINT32)31//��ֹ�ܽӲ���
#define		QNV_GENERAL_ISREFUSEING					(BRIUINT32)32//�Ƿ����ھܽӵ�ǰ����

#define		QNV_GENERAL_GETCALLIDTYPE				(BRIUINT32)50//��ȡ���κ���������������
#define		QNV_GENERAL_GETCALLID					(BRIUINT32)51//��ȡ���κ�����������
#define		QNV_GENERAL_GETTELDIALCODE				(BRIUINT32)52//��ȡ���ε绰�������ĺ���,return buf
#define		QNV_GENERAL_GETTELDIALCODEEX			(BRIUINT32)53//��ȡ���ε绰�������ĺ���,outbuf
#define		QNV_GENERAL_RESETTELDIALBUF				(BRIUINT32)54//��յ绰���ĺ��뻺��
#define		QNV_GENERAL_GETTELDIALLEN				(BRIUINT32)55//�绰���Ѳ��ĺ��볤��

#define		QNV_GENERAL_STARTSHARE					(BRIUINT32)60//�����豸�������
#define		QNV_GENERAL_STOPSHARE					(BRIUINT32)61//ֹͣ�豸�������
#define		QNV_GENERAL_ISSHARE						(BRIUINT32)62//�Ƿ������豸�������ģ��

#define		QNV_GENERAL_ENABLECALLIN				(BRIUINT32)70//��ֹ/�������ߺ���
#define		QNV_GENERAL_ISENABLECALLIN				(BRIUINT32)71//�����Ƿ��������
#define		QNV_GENERAL_ISLINEHOOK					(BRIUINT32)72//�����Ƿ�ժ��״̬(�绰��ժ��������line��������ժ������ʾժ��״̬)
#define		QNV_GENERAL_ISLINEFREE					(BRIUINT32)73//�����Ƿ����(û��ժ������û�������ʾ����)

#define		QNV_GENERAL_RESETRINGBACK				(BRIUINT32)80//��λ��⵽�Ļ���,�����������
#define		QNV_GENERAL_CHECKCHANNELID				(BRIUINT32)81//���ͨ��ID�Ƿ�Ϸ�
#define		QNV_GENERAL_CHECKDIALTONE				(BRIUINT32)82//���ժ�����Ƿ��⵽��������
#define		QNV_GENERAL_CHECKSILENCE				(BRIUINT32)83//�����·����
#define		QNV_GENERAL_CHECKVOICE					(BRIUINT32)84//�����·����,�����������ֵ��ʹ��QNV_PARAM_SPEECHSILENCEAM����
#define		QNV_GENERAL_CHECKLINESTATE				(BRIUINT32)85//�����·״̬(�Ƿ����������/�Ƿ�ӷ�)
#define		QNV_GENERAL_GETMAXPOWER					(BRIUINT32)86//��ȡ��ǰ�����������
#define		QNV_GENERAL_GETCHANNELIDOFSERIAL		(BRIUINT32)87//�������кŻ�ȡͨ��ID
#define		QNV_GENERAL_RESETRINGBACKEX				(BRIUINT32)88//���¿�ʼ���Է��ź�,��ϵͳ�����ǲ��Ž���״̬,���ܵ�ǰ״̬�Ƿ��Ѿ�����

#define		QNV_GENERAL_SETUSERVALUE				(BRIUINT32)90//�û��Զ���ͨ������,ϵͳ�˳����Զ��ͷ�
#define		QNV_GENERAL_SETUSERSTRING				(BRIUINT32)91//�û��Զ���ͨ���ַ�,ϵͳ�˳����Զ��ͷ�
#define		QNV_GENERAL_GETUSERVALUE				(BRIUINT32)92//��ȡ�û��Զ���ͨ������
#define		QNV_GENERAL_GETUSERSTRING				(BRIUINT32)93//��ȡ�û��Զ���ͨ���ַ�


#define		QNV_GENERAL_USEREVENT					(BRIUINT32)99//�����û��Զ����¼�
//��ʼ��ͨ��INI�ļ�����
#define		QNV_GENERAL_READPARAM					(BRIUINT32)100//��ȡini�ļ�����ȫ��������ʼ��
#define		QNV_GENERAL_WRITEPARAM					(BRIUINT32)101//�Ѳ���д�뵽ini�ļ�
//

//call log
#define		QNV_CALLLOG_BEGINTIME					(BRIUINT32)1//��ȡ���п�ʼʱ��
#define		QNV_CALLLOG_RINGBACKTIME				(BRIUINT32)2//��ȡ����ʱ��
#define		QNV_CALLLOG_CONNECTEDTIME				(BRIUINT32)3//��ȡ��ͨʱ��
#define		QNV_CALLLOG_ENDTIME						(BRIUINT32)4//��ȡ����ʱ��
#define		QNV_CALLLOG_CALLTYPE					(BRIUINT32)5//��ȡ��������/����/����
#define		QNV_CALLLOG_CALLRESULT					(BRIUINT32)6//��ȡ���н��
#define		QNV_CALLLOG_CALLID						(BRIUINT32)7//��ȡ����
#define		QNV_CALLLOG_CALLRECFILE					(BRIUINT32)8//��ȡ¼���ļ�·��
#define		QNV_CALLLOG_DELRECFILE					(BRIUINT32)9//ɾ����־¼���ļ���Ҫɾ��ǰ������ֹͣ¼��

#define		QNV_CALLLOG_RESET						(BRIUINT32)20//��λ����״̬
#define		QNV_CALLLOG_AUTORESET					(BRIUINT32)21//�Զ���λ
//


//���ߺ��������豸�޹�
//uToolType
#define		QNV_TOOL_PSTNEND						(BRIUINT32)1//���PSTN�����Ƿ��Ѿ�����
#define		QNV_TOOL_CODETYPE						(BRIUINT32)2//�жϺ�������(�ڵ��ֻ�/�̻�)
#define		QNV_TOOL_LOCATION						(BRIUINT32)3//��ȡ�������ڵ���Ϣ
#define		QNV_TOOL_DISKFREESPACE					(BRIUINT32)4//��ȡ��Ӳ��ʣ��ռ�(M)
#define		QNV_TOOL_DISKTOTALSPACE					(BRIUINT32)5//��ȡ��Ӳ���ܹ��ռ�(M)
#define		QNV_TOOL_DISKLIST						(BRIUINT32)6//��ȡӲ���б�
#define		QNV_TOOL_RESERVID1						(BRIUINT32)7//����ID1
#define		QNV_TOOL_RESERVID2						(BRIUINT32)8//����ID2
#define		QNV_TOOL_CONVERTFMT						(BRIUINT32)9//ת�������ļ���ʽ
#define		QNV_TOOL_SELECTDIRECTORY				(BRIUINT32)10//ѡ��Ŀ¼
#define		QNV_TOOL_SELECTFILE						(BRIUINT32)11//ѡ���ļ�
#define		QNV_TOOL_CONVERTTOTIFF					(BRIUINT32)12//ת��ͼƬ������tiff��ʽ,��������������ģ��,֧�ָ�ʽ:(*.doc,*.htm,*.html,*.mht,*.jpg,*.pnp.....)
#define		QNV_TOOL_APMQUERYSUSPEND				(BRIUINT32)13//�Ƿ�����PC�������/����,��USB�豸�����ʹ��
#define		QNV_TOOL_SLEEP							(BRIUINT32)14//�õ��ø÷������̵߳ȴ�N����
#define		QNV_TOOL_SETUSERVALUE					(BRIUINT32)15//�����û��Զ�����Ϣ
#define		QNV_TOOL_GETUSERVALUE					(BRIUINT32)16//��ȡ�û��Զ�����Ϣ
#define		QNV_TOOL_SETUSERVALUEI					(BRIUINT32)17//�����û��Զ�����Ϣ
#define		QNV_TOOL_GETUSERVALUEI					(BRIUINT32)18//��ȡ�û��Զ�����Ϣ
#define		QNV_TOOL_ISFILEEXIST					(BRIUINT32)20//��Ȿ���ļ��Ƿ����
#define		QNV_TOOL_FSKENCODE						(BRIUINT32)21//FSK����
#define		QNV_TOOL_WRITELOG						(BRIUINT32)22//д�ļ���־->userlogĿ¼
//------------------------------------------------------

//�洢����,�����ݽ������õĴ洢��USBоƬ��
#define		QNV_STORAGE_PUBLIC_READ					(BRIUINT32)1//��ȡ������������
#define		QNV_STORAGE_PUBLIC_READSTR				(BRIUINT32)2//��ȡ���������ַ�������,����'\0'�Զ�����
#define		QNV_STORAGE_PUBLIC_WRITE				(BRIUINT32)3//д�빲����������
#define		QNV_STORAGE_PUBLIC_SETREADPWD			(BRIUINT32)4//���ö�ȡ�����������ݵ�����
#define		QNV_STORAGE_PUBLIC_SETWRITEPWD			(BRIUINT32)5//����д�빲���������ݵ�����
#define		QNV_STORAGE_PUBLIC_GETSPACESIZE			(BRIUINT32)6//��ȡ�洢�ռ䳤��

//---����Ϊ�ڲ�ʹ�ýӿ�
#define		QNV_STORAGE_GLOBALINFO_READ				(BRIUINT32)11//��ȡ
#define		QNV_STORAGE_GLOBALINFO_READSTR			(BRIUINT32)12//��ȡ�ַ���
#define		QNV_STORAGE_GLOBALINFO_WRITE			(BRIUINT32)13//д��
#define		QNV_STORAGE_GLOBALINFO_SETREADPWD		(BRIUINT32)14//���ö�ȡ�������ݵ�����
#define		QNV_STORAGE_GLOBALINFO_SETWRITEPWD		(BRIUINT32)15//����д���������ݵ�����
#define		QNV_STORAGE_GLOBALINFO_GETSPACESIZE		(BRIUINT32)16//��ȡ�洢�ռ䳤��

#define		QNV_STORAGE_PRIVATEINFO_READ			(BRIUINT32)21//��ȡ
#define		QNV_STORAGE_PRIVATEINFO_READSTR			(BRIUINT32)22//��ȡ�ַ���
#define		QNV_STORAGE_PRIVATEINFO_WRITE			(BRIUINT32)23//д��
#define		QNV_STORAGE_PRIVATEINFO_SETREADPWD		(BRIUINT32)24//���ö�ȡ�������ݵ�����
#define		QNV_STORAGE_PRIVATEINFO_SETWRITEPWD		(BRIUINT32)25//����д���������ݵ�����
#define		QNV_STORAGE_PRIVATEINFO_GETSPACESIZE	(BRIUINT32)26//��ȡ�洢�ռ䳤��

#define		QNV_STORAGE_OEMINFO_READ				(BRIUINT32)31//��ȡ
#define		QNV_STORAGE_OEMINFO_READSTR				(BRIUINT32)32//��ȡ�ַ���
#define		QNV_STORAGE_OEMINFO_WRITE				(BRIUINT32)33//д��
#define		QNV_STORAGE_OEMINFO_SETREADPWD			(BRIUINT32)34//���ö�ȡ�������ݵ�����
#define		QNV_STORAGE_OEMINFO_SETWRITEPWD			(BRIUINT32)35//����д���������ݵ�����
#define		QNV_STORAGE_OEMINFO_GETSPACESIZE		(BRIUINT32)36//��ȡ�洢�ռ䳤��

#define		QNV_STORAGE_DEVINFO_READ				(BRIUINT32)41//��ȡ
#define		QNV_STORAGE_DEVINFO_READSTR				(BRIUINT32)42//��ȡ�ַ���
#define		QNV_STORAGE_DEVINFO_WRITE				(BRIUINT32)43//д��
#define		QNV_STORAGE_DEVINFO_SETREADPWD			(BRIUINT32)44//���ö�ȡ�������ݵ�����
#define		QNV_STORAGE_DEVINFO_SETWRITEPWD			(BRIUINT32)45//����д���������ݵ�����
#define		QNV_STORAGE_DEVINFO_GETSPACESIZE		(BRIUINT32)46//��ȡ�洢�ռ䳤��
//--------------------------------------------------------------------------------------


//Զ���ļ�����
//RemoteType
#define		QNV_REMOTE_UPLOAD_START					(BRIUINT32)1//�ϴ��ļ���WEB������(httpЭ��)
#define		QNV_REMOTE_UPLOAD_DATA					(BRIUINT32)2//�ϴ��ַ����ݵ�WEB������(send/post)(����)
#define		QNV_REMOTE_UPLOAD_STOP					(BRIUINT32)3//�ϴ��ļ���WEB������(httpЭ��)
#define		QNV_REMOTE_UPLOAD_LOG					(BRIUINT32)4//�����ϴ���ǰû�гɹ��ļ�¼
#define		QNV_REMOTE_UPLOAD_TOTALSIZE				(BRIUINT32)5//��ȡ��Ҫ�ϴ����ܹ�����
#define		QNV_REMOTE_UPLOAD_TRANSIZE				(BRIUINT32)6//��ȡ�Ѿ��ϴ��ĳ���
#define		QNV_REMOTE_UPLOAD_CLEARLOG				(BRIUINT32)7//ɾ������δ�ɹ�����־
#define		QNV_REMOTE_UPLOAD_COUNT					(BRIUINT32)8//
#define		QNV_REMOTE_UPLOAD_STOPALL				(BRIUINT32)9//

#define		QNV_REMOTE_DOWNLOAD_START				(BRIUINT32)20//��ʼ����Զ���ļ�
#define		QNV_REMOTE_DOWNLOAD_STOP				(BRIUINT32)21//ֹͣ����Զ���ļ�
#define		QNV_REMOTE_DOWNLOAD_TOTALSIZE			(BRIUINT32)22//���ص��ܹ�����
#define		QNV_REMOTE_DOWNLOAD_TRANSIZE			(BRIUINT32)23//�Ѿ����صĳ���
#define		QNV_REMOTE_DOWNLOAD_COUNT				(BRIUINT32)24//
#define		QNV_REMOTE_DOWNLOAD_STOPALL				(BRIUINT32)25//

#define		QNV_REMOTE_SETCOOKIE					(BRIUINT32)40//����HTTP���ӵ�COOKIE
//------------------------------------------------------

//CC����
#define		QNV_CCCTRL_SETLICENSE					(BRIUINT32)1//����license
#define		QNV_CCCTRL_SETSERVER					(BRIUINT32)2//���÷�����IP��ַ
#define		QNV_CCCTRL_LOGIN						(BRIUINT32)3//��½
#define		QNV_CCCTRL_LOGOUT						(BRIUINT32)4//�˳�
#define		QNV_CCCTRL_ISLOGON						(BRIUINT32)5//�Ƿ��½�ɹ���
#define		QNV_CCCTRL_REGCC						(BRIUINT32)6//ע��CC����
#define		QNV_CCCTRL_STARTFINDSERVER				(BRIUINT32)7//�Զ�����������CC������,255.255.255.255��ʾֻ�㲥ģʽ/0.0.0.0ֻ��Ѱģʽ/�ձ�ʾ�㲥+��Ѱģʽ/����Ϊָ��IP��ʽ
#define		QNV_CCCTRL_STOPFINDSERVER				(BRIUINT32)8//ֹͣ����
#define		QNV_CCCTRL_MODIFYPWD					(BRIUINT32)9//�޸ĵ�½����
#define		QNV_CCCTRL_SETFINDSVRTIMEOUT			(BRIUINT32)10//���������ĳ�ʱʱ��
#define		QNV_CCCTRL_GETFINDSVRTIMEOUT			(BRIUINT32)11//��ȡ�����ĳ�ʱʱ��
//
//����
#define		QNV_CCCTRL_CALL_START					(BRIUINT32)1//����CC
#define		QNV_CCCTRL_CALL_VOIP					(BRIUINT32)2//VOIP�����̻�
#define		QNV_CCCTRL_CALL_STOP					(BRIUINT32)3//ֹͣ����
#define		QNV_CCCTRL_CALL_ACCEPT					(BRIUINT32)4//��������
#define		QNV_CCCTRL_CALL_BUSY					(BRIUINT32)5//����æ��ʾ
#define		QNV_CCCTRL_CALL_REFUSE					(BRIUINT32)6//�ܽ�
#define		QNV_CCCTRL_CALL_STARTPLAYFILE			(BRIUINT32)7//�����ļ�
#define		QNV_CCCTRL_CALL_STOPPLAYFILE			(BRIUINT32)8//ֹͣ�����ļ�
#define		QNV_CCCTRL_CALL_STARTRECFILE			(BRIUINT32)9//��ʼ�ļ�¼��
#define		QNV_CCCTRL_CALL_STOPRECFILE				(BRIUINT32)10//ֹͣ�ļ�¼��
#define		QNV_CCCTRL_CALL_HOLD					(BRIUINT32)11//����ͨ��,��Ӱ�첥���ļ�
#define		QNV_CCCTRL_CALL_UNHOLD					(BRIUINT32)12//�ָ�ͨ��
#define		QNV_CCCTRL_CALL_SWITCH					(BRIUINT32)13//����ת�Ƶ�����CC

#define		QNV_CCCTRL_CALL_CONFHANDLE				(BRIUINT32)20//��ȡ���о�����ڵĻ�����

//
//��Ϣ/����
#define		QNV_CCCTRL_MSG_SENDMSG					(BRIUINT32)1//������Ϣ
#define		QNV_CCCTRL_MSG_SENDCMD					(BRIUINT32)2//��������
#define		QNV_CCCTRL_MSG_REPLYWEBIM				(BRIUINT32)3//�ظ�WEB801��Ϣ
#define		QNV_CCCTRL_MSG_REPLYWEBCHECK			(BRIUINT32)4//Ӧ��WEB801����״̬��ѯ
#define		QNV_CCCTRL_MSG_QUERYIPINFO				(BRIUINT32)5//��ѯCC������IP��ַ��Ϣ
//
//
//����
#define		QNV_CCCTRL_CONTACT_ADD					(BRIUINT32)1//���Ӻ���
#define		QNV_CCCTRL_CONTACT_DELETE				(BRIUINT32)2//ɾ������
#define		QNV_CCCTRL_CONTACT_ACCEPT				(BRIUINT32)3//���ܺ���
#define		QNV_CCCTRL_CONTACT_REFUSE				(BRIUINT32)4//�ܾ�����
#define		QNV_CCCTRL_CONTACT_GET					(BRIUINT32)5//��ȡ����״̬
//
//

//������Ϣ/�Լ�����Ϣ
#define		QNV_CCCTRL_CCINFO_OWNERCC				(BRIUINT32)1//��ȡ���˵�½��CC
#define		QNV_CCCTRL_CCINFO_NICK					(BRIUINT32)2//��ȡCC���ǳ�,���û������CC�ͱ�ʾ��ȡ���˵��ǳ�
#define		QNV_CCCTRL_CCINFO_PWD					(BRIUINT32)3//��ȡ���������
#define		QNV_CCCTRL_CCINFO_CRYPTPWD				(BRIUINT32)4//��ȡ���ܺ������,��½�ɹ�����ܻ�ȡ�����򷵻�ʧ��
//
//------------------------------------------------------------

//socket �ն˿���
//�ڲ�ʹ�ýӿ�
#define		QNV_SOCKET_CLIENT_CONNECT				(BRIUINT32)1//���ӵ�������
#define		QNV_SOCKET_CLIENT_DISCONNECT			(BRIUINT32)2//�Ͽ�������
#define		QNV_SOCKET_CLIENT_STARTRECONNECT		(BRIUINT32)3//�Զ�����������
#define		QNV_SOCKET_CLIENT_STOPRECONNECT			(BRIUINT32)4//ֹͣ�Զ�����������
#define		QNV_SOCKET_CLIENT_ISCONNECTED			(BRIUINT32)5//����Ƿ��Ѿ����ӵ���������
#define		QNV_SOCKET_CLIENT_SENDDATA				(BRIUINT32)6//������������
#define		QNV_SOCKET_CLIENT_APPENDDATA			(BRIUINT32)7//׷�ӷ������ݵ����У�������Է��;���������

//socket �������˿���
//�ڲ�ʹ�ýӿ�
//UDPģ��
#define		QNV_SOCKET_UDP_OPEN						(BRIUINT32)1//��UDPģ��
#define		QNV_SOCKET_UDP_CLOSE					(BRIUINT32)2//�ر�UDPģ��
#define		QNV_SOCKET_UDP_ISOPEN					(BRIUINT32)3//�Ƿ����UDPģ��
#define		QNV_SOCKET_UDP_SENDDATA					(BRIUINT32)4//��Ŀ���ַ/�˿ڷ�������
#define		QNV_SOCKET_UDP_SETSVRNAME				(BRIUINT32)5//������������(ָ��������)
#define		QNV_SOCKET_UDP_STARTFINDSVR				(BRIUINT32)6//����ָ������������
#define		QNV_SOCKET_UDP_STOPFINDSVR				(BRIUINT32)7//ֹͣ����
//

//AUDIO ��������ģ��
#define		QNV_AUDRV_INSTALL						(BRIUINT32)1//��װ������������
#define		QNV_AUDRV_UNINSTALL						(BRIUINT32)2//ɾ��������������
#define		QNV_AUDRV_ISINSTALL						(BRIUINT32)3//���ICC301���������Ƿ�װ��
#define		QNV_AUDRV_SETWAVEOUTID					(BRIUINT32)4//����ICC301�����������������Ŀ��USBͨ��ID(0->N),Ĭ��Ϊ��һ��ͨ��(0),���ı������������
#define		QNV_AUDRV_SETWAVEINID					(BRIUINT32)5//����ICC301�����������������USBͨ��ID(0->N),Ĭ��Ϊ��һ��ͨ��(0),���ı������������
#define		QNV_AUDRV_SWITCHWAVEOUTID				(BRIUINT32)6//ת��ICC301���������������������ͨ��
#define		QNV_AUDRV_SWITCHWAVEINID				(BRIUINT32)7//ת��ICC301���������������������ͨ��
#define		QNV_AUDRV_WAVEOUTCOUNT					(BRIUINT32)8//�Ѿ��򿪵�waveout����
#define		QNV_AUDRV_WAVEINCOUNT					(BRIUINT32)9//�Ѿ��򿪵�wavein����
//

//�ӿں����б�
//
// ���豸
BRIINT32	BRISDKLIBAPI	QNV_OpenDevice(BRIUINT32 uDevType,BRIUINT32 uValue,BRICHAR8 *pValue);
// �ر��豸
BRIINT32	BRISDKLIBAPI	QNV_CloseDevice(BRIUINT32 uDevType,BRIUINT32 uValue);
// set dev ctrl
BRIINT32	BRISDKLIBAPI	QNV_SetDevCtrl(BRIINT16 nChannelID,BRIUINT32 uCtrlType,BRIINT32 nValue);
// get dev ctrl
BRIINT32	BRISDKLIBAPI	QNV_GetDevCtrl(BRIINT16 nChannelID,BRIUINT32 uCtrlType);

// set param
BRIINT32	BRISDKLIBAPI	QNV_SetParam(BRIINT16 nChannelID,BRIUINT32 uParamType,BRIINT32 nValue);

// get param
BRIINT32	BRISDKLIBAPI	QNV_GetParam(BRIINT16 nChannelID,BRIUINT32 uParamType);

// play file
BRIINT32	BRISDKLIBAPI	QNV_PlayFile(BRIINT16 nChannelID,BRIUINT32 uPlayType,BRIINT32 nValue,BRIINT32 nValueEx,BRICHAR8 *pValue);

// play buf
BRIINT32	BRISDKLIBAPI	QNV_PlayBuf(BRIINT16 nChannelID,BRIUINT32 uPlayType,BRIINT32 nValue,BRIINT32 nValueEx,BRICHAR8 *pValue);

// play multifile
BRIINT32	BRISDKLIBAPI	QNV_PlayMultiFile(BRIINT16 nChannelID,BRIUINT32 uPlayType,BRIINT32 nValue,BRIINT32 nValueEx,BRICHAR8 *pValue);
// play string
BRIINT32	BRISDKLIBAPI	QNV_PlayString(BRIINT16 nChannelID,BRIUINT32 uPlayType,BRIINT32 nValue,BRIINT32 nValueEx,BRICHAR8 *pValue);

// record file
BRIINT32	BRISDKLIBAPI	QNV_RecordFile(BRIINT16 nChannelID,BRIUINT32 uRecordType,BRIINT32 nValue,BRIINT32 nValueEx,BRICHAR8 *pValue);

// record buf
BRIINT32	BRISDKLIBAPI	QNV_RecordBuf(BRIINT16 nChannelID,BRIUINT32 uRecordType,BRIINT32 nValue,BRIINT32 nValueEx,BRICHAR8 *pValue);

// conference
BRIINT32	BRISDKLIBAPI	QNV_Conference(BRIINT16 nChannelID,BRIINT32 nConfID,BRIUINT32 uConfType,BRIINT32 nValue,BRICHAR8 *pValue);

// broadcast
BRIINT32	BRISDKLIBAPI	QNV_Broadcast(BRIINT16 nChannelID,BRIUINT32 uBroadType,BRIINT32 nValue,BRICHAR8 *pValue);

// speech
BRIINT32	BRISDKLIBAPI	QNV_Speech(BRIINT16 nChannelID,BRIUINT32 uSpeechType,BRIINT32 nValue,BRICHAR8 *pValue);

// fax
BRIINT32	BRISDKLIBAPI	QNV_Fax(BRIINT16 nChannelID,BRIUINT32 uFaxType,BRIINT32 nValue,BRICHAR8 *pValue);

// event
BRIINT32	BRISDKLIBAPI	QNV_Event(BRIINT16 nChannelID,BRIUINT32 uEventType,BRIINT32 nValue,BRICHAR8 *pInValue,BRICHAR8 *pOutValue,BRIINT32 nBufSize);

// general
BRIINT32	BRISDKLIBAPI	QNV_General(BRIINT16 nChannelID,BRIUINT32 uGeneralType,BRIINT32 nValue,BRICHAR8 *pValue);

// pstn call log
BRIINT32	BRISDKLIBAPI	QNV_CallLog(BRIINT16 nChannelID,BRIUINT32 uLogType,BRICHAR8 *pValue,BRIINT32 nValue);

// devinfo
BRIINT32	BRISDKLIBAPI	QNV_DevInfo(BRIINT16 nChannelID,BRIUINT32 uDevInfoType);

// storage read write
BRIINT32	BRISDKLIBAPI	QNV_Storage(BRIINT16 nDevID,BRIUINT32 uOPType,BRIUINT32 uSeek,BRICHAR8 *pPwd,BRICHAR8 *pValue,BRIINT32 nBufSize);

// tool
BRIINT32	BRISDKLIBAPI	QNV_Tool(BRIUINT32 uToolType,BRIINT32 nValue,BRICHAR8 *pInValue,BRICHAR8 *pInValueEx,BRICHAR8 *pOutValue,BRIINT32 nBufSize);

// remote
BRIINT32	BRISDKLIBAPI	QNV_Remote(BRIUINT32 uRemoteType,BRIINT32 nValue,BRICHAR8 *pInValue,BRICHAR8 *pInValueEx,BRICHAR8 *pOutValue,BRIINT32 nBufSize);

// CC ctrl 
BRIINT32	BRISDKLIBAPI	QNV_CCCtrl(BRIUINT32 uCtrlType,BRICHAR8 *pInValue,BRIINT32 nValue);
// CC Call
BRIINT32	BRISDKLIBAPI	QNV_CCCtrl_Call(BRIUINT32 uCallType,BRIINT32 lHandle,BRICHAR8 *pInValue,BRIINT32 nValue);
// CC msg
BRIINT32	BRISDKLIBAPI	QNV_CCCtrl_Msg(BRIUINT32 uMsgType,BRICHAR8 *pDestCC,BRICHAR8 *pMsgValue,BRICHAR8 *pParam,BRIINT32 nReserv);
//
// CC contact
BRIINT32	BRISDKLIBAPI	QNV_CCCtrl_Contact(BRIUINT32 uContactType,BRICHAR8 *pDestCC,BRICHAR8 *pValue);
//
// CC contact info
BRIINT32	BRISDKLIBAPI	QNV_CCCtrl_CCInfo(BRIUINT32 uInfoType,BRICHAR8 *pDestCC,BRICHAR8 *pOutValue,BRIINT32 nBufSize);
//
//Զ��C/S SOCKET
//�ն�
BRIINT32	BRISDKLIBAPI	QNV_Socket_Client(BRIUINT32 uSktType,BRIINT32 nHandle,BRIINT32 nValue,BRICHAR8 *pInValue,BRIINT32 nInValueLen);

//��������
BRIINT32	BRISDKLIBAPI	QNV_Socket_Server(BRIUINT32 uSktType,BRIINT32 nValue,BRICHAR8 *pInValue,BRIINT32 nInValueLen);

//UDPģ��
BRIINT32	BRISDKLIBAPI	QNV_Socket_UDP(BRIUINT32 uUDPType,BRIINT32 nValue,BRICHAR8 *pInAddr,BRICHAR8 *pInValue,BRIINT32 nInValueLen);

//AuDrv������������
BRIINT32	BRISDKLIBAPI	QNV_Audrv(BRIUINT32 uAudioType,BRIINT32 nValue,BRICHAR8 *pInValue,BRICHAR8 *pOutValue,BRIINT32 nBufSize);

//��ȡ���һ�κ�����������ֵ
BRIINT32	BRISDKLIBAPI	QNV_GetLastError();
#ifdef __cplusplus
}
#endif

#endif