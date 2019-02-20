CC=g++
CFLAGS=-std=c++11
OUT=team_generator
SOURCE=$(OUT).cpp
FILE=names.txt
SIZE=5

all: $(OUT)

$(OUT): $(SOURCE)
	$(CC) $(CFLAGS) -o $(OUT) $(SOURCE)

clean:
	rm -f $(OUT)

test: $(OUT)
	./$(OUT) $(FILE) $(SIZE)

