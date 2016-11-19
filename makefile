# MAKEFILE FOR muscleFactory
#

EXE = muscleFactory


CC = /usr/bin/gcc

FOLDER = -I/media/sf_BS_Praktikum/bsp2/muscleFactory/muscleFactory

CFLAG  = -pthread
CFLAG += -g
CFLAG += -Wall

LDFLAG = -lpthread

SRC = main.c philosoph.o muscleFactory.o global.h philosoph.h

# targets (all is the default, because its on top.)

all: $(EXE)

run: $(EXE)
	./$(EXE)

$(EXE): $(SRC)
	$(CC) $(FOLDER) $(CFLAG) $(LDFLAG) -o $@ $^

philosoph.o: philosoph.c
	$(CC) -c $(FOLDER) $(CFLAG) $(LDFLAG) -o $@ $^

muscleFactory.o: muscleFactory.c
	$(CC) -c $(FOLDER) $(CFLAG) $(LDFLAG) -o $@ $^

clean:
	rm -f $(EXE)
	rm -f philosoph.o
	rm -f muscleFactory.o
