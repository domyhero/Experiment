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
#include <cmath>
#include <list>
#include <map>

#include "LexicalAnalysis.h"
#include "Types.h"
#include "Error.h"

LexicalAnalysis::LexicalAnalysis() : lineno_(0)
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

	while (std::cin.getline(readBuff, READBUF_SIZE)) {
		char *stream = readBuff;
		tokenNode.line = ++lineno_;
		do {
			stream = analyseToken(stream, tokenNode);
			if (tokenNode.key != " ") {
				tokens_stream_.push_back(tokenNode);
			}
		} while (*stream);
	}

	for (auto &tokenNode : tokens_stream_) {
		analyseKeyWord(tokenNode);
	}

	if (!error_list_.empty()) {
		std::cout << "解析过程中遇到了一些错误：" << std::endl;
		for (auto &error : error_list_) {
			std::cout << "错误行号: " << error.getErrorLine() 
				<< " 错误类型: " << error.getErrorString() << std::endl;
		}
		std::cout << std::endl;
	}
}
	
/// 输出符号流
void LexicalAnalysis::printTokensStream()
{
	for (auto &index : tokens_stream_) {
		std::cout << "行号: " << index.line << " ";
		std::cout << "名字: " << index.key << " 类型: ";
		if (index.type == USER_WORD) {
			std::cout << "用户标示符" << " ";
		} else if (index.type < KEYWORD_INDEX_MAX) {
			std::cout << "关键字" << " ";
		} else if (index.type < NUMBER_INDEX_MAX) {
			if (index.type == CHAR_VAL) {
				std::cout << "字符 值:" << index.value.cvalue;
			} else if (index.type == UCHAR_VAL) {
				std::cout << "无符号字符 值:" << index.value.ucvalue;
			} else if (index.type == INT_VAL) {
				std::cout << "整型 值:" << index.value.ivalue;
			} else if (index.type == UINT_VAL) {
				std::cout << "无符号整型 值:" << index.value.uivalue;
			} else if (index.type == FLOAT_VAL) {
				std::cout << "浮点数 值:" << index.value.fvalue;
			} else if (index.type == DOUBLE_VAL) {
				std::cout << "双精度浮点数 值:" << index.value.dvalue;
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
	while (*stream == ' ' || *stream == '\t') {
		stream++;
	}

	return stream;
}

/// 识别关键字
void LexicalAnalysis::analyseKeyWord(TokenNode &tokenNode)
{
	if (tokenNode.type != USER_WORD) {
		return;
	}

	for (auto &keywordPair : keywordMap) {
		if (tokenNode.key == keywordPair.first) {
			tokenNode.type = keywordPair.second;
			break;
		}
	}
}

/// 判断当前状态
State LexicalAnalysis::analyseState(char *stream)
{
	if (isalpha(*stream) || *stream == '_') {
		return Keyword;
	} else if (isdigit(*stream)) {
		return Number;
	} else if (*stream == '(' || *stream == ')' || *stream == '['  ||
		   *stream == ']' || *stream == '{' || *stream == '}'  ||
		   *stream == ',' || *stream == ';' || *stream == '\'' ||
		   *stream == '\"' ) {
		return Limit;
	// 33-47   !"#$%&'()*+,-./    58-64   :;<=>?@    91-96   [\]^_`    123-126 {|}~}
	} else if ((*stream > 32 && *stream < 48) || (*stream >  57 && *stream <  65) ||
		   (*stream > 90 && *stream < 97) || (*stream > 122 && *stream < 127)) {
		return Iterator;
	} else if (*stream == '\0' || *stream == '\n' || (*stream == '\r' && *(stream+1) == '\n')) {
		return Endline;
	} else if (*stream == ' ' || *stream == '\t') {
		return Blank;
	}

	ErrorReport error;
	error.setErrorCode(ErrorReport::CHAR_ERROR);
	error.setErrorLine(lineno_);

	error_list_.push_back(error);

	return Error;
}

/// 解析一个Token
char *LexicalAnalysis::analyseToken(char *stream, TokenNode &tokenNode)
{
	char *tmpstr = stream;

	switch (analyseState(stream)) {
		case Keyword:
			tmpstr = analyseIden(tmpstr, tokenNode);
			tmpstr = skipBlank(tmpstr);
			break;
		case Number:
			tmpstr = analyseNumber(tmpstr, tokenNode);
			tmpstr = skipBlank(tmpstr);
			break;
		case Iterator:
			tmpstr = analyseIterator(tmpstr, tokenNode);
			tmpstr = skipBlank(tmpstr);
			break;
		case Limit:
			tmpstr = analyseLimit(tmpstr, tokenNode);
			tmpstr = skipBlank(tmpstr);
			break;
		case Endline:
			*tmpstr = '\0';
			break;
		case Blank:
			tmpstr = skipBlank(tmpstr);
			tokenNode.key = " ";
			break;
		case Error:
			tmpstr++;
			break;
		default:
			break;
	}

	return tmpstr;
}

/// 解析标识符
char *LexicalAnalysis::analyseIden(char *stream, TokenNode &tokenNode)
{
	char *tmpstr = stream;

	while (analyseState(tmpstr) == Keyword) {
		tmpstr++;
	}

	tokenNode.key = std::string(stream, tmpstr);
	tokenNode.type = USER_WORD;

	return tmpstr;
}

/// 解析符号
char *LexicalAnalysis::analyseIterator(char *stream, TokenNode &tokenNode)
{
	tokenNode.key = *stream;
	switch (*stream) {
		case '!':
			tokenNode.type = NOT;
			break;
		case '&':
			tokenNode.type = BYTE_AND;
			break;
		case '~':
			tokenNode.type = COMPLEMENT;
			break;
		case '^':
			tokenNode.type = BYTE_XOR;
			break;
		case '*': 
			tokenNode.type = MUL;
			break;
		case '/':
			tokenNode.type = DIV;
			break;
		case '%':
			tokenNode.type = MOD;
			break;
		case '+':
			tokenNode.type = ADD;
			break;
		case '-':
			tokenNode.type = SUB;
			break;
		case '<':
			tokenNode.type = LES_THAN;
			break;
		case '>':
			tokenNode.type = GRT_THAN;
			break;
		case '=':
			tokenNode.type = ASG;
			break;
	}
	
	return stream+1;
}

/// 解析界符
char *LexicalAnalysis::analyseLimit(char *stream, TokenNode &tokenNode)
{
	tokenNode.key = *stream;
	switch (*stream) {
		case '(':
			tokenNode.type = LEFT_BRA;
			break;
		case ')':
			tokenNode.type = RIGHT_BRA;
			break;
		case '[':
			tokenNode.type = LEFT_INDEX;
			break;
		case ']':
			tokenNode.type = RIGHT_INDEX;
			break;
		case '{':
			tokenNode.type = L_BOUNDER;
			break;
		case '}':
			tokenNode.type = R_BOUNDER;
			break;
		case ',':
			tokenNode.type = COMMA;
			break;
		case ';':
			tokenNode.type = SEMI;
			break;

		// TODO 解析符号和字符串
		case '\'':
			tokenNode.type = SIN_QUE;
			break;
		case '\"':
			tokenNode.type = DOU_QUE;
			break;
	}

	return stream+1;
}

/// 解析数字
char *LexicalAnalysis::analyseNumber(char *stream, TokenNode &tokenNode)
{
	char *num = stream;
	double n = 0, scale = 0;
	int subscale = 0, signsubscale = 1;

	if (isdigit(*num)) {
		do{
			n = (n * 10.0) + (*num++ - '0');
		} while (isdigit(*num));
	}

	if (*num == '.' && isdigit(*(num+1))) {
		num++;
		do {
			n = (n * 10.0) + (*num++ - '0'), scale--;
		} while (isdigit(*num));
	}

	if (*num == 'e' || *num == 'E') {
		num++;
		if (*num == '+') {
			num++;
		} else if (*num == '-') {
			signsubscale = -1;
			num++;
		}
		while (isdigit(*num)) {
			subscale = (subscale * 10) + (*num++ - '0');
		}
	}

	n = n * pow(10.0, (scale + subscale * signsubscale));

	tokenNode.key = std::string(stream, num);

	if (scale) {
		tokenNode.type = DOUBLE_VAL;
		tokenNode.value.dvalue = n;
	} else {
		tokenNode.type = INT_VAL;
		tokenNode.value.ivalue = n;
	}

	return num;
}

