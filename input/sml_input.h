/*
 * =====================================================================================
 *
 *       Filename:  sml_input.h
 *
 *    Description:  sml消息库
 *
 *        Version:  1.0
 *        Created:  2014年03月26日 09时08分49秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hurley (LiuHuan), liuhuan1992@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */

#ifndef SML_INPUT_H_
#define SML_INPUT_H_

#include <X11/Xlib.h>
#include <X11/extensions/XTest.h>

#ifdef __cplusplus
extern "c"
{
#endif

#ifndef __cplusplus
typedef
enum {
	false = 0,
	true = 1
} bool;
#endif

typedef Display *sml_handle;;

/*
 * 初始化键消息模拟库
 */
sml_handle sml_init();

/*
 * 释放句柄资源
 */
void sml_destory(sml_handle handle);

// 鼠标键位定义
typedef 
enum {
	MLEFT = 1,
	MMIDDLE = 2,
	MRIGHT = 3
} mktype_t;

/*
 * 在某坐标模拟鼠标消息
 *
 * @x，@y 为鼠标坐标
 * @type 为鼠标按键类型
 * 	MLEFT 为左键，MMIDDLE 为中键，MRIGHT 为右键
 */
void sml_clickat(sml_handle handle, int x, int y, mktype_t type);

/**
 * 键盘按下抬起消息
 *
 * @key 模拟的键
 * @is_press 按下还是抬起
 */
bool sml_presskey(sml_handle handle, int key, bool is_press);

/*
 * 发送一个键盘按键消息
 */
bool sml_presskeyonce(sml_handle handle, int key);

/*
 * 鼠标坐标移动
 *
 * @x，@y 鼠标坐标
 */
bool sml_movemouseto(sml_handle handle, int x, int y);

/*
 * 在当前坐标模拟鼠标消息
 *
 * @type 为鼠标按键类型
 * 	MLEFT 为左键，MMIDDLE 为中键，MRIGHT 为右键
 */
bool sml_mbuttonpress(sml_handle handle, mktype_t type, bool is_press);

/*
 * 发送一个鼠标按键点击消息
 */
bool sml_mbuttonpressonce(sml_handle handle, mktype_t type);

#ifdef __cplusplus
}
#endif

#endif  // SML_INPUT_H_
