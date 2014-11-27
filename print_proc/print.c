/*
 * =====================================================================================
 *
 *       Filename:  print.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年09月15日 15时35分24秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Qianyi.lh (liuhuan), qianyi.lh@alibaba-inc.com
 *        Company:  Alibaba-Inc Aliyun
 *
 * =====================================================================================
 */

#include <linux/kernel.h> 
#include <linux/module.h> 
#include <linux/init.h> 

static int __init print_init(void)
{
        printk("Hello Kernel\n");
        
        return 0;
}

static void __exit print_exit(void)
{
        printk("Goodbye kernel\n");
}

module_init(print_init);
module_exit(print_exit);
MODULE_AUTHOR("hurley");
MODULE_DESCRIPTION("Print Process Info.");
MODULE_LICENSE("GPL");
