#include "RPGE_E_time.h"
#include <errno.h>
#include <stdlib.h>
#include "log.h"

static TimerManager_TIME_RPGE* _timerManager;
static int _FPS;

int INIT_TIME_RPGE(TimerManager_TIME_RPGE* manager, int FPS)
{
    if (manager == NULL) {
        log_error("setTimerManager_TIME(): manager%s is invalid", manager);
        errno = EINVAL;
        return 1;
    }
    _timerManager = manager;
    _FPS = FPS;
    log_debug("[set new _timerManager {FPS=%d}]", FPS);
    return 0;
}

void QUIT_TIME_RPGE() {
    _destroyTimerManager_TIME_RPGE(_timerManager);
}

Timer_RPGE* setTimerTicks_TIME_RPGE(unsigned int ID, int ticks) {
    Timer_RPGE* timer = _create_TimerTicks_TIME_RPGE(ID, ticks);
    if (timer == NULL) return NULL;
    if (_addTimer_TimerManager_TIME_RPGE(timer)) {
        free(timer);
        return NULL;
    } 
    return timer;
}

Timer_RPGE* setTimerSec_TIME_RPGE(unsigned int ID, int sec) {
    Timer_RPGE* timer = setTimerTicks_TIME_RPGE(ID, sec * _FPS);
    return timer;
}

int _addTimer_TimerManager_TIME_RPGE(Timer_RPGE* timer) {
    if (timer == NULL) {
        log_error("addTimer_TimerManager_TIME_RPGE(): timer%s is invalid", timer);
        errno = EINVAL;
        return 1;
    }
    for(int i = 0; i < _timerManager->length; i++) {
        if (_timerManager->timerList[i] == NULL) {
            _timerManager->timerList[i] = timer;
            return 0;
        }
    }
    log_trace("addTimer_TimerManager_TIME_RPGE(): for ID=%d no timer was found", timer->ID);
    return 1;
}

int removeTimer_TIME_RPGE(unsigned int ID) {
    for (int i = 0; i < _timerManager->length; i++) {
        if (_timerManager->timerList[i]->ID == ID) {
            free(_timerManager->timerList[i]);
            _timerManager->timerList[i] = NULL;
            return 0;
        }
    }
    log_trace("removeTimer_TimerManager_TIME_RPGE(): for ID=%d no timer was found", ID);
    return 1;
}

void _destroyTimerManager_TIME_RPGE(TimerManager_TIME_RPGE* manager) {
    // free timer 
    for (int i = 0; i < manager->length; i++) {
        free(manager->timerList[i]);
    }
    free(manager);
}

bool checkTimer_TIME_RPGE(unsigned int ID) {
    for (int i = 0; i < _timerManager->length; i++) {
        if (_timerManager->timerList[i]->ID == ID) {
            if (_timerManager->timerList[i]->limitTicks == _timerManager->timerList[i]->countTicks) 
            {
                _timerManager->timerList[i]->countTicks = 0;
                return true;
            }
            return false;
        }
    }
}

void _update_TIME_RPGE() {
    for (int i = 0; i < _timerManager->length; i++) {
        if (_timerManager->timerList[i] == NULL) {
            _timerManager->timerList[i]->countTicks++;
        }
    }
}

TimerManager_TIME_RPGE* _create_TimerManager_TIME_RPGE() {
    TimerManager_TIME_RPGE* manager = malloc(sizeof(TimerManager_TIME_RPGE));
    manager->length = 30;
    for (int i = 0; i < manager->length; i++) {
        manager->timerList[i] = NULL;
    }
    log_trace("[Created TimeManager_TIME_RPGE]");
    return manager;
}

Timer_RPGE* _create_TimerSec_TIME_RPGE(unsigned int ID, int sec, int FPS) {
    return _create_TimerTicks_TIME_RPGE(ID, FPS* sec);
}

Timer_RPGE* _create_TimerTicks_TIME_RPGE(unsigned int ID, int ticks) {
    Timer_RPGE* timer = malloc(sizeof(Timer_RPGE));
    if (timer == NULL) return NULL;
    timer->countTicks = 0;
    timer->ID = ID;
    timer->limitTicks = ticks;
    return timer;
}