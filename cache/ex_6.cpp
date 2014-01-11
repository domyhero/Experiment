// =====================================================================================
// 
//       Filename:  ex_1.cpp
//
//    Description:  
//
//        Version:  1.0
//        Created:  2013年10月23日 23时06分33秒
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Hurley (LiuHuan), liuhuan1992@gmail.com
//        Company:  Class 1107 of Computer Science and Technology
// 
// =====================================================================================

#include <iostream>
#include <boost/timer.hpp>

#define LENGTH 64 * 1024 * 1024

int main(int argc, char *argv[])
{
	int *array = new int[LENGTH];

	boost::timer timer;
	
	// 一个优化的反例！
	for (int i = 0; i < LENGTH; i++) {
		array[i] *= 3;
	}

	timer.restart();
	std::cout << timer.elapsed() << std::endl;

	for (int i = 0; i < LENGTH; i+=2) {
		array[i] *= 3;
		array[i+1] *= 3;
	}

	std::cout << timer.elapsed() << std::endl;

	return 0;
}

