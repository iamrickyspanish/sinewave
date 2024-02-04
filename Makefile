CC=gcc
SRCDIR=src
OBJDIR=obj
DSTDIR=dst
DEPDIR=dep
#INCDIR=inc

CFLAGS=-Wall -g
IFLAGS=-Isrc/inc -I$(DEPDIR)/rbuffer/inc -I$(DEPDIR)/raylib/include -L$(DEPDIR)/raylib/lib
LFLAGS=-lraylib -lm
# SRCS=$(SRCDIR)/sinewave.c $(DEPDIR)/rbuffer/src/rbuffer.c
OBJS=$(OBJDIR)/sinewave.o $(OBJDIR)/rbuffer.o $(OBJDIR)/lib/ioaudio.o $(OBJDIR)/lib/osc.o $(OBJDIR)/lib/keyboard.o $(OBJDIR)/lib/voice.o $(OBJDIR)/lib/engine.o $(OBJDIR)/lib/list.o#$(DEPDIR)/raylib/lib/libraylib.a

all: $(OBJS)
	$(CC) $(CFLAGS) $(IFLAGS) $(OBJS) -o $(DSTDIR)/sinewave $(LFLAGS)

$(OBJDIR)/rbuffer.o: $(DEPDIR)/rbuffer/src/rbuffer.c
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

$(OBJDIR)/sinewave.o: $(SRCDIR)/sinewave.c
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

$(OBJDIR)/lib/ioaudio.o: $(SRCDIR)/lib/ioaudio.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

$(OBJDIR)/lib/osc.o: $(SRCDIR)/lib/osc.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

$(OBJDIR)/lib/keyboard.o: $(SRCDIR)/lib/keyboard.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

$(OBJDIR)/lib/voice.o: $(SRCDIR)/lib/voice.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

$(OBJDIR)/lib/engine.o: $(SRCDIR)/lib/engine.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

$(OBJDIR)/lib/list.o: $(SRCDIR)/lib/list.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@
# $(OBJ): $(SRCS)
# 	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f obj/**/*.o obj/*.o dst/*

test: __tests__/lib/list.test.c src/lib/list.c
	$(CC) $(CFLAGS) $(IFLAGS) $< src/lib/list.c -o $(DSTDIR)/test