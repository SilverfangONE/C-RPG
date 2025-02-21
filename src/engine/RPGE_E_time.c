#include "RPGE_E_time.h"
#include "log.h"
#include <errno.h>
#include <stdlib.h>
#include <string.h>


static TimerManager_TIME_RPGE *_timerManager;
const char SYSTEM_TIMER_ID[] = "_system";

TimerManager_TIME_RPGE* INIT_TIME_RPGE(int FPS, int tickSizeCap)
{
    _timerManager = _create_TimerManager_TIME_RPGE();
    _timerManager->tickSizeCap = tickSizeCap;
    _timerManager->FPS = FPS;
    // logging.
    Timer_RPGE temp;
    log_debug("[set new _timerManager {FPS=%d, slotSize=%d, tickSizeCap=%d, maxCharIDSize=%d}]", _timerManager->FPS,
        _timerManager->length, _timerManager->tickSizeCap, sizeof(temp.ID)-1);
    setTimerSec_TIME_RPGE(SYSTEM_TIMER_ID, 10);
    return _timerManager;
}
    
void QUIT_TIME_RPGE()
{
    _destroyTimerManager_TIME_RPGE(_timerManager);
}
    
Timer_RPGE *setTimerTicks_TIME_RPGE(const char* ID, int ticks)
{
        Timer_RPGE *timer = _create_TimerTicks_TIME_RPGE(ID, ticks);
        if (timer == NULL)
        return NULL;
        if (_addTimer_TimerManager_TIME_RPGE(timer))
        {
            free(timer);
        return NULL;
    }
    log_trace("[Created Timer_RPGE {.ID='%s', .limitTicks=%d, sec=%d}]", timer->ID, timer->limitTicks, timer->limitTicks / _timerManager->FPS);
    return timer;
}

Timer_RPGE *setTimerSec_TIME_RPGE(const char* ID, int sec)
{
    Timer_RPGE *timer = setTimerTicks_TIME_RPGE(ID, sec * _timerManager->FPS);
    return timer;
}

int _addTimer_TimerManager_TIME_RPGE(Timer_RPGE *timer)
{
    if (timer == NULL)
    {
        log_error("addTimer_TimerManager_TIME_RPGE(): timer is NULL", timer);
        errno = EINVAL;
        return 1;
    }
    for (int i = 0; i < _timerManager->length; i++)
    {
        if (_timerManager->timerList[i] == NULL)
        {
            _timerManager->timerList[i] = timer;
            return 0;
        }
    }
    log_warn("addTimer_TimerManager_TIME_RPGE(): for ID {'%s'} no timer was found", timer->ID);
    return 1;
}

int removeTimer_TIME_RPGE(const char* ID)
{
    for (int i = 0; i < _timerManager->length; i++)
    {
        #ifdef _WIN32
            if (_stricmp(_timerManager->timerList[i]->ID, ID) == 0)
            {
                free(_timerManager->timerList[i]);
                _timerManager->timerList[i] = NULL;
                return 0;
            }
        #elif defined(__linux__) || defined(__APPLE__)
            if(strcasecmp(_timerManager->timerList[i]->ID, ID) == 0) 
            {
                free(_timerManager->timerList[i]);
                _timerManager->timerList[i] = NULL;
                return 0;
            }
        #endif
    }
    log_warn("removeTimer_TimerManager_TIME_RPGE(): for ID {'%s'} no timer was found", ID);
    return 1;
}

void _destroyTimerManager_TIME_RPGE(TimerManager_TIME_RPGE *manager)
{
    // free timer
    for (int i = 0; i < manager->length; i++)
    {
        free(manager->timerList[i]);
    }
    free(manager);
}

bool checkTimer_TIME_RPGE(const char* ID)
{
    for (int i = 0; i < _timerManager->length; i++)
    {
        if (_timerManager->timerList[i] == NULL)
        {
            continue;
        }
    
        #ifdef _WIN32
            if (_stricmp(_timerManager->timerList[i]->ID, ID) != 0)
            {
                continue;
            }
        #elif defined(__linux__) || defined(__APPLE__)
            if(strcasecmp(_timerManager->timerList[i]->ID, ID) != 0) 
            {
                continue;
            }
        #endif
    
        // check limitTicks with countTicks.
        if (_timerManager->timerList[i]->limitTicks == _timerManager->timerList[i]->countTicks)
        {
            _timerManager->timerList[i]->toReset = true;
            return true;
        }
        return false;
    }
    log_warn("checkTimer_TIME_RPGE(): Timer {.ID='%s'} doesn't exist", ID);
    return false;
}

void _update_TIME_RPGE()
{
    // check if TIME_RPGE is init.
    if (_timerManager == NULL)
    {
        log_error("_update_TIME_RPGE(): no _timerManager is set!");
        return;
    }
    for (int i = 0; i < _timerManager->length; i++)
    {
        // check if slot is not empty and a timer needs to be updated
        if (_timerManager->timerList[i] != NULL)
        {
            if (_timerManager->timerList[i]->countTicks >= _timerManager->tickSizeCap ||
                _timerManager->timerList[i]->toReset)
            {
                _timerManager->timerList[i]->toReset = false;
                _timerManager->timerList[i]->countTicks = 0;
            }
            else
            {
                _timerManager->timerList[i]->countTicks++;
            }
        }
    }
}

TimerManager_TIME_RPGE *_create_TimerManager_TIME_RPGE()
{
    TimerManager_TIME_RPGE *manager = malloc(sizeof(TimerManager_TIME_RPGE));
    manager->length = 30;
    for (int i = 0; i < manager->length; i++)
    {
        manager->timerList[i] = NULL;
    }
    log_trace("[Created TimeManager_TIME_RPGE]");
    return manager;
}

Timer_RPGE *_create_TimerSec_TIME_RPGE(const char* ID, int sec, int FPS)
{
    return _create_TimerTicks_TIME_RPGE(ID, FPS * sec);
}

Timer_RPGE *_create_TimerTicks_TIME_RPGE(const char* ID, int ticks)
{
    Timer_RPGE *timer = malloc(sizeof(Timer_RPGE));
    if (timer == NULL)
        return NULL;
    if (ID == NULL || strnlen(ID, sizeof(timer->ID)) < 1) 
    {
        log_error("_create_TimerTicks_TIME_RPGE: ID {'%s'} is invalid!", ID);
        errno = EINVAL;
        return NULL;
    }
    timer->toReset = false;
    // first time call is true;
    timer->countTicks = ticks;
    strncpy(timer->ID, ID, sizeof(timer->ID) - 1);
    timer->ID[sizeof(timer->ID)] = '\0';
    timer->limitTicks = ticks;
    return timer;
}