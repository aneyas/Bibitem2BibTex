CC=clang

SOURCE := $(wildcard src/*.c)
CIISOURCE := $(wildcard cii_src/*.c)

SRCOBJ := $(SOURCE:src/%.c=obj/%.o) 
CIISRCOBJ := $(CIISOURCE:cii_src/%.c=obj/%.o)


#Note mem.o and memchk.o cannot appear at the same time.
convert:$(SRCOBJ) $(CIISRCOBJ)
	$(CC) -o $@ $<

$(SRCOBJ):obj/%.o:src/%.c
	$(CC) -c $< -o $@ -Iinclude

$(CIISRCOBJ):obj/%.o:cii_src/%.c
	$(CC) -c $< -o $@ -Icii_include


.PHONY: clean

clean:
	rm -f obj/*.o convert
