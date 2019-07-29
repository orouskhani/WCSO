/******************************************/
/***        Author: Pei-Wei Tsai        ***/
/***   E-mail: pwtsai@bit.kuas.edu.tw   ***/
/***         Version: 2.0.0.0           ***/
/***   Released on: November 5, 2009    ***/
/******************************************/

// CSO.cpp : Defines the entry point for the console application.

#include <stdio.h>								// Including the standard C library
#include <stdlib.h>								// Including the standard C library
#include <string.h>							  // Including the standard C library

/* Line 15 includes the main library of the CSO algorithm */
#include "CSO_lib.h"							// Including the main library of the CSO algorithm.
/* Line 17 includes the library supports the benchmark functions */
#include "Benchmark.h"						// Including the benchmark library, which contains the test functions.
/* Line 19 includes the library for counting the executing time. */
#include "mytimer.h"


void CSO_Algorithm(int i_Cycle,int i_Iteration,int i_PSize,int i_Dim,double d_InitL,double d_InitR,double d_MaxVel,bool b_Maximize,int i_FN,mytimer *timer,double d_avefns[],double d_avetime[])
{
	tcat *t_cat = NULL;							          // The populations are called "t_cat" in this program.
	int i, j, k;
  double d_Start, d_Stop;

	t_cat = new tcat [(i_PSize+1)];				    // Locate memory space for the artificial agents.
	for(k=0;k<(i_PSize+1);k++)					      // Locate the memory to store the coordinate and the velocity of the cats.
	{
		t_cat[k].d_pos = new double [i_Dim];
		t_cat[k].d_vel = new double [i_Dim];
	}

	for(i=0;i<i_Cycle;i++)						        // The for-loop for repeating the operation cycle.
	{
    mytimer_start(timer);                   // Start the timer for counting the process time.

    srand((unsigned long)(i+1));              // Set the random seed in accordance with the cycle.

    mytimer_hold(timer,1);                  // Get the system time and store it in the 1st set of the timer.
    d_Start=mytimer_get_hold(timer,1);

    CSO_Initialization(t_cat,i_PSize,i_Dim,d_InitL,d_InitR,d_MaxVel,i_FN); // Initial process of the CSO algorithm

		for(j=0;j<i_Iteration;j++)				      // The for-loop for repeating the iteration.
		{
      CSO_Evaluation(t_cat,i_PSize,i_Dim,b_Maximize,i_FN); // Evaluate the fitness value of every cat in the current iteration.
      CSO_Movement(t_cat,i_PSize,i_Dim,b_Maximize,i_FN,d_MaxVel);  // Move the cats in the solution space.
      mytimer_hold(timer,2);                // Get the system time and store it in the 2nd set of the timer.
      d_Stop=mytimer_get_hold(timer,2);
      d_avetime[j]+=(d_Stop-d_Start);       // Store the spent time so far to take average.
      d_avefns[j]+=t_cat[i_PSize].val;      // Store the near best solution found so far to take average.

      if((j==0)||(((j+1)%200)==0))
        printf("[Cycle : Iteration]: [%3d ,%5d ]=%.16f\n",i,(j+1),t_cat[i_PSize].val);

		}										                    // End of the for-loop of Iteration.

    mytimer_stop(timer);                    // Stop the timer.
	}											                    // End of the for-loop of Cycle.

	for(k=0;k<(i_PSize+1);k++)					      // The for-loop to delete the required spaces in the structure tcat.
	{											                    // Please note that this for-loop must be executed before "delete [] t_cat".
		delete [] t_cat[k].d_pos;
		delete [] t_cat[k].d_vel;
	}
	delete [] t_cat;
}


int main(int argc, char* argv[])
{
	/* Parameters for applying CSO to solve functions - Start */
	int i_Cycle[i_FuncNum]={50, 50, 50};		// Defines the total cycle for runing this algorithm. 
												// The number of the elements in "i_Cycle" correspnds to the "i_FuncNum" defined in the "Benchmark.h".
												// In this case, the program executes 50 times of the whole iterations to get the average output.

	int i_Iteration[i_FuncNum]={2000, 2000, 2000}; // Defines the total iteration number in one cycle.
												// The number of the elements in "i_Iteration" correspnds to the "i_FuncNum" defined in the "Benchmark.h".
												// In this case, the program executes 2000 iterations in one cycle.

	int i_Dim[i_FuncNum]={30, 30, 30};			// Defines the dimension of the benchmark functions.
												// The number of the elements in "i_Dim" correspnds to the "i_FuncNum" defined in the "Benchmark.h".
												// In this case, all the dimensions of the benchmark functions are set to 30.

	int i_PSize[i_FuncNum]={160, 160, 160};		// Defines the population size used to run the CSO algorithm.

  double d_InitL[i_FuncNum]={15.0, 2.56, 300.0};       // Defines the left border of the initial ranges.
  double d_InitR[i_FuncNum]={30.0, 5.12, 600.0};       // Defines the right border of the initial ranges.
  double d_MaxVel[i_FuncNum]={100.0, 10.0, 600.0};     // Defines the maximum velocity of the cats.
  bool b_Maximize[i_FuncNum]={0, 0, 0};                // Defines the goal of optimization. Set "1" to let CSO find the near maximum solution, and set "0" to find the minimum.
	/* Parameters for applying CSO to solve functions - End   */

  /* Parameter to store the result - Start */
	double *d_avefns = NULL;				          // "d_avefns" contains the fitness vaules added based on iterations for all the cycles in order to take average.
	double *d_avetime = NULL;				          // "d_avetime" contains the process time counted based on iterations. It will be averaged to get the final results.
	FILE *f_FnsRec = NULL, *f_TimRec = NULL;	// The file pointers for recording the result listed above.
  FILE *f_Observe = NULL;                   // The file pointer for recording the result listed above.
	char c_fname1[200], c_fname2[200];			  // Contains the file names for the file pointers.
  char c_fname3[200];                       // Contains the file name for the file pointer.
	/* Parameter to store the result - End   */

  mytimer *timer;
  timer=mytimer_create();

	int i, j;

	// Call the CSO algorithm.
	for(i=1;i<=i_FuncNum;i++)				                	// The for-loop for executing the benchmark function.
	{
    /* Initialize the parameters for recording the results - Start */
    d_avefns = new double [i_Iteration[(i-1)]];     // Allocate the memory for storing the averaged fitness values in every iteration.
    d_avetime = new double [i_Iteration[(i-1)]];    // Allocate the memory for storing the averaged process time in every iteration.
    for(j=0;j<i_Iteration[(i-1)];j++)
    {
      d_avefns[j]=0.0;
      d_avetime[j]=0.0;
    }
    /* Initialize the parameters for recording the results - End   */

		CSO_Algorithm(i_Cycle[(i-1)],i_Iteration[(i-1)],i_PSize[(i-1)],i_Dim[(i-1)],d_InitL[(i-1)],d_InitR[(i-1)],d_MaxVel[(i-1)],b_Maximize[(i-1)],i,timer,d_avefns,d_avetime);  // Call the CSO algorithm to solve the problem.

    /* Result Store - Start */
    sprintf(c_fname1,"CSO_Function%d_FitnessValue_%dItr_%dCyc_%dPop_%dDim.txt",i,i_Iteration[(i-1)],i_Cycle[(i-1)],i_PSize[(i-1)],i_Dim[(i-1)]);
    sprintf(c_fname2,"CSO_Function%d_ProcessTime_%dItr_%dCyc_%dPop_%dDim.txt",i,i_Iteration[(i-1)],i_Cycle[(i-1)],i_PSize[(i-1)],i_Dim[(i-1)]);
    sprintf(c_fname3,"CSO_Observe_Function%d_%dItr_%dCyc_%dPop_%dDim.txt",i,i_Iteration[(i-1)],i_Cycle[(i-1)],i_PSize[(i-1)],i_Dim[(i-1)]);

    if(!(f_FnsRec=fopen(c_fname1,"w")))
  	{
	  	printf("Failed to Open the File!\n");
		  exit(13);
  	}
    if(!(f_TimRec=fopen(c_fname2,"w")))
  	{
	  	printf("Failed to Open the File!\n");
		  exit(13);
  	}
    if(!(f_Observe=fopen(c_fname3,"w")))
  	{
	  	printf("Failed to Open the File!\n");
		  exit(13);
  	}

    for(j=0;j<i_Iteration[(i-1)];j++)
    {
      d_avefns[j]/=(double)i_Cycle[(i-1)];      // Take average to get the result.
      d_avetime[j]/=(double)i_Cycle[(i-1)];     // Take average to get the average process time.

      fprintf(f_FnsRec,"%f\n\n",d_avefns[j]);
      fprintf(f_TimRec,"%f\n\n",d_avetime[j]);
      fprintf(f_Observe,"[Cycles : Iteration : Population Size : Dimension] [%3d :%5d :%4d :%3d] [Fitness : Time]: [\t%.16f ,\t%.16f]\n\n",i_Cycle[(i-1)],j,i_PSize[(i-1)],i_Dim[(i-1)],d_avefns[j],d_avetime[j]);
    }

    fclose(f_FnsRec);
    fclose(f_TimRec);
    fclose(f_Observe);
    /* Result Store - End   */

    delete [] d_avefns;
    delete [] d_avetime;
	}											                        // End of the for-loop for executing the benchmark function.

  mytimer_free(timer);                          // Release the timer.

	return 0;
}
