CC = g++
CFLAGS = -std=c++17
SOURCES = main.cpp 
LDFLAGS =

build:
	$(CC) $(CFLAGS) $(SOURCES) -O2 -o delivery_service

run:
	./delivery_service

all: build run
