/*
 * =====================================================================================
 *
 *       Filename:  passwd_check.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年05月14日 17时17分43秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hurley (LiuHuan), liuhuan1992@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */

#include <assert.h>
#include <stdlib.h>
#include <string.h>

int passwd_check(const char *passwd)
{
	int i;
	int length;
	int char_types[4] = {0};
	int types = 0;
	
	assert(passwd != NULL);
	
	length = strlen(passwd);
	if (length < 8 || length > 16) {
		return 0;
	}

	for (i = 0; i < length; i++) {
		if (passwd[i] >= 'a' && passwd[i] <= 'z') {
			char_types[0] = 1;
			continue;
		} else if (passwd[i] >= 'A' && passwd[i] <= 'Z') {
			char_types[1] = 1;
			continue;
		} else if (passwd[i] >= '0' && passwd[i] <= '9') {
			char_types[2] = 1;
			continue;
		} else if (passwd[i] == '~' || passwd[i] == '!'  || passwd[i] == '@' || passwd[i] == '#'  ||
		    	   passwd[i] == '$' || passwd[i] == '%'  || passwd[i] == '^') {
			char_types[3] = 1;
			continue;
		} else {
			return 0;
		}
	}
	
	for (i = 0; i < 4; i++) {
		if (char_types[i] == 1) {
			types++;
		}
	}
	
	if (types < 3) {
		return 0;
	}
	
	return 1;
}
