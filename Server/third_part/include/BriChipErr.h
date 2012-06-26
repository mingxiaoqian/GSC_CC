#ifndef __BRICHIPERR_H__
#define __BRICHIPERR_H__
//API����ID����

//USB�豸���� ���صĴ���ID
#define		BCERR_BASE					(-9)  //��С����ֵ
#define		BCERR_INVALIDHANDLE			(-9)  //���Ϸ��ľ��
#define		BCERR_NOPLAYHANDLE			(-10) //û�п��в��ž��
#define		BCERR_OPENFILEFAILED		(-11) //���ļ�ʧ��
#define		BCERR_READFILEFAILED		(-12) //��ȡ�ļ����ݴ���
#define		BCERR_WAVHEADERFAILED		(-13) //�����ļ�ͷʧ��
#define		BCERR_NOTSUPPORTFORMAT		(-14) //������ʽ��֧��
#define		BCERR_NORECHANDLE			(-15) //û���㹻��¼�����
#define		BCERR_CREATEFILEFAILED		(-16) //����¼���ļ�ʧ��,����ļ�·����ʽ
#define		BCERR_NOBUFSIZE				(-17) //���岻��
#define		BCERR_PARAMERR				(-18) //��������
#define		BCERR_INVALIDTYPE			(-19) //���Ϸ��Ĳ�������		
#define		BCERR_INVALIDCHANNEL		(-20) //���Ϸ���ͨ��ID
#define		BCERR_ISMULTIPLAYING		(-21) //���ڶ��ļ�����,����ֹͣ����
#define		BCERR_ISCONFRECING			(-22) //���ڻ���¼��,����ֹͣ¼��
#define		BCERR_INVALIDCONFID			(-23) //����Ļ���ID��
#define		BCERR_NOTCREATECONF			(-24) //����ģ�黹δ����
#define		BCERR_NOTCREATEMULTIPLAY	(-25) //û�п�ʼ���ļ�����
#define		BCERR_NOTCREATESTRINGPLAY	(-26) //û�п�ʼ�ַ�����
#define		BCERR_ISFLASHING			(-27) //�����Ĳ��,����ֹͣ
#define		BCERR_FLASHNOTLINE			(-28) //�豸û�н�ͨ��·�����Ĳ��
#define		BCERR_NOTLOADFAXMODULE		(-29) //δ��������ģ��
#define		BCERR_FAXMODULERUNING		(-30) //��������ʹ�ã�����ֹͣ
#define		BCERR_VALIDLICENSE			(-31) //�����license
#define		BCERR_ISFAXING				(-32) //���ڴ��治����һ�
#define		BCERR_CCMSGOVER				(-33) //CC��Ϣ����̫��
#define		BCERR_CCCMDOVER				(-34) //CC�����̫��
#define		BCERR_INVALIDSVR			(-35) //����������
#define		BCERR_INVALIDFUNC			(-36) //δ�ҵ�ָ������ģ��
#define		BCERR_INVALIDCMD			(-37) //δ�ҵ�ָ������
#define		BCERR_UNSUPPORTFUNC			(-38) //�豸��֧�ָù���unsupport func
#define		BCERR_DEVNOTOPEN			(-39) //δ��ָ���豸
#define		BCERR_INVALIDDEVID			(-40) //���Ϸ���ID
#define		BCERR_INVALIDPWD			(-41) //�������
#define		BCERR_READSTOREAGEERR		(-42) //��ȡ�洢����
#define		BCERR_INVALIDPWDLEN			(-43) //���볤��̫��
#define		BCERR_NOTFORMAT				(-44) //flash��δ��ʽ��
#define		BCERR_FORMATFAILED			(-45) //��ʽ��ʧ��
#define		BCERR_NOTENOUGHSPACE		(-46) //д���FLASH����̫��,�洢�ռ䲻��
#define		BCERR_WRITESTOREAGEERR		(-47) //д��洢����
#define		BCERR_NOTSUPPORTCHECK		(-48) //ͨ����֧����·��⹦��
#define		BCERR_INVALIDPATH			(-49) //���Ϸ����ļ�·��
#define		BCERR_AUDRVINSTALLED		(-50) //�������������Ѿ���װ
#define		BCERR_AUDRVUSEING			(-51) //������������ʹ�ò��ܸ���,���˳�����ʹ�ø���������������������������ٰ�װ
#define		BCERR_AUDRVCOPYFAILED		(-52) //�������������ļ�����ʧ��

#define		ERROR_INVALIDDLL			(-198)//���Ϸ���DLL�ļ�
#define		ERROR_NOTINIT				(-199)//��û�г�ʼ���κ��豸
#define		BCERR_UNKNOW				(-200)//δ֪����

//-------------------------------------------------------
//CC ���� �ص��Ĵ���ID
#define TMMERR_BASE 0

#define TMMERR_SUCCESS			(DWORD)0
#define TMMERR_FAILED			(DWORD)(-1)//�쳣����
#define TMMERR_ERROR			(TMMERR_BASE + 1)//��������
#define TMMERR_SERVERDEAD		(TMMERR_BASE + 2)//������û��Ӧ
#define TMMERR_INVALIDUIN		(TMMERR_BASE + 3)//���Ϸ���
#define TMMERR_INVALIDUSER		(TMMERR_BASE + 4)//���Ϸ����û�
#define TMMERR_INVALIDPASS		(TMMERR_BASE + 5)//���Ϸ�������
#define TMMERR_DUPLOGON			(TMMERR_BASE + 6)//�ظ���½
#define TMMERR_INVALIDCONTACT	(TMMERR_BASE + 7)//��ӵĺ���CC������
#define TMMERR_USEROFFLINE		(TMMERR_BASE + 8)//�û�������
#define TMMERR_INVALIDTYPE		(TMMERR_BASE + 9)//��Ч
#define TMMERR_EXPIRED			(TMMERR_BASE + 14)//��ʱ
#define TMMERR_INVALIDDLL		(TMMERR_BASE + 15)//��Ч
#define TMMERR_OVERRUN			(TMMERR_BASE + 16)//��Ч
#define TMMERR_NODEVICE			(TMMERR_BASE + 17)//���豸ʧ��
#define TMMERR_DEVICEBUSY		(TMMERR_BASE + 18)//��������ʱ�豸æ
#define	TMMERR_NOTLOGON			(TMMERR_BASE + 19)//δ��½
#define TMMERR_ADDSELF			(TMMERR_BASE + 20)//���������Լ�Ϊ����
#define TMMERR_ADDDUP			(TMMERR_BASE + 21)//���Ӻ����ظ�
#define TMMERR_SESSIONBUSY		(TMMERR_BASE + 23)//��Ч
#define TMMERR_NOINITIALIZE		(TMMERR_BASE + 25)//��δ��ʼ��
#define TMMERR_NOANSWER			(TMMERR_BASE + 26)//��Ч
#define TMMERR_TIMEOUT			(TMMERR_BASE + 27)//��Ч
#define TMMERR_LICENCE			(TMMERR_BASE + 28)//��Ч
#define TMMERR_SENDPACKET		(TMMERR_BASE + 29)//��Ч
#define TMMERR_EDGEOUT			(TMMERR_BASE + 30)//��Ч
#define TMMERR_NOTSUPPORT		(TMMERR_BASE + 31)//��Ч
#define TMMERR_NOGROUP			(TMMERR_BASE + 32)//��Ч
#define TMMERR_LOWERVER_PEER	(TMMERR_BASE + 34)//��Ч
#define TMMERR_LOWERVER			(TMMERR_BASE + 35)//��Ч
#define TMMERR_HASPOINTS		(TMMERR_BASE + 36)//��Ч
#define TMMERR_NOTENOUGHPOINTS	(TMMERR_BASE + 37)//��Ч
#define TMMERR_NOMEMBER			(TMMERR_BASE + 38)//��Ч
#define TMMERR_NOAUTH			(TMMERR_BASE + 39)//��Ч
#define TMMERR_REGTOOFAST		(TMMERR_BASE + 40)//ע��̫��
#define TMMERR_REGTOOMANY		(TMMERR_BASE + 41)//ע��̫��
#define TMMERR_POINTSFULL		(TMMERR_BASE + 42)//��Ч
#define TMMERR_GROUPOVER		(TMMERR_BASE + 43)//��Ч
#define TMMERR_SUBGROUPOVER		(TMMERR_BASE + 44)//��Ч
#define TMMERR_HASMEMBER		(TMMERR_BASE + 45)//��Ч
#define TMMERR_NOCONFERENCE		(TMMERR_BASE + 46)//��Ч
#define	TMMERR_RECALL			(TMMERR_BASE + 47)//����ת��
#define	TMMERR_SWITCHVOIP		(TMMERR_BASE + 48)//�޸�VOIP��������ַ
#define	TMMERR_RECFAILED		(TMMERR_BASE + 49)//�豸¼������

#define TMMERR_CANCEL			(TMMERR_BASE + 101)//�Լ�ȡ��
#define TMMERR_CLIENTCANCEL		(TMMERR_BASE + 102)//�Է�ȡ��
#define TMMERR_REFUSE			(TMMERR_BASE + 103)//�ܾ��Է�
#define TMMERR_CLIENTREFUSE		(TMMERR_BASE + 104)//�Է��ܾ�
#define TMMERR_STOP				(TMMERR_BASE + 105)//�Լ�ֹͣ(�ѽ�ͨ)
#define TMMERR_CLIENTSTOP		(TMMERR_BASE + 106)//�Է�ֹͣ(�ѽ�ͨ)

#define TMMERR_VOIPCALLFAILED	 (TMMERR_BASE + 108)//�ʺ�ûǮ��
#define TMMERR_VOIPCONNECTED	 (TMMERR_BASE + 200)//VOIP������ͨ��
#define TMMERR_VOIPDISCONNECTED	 (TMMERR_BASE + 201)//���������Ͽ����ӣ�SOCKET �������ر��ˡ�
#define TMMERR_VOIPACCOUNTFAILED (TMMERR_BASE + 202)//����
#define TMMERR_VOIPPWDFAILED	 (TMMERR_BASE + 203)//�ʺ��������
#define TMMERR_VOIPCONNECTFAILED (TMMERR_BASE + 204)//����VOIP������ʧ��
#define TMMERR_STARTPROXYTRANS	 (TMMERR_BASE + 205)//ͨ�������������ת��
//----------------------------------------------------------

#endif