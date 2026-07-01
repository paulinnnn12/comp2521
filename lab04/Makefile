# COMP2521 - Week 4 Lab

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
all: runBst numCommonValues

runBst: runBst.c bst.c Queue.c
numCommonValues: numCommonValues.c bst.c Queue.c

.PHONY: clean
clean:
	rm -f runBst numCommonValues

