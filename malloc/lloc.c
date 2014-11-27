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
#include <assert.h>

int main(int argc, char *argv[])
{
        int count = 0;
        char *p = NULL;

        while ((p = malloc(1*1024*1024)) != NULL) {
                count++;
                int i = 0;
                for (i = 0; i < 1024*1024; i++) {
                        *(p+i) = 0;
                }
        }
        printf("count is %f G\n", count / 1024.0f);

        sleep(10000);

        return EXIT_SUCCESS;
}


