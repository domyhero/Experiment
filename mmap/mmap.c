/*
 * =====================================================================================
 *
 *       Filename:  mmap.c
 *
 *    Description:  mmap 拷贝文件
 *
 *        Version:  1.0
 *        Created:  2013年11月20日 20时53分49秒
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
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
	int fd_src = open("hosts", O_RDONLY);
	if (fd_src == -1) {
		perror("open hosts");
	}
	
	struct stat src_stat;
	if (fstat(fd_src, &src_stat) == -1) {
		perror("fstat");
	}
	
	int fd_dst = open("hosts.bak", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd_dst == -1) {
		perror("open hosts.bak");
	}
	if (lseek(fd_dst, src_stat.st_size-1, SEEK_SET) == -1) {
		perror("lseek");
	}

	if (write(fd_dst, "1", 1) != 1) {
		perror("write");
	}

	char *src = mmap(NULL, src_stat.st_size, PROT_READ, MAP_PRIVATE, fd_src, 0);
	if (!src) {
		perror("mmap src");
	}

	char *dst = mmap(NULL, src_stat.st_size, PROT_WRITE, MAP_SHARED, fd_dst, 0);
	if (!dst) {
		perror("mmap dst");
	}

	memcpy(dst, src, src_stat.st_size);

	munmap(src, src_stat.st_size);
	munmap(dst, src_stat.st_size);

	close(fd_src);
	close(fd_dst);

	return EXIT_SUCCESS;
}

