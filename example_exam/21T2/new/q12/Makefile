# COMP2521 Final Exam
# mergeOrdered

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

all: testMergeOrdered

testMergeOrdered: testMergeOrdered.o mergeOrdered.o list.o
	$(CC) $(CFLAGS) -o testMergeOrdered testMergeOrdered.o mergeOrdered.o list.o

testMergeOrdered.o: testMergeOrdered.c list.h
mergeOrdered.o: mergeOrdered.c list.h
list.o: list.c list.h

clean:
	rm -f testMergeOrdered *.o core

