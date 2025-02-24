#ifndef RPGE_E_TIMER
#define RPGE_E_TIMER

#include <stdbool.h>

typedef struct Timer_RPGE {
    unsigned int ID;
    int countTicks;
    int limitTicks;
    bool toReset;
} Timer_RPGE;

typedef struct TimerManager_TIME_RPGE {
    Timer_RPGE* timerList[30];
    int length;
    int tickSizeCap;
    int FPS;
} TimerManager_TIME_RPGE;

/**
 * Sets new refrence of a TimerManager_TIME_RPGE struct for use. 
 * 
 * @param manager TimerManager_TIME_RPGE* pointer to new manager which should be used. 
 * @param FPS frams per second of running program 
 * @return 0 if no error occured
 */
int INIT_TIME_RPGE(TimerManager_TIME_RPGE* manager, int FPS, int tickSizeCap);

/**
 * Creates Timer_RPGE struct which is managed by TimerManager_TIME_RPGE _timerManager struct.
 * @param ID of timer to be set
 * @param limitTicks sets the limit of tickets until timer is finished.
 * @return pointer of created Timer_RPGE struct 
 */
Timer_RPGE* setTimerTicks_TIME_RPGE(unsigned int ID, int limitTicks);

/**
 * Creates Timer_RPGE struct which is managed by TimerManager_TIME_RPGE _timerManager struct.
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
 * Frees TimerManger_RPGE struct from heap.
 * 
 * @param manager TimerManager_TIME_RPGE* pointer to be freed
 */
void _destroyTimerManager_TIME_RPGE(TimerManager_TIME_RPGE* manager);

/**
 * Quit _timerManager context.
 */
void QUIT_TIME_RPGE();

/**
 * @param timer pointer to Timer_RPGE struct which should be added.
 * @return 0 if no error occurred, otherwise 1 (no slot free / timer is NULL)
 */
int _addTimer_TimerManager_TIME_RPGE(Timer_RPGE* timer);

/**
 * Frees Timer struct from heap
 * @param ID of target Timer
 * @return 0 if target has been found, otherwise 1
 */
int removeTimer_TIME_RPGE(unsigned int ID);

/**
 * update _timeManager tick
 */
void _update_TIME_RPGE();

TimerManager_TIME_RPGE* _create_TimerManager_TIME_RPGE();
Timer_RPGE* _create_TimerTicks_TIME_RPGE(unsigned int ID, int sec);
Timer_RPGE* _create_TimerSec_TIME_RPGE(unsigned int ID, int sec, int FPS);


#endif