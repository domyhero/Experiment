/*
 * =====================================================================================
 *
 *       Filename:  change_reg.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年11月15日 22时49分49秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hurley (LiuHuan), liuhuan1992@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */

#include <linux/module.h> 
#include <linux/init.h> 
#include <linux/sched.h>
#include <linux/pid.h>
#include <asm/syscalls.h>

static int pid; 
static unsigned int va; 

module_param(pid, int, 0644); 
module_param(va, uint, 0644); 

static int __init change_reg_init(void)
{
	struct task_struct *task;
	struct pt_regs *regs;

	if ((task = pid_task(find_vpid(pid), PIDTYPE_PID)) == NULL) {
		printk("<1> Cannot Find pid: %d\n", pid);
	}

	printk("Find pid %d succeed!\n", task->pid);

	regs = task_pt_regs(task);

	printk("ss: 0x%lX\n", regs->ss);
	printk("esp: 0x%lX\n", regs->sp);
	printk("ebp: 0x%lX\n", regs->bp);
	printk("cs: 0x%lX\n", regs->cs);
	printk("eip: 0x%lX\n", regs->ip);

	regs->ip = 0x8048523;
	//regs->sp = regs->bp;

	return 0;
}

static void __exit change_reg_exit(void)
{
	printk("<1> Goodbye, change_reg!\n");
}

module_init(change_reg_init);
module_exit(change_reg_exit);
MODULE_AUTHOR("hurley");
MODULE_DESCRIPTION("change reg Info.");
MODULE_LICENSE("GPL");

