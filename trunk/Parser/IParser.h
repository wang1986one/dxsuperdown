#pragma once

class ParserRequest
{
	CString ID;					// ��Ҫ������ID
	CString UserName;		// �û���
	CString Password;			// ����
	MString Information;		// ��������
};

class ParserResponse
{
	CString RealAddress;		// ��ʵ��ַ
	MString Information;		// ��������
};

class IParser
{
	// ���ݽ����ӿ�
	virtual ParserResponse Parser(ParserRequest request) =0;
};

