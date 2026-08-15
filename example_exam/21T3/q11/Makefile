# COMP2521 Final Exam
# bstToArrays

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

all: testBstToArrays

testBstToArrays: testBstToArrays.c bstToArrays.c BSTree.c
	$(CC) $(CFLAGS) -o testBstToArrays testBstToArrays.c bstToArrays.c BSTree.c

clean:
	rm -f testBstToArrays

