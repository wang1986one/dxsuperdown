#pragma once
#include <vector>
#include "Utils/Network/WinHttp.h"
#include "Utils/Delegate.h"

namespace Utils
{
	/*
	INTERNET_CONNECTION_LAN ����������    ���ھ�����
	INTERNET_CONNECTION_MODEM ������    ��������
	INTERNET_CONNECTION_PROXY �������� ����
	INTERNET_CONNECTION_MODEM_BUSY ������ռ��
	INTERNET_CONNECTION_CONFIGURED    ���������ӣ�����ǰ������
	INTERNET_CONNECTION_OFFLINE ������ ����
	INTERNET_RAS_INSTALLED��������������RAS��װ
	*/
	bool GetInternetConnectionType(LPDWORD lpdwType);

	bool IsInner(LPCTSTR lpIPAddress);

	bool IsInner(LPCTSTR lpIPAddress, LPCTSTR lpStartAddress, LPCTSTR lpEndAddress);

	long GetIPNum(LPCTSTR lpIPAddress);

	bool ParserURL(LPCTSTR lpURL,
		CString* szHostName,
		INTERNET_PORT* nPort=NULL,
		CString* szUrlPath=NULL,
		CString* szUserName=NULL,
		CString* szPassword=NULL,
		CString* ExtraInfo=NULL,
		INTERNET_SCHEME* Scheme=NULL);

	class CPing;

	typedef struct _stPingResult
	{
		UINT nResultTTL;
		UINT nRecvedSize;
		UINT nTimes;
	}PingResult,*PPingResult;

	class	PingPackage
	{
	public:
		void SetURL(LPCTSTR lpURL);

		CString szHostName;
		UINT nPackageNumber;
		UINT nPackageSize;

		// ����Ϊ���
		UINT nRecvedNumber;
		UINT nTotalTimes;
		std::vector<PingResult> ResultList;

		PingPackage():nPackageNumber(4),nPackageSize(32),nRecvedNumber(0),nTotalTimes(0) {}
	};

	class IPingNotify
	{
	public:
		virtual void PingFinished(PingPackage* pPackage)=0;
	};

	typedef ACF::Delegate<void (PingPackage*) >    FinishedHandler;

	class CPing
	{
	public:
		CPing(void);
		virtual ~CPing(void);
		// ����һ��Ping̽���߳�
		void SendPing(PingPackage* pPingPackage);

		//Ping��ɺ��¼�
		// void (PingPackage*)
		FinishedHandler eventFinished;

	private:
		void Init();
		void Uninit();

		// ����Ping ICMP��
		static bool ConstructIcmpMessage(char* pDataBuff, int nDataSize);
		// ����У���
		static USHORT CheckSum(USHORT* pBuff, int nSize);
		// �������ݰ�
		static bool DecodeIpPacket(char* pBuff, int nBuffSize, sockaddr_in* pAddr, PingPackage* pPingPackage);
		SOCKET m_socketRaw;

	private:
		static DWORD PingThread(LPVOID pParam);
	};
}