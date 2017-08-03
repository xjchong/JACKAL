CXX:=g++
CXXFLAGS:=-std=c++14 -Wall -MMD
EXEC:=JACKAL
SRC:=$(shell find src -name "*.cc")
OBJ:=${SRC:.cc=.o} main.o
DEP:=${OBJ:.o=.d}

${EXEC}: ${OBJ}
	${CXX} ${CXXFLAGS} ${OBJ} -lBearLibTerminal -o ${EXEC}
-include ${DEP}

clean:
	rm ${OBJ} ${DEP}
.PHONY: clean
