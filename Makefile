FLAGS=-g -Wall
INFILE=main

all: 
	gcc $(INFILE).c $(FLAGS) -o $(INFILE)

clean:
	rm $(INFILE)

