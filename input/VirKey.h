/*
 * =====================================================================================
 *
 *       Filename:  VirKey.h
 *
 *    Description:  XTest 消息库的 C++ 封装
 *
 *        Version:  1.0
 *        Created:  2014年03月27日 14时08分49秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hurley (LiuHuan), liuhuan1992@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */

#ifndef VIRKEY_H_
#define VIRKEY_H_

#include <X11/Xlib.h>
#include <X11/extensions/XTest.h>

/// 虚拟鼠标键盘模拟类
class VirKey {

	typedef Display *VirKeyHandle;

	/// 鼠标键位定义
	typedef enum {
		MLEFT = 1,
		MMIDDLE = 2,
		MRIGHT = 3
	} VirKeyMType;

public:
	/// 构造函数
	VirKey();

	/// 析构函数
	~VirKey();

	/**
	 * 在某坐标模拟鼠标消息
	 *
	 * @x，@y 为鼠标坐标
	 * @type 为鼠标按键类型
	 * 	MLEFT 为左键，MMIDDLE 为中键，MRIGHT 为右键
	 */
	void ClickAt(int x, int y, VirKeyMType type);

	/**
	 * 键盘按下抬起消息
	 *
	 * @key 模拟的键
	 * @is_press 按下还是抬起
	 */
	bool PressKey(int key, bool isPress);

	/**
	 * 发送一个键盘按键消息
	 */
	bool PressKeyOnce(int key);

	/**
	 * 鼠标坐标移动
	 *
	 * @x，@y 鼠标坐标
	 */
	bool MoveMouseTo(int x, int y);

	/**
	 * 在当前坐标模拟鼠标消息
	 *
	 * @type 为鼠标按键类型
	 * 	MLEFT 为左键，MMIDDLE 为中键，MRIGHT 为右键
	 */
	bool MButtonPress(VirKeyMType type, bool isPress);

	/**
	 * 发送一个鼠标按键点击消息
	 */
	bool MbuttonPressOnce(VirKeyMType type);

private:
	VirKeyHandle handle_;
};

#endif  // VIRKEY_H_
