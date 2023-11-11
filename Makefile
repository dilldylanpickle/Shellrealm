FLAGS=-g -Wall
SRC_FILES=main.c error.c
OBJ_FILES=$(patsubst %.c,%.o,$(SRC_FILES))
EXE_FILE=shellrealm  # Replace with your desired executable name

all: $(EXE_FILE)

$(EXE_FILE): $(OBJ_FILES)
	gcc $(FLAGS) -o $@ $^

%.o: %.c
	gcc $(FLAGS) -c -o $@ $<

clean:
	rm -f $(EXE_FILE) $(OBJ_FILES)
