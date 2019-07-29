#ifndef MYTIMER
#define MYTIMER

#ifdef __cplusplus
extern "C" {
#endif

#define MYTIMER_MAX_TIMER 100

enum mytimer_state {
  	MYTIMER_STATE_STOP=0,
  	MYTIMER_STATE_RUNNING
};

typedef struct tagmytimer {
	double abs_stTime;
	double abs_hldTime[MYTIMER_MAX_TIMER];
	double abs_curTime;

	int state;
} mytimer;

mytimer *mytimer_create(void);
double mytimer_get_abs(void);
int mytimer_start(mytimer *pTimer);
double mytimer_hold(mytimer *pTimer,int index);
double mytimer_stop(mytimer *pTimer);
double mytimer_get_hold(mytimer *pTimer,int index);
double mytimer_get_curr(mytimer *pTimer);
void mytimer_free(mytimer *pTimer);



#ifdef __cplusplus
}
#endif



#endif
