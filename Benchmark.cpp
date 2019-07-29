/******************************************/
/***        Author: Pei-Wei Tsai        ***/
/***   E-mail: pwtsai@bit.kuas.edu.tw   ***/
/***         Version: 2.0.0.0           ***/
/***   Released on: November 1, 2009    ***/
/******************************************/

/* The "Benchmark.h" and the "Benchmark.cpp" composes a library contains i_FuncNum test functions. */
#include "Benchmark.h"			// Include its header file.
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double Benchmark(int i_fn,int i_dim,double d_pos[])
{
	int i, j;
	double d_tmp[4];	// variables for temporary storage.
	double d_result;	// cotains the result to return to the main program.
  
	/* initialize the parameters - Start */
	for(i=0;i<4;i++)
		d_tmp[i]=0.0;
	/* initialize the parameters - End   */

	if(i_fn==1)	// Rosenbrock Function
	{
		for(j=0;j<(i_dim-1);j++)
      d_tmp[0]+=(100.0*(pow((d_pos[j]-pow(d_pos[j-1],2.0)),2.0))+pow((d_pos[j-1]-1.0),2.0));

    d_result=d_tmp[0];
	}
	else if(i_fn==2)	// Rastrigrin Function
	{
		for(j=0;j<i_dim;j++)
		{
			d_tmp[0]=pow(d_pos[j],2.0);
			d_tmp[1]=(10.0*cos(d_PII*d_pos[j]));
			d_tmp[2]+=(d_tmp[0]-d_tmp[1]+10.0);
		}
		d_result=d_tmp[2];
	}
	else if(i_fn==3)	// Griewank Function
	{
		d_tmp[2]=1.0;

		for(j=0;j<i_dim;j++)
		{
			d_tmp[0]+=(pow((d_pos[j]-100.0),2.0));
			
			d_tmp[1]=((d_pos[j]-100.0)/sqrt((j+1)));
			d_tmp[2]*=cos(d_tmp[1]);
		}
		d_result=(0.00025*d_tmp[0]-d_tmp[2]+1.0);
	}
/*
	else if(i_fn==4)	// Test Function 4
	{
	}
	else if(i_fn==5)  // Test Function 5
	{
	}
	else // Test Function 6
	{
	}
*/

  return d_result;
}