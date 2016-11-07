# MAKEFILE FOR muscleFactory
#

EXE = muscleFactory


CC = /usr/bin/gcc

CFLAG  = -pthread
CFLAG += -g
CFLAG += -Wall

LDFLAG = -lpthread

SRC = main.c

# targets (all is the default, because its on top.)

all: $(EXE)

run: $(EXE)
	./$(EXE)

$(EXE): $(SRC)
	$(CC) $(CFLAG) $(LDFLAG) -o $@ $<

clean:
	rm -f $(EXE)
