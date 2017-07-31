CXX:=g++
CXXFLAGS:=-std=c++14 -Wall -Werror -MMD
EXEC:=JACKAL
SRC:=$(shell find src -name "*.cc")
OBJ:=${SRC:.cc=.o} main.o
DEP:=${OBJ:.o=.d}

${EXEC}: ${OBJ}
	${CXX} ${CXXFLAGS} ${OBJ} -lncurses -o ${EXEC}
-include ${DEP}

clean:
	rm ${OBJ} ${DEP}
.PHONY: clean
