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

};