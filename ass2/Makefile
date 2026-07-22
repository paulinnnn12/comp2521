# COMP2521 - Assignment 2

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
all: testStation testEvacuation

testStation: testStation.c Station.c
	$(CC) $(CFLAGS) -o testStation testStation.c Station.c

testEvacuation: testEvacuation.c evacuation.c Station.c stationReader.c
	$(CC) $(CFLAGS) -o testEvacuation testEvacuation.c evacuation.c Station.c stationReader.c

.PHONY: clean
clean:
	rm -f testStation testEvacuation

