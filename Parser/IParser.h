#pragma once

class ParserRequest
{
	CString ID;					// 需要解析的ID
	CString UserName;		// 用户名
	CString Password;			// 密码
	MString Information;		// 其他数据
};

class ParserResponse
{
	CString RealAddress;		// 真实地址
	MString Information;		// 其他数据
};

class IParser
{
	// 内容解析接口
	virtual ParserResponse Parser(ParserRequest request) =0;
};

