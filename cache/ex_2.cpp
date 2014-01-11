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
	boost::timer timer;

	for (int k = 1; k <= 1024; k *= 2) {
		int *array = new int[LENGTH];
		timer.restart();
		for (int i = 0; i < LENGTH; i+=k) {
			array[i] *= 3;
		}
		std::cout << "k = " << k << " time: " << timer.elapsed() << std::endl;
		delete[] array;
	}

	return 0;
}

