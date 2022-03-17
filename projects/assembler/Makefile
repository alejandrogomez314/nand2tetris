CC=gcc
CFLAGS=-Wall -Werror
SOURCES=main.c assembler.c symbolTable.c
EXECUTABLE=hackasm

all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES)
		$(CC) $(CFLAGS) -o $(EXECUTABLE) $(SOURCES)

clean:
		rm -f $(EXECUTABLE)
