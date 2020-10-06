CC=clang
CFLAGS=-I.
DEPS = tab.h
OBJ = tab.o test.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

test: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

