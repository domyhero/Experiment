// =====================================================================================
// 
//       Filename:  Types.h
//
//    Description:  类型定义
//
//        Version:  1.0
//        Created:  2014年04月01日 08时09分05秒
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Hurley (LiuHuan), liuhuan1992@gmail.com
//        Company:  Class 1107 of Computer Science and Technology
// 
// =====================================================================================

#ifndef TYPES_H_
#define TYPES_H_

#include <string>


/// Token 类型
enum TokenType {
	// 关键字
	AUTO 	  =	1,
	BREAK 	  =	2,
	CASE  	  =	3,
	CHAR 	  =	4,
	CONST 	  =	5,
	CONTINUE  =	6,
	DEFAULT   =	7,
	DO 	  =	8,
	DOUBLE 	  =	9,
	ELSE 	  =	10,
	ENUM 	  =	11,
	EXTERN 	  =	12,
	FLOAT 	  =	13,
	FOR 	  =	14,
	GOTO 	  =	15,
	IF 	  =	16,
	INT 	  =	17,
	LONG 	  =	18,
	REGISTER  =	19,
	RETURN 	  =	20,
	SHORT 	  =	21,
	SIGNED 	  =	22,
	SIZEOF 	  =	23,
	STATIC 	  =	24,
	STRUCT 	  =	25,
	SWITCH 	  =	26,
	TYPEDEF   =	27,
	UNION 	  =	28,
	UNSIGNED  =	29,
	VOID 	  =	30,
	VOLATILE  =	31,
	WHILE 	  =	32,

	// 用户标示符
	USER_TYPE,

	KEYWORD_INDEX_MAX,
	
	// 常量
	CHAR_VAL   = 	51, 	// 字符常量
	UCHAR_VAL   = 	52, 	// 无符号字符常量
	INT_VAL    =	53, 	// 整形常量
	UINT_VAL    =	54, 	// 无符号整形常量
	FLOAT_VAL  =	55, 	// 浮点数常量
	DOUBLE_VAL =	56, 	// 双精度浮点数常量

	NUMBER_INDEX_MAX,
	
	// 运算符
	NOT 	   =	61, 	// !
	BYTE_AND   =	62, 	// &
	COMPLEMENT =	63, 	// ~
	BYTE_XOR   =	64, 	// ^
	MUL 	   =	65, 	// *
	DIV 	   =	66, 	// /
	MOD 	   =	67, 	// %
	ADD 	   =	68, 	// +
	SUB 	   =	69, 	// -
	LES_THAN   =	70, 	// <
	GRT_THAN   =	71, 	// >
	ASG 	   =	72, 	// =
	ARROW 	   =	73, 	// ->
	SELF_ADD   =	74, 	// ++
	SELF_SUB   =	75, 	// --
	LEFT_MOVE  =	76, 	// <<
	RIGHT_MOVE =	77, 	// >>
	LES_EQUAL  =	78, 	// <=
	GRT_EQUAL  =	79, 	// >=
	EQUAL 	   =	80, 	// ==
	NOT_EQUAL  =	81, 	// !=
	AND 	   =	82, 	// &&
	OR 	   =	83, 	// ||

	COMPLETE_ADD        =	84, // +=
	COMPLETE_SUB        =	85, // -=
	COMPLETE_MUL        =	86, // *=
	COMPLETE_DIV 	    = 	87, // /=
	COMPLETE_BYTE_XOR   =	88, // ^=
	COMPLETE_BYTE_AND   =	89, // &=
	COMPLETE_COMPLEMENT =	90, // ~=
	COMPLETE_MOD 	    =	91, // %=
	BYTE_OR             =	92, // |
	
	OPERATOR_INDEX_MAX,

	// 限界符
	LEFT_BRA 	=	100, // (
	RIGHT_BRA 	=	101, // )
	LEFT_INDEX 	=	102, // [
	RIGHT_INDEX 	=	103, // ]
	L_BOUNDER 	=	104, // {
	R_BOUNDER 	=	105, // }
	POINTER 	=	106, // .
	JING 		=	107, // #
	UNDER_LINE 	=	108, // _
	COMMA 		=	109, // ,
	SEMI 		=	110, // ;
	SIN_QUE 	=	111, // '
	DOU_QUE 	=	112, // "

	LIMIT_INDEX_MAX
};


/// Token 节点
struct TokenNode
{
	std::string key;		// 实际名字
    	TokenType type;			// 类型码
    	int line = 0;			// 所在行数

    	union value { 			// 值(可选域)
		char cvalue;		// 字符型
		unsigned char ucvalue;
		short svalue; 		// 短整型
		unsigned usvalue;
    		int ivalue; 		// 整型
		unsigned int uivalue;
		double dvalue; 		// 浮点
		float  fvalue;
    	} value;
	std::string strvalue; 		// 字符串类型的值
};

/// 词法分析状态
enum State {
	Begin,
	Keyword,
	Number,
	Iterator,
	Limit,
	Error
};

#endif 	// TYPES_H_
