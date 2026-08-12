# COMP2521 Final Exam
# equalBST

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

all: testEqualBST

testEqualBST: testEqualBST.o equalBST.o BSTree.o
	$(CC) $(CFLAGS) -o testEqualBST testEqualBST.o equalBST.o BSTree.o

testEqualBST.o: testEqualBST.c BSTree.h
equalBST.o: equalBST.c BSTree.h
BSTree.o: BSTree.c BSTree.h

clean:
	rm -f testEqualBST *.o core

