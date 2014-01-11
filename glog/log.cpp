// =====================================================================================
// 
//       Filename:  log.cpp
//
//    Description:  glog 的测试代码
//
//        Version:  1.0
//        Created:  2013年08月12日 22时45分35秒
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Hurley (LiuHuan), liuhuan1992@gmail.com
//        Company:  Class 1107 of Computer Science and Technology
// 
// =====================================================================================

#include <iostream>
#include <glog/logging.h>

int main(int argc, char *argv[])
{
	google::InitGoogleLogging(argv[0]);
	google::LogToStderr();

	LOG(INFO) <<"program start";

	int valueint = 10;  
	LOG_IF(ERROR, valueint == 10) << "valueint = 10";

	return 0;
}

