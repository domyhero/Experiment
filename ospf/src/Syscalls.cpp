// =====================================================================================
//
//       Filename:  Syscalls.cpp
//
//    Description:  系统调用相关
//
//        Version:  1.0
//        Created:  2014年12月30日 15时19分28秒
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Qianyi.lh (liuhuan), qianyi.lh@alibaba-inc.com
//        Company:  Alibaba-Inc Aliyun
//
// =====================================================================================

#include <map>

#include <stdint.h>
#include <unistd.h>
#include <stdio.h>

#include "Syscalls.h"

namespace ospf {

namespace syscall {

/*
static int sys_exit()
{
        return 0;
}

static int sys_open()
{
        return 0;
}

static int sys_close()
{
        return 0;
}

static int sys_read()
{
        return 0;
}
*/

static int sys_write(uint32_t fileno, uint8_t *buffer, uint32_t len)
{
        if (fileno == STDOUT_FILENO) {
                write(STDOUT_FILENO, buffer, len);
        }
        
        return 0;
}

bool syscall(uint32_t sysno, uint32_t *args)
{
        switch (sysno) {
                case SYS_EXIT:
                        break;
                case SYS_OPEN:
                        break;
                case SYS_CLOSE:
                        break;
                case SYS_READ:
                        break;
                case SYS_WRITE:
                        sys_write((uint32_t)args[0], (uint8_t *)args[1], (uint32_t)args[2]);
                        break;
                default:
                        // Error sysno
                        break;
        }
        
        return true;
}

int32_t get_syscall_nr_args(uint32_t sysno)
{
        std::map<uint32_t, int32_t> sys_nr_args_map = {
                {SYS_EXIT, 0},
                {SYS_OPEN, 2},
                {SYS_CLOSE, 1},
                {SYS_READ, 3},
                {SYS_WRITE, 3}
        };

        if (sys_nr_args_map.find(sysno) != sys_nr_args_map.end()) {
                return sys_nr_args_map[sysno];
        }

        return -1;
}

} // namespace syscall

} // namespace ospf
