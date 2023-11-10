FLAGS=-g -Wall
SRC_FILES=main.c main-debug.c server.c
EXE_FILES=$(patsubst %.c,%,$(SRC_FILES))

all: $(EXE_FILES)

%: %.c
	gcc $< $(FLAGS) -o $@

clean:
	rm -f $(EXE_FILES)
