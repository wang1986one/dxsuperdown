#pragma once

namespace Utils
{
	typedef struct _stMemBuffer
	{
		char* pData;						// ������ָ��
		UINT nDataLength;		// ���ݳ���
		UINT nBufferLength;	// �������ܳ���
		UINT nRefCount;			// ���ü���

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

		// ����������
		CMemBuffer& operator+=(const CMemBuffer& other);
		CMemBuffer& operator+=(const CStringA& other);
		CMemBuffer& operator+=(const CStringW& other);
		CMemBuffer& operator=(const CMemBuffer& other);

		bool Alloc(UINT nLength);		// �������ݻ�����,��һ�����·����ڴ�
		bool ReAlloc(UINT nNewLength,bool bKeepData);	// �����ڴ棬ָ�������Ƿ񱣴�
		bool IsEmpty(void);
		void Free(void);	// �ͷ��ڴ�
		void Clear(void);	// �����統ǰ�ڴ汻���ã��������ڴ� ���ü�������δʵ��
		void Empty(void);

	protected:
		void Initialize(void);
		PMemBufferBlock m_pMemBuffer;
	};
}

