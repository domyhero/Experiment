// =====================================================================================
// 
//       Filename:  Error.h
//
//    Description:  错误处理
//
//        Version:  1.0
//        Created:  2014年04月01日 08时19分51秒
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Hurley (LiuHuan), liuhuan1992@gmail.com
//        Company:  Class 1107 of Computer Science and Technology
// 
// =====================================================================================

#ifndef ERROR_H_
#define ERROR_H_

/// 错误消息管理
class ErrorReport {
public:
	ErrorReport() : error_code_(NO_ERROR)
	{
	}

	~ErrorReport()
	{
	}

	enum ErrorCode {
		NO_ERROR 	      =  0,
		FLOAT_ERROR_NUM       =	 1,
		DOUBLE_ERROR_NUM      =	 2,
		NOTE_ERROR_NUM 	      =	 3,
		STRING_ERROR_NUM      =	 4,
		CHARCONST_ERROR_NUM   =	 5,
		CHAR_ERROR_NUM 	      =	 6,
		LEFT_BRA_ERROR_NUM    =	 7,
		RIGHT_BRA_ERROR_NUM   =	 8,
		LEFT_INDEX_ERROR_NUM  =	 9,
		RIGHT_INDEX_ERROR_NUM =	 10,
		L_BOUNDER_ERROR_NUM   =	 11,
		R_BOUNDER_ERROR_NUM   =	 12,
		PRE_PROCESS_ERROR_NUM =  13,

		ERROR_INDEX_MAX
	};

	const char *ErrorStrings[ERROR_INDEX_MAX] = {
			"没有错误",
			"float表示错误",
			"double表示错误",
			"注释没有结束符",
			"字符串常量没有结束符",
			"字符常量没有结束符",
			"非法字符",
			"\'(\'没有对应项",
			"\')\'没有对应项",
			"\'[\'没有对应项",
			"\']\'没有对应项",
			"\'{\'没有对应项",
			"\'}\'没有对应项",
			"预处理错误" 
	};

	/// 返回错误代码
	ErrorCode getErrorCode()
	{
		return error_code_;
	}

	/// 返回错误类型
	const char *getErrorString()
	{
		return ErrorReport::ErrorStrings[error_code_];
	}

private:
	ErrorCode error_code_;
};

#endif 	// ERROR_H_
