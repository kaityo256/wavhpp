all: a.out

CC=g++
CPPFLAGS=-Wall -Wextra

a.out: sample.cpp wav.hpp
	$(CC) $(CPPFLAGS) $< -o $@

.PHONY: clean

clean:
	rm -f a.out
	rm -f test.wav
