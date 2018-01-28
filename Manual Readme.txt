Instructions to run the benchmarking programs

This assignment is for benchmarking different parts of computers involving CPU, Memory, Disk and networks
which executed separately as C- Programming file.

To compile the source file type the following command in the Termial which is opened in the file saved location

CPU benchmarking:
gcc -pthread -o cpu cpu.c

once the file is compiled run the executable using the following command

./cpu

This will show the results of the follwoing

FLOPS Computations - 1 Thread Statistics
FLOPS Computations - 2 Thread Statistics
FLOPS Computations - 4 Thread Statistics
FLOPS Computations - 8 Thread Statistics
IOPS Computations - 1 Thread Statistics
IOPS Computations - 2 Thread Statistics
IOPS Computations - 4 Thread Statistics
IOPS Computations - 8 Thread Statistics
FLOPS Sampling - 8 Thread Statistics
IOPS Sampling - 8 Thread Statistics

Network Benchmarking:
First compile the server file followed by the client using the following commands
gcc server.c -pthread -o server
gcc client.c -pthread -o client

Second execute the server followed by the client using the following commands
./server <TCP/UDP> 65536 <1/2/4/8>
./client <TCP/UDP> <Server IP> 65536 <1/2/4/8>
The <TCP/UDP> and <1/2/4/8> has to be the same in both the server and client to get the output


Disk benchmarking:
1. gcc diskread.c -o diskread -lpthread

Once the file is compiled execute the file using following command
./diskread

This will give the output for the disk sequential and random read operations.

Sequential read 1,2,4,8 thread and for 8b,8kb,8mb
Random read 1,2,4,8 thread and for 8b,8kb,8mb

2. gcc diskreadwrite.c -o diskreadwrite -lpthread

Once the file is compiled execute the file using following command
./diskreadwrite

This will give the output for the disk  read and write operations.

Sequential read 1,2,4,8 thread and for 8b,8kb,8mb
Sequential write 1,2,4,8 thread and for 8b,8kb,8mb
Random write 1,2,4,8 thread and for 8b,8kb,8mb
Random read 1,2,4,8 thread and for 8b,8kb,8mb

Memory Benchmarking:
1. gcc memory.c -o memory -lpthread

Once the file is compiled execute the file using following command
./memory

This will give the output for memory sequential and random access

Sequential access 1,2,4,8 thread and for 8b,8kb,8mb
Random access 1,2,4,8 thread and for 8b,8kb,8mb





