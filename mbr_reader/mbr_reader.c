/*
 * =====================================================================================
 *
 *       Filename:  mbr_reader.c
 *
 *    Description:  读取磁盘MBR的小程序
 *
 *        Version:  1.0
 *        Created:  2013年06月06日 18时04分17秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hurley (LiuHuan), liuhuan1992@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */

#include <unistd.h>
#include <fcntl.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define SECTION_SIZE    512 	// 扇区大小
#define MBR_CODE_LENGTH 446 	// MBR 引导代码长度
#define PARTITION_SIZE   16 	// 分区表项大小
#define PARTITION_COUNT   4 	// 分区表项目个数

#pragma pack(push, 1)  	// 保存对齐状态 & 设定为1字节对齐
typedef
struct _partition_info
{
	unsigned char active_flag; 		// 活动分区标记，0x00表示非活动, 0x80表示活动
	unsigned char start_CHS[3]; 		// 起始磁头号，扇区号，柱面号。其中磁头号1字节，扇区号2字节的低6位，柱面号2字节的高2位+3字节
	unsigned char partition_type; 		// 分区类型
	unsigned char end_CHS[3]; 		// 结束磁头号，含义同起始磁头号
	unsigned int  start_sector; 	 	// 逻辑起始扇区号
	unsigned int  number_of_sectors; 	// 所占用扇区数
}partition_info;

typedef
struct _mbr_info
{
	unsigned char  mbr_code[MBR_CODE_LENGTH]; 	// 主引导代码
	partition_info partition[PARTITION_COUNT]; 	// 4 个主分区表信息
	unsigned short magic_num; 			// 魔数 0xAA55
}mbr_info;
#pragma pack(pop) 	// 恢复对齐状态

void print_partition_info(partition_info *part_info);

int main(int argc, char *argv[])
{
	int 		disk_fd;
	size_t 		read_count;
	unsigned char 	mbr_data[SECTION_SIZE];
	
	disk_fd = open("/dev/sda", O_RDONLY);
	if (disk_fd == -1) {
		printf("What the fuck? Open '/dev/sda' error. Please run it as root.\n");
		return EXIT_FAILURE;
	}

	read_count = read(disk_fd, mbr_data, SECTION_SIZE);
	if (read_count != SECTION_SIZE) {
		printf("Read '/dev/sda'error.\n");
		return EXIT_FAILURE;
	}
	
	close(disk_fd);
	
	printf("MBR 十六进制数据:\n");
	int i;
	for (i = 0; i < SECTION_SIZE; i++) {
		printf("%02hhX ", mbr_data[i]);
		if ((i+1) % 32 == 0) {
			printf("\n");
		}
	}
	
	mbr_info *mbr = (mbr_info *)mbr_data;

	for (i = 0; i < PARTITION_COUNT; i++) {
		printf("\n分区表项 %d：\n\n", i + 1);
		print_partition_info(&(mbr->partition[i]));
	}

	return EXIT_SUCCESS;
}

void print_partition_info(partition_info *part_info)
{
	/* 
	 * 对于现代大于 8.4 G 的硬盘，CHS 已经无法表示。
	 * BIOS 使用 LBA 模式，对于超出的部分，CHS 值通常设为 FEFFFF, 并加以忽略。
	 * 直接使用 08-0f 的4字节相对值，再进行内部转换。
	 */
	printf("分区活动标记： %02hhX\n", part_info->active_flag);
	printf("分区起始磁头、扇区、柱面号（未分割）：%02hhX%02hhX%02hhX\n", 
			part_info->start_CHS[0], part_info->start_CHS[1], part_info->start_CHS[2]);
	printf("分区类型：     %02hhX\n", part_info->partition_type);
	printf("分区结束磁头、扇区、柱面号（未分割）：%02hhX%02hhX%02hhX\n", 
			part_info->end_CHS[0], part_info->end_CHS[1], part_info->end_CHS[2]);
	printf("逻辑起始扇区号：%u\n", part_info->start_sector);
	printf("所占扇区数量：  %u\n", part_info->number_of_sectors);
}

