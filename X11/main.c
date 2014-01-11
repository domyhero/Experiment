/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年12月02日 21时23分44秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hurley (LiuHuan), liuhuan1992@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	Display *disp = XOpenDisplay(NULL);
	
	Window win = XCreateSimpleWindow(disp, RootWindow(disp, DefaultScreen(disp)), 0, 0, 800, 600, 0, 0, 0);
	XSelectInput(disp, win, ButtonPressMask | KeyPressMask | ExposureMask);
	XMapRaised(disp, win);

	XEvent event;
	int running = 1;
	while (running) {
		XNextEvent(disp, &event);
		switch (event.type) {
	    	case MapNotify:
			running = 0;
		  	break;
		case ButtonPress:
			printf("ButtonPress\n");
			break;
		case KeyPress:
			printf("KeyPress\n");
			break;
		}
	}
	
	XDestroyWindow(disp, win);
	XCloseDisplay(disp);

	return EXIT_SUCCESS;
}

