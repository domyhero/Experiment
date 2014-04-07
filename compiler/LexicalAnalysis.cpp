// =====================================================================================
// 
//       Filename:  LexicalAnalysis.cpp
//
//    Description:  词法分析
//
//        Version:  1.0
//        Created:  2014年04月01日 08时55分18秒
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Hurley (LiuHuan), liuhuan1992@gmail.com
//        Company:  Class 1107 of Computer Science and Technology
// 
// =====================================================================================

#include <iostream>
#include <fstream>

#include "LexicalAnalysis.h"
#include "Types.h"
#include "Error.h"

ErrorReport glbLexErrReport;

LexicalAnalysis::LexicalAnalysis()
{

}

LexicalAnalysis::~LexicalAnalysis()
{

}

/// 构造符号流
void LexicalAnalysis::cerateTokensStream()
{
	TokenNode tokenNode;
	char readBuff[READBUF_SIZE];
	int line = 0;

	while (std::cin.getline(readBuff, READBUF_SIZE)) {
		char *stream = readBuff;
		tokenNode.line = ++line;
		do {
			stream = analyseToken(stream, tokenNode);
			tokens_stream_.push_back(tokenNode);
		} while (*stream);
	}
}
	
/// 输出符号流
void LexicalAnalysis::printTokensStream()
{
	for (auto &index : tokens_stream_) {
		std::cout << "行号: " << index.line << " ";
		std::cout << "名字: " << index.key << " 类型: ";
		if (index.type < KEYWORD_INDEX_MAX) {
			std::cout << "关键字" << " ";
		} else if (index.type < NUMBER_INDEX_MAX) {
			switch (index.type) {
				case CHAR_VAL:
					std::cout << "字符 值:" << index.value.cvalue;
					break;
				case UCHAR_VAL:  
					std::cout << "无符号字符 值:" << index.value.ucvalue;
					break;
				case INT_VAL:
					std::cout << "整型 值:" << index.value.ivalue;
					break;
				case UINT_VAL:
					std::cout << "无符号整型 值:" << index.value.uivalue;
					break;
				case FLOAT_VAL: 
					std::cout << "浮点数 值:" << index.value.fvalue;
					break;
				case DOUBLE_VAL:
					std::cout << "双精度浮点数 值:" << index.value.dvalue;
					break;
				default:
					break;
			}
		} else if (index.type < OPERATOR_INDEX_MAX) {
			std::cout << "运算符" << " ";
		} else if (index.type < LIMIT_INDEX_MAX) {
			std::cout << "界符" << " ";
		}
		std::cout << std::endl;
	}
}

/// 指针移动到下一个非空白字符
char *LexicalAnalysis::skipBlank(char *stream)
{
	// TAB 9
	while (*stream == ' ' || *stream == 9) {
		stream++;
	}

	return stream;
}

/// 判断当前状态
State LexicalAnalysis::analyseState(char *stream)
{
	if (isalpha(*stream) || *stream == '_') {
		return Keyword;
	} else if (isdigit(*stream)) {
		return Number;
		   // 33-47   !"#$%&'()*+,-./    58-64   :;<=>?@    91-96   [\]^_`    123-126 {|}~}
	} else if ((*stream > 32 && *stream < 48) || (*stream >  57 && *stream <  65) ||
		   (*stream > 90 && *stream < 97) || (*stream > 122 && *stream < 127)) {
		return Iterator;
	}

	glbLexErrReport.setErrorCode(ErrorReport::CHAR_ERROR);

	return Error;
}

/// 解析一个Token
char *LexicalAnalysis::analyseToken(char *stream, TokenNode &tokenNode)
{
	char *tmpstr = stream;

	switch (analyseState(stream)) {
		case Keyword:
			tmpstr = analyseIden(tmpstr, tokenNode);
			break;
		case Number:
			tmpstr = analyseNumber(tmpstr, tokenNode);
			break;
		case Iterator:
			tmpstr = analyseIterator(tmpstr, tokenNode);
			break;
		case Limit:
			tmpstr = analyseLimit(tmpstr, tokenNode);
			break;
		case Error:
			std::cout << glbLexErrReport.getErrorString() << std::endl;
			break;
		default:
			break;
	}

	return tmpstr;
}

/// 解析标识符
char *LexicalAnalysis::analyseIden(char *stream, TokenNode &tokenNode)
{
	return stream;
}

/// 解析符号
char *LexicalAnalysis::analyseIterator(char *stream, TokenNode &tokenNode)
{
	return stream;
}

/// 解析届符
char *LexicalAnalysis::analyseLimit(char *stream, TokenNode &tokenNode)
{
	return stream;
}

/// 解析数字
char *LexicalAnalysis::analyseNumber(char *stream, TokenNode &tokenNode)
{
	return stream;
}

