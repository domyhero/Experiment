/*
 * =====================================================================================
 *
 *       Filename:  input.c
 *
 *    Description:  模拟鼠标消息
 *
 *        Version:  1.0
 *        Created:  2014年03月25日 17时19分53秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hurley (LiuHuan), liuhuan1992@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */

#include <unistd.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sml_input.h"

/*
 * 初始化键消息模拟库
 */
sml_handle sml_init()
{
	Display *dpy = XOpenDisplay(NULL);
	if (!dpy) {
		return false;	
	}
	
	return dpy;
}

/*
 * 释放资源
 */
void sml_destory(sml_handle handle)
{
	assert(handle);
	XCloseDisplay(handle);
}

/*
 * 在某坐标模拟鼠标消息
 *
 * @x，@y 为鼠标坐标
 * @type 为鼠标按键类型
 *
 * MLEFT 为左键，MMIDDLE 为中键，MRIGHT 为右键
 */
void sml_clickat(sml_handle handle, int x, int y, mktype_t type)
{
	assert(handle);

	XEvent event;

	// 保存鼠标当前位置等信息
	XQueryPointer(  handle, 
			RootWindow(handle, DefaultScreen(handle)), 
			&event.xbutton.root,
			&event.xbutton.window,
      			&event.xbutton.x_root,
			&event.xbutton.y_root,
      			&event.xbutton.x,
			&event.xbutton.y,
      			&event.xbutton.state);

	// 移动鼠标，-1 表示当前屏幕
	XTestFakeMotionEvent(handle, -1, x, y, CurrentTime);

	// 模拟按下和松开鼠标
	XTestFakeButtonEvent(handle, type, 1, CurrentTime);
	XTestFakeButtonEvent(handle, type, 0, CurrentTime);

	// 移动鼠标到原先位置
	XTestFakeMotionEvent(handle, -1, event.xbutton.x, event.xbutton.y, CurrentTime);
}

int main(int argc, char *argv[])
{
	sml_handle handle = sml_init();;

	sml_clickat(handle, 200, 200, MLEFT);

	sml_destory(handle);

	return EXIT_SUCCESS;
}

