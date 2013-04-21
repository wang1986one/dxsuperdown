#pragma once

typedef UINT (WINAPI *PTHREAD_START)(LPVOID lpThreadParameter);
typedef PTHREAD_START LPTHREAD_START;

namespace Utils
{
	//���߳�ͬ����
	class ThreadLocker;

	class Mutex
	{
	public:
		Mutex(void);

		~Mutex(void);

		void Lock(void);

		void UnLock(void);

		//��ǰ�Ƿ���ס
		bool isLock(void) const;
	protected:
		CRITICAL_SECTION mCs;
	private:
	};

	class ThreadLocker
	{
	public:
		ThreadLocker(Mutex *mutex);

		~ThreadLocker(void);
	protected:
		Mutex *m_mtx;
	private:
	};

	class Monitor
	{
	private:
		HANDLE m_pEvent ;
	public:
		Monitor(BOOL isManual = FALSE);
		~Monitor(); 

		// ���Ϊauto����SetEvent��event obj��Ϊ���źţ���һ���ȴ��߳�release��
		//event obj�Զ���Ϊ���ź�
		//�����manual����release���еȴ��̣߳���û�к����Զ�����
		void Set();

		//�ֶ���event obj��Ϊ���ź�
		void Reset();
		// ���Ϊauto����PulseEvent��event obj��Ϊ���źţ���һ���ȴ��߳�release��
		//event obj�Զ���Ϊ���ź�
		//�����manual��PulseEvent��event obj��Ϊ���źţ���release���еȴ��̣߳�
		//Ȼ��event obj�Զ���Ϊ���ź�
		void Pulse();
		// �ȴ�ֱ����ʱ
		DWORD Wait(long timeout);
	};

	class Thread
	{
	private:    
		HANDLE threadHandle ; 
		unsigned long  threadId ;    
		unsigned long  exitCode ;
		BOOL needTerminate ;

	public:
		Thread(unsigned long exit_code = 0 );
		~Thread(void); 

		//�����߳�;
		void Start(LPTHREAD_START_ROUTINE pfn ,void* pParam);
		void SetTerminateSymbol(BOOL needTerminate); 
		void Wait(DWORD dwMilliseconds);

		long GetThreadID();
		HANDLE GetThreadHandle(void);
	};

	//�����߳�(�����߳��׳����쳣)
	//�����߳̾��
	HANDLE CreateThread(LPTHREAD_START lpStartAddress,
		LPVOID lpParameter = NULL,
		LPDWORD pthreadId = NULL,
		DWORD dwCreationFlags = 0);

	HANDLE CreateWorkThread(LPTHREAD_START_ROUTINE lpStartAddress,
		LPVOID lpParameter = NULL,
		LPDWORD pthreadId = NULL,
		DWORD dwCreationFlags = 0);

	//�����̳߳ط�ʽ�����߳�(�����߳��׳����쳣)
	BOOL CreateThreadPool(LPTHREAD_START_ROUTINE lpStartAddress, 
		LPVOID lpParameter = NULL);
}