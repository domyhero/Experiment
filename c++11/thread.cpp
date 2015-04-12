// =====================================================================================
// 
//       Filename:  pthread.cpp
//
//    Description:  线程测试
//
//        Version:  1.0
//        Created:  2013年05月13日 21时10分31秒
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Hurley (LiuHuan), liuhuan1992@gmail.com
//        Company:  Class 1107 of Computer Science and Technology
// 
// =====================================================================================

#include <iostream>  
#include <thread>  
#include <string>  

void my_thread(int num, const std::string& strName)  
{  
	std::cout << "num:" << num << " name:" << strName << std::endl;  
}  

int main(int argc, char *argv[])
{  
	int num = 1234;  
	std::string strName = "haha";  
	std::thread test(my_thread, num, strName);  
	test.join();

	return 0;  
}
