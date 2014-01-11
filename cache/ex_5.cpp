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

#define N 65 * 1024 * 1024

struct Point {
	int x;
	int y;
};

int main(int argc, char *argv[])
{
	int *px = new int[N];
	int *py = new int[N];

	Point *point = new Point[N];

	boost::timer timer;

	for (int i = 0; i < N; i++) {
		px[i]++;
		py[i]++;
	}
	std::cout << timer.elapsed() << std::endl;

	timer.restart();
	for (int i = 0; i < N; i++) {
		point[i].x++;
		point[i].y++;
	}
	std::cout << timer.elapsed() << std::endl;

	return 0;
}

