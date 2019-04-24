
CC = gcc

OBJ = opencl.o process.o

opencl.o: opencl.c image.cl main.h
	$(CC) -c opencl.c -lOpenCL

process.o: process.c main.h
	$(CC) -c process.c -lOpenCL

running: main.c main.o process.o opencl.o main.h
	$(CC) $(OBJ) -o running main.c -lOpenCL

clean:
	rm opencl.o
	rm process.o
	rm running

all: running
