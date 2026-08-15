# COMP2521 Final Exam
# numSubsequences

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

all: testNumSubsequences

testNumSubsequences: testNumSubsequences.c numSubsequences.c list.c
	$(CC) $(CFLAGS) -o testNumSubsequences testNumSubsequences.c numSubsequences.c list.c

clean:
	rm -f testNumSubsequences

