#include "RPGE_E_time.h"
#include <errno.h>
#include <stdlib.h>
#include "log.h"

static TimerManager_RPGE* _timerManager;
static int _FPS;

int setTimerManager_TIME_RPGE(TimerManager_RPGE* manager, int FPS) {
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

void INIT_TIME_RPGE(int FPS) {
    log_debug("[init _timerManager {FPS=%d}]", FPS);
    _timerManager = malloc(sizeof(TimerManager_RPGE));
    _FPS = FPS;
}

void QUIT_TIME_RPGE() {
    destroyTimerManager_TIME_RPGE(_timerManager);
}

Timer_RPGE* setTimerTicks_TIME_RPGE(unsigned int ID, int ticks) {
    Timer_RPGE* timer = malloc(sizeof(Timer_RPGE));
    timer->countTicks = 0;
    timer->ID = ID;
    timer->limitTicks = ticks;
    return timer;
}

Timer_RPGE* setTimerSec_TIME_RPGE(unsigned int ID, int sec) {
    Timer_RPGE* timer = malloc(sizeof(Timer_RPGE));
    timer->countTicks = 0;
    timer->ID = ID;
    timer->limitTicks = sec * _FPS;
    return timer;
}

int addTimer_TimerManager_TIME_RPGE(Timer_RPGE* timer) {
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

int removeTimer_TimerManager_TIME_RPGE(unsigned int ID) {
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

void destroyTimerManager_TIME_RPGE(TimerManager_RPGE* manager) {
    // free timer 
    for (int i = 0; i < manager->length; i++) {
        free(manager->timerList[i]);
    }
    free(manager);
}

int destroyTimer_TIME_RPGE(unsigned int ID) {
    for (int i = 0; i < _timerManager->length; i++) {
        if(_timerManager->timerList[i]->ID == ID) {
            free(_timerManager->timerList[i]);
            return 0;
        }
    }
    return 1;
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

void _UPDATE_TIME_RPGE() {
    for (int i = 0; i < _timerManager->length; i++) {
        if (_timerManager->timerList[i] == NULL) {
            _timerManager->timerList[i]->countTicks++;
        }
    }
}