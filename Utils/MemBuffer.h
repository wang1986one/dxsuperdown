#pragma once

namespace Utils
{
	typedef struct _stMemBuffer
	{
		char* pData;						// 缓冲区指针
		UINT nDataLength;		// 数据长度
		UINT nBufferLength;	// 缓冲区总长度
		UINT nRefCount;			// 引用计数

		_stMemBuffer()
			: pData(NULL)
			, nBufferLength(0)
			, nDataLength(0)
			, nRefCount(0)
		{
		}
	}MemBufferBlock,*PMemBufferBlock;

	class CMemBuffer
	{
	public:
		CMemBuffer(UINT nInitLength=10240);
		CMemBuffer(const CStringA strData);
		CMemBuffer(const CStringW strData);
		CMemBuffer(const CMemBuffer& other);
		CMemBuffer(const LPVOID pData,UINT nDataLength);
		virtual ~CMemBuffer(void);

		char* GetBuffer(void) const;
		UINT GetBufferLength(void) const;
		UINT GetBufferBlockLength(void) const;
		UINT GetBufferBlockRefCount(void) const;
		void SetBufferLength(UINT nDataLength);

		CMemBuffer& Append(const CStringA& other);
		CMemBuffer& Append(const CStringW& other);
		CMemBuffer& Append(const CMemBuffer& other);
		CMemBuffer& Append(const LPCSTR pData);
		CMemBuffer& Append(const LPWSTR pData);
		CMemBuffer& Append(const LPVOID pData,UINT nDataLength);

		// 操作符重载
		CMemBuffer& operator+=(const CMemBuffer& other);
		CMemBuffer& operator+=(const CStringA& other);
		CMemBuffer& operator+=(const CStringW& other);
		CMemBuffer& operator=(const CMemBuffer& other);

		bool Alloc(UINT nLength);		// 请求数据缓冲区,不一定重新分配内存
		bool ReAlloc(UINT nNewLength,bool bKeepData);	// 分配内存，指定数据是否保存
		bool IsEmpty(void);
		void Free(void);	// 释放内存
		void Clear(void);	// 清理，如当前内存被引用，不销毁内存 引用计数功能未实现
		void Empty(void);

	protected:
		void Initialize(void);
		PMemBufferBlock m_pMemBuffer;
	};
}

