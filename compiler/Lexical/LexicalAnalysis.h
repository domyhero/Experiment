// =====================================================================================
// 
//       Filename:  LexicalAnalysis.h
//
//    Description:  词法分析
//
//        Version:  1.0
//        Created:  2014年04月01日 08时45分52秒
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Hurley (LiuHuan), liuhuan1992@gmail.com
//        Company:  Class 1107 of Computer Science and Technology
// 
// =====================================================================================

#ifndef LEXICALANALYSIS_H_
#define LEXICALANALYSIS_H_

#include <list>

#include "Error.h"
#include "Types.h"

#define READBUF_SIZE 4096

/// 词法分析
class LexicalAnalysis {
public:
	LexicalAnalysis();
	~LexicalAnalysis();
	
	/// 构造符号流
	void cerateTokensStream();
	
	/// 输出符号流
	void printTokensStream();

private:
	/// 指针移动到下一个非空白字符
	char *skipBlank(char *stream);

	/// 识别关键字
	void analyseKeyWord(TokenNode &tokenNode);

	/// 判断当前状态
	State analyseState(char *stream);

	/// 解析一个Token
	char *analyseToken(char *stream, TokenNode &tokenNode);

	/// 解析标识符
	char *analyseIden(char *stream, TokenNode &tokenNode);

	/// 解析符号
	char *analyseIterator(char *stream, TokenNode &tokenNode);
	
	/// 解析界符
	char *analyseLimit(char *stream, TokenNode &tokenNode);

	/// 解析数字
	char *analyseNumber(char *stream, TokenNode &tokenNode);

private:
	/// 当前处理的行号
	int lineno_;

	/// 符号流
	std::list<TokenNode> tokens_stream_;

	/// 错误流
	std::list<ErrorReport> error_list_;
};

#endif 	// LEXICALANALYSIS_H_
