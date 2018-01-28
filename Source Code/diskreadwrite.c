

#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<pthread.h>
#include<string.h>
#include<fcntl.h>



// structure definition 
struct thread_struct
{
	int ThreadNum;
	int duration;
	int interval;
	long size_of_block;
	int block_index;
};







struct Struct_Disk
{
	int ThreadNum;
	char chrOperation;
	struct timeval clkstart1;
	struct timeval clkend1;
	struct timeval clkStart2;
	struct timeval clkend2;
	long size_of_block;
	long lngNoOfBlocks;
	unsigned long lngTotalMemSize;
	double dblThroughput;
	double dblLatency;
};




struct thread_struct strctTAS[9];


struct Struct_Disk StrctSeq[6][12];
struct Struct_Disk StrctRand[6][12];
int counter = 0;





char* initializeptr(int length)
{
	
	const char* const strInitialize = "a1b2c3d4e5f6g7h8i9j0k11l12m13n14o15p16q17r18s19t20u21v22w23x24y25z26";

	
	long size = 1024 * 1024 * 100 * sizeof (char);
	char *stringreturn;
	int i=0;
	int intRand=0;

	// reset seed
	srand((unsigned)time(NULL));

	// allocating 100 MB 
	stringreturn = malloc (size);

	while (i < length)
	{
		// generating random number
		intRand = (int) ((rand() * 1000) + 1);
		intRand = intRand % strlen (strInitialize);
		if ((intRand < strlen (strInitialize)) && (intRand >= 0))
		{
			// initializing string with random characters from array
			*(stringreturn + i) = strInitialize[intRand];
			i++;
		}
	}
	return stringreturn;
}




// function to compute Throughput & Latency 
void *computeDisk(void *tss)
{
	// variable declaration
	struct thread_struct *ts = tss;
	char *sourceptr, *original, *strRead;
	char *strTemp;
	long size_of_block = ts->size_of_block;
	int i = 0, j = 0;
	long lngNoOfBlocks;
	if (size_of_block < 1024 * 1024)
	{
		lngNoOfBlocks = 1024 * 30 / size_of_block;
	}
	else
	{
		lngNoOfBlocks = 1024 * 1024 * 50 / size_of_block;
	}
	struct timeval clkStart, clkEnd;
	long lngRandom;
	int fdWrite, fdRead, intWriteOutput, intReadOutput, intSeek;

	
	sourceptr = initializeptr(size_of_block * lngNoOfBlocks);
	strRead = initializeptr(size_of_block * lngNoOfBlocks);

	// initialize dummy pointers
	original = sourceptr;

	// creating a file
	fdRead = open ("./Testfile.txt", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
	for (i=0;i<lngNoOfBlocks;i++)
	{
		intWriteOutput = write (fdRead, strRead, size_of_block);
		if (intWriteOutput == -1)
		{
			printf ("Error while writing into file during Sequential Access Disk Benchmarking experiment\n");
			exit (0);
		}
		strRead += size_of_block;
	}

	if (close(fdRead)== -1)
	{
		printf ("Error while closing the reading file during Sequential Access Disk Benchmarking experiment\n");
		exit (0);
	}
      //code for sequential access 
	fdWrite = open ("./FileTestSeqWrite.txt", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);

	// start  timer
	gettimeofday(&clkStart, NULL);
	for (i=0;i<lngNoOfBlocks;i++)
	{
		
		intWriteOutput = write (fdWrite, sourceptr, size_of_block);

		
		if (intWriteOutput == -1)
		{
			printf ("Error while writing into file during Sequential Access Disk Benchmarking experiment\n");
			exit (0);
		}

		
		sourceptr += size_of_block;
		fsync (fdWrite);
	}

	// end timer
	gettimeofday(&clkEnd, NULL);

	// reset Source and Destination ptrs
	sourceptr = original;

	// initialize the structure variable
	StrctSeq[ts->block_index][ts->ThreadNum-1].chrOperation='W';
	StrctSeq[ts->block_index][ts->ThreadNum-1].ThreadNum = ts->ThreadNum;
	StrctSeq[ts->block_index][ts->ThreadNum-1].clkstart1 = clkStart;
	StrctSeq[ts->block_index][ts->ThreadNum-1].clkend1 = clkEnd;
	StrctSeq[ts->block_index][ts->ThreadNum-1].lngTotalMemSize = size_of_block * lngNoOfBlocks;
	StrctSeq[ts->block_index][ts->ThreadNum-1].dblThroughput = (((double)size_of_block * (double)lngNoOfBlocks)) /
			((((double)clkEnd.tv_sec - (double)clkStart.tv_sec) + (((double)clkEnd.tv_usec - (double)clkStart.tv_usec) / 1000000)) * 1024 * 1024);
	StrctSeq[ts->block_index][ts->ThreadNum-1].size_of_block = size_of_block;
	StrctSeq[ts->block_index][ts->ThreadNum-1].lngNoOfBlocks = lngNoOfBlocks;
	StrctSeq[ts->block_index][ts->ThreadNum-1].clkStart2 = clkStart;
	StrctSeq[ts->block_index][ts->ThreadNum-1].clkend2 = clkEnd;
	StrctSeq[ts->block_index][ts->ThreadNum-1].dblLatency =
			((((double)clkEnd.tv_sec - (double)clkStart.tv_sec) + (((double)clkEnd.tv_usec - (double)clkStart.tv_usec) / 1000000)) * 1000)
			/ (((double)lngNoOfBlocks));
	if (close(fdWrite)== -1)
	{
		printf ("Error while closing the file after sequential write operation during Disk Benchmarking experiment\n");
		exit (0);
	}
	
	

	//code for sequential access disk performance read operation starts from here
	fdRead = open ("./Testfile.txt", O_RDONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);

	// start 
	gettimeofday(&clkStart, NULL);
	for (i=0;i<lngNoOfBlocks;i++)
	{
		
		strTemp = malloc (size_of_block * sizeof(char));

		
		intReadOutput = read (fdRead, strTemp, size_of_block);

		// check the status of write operation and exit in case of error
		if (intReadOutput == -1)
		{
			printf ("Error while reading from file during Sequential Access Disk Benchmarking experiment\n");
			exit (0);
		}

		//free the buffer memory
		free (strTemp);
		fsync (fdRead);
	}

	//  end timer
	gettimeofday(&clkEnd, NULL);

	// reset Source and Destination ptr
	sourceptr = original;

	// initialize the structure variables with appropriate values
	StrctSeq[ts->block_index + 1][ts->ThreadNum-1].chrOperation='R';
	StrctSeq[ts->block_index + 1][ts->ThreadNum-1].ThreadNum = ts->ThreadNum;
	StrctSeq[ts->block_index + 1][ts->ThreadNum-1].clkstart1 = clkStart;
	StrctSeq[ts->block_index + 1][ts->ThreadNum-1].clkend1 = clkEnd;
	StrctSeq[ts->block_index + 1][ts->ThreadNum-1].lngTotalMemSize = size_of_block * lngNoOfBlocks;
	StrctSeq[ts->block_index + 1][ts->ThreadNum-1].dblThroughput = (((double)size_of_block * (double)lngNoOfBlocks)) /
			((((double)clkEnd.tv_sec - (double)clkStart.tv_sec) + (((double)clkEnd.tv_usec - (double)clkStart.tv_usec) / 1000000)) * 1024 * 1024);
	StrctSeq[ts->block_index + 1][ts->ThreadNum-1].size_of_block = size_of_block;
	StrctSeq[ts->block_index + 1][ts->ThreadNum-1].lngNoOfBlocks = lngNoOfBlocks;
	StrctSeq[ts->block_index + 1][ts->ThreadNum-1].clkStart2 = clkStart;
	StrctSeq[ts->block_index + 1][ts->ThreadNum-1].clkend2 = clkEnd;
	StrctSeq[ts->block_index + 1][ts->ThreadNum-1].dblLatency =
			((((double)clkEnd.tv_sec - (double)clkStart.tv_sec) + (((double)clkEnd.tv_usec - (double)clkStart.tv_usec) / 1000000)) * 1000)
			/ (((double)size_of_block * (double)lngNoOfBlocks));
	if (close(fdRead)== -1)
	{
		printf ("Error while closing the file after sequential read operation during Disk Benchmarking experiment\n");
		exit (0);
	}
	
	fdWrite = open ("./FileTestRandWrite.txt", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);

	
	gettimeofday(&clkStart, NULL);
	for (i=0;i<lngNoOfBlocks;i++)
	{
		// generate a random number betwwen 0 and No. of Blocs
		lngRandom = random() % lngNoOfBlocks;

		// position the File Pointer to random blocks away
		if ((intSeek = lseek(fdWrite, lngRandom, SEEK_SET)) == -1)
		{
			printf ("Error while seeking in file during random write operation during Disk Benchmarking experiment\n");
			exit (0);
		}

		// write the Block Size characters from Source character pointer into disk file
		intWriteOutput = write (fdWrite, sourceptr, strlen(sourceptr));

		// check the status of write operation and exit in case of error
		if (intWriteOutput == -1)
		{
			printf ("Error while writing into file during Random Access Disk Benchmarking experiment\n");
			exit (0);
		}

		// increment the Source pointer by Block Size
		sourceptr += size_of_block;
		fsync (fdWrite);
	}

	//  end timer
	gettimeofday(&clkEnd, NULL);

	// reset Source and Destination ptr
	sourceptr = original;

	// initialize the structure variables with appropriate values
	StrctRand[ts->block_index][ts->ThreadNum-1].chrOperation='W';
	StrctRand[ts->block_index][ts->ThreadNum-1].ThreadNum = ts->ThreadNum;
	StrctRand[ts->block_index][ts->ThreadNum-1].clkstart1 = clkStart;
	StrctRand[ts->block_index][ts->ThreadNum-1].clkend1 = clkEnd;
	StrctRand[ts->block_index][ts->ThreadNum-1].lngTotalMemSize = size_of_block * lngNoOfBlocks;
	StrctRand[ts->block_index][ts->ThreadNum-1].dblThroughput = (((double)size_of_block * (double)lngNoOfBlocks)) /
			((((double)clkEnd.tv_sec - (double)clkStart.tv_sec) + (((double)clkEnd.tv_usec - (double)clkStart.tv_usec) / 1000000)) * 1024 * 1024);
	StrctRand[ts->block_index][ts->ThreadNum-1].size_of_block = size_of_block;
	StrctRand[ts->block_index][ts->ThreadNum-1].lngNoOfBlocks = lngNoOfBlocks;
	StrctRand[ts->block_index][ts->ThreadNum-1].clkStart2 = clkStart;
	StrctRand[ts->block_index][ts->ThreadNum-1].clkend2 = clkEnd;
	StrctRand[ts->block_index][ts->ThreadNum-1].dblLatency =
			((((double)clkEnd.tv_sec - (double)clkStart.tv_sec) + (((double)clkEnd.tv_usec - (double)clkStart.tv_usec) / 1000000)) * 1000)
			/ (((double)size_of_block * (double)lngNoOfBlocks));
	if (close(fdWrite)== -1)
	{
		printf ("Error while closing the file after random write operation during Disk Benchmarking experiment\n");
		exit (0);
	}
	
	

	
	fdRead = open ("./Testfile.txt", O_RDONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);

	
	gettimeofday(&clkStart, NULL);
	for (i=0;i<lngNoOfBlocks;i++)
	{
	
		strTemp = malloc (size_of_block * sizeof(char));

		
		lngRandom = random() % lngNoOfBlocks;

		if (lseek(fdRead, lngRandom, SEEK_SET) == -1)
		{
			printf ("Error while seeking in file during random read operation during Disk Benchmarking experiment\n");
			exit (0);
		}

		

		
		if (intReadOutput == -1)
		{
			printf ("Error while reading from file during Random Access Disk Benchmarking experiment\n");
			exit (0);
		}

		// free the buffer memory
		free (strTemp);
		fsync (fdRead);
	}

	//  end timer
	gettimeofday(&clkEnd, NULL);

	// reset Source and Destination ptr
	sourceptr = original;

	// initialize the structure variables with appropriate values
	StrctRand[ts->block_index + 1][ts->ThreadNum-1].chrOperation='R';
	StrctRand[ts->block_index + 1][ts->ThreadNum-1].ThreadNum = ts->ThreadNum;
	StrctRand[ts->block_index + 1][ts->ThreadNum-1].clkstart1 = clkStart;
	StrctRand[ts->block_index + 1][ts->ThreadNum-1].clkend1 = clkEnd;
	StrctRand[ts->block_index + 1][ts->ThreadNum-1].lngTotalMemSize = size_of_block * lngNoOfBlocks;
	StrctRand[ts->block_index + 1][ts->ThreadNum-1].dblThroughput = (((double)size_of_block * (double)lngNoOfBlocks)) /
			((((double)clkEnd.tv_sec - (double)clkStart.tv_sec) + (((double)clkEnd.tv_usec - (double)clkStart.tv_usec) / 1000000)) * 1024 * 1024);
	StrctRand[ts->block_index + 1][ts->ThreadNum-1].size_of_block = size_of_block;
	StrctRand[ts->block_index + 1][ts->ThreadNum-1].lngNoOfBlocks = lngNoOfBlocks;
	StrctRand[ts->block_index + 1][ts->ThreadNum-1].clkStart2 = clkStart;
	StrctRand[ts->block_index + 1][ts->ThreadNum-1].clkend2 = clkEnd;
	StrctRand[ts->block_index + 1][ts->ThreadNum-1].dblLatency =
			((((double)clkEnd.tv_sec - (double)clkStart.tv_sec)+(((double)clkEnd.tv_usec - (double)clkStart.tv_usec) / 1000000)) * 1000)
			/ (((double)size_of_block * (double)lngNoOfBlocks));
	if (close(fdRead)== -1)
	{
		printf ("Error while closing the file after random read operation during Disk Benchmarking experiment\n");
		exit (0);
	}
	

	free (sourceptr);
	return NULL;
}


// function to govern Run Time
void *runTimer (void *tss)
{
	struct thread_struct *ts = tss;

	counter = 0;
	while (counter < ts->duration)
	{
		sleep(ts->interval);
		counter = counter + 1;
	}
	return NULL;
}




void DiskBenchmarking()
{
	pthread_t arrPTh[2];
	int i = 0;
	int intNoOfThreads=0;

	//Create thread
	intNoOfThreads = 1;

	// loop to create threads
	for (i=0;i<intNoOfThreads;i++)
	{
		// initialize the tsuments to be passed to threading function in structure
		strctTAS[i].ThreadNum = i+1;
		strctTAS[i].size_of_block = 8;
		strctTAS[i].block_index = 0;

		// create the thread, call the respective function with appropriate tsuments  and check creation status
		if (pthread_create(&arrPTh[i], NULL, computeDisk, (void *)&(strctTAS[i]))!=0)
		{
			printf ("Unable to create thread %d", i+1);
			exit(0);
		}
	}

	
	for (i=0;i<intNoOfThreads;i++)
	{
		pthread_join(arrPTh[i], NULL);
	}

	
	for (i=0;i<intNoOfThreads;i++)
	{
		// initialize the tsuments to be passed to threading function in structure
		strctTAS[i].ThreadNum = i+1;
		strctTAS[i].size_of_block = 8000;
		strctTAS[i].block_index = 2;

		// create the thread, call the respective function with appropriate tsuments  and check creation status
		if (pthread_create(&arrPTh[i], NULL, computeDisk, (void *)&(strctTAS[i]))!=0)
		{
			printf ("Unable to create thread %d", i+1);
			exit(0);
		}
	}

	
	for (i=0;i<intNoOfThreads;i++)
	{
		pthread_join(arrPTh[i], NULL);
	}

	
	for (i=0;i<intNoOfThreads;i++)
	{
		
		strctTAS[i].ThreadNum = i+1;
		strctTAS[i].size_of_block = 8e+6;
		strctTAS[i].block_index = 4;

		
		if (pthread_create(&arrPTh[i], NULL, computeDisk, (void *)&(strctTAS[i]))!=0)
		{
			printf ("Unable to create thread %d", i+1);
			exit(0);
		}
	}


	for (i=0;i<intNoOfThreads;i++)
	{
		pthread_join(arrPTh[i], NULL);
	}
	
	
	


	printf ("\n\n\nDisk - Sequential Access Statistics\nDescription\tThread 1 Values\n");
	for (i=0;i<6;i++)
	{
		if (StrctSeq[i][0].chrOperation=='R')
		{
			printf ("Operation: \tRead\n");
		}
		else
		{
			printf ("Operation: \tWrite\n");
		}
		
		
		printf ("Block Size: \t%ld Bytes\n", StrctSeq[i][0].size_of_block);
		printf ("No. of Blocks: \t%ld\n", StrctSeq[i][0].lngNoOfBlocks);
		printf ("Total Memory Size: \t%ld Bytes\n", StrctSeq[i][0].lngTotalMemSize);
		printf ("Throughput: \t%7.4f MBPS\n", StrctSeq[i][0].dblThroughput);
		printf ("Latency: \t%02.15f milliSec\n\n\n", StrctSeq[i][0].dblLatency);
		
	}

	printf ("\n\n\nDisk - Random Access Statistics\nDescription\tThread 1 Values\n");
	for (i=0;i<6;i++)
	{
		if (StrctRand[i][0].chrOperation=='R')
		{
			printf ("Operation: \tRead\n");
		}
		else
		{
			printf ("Operation: \tWrite\n");
		}
		
		printf ("Block Size: \t%ld Bytes\n", StrctRand[i][0].size_of_block);
		printf ("No. of Blocks: \t%ld\n", StrctRand[i][0].lngNoOfBlocks);
		printf ("Total Memory Size: \t%ld Bytes\n", StrctRand[i][0].lngTotalMemSize);
		printf ("Throughput: \t%7.4f MBPS\n", StrctRand[i][0].dblThroughput);
		printf ("Latency: \t%02.15f milliSec\n\n\n", StrctRand[i][0].dblLatency);
		
	}


	intNoOfThreads = 2;


	for (i=0;i<intNoOfThreads;i++)
	{
		// initialize the tsuments to be passed to threading function in structure
		strctTAS[i].ThreadNum = i+1;
		strctTAS[i].size_of_block = 8;
		strctTAS[i].block_index = 0;

		// create the thread, call the respective function with appropriate tsuments  and check creation status
		if (pthread_create(&arrPTh[i], NULL, computeDisk, (void *)&(strctTAS[i]))!=0)
		{
			printf ("Unable to create thread %d", i+1);
			exit(0);
		}
	}

	
	for (i=0;i<intNoOfThreads;i++)
	{
		pthread_join(arrPTh[i], NULL);
	}

	
	for (i=0;i<intNoOfThreads;i++)
	{
		// initialize the tsuments to be passed to threading function in structure
		strctTAS[i].ThreadNum = i+1;
		strctTAS[i].size_of_block = 8000;
		strctTAS[i].block_index = 2;

		// create the thread, call the respective function with appropriate tsuments  and check creation status
		if (pthread_create(&arrPTh[i], NULL, computeDisk, (void *)&(strctTAS[i]))!=0)
		{
			printf ("Unable to create thread %d", i+1);
			exit(0);
		}
	}

	
	for (i=0;i<intNoOfThreads;i++)
	{
		pthread_join(arrPTh[i], NULL);
	}

	
	for (i=0;i<intNoOfThreads;i++)
	{
		// initialize the tsuments to be passed to threading function in structure
		strctTAS[i].ThreadNum = i+1;
		strctTAS[i].size_of_block = 8e+6;
		strctTAS[i].block_index = 4;

		// create the thread, call the respective function with appropriate tsuments  and check creation status
		if (pthread_create(&arrPTh[i], NULL, computeDisk, (void *)&(strctTAS[i]))!=0)
		{
			printf ("Unable to create thread %d", i+1);
			exit(0);
		}
	}

	
	for (i=0;i<intNoOfThreads;i++)
	{
		pthread_join(arrPTh[i], NULL);
	}

	// print the results for the experiments 
	printf ("\n\n\nDisk - Sequential Access Statistics\nDescription\tThread 1 Values\tThread 2 Values\tFinal Values\n");
	for (i=0;i<6;i++)
	{
		if (StrctSeq[i][0].chrOperation=='R')
		{
			printf ("Operation: \tRead\tRead\tRead\n");
		}
		else
		{
			printf ("Operation: \tWrite\n");
		}
		   
		printf ("Block Size: \t%ld Bytes\t%ld Bytes\t%ld Bytes\n", StrctSeq[i][0].size_of_block,
				 StrctSeq[i][1].size_of_block, StrctSeq[i][1].size_of_block);
		printf ("No. of Blocks: \t%ld\t%ld\t%ld\n", StrctSeq[i][0].lngNoOfBlocks,
				StrctSeq[i][1].lngNoOfBlocks, (StrctSeq[i][0].lngNoOfBlocks + StrctSeq[i][1].lngNoOfBlocks));
		printf ("Total Memory Size: \t%ld Bytes\t%ld Bytes\t%ld Bytes\n", StrctSeq[i][0].lngTotalMemSize,
				StrctSeq[i][1].lngTotalMemSize, (StrctSeq[i][0].lngTotalMemSize + StrctSeq[i][1].lngTotalMemSize));
		printf ("Throughput: \t%7.4f MBPS\t%7.4f MBPS\t%7.4f MBPS\n", StrctSeq[i][0].dblThroughput,
				StrctSeq[i][1].dblThroughput, (StrctSeq[i][0].dblThroughput + StrctSeq[i][1].dblThroughput));
		printf ("Latency: \t%02.15f milliSec\t%02.15f milliSec\t%02.15f milliSec\n\n", StrctSeq[i][0].dblLatency,
				StrctSeq[i][1].dblLatency, (StrctSeq[i][0].dblLatency + StrctSeq[i][1].dblLatency) / 2);
				
	}

	printf ("\n\n\nDisk - Random Access Statistics\nDescription\tThread 1 Values\tThread 2 Values\tFinal Values\n");
	for (i=0;i<6;i++)
	{
		if (StrctRand[i][0].chrOperation=='R')
		{
			printf ("Operation: \tRead\tRead\tRead\n");
		}
		else
		{
			printf ("Operation: \tWrite\n");
		}
		
		
		printf ("Block Size: \t%ld Bytes\t%ld Bytes\t%ld Bytes\n", StrctRand[i][0].size_of_block,
				 StrctRand[i][1].size_of_block, StrctRand[i][1].size_of_block);
		printf ("No. of Blocks: \t%ld\t%ld\t%ld\n", StrctRand[i][0].lngNoOfBlocks,
				StrctRand[i][1].lngNoOfBlocks, (StrctRand[i][0].lngNoOfBlocks + StrctRand[i][1].lngNoOfBlocks));
		printf ("Total Memory Size: \t%ld Bytes\t%ld Bytes\t%ld Bytes\n", StrctRand[i][0].lngTotalMemSize,
				StrctRand[i][1].lngTotalMemSize, (StrctRand[i][0].lngTotalMemSize + StrctRand[i][1].lngTotalMemSize));
		printf ("Throughput: \t%7.4f MBPS\t%7.4f MBPS\t%7.4f MBPS\n", StrctRand[i][0].dblThroughput,
				StrctRand[i][1].dblThroughput, (StrctRand[i][0].dblThroughput + StrctRand[i][1].dblThroughput));
		printf ("Latency: \t%02.15f milliSec\t%02.15f milliSec\t%02.15f milliSec\n\n", StrctRand[i][0].dblLatency,
				StrctRand[i][1].dblLatency, (StrctRand[i][0].dblLatency + StrctRand[i][1].dblLatency) / 2);
				
	}
	
	
	
	
	
	
	
	
	
}

void bench()
{

   pthread_t arrPTh[9];
  int intNoOfThreads;
  int i;
  
// 4 threads
	//Create  thread
	intNoOfThreads = 4;

	
	for (i=0;i<intNoOfThreads;i++)
	{
		
		strctTAS[i].ThreadNum = i+1;
		strctTAS[i].size_of_block = 8;
		strctTAS[i].block_index = 0;

		
		if (pthread_create(&arrPTh[i], NULL, computeDisk, (void *)&(strctTAS[i]))!=0)
		{
			printf ("Unable to create thread %d", i+1);
			exit(0);
		}
	}

	
	for (i=0;i<intNoOfThreads;i++)
	{
		pthread_join(arrPTh[i], NULL);
	}

	
	for (i=0;i<intNoOfThreads;i++)
	{
		
		strctTAS[i].ThreadNum = i+1;
		strctTAS[i].size_of_block = 8000;
		strctTAS[i].block_index = 2;

		
		if (pthread_create(&arrPTh[i], NULL, computeDisk, (void *)&(strctTAS[i]))!=0)
		{
			printf ("Unable to create thread %d", i+1);
			exit(0);
		}
	}

	
	for (i=0;i<intNoOfThreads;i++)
	{
		pthread_join(arrPTh[i], NULL);
	}

	
	for (i=0;i<intNoOfThreads;i++)
	{
		
		strctTAS[i].ThreadNum = i+1;
		strctTAS[i].size_of_block = 8e+6;
		strctTAS[i].block_index = 4;

		
		if (pthread_create(&arrPTh[i], NULL, computeDisk, (void *)&(strctTAS[i]))!=0)
		{
			printf ("Unable to create thread %d", i+1);
			exit(0);
		}
	}

	
	for (i=0;i<intNoOfThreads;i++)
	{
		pthread_join(arrPTh[i], NULL);
	}

	// print the results 
	printf ("\n\n\nDisk - Sequential Access Statistics\nDescription\tThread 1 Values\tThread 2 Values\tFinal Values\n");
	for (i=0;i<6;i++)
	{
		if (StrctSeq[i][0].chrOperation=='R')
		{
			printf ("Operation: \tRead\tRead\tRead\n");
		}
		else
		{
			printf ("Operation: \tWrite\n");
		}
		
		   
		printf ("Block Size: \t%ld Bytes\t%ld Bytes\t%ld Bytes\t%ld Bytes\t%ld Bytes\n", StrctSeq[i][0].size_of_block,
				 StrctSeq[i][1].size_of_block, StrctSeq[i][2].size_of_block,StrctSeq[i][3].size_of_block,StrctSeq[i][3].size_of_block);
		printf ("No. of Blocks: \t%ld\t%ld\t%ld\t%ld\t%ld\n", StrctSeq[i][0].lngNoOfBlocks,
				StrctSeq[i][1].lngNoOfBlocks,StrctSeq[i][2].lngNoOfBlocks,StrctSeq[i][3].lngNoOfBlocks,
				(StrctSeq[i][0].lngNoOfBlocks + StrctSeq[i][1].lngNoOfBlocks+StrctSeq[i][2].lngNoOfBlocks + StrctSeq[i][3].lngNoOfBlocks) );
		printf ("Total Memory Size: \t%ld Bytes\t%ld Bytes\t%ld Bytes\t%ld Bytes\t%ld Bytes\n", StrctSeq[i][0].lngTotalMemSize,
				StrctSeq[i][1].lngTotalMemSize, StrctSeq[i][2].lngTotalMemSize,StrctSeq[i][3].lngTotalMemSize,(StrctSeq[i][0].lngTotalMemSize + StrctSeq[i][1].lngTotalMemSize,
				StrctSeq[i][2].lngTotalMemSize + StrctSeq[i][3].lngTotalMemSize) );
		printf ("Throughput: \t%7.4f MBPS\t%7.4f MBPS\t%7.4f MBPS\t%7.4f MBPS\t%7.4f MBPS\n", StrctSeq[i][0].dblThroughput,
				StrctSeq[i][1].dblThroughput, StrctSeq[i][2].dblThroughput,StrctSeq[i][3].dblThroughput,
				(StrctSeq[i][0].dblThroughput + StrctSeq[i][1].dblThroughput+StrctSeq[i][2].dblThroughput + StrctSeq[i][3].dblThroughput));
		printf ("Latency: \t%02.15f milliSec\t%02.15f milliSec\t%02.15f milliSec\t%02.15f milliSec\t%02.15f milliSec\n\n", StrctSeq[i][0].dblLatency,
				StrctSeq[i][1].dblLatency, StrctSeq[i][2],StrctSeq[i][3],(StrctSeq[i][0].dblLatency + StrctSeq[i][1].dblLatency
				+StrctSeq[i][2].dblLatency + StrctSeq[i][3].dblLatency)/4 );
				
	}

	printf ("\n\n\nDisk - Random Access Statistics\nDescription\tThread 1 Values\tThread 2 Values\tFinal Values\n");
	for (i=0;i<6;i++)
	{
		if (StrctRand[i][0].chrOperation=='R')
		{
			printf ("Operation: \tRead\tRead\tRead\n");
		}
		else
		{
			printf ("Operation: \tWrite\n");
		}
		
		
		printf ("Block Size: \t%ld Bytes\t%ld Bytes\t%ld Bytes\t%ld Bytes\t%ld Bytes\n", StrctRand[i][0].size_of_block,
				 StrctRand[i][1].size_of_block, StrctRand[i][2].size_of_block,StrctRand[i][3].size_of_block,StrctRand[i][3].size_of_block);
		printf ("No. of Blocks: \t%ld\t%ld\t%ld\t%ld\t%ld\n", StrctRand[i][0].lngNoOfBlocks,
				StrctRand[i][1].lngNoOfBlocks, StrctRand[i][2].lngNoOfBlocks,StrctRand[i][3].lngNoOfBlocks,(StrctRand[i][0].lngNoOfBlocks+StrctRand[i][1].lngNoOfBlocks
				+StrctRand[i][2].lngNoOfBlocks+StrctRand[i][3].lngNoOfBlocks));
		printf ("Total Memory Size: \t%ld Bytes\t%ld Bytes\t%ld Bytes\t%ld Bytes\t%ld Bytes\n", StrctRand[i][0].lngTotalMemSize,
				StrctRand[i][1].lngTotalMemSize, StrctRand[i][2].lngTotalMemSize,StrctRand[i][3].lngTotalMemSize,(StrctRand[i][0].lngTotalMemSize+
				StrctRand[i][1].lngTotalMemSize+StrctRand[i][2].lngTotalMemSize+StrctRand[i][3].lngTotalMemSize));
		printf ("Throughput: \t%7.4f MBPS\t%7.4f MBPS\t%7.4f MBPS\t%7.4f MBPS\t%7.4f MBPS\n", StrctRand[i][0].dblThroughput,
				StrctRand[i][1].dblThroughput, StrctRand[i][2].dblThroughput,StrctRand[i][3].dblThroughput,
				(StrctRand[i][0].dblThroughput+StrctRand[i][1].dblThroughput+StrctRand[i][2].dblThroughput+StrctRand[i][3].dblThroughput));
		printf ("Latency: \t%02.15f milliSec\t%02.15f milliSec\t%02.15f milliSec\t%02.15f milliSec\t%02.15f milliSec\n\n", StrctRand[i][0].dblLatency,
				StrctRand[i][1].dblLatency, StrctRand[i][2].dblLatency ,StrctRand[i][3].dblLatency,
				(StrctRand[i][0].dblLatency+StrctRand[i][1].dblLatency+StrctRand[i][2].dblLatency+StrctRand[i][3].dblLatency)/4);
				
	}
	
	
	
	
}






// main function 
void main()
{
	int i=0;
	int intReportInterval=1;
	int intRunTime=600;
	int intInput;
	DiskBenchmarking();
				bench();
	
	
}
// main function to call Benchmarking Experiments ends over here
