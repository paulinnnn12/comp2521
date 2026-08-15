# COMP2521 Final Exam
# totalTextSize

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

all: testFs

testFs: testFs.c totalTextSize.c Fs.c
	$(CC) $(CFLAGS) -o testFs testFs.c totalTextSize.c Fs.c

clean:
	rm -f testFs

