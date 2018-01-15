CXX = g++
CXXFLAGS = -std=c++14 -Wall -Werror -MMD -g
EXEC = main
OBJECTS = main.o game.o floor.o cell.o character.o shade.o player.o subject.o human.o dwarf.o halfling.o merchant.o dragon.o elf.o orcs.o enemy.o item.o decorator.o drow.o vampire.o goblin.o troll.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lncurses

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
.PHONY: clean
