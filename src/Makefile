CC = gcc 

OBJ = host.o mat_mul_opencl.o

mat_mul_opencl.o: host.h mat_mul_opencl.c
	$(CC) -c mat_mul_opencl.c -lOpenCL

host.o: host.h host.c
	$(CC) -c host.c -lOpenCL

opencl_default: main.c host.o mat_mul_opencl.o host.h
	$(CC) $(OBJ) -o opencl main.c -lOpenCL

clean:
	rm host.o
	rm mat_mul_opencl.o
	rm opencl

all: opencl_default
