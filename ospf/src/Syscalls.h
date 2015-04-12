// =====================================================================================
//
//       Filename:  Syscalls.h
//
//    Description:  系统调用相关
//
//        Version:  1.0
//        Created:  2014年12月30日 15时16分44秒
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Qianyi.lh (liuhuan), qianyi.lh@alibaba-inc.com
//        Company:  Alibaba-Inc Aliyun
//
// =====================================================================================

#ifndef SYSCALLS_H_
#define SYSCALLS_H_

#include <stdint.h>

namespace ospf {

namespace syscall {

#define SYS_EXIT    0x0
#define SYS_OPEN    0x1
#define SYS_CLOSE   0x2
#define SYS_READ    0x3
#define SYS_WRITE   0x4

#define MAX_SYSCALL_NUM  0x4

bool syscall(uint32_t sysno, uint32_t *args);

int32_t get_syscall_nr_args(uint32_t sysno);

}

}

#endif  // SYSCALLS_H_
