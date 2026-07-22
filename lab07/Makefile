# COMP2521 - Week 7 Lab

# !!! DO NOT MODIFY THIS FILE !!!

CC = clang
CFLAGS = -Wall -Wvla -Werror -gdwarf-4

########################################################################

.PHONY: asan msan nosan

asan: CFLAGS += -fsanitize=address,leak,undefined
asan: all

msan: CFLAGS += -fsanitize=memory,undefined -fsanitize-memory-track-origins
msan: all

nosan: all

########################################################################

.PHONY: all
all: bfsTree dfsTree shortestPath cycle furthestVertex largestComponent iterativeDfsTree

bfsTree: bfsTree.c GraphAdjList.c graphReader.c Queue.c
dfsTree: dfsTree.c GraphAdjMatrix.c graphReader.c
shortestPath: shortestPath.c GraphAdjMatrix.c graphReader.c Queue.c
cycle: cycle.c GraphAdjList.c graphReader.c Queue.c
furthestVertex: furthestVertex.c GraphAdjList.c graphReader.c Queue.c
largestComponent: largestComponent.c GraphAdjMatrix.c graphReader.c Queue.c

iterativeDfsTree: iterativeDfsTree.c GraphAdjList.c graphReader.c Stack.c

.PHONY: clean
clean:
	rm -f bfsTree dfsTree shortestPath cycle furthestVertex largestComponent iterativeDfsTree

