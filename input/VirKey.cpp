/*
 * =====================================================================================
 *
 *       Filename:  VirKey.cpp
 *
 *    Description:  键盘鼠标消息模拟类
 *
 *        Version:  1.0
 *        Created:  2014年03月28日 14时25分33秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hurley (LiuHuan), liuhuan1992@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */

#include <assert.h>

#include "VirKey.h"

/// 构造函数
VirKey::VirKey()
{
	handle_ = XOpenDisplay(NULL);
}

/// 析构函数
VirKey::~VirKey()
{
	if (handle_ != NULL) {
		XCloseDisplay(handle_);
	}
}

/**
 * 在某坐标模拟鼠标消息
 *
 * @x，@y 为鼠标坐标
 * @type 为鼠标按键类型
 * 	MLEFT 为左键，MMIDDLE 为中键，MRIGHT 为右键
 */
void VirKey::ClickAt(int x, int y, VirKeyMType type)
{
	assert(handle_);

	XEvent event;

	// 保存鼠标当前位置等信息
	XQueryPointer(  handle_, 
			RootWindow(handle_, DefaultScreen(handle_)), 
			&event.xbutton.root,
			&event.xbutton.window,
      			&event.xbutton.x_root,
			&event.xbutton.y_root,
      			&event.xbutton.x,
			&event.xbutton.y,
      			&event.xbutton.state);

	// 移动鼠标，-1 表示当前屏幕
	XTestFakeMotionEvent(handle_, -1, x, y, CurrentTime);

	// 模拟按下和松开鼠标
	XTestFakeButtonEvent(handle_, type, 1, CurrentTime);
	XTestFakeButtonEvent(handle_, type, 0, CurrentTime);

	// 移动鼠标到原先位置
	XTestFakeMotionEvent(handle_, -1, event.xbutton.x, event.xbutton.y, CurrentTime);
}

/**
 * 键盘按下抬起消息
 *
 * @key 模拟的键
 * @is_press 按下还是抬起
 */
bool VirKey::PressKey(int key, bool isPress)
{
	assert(handle_);

	KeyCode keyCode = XKeysymToKeycode(handle_, key);
	if (key == NoSymbol) {
		return false;
	}

	XTestFakeKeyEvent(handle_, keyCode, isPress, CurrentTime);
	XFlush(handle_);

	return true;
}

/**
 * 发送一个键盘按键消息
 */
bool VirKey::PressKeyOnce(int key)
{
	assert(handle_);

	KeyCode keyCode = XKeysymToKeycode(handle_, key);
	if (key == NoSymbol) {
		return false;
	}

	XTestFakeKeyEvent(handle_, keyCode, 1, CurrentTime);
	XTestFakeKeyEvent(handle_, keyCode, 0, CurrentTime);
	XFlush(handle_);

	return true;
}

/**
 * 鼠标坐标移动
 *
 * @x，@y 鼠标坐标
 */
bool VirKey::MoveMouseTo(int x, int y)
{
	assert(handle_);

	if (!XTestFakeMotionEvent(handle_, -1, x, y, CurrentTime)) {
	        return false;
	}

	return true;
}

/**
 * 在当前坐标模拟鼠标消息
 *
 * @type 为鼠标按键类型
 * 	MLEFT 为左键，MMIDDLE 为中键，MRIGHT 为右键
 */
bool VirKey::MButtonPress(VirKeyMType type, bool isPress)
{
	assert(handle_);

	if (!XTestFakeButtonEvent(handle_, type, isPress, CurrentTime)) {
		return false;
	}

	return true;
}

/**
 * 发送一个鼠标按键点击消息
 */
bool VirKey::MbuttonPressOnce(VirKeyMType type)
{
	assert(handle_);

	if (!XTestFakeButtonEvent(handle_, type, 1, CurrentTime)) {
		return false;
	}

	if (!XTestFakeButtonEvent(handle_, type, 0, CurrentTime)) {
		return false;
	}

	return true;
}

#if 0
// 编译方法 g++ -lX11 -lXtst
int main(void)
{
	VirKey virkey;

	virkey.PressKeyOnce('a');
	virkey.PressKeyOnce('b');
	virkey.PressKeyOnce('c');
}
#endif
