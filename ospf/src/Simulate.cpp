// =====================================================================================
//
//       Filename:  Simulate.cpp
//
//    Description:  字节码解释器
//
//        Version:  1.0
//        Created:  2014年12月30日 14时56分07秒
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Qianyi.lh (liuhuan), qianyi.lh@alibaba-inc.com
//        Company:  Alibaba-Inc Aliyun
//
// =====================================================================================

#include <stdint.h>
#include <iostream>

#include "CurrentThread.h"
#include "Simulate.h"
#include "Syscalls.h"

namespace ospf {

namespace simulate {

typedef int32_t (*sim_func_t)(uint8_t *, uint8_t *);

static int32_t sim_add(uint8_t *byte_code, uint8_t *byte_data);

static int32_t sim_sub(uint8_t *byte_code, uint8_t *byte_data);

static int32_t sim_syscall(uint8_t *byte_code, uint8_t *byte_data);

// 具体字节码处理函数
static sim_func_t sim_func[BYTE_CODE_MAX + 1] = {
        NULL,
        &sim_add,
        &sim_sub,
        &sim_syscall
};

bool simulate(uint8_t *byte_code, uint32_t code_len, uint8_t *byte_data, uint32_t data_len)
{
        for (uint32_t i = 0; i < code_len; ++i) {
                if (CurrentThread::is_intr) {
                        if (CurrentThread::intr_no != 0) {
                                // TODO 中断处理
                        }
                }
                if (byte_code[i] <= 0 || byte_code[i] > BYTE_CODE_MAX) {
                        // errno = XXXX
                        return false;
                }
                
                sim_func[byte_code[0]](byte_code, byte_data);
        }
        
        return true;
}

static int32_t sim_add(uint8_t *byte_code, uint8_t *byte_data)
{
        return 0;
}

static int32_t sim_sub(uint8_t *byte_code, uint8_t *byte_data)
{
        return 0;
}

static int32_t sim_syscall(uint8_t *byte_code, uint8_t *byte_data)
{
        uint32_t *word_data = (uint32_t *)byte_data;
        uint32_t sysno = *word_data++;
        int32_t nr_args = syscall::get_syscall_nr_args(sysno);
        uint32_t nr_data = 1;
        
        if (nr_args == -1) {
                // ........
        }
        
        uint32_t fileno;
        uint8_t *buffer = NULL;
        uint32_t len;
        if (nr_args > 0) {
                if (sysno == SYS_WRITE) {
                        fileno = *word_data++;
                        len = *word_data++;
                        buffer = new uint8_t[len];
                
                        uint32_t count = (len + sizeof(uint32_t)-1) / sizeof(uint32_t); 
                        uint32_t *pbuff = (uint32_t *)buffer;
                        for (uint32_t i = 0; i < count; ++i) {
                                pbuff[i] = *word_data++;
                        }
                        
                        nr_data += count;
                        
                } // TODO else
                
                uint32_t *args = new uint32_t[nr_args];
                args[0] = fileno;
                args[1] = (uint32_t)buffer;
                args[2] = len;
                                
                syscall::syscall(sysno, args);
                if (buffer) {
                        delete []buffer;
                        buffer = NULL;
                }
                delete []args;
        } else {
                syscall::syscall(sysno, NULL);
        }

        // nr_data + sysno
        return (nr_data + 1) * sizeof(uint32_t);
}

}       // namespace Simulate

}       // namespace ospf
