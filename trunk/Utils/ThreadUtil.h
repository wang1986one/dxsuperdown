#pragma once

typedef UINT (WINAPI *PTHREAD_START)(LPVOID lpThreadParameter);
typedef PTHREAD_START LPTHREAD_START;

namespace Utils
{
	//多线程同步锁
	class ThreadLocker;

	class Mutex
	{
	public:
		Mutex(void);

		~Mutex(void);

		void Lock(void);

		void UnLock(void);

		//当前是否被锁住
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

		// 如果为auto，则SetEvent将event obj设为有信号，当一个等待线程release后，
		//event obj自动设为无信号
		//如果是manual，则release所有等待线程，且没有后面自动重设
		void Set();

		//手动将event obj设为无信号
		void Reset();
		// 如果为auto，则PulseEvent将event obj设为有信号，当一个等待线程release后，
		//event obj自动设为无信号
		//如果是manual，PulseEvent将event obj设为有信号，且release所有等待线程，
		//然后将event obj自动设为无信号
		void Pulse();
		// 等待直到超时
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

		//启动线程;
		void Start(LPTHREAD_START_ROUTINE pfn ,void* pParam);
		void SetTerminateSymbol(BOOL needTerminate); 
		void Wait(DWORD dwMilliseconds);

		long GetThreadID();
		HANDLE GetThreadHandle(void);
	};

	//创建线程(忽略线程抛出的异常)
	//返回线程句柄
	HANDLE CreateThread(LPTHREAD_START lpStartAddress,
		LPVOID lpParameter = NULL,
		LPDWORD pthreadId = NULL,
		DWORD dwCreationFlags = 0);

	HANDLE CreateWorkThread(LPTHREAD_START_ROUTINE lpStartAddress,
		LPVOID lpParameter = NULL,
		LPDWORD pthreadId = NULL,
		DWORD dwCreationFlags = 0);

	//采用线程池方式创建线程(忽略线程抛出的异常)
	BOOL CreateThreadPool(LPTHREAD_START_ROUTINE lpStartAddress, 
		LPVOID lpParameter = NULL);
}