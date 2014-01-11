/*
 * =====================================================================================
 *
 *       Filename:  epoll.c
 *
 *    Description:  测试 epoll
 *
 *        Version:  1.0
 *        Created:  2013年11月14日 16时53分58秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hurley (LiuHuan), liuhuan1992@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */

#define _GNU_SOURCE

#include <unistd.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <sys/fcntl.h>
#include <linux/sysctl.h>
#include <sys/resource.h>

#define SERVER_PORT 9527
#define MAX_EVENTS 10000

#define RECV_BUFF 1024

char *send_info = "Hello epoll!\n";

int main(int argc, char *argv[])
{
	struct rlimit rt;
	rt.rlim_max = rt.rlim_cur = MAX_EVENTS;

	//if (setrlimit(RLIMIT_NOFILE, &rt) == -1) {
	//	perror("setrlimit");
	//	exit(EXIT_FAILURE);
	//}

	int listen_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_sock == -1) {
		perror("socket");
		exit(EXIT_FAILURE);
	}
	
	int optval = 1;
	if (setsockopt(listen_sock, SOL_SOCKET, SO_REUSEADDR, (void *)&optval, sizeof( int )) < 0) {
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}

	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(SERVER_PORT);
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(listen_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
		perror("bind");
		exit(EXIT_FAILURE);
	}

	if (listen(listen_sock, 512) == -1) {
		perror("listen");
		exit(EXIT_FAILURE);
	}

	int epollfd = epoll_create(MAX_EVENTS);
	if (epollfd == -1) {
		perror("epoll_create");
		exit(EXIT_FAILURE);
	}

	struct epoll_event ev;
	bzero(&ev, sizeof(ev));
	ev.events = EPOLLIN | EPOLLET;
	ev.data.fd = listen_sock;

	if (epoll_ctl(epollfd, EPOLL_CTL_ADD, listen_sock, &ev) == -1) {
		perror("epoll_ctl: listen_sock");
		exit(EXIT_FAILURE);
	}

	struct sockaddr_in client_addr;
	int addrlen = sizeof(client_addr);
	char recv_buff[RECV_BUFF];
	struct epoll_event events[MAX_EVENTS];
	while (1) {
		int nfds = epoll_wait(epollfd, events, MAX_EVENTS, -1);
		if (nfds == -1) {
			perror("epoll_wait");
			exit(EXIT_FAILURE);
		}
		for (int i = 0; i < nfds; ++i) {
			if (events[i].data.fd == listen_sock) {
				int conn_sock = accept4(listen_sock, (struct sockaddr *)&client_addr, &addrlen, SOCK_NONBLOCK);
				if (conn_sock == -1) {
					perror("accept");
					exit(EXIT_FAILURE);
				}
				ev.events = EPOLLIN | EPOLLET;
				ev.data.fd = conn_sock;
				if (epoll_ctl(epollfd, EPOLL_CTL_ADD, conn_sock, &ev) == -1) {
					perror("epoll_ctl: conn_sock");
					exit(EXIT_FAILURE);
				}
			} else if (events[i].events & EPOLLIN) {
				int n = 0;
				if (( n = read(events[i].data.fd, recv_buff, RECV_BUFF)) == 0) {
					continue;
				}
				recv_buff[n] = '\0';
				printf("%s\n", recv_buff);
				ev.data.fd = events[i].data.fd;
				ev.events = EPOLLOUT | EPOLLET;
				if (epoll_ctl(epollfd, EPOLL_CTL_MOD, events[i].data.fd, &ev) == -1) {
					perror("epoll_ctl: read");
					exit(EXIT_FAILURE);
				}
			} else if (events[i].events & EPOLLOUT) {
				write(events[i].data.fd, send_info, strlen(send_info));
				ev.data.fd = events[i].data.fd;
				ev.events = EPOLLIN | EPOLLET;
				if (epoll_ctl(epollfd, EPOLL_CTL_MOD, events[i].data.fd, &ev) == -1) {
					perror("epoll_ctl: write");
					exit(EXIT_FAILURE);
				}
			} else if (events[i].events & EPOLLHUP) {
				printf("hup fd: %d\n", events[i].data.fd);
			} else if (events[i].events & EPOLLERR) {
				printf("err fd: %d\n", events[i].data.fd);
			}
			
		}
	}

	close(epollfd);

	return EXIT_SUCCESS;
}

