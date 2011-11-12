//---------------------------------------------------------------------------

#ifndef TCMDParserH
#define TCMDParserH
//---------------------------------------------------------------------------
#include    <VCL.h>
#include    "CommFunc.h"
#include    <StrUtils.hpp>

//小型命令行解析
class	TCMDParser
{
private:

	String   			ReadPar(char * data, int Len, int &pos);
	String				ReadUntil(char * data, int Len, int &pos, char endCh);
	char			m_Spliter;
	char			m_StrCh;
	char			m_StrChReplace;	
public:
					//命令,  		分隔符,		字符串		字符串分隔符转义符
	void	GetCMD(String	cmd, char spliter, char StrCh, char	StrChReplace, TStrings * Output);
};


String   	TCMDParser::ReadPar(char * data, int Len, int &pos)
{
	while(pos < Len)
	{
		//去休止符
		if(data[pos] == m_Spliter)
			pos++;
		else
			break;
	}

	if(data[pos] == m_StrCh)
	{
		pos++;
		return	ReadUntil(data, Len, pos, m_StrCh);
	}
	else
		return	ReadUntil(data, Len, pos, m_Spliter);
}

String		TCMDParser::ReadUntil(char * data, int Len, int &pos, char endCh)
{
	bool	parseString = false;

	String result;
	if(m_StrCh == endCh)
		parseString = true;
	while(pos < Len)
	{
		if(parseString == true && data[pos] == m_StrChReplace)
		{
			//转义符
			pos++;
			result = result + data[pos];
			pos++;
			continue;
		} 
		if(data[pos] == endCh)
		{
			pos++;
			break;
		}
		result = result + data[pos];

		if(IsDBCSLeadByte(data[pos]))
		{			pos++;			result = result + data[pos];		}

		pos++;			
	}

	return	result; 
}

void	TCMDParser::GetCMD(String	cmd, char spliter, char StrCh, char	StrChReplace, TStrings * Output)
{
	Output->Clear();

	cmd = ReplaceStr(cmd, StrChReplace, (String)StrChReplace+(String)StrChReplace);
	String chStr = (String)StrChReplace + (String)StrChReplace + (String)StrCh;
	String chReplaceStr = (String)StrChReplace + (String)StrCh; 
	cmd = ReplaceStr(cmd, chStr, chReplaceStr);

	m_Spliter = spliter;
	m_StrCh = StrCh;
	m_StrChReplace = StrChReplace;

	int pos = 0;
	while(pos < cmd.Length())
	{
		Output->Add(ReadPar(cmd.c_str(), cmd.Length(), pos));
	}
}

#endif
