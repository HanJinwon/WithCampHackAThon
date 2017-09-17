#include <SoftwareSerial.h>
#include <AFMotor.h>
AF_DCMotor motor1(1); //오른쪽 모터             // 1: M1에 연결,  2: M2에 연결
AF_DCMotor motor2(2); //왼쪽 모터

#define BlueTx 0   //Tx (보내는핀 설정)
#define BlueRx 1   //Rx (받는핀 설정)
#define TriggerPin 8
#define EchoPin 9
long Duration = 0;
int cnt = 0;
bool FinishFlag = false;
SoftwareSerial btSerial(BlueTx, BlueRx);

byte buffer[1024]; // 데이터를 수신 받을 버퍼
int bufferPosition;

void setup()
{
  pinMode(TriggerPin, OUTPUT); // Trigger is an output pin
  pinMode(EchoPin, INPUT); // Echo is an input pin
  Serial.begin(9600); // Serial Output
  btSerial.begin(9600); //블루투스 시리얼
  bufferPosition = 0; 
}

void loop()
{
  /*digitalWrite(TriggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(TriggerPin, HIGH); // Trigger pin to HIGH
  delayMicroseconds(10); // 10us high
  digitalWrite(TriggerPin, LOW); // Trigger pin to HIGH
  Duration = pulseIn(EchoPin, HIGH); // Waits for the echo pin to get high
  // returns the Duration in microseconds

  long Distance_mm = Distance(Duration); // Use function to calculate the distance
  */
   if (btSerial.available()>0)
   {
      byte command = btSerial.read();
      //Serial.write(command);
      //buffer[bufferPosition++] = command;
      //Stop();
      switch (command)
      {
      case '2':
         forward_left();
         //Serial.println("Forward Left");
         break;
      case '1':
         forward();
         //Serial.println("Forward");
         break;
      case '8':
         forward_right();
         //Serial.println("Forward right");
         break;
      case '3':
         left();
         //Serial.println("Left");
         break;
      case '0':
         Stop();
         //Serial.println("Stop");
         break;
      case '7':
         right();
         //Serial.println("Right");
         break;
      case '4':
         back_left();
         //Serial.println("Back Left");
         break;
      case '5':
         back();
         //Serial.println("Back");
         break;
      case '6':
         back_right();
         //Serial.println("Back Right");
         break;
      }
      if(command == '\n'){ // 문자열 종료 표시
      buffer[bufferPosition] = '\0';
      bufferPosition = 0;
      }
  }
}


void forward()
{
   motor1.setSpeed(255); //Define maximum velocity
   motor1.run(FORWARD); //rotate the motor clockwise
   motor2.setSpeed(255); //Define maximum velocity
   motor2.run(FORWARD); //rotate the motor clockwise
}

void forward_left()
{
   motor1.setSpeed(255); //Define maximum velocity
   motor1.run(FORWARD); //rotate the motor clockwise
   motor2.setSpeed(122); //Define maximum velocity
   motor2.run(FORWARD); //rotate the motor clockwise
}

void forward_right()
{
   motor1.setSpeed(122); //Define maximum velocity
   motor1.run(FORWARD); //rotate the motor clockwise
   motor2.setSpeed(255); //Define maximum velocity
   motor2.run(FORWARD); //rotate the motor clockwise

}

void left()
{
   motor1.setSpeed(255); //Define maximum velocity
   motor1.run(FORWARD); //rotate the motor clockwise
   motor2.setSpeed(0);
   motor2.run(RELEASE); //turn motor2 off
}

void right()
{
   motor1.setSpeed(0);
   motor1.run(RELEASE); //turn motor1 off
   motor2.setSpeed(255); //Define maximum velocity
   motor2.run(FORWARD); //rotate the motor clockwise
}

void back()
{
   motor1.setSpeed(255);
   motor1.run(BACKWARD); //rotate the motor counterclockwise
   motor2.setSpeed(255);
   motor2.run(BACKWARD); //rotate the motor counterclockwise
}

void back_left()
{
   motor1.setSpeed(255);
   motor1.run(BACKWARD); //rotate the motor counterclockwise
   motor2.setSpeed(122);
   motor2.run(BACKWARD); //rotate the motor counterclockwise
}

void back_right()
{
   motor1.setSpeed(122);
   motor1.run(BACKWARD); //rotate the motor counterclockwise
   motor2.setSpeed(255);
   motor2.run(BACKWARD); //rotate the motor counterclockwise
}

void Stop()
{
   motor1.setSpeed(0);
   motor2.run(RELEASE); //turn motor1 off
   motor2.setSpeed(0);
   motor2.run(RELEASE); //turn motor2 off
}

long Distance(long time)
{
  // Calculates the Distance in mm
  // ((time)*(Speed of sound))/ toward and backward of object) * 10

  long DistanceCalc; // Calculation variable
  DistanceCalc = ((time / 2.9) / 2); // Actual calculation in mm
  //DistanceCalc = time / 74 / 2; // Actual calculation in inches
  return DistanceCalc; // return calculated value
}
