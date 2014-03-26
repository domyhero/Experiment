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

// 不是c++编译器则自定义bool类型
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
 * 释放资源
 */
void sml_destory(sml_handle handle);

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
 *
 * MLEFT 为左键，MMIDDLE 为中键，MRIGHT 为右键
 */
void sml_clickat(sml_handle handle, int x, int y, mktype_t type);

#endif  // SML_INPUT_H_
