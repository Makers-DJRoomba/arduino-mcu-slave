#ifndef ENCODER_H
#define ENCODER_H

/* Rotary Encoders */
class Encoder {
  public:
    Encoder(const int pin);
    ~Encoder(); 
    int getValue();

  private:
    static void increment();
    static int _ticks = 0;
    static TaskHandle_t increment_Task;
    SemaphoreHandle_t tick_Semaphore = NULL;
};

#endif