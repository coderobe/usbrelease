CC:=gcc
LD:=gcc

CFLAGS:=-O3
LDFLAGS:=

SOURCES=usbrelease.c
OBJECTS=$(SOURCES:.c=.c.o)
TARGET:=usbrelease

.DEFAULT_GOAL=all

%.c.o: %.c
	${CC} ${CFLAGS} -c $< -o $@

${TARGET}: ${OBJECTS}
	${LD} ${LDFLAGS} -o $@ $+

.PHONY: all build debug

all: build

build: ${TARGET}

debug: CFLAGS+=-ggdb -D_DEBUG
debug: build

clean:
	rm -f ${TARGET} ${OBJECTS}
