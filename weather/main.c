/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  向中国天气网获取天气数据
 *
 *        Version:  1.0
 *        Created:  2013年12月16日 12时09分57秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hurley (LiuHuan), liuhuan1992@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SER_IP "113.108.239.105"
#define SER_PORT 80
#define HTTP_REQ "GET /data/sk/101110101.html HTTP/1.1\r\nHost:www.weather.com.cn\r\nConnection:close\r\n\r\n"
#define BUFSIZE 4096

int main(int argc, char *argv[])
{
	int conn_fd = socket(AF_INET, SOCK_STREAM, 0);
	
	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(SER_PORT);
	server_addr.sin_addr.s_addr = inet_addr(SER_IP);
	
	connect(conn_fd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr_in));

	send(conn_fd, HTTP_REQ, strlen(HTTP_REQ), 0);

	char recv_buf[BUFSIZE];
	int length = 0, counts = 0;
	do {
		length = recv(conn_fd, recv_buf + counts, BUFSIZE - counts, 0);
		counts += length;
	} while (length != 0);
	
	recv_buf[counts] = '\0';

	char *start = strstr(recv_buf, "{\"weatherinfo");

	// 结尾的匹配过于简陋，作为这里的特例只是勉强能用罢了。可以考虑正则表达式匹配。
	char *end = strstr(recv_buf, "}}");
	if (start  == NULL || end == NULL) {
		printf("Recv Error!");
		puts(recv_buf);
		exit(-1);
	}
	*(end + 2) = '\0';

	puts(start);

	close(conn_fd);

	return EXIT_SUCCESS;
}

