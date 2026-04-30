#pragma once


class Timer{

    private:

        float duration=0.0f; // number till the timer counts up to
        float time=0.0f;// actual time of the timer
        //if we want to have the power to paused it maybe use a bool:active

    public:
        Timer(float duration);
        void update(float dt);
        void reset();
        bool isReady() const ;
        void setReady(); //function so th etimer is already charge
        bool checkTime(float t); //it returns true if the time you pass is more or equal to the time in the timer
        void startTimer(float t); //if you need to start a timer with a different duration

};