/*
 * =====================================================================================
 *
 *       Filename:  inotify.c
 *
 *    Description:  inotify 机制的测试
 *
 *        Version:  1.0
 *        Created:  2014年03月28日 16时55分25秒
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
#include <sys/inotify.h>

int main(int argc, char *argv[])
{
	int handle = inotify_init();

	if (handle == -1) {
		perror("inotify_init");
	}

	if (inotify_add_watch(handle, "/home/hurley", IN_CREATE) == -1) {
		perror("watch");
	}

	char event_buf[1024];

	while (1) {
		int readn = read(handle, event_buf, 1024);
		if (readn == 0) {
			perror("read() return 0");
			return -1;
		} else if (readn == -1) {
			perror("read() error");
			return -1;
		}

		char *pbuf = event_buf;
		while (pbuf < event_buf + readn) {
			struct inotify_event *in_event = (struct inotify_event *)pbuf;
			if (in_event->mask & IN_CREATE) {
				printf("file \"/home/hurley/%s\" created!\n", in_event->name);
			}
			pbuf += sizeof(struct inotify_event) + in_event->len;
		}
	}

	return EXIT_SUCCESS;
}

