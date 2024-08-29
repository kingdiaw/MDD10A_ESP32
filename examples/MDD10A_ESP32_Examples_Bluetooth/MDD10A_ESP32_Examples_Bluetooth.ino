#include <MDD10A_Motor_Driver.h>
#include "BluetoothSerial.h"

#define PWM1 25
#define DIR1 26
#define PWM2 27
#define DIR2 14

//Step 1: Rename Your BT name
String device_name = "ESP32-BT-Slave";

// Check if Bluetooth is available
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

// Check Serial Port Profile
#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Port Profile for Bluetooth is not available or not enabled. It is only available for the ESP32 chip.
#endif

MotorDriver m1(PWM1, DIR1);
MotorDriver m2(PWM2, DIR2);
BluetoothSerial SerialBT;

//Global Variable
char data;

void setup() {
  // put your setup code here, to run once:
  byte arr_pin_input[] = {};
  Serial.begin(115200);
  SerialBT.begin(device_name);  //Bluetooth device name
  Serial.printf("The device with name \"%s\" is started.\nNow you can pair it with Bluetooth!\n", device_name.c_str());
  for (byte i = 0; i < sizeof(arr_pin_input); i++) pinMode(arr_pin_input[i], INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (SerialBT.available()) {
    data=SerialBT.read();
  }
  
  if(data == 'F')robot(1,1,128,128);
  else if(data == 'B')robot(0,0,128,128);
  else if(data == 'L')robot(0,1,128,128);
  else if(data == 'R')robot(1,0,128,128);
  else if(data == 'S')robot(0,0,0,0);
}

void robot(int m1_dir, int m2_dir, int speed_m1, int speed_m2) {
  m1.setSpeed(m1_dir > 0 ? speed_m1 : -speed_m1);
  m2.setSpeed(m2_dir > 0 ? speed_m2 : -speed_m2);
}
