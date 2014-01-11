#Makefile

OBJECT = gtest.o
ELF = gtest
LINK = -lgtest -lpthread

gtest: gtest.o
	@ echo '链接....'
	${CXX} -Wall $< -o $@ ${LINK}
gtest.o: gtest.cpp
	@ echo '编译...'
	${CXX} -Wall -c $< -o $@

.PHONY:clean
clean:
	${RM} ${OBJECT} ${ELF}
