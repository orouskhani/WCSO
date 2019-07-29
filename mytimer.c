//#include <resource.h>
#include "mytimer.h"
#include "time.h"
#include <windows.h> //I've ommited this line.
#if defined(_MSC_VER) || defined(_MSC_EXTENSIONS)
  #define DELTA_EPOCH_IN_MICROSECS  11644473600000000Ui64
#else
  #define DELTA_EPOCH_IN_MICROSECS  11644473600000000ULL
#endif
 //Maysam, ezafe kardim!!!
struct timezone 
{
  int  tz_minuteswest; /* minutes W of Greenwich */
  int  tz_dsttime;     /* type of dst correction */
};
 
int gettimeofday(struct timeval *tv, struct timezone *tz)
{
  FILETIME ft;
  unsigned __int64 tmpres = 0;
  static int tzflag;
 
  if (NULL != tv)
  {
    GetSystemTimeAsFileTime(&ft);
 
    tmpres |= ft.dwHighDateTime;
    tmpres <<= 32;
    tmpres |= ft.dwLowDateTime;
 
    /*converting file time to unix epoch*/
    tmpres -= DELTA_EPOCH_IN_MICROSECS; 
    tmpres /= 10;  /*convert into microseconds*/
    tv->tv_sec = (long)(tmpres / 1000000UL);
    tv->tv_usec = (long)(tmpres % 1000000UL);
  }
 
  if (NULL != tz)
  {
    if (!tzflag)
    {
      _tzset();
      tzflag++;
    }
    tz->tz_minuteswest = _timezone / 60;
    tz->tz_dsttime = _daylight;
  }
 
  return 0;
}


mytimer *mytimer_create(void)
{
	mytimer *pTimer;
	
	pTimer=(mytimer *)malloc(sizeof(mytimer));
	pTimer->abs_stTime=0;
	pTimer->state=MYTIMER_STATE_STOP;
	
	return pTimer;
}

double mytimer_get_abs(void)
{
	struct timeval tp;
	struct timezone tz;
    int ret;

	ret=gettimeofday(&tp,&tz);
	if(ret!=0)
		return -1.0;

	return (double)tp.tv_sec+(double)tp.tv_usec/1e6;
}

int mytimer_start(mytimer *pTimer)
{
	double abs_time;

	abs_time=mytimer_get_abs();
	if(abs_time<0.0)
		return -1;

	pTimer->abs_stTime=abs_time;

	return 0;
}

double mytimer_hold(mytimer *pTimer,int index)
{
	double abs_time;

	abs_time=mytimer_get_abs();
	if(abs_time<0.0)
		return -1;

	pTimer->abs_hldTime[index]=abs_time;

	return 0;
}

double mytimer_stop(mytimer *pTimer)
{
	double abs_time;

	abs_time=mytimer_get_abs();
	if(abs_time<0.0)
		return -1;

	pTimer->abs_curTime=abs_time;

	return 0;
}

double mytimer_get_hold(mytimer *pTimer,int index)
{
	return pTimer->abs_hldTime[index]-pTimer->abs_stTime;
}

double mytimer_get_curr(mytimer *pTimer)
{
	return pTimer->abs_curTime-pTimer->abs_stTime;
}

void mytimer_free(mytimer *pTimer)
{
  	free(pTimer);
  	return;
}


