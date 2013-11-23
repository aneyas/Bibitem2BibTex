CC=clang
DEBUG=
OPT=-O2

ifdef $(DEBUG)
	OPT=$(OPT) -g
endif

SOURCE := $(wildcard src/*.c)
CIISOURCE := $(wildcard cii_src/*.c)

SRCOBJ := $(SOURCE:src/%.c=obj/%.o) 
CIISRCOBJ := $(CIISOURCE:cii_src/%.c=obj/%.o)

INCLUDE := $(wildcard include/*.h)


#Note mem.o and memchk.o cannot appear at the same time.
convert:$(SRCOBJ) $(CIISRCOBJ)
	$(CC) -o $@ $^ $(OPT)

$(SRCOBJ):obj/%.o:src/%.c $(INCLUDE)
	$(CC) -c $< -o $@ -Iinclude -Icii_include $(OPT)

$(CIISRCOBJ):obj/%.o:cii_src/%.c
	$(CC) -c $< -o $@ -Icii_include $(OPT)


.PHONY: clean

clean:
	rm -f obj/*.o convert
