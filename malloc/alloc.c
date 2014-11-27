/*
 * =====================================================================================
 *
 *       Filename:  alloc.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年10月20日 14时42分29秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Qianyi.lh (liuhuan), qianyi.lh@alibaba-inc.com
 *        Company:  Alibaba-Inc Aliyun
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
        int count = 0;

        while (malloc(1*1024*1024) != NULL) {
                count++;
        }
        printf("count is %f G\n", count / 1024.0f);

        return EXIT_SUCCESS;
}


