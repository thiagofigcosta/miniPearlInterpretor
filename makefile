rwildcard=$(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2) $(filter $(subst *,%,$2),$d))
SCR=$(call rwildcard,,*.cpp)

all: make

make:
	g++ $(SCR) -g -std=c++11 -w -o miniPearlInterpretor

example:
	./miniPearlInterpretor alunos.mp