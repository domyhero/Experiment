#!Makefile

C_SOURCES = $(shell find . -name "*.c")

CC = gcc

C_FLAGS = -Wall -g -I/home/hurley/Program/lib/include -L/home/hurley/Program/lib/lib -lev

all:
	@echo 编译代码文件 $< ...
	$(CC) $(C_FLAGS) $(C_SOURCES) -o server


.PHONY:clean
clean:
	$(RM) $(S_OBJECTS) $(C_OBJECTS) server

