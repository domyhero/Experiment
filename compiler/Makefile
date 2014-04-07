#!Makefile
#
# --------------------------------------------------------
#
#    词法分析器 2014/04/07
#
#	@hurley25
#
# --------------------------------------------------------
#

C_SOURCES = $(shell find . -name "*.cpp")
C_OBJECTS = $(patsubst %.cpp, %.o, $(C_SOURCES))

CC = g++

C_FLAGS = -c -g -Wall -std=c++11

all: $(C_OBJECTS) 
	@echo 链接 ...
	$(CC) $(C_OBJECTS) -o program

.cpp.o:
	@echo 编译代码文件 $< ...
	$(CC) $(C_FLAGS) $< -o $@

.PHONY:clean
clean:
	@echo 清理临时文件
	$(RM) $(C_OBJECTS)

