#ifndef RPGE_E_TIMER
#define RPGE_E_TIMER

#include <stdbool.h>

typedef struct Timer_RPGE {
    unsigned int ID;
    int countTicks;
    int limitTicks;
} Timer_RPGE;

typedef struct TimerManager_RPGE {
    Timer_RPGE* timerList[30];
    int length;
} TimerManager_RPGE;

/**
 * Sets new refrence of a TimerManager_RPGE struct for use. 
 * 
 * @param manager TimerManager_RPGE* pointer to new manager which should be used. 
 * @param FPS frams per second of running program 
 * @return 0 if no error occured
 */
int setTimerManager_TIME_RPGE(TimerManager_RPGE* manager, int FPS);

/**
 * Creates Timer_RPGE struct which is managed by TimerManager_RPGE _timerManager struct.
 * @param ID of timer to be set
 * @param limitTicks sets the limit of tickets until timer is finished.
 * @return pointer of created Timer_RPGE struct 
 */
Timer_RPGE* setTimerTicks_TIME_RPGE(unsigned int ID, int limitTicks);

/**
 * Creates Timer_RPGE struct which is managed by TimerManager_RPGE _timerManager struct.
 * @param ID of timer to be set
 * @param sec sets the limit of sec until timer is finished.
 * @return pointer of created Timer_RPGE struct 
 */
Timer_RPGE* setTimerSec_TIME_RPGE(unsigned int ID, int sec);

/**
 * Checks if timer has reached limitTicks.
 * 
 * @param ID of target Timer
 * @return true if timer is finished
 */
bool checkTimer_TIME_RPGE(unsigned int ID);

/**
 * Frees Timer struct from heap
 * @param ID of target Timer
 * @return 0 if target has been found, otherwise 1
 */
int destroyTimer_TIME_RPGE(unsigned int ID);

/**
 * Frees TimerManger_RPGE struct from heap.
 * 
 * @param manager TimerManager_RPGE* pointer to be freed
 */
void destroyTimerManager_TIME_RPGE(TimerManager_RPGE* manager);

/**
 * Initzialize default TimerManager_RPGE struct for use.
 * @param FPS frams per second of running program.
 */
void INIT_TIME_RPGE(int FPS);

/**
 * Quit _timerManager context.
 */
void QUIT_TIME_RPGE();

/**
 * @param timer pointer to Timer_RPGE struct which should be added.
 * @return 0 if no error occurred, otherwise 1 (no slot free / timer is NULL)
 */
int addTimer_TimerManager_TIME_RPGE(Timer_RPGE* timer);

/**
 * @return 0 if no error occurred, otherwise 1
 */
int removeTimer_TimerManager_TIME_RPGE(unsigned int ID);

/**
 * update _timeManager tick
 */
void _UPDATE_TIME_RPGE();

#endif