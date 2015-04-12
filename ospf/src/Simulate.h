// =====================================================================================
//
//       Filename:  Simulate.h
//
//    Description:  字节码解释器
//
//        Version:  1.0
//        Created:  2014年12月30日 14时56分28秒
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Qianyi.lh (liuhuan), qianyi.lh@alibaba-inc.com
//        Company:  Alibaba-Inc Aliyun
//
// =====================================================================================

#ifndef SIMULATE_H_
#define SIMULATE_H_

// 字节码定义
enum byte_code_t {
        SIMU_ADD = 0x1,
        SIMU_SUB = 0x2,
        SIMU_SYSCALL = 0x3
};

#define BYTE_CODE_MAX 0x3

namespace ospf {

namespace simulate {

bool simulate(uint8_t *byte_code, uint32_t code_len, uint8_t *byte_data, uint32_t data_len);

}

}

#endif // SIMULATE_H_
