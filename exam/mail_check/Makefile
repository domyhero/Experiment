#Makefile

OBJECT = unit_test.o mail_check.o
ELF = unit_test
LINK = -lgtest -lpthread

CXX = g++ -g

unit_test: unit_test.o mail_check.o
	${CXX} -Wall $^ -o $@ ${LINK}
mail_check.o: mail_check.c
	${CXX} -Wall -c $< -o $@
unit_test.o: unit_test.cpp
	${CXX} -Wall -c $< -o $@
	
.PHONY:clean
clean:
	${RM} ${OBJECT} ${ELF}
