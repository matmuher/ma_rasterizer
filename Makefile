EXEC := out.exe
CFLAGS := -Wall -g -std=c++17
CPP := g++
LIBS := -lsfml-graphics -lsfml-window -lsfml-system

INC_DIR := ./include/
SRC_DIR := ./src/

SRC	= $(shell find $(SRC_DIR) -name '*.cpp')

all:
	$(CPP) $(CFLAGS) $(SRC) -o $(EXEC) -I$(INC_DIR) $(LIBS)
