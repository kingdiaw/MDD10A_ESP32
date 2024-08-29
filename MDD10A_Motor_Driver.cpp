#include "MDD10A_Motor_Driver.h"

// Constructor implementation
MotorDriver::MotorDriver(int pwm_pin, int dir_pin) {
  _pwm_pin = pwm_pin;
  _dir_pin = dir_pin;
  pinMode(_pwm_pin, OUTPUT);
  pinMode(_dir_pin, OUTPUT);
  analogWrite(_pwm_pin, 0); // Initialize PWM to 0
}

// Method to set the speed implementation
void MotorDriver::setSpeed(int16_t speed) {
  if (speed > 0) {
    digitalWrite(_dir_pin, LOW);   // Forward direction
    analogWrite(_pwm_pin, speed);  // Set PWM speed
  } else {
    digitalWrite(_dir_pin, HIGH);  // Reverse direction
    analogWrite(_pwm_pin, -speed); // Set PWM speed
  }
}
