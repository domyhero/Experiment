#!Makefile

obj-m = print.o
KERNEL_VERSION = $(shell uname -r)
KERNEL_DIR=/usr/src/kernels/$(KERNEL_VERSION)
PWD = $(shell pwd)

all:
	$(MAKE) -C $(KERNEL_DIR) SUBDIRS=$(PWD) modules


