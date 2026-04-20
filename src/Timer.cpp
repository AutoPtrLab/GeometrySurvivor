#include "Timer.h"

Timer::Timer(float duration):duration(duration){}
void Timer::update(float dt){

    time+=dt;
}
void Timer::reset(){
    time = 0.0f;
}
bool Timer::isReady() const {
    return time>=duration;
}