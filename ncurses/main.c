/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  ncurses 使用
 *
 *        Version:  1.0
 *        Created:  2013年06月11日 18时34分14秒
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
#include <ncurses.h>

int main(int argc, char *argv[])
{
	initscr(); 	/* init ncurses mode */
	noecho(); 	/* input is invisiable */
	cbreak(); 	/* no line buffering */
	printw("Hello world and also ncurses!\n");
	refresh(); 	/* let us see the string */
	getch(); 	/* just hold and wait for any key pressed */
	endwin(); 	/* leave ncurses mode */

	return EXIT_SUCCESS;
}
