#!/bin/bash

CC=clang
CFLAGS=-g -Wall -std=c11
OBJS=shared/shared_mem.o 
EXE=wrshmem.elf rdshmem.elf destroy_blk.elf

all: $(EXE)

%.elf: %.o $(OBJS)
	$(CC) $(CFLAGS) $< $(OBJS) -o $@


%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf *.dSYM *.o $(EXE)
