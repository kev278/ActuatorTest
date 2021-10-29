// Set motor pins
int motor1pin1 = 6;
int motor1pin2 = 7;

int motor2pin1 = 4;
int motor2pin2 = 5;

volatile int count = 0;//if the interrupt will change this value, it must be volatile

void setup() {
// Initialize motor pins as output pins
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(motor2pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT);

// Setup for Interrupt
  pinMode(2, INPUT); //set as input
  digitalWrite(2, HIGH);//enable internal pullup resistor
  attachInterrupt(digitalPinToInterrupt(2), interruptName, RISING);//Interrupt initialization

  Serial.begin(9600);
  
}

void loop() {

// Turn on the Motors
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, HIGH);

  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, HIGH);

  Serial.println(count);//see the counts advance
  delay(100);//Delays usually can't be interfered with, here we will see the interrupt work


  if (count > 20) //Set the number for a  particular position. We have very fine control upto 5 degrees
  {
  // Stops the motor as the desired position  
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, LOW);

  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, LOW);
  delay(5000);
    }
}

void interruptName()
{
  count = count+1;
}//end Interrupt Service Routine (ISR)
