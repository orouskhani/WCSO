/******************************************/
/***        Author: Pei-Wei Tsai        ***/
/***   E-mail: pwtsai@bit.kuas.edu.tw   ***/
/***         Version: 2.0.0.0           ***/
/***   Released on: November 1, 2009    ***/
/******************************************/

#ifndef TAGCAT
#define TAGCAT

#include "iostream"
#include <string>
#include <fstream>


// Parameter setting:

/* Parameters for the Seeking Mode - Start */
#define SMP			5		    // The maximum contineuously stay and view times.
#define SRD		  0.2     // The persentage of the perturbation on the selected dimensions in the "Tracing" mode.
#define CDC			0.8     // Mutation Range form this point to the other.
#define SPC			1       // Self-position Considering in the "Seeking" mode. Set "1" to activate; set "0" to deactivate.
/* Parameters for the Seeking Mode - End   */

/* Parameter for the Tracing Mode - Start */
#define C1      2.0     // Parameter for the velocity
/* Parameter for the Tracing Mode - End   */

/* Parameter for repicking the cats to move by the tracing mode in the next iteration. - Start */
#define MR			0.02	  // The ratio of cats in the "Seeking" mode.
/* Parameter for repicking the cats to move by the tracing mode in the next iteration. - End   */

/* Structure Define of a "Cat" - Start */
typedef struct tagcat{

  double *d_pos;			  // Record the cat's coordinate.
  double val;				    // Fitness value, which is evaluated by the benchmark function.
  bool STFlag;				  // The flag controls the cat to move into the seeking mode or the tracing mode.
  double *d_vel;			  // The velocity corresponding to the position.

} tcat;
/* Structure Define of a "Cat" - End   */

void CSO_Initialization(tcat t_cat[],int i_PSize,int i_Dim,double d_InitL,double d_InitR,double d_MaxVel,int i_FN);
void CSO_Evaluation(tcat t_cat[],int i_PSize,int i_Dim,bool b_Maximize,int i_FN);
void CSO_Movement(tcat t_cat[],int i_PSize,int i_Dim,bool b_Maximize,int i_FN,double d_MaxVel);

#endif
