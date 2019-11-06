#ifndef ULTRASONIC_H
#define ULTRASONIC_H

class UltrasonicRanger {
  public:
    UltrasonicRanger(const int trig_pin,
                     const int echo_pin); 
    ~UltrasonicRanger();
    void init();
    unsigned long getDistance();

  private:
    struct TaskParameters { const int trig_pin; const int echo_pin; } Params;
    static void pulseOut();
    static unsigned long _duration;
    Taskhandle_t pulse_Task;
    SemaphoreHandle_t duration_Mutex = NULL;
};

#endif