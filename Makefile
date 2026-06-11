# COMP2521 - Week 2 Lab

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
all: power fastPower rabbits listTail listFunniness listMax listInsertOrdered listSum listInsertNth listShift

power: power.c
fastPower: fastPower.c
rabbits: rabbits.c
listTail: listTail.c list.c
listFunniness: listFunniness.c list.c
listMax: listMax.c list.c
listInsertOrdered: listInsertOrdered.c list.c
listSum: listSum.c list.c
listInsertNth: listInsertNth.c list.c
listShift: listShift.c list.c

.PHONY: clean
clean:
	rm -f power fastPower rabbits listTail listFunniness listMax listInsertOrdered listSum listInsertNth listShift

