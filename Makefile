CC		:= gcc
C_FLAGS := -Wall -Wextra -pedantic -g

BIN		:= bin
SRC		:= src
INCLUDE	:= include
LIB		:= lib

LIBRARIES	:= -lSDL -lSDL_image

OS	:= 

ifeq ($(OS),Windows_NT)
EXECUTABLE	:= labyrinth.exe
else
EXECUTABLE	:= labyrinth
endif

all: $(BIN)/$(EXECUTABLE)

clean:
	-$(RM) $(BIN)/$(EXECUTABLE)

run: all
	./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC)/*
	$(CC) $(C_FLAGS) -I$(INCLUDE) -L$(LIB) $^ -o $@ $(LIBRARIES)