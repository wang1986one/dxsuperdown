#pragma once
#include <vector>
#include "Utils/Network/WinHttp.h"
#include "Utils/Delegate.h"

namespace Utils
{
	/*
	INTERNET_CONNECTION_LAN 　　　　　    处于局域网
	INTERNET_CONNECTION_MODEM 　　　    拨号上网
	INTERNET_CONNECTION_PROXY 　　　　 代理
	INTERNET_CONNECTION_MODEM_BUSY 　代理被占用
	INTERNET_CONNECTION_CONFIGURED    网络已连接，但当前不可用
	INTERNET_CONNECTION_OFFLINE 　　　 离线
	INTERNET_RAS_INSTALLED　　　　　　　RAS安装
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

		// 以下为结果
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
		// 发出一个Ping探测线程
		void SendPing(PingPackage* pPingPackage);

		//Ping完成后事件
		// void (PingPackage*)
		FinishedHandler eventFinished;

	private:
		void Init();
		void Uninit();

		// 构造Ping ICMP包
		static bool ConstructIcmpMessage(char* pDataBuff, int nDataSize);
		// 计算校验和
		static USHORT CheckSum(USHORT* pBuff, int nSize);
		// 解析数据包
		static bool DecodeIpPacket(char* pBuff, int nBuffSize, sockaddr_in* pAddr, PingPackage* pPingPackage);
		SOCKET m_socketRaw;

	private:
		static DWORD PingThread(LPVOID pParam);
	};
}