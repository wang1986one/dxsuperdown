#pragma once
class CFlvcdParser
	: public IParser
{
public:
	CFlvcdParser(void);
	~CFlvcdParser(void);

	virtual ParserResponse Parser( ParserRequest request );
};

