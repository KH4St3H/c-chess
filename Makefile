CC=gcc
CFLAGS=-I.
DEPS = utils.h moves.h
OBJ = main.o utils.o moves.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

chess: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f *.o 
	rm chess