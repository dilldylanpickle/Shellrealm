FLAGS=-g -Wall
LIBS=-lreadline
SRC_FILES=main.c error.c
OBJ_FILES=$(patsubst %.c,%.o,$(SRC_FILES))
EXE_FILE=shellrealm

all: $(EXE_FILE)

$(EXE_FILE): $(OBJ_FILES)
	gcc $(FLAGS) -o $@ $^ $(LIBS)

%.o: %.c
	gcc $(FLAGS) -c -o $@ $<

clean:
	rm -f $(EXE_FILE) $(OBJ_FILES)
