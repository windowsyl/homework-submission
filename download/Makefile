CC=clang
CFLAGS=-std=gnu11 -Wall $(shell curl-config --cflags) $(shell curl-config --libs)
DEBUG_CFLAGS=-O1 -g -fno-omit-frame-pointer -fno-optimize-sibling-calls -fsanitize=address

download: download.c
	$(CC) $(CFLAGS) download.c -o download

debug: download.c
	$(CC) $(CFLAGS) $(DEBUG_CFLAGS) download.c -o debug