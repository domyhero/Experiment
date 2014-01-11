/*
 * =====================================================================================
 *
 *       Filename:  mail_check.c
 *
 *    Description:  邮件检测
 *
 *        Version:  1.0
 *        Created:  2013年05月14日 18时20分23秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hurley (LiuHuan), liuhuan1992@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */

#include <assert.h>
#include <string.h>
#include <stdlib.h>

int mail_check(const char *str_mail)
{
	assert(str_mail != NULL);

	int i;
	int length;

	if (str_mail[0] == '@') {
		return 0;
	}
	
	length = strlen(str_mail);
	for (i = 0; i < length; i++) {
		if (str_mail[i] >= 'A' && str_mail[i] <= 'Z') {
			continue;
		} else if (str_mail[i] >= 'a' && str_mail[i] <= 'z') {
			continue;
		} else if (str_mail[i] >= '0' && str_mail[i] <= '9') {
			continue;
		} else if (str_mail[i] == '@') {
			break;
		} else {
			return 0;
		}
	}

	if (strcmp("@qq.com", str_mail + i) == 0) {
		return 1;
	} else if (strcmp("@163.com", str_mail + i) == 0) {
		return 1;
	} else if (strcmp("@gmail.com", str_mail + i) == 0) {
		return 1;
	} else if (strcmp("@hotmail.com", str_mail + i) == 0) {
		return 1;
	} else if (strcmp("@sina.com.cn", str_mail + i) == 0) {
		return 1;
	}

	return 0;
}

