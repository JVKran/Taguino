#ifndef RECIEVER_HPP
#define RECIEVER_HPP

#include "hwlib.hpp"
#include "rtos"

class msg_decoder : public rtos::task<>{
private:
    uint16_t irMessage;
    rtos::channel<uint16_t, 1024> pauses;
public:
    msg_decoder(uint16_t irMessage);
};

class msg_listener{
public:
    virtual void msg_listener(const int m) = 0;
};

class msg_logger : public rtos::task<>{
private:
	rtos::channel<uint_fast64_t, 1024> messages;
public:
    msg_logger(){}

};

class pause_listener{
public:
    virtual void pause_listener(const uint_fast64_t pause) = 0;
};

class pause_detector : public rtos::task<>{
private:
    hwlib::target::pin_in & pinIR;
    pause_listener & listener;
    rtos::clock clock;
    rtos::channel<int, 1024> detections;

    uint_fast64_t countedDuration;
    uint_fast64_t pauseDuration;
    uint_fast64_t getPauseDuration();
public:
    pause_detector(hwlib::target::pin_in & pinIR, pause_listener & listener);
    pauseDetected(int n);
};
#endif /*reciever.hpp*/