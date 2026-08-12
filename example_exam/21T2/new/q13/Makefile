# COMP2521 Final Exam
# nodesNotBalanced

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

all: testNodesNotBalanced

testNodesNotBalanced: testNodesNotBalanced.o nodesNotBalanced.o BSTree.o
	$(CC) $(CFLAGS) -o testNodesNotBalanced testNodesNotBalanced.o nodesNotBalanced.o BSTree.o

testNodesNotBalanced.o: testNodesNotBalanced.c BSTree.h 
nodesNotBalanced.o: nodesNotBalanced.c BSTree.h 
BSTree.o: BSTree.c BSTree.h 

clean:
	rm -f testNodesNotBalanced *.o core

