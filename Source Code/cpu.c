#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<pthread.h>
#include<string.h>
#include<fcntl.h>

// defining constants
#define ITERATIONS 1000000000
#define NOOFFOPS 85
#define NOOFFOPS2 105

// structure definition starts from here
struct thread_arg_struct
{
	int intThreadNo;
	int intRunDuration;
	int intSamplingInterval;
	long lngBlockSize;
	int intBlockSizeIndex;
};

struct Flops_details
{
	int intThreadNo;
	double dblIterations;
	double dblTotalNoOfOps;
	struct timeval clkStart;
	struct timeval clkEnd;
	double dblGFlops;
};

struct CPUB2Data
{
	int intSamplingSequence;
	long int lngSamplingIntervalCounter;
	long int lngTotalCounter;
	double dblSamplingTime;
};


// global structure variable declaration
struct Flops_details strctFD[1][8];
struct Flops_details strctID[1][8];
struct thread_arg_struct strctTAS[8];
struct CPUB2Data strctCPUP2FlopsData[600][8];
struct CPUB2Data strctCPUP2IopsData[600][8];
int intSecCounter = 0;

// function to compute Flops
void *computeFlops(void *args)
{
	// variable declaration
	volatile double i;
	volatile double dblAddVar1 = 1.234567;
	volatile double dblAddVar2 = 2.098765;
	volatile double dblAddVar3 = 4.098765;
	volatile double dblAddVar4 = 1.098765;
	volatile double dblAddVar5 = 2.234567;
	volatile double dblAddVar6 = 3.234567;
	volatile double dblAddVar7 = 1.238906;
	volatile double dblAddVar8 = 3.056452;
	volatile double dblAddVar9 = 1.234567;
	volatile double dblAddVar10 = 2.098765;
	volatile double dblAddVar11 = 4.098765;
	volatile double dblAddVar12 = 1.098765;
	volatile double dblAddVar13 = 2.234567;
	volatile double dblAddVar14 = 3.234567;
	volatile double dblAddVar15 = 1.238906;
	volatile double dblAddVar16 = 3.056452;
	volatile double dblAddVar17 = 2.234567;
	volatile double dblAddVar18 = 3.234567;
	volatile double dblAddVar19 = 1.238906;
	volatile double dblAddVar20 = 3.056452;
	volatile double dblMulVar1 = 1.234567;
	volatile double dblMulVar2 = 2.098765;
	volatile double dblMulVar3 = 4.098765;
	volatile double dblMulVar4 = 1.098765;
	volatile double dblMulVar5 = 2.234567;
	volatile double dblMulVar6 = 3.234567;
	volatile double dblMulVar7 = 1.238906;
	volatile double dblMulVar8 = 3.056452;
	volatile double dblMulVar9 = 1.234567;
	volatile double dblMulVar10 = 2.098765;
	volatile double dblMulVar11 = 4.098765;
	volatile double dblMulVar12 = 1.098765;
	volatile double dblMulVar13 = 2.234567;
	volatile double dblMulVar14 = 3.234567;
	volatile double dblMulVar15 = 1.238906;
	volatile double dblMulVar16 = 3.056452;
	volatile double dblMulVar17 = 2.234567;
	volatile double dblMulVar18 = 3.234567;
	volatile double dblMulVar19 = 1.238906;
	volatile double dblMulVar20 = 3.056452;
	volatile double dblNoOfOpsCounter=0;
	struct timeval clkStart, clkPrev, clkEnd, clkTemp;
	struct thread_arg_struct *arg = args;
	gettimeofday(&clkStart, NULL);

	for(i = 0; (i < ITERATIONS);i++)
	{
		// Additions
		dblAddVar1 = dblAddVar1 + 0.05;
		dblAddVar2 = dblAddVar2 + 0.03;
		dblAddVar3 = dblAddVar3 + 0.08;
		dblAddVar4 = dblAddVar4 + 0.08;
		dblAddVar5 = dblAddVar5 + 0.02;
		dblAddVar6 = dblAddVar6 + 0.02;
		dblAddVar7 = dblAddVar7 + 0.02;
		dblAddVar8 = dblAddVar8 + 0.02;
		dblAddVar9 = dblAddVar9 + 0.05;
		dblAddVar10 = dblAddVar10 + 0.03;
		dblAddVar11 = dblAddVar11 + 0.08;
		dblAddVar12 = dblAddVar12 + 0.08;
		dblAddVar13 = dblAddVar13 + 0.02;
		dblAddVar14 = dblAddVar14 + 0.05;
		dblAddVar15 = dblAddVar15 + 0.09;
		dblAddVar16 = dblAddVar16 + 0.001;
		dblAddVar17 = dblAddVar17 + 0.5;
		dblAddVar18 = dblAddVar18 + 0.2;
		dblAddVar19 = dblAddVar19 + 0.9;
		dblAddVar20 = dblAddVar20 + 0.1;

		// Multiplications
		dblMulVar1 = dblMulVar1 * 0.05;
		dblMulVar2 = dblMulVar2 * 0.03;
		dblMulVar3 = dblMulVar3 * 0.03;
		dblMulVar4 = dblMulVar4 * 0.08;
		dblMulVar5 = dblMulVar5 * 0.02;
		dblMulVar6 = dblMulVar6 * 0.02;
		dblMulVar7 = dblMulVar7 * 0.02;
		dblMulVar8 = dblMulVar8 * 0.02;
		dblMulVar9 = dblMulVar9 * 0.05;
		dblMulVar10 = dblMulVar10 * 0.03;
		dblMulVar11 = dblMulVar11 * 0.03;
		dblMulVar12 = dblMulVar12 * 0.08;
		dblMulVar13 = dblMulVar13 * 0.02;
		dblMulVar14 = dblMulVar14 * 0.02;
		dblMulVar15 = dblMulVar15 * 0.02;
		dblMulVar16 = dblMulVar16 * 0.02;
		dblMulVar17 = dblMulVar17 * 0.02;
		dblMulVar18 = dblMulVar18 * 0.02;
		dblMulVar19 = dblMulVar19 * 0.02;
		dblMulVar20 = dblMulVar20 * 0.02;

		// Increment the Total Operations' counter
		dblNoOfOpsCounter = dblNoOfOpsCounter + NOOFFOPS;
	}

	gettimeofday(&clkEnd, NULL);

	strctFD[0][arg->intThreadNo-1].intThreadNo = arg->intThreadNo;
	strctFD[0][arg->intThreadNo-1].dblTotalNoOfOps = dblNoOfOpsCounter + 2;
	strctFD[0][arg->intThreadNo-1].dblIterations = i;
	strctFD[0][arg->intThreadNo-1].clkStart = clkStart;
	strctFD[0][arg->intThreadNo-1].clkEnd = clkEnd;

	//Flops computations formula
	strctFD[0][arg->intThreadNo-1].dblGFlops = (((double)dblNoOfOpsCounter)/
			((((double)clkEnd.tv_sec - (double)clkStart.tv_sec) + (((double)clkEnd.tv_usec - (double)clkStart.tv_usec) / 1000000)))) / 1000000000;
	return NULL;
}
// function to compute Iops 
void *computeIops(void *args)
{
	// variable declaration
	volatile int i = 0;
	volatile long lngAddVar1 = 1;
	volatile long lngAddVar2 = 2;
	volatile long lngAddVar3 = 9;
	volatile long lngAddVar4 = 4;
	volatile long lngAddVar5 = -7;
	volatile long lngAddVar6 = -3;
	volatile long lngAddVar7 = -3;
	volatile long lngAddVar8 = 5;
	volatile long lngAddVar9 = 1;
	volatile long lngAddVar10 = 2;
	volatile long lngAddVar11 = 9;
	volatile long lngAddVar12 = 4;
	volatile long lngAddVar13 = -7;
	volatile long lngAddVar14 = -3;
	volatile long lngAddVar15 = -3;
	volatile long lngAddVar16 = 5;
	volatile long lngAddVar17 = -7;
	volatile long lngAddVar18 = -3;
	volatile long lngAddVar19 = -3;
	volatile long lngAddVar20 = 5;
	volatile long lngMulVar1 = 1;
	volatile long lngMulVar2 = 2;
	volatile long lngMulVar3 = 9;
	volatile long lngMulVar4 = 4;
	volatile long lngMulVar5 = -7;
	volatile long lngMulVar6 = -3;
	volatile long lngMulVar7 = -3;
	volatile long lngMulVar8 = -3;
	volatile long lngMulVar9 = 1;
	volatile long lngMulVar10 = 2;
	volatile long lngMulVar11 = 9;
	volatile long lngMulVar12 = 4;
	volatile long lngMulVar13 = -7;
	volatile long lngMulVar14 = -3;
	volatile long lngMulVar15 = -3;
	volatile long lngMulVar16 = -3;
	volatile long lngMulVar17 = -7;
	volatile long lngMulVar18 = -3;
	volatile long lngMulVar19 = -3;
	volatile long lngMulVar20 = -3;
	volatile long int lngNoOfOpsCounter=0;
	struct timeval clkStart, clkPrev, clkEnd, clkTemp;
	struct thread_arg_struct *arg = args;

	gettimeofday(&clkStart, NULL);

	for(i = 0; (i < ITERATIONS);i++)
	{
		// Additions
		lngAddVar1 = lngAddVar1 + 5;
		lngAddVar2 = lngAddVar2 + 3;
		lngAddVar3 = lngAddVar3 + 8;
		lngAddVar4 = lngAddVar4 + 7;
		lngAddVar5 = lngAddVar5 + 4;
		lngAddVar6 = lngAddVar6 + 6;
		lngAddVar7 = lngAddVar7 + 1;
		lngAddVar8 = lngAddVar8 + 2;
		lngAddVar9 = lngAddVar9 + 5;
		lngAddVar10 = lngAddVar10 + 3;
		lngAddVar11 = lngAddVar11 + 8;
		lngAddVar12 = lngAddVar12 + 7;
		lngAddVar13 = lngAddVar13 + 4;
		lngAddVar14 = lngAddVar14 + 6;
		lngAddVar15 = lngAddVar15 + 1;
		lngAddVar16 = lngAddVar16 + 2;
		lngAddVar17 = lngAddVar17 + 4;
		lngAddVar18 = lngAddVar18 + 6;
		lngAddVar19 = lngAddVar19 + 1;
		lngAddVar20 = lngAddVar20 + 2;

		// Multiplications
		lngMulVar1 = lngMulVar1 * 5;
		lngMulVar2 = lngMulVar2 * 3;
		lngMulVar3 = lngMulVar3 * 8;
		lngMulVar4 = lngMulVar4 * 7;
		lngMulVar5 = lngMulVar5 * 4;
		lngMulVar6 = lngMulVar6 * 6;
		lngMulVar7 = lngMulVar7 * 1;
		lngMulVar8 = lngMulVar8 * 2;
		lngMulVar9 = lngMulVar9 * 5;
		lngMulVar10 = lngMulVar10 * 3;
		lngMulVar11 = lngMulVar11 * 8;
		lngMulVar12 = lngMulVar12 * 7;
		lngMulVar13 = lngMulVar13 * 4;
		lngMulVar14 = lngMulVar14 * 6;
		lngMulVar15 = lngMulVar15 * 1;
		lngMulVar16 = lngMulVar16 * 2;
		lngMulVar17 = lngMulVar17 * 4;
		lngMulVar18 = lngMulVar18 * 6;
		lngMulVar19 = lngMulVar19 * 1;
		lngMulVar20 = lngMulVar20 * 2;

		lngNoOfOpsCounter = lngNoOfOpsCounter + NOOFFOPS;
	}
	gettimeofday(&clkEnd, NULL);

	// initialize the structure variables with appropriate values
	strctID[0][arg->intThreadNo-1].intThreadNo = arg->intThreadNo;
	strctID[0][arg->intThreadNo-1].dblTotalNoOfOps = lngNoOfOpsCounter + 2;
	strctID[0][arg->intThreadNo-1].dblIterations = i;
	strctID[0][arg->intThreadNo-1].clkStart = clkStart;
	strctID[0][arg->intThreadNo-1].clkEnd = clkEnd;

	//Iops computations formula
	strctID[0][arg->intThreadNo-1].dblGFlops = (((double)lngNoOfOpsCounter)/
			((((double)clkEnd.tv_sec - (double)clkStart.tv_sec) + (((double)clkEnd.tv_usec - (double)clkStart.tv_usec) / 1000000)))) / 1000000000;
	return NULL;
}

// function to compute sample Flops 
void *computeFlops2(void *args)
{
	// variable declaration
	volatile double i;
	volatile double dblAddVar1 = 1.234567;
	volatile double dblAddVar2 = 2.098765;
	volatile double dblAddVar3 = 4.098765;
	volatile double dblAddVar4 = 1.098765;
	volatile double dblAddVar5 = 2.234567;
	volatile double dblAddVar6 = 3.234567;
	volatile double dblAddVar7 = 1.238906;
	volatile double dblAddVar8 = 3.056452;
	volatile double dblAddVar9 = 1.234567;
	volatile double dblAddVar10 = 2.098765;
	volatile double dblAddVar11 = 4.098765;
	volatile double dblAddVar12 = 1.098765;
	volatile double dblAddVar13 = 2.234567;
	volatile double dblAddVar14 = 3.234567;
	volatile double dblAddVar15 = 1.238906;
	volatile double dblAddVar16 = 3.056452;
	volatile double dblAddVar17 = 2.234567;
	volatile double dblAddVar18 = 3.234567;
	volatile double dblAddVar19 = 1.238906;
	volatile double dblAddVar20 = 3.056452;
	volatile double dblMulVar1 = 1.234567;
	volatile double dblMulVar2 = 2.098765;
	volatile double dblMulVar3 = 4.098765;
	volatile double dblMulVar4 = 1.098765;
	volatile double dblMulVar5 = 2.234567;
	volatile double dblMulVar6 = 3.234567;
	volatile double dblMulVar7 = 1.238906;
	volatile double dblMulVar8 = 3.056452;
	volatile double dblMulVar9 = 1.234567;
	volatile double dblMulVar10 = 2.098765;
	volatile double dblMulVar11 = 4.098765;
	volatile double dblMulVar12 = 1.098765;
	volatile double dblMulVar13 = 2.234567;
	volatile double dblMulVar14 = 3.234567;
	volatile double dblMulVar15 = 1.238906;
	volatile double dblMulVar16 = 3.056452;
	volatile double dblMulVar17 = 2.234567;
	volatile double dblMulVar18 = 3.234567;
	volatile double dblMulVar19 = 1.238906;
	volatile double dblMulVar20 = 3.056452;
	volatile double dblTotalCounter=0;
	volatile double dblSamplingIntervalCounter=0;
	struct thread_arg_struct *arg = args;
	while (intSecCounter<arg->intRunDuration)
	{
		// Additions
		dblAddVar1 = dblAddVar1 + 0.05;
		dblAddVar2 = dblAddVar2 + 0.03;
		dblAddVar3 = dblAddVar3 + 0.08;
		dblAddVar4 = dblAddVar4 + 0.08;
		dblAddVar5 = dblAddVar5 + 0.02;
		dblAddVar6 = dblAddVar6 + 0.02;
		dblAddVar7 = dblAddVar7 + 0.02;
		dblAddVar8 = dblAddVar8 + 0.02;
		dblAddVar9 = dblAddVar9 + 0.05;
		dblAddVar10 = dblAddVar10 + 0.03;
		dblAddVar11 = dblAddVar11 + 0.08;
		dblAddVar12 = dblAddVar12 + 0.08;
		dblAddVar13 = dblAddVar13 + 0.02;
		dblAddVar14 = dblAddVar14 + 0.05;
		dblAddVar15 = dblAddVar15 + 0.09;
		dblAddVar16 = dblAddVar16 + 0.001;
		dblAddVar17 = dblAddVar17 + 0.5;
		dblAddVar18 = dblAddVar18 + 0.2;
		dblAddVar19 = dblAddVar19 + 0.9;
		dblAddVar20 = dblAddVar20 + 0.1;

		// Multiplications
		dblMulVar1 = dblMulVar1 * 0.05;
		dblMulVar2 = dblMulVar2 * 0.03;
		dblMulVar3 = dblMulVar3 * 0.03;
		dblMulVar4 = dblMulVar4 * 0.08;
		dblMulVar5 = dblMulVar5 * 0.02;
		dblMulVar6 = dblMulVar6 * 0.02;
		dblMulVar7 = dblMulVar7 * 0.02;
		dblMulVar8 = dblMulVar8 * 0.02;
		dblMulVar9 = dblMulVar9 * 0.05;
		dblMulVar10 = dblMulVar10 * 0.03;
		dblMulVar11 = dblMulVar11 * 0.03;
		dblMulVar12 = dblMulVar12 * 0.08;
		dblMulVar13 = dblMulVar13 * 0.02;
		dblMulVar14 = dblMulVar14 * 0.02;
		dblMulVar15 = dblMulVar15 * 0.02;
		dblMulVar16 = dblMulVar16 * 0.02;
		dblMulVar17 = dblMulVar17 * 0.02;
		dblMulVar18 = dblMulVar18 * 0.02;
		dblMulVar19 = dblMulVar19 * 0.02;
		dblMulVar20 = dblMulVar20 * 0.02;

		dblTotalCounter = dblTotalCounter + NOOFFOPS2;
		dblSamplingIntervalCounter = dblSamplingIntervalCounter + NOOFFOPS2;

			strctCPUP2FlopsData[(int)intSecCounter][arg->intThreadNo-1].intSamplingSequence = intSecCounter;
			strctCPUP2FlopsData[(int)intSecCounter][arg->intThreadNo-1].lngSamplingIntervalCounter += (long int)dblSamplingIntervalCounter;
			strctCPUP2FlopsData[(int)intSecCounter][arg->intThreadNo-1].lngTotalCounter = (long int)dblTotalCounter + 12;
			strctCPUP2FlopsData[(int)intSecCounter][arg->intThreadNo-1].dblSamplingTime = 1;
			dblSamplingIntervalCounter = 0;

	}

	return NULL;
}

// function to compute sample Iops 
void *computeIops2(void *args)
{
	// variable declaring
	volatile int i = 0;
	volatile long lngAddVar1 = 1;
	volatile long lngAddVar2 = 2;
	volatile long lngAddVar3 = 9;
	volatile long lngAddVar4 = 4;
	volatile long lngAddVar5 = -7;
	volatile long lngAddVar6 = -3;
	volatile long lngAddVar7 = -3;
	volatile long lngAddVar8 = 5;
	volatile long lngAddVar9 = 1;
	volatile long lngAddVar10 = 2;
	volatile long lngAddVar11 = 9;
	volatile long lngAddVar12 = 4;
	volatile long lngAddVar13 = -7;
	volatile long lngAddVar14 = -3;
	volatile long lngAddVar15 = -3;
	volatile long lngAddVar16 = 5;
	volatile long lngAddVar17 = -7;
	volatile long lngAddVar18 = -3;
	volatile long lngAddVar19 = -3;
	volatile long lngAddVar20 = 5;
	volatile long lngMulVar1 = 1;
	volatile long lngMulVar2 = 2;
	volatile long lngMulVar3 = 9;
	volatile long lngMulVar4 = 4;
	volatile long lngMulVar5 = -7;
	volatile long lngMulVar6 = -3;
	volatile long lngMulVar7 = -3;
	volatile long lngMulVar8 = -3;
	volatile long lngMulVar9 = 1;
	volatile long lngMulVar10 = 2;
	volatile long lngMulVar11 = 9;
	volatile long lngMulVar12 = 4;
	volatile long lngMulVar13 = -7;
	volatile long lngMulVar14 = -3;
	volatile long lngMulVar15 = -3;
	volatile long lngMulVar16 = -3;
	volatile long lngMulVar17 = -7;
	volatile long lngMulVar18 = -3;
	volatile long lngMulVar19 = -3;
	volatile long lngMulVar20 = -3;
	volatile long int lngTotalCounter=0;
	volatile long int lngSamplingIntervalCounter=0;
	struct thread_arg_struct *arg = args;

	while (intSecCounter<arg->intRunDuration)
	{
		// Additions
		lngAddVar1 = lngAddVar1 + 5;
		lngAddVar2 = lngAddVar2 + 3;
		lngAddVar3 = lngAddVar3 + 8;
		lngAddVar4 = lngAddVar4 + 7;
		lngAddVar5 = lngAddVar5 + 4;
		lngAddVar6 = lngAddVar6 + 6;
		lngAddVar7 = lngAddVar7 + 1;
		lngAddVar8 = lngAddVar8 + 2;
		lngAddVar9 = lngAddVar9 + 5;
		lngAddVar10 = lngAddVar10 + 3;
		lngAddVar11 = lngAddVar11 + 8;
		lngAddVar12 = lngAddVar12 + 7;
		lngAddVar13 = lngAddVar13 + 4;
		lngAddVar14 = lngAddVar14 + 6;
		lngAddVar15 = lngAddVar15 + 1;
		lngAddVar16 = lngAddVar16 + 2;
		lngAddVar17 = lngAddVar17 + 4;
		lngAddVar18 = lngAddVar18 + 6;
		lngAddVar19 = lngAddVar19 + 1;
		lngAddVar20 = lngAddVar20 + 2;

		// Multiplications
		lngMulVar1 = lngMulVar1 * 5;
		lngMulVar2 = lngMulVar2 * 3;
		lngMulVar3 = lngMulVar3 * 8;
		lngMulVar4 = lngMulVar4 * 7;
		lngMulVar5 = lngMulVar5 * 4;
		lngMulVar6 = lngMulVar6 * 6;
		lngMulVar7 = lngMulVar7 * 1;
		lngMulVar8 = lngMulVar8 * 2;
		lngMulVar9 = lngMulVar9 * 5;
		lngMulVar10 = lngMulVar10 * 3;
		lngMulVar11 = lngMulVar11 * 8;
		lngMulVar12 = lngMulVar12 * 7;
		lngMulVar13 = lngMulVar13 * 4;
		lngMulVar14 = lngMulVar14 * 6;
		lngMulVar15 = lngMulVar15 * 1;
		lngMulVar16 = lngMulVar16 * 2;
		lngMulVar17 = lngMulVar17 * 4;
		lngMulVar18 = lngMulVar18 * 6;
		lngMulVar19 = lngMulVar19 * 1;
		lngMulVar20 = lngMulVar20 * 2;


		lngTotalCounter = lngTotalCounter + NOOFFOPS2;
		lngSamplingIntervalCounter = lngSamplingIntervalCounter + NOOFFOPS2;

			strctCPUP2IopsData[(int)intSecCounter][arg->intThreadNo-1].intSamplingSequence = intSecCounter;
			strctCPUP2IopsData[(int)intSecCounter][arg->intThreadNo-1].lngSamplingIntervalCounter += (long int)lngSamplingIntervalCounter;
			strctCPUP2IopsData[(int)intSecCounter][arg->intThreadNo-1].lngTotalCounter = (long int)lngTotalCounter + 12;
			strctCPUP2IopsData[(int)intSecCounter][arg->intThreadNo-1].dblSamplingTime = 1;			lngSamplingIntervalCounter = 0;

	}


	return NULL;
}

//funciton for runtime
void *runTimer (void *args)
{
	struct thread_arg_struct *arg = args;

	intSecCounter = 0;
	while (intSecCounter < arg->intRunDuration)
	{
		sleep(arg->intSamplingInterval);
		intSecCounter = intSecCounter + 1;
	}
	return NULL;
}

// function to call Flops & Iops benchmarking with 1,2,4 & 8 threads
void CPUBenchmarking_Part1()
{
	pthread_t arrPTh[8];
	int i = 0;
	int intNoOfThreads=0;
	double dblSumOps, dblTime1, dblTime2, dblTime3, dblTime4, dblTime5,dblTime6,dblTime7,dblTime8 , dblAvgTimeTaken;

	// FLOPS part
	intNoOfThreads = 1;

	for (i=0;i<intNoOfThreads;i++)
	{
		// initialize the arguments
		strctTAS[i].intThreadNo=i+1;

		// create the thread
		if (pthread_create(&arrPTh[i], NULL, computeFlops, (void *)&(strctTAS[i]))!=0)
		{
			printf ("Unable to create thread %d", i+1);
			exit(0);
		}
	}

	for (i=0;i<intNoOfThreads;i++)
	{
		pthread_join(arrPTh[i], NULL);
	}

	printf ("\n\nFLOPS computations - 1 Thread Statistics\nDescription\tThread 1 Values\n");
	printf ("Thread No: \t%d\n", strctFD[0][0].intThreadNo);
	printf ("Iterations: \t%f\n", strctFD[0][0].dblIterations);
	printf ("Total No of Operations: \t%f\n", strctFD[0][0].dblTotalNoOfOps);
	printf ("Flops: \t%f\n", strctFD[0][0].dblGFlops);
	printf ("Final Flops: \t%f\n", strctFD[0][0].dblGFlops);

	//Create worker thread
	intNoOfThreads = 2;

	for (i=0;i<intNoOfThreads;i++)
	{
		// initialize the arguments
		strctTAS[i].intThreadNo=i+1;

		// create the thread
		if (pthread_create(&arrPTh[i], NULL, computeFlops, (void *)&(strctTAS[i]))!=0)
		{
			printf ("Unable to create thread %d", i+1);
			exit(0);
		}
	}

	for (i=0;i<intNoOfThreads;i++)
	{
		pthread_join(arrPTh[i], NULL);
	}

	printf ("\n\nFLOPS computations - 2 Threads Statistics\nDescription\tThread 1 Values\tThread 2 Values\n");
	printf ("Thread No: \t%d\t%d\n", strctFD[0][0].intThreadNo, strctFD[0][1].intThreadNo);
	printf ("Iterations: \t%f\t%f\n", strctFD[0][0].dblIterations, strctFD[0][1].dblIterations);
	printf ("Total No of Operations: \t%f\t%f\n", strctFD[0][0].dblTotalNoOfOps, strctFD[0][1].dblTotalNoOfOps);
	printf ("Flops: \t%f\t%f\n", strctFD[0][0].dblGFlops, strctFD[0][1].dblGFlops);
	dblSumOps = strctFD[0][0].dblTotalNoOfOps + strctFD[0][1].dblTotalNoOfOps;
	dblTime1 = (double)(((double)strctFD[0][0].clkEnd.tv_sec - (double)strctFD[0][0].clkStart.tv_sec) +
			 (((double)strctFD[0][0].clkEnd.tv_usec - (double)strctFD[0][0].clkStart.tv_usec) / 1000000));
	dblTime2 = (double)(((double)strctFD[0][1].clkEnd.tv_sec - (double)strctFD[0][1].clkStart.tv_sec) +
			 (((double)strctFD[0][1].clkEnd.tv_usec - (double)strctFD[0][1].clkStart.tv_usec) / 1000000));
	dblAvgTimeTaken = (dblTime1 + dblTime2) / 2;
	printf ("Final Flops: \t%f\n", ((dblSumOps / dblAvgTimeTaken) / (double)1000000000));
	intNoOfThreads = 4;


	for (i=0;i<intNoOfThreads;i++)
	{
		// initialize the arguments
		strctTAS[i].intThreadNo=i+1;

		// create the thread
		if (pthread_create(&arrPTh[i], NULL, computeFlops, (void *)&(strctTAS[i]))!=0)
		{
			printf ("Unable to create thread %d", i+1);
			exit(0);
		}
	}

	for (i=0;i<intNoOfThreads;i++)
	{
		pthread_join(arrPTh[i], NULL);
	}

	printf ("\n\nFLOPS computations - 4 Threads Statistics\nDescription\tThread 1 Values\tThread 2 Values\tThread 3 Values\tThread 4 Values\n");
	printf ("Thread No: \t%d\t%d\t%d\t%d\n", strctFD[0][0].intThreadNo, strctFD[0][1].intThreadNo, strctFD[0][2].intThreadNo, strctFD[0][3].intThreadNo);
	printf ("Iterations: \t%f\t%f\t%f\t%f\n", strctFD[0][0].dblIterations, strctFD[0][1].dblIterations, strctFD[0][2].dblIterations, strctFD[0][3].dblIterations);
	printf ("Total No of Operations: \t%f\t%f\t%f\t%f\n", strctFD[0][0].dblTotalNoOfOps, strctFD[0][1].dblTotalNoOfOps, strctFD[0][2].dblTotalNoOfOps, strctFD[0][3].dblTotalNoOfOps);
	printf ("Flops: \t%f\t%f\t%f\t%f\n", strctFD[0][0].dblGFlops, strctFD[0][1].dblGFlops, strctFD[0][2].dblGFlops, strctFD[0][3].dblGFlops);
	dblSumOps = strctFD[0][0].dblTotalNoOfOps + strctFD[0][1].dblTotalNoOfOps + strctFD[0][2].dblTotalNoOfOps + strctFD[0][3].dblTotalNoOfOps;
	dblTime1 = (double)(((double)strctFD[0][0].clkEnd.tv_sec - (double)strctFD[0][0].clkStart.tv_sec) +
			 (((double)strctFD[0][0].clkEnd.tv_usec - (double)strctFD[0][0].clkStart.tv_usec) / 1000000));
	dblTime2 = (double)(((double)strctFD[0][1].clkEnd.tv_sec - (double)strctFD[0][1].clkStart.tv_sec) +
			 (((double)strctFD[0][1].clkEnd.tv_usec - (double)strctFD[0][1].clkStart.tv_usec) / 1000000));
	dblTime3 = (double)(((double)strctFD[0][2].clkEnd.tv_sec - (double)strctFD[0][2].clkStart.tv_sec) +
			 (((double)strctFD[0][2].clkEnd.tv_usec - (double)strctFD[0][2].clkStart.tv_usec) / 1000000));
	dblTime4 = (double)(((double)strctFD[0][3].clkEnd.tv_sec - (double)strctFD[0][3].clkStart.tv_sec) +
			 (((double)strctFD[0][3].clkEnd.tv_usec - (double)strctFD[0][3].clkStart.tv_usec) / 1000000));
	dblAvgTimeTaken = (dblTime1 + dblTime2 + dblTime3 + dblTime4) / 4;
	printf ("Final Flops: \t%f\n", ((dblSumOps / dblAvgTimeTaken) / (double)1000000000));

intNoOfThreads = 8;

	for (i=0;i<intNoOfThreads;i++)
	{
		// initialize the arguments
		strctTAS[i].intThreadNo=i+1;

		// create the thread
		if (pthread_create(&arrPTh[i], NULL, computeFlops, (void *)&(strctTAS[i]))!=0)
		{
			printf ("Unable to create thread %d", i+1);
			exit(0);
		}
	}

	// wait for threads to be finished
	for (i=0;i<intNoOfThreads;i++)
	{
		pthread_join(arrPTh[i], NULL);
	}


	printf ("\n\nFLOPS computations - 8 Threads Statistics\nDescription\tThread 1 Values\tThread 2 Values\tThread 3 Values\tThread 4 Values\tThread 5 Values\tThread 6 Values\Thread 7 Values\tThread 8 Values\n");
	printf ("Thread No: \t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", strctFD[0][0].intThreadNo, strctFD[0][1].intThreadNo, strctFD[0][2].intThreadNo, strctFD[0][3].intThreadNo, strctFD[0][4].intThreadNo, strctFD[0][5].intThreadNo, strctFD[0][6].intThreadNo, strctFD[0][7].intThreadNo);
	
	printf ("Iterations: \t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\n", strctFD[0][0].dblIterations, strctFD[0][1].dblIterations, strctFD[0][2].dblIterations, strctFD[0][3].dblIterations, strctFD[0][4].dblIterations, strctFD[0][5].dblIterations, strctFD[0][6].dblIterations, strctFD[0][7].dblIterations);

	printf ("Total No of Operations: \t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\n", strctFD[0][0].dblTotalNoOfOps, strctFD[0][1].dblTotalNoOfOps, strctFD[0][2].dblTotalNoOfOps, strctFD[0][3].dblTotalNoOfOps,strctFD[0][4].dblTotalNoOfOps, strctFD[0][5].dblTotalNoOfOps, strctFD[0][6].dblTotalNoOfOps, strctFD[0][7].dblTotalNoOfOps );
	printf ("Flops: \t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\n", strctFD[0][0].dblGFlops, strctFD[0][1].dblGFlops, strctFD[0][2].dblGFlops, strctFD[0][3].dblGFlops, strctFD[0][4].dblGFlops, strctFD[0][5].dblGFlops, strctFD[0][6].dblGFlops, strctFD[0][7].dblGFlops);

	dblSumOps = strctFD[0][0].dblTotalNoOfOps + strctFD[0][1].dblTotalNoOfOps + strctFD[0][2].dblTotalNoOfOps + strctFD[0][3].dblTotalNoOfOps + strctFD[0][4].dblTotalNoOfOps + strctFD[0][5].dblTotalNoOfOps + strctFD[0][6].dblTotalNoOfOps + strctFD[0][7].dblTotalNoOfOps;

	dblTime1 = (double)(((double)strctFD[0][0].clkEnd.tv_sec - (double)strctFD[0][0].clkStart.tv_sec) +
			 (((double)strctFD[0][0].clkEnd.tv_usec - (double)strctFD[0][0].clkStart.tv_usec) / 1000000));
	dblTime2 = (double)(((double)strctFD[0][1].clkEnd.tv_sec - (double)strctFD[0][1].clkStart.tv_sec) +
			 (((double)strctFD[0][1].clkEnd.tv_usec - (double)strctFD[0][1].clkStart.tv_usec) / 1000000));
	dblTime3 = (double)(((double)strctFD[0][2].clkEnd.tv_sec - (double)strctFD[0][2].clkStart.tv_sec) +
			 (((double)strctFD[0][2].clkEnd.tv_usec - (double)strctFD[0][2].clkStart.tv_usec) / 1000000));
	dblTime4 = (double)(((double)strctFD[0][3].clkEnd.tv_sec - (double)strctFD[0][3].clkStart.tv_sec) +
			 (((double)strctFD[0][3].clkEnd.tv_usec - (double)strctFD[0][3].clkStart.tv_usec) / 1000000));
	dblTime5 = (double)(((double)strctFD[0][4].clkEnd.tv_sec - (double)strctFD[0][4].clkStart.tv_sec)
+

			 (((double)strctFD[0][4].clkEnd.tv_usec - (double)strctFD[0][4].clkStart.tv_usec) / 1000000));
	dblTime6 = (double)(((double)strctFD[0][5].clkEnd.tv_sec - (double)strctFD[0][5].clkStart.tv_sec)
+

			 (((double)strctFD[0][5].clkEnd.tv_usec - (double)strctFD[0][5].clkStart.tv_usec) / 1000000));
	dblTime7 = (double)(((double)strctFD[0][6].clkEnd.tv_sec - (double)strctFD[0][6].clkStart.tv_sec)
+

			 (((double)strctFD[0][6].clkEnd.tv_usec - (double)strctFD[0][6].clkStart.tv_usec) / 1000000));
	dblTime8 = (double)(((double)strctFD[0][7].clkEnd.tv_sec - (double)strctFD[0][7].clkStart.tv_sec)
+

			 (((double)strctFD[0][7].clkEnd.tv_usec - (double)strctFD[0][7].clkStart.tv_usec) / 1000000));




	dblAvgTimeTaken = (dblTime1 + dblTime2 + dblTime3 + dblTime4 + dblTime5 + dblTime6 + dblTime7 + dblTime8) / 8;
	printf ("Final Flops: \t%f\n", ((dblSumOps / dblAvgTimeTaken) / (double)1000000000));



	//IOPS part
	intNoOfThreads = 1;

	for (i=0;i<intNoOfThreads;i++)
	{
		// initialize the arguments 
		strctTAS[i].intThreadNo=i+1;

		// create the thread
		if (pthread_create(&arrPTh[i], NULL, computeIops, (void *)&(strctTAS[i]))!=0)
		{
			printf ("Unable to create thread %d", i+1);
			exit(0);
		}
	}

	for (i=0;i<intNoOfThreads;i++)
	{
		pthread_join(arrPTh[i], NULL);
	}

	printf ("\n\nIOPS computations - 1 Thread Statistics\nDescription\tThread 1 Values\n");
	printf ("Thread No: \t%d\n", strctID[0][0].intThreadNo);
	printf ("Iterations: \t%f\n", strctID[0][0].dblIterations);
	printf ("Total No of Operations: \t%f\n", strctID[0][0].dblTotalNoOfOps);
	printf ("Iops: \t%f\n", strctID[0][0].dblGFlops);
	printf ("Final Iops: \t%f\n", strctID[0][0].dblGFlops);
	intNoOfThreads = 2;
	for (i=0;i<intNoOfThreads;i++)
	{
		// initialize the arguments
		strctTAS[i].intThreadNo=i+1;

		// create the thread
		if (pthread_create(&arrPTh[i], NULL, computeIops, (void *)&(strctTAS[i]))!=0)
		{
			printf ("Unable to create thread %d", i+1);
			exit(0);
		}
	}

	for (i=0;i<intNoOfThreads;i++)
	{
		pthread_join(arrPTh[i], NULL);
	}

	printf ("\n\nIOPS computations - 2 Threads Statistics\nDescription\tThread 1 Values\tThread 2 Values\n");
	printf ("Thread No: \t%d\t%d\n", strctID[0][0].intThreadNo, strctID[0][1].intThreadNo);
	printf ("Iterations: \t%f\t%f\n", strctID[0][0].dblIterations, strctID[0][1].dblIterations);
	printf ("Total No of Operations: \t%f\t%f\n", strctID[0][0].dblTotalNoOfOps, strctID[0][1].dblTotalNoOfOps);
	printf ("Iops: \t%f\t%f\n", strctID[0][0].dblGFlops, strctID[0][1].dblGFlops);
	dblSumOps = strctID[0][0].dblTotalNoOfOps + strctID[0][1].dblTotalNoOfOps;
	dblTime1 = (double)(((double)strctID[0][0].clkEnd.tv_sec - (double)strctID[0][0].clkStart.tv_sec) +
			 (((double)strctID[0][0].clkEnd.tv_usec - (double)strctID[0][0].clkStart.tv_usec) / 1000000));
	dblTime2 = (double)(((double)strctID[0][1].clkEnd.tv_sec - (double)strctID[0][1].clkStart.tv_sec) +
			 (((double)strctID[0][1].clkEnd.tv_usec - (double)strctID[0][1].clkStart.tv_usec) / 1000000));
	dblAvgTimeTaken = (dblTime1 + dblTime2) / 2;
	printf ("Final Iops: \t%f\n", ((dblSumOps / dblAvgTimeTaken) / (double)1000000000));
	intNoOfThreads = 4;

	for (i=0;i<intNoOfThreads;i++)
	{
		// initialize the arguments
		strctTAS[i].intThreadNo=i+1;

		// create the thread
		if (pthread_create(&arrPTh[i], NULL, computeIops, (void *)&(strctTAS[i]))!=0)
		{
			printf ("Unable to create thread %d", i+1);
			exit(0);
		}
	}

	for (i=0;i<intNoOfThreads;i++)
	{
		pthread_join(arrPTh[i], NULL);
	}
	printf ("\n\nIOPS computations - 4 Threads Statistics\nDescription\tThread 1 Values\tThread 2 Values\tThread 3 Values\tThread 4 Values\n");
	printf ("Thread No: \t%d\t%d\t%d\t%d\n", strctID[0][0].intThreadNo, strctID[0][1].intThreadNo, strctID[0][2].intThreadNo, strctID[0][3].intThreadNo);
	printf ("Iterations: \t%f\t%f\t%f\t%f\n", strctID[0][0].dblIterations, strctID[0][1].dblIterations, strctID[0][2].dblIterations, strctID[0][3].dblIterations);
	printf ("Total No of Operations: \t%f\t%f\t%f\t%f\n", strctID[0][0].dblTotalNoOfOps, strctID[0][1].dblTotalNoOfOps, strctID[0][2].dblTotalNoOfOps, strctID[0][3].dblTotalNoOfOps);
	printf ("Iops: \t%f\t%f\t%f\t%f\n", strctID[0][0].dblGFlops, strctID[0][1].dblGFlops, strctID[0][2].dblGFlops, strctID[0][3].dblGFlops);
	dblSumOps = strctID[0][0].dblTotalNoOfOps + strctID[0][1].dblTotalNoOfOps + strctID[0][2].dblTotalNoOfOps + strctID[0][3].dblTotalNoOfOps;
	dblTime1 = (double)(((double)strctID[0][0].clkEnd.tv_sec - (double)strctID[0][0].clkStart.tv_sec) +
			 (((double)strctID[0][0].clkEnd.tv_usec - (double)strctID[0][0].clkStart.tv_usec) / 1000000));
	dblTime2 = (double)(((double)strctID[0][1].clkEnd.tv_sec - (double)strctID[0][1].clkStart.tv_sec) +
			 (((double)strctID[0][1].clkEnd.tv_usec - (double)strctID[0][1].clkStart.tv_usec) / 1000000));
	dblTime3 = (double)(((double)strctID[0][2].clkEnd.tv_sec - (double)strctID[0][2].clkStart.tv_sec) +
			 (((double)strctID[0][2].clkEnd.tv_usec - (double)strctID[0][2].clkStart.tv_usec) / 1000000));
	dblTime4 = (double)(((double)strctID[0][3].clkEnd.tv_sec - (double)strctID[0][3].clkStart.tv_sec) +
			 (((double)strctID[0][3].clkEnd.tv_usec - (double)strctID[0][3].clkStart.tv_usec) / 1000000));
	dblAvgTimeTaken = (dblTime1 + dblTime2 + dblTime3 + dblTime4) / 4;
	printf ("Final Iops: \t%f\n", ((dblSumOps / dblAvgTimeTaken) / (double)1000000000));
	intNoOfThreads = 8;
	for (i=0;i<intNoOfThreads;i++)
	{
		// initialize the arguments 
		strctTAS[i].intThreadNo=i+1;

		// create the thread
		if (pthread_create(&arrPTh[i], NULL, computeIops, (void *)&(strctTAS[i]))!=0)
		{
			printf ("Unable to create thread %d", i+1);
			exit(0);
		}
	}

	for (i=0;i<intNoOfThreads;i++)
	{
		pthread_join(arrPTh[i], NULL);
	}


	printf ("\n\nIOPS computations - 8 Threads Statistics\nDescription\tThread 1 Values\tThread 2 Values\tThread 3 Values\tThread 4 Values\tThread 5 Values\tThread 6 Values\tThread 7 Values\tThread 8 Values\n");
	
	printf ("Thread No: \t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", strctID[0][0].intThreadNo, strctID[0][1].intThreadNo, strctID[0][2].intThreadNo, strctID[0][3].intThreadNo, strctID[0][4].intThreadNo, strctID[0][5].intThreadNo, strctID[0][6].intThreadNo, strctID[0][7].intThreadNo);
	
	printf ("Iterations: \t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\n", strctID[0][0].dblIterations, strctID[0][1].dblIterations, strctID[0][2].dblIterations, strctID[0][3].dblIterations, strctID[0][4].dblIterations, strctID[0][5].dblIterations, strctID[0][6].dblIterations, strctID[0][7].dblIterations);

	printf ("Total No of Operations: \t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\n", strctID[0][0].dblTotalNoOfOps, strctID[0][1].dblTotalNoOfOps, strctID[0][2].dblTotalNoOfOps, strctID[0][3].dblTotalNoOfOps, strctID[0][4].dblTotalNoOfOps, strctID[0][5].dblTotalNoOfOps, strctID[0][6].dblTotalNoOfOps, strctID[0][7].dblTotalNoOfOps);

	printf ("Iops: \t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\n", strctID[0][0].dblGFlops, strctID[0][1].dblGFlops, strctID[0][2].dblGFlops, strctID[0][3].dblGFlops, strctID[0][4].dblGFlops, strctID[0][5].dblGFlops, strctID[0][6].dblGFlops, strctID[0][7].dblGFlops);
	
	dblSumOps = strctID[0][0].dblTotalNoOfOps + strctID[0][1].dblTotalNoOfOps + strctID[0][2].dblTotalNoOfOps + strctID[0][3].dblTotalNoOfOps+ strctID[0][4].dblTotalNoOfOps+ strctID[0][5].dblTotalNoOfOps+ strctID[0][6].dblTotalNoOfOps+ strctID[0][7].dblTotalNoOfOps;

	dblTime1 = (double)(((double)strctID[0][0].clkEnd.tv_sec - (double)strctID[0][0].clkStart.tv_sec) +
			 (((double)strctID[0][0].clkEnd.tv_usec - (double)strctID[0][0].clkStart.tv_usec) / 1000000));
	dblTime2 = (double)(((double)strctID[0][1].clkEnd.tv_sec - (double)strctID[0][1].clkStart.tv_sec) +
			 (((double)strctID[0][1].clkEnd.tv_usec - (double)strctID[0][1].clkStart.tv_usec) / 1000000));
	dblTime3 = (double)(((double)strctID[0][2].clkEnd.tv_sec - (double)strctID[0][2].clkStart.tv_sec) +
			 (((double)strctID[0][2].clkEnd.tv_usec - (double)strctID[0][2].clkStart.tv_usec) / 1000000));
	dblTime4 = (double)(((double)strctID[0][3].clkEnd.tv_sec - (double)strctID[0][3].clkStart.tv_sec) +
			 (((double)strctID[0][3].clkEnd.tv_usec - (double)strctID[0][3].clkStart.tv_usec) / 1000000));
	dblTime5 = (double)(((double)strctID[0][4].clkEnd.tv_sec - (double)strctID[0][4].clkStart.tv_sec) +
			 (((double)strctID[0][4].clkEnd.tv_usec - (double)strctID[0][4].clkStart.tv_usec) / 1000000));
	
	dblTime6 = (double)(((double)strctID[0][5].clkEnd.tv_sec - (double)strctID[0][5].clkStart.tv_sec) +
			 (((double)strctID[0][5].clkEnd.tv_usec - (double)strctID[0][5].clkStart.tv_usec) / 1000000));
	
	dblTime7 = (double)(((double)strctID[0][6].clkEnd.tv_sec - (double)strctID[0][6].clkStart.tv_sec) +
			 (((double)strctID[0][6].clkEnd.tv_usec - (double)strctID[0][6].clkStart.tv_usec) / 1000000));
	
	dblTime8 = (double)(((double)strctID[0][7].clkEnd.tv_sec - (double)strctID[0][7].clkStart.tv_sec) +
			 (((double)strctID[0][7].clkEnd.tv_usec - (double)strctID[0][7].clkStart.tv_usec) / 1000000));
	
	


	dblAvgTimeTaken = (dblTime1 + dblTime2 + dblTime3 + dblTime4 + dblTime5 + dblTime6 + dblTime7 + dblTime8) / 8;
	
	printf ("Final Iops: \t%f\n", ((dblSumOps / dblAvgTimeTaken) / (double)1000000000));
}



// function to call Flops & Iops sampling benchmarking for 8 threads
void CPUBenchmarking_Part2(int intRunDuration, int intSamplingInterval)
{
	pthread_t arrPTh[9];
	int i = 0;
	int intNoOfThreads = 0;
	double dblSumOps, dblTime1, dblTime2, dblTime3, dblTime4, dblTime5, dblTime6, dblTime7, dblTime8, dblAvgTimeTaken, dblFinalFlops;

	//FLOPS
	intNoOfThreads = 8;
	for (i=0;i<intNoOfThreads;i++)
	{
		// initialize the arguments
		strctTAS[i].intThreadNo=i+1;
		strctTAS[i].intRunDuration = intRunDuration;
		strctTAS[i].intSamplingInterval = intSamplingInterval;

		// create the thread
		if (pthread_create(&arrPTh[i], NULL, computeFlops2, (void *)&(strctTAS[i]))!=0)
		{
			printf ("Unable to create thread %d", i+1);
			exit(0);
		}
	}

	// create the thread
	if (pthread_create(&arrPTh[i], NULL, runTimer, (void *)&(strctTAS[0]))!=0)
	{
		printf ("Unable to create thread %d", i+1);
		exit(0);
	}

	for (i=0;i<9;i++)
	{
		pthread_join(arrPTh[i], NULL);
	}

	printf ("\n\nFLOPS Sampling - 8 Threads Statistics\nSampling Sequence\tFinal Flops\n");
	for (i=0;i<intRunDuration;i++)
	{
		dblSumOps = ((double)strctCPUP2FlopsData[i][0].lngSamplingIntervalCounter + strctCPUP2FlopsData[i][1].lngSamplingIntervalCounter +
				strctCPUP2FlopsData[i][2].lngSamplingIntervalCounter + strctCPUP2FlopsData[i][3].lngSamplingIntervalCounter + strctCPUP2FlopsData[i][4].lngSamplingIntervalCounter+ strctCPUP2FlopsData[i][5].lngSamplingIntervalCounter+ strctCPUP2FlopsData[i][6].lngSamplingIntervalCounter+ strctCPUP2FlopsData[i][7].lngSamplingIntervalCounter);
		dblTime1 = strctCPUP2FlopsData[i][0].dblSamplingTime;
		dblTime2 = strctCPUP2FlopsData[i][1].dblSamplingTime;
		dblTime3 = strctCPUP2FlopsData[i][2].dblSamplingTime;
		dblTime4 = strctCPUP2FlopsData[i][3].dblSamplingTime;
		dblTime5 = strctCPUP2FlopsData[i][4].dblSamplingTime;
		dblTime6 = strctCPUP2FlopsData[i][5].dblSamplingTime;
		dblTime7 = strctCPUP2FlopsData[i][6].dblSamplingTime;
		dblTime8 = strctCPUP2FlopsData[i][7].dblSamplingTime;
		dblAvgTimeTaken = (dblTime1 + dblTime2 + dblTime3 + dblTime4 + dblTime5+ dblTime6+ dblTime7+ dblTime8) / 8;
		dblFinalFlops = ((dblSumOps / dblAvgTimeTaken) / (double)1000000000);
		printf ("%d\t%f\n", strctCPUP2FlopsData[i][0].intSamplingSequence + 1, dblFinalFlops);
	}



	//IOPS
	intNoOfThreads = 8;

	// loop to create threads
	for (i=0;i<intNoOfThreads;i++)
	{
		// initialize the arguments 
		strctTAS[i].intThreadNo=i+1;
		strctTAS[i].intRunDuration = intRunDuration;
		strctTAS[i].intSamplingInterval = intSamplingInterval;

		// create the thread
		if (pthread_create(&arrPTh[i], NULL, computeIops2, (void *)&(strctTAS[i]))!=0)
		{
			printf ("Unable to create thread %d", i+1);
			exit(0);
		}
	}

	// create the thread
	if (pthread_create(&arrPTh[i], NULL, runTimer, (void *)&(strctTAS[0]))!=0)
	{
		printf ("Unable to create thread %d", i+1);
		exit(0);
	}


	for (i=0;i<9;i++)
	{
		pthread_join(arrPTh[i], NULL);
	}

	printf ("\n\nIOPS Sampling - 8 Threads Statistics\nSampling Sequence\tFinal Iops\n");
	for (i=0;i<intRunDuration;i++)
	{
		dblSumOps = ((double)strctCPUP2IopsData[i][0].lngSamplingIntervalCounter + strctCPUP2IopsData[i][1].lngSamplingIntervalCounter +
				strctCPUP2IopsData[i][2].lngSamplingIntervalCounter + strctCPUP2IopsData[i][3].lngSamplingIntervalCounter+ strctCPUP2IopsData[i][4].lngSamplingIntervalCounter+ strctCPUP2IopsData[i][5].lngSamplingIntervalCounter+ strctCPUP2IopsData[i][6].lngSamplingIntervalCounter+ strctCPUP2IopsData[i][7].lngSamplingIntervalCounter);
		dblTime1 = strctCPUP2IopsData[i][0].dblSamplingTime;
		dblTime2 = strctCPUP2IopsData[i][1].dblSamplingTime;
		dblTime3 = strctCPUP2IopsData[i][2].dblSamplingTime;
		dblTime4 = strctCPUP2IopsData[i][3].dblSamplingTime;
		dblTime5 = strctCPUP2IopsData[i][4].dblSamplingTime;
		dblTime6 = strctCPUP2IopsData[i][5].dblSamplingTime;
		dblTime7 = strctCPUP2IopsData[i][6].dblSamplingTime;
		dblTime8 = strctCPUP2IopsData[i][7].dblSamplingTime;
		dblAvgTimeTaken = (dblTime1 + dblTime2 + dblTime3 + dblTime4 + dblTime5+ dblTime6+ dblTime7+ dblTime8 ) / 8;
		dblFinalFlops = ((dblSumOps / dblAvgTimeTaken) / (double)1000000000);

		printf ("%d\t%f\n", strctCPUP2IopsData[i][0].intSamplingSequence + 1, dblFinalFlops);
	}
}



// main function for CPU Bench marking 
void main()
{
	int i=0;
	int intReportInterval=1;
	int intRunTime=600;
	int intInput;
	{
				CPUBenchmarking_Part1 ();
				CPUBenchmarking_Part2 (600, 1);
	}
}


