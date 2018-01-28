

#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<pthread.h>
#include<string.h>
#include<fcntl.h>


// defining structure
struct struct_thread
{
	int thread_num;
	int run_time;
	int sample_time;
	long Block_size;
	int block_index;
};




struct Struct_memory
{
	int thread_num;
	struct timeval clkStart1;
	struct timeval ClkEnd1;
	struct timeval clkStart2;
	struct timeval clkEnd2;
	long Block_size;
	long Block_num;
	unsigned long total_memory;
	double throughput;
	double latency;
};



//  declaration of structure variable 

struct struct_thread strctTh[9];

struct Struct_memory StrctMem[6][9];
struct Struct_memory StrctRandom[6][9];

int counter = 0;



// initialize pointers
char* poniter_initialize(int l)
{
	
	const char* const strInitialize = "a1b2c3d4e5f6g7h8i9j0k11l12m13n14o15p16q17r18s19t20u21v22w23x24y25z26";

	// set mem size to 100mb
	long size = 1024 * 1024 * 100 * sizeof (char);
	char *returnsrting;
	int i=0;
	int random=0;

	// set seed
	srand((unsigned)time(NULL));

	
	returnsrting = malloc (size);

	while (i < l)
	{
		// generate rand number
		random = (int) ((rand() * 1000) + 1);
		random = random % strlen (strInitialize);
		if ((random < strlen (strInitialize)) && (random >= 0))
		{
			// initializing string with random characters from array
			*(returnsrting + i) = strInitialize[random];
			i++;
		}
	}
	return returnsrting;
}


// function to compute Throughput & Latency for Memory 
void *MemoryPerformanecal(void *sts)
{
	//  declaration of variables
	struct struct_thread *st = sts;
	char *source, *destination, *originalsource, *original_dest;
	long Block_size = st->Block_size;
	int i = 0, j = 0;
	long Block_num = 1024 * 1024 * 100 / Block_size;
	struct timeval clkStart, clkEnd;
	long Randlng, Final_disp;

	// initialize strings with rand chars
	source = poniter_initialize(Block_size);
	destination = poniter_initialize(Block_size);

	// initialize dummy pointers to original strings to reset in future
	originalsource = source;
	original_dest = destination;

	

	// start timer
	gettimeofday(&clkStart, NULL);
	for (i=0;i<Block_num;i++)
	{
		// compying data
		memcpy(destination, source, Block_size);

		
		source += Block_size;
		destination += Block_size;
	}

	//  end timer
	gettimeofday(&clkEnd, NULL);

	// reset pointers to original location
	source = originalsource;
	destination = original_dest;

	// initialize the structure 
	StrctMem[st->block_index][st->thread_num-1].thread_num = st->thread_num;
	StrctMem[st->block_index][st->thread_num-1].clkStart1 = clkStart;
	StrctMem[st->block_index][st->thread_num-1].ClkEnd1 = clkEnd;
	StrctMem[st->block_index][st->thread_num-1].total_memory = Block_size * Block_num;
	StrctMem[st->block_index][st->thread_num-1].throughput = (((double)Block_size * (double)Block_num)) /
			((((double)clkEnd.tv_sec - (double)clkStart.tv_sec) + (((double)clkEnd.tv_usec - (double)clkStart.tv_usec) / 1000000)) * 1024 * 1024);
	StrctMem[st->block_index][st->thread_num-1].Block_size = Block_size;
	StrctMem[st->block_index][st->thread_num-1].Block_num = Block_num;

	// start timer
	gettimeofday(&clkStart, NULL);
	for (i=0;i<Block_num;i++)
	{
		
		memset(destination, (char)((j % 26) + 65), Block_size);

		// increment the Destination ptr by  Size of block
		destination += Block_size;
	}

	// set timer
	gettimeofday(&clkEnd, NULL);

	// reset  pointers to their original position
	source = originalsource;
	destination = original_dest;

	
	StrctMem[st->block_index][st->thread_num-1].clkStart2 = clkStart;
	StrctMem[st->block_index][st->thread_num-1].clkEnd2 = clkEnd;
	StrctMem[st->block_index][st->thread_num-1].latency =
			((((double)clkEnd.tv_sec - (double)clkStart.tv_sec) + (((double)clkEnd.tv_usec - (double)clkStart.tv_usec) / 1000000)) * 1000)
			/ (((double)Block_size * (double)Block_num));
	

	//code for random access 

	// initialize strings 
	source = poniter_initialize(Block_size);
	destination = poniter_initialize(Block_size);

	// start  timer
	gettimeofday(&clkStart, NULL);
	for (i=0;i<Block_num;)
	{
		// generate random number between 0 and No. of Blocks
		Randlng = random() % (Block_num / 2);
		if ((Randlng >= 0) && (Randlng < Block_num / 2))
		{
			// move Source and Destination character pointers to Random Blocks away from initial / starting position
			if (i % 2 == 0)
			{
				source += (Block_size * Randlng);
				destination += (Block_size * Randlng);
			}
			else
			{
				long lngSrcLength = strlen (source);
				long lngDestLength = strlen (destination);
				source = source + (strlen (source) - (((lngSrcLength / Block_size) - Randlng) * Block_size));
				destination = destination + (strlen(destination) - (((lngDestLength / Block_size) - Randlng) * Block_size));
			}

			// copy the Blocks from Source to Destination within Memory itself
			memcpy(destination, source, Block_size);

			// reset Source and Destination character pointers to their original position
			source = originalsource;
			destination = original_dest;

			// increment the loop variable only if the random number generated is between 0 and No. of Blocks
			i++;
		}
	}

	//  end timer
	gettimeofday(&clkEnd, NULL);

	// reset  pointers to their original position
	source = originalsource;
	destination = original_dest;

	// initialize variables with appropriate values
	StrctRandom[st->block_index][st->thread_num-1].thread_num = st->thread_num;
	StrctRandom[st->block_index][st->thread_num-1].clkStart1 = clkStart;
	StrctRandom[st->block_index][st->thread_num-1].ClkEnd1 = clkEnd;
	StrctRandom[st->block_index][st->thread_num-1].total_memory = Block_size * Block_num;
	StrctRandom[st->block_index][st->thread_num-1].throughput = (((double)Block_size * (double)Block_num)) /
			((((double)clkEnd.tv_sec - (double)clkStart.tv_sec) + (((double)clkEnd.tv_usec - (double)clkStart.tv_usec) / 1000000)) * 1024 * 1024);
	StrctRandom[st->block_index][st->thread_num-1].Block_size = Block_size;
	StrctRandom[st->block_index][st->thread_num-1].Block_num = Block_num;

	// start  timer
	gettimeofday(&clkStart, NULL);
	for (i=0;i<Block_num;)
	{
		// generate random number between 0 and No. of Blocks
		Randlng = random() % Block_num;
		if ((Randlng >= 0) && (Randlng < Block_num))
		{
			
			destination += (Block_size * Randlng);

			
			memset(destination, (char)((j % 26) + 65), Block_size);

			
			source = originalsource;
			destination = original_dest;

			// increment the loop variable only if the random number generated is between 0 and No. of Blocks
			i++;
		}
	}

	// set  end timer
	gettimeofday(&clkEnd, NULL);

	// reset  pointers to their original position
	source = originalsource;
	destination = original_dest;

	// initialize the structure variables 
	StrctRandom[st->block_index][st->thread_num-1].clkStart2 = clkStart;
	StrctRandom[st->block_index][st->thread_num-1].clkEnd2 = clkEnd;
	StrctRandom[st->block_index][st->thread_num-1].latency =
			((((double)clkEnd.tv_sec - (double)clkStart.tv_sec) + (((double)clkEnd.tv_usec - (double)clkStart.tv_usec) / 1000000)) * 1000)
			/ (((double)Block_size * (double)Block_num));
	

	free (source);
	free (destination);
	return NULL;
}




// function to calculate run time
void *runTimer (void *sts)
{
	struct struct_thread *st = sts;

	counter = 0;
	while (counter < st->run_time)
	{
		sleep(st->sample_time);
		counter = counter + 1;
	}
	return NULL;
}




// function to call Memory Benchmarking 
void MemoryBench()
{
	pthread_t arrPTh[9];
	int i = 0;
	int intNoOfThreads=0;

	//Create worker thread
	intNoOfThreads = 1;

	// loop to create threads
	for (i=0;i<intNoOfThreads;i++)
	{
	
		strctTh[i].thread_num = i+1;
		strctTh[i].Block_size = 8;
		strctTh[i].block_index = 0;

		// create the threads
		if (pthread_create(&arrPTh[i], NULL, MemoryPerformanecal, (void *)&(strctTh[i]))!=0)
		{
			printf ("Unable to create thread %d", i+1);
			exit(0);
		}
	}

	
	for (i=0;i<intNoOfThreads;i++)
	{
		pthread_join(arrPTh[i], NULL);
	}

	//  create threads
	for (i=0;i<intNoOfThreads;i++)
	{
		// initialize the stuments to be passed to threading function in structure
		strctTh[i].thread_num = i+1;
		strctTh[i].Block_size = 8000;
		strctTh[i].block_index = 1;

		// create the thread, call the respective function with appropriate stuments  and check creation status
		if (pthread_create(&arrPTh[i], NULL, MemoryPerformanecal, (void *)&(strctTh[i]))!=0)
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
		// initialize the stuments to be passed to threading function in structure
		strctTh[i].thread_num = i+1;
		strctTh[i].Block_size = 8e+6;
		strctTh[i].block_index = 2;

		// create the thread, call the respective function with appropriate stuments  and check creation status
		if (pthread_create(&arrPTh[i], NULL, MemoryPerformanecal, (void *)&(strctTh[i]))!=0)
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
	printf ("\n\n\nSequential Memory Access Statistics\nDescription\tThread 1 Values\n");
	for (i=0;i<3;i++)
	{
		printf ("Block Size: \t%ld Bytes\n", StrctMem[i][0].Block_size);
		printf ("No. of Blocks: \t%ld\n", StrctMem[i][0].Block_num);
		printf ("Total Memory Size: \t%ld Bytes\n", StrctMem[i][0].total_memory);
		printf ("Throughput: \t%7.4f MBPS\n", StrctMem[i][0].throughput);
		printf ("Latency: \t%02.15f milliSec\n\n", StrctMem[i][0].latency);
	}

	printf ("\n\n\nRandom Memory Access Statistics\nDescription\tThread 1 Values\n");
	for (i=0;i<3;i++)
	{
		printf ("Block Size: \t%ld Bytes\n", StrctRandom[i][0].Block_size);
		printf ("No. of Blocks: \t%ld\n", StrctRandom[i][0].Block_num);
		printf ("Total Memory Size: \t%ld Bytes\n", StrctRandom[i][0].total_memory);
		printf ("Throughput: \t%7.4f MBPS\n", StrctRandom[i][0].throughput);
		printf ("Latency: \t%02.15f milliSec\n\n", StrctRandom[i][0].latency);
	}

	// two threads
	intNoOfThreads = 2;

	// create threads
	for (i=0;i<intNoOfThreads;i++)
	{
		// initialize the stuments to be passed to threading function in structure
		strctTh[i].thread_num = i+1;
		strctTh[i].Block_size = 8;
		strctTh[i].block_index = 0;

		// create the thread, call the respective function with appropriate stuments  and check creation status
		if (pthread_create(&arrPTh[i], NULL, MemoryPerformanecal, (void *)&(strctTh[i]))!=0)
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
		// initialize the stuments to be passed to threading function in structure
		strctTh[i].thread_num = i+1;
		strctTh[i].Block_size = 8000;
		strctTh[i].block_index = 1;

		// create the thread, call the respective function with appropriate stuments  and check creation status
		if (pthread_create(&arrPTh[i], NULL, MemoryPerformanecal, (void *)&(strctTh[i]))!=0)
		{
			printf ("Unable to create thread %d", i+1);
			exit(0);
		}
	}

	for (i=0;i<intNoOfThreads;i++)
	{
		pthread_join(arrPTh[i], NULL);
	}

	// loop to create threads
	for (i=0;i<intNoOfThreads;i++)
	{
		// initialize the stuments to be passed to threading function in structure
		strctTh[i].thread_num = i+1;
		strctTh[i].Block_size = 8e+6;
		strctTh[i].block_index = 2;

		// create the thread, call the respective function with appropriate stuments  and check creation status
		if (pthread_create(&arrPTh[i], NULL, MemoryPerformanecal, (void *)&(strctTh[i]))!=0)
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
	printf ("\n\n\nMemory - Sequential Access Statistics\nDescription\tThread 1 Values\tThread 2 Values\tFinal Values\n");
	for (i=0;i<3;i++)
	{
		printf ("Block Size: \t%ld Bytes\t%ld Bytes\t%ld Bytes\n", StrctMem[i][0].Block_size,
				StrctMem[i][1].Block_size, StrctMem[i][1].Block_size);
		printf ("No. of Blocks: \t%ld\t%ld\t%ld\n", StrctMem[i][0].Block_num,
				StrctMem[i][1].Block_num, (StrctMem[i][0].Block_num + StrctMem[i][1].Block_num));
		printf ("Total Memory Size: \t%ld Bytes\t%ld Bytes\t%ld Bytes\n", StrctMem[i][0].total_memory,
				StrctMem[i][1].total_memory, (StrctMem[i][0].total_memory + StrctMem[i][1].total_memory));
		printf ("Throughput: \t%7.4f MBPS\t%7.4f MBPS\t%7.4f MBPS\n", StrctMem[i][0].throughput,
				StrctMem[i][1].throughput, (StrctMem[i][0].throughput + StrctMem[i][1].throughput));
		printf ("Latency: \t%02.15f milliSec\t%02.15f milliSec\t%02.15f milliSec\n\n", StrctMem[i][0].latency,
				StrctMem[i][1].latency, (StrctMem[i][0].latency + StrctMem[i][1].latency)/2);
	}

	printf ("\n\n\nMemory - Random Access Statistics\nDescription\tThread 1 Values\tThread 2 Values\tFinal Values\n");
	for (i=0;i<3;i++)
	{
		printf ("Block Size: \t%ld Bytes\t%ld Bytes\t%ld Bytes\n", StrctRandom[i][0].Block_size,
				StrctRandom[i][1].Block_size, StrctRandom[i][1].Block_size);
		printf ("No. of Blocks: \t%ld\t%ld\t%ld\n", StrctRandom[i][0].Block_num,
				StrctRandom[i][1].Block_num, (StrctRandom[i][0].Block_num + StrctRandom[i][1].Block_num));
		printf ("Total Memory Size: \t%ld Bytes\t%ld Bytes\t%ld Bytes\n", StrctRandom[i][0].total_memory,
				StrctRandom[i][1].total_memory, (StrctRandom[i][0].total_memory + StrctRandom[i][1].total_memory));
		printf ("Throughput: \t%7.4f MBPS\t%7.4f MBPS\n\t%7.4f MBPS\n", StrctRandom[i][0].throughput,
				StrctRandom[i][1].throughput, (StrctRandom[i][0].throughput + StrctRandom[i][1].throughput));
		printf ("Latency: \t%02.15f milliSec\t%02.15f milliSec\t%02.15f milliSec\n\n", StrctRandom[i][0].latency,
				StrctRandom[i][1].latency, (StrctRandom[i][0].latency + StrctRandom[i][1].latency)/2);
	}
	
	
	
	// 4 threads
	
	intNoOfThreads = 4;

	// loop to create threads
	for (i=0;i<intNoOfThreads;i++)
	{
		// initialize the stuments to be passed to threading function in structure
		strctTh[i].thread_num = i+1;
		strctTh[i].Block_size = 8;
		strctTh[i].block_index = 0;

		// create the thread, call the respective function with appropriate stuments  and check creation status
		if (pthread_create(&arrPTh[i], NULL, MemoryPerformanecal, (void *)&(strctTh[i]))!=0)
		{
			printf ("Unable to create thread %d", i+1);
			exit(0);
		}
	}

	
	for (i=0;i<intNoOfThreads;i++)
	{
		pthread_join(arrPTh[i], NULL);
	}

	// loop to create threads
	for (i=0;i<intNoOfThreads;i++)
	{
		// initialize the stuments to be passed to threading function in structure
		strctTh[i].thread_num = i+1;
		strctTh[i].Block_size = 8000;
		strctTh[i].block_index = 1;

		// create the thread, call the respective function with appropriate stuments  and check creation status
		if (pthread_create(&arrPTh[i], NULL, MemoryPerformanecal, (void *)&(strctTh[i]))!=0)
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
		// initialize the stuments to be passed to threading function in structure
		strctTh[i].thread_num = i+1;
		strctTh[i].Block_size = 8e+6;
		strctTh[i].block_index = 2;

		// create the thread, call the respective function with appropriate stuments  and check creation status
		if (pthread_create(&arrPTh[i], NULL, MemoryPerformanecal, (void *)&(strctTh[i]))!=0)
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
	printf ("\n\n\nMemory - Sequential Access Statistics\nDescription\tThread 1 Values\tThread 2 Values\tFinal Values\n");
	for (i=0;i<3;i++)
	{
		printf ("Block Size: \t%ld Bytes\t%ld Bytes\t%ld Bytes\t%ld Bytes\t%ld Bytes\n", StrctMem[i][0].Block_size,
				StrctMem[i][1].Block_size, StrctMem[i][2].Block_size,StrctMem[i][3].Block_size,StrctMem[i][3].Block_size);
		printf ("No. of Blocks: \t%ld\t%ld\t%ld\t%ld\t%ld\n", StrctMem[i][0].Block_num,
				StrctMem[i][1].Block_num,StrctMem[i][2].Block_num,StrctMem[i][3].Block_num,
				(StrctMem[i][0].Block_num + StrctMem[i][1].Block_num+StrctMem[i][2].Block_num + StrctMem[i][3].Block_num));
		printf ("Total Memory Size: \t%ld Bytes\t%ld Bytes\t%ld Bytes\t%ld Bytes\t%ld Bytes\n", StrctMem[i][0].total_memory,
				StrctMem[i][1].total_memory,StrctMem[i][2].total_memory,StrctMem[i][3].total_memory, 
				(StrctMem[i][0].total_memory + StrctMem[i][1].total_memory + StrctMem[i][2].total_memory +StrctMem[i][3].total_memory
				+StrctMem[i][4].total_memory));
		printf ("Throughput: \t%7.4f MBPS\t%7.4f MBPS\t%7.4f MBPS\t%7.4f MBPS\t%7.4f MBPS\n", StrctMem[i][0].throughput,
				StrctMem[i][1].throughput,StrctMem[i][2].throughput,StrctMem[i][3].throughput, (StrctMem[i][0].throughput + StrctMem[i][1].throughput+
				StrctMem[i][2].throughput+StrctMem[i][3].throughput));
		printf ("Latency: \t%02.15f milliSec\t%02.15f milliSec\t%02.15f milliSec\t%02.15f milliSec\t%02.15f milliSec\n\n", StrctMem[i][0].latency,
				StrctMem[i][1].latency,StrctMem[i][2].latency,StrctMem[i][3].latency, 
				(StrctMem[i][0].latency + StrctMem[i][1].latency+ StrctMem[i][2].latency+ StrctMem[i][3].latency)/4);
	}

	printf ("\n\n\nMemory - Random Access Statistics\nDescription\tThread 1 Values\tThread 2 Values\tFinal Values\n");
	for (i=0;i<3;i++)
	{
		printf ("Block Size: \t%ld Bytes\t%ld Bytes\t%ld Bytes\t%ld Bytes\t%ld Bytes\n", StrctRandom[i][0].Block_size,
				StrctRandom[i][1].Block_size, StrctRandom[i][2].Block_size, StrctRandom[i][3].Block_size,StrctRandom[i][3].Block_size);
		printf ("No. of Blocks: \t%ld\t%ld\t%ld\t%ld\t%ld\n", StrctRandom[i][0].Block_num,
				StrctRandom[i][1].Block_num,StrctRandom[i][2].Block_num, StrctRandom[i][3].Block_num,
				(StrctRandom[i][0].Block_num + StrctRandom[i][1].Block_num + StrctRandom[i][2].Block_num
				+ StrctRandom[i][3].Block_num));
		printf ("Total Memory Size: \t%ld Bytes\t%ld Bytes\t%ld Bytes\t%ld Bytes\t%ld Bytes\n", StrctRandom[i][0].total_memory,
				StrctRandom[i][1].total_memory,StrctRandom[i][2].total_memory,StrctRandom[i][3].total_memory, 
				(StrctRandom[i][0].total_memory + StrctRandom[i][1].total_memory + StrctRandom[i][2].total_memory
				+ StrctRandom[i][3].total_memory));
		printf ("Throughput: \t%7.4f MBPS\t%7.4f MBPS\n\t%7.4f MBPS\t%7.4f MBPS\t%7.4f MBPS\n", StrctRandom[i][0].throughput,
				StrctRandom[i][1].throughput,StrctRandom[i][2].throughput,StrctRandom[i][3].throughput, 
				(StrctRandom[i][0].throughput + StrctRandom[i][1].throughput + StrctRandom[i][2].throughput
				+ StrctRandom[i][3].throughput));
		printf ("Latency: \t%02.15f milliSec\t%02.15f milliSec\t%02.15f milliSec\t%02.15f milliSec\t%02.15f milliSec\n\n", StrctRandom[i][0].latency,
				StrctRandom[i][1].latency, StrctRandom[i][2].latency,
				StrctRandom[i][3].latency,
				(StrctRandom[i][0].latency + StrctRandom[i][1].latency+ StrctRandom[i][2].latency+ StrctRandom[i][3].latency)/4);
	}
	
	
	
	// 8 threads
	
	intNoOfThreads = 8;

	// loop to create threads
	for (i=0;i<intNoOfThreads;i++)
	{
		
		strctTh[i].thread_num = i+1;
		strctTh[i].Block_size = 8;
		strctTh[i].block_index = 0;

		
		if (pthread_create(&arrPTh[i], NULL, MemoryPerformanecal, (void *)&(strctTh[i]))!=0)
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
		// initialize the stuments to be passed to threading function in structure
		strctTh[i].thread_num = i+1;
		strctTh[i].Block_size = 8000;
		strctTh[i].block_index = 1;

		// create the thread, call the respective function with appropriate stuments  and check creation status
		if (pthread_create(&arrPTh[i], NULL, MemoryPerformanecal, (void *)&(strctTh[i]))!=0)
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
		// initialize the stuments to be passed to threading function in structure
		strctTh[i].thread_num = i+1;
		strctTh[i].Block_size = 8e+6;
		strctTh[i].block_index = 2;

		// create the thread, call the respective function with appropriate stuments  and check creation status
		if (pthread_create(&arrPTh[i], NULL, MemoryPerformanecal, (void *)&(strctTh[i]))!=0)
		{
			printf ("Unable to create thread %d", i+1);
			exit(0);
		}
	}

	
	for (i=0;i<intNoOfThreads;i++)
	{
		pthread_join(arrPTh[i], NULL);
	}

	// print the results for the experiments conducted
	printf ("\n\n\nMemory - Sequential Access Statistics\nDescription\tThread 1 Values\tThread 2\tThread 3\tThread 4 Values\tFinal Values\n");
	for (i=0;i<3;i++)
	{
		printf ("Block Size: \t%ld Bytes\t%ld Bytes\t%ld Bytes\t%ld Bytes\t%ld Bytes\t%ld Bytes\t%ld Bytes\t%ld Bytes\t%ld Bytes\n", StrctMem[i][0].Block_size,
				StrctMem[i][1].Block_size, StrctMem[i][2].Block_size,StrctMem[i][3].Block_size,
				StrctMem[i][4].Block_size,StrctMem[i][5].Block_size,StrctMem[i][6].Block_size,StrctMem[i][7].Block_size,
				StrctMem[i][7].Block_size);
		printf ("No. of Blocks: \t%ld\t%ld\t%ld\t%ld\t%ld\t%ld\t%ld\t%ld\t%ld\n", StrctMem[i][0].Block_num,
				StrctMem[i][1].Block_num,StrctMem[i][2].Block_num,StrctMem[i][3].Block_num,StrctMem[i][4].Block_num,
				StrctMem[i][5].Block_num,StrctMem[i][6].Block_num,StrctMem[i][7].Block_num,
				(StrctMem[i][0].Block_num + StrctMem[i][1].Block_num+StrctMem[i][2].Block_num + StrctMem[i][3].Block_num
				+StrctMem[i][4].Block_num+StrctMem[i][5].Block_num+StrctMem[i][6].Block_num+StrctMem[i][7].Block_num));
		printf ("Total Memory Size: \t%ld Bytes\t%ld Bytes\t%ld Bytes\t%ld Bytes\t%ld Bytes\t%ld Bytes\t%ld Bytes\t%ld Bytes\t%ld Bytes\n", StrctMem[i][0].total_memory,
				StrctMem[i][1].total_memory,StrctMem[i][2].total_memory,StrctMem[i][3].total_memory, 
				(StrctMem[i][0].total_memory + StrctMem[i][1].total_memory + StrctMem[i][2].total_memory +StrctMem[i][3].total_memory
				+StrctMem[i][4].total_memory+StrctMem[i][5].total_memory+StrctMem[i][6].total_memory+StrctMem[i][7].total_memory));
		printf ("Throughput: \t%7.4f MBPS\t%7.4f MBPS\t%7.4f MBPS\t%7.4f MBPS\t%7.4f MBPS\t%7.4f MBPS\t%7.4f MBPS\t%7.4f MBPS\t%7.4f MBPS\n", StrctMem[i][0].throughput,
				StrctMem[i][1].throughput,StrctMem[i][2].throughput,StrctMem[i][3].throughput,StrctMem[i][4].throughput,
				StrctMem[i][5].throughput,StrctMem[i][6].throughput,StrctMem[i][7].throughput,
				(StrctMem[i][0].throughput + StrctMem[i][1].throughput+
				StrctMem[i][2].throughput+StrctMem[i][3].throughput+StrctMem[i][4].throughput+StrctMem[i][5].throughput
				+StrctMem[i][6].throughput+StrctMem[i][7].throughput));
		printf ("Latency: \t%02.15f milliSec\t%02.15f milliSec\t%02.15f milliSec\t%02.15f milliSec\t%02.15f milliSec\t%02.15f milliSec\t%02.15f milliSec\t%02.15f milliSec\t%02.15f milliSec\n\n", 
		StrctMem[i][0].latency,
				StrctMem[i][1].latency,StrctMem[i][2].latency,StrctMem[i][3].latency,StrctMem[i][4].latency,StrctMem[i][5].latency, 
				StrctMem[i][6].latency, StrctMem[i][7].latency, 
				(StrctMem[i][0].latency + StrctMem[i][1].latency+ StrctMem[i][2].latency+ StrctMem[i][3].latency
				+StrctMem[i][4].latency+StrctMem[i][5].latency+StrctMem[i][6].latency+StrctMem[i][7].latency)/8);
	}

	printf ("\n\n\nMemory - Random Access Statistics\nDescription\tThread 1 Values\tThread 2 Values\tThread 3\tThread 4\tFinal Values\n");
	for (i=0;i<3;i++)
	{
		printf ("Block Size: \t%ld Bytes\t%ld Bytes\t%ld Bytes\t%ld Bytes\t%ld Bytes\t%ld Bytes\t%ld Bytes\t%ld Bytes\n", StrctRandom[i][0].Block_size,
				StrctRandom[i][1].Block_size, StrctRandom[i][2].Block_size, StrctRandom[i][3].Block_size,StrctRandom[i][4].Block_size
				,StrctRandom[i][5].Block_size,StrctRandom[i][6].Block_size,StrctRandom[i][7].Block_size,StrctRandom[i][7].Block_size);
		printf ("No. of Blocks: \t%ld\t%ld\t%ld\t%ld\t%ld\t%ld\t%ld\t%ld\t%ld\n", StrctRandom[i][0].Block_num,
				StrctRandom[i][1].Block_num,StrctRandom[i][2].Block_num, StrctRandom[i][3].Block_num,StrctRandom[i][4].Block_num,
				StrctRandom[i][5].Block_num,StrctRandom[i][6].Block_num,StrctRandom[i][7].Block_num,
				(StrctRandom[i][0].Block_num + StrctRandom[i][1].Block_num + StrctRandom[i][2].Block_num
				+ StrctRandom[i][3].Block_num+ StrctRandom[i][4].Block_num+ StrctRandom[i][5].Block_num+ StrctRandom[i][6].Block_num
				+ StrctRandom[i][7].Block_num));
		printf ("Total Memory Size: \t%ld Bytes\t%ld Bytes\t%ld Bytes\t%ld Bytes\t%ld Bytes\t%ld Bytes\t%ld Bytes\t%ld Bytes\t%ld Bytes\n", StrctRandom[i][0].total_memory,
				StrctRandom[i][1].total_memory,StrctRandom[i][2].total_memory,StrctRandom[i][3].total_memory,StrctRandom[i][4].total_memory, 
				StrctRandom[i][5].total_memory,StrctRandom[i][6].total_memory,StrctRandom[i][7].total_memory,
				(StrctRandom[i][0].total_memory + StrctRandom[i][1].total_memory + StrctRandom[i][2].total_memory
				+ StrctRandom[i][3].total_memory+ StrctRandom[i][4].total_memory+ StrctRandom[i][5].total_memory+ StrctRandom[i][6].total_memory
				+ StrctRandom[i][7].total_memory));
		printf ("Throughput: \t%7.4f MBPS\t%7.4f MBPS\n\t%7.4f MBPS\t%7.4f MBPS\t%7.4f MBPS\t%7.4f MBPS\t%7.4f MBPS\t%7.4f MBPS\t%7.4f MBPS\n", StrctRandom[i][0].throughput,
				StrctRandom[i][1].throughput,StrctRandom[i][2].throughput,StrctRandom[i][3].throughput,StrctRandom[i][4].throughput,
             StrctRandom[i][5].throughput,StrctRandom[i][6].throughput,	StrctRandom[i][7].throughput,			
				(StrctRandom[i][0].throughput + StrctRandom[i][1].throughput + StrctRandom[i][2].throughput
				+ StrctRandom[i][3].throughput+ StrctRandom[i][4].throughput+ StrctRandom[i][5].throughput+ StrctRandom[i][6].throughput
				+ StrctRandom[i][7].throughput));
		printf ("Latency: \t%02.15f milliSec\t%02.15f milliSec\t%02.15f milliSec\t%02.15f milliSec\t%02.15f milliSec\t%02.15f milliSec\t%02.15f milliSec\t%02.15f milliSec\t%02.15f milliSec\n\n", 
		StrctRandom[i][0].latency,
				StrctRandom[i][1].latency, StrctRandom[i][2].latency,
				StrctRandom[i][3].latency,StrctRandom[i][4].latency,StrctRandom[i][5].latency,StrctRandom[i][6].latency,StrctRandom[i][7].latency,
				(StrctRandom[i][0].latency + StrctRandom[i][1].latency+ StrctRandom[i][2].latency+ StrctRandom[i][3].latency
				+ StrctRandom[i][4].latency+ StrctRandom[i][5].latency+ StrctRandom[i][6].latency+ StrctRandom[i][7].latency)/8);
	}
}




// main function to call Benchmarking Experiments starts from here
void main()
{
	int i=0;
	int intReportInterval=1;
	int intRunTime=600;
	int intInput;
	MemoryBench();
	
}
// main function to call Benchmarking Experiments ends over here
