/******************************************/
/***        Author: Pei-Wei Tsai        ***/
/***   E-mail: pwtsai@bit.kuas.edu.tw   ***/
/***         Version: 2.0.0.0           ***/
/***   Released on: November 1, 2009    ***/
/******************************************/

#ifndef Benchmark
#define Behchmark

#define d_PIE				3.141592653589793238462643383279	// Defines the ratio of the circumference.
#define d_PII				6.283185307179586476925286768758	// Defines twice of the ration of the circumference.

#define i_FuncNum		3					// i_FuncNum defines how many test functions are built in the Benchamrk library.

double Benchmark(int i_fn,int i_dim,double d_pos[]);

/* To emply the Benchmark library to find the results of your test sets, please include the "Benchmark.h" above your main program. */
/* Parameter Description - Start */

/*   i_fn: It denots the number of the benchmark function that you want to use.    */
/*   i_dim: It contains the dimension you applied in the benchmark function.       */
/*   d_pos[]: It is the array contains the coordinate of your solution set.        */
/*                   The fitness value will be returned in the "double" format.    */
/*   [i_fn, Function Name]:                                                        */
/*                 [ 1  , Rosenbrock] [ 2  , Rastrigrin] [ 3  , Griewank]          */
/*                        [ 4  , Benchmark 4] [ 5  , Benchmark 5]                  */

/* Parameter Description - End   */

#endif
