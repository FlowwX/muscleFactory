# MAKEFILE FOR muscleFactory
#

EXE = muscleFactory


CC = /usr/bin/gcc

FOLDER = -I/home/bsp2/muscleFactory 

CFLAG  = -pthread
CFLAG += -g
CFLAG += -Wall

LDFLAG = -lpthread

HEADER = global.h philosoph.h
SRC    = main.c philosoph.c muscleFactory.c
OBJ    = $(SRC:%.c=%.o) 

# targets (all is the default, because its on top.)

all: $(EXE)

run: $(EXE)
	./$(EXE)

$(EXE): $(OBJ) $(HEADER)
	$(CC) $(FOLDER) $(CFLAG) $(LDFLAG) -o $@ $^

%.o: %.c
	$(CC) -c $(FOLDER) $(CFLAG) $(LDFLAG) -o $@ $^

clean:
	rm -f $(EXE)
	rm -f philosoph.o
	rm -f muscleFactory.o
