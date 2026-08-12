# COMP2521 Final Exam
# rankPopularity

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

all: testRankPopularity

testRankPopularity: testRankPopularity.o rankPopularity.o Graph.o
	$(CC) $(CFLAGS) -o testRankPopularity testRankPopularity.o rankPopularity.o Graph.o

testRankPopularity.o: testRankPopularity.c Graph.h
rankPopularity.o: rankPopularity.c Graph.h
Graph.o: Graph.c Graph.h

clean:
	rm -f testRankPopularity *.o core

