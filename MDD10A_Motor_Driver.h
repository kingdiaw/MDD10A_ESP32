#ifndef MDD10A_MOTOR_DRIVER_H
#define MDD10A_MOTOR_DRIVER_H

#include <Arduino.h>
#include <stdint.h>

// Class definition
class MotorDriver {
private:
  int _pwm_pin;
  int _dir_pin;

public:
  // Constructor
  MotorDriver(int pwm_pin, int dir_pin);

  // Method to set the speed
  void setSpeed(int16_t speed); 
};

#endif
