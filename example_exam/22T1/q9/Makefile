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

all: testZipList

testZipList: testZipList.c zipList.c list.c
	$(CC) $(CFLAGS) -o testZipList testZipList.c zipList.c list.c

clean:
	rm -f testZipList

