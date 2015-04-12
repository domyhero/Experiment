/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  libev study
 *
 *        Version:  1.0
 *        Created:  2014年08月14日 09时37分19秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Qianyi.lh (liuhuan), qianyi.lh@alibaba-inc.com
 *        Company:  Alibaba-Inc Aliyun
 *
 * =====================================================================================
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>
#include <netinet/in.h>
#include <strings.h>

#include <ev.h>

#define PORT 8086
#define BUFFER_SIZE 512

void accept_cb(struct ev_loop *loop, struct ev_io *watcher, int revents);
void read_cb(struct ev_loop *loop, struct ev_io *watcher, int revents);
static void timeout_cb (EV_P_ ev_timer *w, int revents) ;

int main(void)
{
        int fd = socket(PF_INET, SOCK_STREAM, 0);
        if (fd < 0) {
                printf("socket error. errno:%d\n", errno);
                return -1;
        }

        struct sockaddr_in addr;
        bzero(&addr, sizeof(addr));
        addr.sin_family = AF_INET;
        addr.sin_port = htons(PORT);
        addr.sin_addr.s_addr = INADDR_ANY;

        if (bind(fd, (struct sockaddr*) &addr, sizeof(addr)) != 0) {
                printf("bind error.errno:%d\n",errno);
        }

        if (listen(fd, 10) < 0) {
                printf("listen error\n");
                return -1;
        }

        struct ev_loop *loop = ev_default_loop(0);

        ev_io socket_watcher;
        ev_io_init(&socket_watcher, accept_cb, fd, EV_READ);
        ev_io_start(loop, &socket_watcher);

        ev_timer timeout_watcher;
        ev_timer_init (&timeout_watcher, timeout_cb, 2, 2);
        ev_timer_start (loop, &timeout_watcher);

        while (1) {
                printf("ev_loop...\n") ;
                ev_loop(loop, 0);
        }

        return 0;
}

void accept_cb(struct ev_loop *loop, struct ev_io *watcher, int revents)
{
        if (EV_ERROR & revents) {
                printf("error event in accept\n");
                return;
        }

        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);

        int client_sd = accept(watcher->fd, (struct sockaddr *)&client_addr, &client_len);
        if (client_sd < 0) {
                printf("accept error\n");
                return;
        }
        printf("someone connected.\n");

        struct ev_io *w_client = (struct ev_io*)malloc(sizeof(struct ev_io));
        ev_io_init(w_client, read_cb, client_sd, EV_READ);
        ev_io_start(loop, w_client);
}

void read_cb(struct ev_loop *loop, struct ev_io *watcher, int revents)
{
        char buffer[BUFFER_SIZE] = {0};

        if (EV_ERROR & revents) {
                printf("error event in read");
                return;
        }

        ssize_t readn = recv(watcher->fd, buffer, BUFFER_SIZE, 0);
        if (readn < 0) {
                printf("read error, errno: %d\n", errno);
                return;
        }

        if (readn == 0) {
                printf("someone disconnected.errno: %d\n", errno);
                ev_io_stop(loop, watcher);
                free(watcher);
                return;
        } else {
                printf("get the message: %s", buffer);
        }

        // echo...
        send(watcher->fd, buffer, readn, 0);
}

static void timeout_cb(EV_P_ ev_timer *w, int revents)
{
        puts("timeout......");
}

