XX = g++
CXXFLAGS = -std=c++14 -g -Wall -Werror=vla -MMD
EXEC = straights
OBJECTS = main.o card.o board.o component.o decorator.o player.o human.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC} : ${OBJECTS}
		                ${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

clean :
		                rm ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS} # reads the .d files and reruns dependencies
