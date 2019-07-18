
CC = gcc

OBJ = opencl.o process.o

HOST = ../host/

DEVICE = ../device/

opencl.o: $(HOST)opencl.c $(DEVICE)image.cl $(HOST)main.h
	$(CC) -c $(HOST)opencl.c -lOpenCL

process.o: $(HOST)process.c $(HOST)main.h
	$(CC) -c $(HOST)process.c -lOpenCL

running: $(HOST)main.c process.o opencl.o $(HOST)main.h
	$(CC) $(OBJ) -o ./processing $(HOST)main.c -lOpenCL

clean:
	rm opencl.o
	rm process.o
	rm processing

all: running
