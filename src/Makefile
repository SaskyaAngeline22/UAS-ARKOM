CC = gcc
CFLAGS = -fopenmp -O2

all: sequential parallel benchmark

sequential: sequential.c
	$(CC) $(CFLAGS) sequential.c -o sequential

parallel: parallel.c
	$(CC) $(CFLAGS) parallel.c -o parallel

benchmark: benchmark.c
	$(CC) $(CFLAGS) benchmark.c -o benchmark

clean:
	rm -f sequential parallel benchmark
