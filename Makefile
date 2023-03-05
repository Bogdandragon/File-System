all: build

build:
	gcc -Wall -g -o tema3 tema3.c

clean:
	rm -rf tema3