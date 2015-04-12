// =====================================================================================
//
//       Filename:  main.cpp
//
//    Description:  主函数入口
//
//        Version:  1.0
//        Created:  2014年12月30日 14时38分52秒
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Qianyi.lh (liuhuan), qianyi.lh@alibaba-inc.com
//        Company:  Alibaba-Inc Aliyun
//
// =====================================================================================

#include <iostream>
#include <functional>
#include <stdlib.h>

#include "ThreadPool.h"
#include "Simulate.h"

using namespace ospf;

int main(int argc, char *argv[])
{
        printf("OSPF Running ...\n");
        
        ThreadPool threadPool("OSPF Runtime");

        threadPool.setMaxQueueSize(100);

        threadPool.start(4);

        uint8_t byte_code[] = {0x3};
        uint32_t code_len = sizeof(byte_code);
        
        uint8_t byte_data0[] = {0x4, 0x0, 0x0, 0x0,   // 4
                                 0x1, 0x0, 0x0, 0x0,  // 1
                                 0xE, 0x0, 0x0, 0x0,  // 13
                                'H', 'e', 'l', 'l', 'o', ',', ' ', 'O', 'S', 'P', 'F', '0', '!', '\n'};
        
        uint8_t byte_data1[] = {0x4, 0x0, 0x0, 0x0,   // 4
                                 0x1, 0x0, 0x0, 0x0,  // 1
                                 0xE, 0x0, 0x0, 0x0,  // 13
                                'H', 'e', 'l', 'l', 'o', ',', ' ', 'O', 'S', 'P', 'F', '1', '!', '\n'};
                                
        uint8_t byte_data2[] = {0x4, 0x0, 0x0, 0x0,   // 4
                                 0x1, 0x0, 0x0, 0x0,  // 1
                                 0xE, 0x0, 0x0, 0x0,  // 13
                                'H', 'e', 'l', 'l', 'o', ',', ' ', 'O', 'S', 'P', 'F', '2', '!', '\n'};
                                
        uint8_t byte_data3[] = {0x4, 0x0, 0x0, 0x0,   // 4
                                 0x1, 0x0, 0x0, 0x0,  // 1
                                 0xE, 0x0, 0x0, 0x0,  // 13
                                'H', 'e', 'l', 'l', 'o', ',', ' ', 'O', 'S', 'P', 'F', '3', '!', '\n'};
                                
        uint8_t byte_data4[] = {0x4, 0x0, 0x0, 0x0,   // 4
                                 0x1, 0x0, 0x0, 0x0,  // 1
                                 0xE, 0x0, 0x0, 0x0,  // 13
                                'H', 'e', 'l', 'l', 'o', ',', ' ', 'O', 'S', 'P', 'F', '4', '!', '\n'};

        uint8_t byte_data5[] = {0x4, 0x0, 0x0, 0x0,   // 4
                                 0x1, 0x0, 0x0, 0x0,  // 1
                                 0xE, 0x0, 0x0, 0x0,  // 13
                                'H', 'e', 'l', 'l', 'o', ',', ' ', 'O', 'S', 'P', 'F', '5', '!', '\n'};

        uint8_t byte_data6[] = {0x4, 0x0, 0x0, 0x0,   // 4
                                 0x1, 0x0, 0x0, 0x0,  // 1
                                 0xE, 0x0, 0x0, 0x0,  // 13
                                'H', 'e', 'l', 'l', 'o', ',', ' ', 'O', 'S', 'P', 'F', '6', '!', '\n'};

        uint8_t byte_data7[] = {0x4, 0x0, 0x0, 0x0,   // 4
                                 0x1, 0x0, 0x0, 0x0,  // 1
                                 0xE, 0x0, 0x0, 0x0,  // 13
                                'H', 'e', 'l', 'l', 'o', ',', ' ', 'O', 'S', 'P', 'F', '7', '!', '\n'};
                                
        uint8_t byte_data8[] = {0x4, 0x0, 0x0, 0x0,   // 4
                                 0x1, 0x0, 0x0, 0x0,  // 1
                                 0xE, 0x0, 0x0, 0x0,  // 13
                                'H', 'e', 'l', 'l', 'o', ',', ' ', 'O', 'S', 'P', 'F', '8', '!', '\n'};
                                
        uint8_t byte_data9[] = {0x4, 0x0, 0x0, 0x0,   // 4
                                 0x1, 0x0, 0x0, 0x0,  // 1
                                 0xE, 0x0, 0x0, 0x0,  // 13
                                'H', 'e', 'l', 'l', 'o', ',', ' ', 'O', 'S', 'P', 'F', '9', '!', '\n'};                         
                                
        uint32_t data_len = sizeof(byte_data1);

        threadPool.run(std::bind(simulate::simulate, byte_code, code_len, byte_data0, data_len));
        threadPool.run(std::bind(simulate::simulate, byte_code, code_len, byte_data1, data_len));
        threadPool.run(std::bind(simulate::simulate, byte_code, code_len, byte_data2, data_len));
        threadPool.run(std::bind(simulate::simulate, byte_code, code_len, byte_data3, data_len));
        threadPool.run(std::bind(simulate::simulate, byte_code, code_len, byte_data4, data_len));
        threadPool.run(std::bind(simulate::simulate, byte_code, code_len, byte_data5, data_len));
        threadPool.run(std::bind(simulate::simulate, byte_code, code_len, byte_data6, data_len));
        threadPool.run(std::bind(simulate::simulate, byte_code, code_len, byte_data7, data_len));
        threadPool.run(std::bind(simulate::simulate, byte_code, code_len, byte_data8, data_len));
        threadPool.run(std::bind(simulate::simulate, byte_code, code_len, byte_data9, data_len));
        
        sleep(1);
        
        uint8_t byte_data10[] = {0x4, 0x0, 0x0, 0x0,   // 4
                                   0x1, 0x0, 0x0, 0x0,  // 1
                                   0xE, 0x0, 0x0, 0x0,  // 13
                                  'H', 'e', 'l', 'l', 'o', ',', ' ', 'O', 'S', 'P', 'F', '~', '!', '\n'};
        
        char choice = 'N';
        do {
                printf("Add Task(Y/N)? : ");
                scanf("%c", &choice);
                while (getchar() != '\n')
                        ;
                if (choice == 'Y') {
                        threadPool.run(std::bind(simulate::simulate, byte_code, code_len, byte_data10, data_len));
                }
                sleep(1);
        } while (choice == 'Y');
        
        threadPool.stop();

        return 0;
}

