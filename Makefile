all: dis8080
all: examples

dis8080: dis8080.c

.PHONY: examples
examples: add.bin.dis0
examples: add.bin.dis1

add.bin.dis0: example/add.bin
	./dis8080 < example/add.bin > $@

add.bin.dis1: example/add.bin
	./dis8080 < example/add.bin > $@ -d 0x0009 2

.PHONY: clean
clean:
	rm -f dis8080
	rm -f add.bin.dis0
	rm -f add.bin.dis1

