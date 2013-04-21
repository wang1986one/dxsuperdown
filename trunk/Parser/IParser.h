#pragma once
#include <map>

typedef std::map<CString,CString> VString;

class ParserRequest
{
	CString ID;					// ��Ҫ������ID
	CString UserName;		// �û���
	CString Password;			// ����
	VString Information;		// ��������
};

class ParserResponse
{
	CString RealAddress;		// ��ʵ��ַ
	VString Information;		// ��������
};

class IParser
{
	// ���ݽ����ӿ�
	virtual ParserResponse Parser(ParserRequest request) =0;
};

