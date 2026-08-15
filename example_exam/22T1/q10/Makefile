# COMP2521 Final Exam

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

all: testMaxDiff

testMaxDiff: testMaxDiff.c maxDiff.c BSTree.c
	$(CC) $(CFLAGS) -o testMaxDiff testMaxDiff.c maxDiff.c BSTree.c

clean:
	rm -f testMaxDiff

