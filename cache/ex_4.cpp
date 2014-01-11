// =====================================================================================
// 
//       Filename:  ex_1.cpp
//
//    Description:  指令级并行
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

int main(int argc, char *argv[])
{
	int steps = 256 * 1024 * 1024;
	int array[2];
	boost::timer timer;

	for (int i = 0; i < steps; i++) {
		array[0]++;
		array[0]++;
	}
	std::cout << timer.elapsed() << std::endl;

	timer.restart();
	for (int i = 0; i < steps; i++) {
		array[0]++;
		array[1]++;
	}
	std::cout << timer.elapsed() << std::endl;

	return 0;
}

