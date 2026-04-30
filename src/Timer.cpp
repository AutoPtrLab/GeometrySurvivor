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
void Timer::setReady() {
    time=duration;
}
bool Timer::checkTime(float t){
    return t>=time;
}

void Timer::startTimer(float t){
    duration=t;
    reset();
}