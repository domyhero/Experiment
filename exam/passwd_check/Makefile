#Makefile

OBJECT = unit_test.o passwd_check.o
ELF = unit_test
LINK = -lgtest -lpthread

unit_test: unit_test.o passwd_check.o
	${CXX} -Wall $^ -o $@ ${LINK}
passwd_check.o: passwd_check.c
	${CXX} -Wall -c $< -o $@
unit_test.o: unit_test.cpp
	${CXX} -Wall -c $< -o $@
	
.PHONY:clean
clean:
	${RM} ${OBJECT} ${ELF}
