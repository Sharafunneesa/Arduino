// for 5 motors rotates indipendendly

const int motor1_IN1 = 44;
const int motor1_IN2 = 45;
const int motor1_PWM = 6;

const int motor2_IN1 = 40;
const int motor2_IN2 = 41;
const int motor2_PWM = 7;

const int motor3_IN1 = 36;
const int motor3_IN2 = 37;
const int motor3_PWM = 4;

const int motor4_IN1 = 32;
const int motor4_IN2 = 33;
const int motor4_PWM = 5;

const int motor5_IN1 = 24;
const int motor5_IN2 = 25;
const int motor5_PWM = 2;

int LED1 = 48;
int LEDGND = 49;

char data;

bool led_state = false;

unsigned int min_voltage = 0, max_voltage = 250;

double cruisevalue1 = 0.00; 
double cruisevalue2 = 0.00;
double cruisevalue3 = 0.00;
double cruisevalue4 = 0.00;
double cruisevalue5 = 0.00;
double cruisechange = 1.0;

void forwardRelay(int pin1, int pin2)
{
  digitalWrite(pin1, HIGH);
  digitalWrite(pin2, LOW);
}

void backwardRelay(int pin1, int pin2)
{
  digitalWrite(pin1, LOW);
  digitalWrite(pin2, HIGH);
}

void offRelay(int pin1, int pin2)
{
  digitalWrite(pin1, LOW);
  digitalWrite(pin2, LOW);
}

unsigned int M1state = 0, M2state = 0, M3state = 0, M4state = 0, M5state = 0, LEDstate = 0;

void M1Forward()
{

  if(M1state == 2)
  { // Backward State

    if(cruisevalue1 >= min_voltage)
    {
      cruisevalue1 = cruisevalue1 - cruisechange;
    }
    else
    {
      M1state = 1; // Setting forward State
      forwardRelay( motor1_IN1,motor1_IN2);
    }

  }
  else // forward state
  {
    if(cruisevalue1 < max_voltage)
      cruisevalue1 = cruisevalue1 + cruisechange;
  } 
  /*analogWrite(motor1_PWM,cruisevalue1);
  Serial.print("cv1f=");
  Serial.println(cruisevalue1);*/
}

void M2Forward()
{

  if(M2state == 2)
  { // Backward State

    if(cruisevalue2 >= min_voltage)
    {
      cruisevalue2 = cruisevalue2 - cruisechange;
    }
    else
    {
      M2state = 1; // Setting forward State
      forwardRelay( motor2_IN1,motor2_IN2);
    }

  }
  else
  {
    if(cruisevalue2 < max_voltage)
      cruisevalue2 = cruisevalue2 + cruisechange;
  } 
 /* analogWrite(motor2_PWM,cruisevalue2);
   Serial.print("cv2f=");
  Serial.println(cruisevalue2);*/
}

void M3Forward()
{

  if(M3state == 2)
  { // Backward State

    if(cruisevalue3 >= min_voltage)
    {
      cruisevalue3 = cruisevalue3 - cruisechange;
    }
    else
    {
      M3state = 1; // Setting forward State
      forwardRelay( motor3_IN1,motor3_IN2);
    }

  }
  else
  {
    if(cruisevalue3 < max_voltage)
      cruisevalue3 = cruisevalue3 + cruisechange;
  } 
 /* analogWrite(motor3_PWM,cruisevalue3);
   Serial.print("cv3f=");
  Serial.println(cruisevalue3);*/
}

void M4Forward()
{

  if(M4state == 2)
  { // Backward State

    if(cruisevalue4 >= min_voltage)
    {
      cruisevalue4 = cruisevalue4 - cruisechange;
    }
    else
    {
      M4state = 1; // Setting forward State
      forwardRelay( motor4_IN1,motor4_IN2);
    }

  }
  else
  {
    if(cruisevalue4 < max_voltage)
      cruisevalue4 = cruisevalue4 + cruisechange;
  } 
 /* analogWrite(motor4_PWM,cruisevalue4);
   Serial.print("cv4f=");
  Serial.println(cruisevalue4);*/

}

void M5Forward()
{

  if(M5state == 2)
  { // Backward State

    if(cruisevalue5 >= min_voltage)
    {
      cruisevalue5 = cruisevalue5 - cruisechange;
    }
    else
    {
      M5state = 1; // Setting forward State
      forwardRelay( motor5_IN1,motor5_IN2);
    }

  }
  else
  {
    if(cruisevalue5 < max_voltage)
      cruisevalue5 = cruisevalue5 + cruisechange;
  } 
 /* analogWrite(motor5_PWM,cruisevalue5);
  Serial.print("cv5f=");
  Serial.println(cruisevalue5);*/
}

void M1Reverse()
{

  if(M1state == 1)
  { // Forward State

    if(cruisevalue1 >= min_voltage)
    {
      cruisevalue1 = cruisevalue1 - cruisechange;
    }
    else
    {
      M1state = 2; // Setting Reverse State
      backwardRelay( motor1_IN1,motor1_IN2);
    }

  }
  else
  {
    if(cruisevalue1 < max_voltage)
      cruisevalue1 = cruisevalue1 + cruisechange;
  } 
 /* analogWrite(motor1_PWM,cruisevalue1);
  Serial.print("cv1R=");
  Serial.println(cruisevalue1);*/
}

void M2Reverse()
{

  if(M2state == 1)
  { // Forward State

    if(cruisevalue2 >= min_voltage)
    {
      cruisevalue2 = cruisevalue2 - cruisechange;
    }
    else
    {
      M2state = 2; // Setting Reverse State
      backwardRelay( motor2_IN1,motor2_IN2);
    }

  }
  else
  {
    if(cruisevalue2 < max_voltage)
      cruisevalue2 = cruisevalue2 + cruisechange;
  } 
 /* analogWrite(motor2_PWM,cruisevalue2);
   Serial.print("cv2R=");
  Serial.println(cruisevalue2);*/
}

void M3Reverse()
{

  if(M3state == 1)
  { // Forward State

    if(cruisevalue3 >= min_voltage)
    {
      cruisevalue3 = cruisevalue3 - cruisechange;
    }
    else
    {
      M3state = 2; // Setting Reverse State
      backwardRelay( motor3_IN1,motor3_IN2);
    }

  }
  else
  {
    if(cruisevalue3 < max_voltage)
      cruisevalue3 = cruisevalue3 + cruisechange;
  } 
 /* analogWrite(motor3_PWM,cruisevalue3);
   Serial.print("cv3R=");
  Serial.println(cruisevalue3);*/
}

void M4Reverse()
{

  if(M4state == 1)
  { // Forward State

    if(cruisevalue4 >= min_voltage)
    {
      cruisevalue4 = cruisevalue4 - cruisechange;
    }
    else
    {
      M4state = 2; // Setting Reverse State
      backwardRelay( motor4_IN1,motor4_IN2);
    }

  }
  else
  {
    if(cruisevalue4 < max_voltage)
      cruisevalue4 = cruisevalue4 + cruisechange;
  } 
  analogWrite(motor4_PWM,cruisevalue4);
   Serial.print("cv4R=");
  Serial.println(cruisevalue4);
}

void M5Reverse()
{

  if(M5state == 1)
  { // Forward State

    if(cruisevalue5 >= min_voltage)
    {
      cruisevalue5 = cruisevalue5 - cruisechange;
    }
    else
    {
      M5state = 2; // Setting Reverse State
      backwardRelay( motor5_IN1,motor5_IN2);
    }

  }
  else
  {
    if(cruisevalue5 < max_voltage)
      cruisevalue5 = cruisevalue5 + cruisechange;
  } 
  analogWrite(motor5_PWM,cruisevalue5);
  Serial.print("cv5R=");
  Serial.println(cruisevalue5);
}

void M1Idel()
{

  if(cruisevalue1 >= min_voltage)
  {
      cruisevalue1 = cruisevalue1 - cruisechange;
  }
  analogWrite(motor1_PWM,cruisevalue1);
  Serial.print("cv1O=");
  Serial.println(cruisevalue1);
}

void M2Idel()
{

  if(cruisevalue2 >= min_voltage)
  {
      cruisevalue2 = cruisevalue2 - cruisechange;
  }
  analogWrite(motor2_PWM,cruisevalue2);
   Serial.print("cv2O=");
  Serial.println(cruisevalue2); 
}

void M3Idel()
{

  if(cruisevalue3 >= min_voltage)
  {
      cruisevalue3 = cruisevalue3 - cruisechange;
  }
  analogWrite(motor3_PWM,cruisevalue3); 
   Serial.print("cv3O=");
  Serial.println(cruisevalue3);
}

void M4Idel()
{

  if(cruisevalue4 >= min_voltage)
  {
      cruisevalue4 = cruisevalue4 - cruisechange;
  }
  analogWrite(motor4_PWM,cruisevalue4);
   Serial.print("cv4O=");
  Serial.println(cruisevalue4);
}

void M5Idel()
{

  if(cruisevalue5 >= min_voltage)
  {
      cruisevalue5 = cruisevalue5 - cruisechange;
  }
  analogWrite(motor5_PWM,cruisevalue5); 
  Serial.print("cv5O=");
  Serial.println(cruisevalue5);
}

void LEDtoggle()
{
  
  if(LEDstate == 0)
  {  // LED Off

    LEDstate = 1;
    digitalWrite(LED1, HIGH); 

  }
  else if(LEDstate == 1)
  {  //  LED on

    LEDstate = 0;
    digitalWrite(LED1, LOW); 
    
  }
  
}

void IdelAll()
{

  M1Idel();
  M2Idel();
  M3Idel();
  M4Idel();
  M5Idel();

}

void setup()
{

  Serial.begin(19200);

  pinMode(motor1_IN1, OUTPUT);
  pinMode(motor1_IN2, OUTPUT);
  pinMode(motor1_PWM, OUTPUT);

  pinMode(motor2_IN1, OUTPUT);
  pinMode(motor2_IN2, OUTPUT);
  pinMode(motor2_PWM, OUTPUT);

  pinMode(motor3_IN1, OUTPUT);
  pinMode(motor3_IN2, OUTPUT);
  pinMode(motor3_PWM, OUTPUT);
  
  pinMode(motor4_IN1, OUTPUT);
  pinMode(motor4_IN2, OUTPUT);
  pinMode(motor4_PWM, OUTPUT);

  pinMode(motor5_IN1, OUTPUT);
  pinMode(motor5_IN2, OUTPUT);
  pinMode(motor5_PWM, OUTPUT);

  pinMode(LED1, OUTPUT);
  pinMode(LEDGND, OUTPUT);

}


void loop()
{

  if(Serial.available() > 0)
  {
    data = Serial.read();
    Serial.println(data);
  }

  switch(data)
    {
      case '1':
        M1Forward();
        break;
      case 'A':
        M1Reverse();
        break;
      case 'a':
        M1Idel();
        break;
      case '2':
        M2Forward();
        break;
      case 'B':
        M2Reverse();
        break;
      case 'b':
        M2Idel();
        break;
      case '3':
        M3Forward();
        break;
      case 'C':
        M3Reverse();
        break;
      case 'c':
        M3Idel();
        break;
      case '4':
        M4Forward();
        break;
      case 'D':
        M4Reverse();
        break;
      case 'd':
        M4Idel();
        break;
      case '5':
        M5Forward();
        break;
      case 'E':
        M5Reverse();
        break;
      case 'e':
        M5Idel();
        break;
      case 'L':
        LEDtoggle();
        break;
      default:
        IdelAll();
        break;
    }

  analogWrite(motor1_PWM,cruisevalue1);
  analogWrite(motor2_PWM,cruisevalue2);
  analogWrite(motor3_PWM,cruisevalue3);
  analogWrite(motor4_PWM,cruisevalue4);
  analogWrite(motor5_PWM,cruisevalue5);
  Serial.print("cv1=");
  Serial.println(cruisevalue1);
   Serial.print("cv2=");
  Serial.println(cruisevalue2);
   Serial.print("cv3=");
  Serial.println(cruisevalue3);
   Serial.print("cv4=");
  Serial.println(cruisevalue4);
   Serial.print("cv5=");
  Serial.println(cruisevalue5);

  
}
  
