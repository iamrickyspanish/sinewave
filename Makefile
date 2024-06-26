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
OBJS=$(OBJDIR)/sinewave.o $(OBJDIR)/rbuffer.o $(OBJDIR)/lib/ioaudio.o $(OBJDIR)/lib/osc.o $(OBJDIR)/lib/keyboard.o $(OBJDIR)/lib/voice.o $(OBJDIR)/lib/engine.o $(OBJDIR)/lib/list.o $(OBJDIR)/lib/mixer.o $(OBJDIR)/lib/sigpath.o #$(DEPDIR)/raylib/lib/libraylib.a

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

$(OBJDIR)/lib/mixer.o: $(SRCDIR)/lib/mixer.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@
# $(OBJ): $(SRCS)
# 	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/lib/sigpath.o: $(SRCDIR)/lib/sigpath.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

clean:
	rm -f obj/**/*.o obj/*.o dst/*

test_mixer: __tests__/lib/mixer.test.c src/lib/mixer.c
	$(CC) $(CFLAGS) $(IFLAGS) $< src/lib/mixer.c -o $(DSTDIR)/test_mixer

test_sigpath: __tests__/lib/sigpath.test.c src/lib/sigpath.c src/lib/mixer.c src/lib/osc.c
	$(CC) $(CFLAGS) $(IFLAGS)  $< src/lib/mixer.c src/lib/osc.c src/lib/sigpath.c -o $(DSTDIR)/test_sigpath ${LFLAGS}

test_voice: __tests__/lib/voice.test.c src/lib/sigpath.c src/lib/mixer.c src/lib/osc.c src/lib/list.c src/lib/voice.c
	$(CC) $(CFLAGS) $(IFLAGS)  $< src/lib/list.c src/lib/mixer.c src/lib/osc.c src/lib/sigpath.c src/lib/voice.c -o $(DSTDIR)/test_voice ${LFLAGS}

test_engine: __tests__/lib/engine.test.c src/lib/engine.c src/lib/sigpath.c src/lib/mixer.c src/lib/osc.c src/lib/list.c src/lib/voice.c
	$(CC) $(CFLAGS) $(IFLAGS)  $< src/lib/list.c src/lib/mixer.c src/lib/osc.c src/lib/sigpath.c src/lib/voice.c src/lib/engine.c -o $(DSTDIR)/test_engine ${LFLAGS}