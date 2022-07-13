// Set motor1 pins
int motor1pin1 = 5;
int motor1pin2 = 6;

// Set motor1 pins
int motor2pin1 = 9;
int motor2pin2 = 10;

// Set enable pins
int ena = 3;
int enb = 11;

//Set interrupt pins for encoder
volatile int count1 = 0;//if the interrupt will change this value, it must be volatile0
volatile int count2 = 0;

class clutch
{
  public:
  void engage()
  {
      digitalWrite(motor1pin1, HIGH);
      digitalWrite(motor1pin2, LOW); 
      delay(200); //Change the delay values based on the PWM set
      digitalWrite(motor1pin1, LOW);
      digitalWrite(motor1pin2, LOW);
      delay(20);
    }

  void disengage()
  {
      digitalWrite(motor1pin1, LOW);
      digitalWrite(motor1pin2, HIGH); 
      delay(200); //Change the delay values based on the PWM set
      digitalWrite(motor1pin1, LOW);
      digitalWrite(motor1pin2, LOW);
      delay(20);
    }
  };
class MotorTest
/*
 * This class is to test the motors and the directions in which they rotate
 * Use this before enganging the clutch
 */

  
{
  public:
  
  void stopMotor(int a)
  {
      //If a = 1, we stop motor 1, if a = 2, we stop motor 2
      if (a == 1)
      {
      digitalWrite(motor1pin1, LOW);
      digitalWrite(motor1pin2, LOW);
      delay(100);
 
      }
      else if (a == 2)
      {
      digitalWrite(motor2pin1, LOW);
      digitalWrite(motor2pin2, LOW);
      delay(100);
        }
    }

  void startMotor(char c, int a)
  {
      //If a = 1, we start motor 1, if a = 2, we start motor 2
      // char c decides the rotation direction, A is anticlockwise and C is clockwise
      if (c == 'C')
      {
        if (a == 1)
        {
        digitalWrite(motor1pin1, HIGH);
        digitalWrite(motor1pin2, LOW); 
        }
        else if (a == 2)
        {
        digitalWrite(motor2pin1, HIGH);
        digitalWrite(motor2pin2, LOW);
          }
      }
      if (c == 'A')
      {
        if (a == 1)
          {
          digitalWrite(motor1pin1, LOW);
          digitalWrite(motor1pin2, HIGH); 
          }
      else if (a == 2)
          {
          digitalWrite(motor2pin1, LOW);
          digitalWrite(motor2pin2, HIGH);
            }
      }
    }
  
  };


void setup() {
// Initialize motor pins as output pins
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(motor2pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT);
  pinMode(ena, OUTPUT);
  pinMode(enb, OUTPUT);

// Setup for Interrupt
  pinMode(2, INPUT); //set as input
  digitalWrite(2, HIGH);//enable internal pullup resistor
  attachInterrupt(digitalPinToInterrupt(2), interruptName1, RISING);//Interrupt initialization

  pinMode(3, INPUT); //set as input
  digitalWrite(3, HIGH);//enable internal pullup resistor
  attachInterrupt(digitalPinToInterrupt(3), interruptName2, RISING);//Interrupt initialization

  Serial.begin(9600);
  
}

void loop() {

  /*
   * Before turning on the motors, please check the pin connections
   * Check motor connections to confirm clockwise amd anticlockwose direction
   * 
   */

  //Set PWM speed
  analogWrite(ena, 70);
  analogWrite(enb, 73);
  delay(20);

  MotorTest Motor1, Motor2;
  String command;
  char C, A;
  // Giving commands from Serial Monitor
  if(Serial.available()){
        command = Serial.readStringUntil('\n');
         
        if(command.equals("Stop Motor 1")){
             Motor1.stopMotor(1);   
        }
        else if(command.equals("Stop Motor 2")){
            Motor2.stopMotor(2);
        }
        else if(command.equals("Start Motor 1 Clockwise")){
            Motor1.startMotor(C,1);
        }
        else if(command.equals("Start Motor 2 Clockwise")){
            Motor1.startMotor(C,2);
        }

        else if(command.equals("Start Motor 1 Anticlockwise")){
            Motor1.startMotor(A,1);
        }
        else if(command.equals("Start Motor 2 Anticlockwise")){
            Motor1.startMotor(A,2);
        }

        else if(command.equals("Engage")){
            Motor1.startMotor(A,2);
        }

        else if(command.equals("Disengage")){
            Motor1.startMotor(A,2);
        }
        
        else{
            Serial.println("Invalid command");
        }
    }
  

  /*
   * To print counts
  Serial.println(count1);//see the counts advance
  Serial.print(" ");
  Serial.print(count2);
  delay(100);//Delays usually can't be interfered with, here we will see the interrupt work
  */
  
  if (count1 > 1000) //Set the number for a  particular position
  {
  // Stops the motor at the desired position  
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, LOW);

  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, LOW);
  delay(20);
    }
 
}
void interruptName1()
{
  count1 = count1+1;
}//end Interrupt Service Routine (ISR)

void interruptName2()
{
  count2 = count2+1;
}
