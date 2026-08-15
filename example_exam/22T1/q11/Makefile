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

all: testNodesNotInCycle

testNodesNotInCycle: testNodesNotInCycle.c nodesNotInCycle.c Graph.c
	$(CC) $(CFLAGS) -o testNodesNotInCycle testNodesNotInCycle.c nodesNotInCycle.c Graph.c

clean:
	rm -f testNodesNotInCycle

