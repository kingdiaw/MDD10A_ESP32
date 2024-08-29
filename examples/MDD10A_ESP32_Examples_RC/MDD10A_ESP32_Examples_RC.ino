#include <MDD10A_Motor_Driver.h>

#define PWM1 25
#define DIR1 26
#define PWM2 27
#define DIR2 14
#define CH1 12  // putih
#define CH2 2   //kuning

#define Y_MIN 1033  // ch1
#define Y_MAX 2018
#define X_MIN 982  //ch2
#define X_MAX 1993

MotorDriver m1(PWM1, DIR1);
MotorDriver m2(PWM2, DIR2);

//Global Variable
int strength;
int angle;
int y;
int x;

void setup() {
  // put your setup code here, to run once:
  byte arr_pin_input[] = { CH1, CH2 };
  Serial.begin(115200);
  for (byte i = 0; i < sizeof(arr_pin_input); i++) pinMode(arr_pin_input[i], INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  x = pulseIn(CH1, HIGH, 25000);
  y = pulseIn(CH2, HIGH, 25000);  //angle
  strength = map(y, Y_MAX, Y_MIN, -100, 100);
  angle = map(x, X_MIN, X_MAX, 0, 180);

  if (strength > 100) strength = 100;
  if (strength < -100) strength = -100;

  if(angle > 180) angle = 180;
  if(angle < 0) angle = 0;

  Serial.print("Strength:");
  Serial.println(strength);
  Serial.print("angle:");
  Serial.println(angle);


  if (strength > 5) {  //forward 5
    if (angle >= 90)  //turn right >90
    {
      robot(1, 1, (strength * ((180 - angle) * 255 / 90) / 100), (strength * 255 / 100));
    } else if (angle < 90)  //turn left <90 1,1,
    {
      robot(1, 1, (strength * 255 / 100), (strength * (angle * 255 / 90)) / 100);//1,1
    }
  } else if (strength < -5) {//-5
    if (angle >= 90)  //turn right >90
    {
      robot(0, 0, (abs(strength) * 255 / 100), (abs(strength) * ((180 - angle) * 255 / 90) / 100));
      
    } else if (angle < 90)  //turn left <90 0,0 
    {
      robot(0, 0, (abs(strength) * (angle * 255 / 90)) / 100, (abs(strength) * 255 / 100));//0,0
    }
  } 
  else if(angle > 95){
    robot (0,1,128,128);
  }
  else if (angle < 85){
    robot (1,0,128,128);
  }
  else if (angle < 95 && angle > 85){
    robot(1, 1, 0, 0);//1100
  }

}

void robot(int m1_dir, int m2_dir, int speed_m1, int speed_m2) {
  m1.setSpeed(m1_dir>0? speed_m1:-speed_m1);
  m2.setSpeed(m2_dir>0? speed_m2:-speed_m2);
}
