CC=gcc
LD=gcc
CFLAGS+=-Wall -Wextra
LDFLAGS+=
TARG=mipsregs

OFILES=\
	main.o\
	decode.o\
	regs.o\

HFILES=\
	dat.h\
	fns.h\

all: $(TARG)

$(TARG): $(OFILES) $(HFILES)
	$(LD) $(LDFLAGS) -o $(TARG) $(OFILES)

%.$.o: %.c
	$(CC) -c $(CFLAGS) $*.c

clean:
	rm -f *.$.o

nuke: clean
	rm -f $(TARG)
