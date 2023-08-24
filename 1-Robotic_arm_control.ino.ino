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

String INDICATOR = "00", DIRECTION = "00";

unsigned int min_voltage = 0, max_voltage = 250;

unsigned int motor_current_state = 0; 

double cruisevalue1 = 0.00; 
double cruisevalue2 = 0.00;
double cruisevalue3 = 0.00;
double cruisevalue4 = 0.00;
double cruisevalue5 = 0.00;
double cruisechange = 125.0;

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



void m1motor()
  {
    if( DIRECTION == "MF")
    {
      Serial.println("1=");
      if(motor_current_state == 0)  // ideal state
      {
        //Serial.println("M1 in ideal state to forward");
        motor_current_state = 1;    // forward state
        forwardRelay( motor1_IN1,motor1_IN2);

        if(cruisevalue1 < max_voltage)
          cruisevalue1 = cruisevalue1 + cruisechange;
      }
      else if(motor_current_state == 2 ||  motor_current_state == 1 ) // backward state
      {
       // Serial.println("M1 backward to forward");
        if(cruisevalue1 >= min_voltage && motor_current_state == 2)
        {
          if(cruisevalue1 == min_voltage && motor_current_state == 2 )
          {
              motor_current_state = 1;
              forwardRelay(motor1_IN1,motor1_IN2);
          }
          else if(cruisevalue1 > min_voltage)
                cruisevalue1 = cruisevalue1 - cruisechange;
        }
        else if(cruisevalue1 < max_voltage)
                cruisevalue1 = cruisevalue1 + cruisechange;
      }
      else     // already in forward loop
      {
       // Serial.println("M1 in forward state to forward");
        motor_current_state = 1;
        if(cruisevalue1 < max_voltage)
          cruisevalue1 = cruisevalue1 + cruisechange;
      }

    }
    else if( DIRECTION == "MB")
    {
      Serial.println("A=");
      //Serial.println("MB of M1");
      if(motor_current_state == 0)  // ideal state
      {
        //Serial.println("M1 in ideal state to backward");
        motor_current_state = 2;    // backward
        backwardRelay(motor1_IN1, motor1_IN2);
        
        if(cruisevalue1 < max_voltage)
          cruisevalue1 = cruisevalue1 + cruisechange;
      }

      else if (motor_current_state == 1 || motor_current_state == 2 ) 
      { 
      //  Serial.println("M1 in forward state to backward");
        if(cruisevalue1 >= min_voltage && motor_current_state == 1 )  
        {    
          if(cruisevalue1 == min_voltage && motor_current_state == 1 )
          {
            backwardRelay(motor1_IN1,motor1_IN2);
            motor_current_state = 2;
            //cruisevalue = cruisevalue + cruisechange;
          }
          else if(cruisevalue1 > min_voltage)
                cruisevalue1 = cruisevalue1 - cruisechange;
        }
        else if(cruisevalue1 < max_voltage)
           cruisevalue1 = cruisevalue1 + cruisechange;
        
      }
      else
      {
        //Serial.println("M1 in backward state to backward");
        motor_current_state = 2; 
        if(cruisevalue1 < max_voltage)
          cruisevalue1 = cruisevalue1 + cruisechange;
      }
    }
    else if(DIRECTION == "MO")
    {
      Serial.println("a=");
      //Serial.println("MO of M1");
      if (motor_current_state == 1 || motor_current_state == 2) 
      {
       // Serial.println("M1 in forward/backward to off state");
        if(cruisevalue1 >= min_voltage)
          cruisevalue1 = cruisevalue1 - cruisechange;
      }
      if(cruisevalue1 == min_voltage )
      { 
      //  Serial.println("M1 off continue in off state");
        offRelay(motor1_IN1,motor1_IN2);
        motor_current_state = 0;
      }
    }
    //analogWrite(motor1_PWM, cruisevalue1);
    // Serial.println("cruise value gives to m1");
   // Serial.print("cruisechange = ");
   // Serial.println(cruisechange);
     
    Serial.print("1=");
    Serial.println(cruisevalue1);
    
  }


  void m2motor()
  {
    if( DIRECTION == "MF")
    {
      Serial.println("2=");
      //Serial.println("MF of M2");
      if(motor_current_state == 0)  // ideal state
      {
        //Serial.println("M2 ideal state to forward");
        motor_current_state = 1;    // forward state
        forwardRelay(motor2_IN1,motor2_IN2);
        
        if(cruisevalue2 < max_voltage)
          cruisevalue2 = cruisevalue2 + cruisechange;
          
      }
      else if(motor_current_state == 2 || motor_current_state == 1 ) // backward state
      {
       // Serial.println("M2 backward to forward");
        if(cruisevalue2 >= min_voltage && motor_current_state == 2)
        {
          if(cruisevalue2 == min_voltage && motor_current_state == 2)
          {
              motor_current_state = 1;
              forwardRelay(motor2_IN1,motor2_IN2);
          }
          else if(cruisevalue2 > min_voltage)
                cruisevalue2 = cruisevalue2 - cruisechange;
        }
        else if(cruisevalue2 < max_voltage)
                cruisevalue2 = cruisevalue2 + cruisechange;
      }
      else     // already in forward loop
      {
       // Serial.println("M2 forward to forward");
        motor_current_state = 1;
        if(cruisevalue2 < max_voltage)
          cruisevalue2 = cruisevalue2 + cruisechange;
      }
    }
    else if( DIRECTION == "MB")
    {
      Serial.println("B=");
      //Serial.println("MB of M2");
      if(motor_current_state == 0)  // ideal state
      {
       // Serial.println("M2 ideal state to backward");
        motor_current_state = 2;    // backward
        backwardRelay(motor2_IN1,motor2_IN2);
        
        if(cruisevalue2 < max_voltage)
          cruisevalue2 = cruisevalue2 + cruisechange;
      }
      else if (motor_current_state == 1 || motor_current_state == 2 ) 
      { 
       // Serial.println("M2 forward state backward");
        if(cruisevalue2 >= min_voltage && motor_current_state == 1)
        {
          if(cruisevalue2 == min_voltage  && motor_current_state == 1)
          {
            motor_current_state = 2;
            backwardRelay(motor2_IN1,motor2_IN2);
          }
          else if(cruisevalue2 > min_voltage)
                cruisevalue2 = cruisevalue2 - cruisechange;
        }
        else if(cruisevalue2 < max_voltage)
                cruisevalue2 = cruisevalue2 + cruisechange;
      }
      else
      {
       // Serial.println("M2 backward to backward");
        motor_current_state = 2; 
        if(cruisevalue2 < max_voltage)
          cruisevalue2 = cruisevalue2 + cruisechange;
      }
    }
    else if(DIRECTION == "MO")
    {
      Serial.println("b=");
      //Serial.println("MO of M2"); 
      if (motor_current_state == 1 || motor_current_state == 2) 
      {
      //  Serial.println("M2 forward/backward to off state");
        if(cruisevalue2 > min_voltage)
        cruisevalue2 = cruisevalue2 - cruisechange;
      }
      if(cruisevalue2 == min_voltage )
      {
       // Serial.println("M2 off to off state");
        offRelay(motor2_IN1,motor2_IN2);
        motor_current_state = 0;
      }
    }
    //analogWrite(motor2_PWM, cruisevalue2);
    //Serial.print("cruisechange = ");
    //Serial.println(cruisechange);
    Serial.print("2=");
    Serial.println(cruisevalue2);

  }
  void m3motor()//----------------------------------------------------------M3
  {
    if( DIRECTION == "MF")
    {
      Serial.println("3-");
      if(motor_current_state == 0)  // ideal state
      {
        //Serial.println("M3 ideal to forward");
        motor_current_state = 1;    // forward state
        forwardRelay( motor3_IN1,motor3_IN2);

        if(cruisevalue3 < max_voltage)
          cruisevalue3 = cruisevalue3 + cruisechange;
          
      }
      else if(motor_current_state == 2 ||  motor_current_state == 1) // backward state
      {
       // Serial.println("M3 backward to forward");
        if(cruisevalue3 >= min_voltage && motor_current_state == 2)
        {
          if(cruisevalue3 == min_voltage && motor_current_state == 2 )
          {
              motor_current_state = 1;
              forwardRelay(motor3_IN1,motor3_IN2);
          }
          else if(cruisevalue3 > min_voltage)
                cruisevalue3 = cruisevalue3 - cruisechange;
        }
        else if(cruisevalue3 < max_voltage)
                cruisevalue3 = cruisevalue3 + cruisechange;
      }
      else     // already in forward loop
      {
       // Serial.println("M3 forward to forward");
        motor_current_state = 1;
        if(cruisevalue3 < max_voltage)
          cruisevalue3 = cruisevalue3 + cruisechange;
      }
    }
    else if( DIRECTION == "MB")
    {
      Serial.println("C-");
      //Serial.println("MB of M3");
      if(motor_current_state == 0)  // ideal state
      {
        //Serial.println("M3 ideal to backward");
        motor_current_state = 2;    // backward
        backwardRelay(motor3_IN1,motor3_IN2);
        
        if(cruisevalue3 < max_voltage)
          cruisevalue3 = cruisevalue3 + cruisechange;
      }
      else if (motor_current_state == 1 || motor_current_state == 2 ) 
      { 
      //  Serial.println("M3 forward to backward");
        if(cruisevalue3 >= min_voltage && motor_current_state == 1)
        {
          if(cruisevalue3 == min_voltage && motor_current_state == 1)
          {
            motor_current_state = 2;
            backwardRelay(motor3_IN1,motor3_IN2);
          }
          else if(cruisevalue3 > min_voltage)
                cruisevalue3 = cruisevalue3 - cruisechange;
        }
        else if(cruisevalue3 < max_voltage)
                cruisevalue3 = cruisevalue3 + cruisechange;
      }
      else
      {
      //  Serial.println("M3 backward to backward");
        motor_current_state = 2; 
        if(cruisevalue3 < max_voltage)
          cruisevalue3 = cruisevalue3 + cruisechange;
      }
    }
    else if(DIRECTION == "MO")
    {
        Serial.println("c-");
        //Serial.println("MO of M3");
        if (motor_current_state == 1 || motor_current_state == 2) 
        {
         // Serial.println("M3 forward/backward to off state");
          if(cruisevalue3 > min_voltage)
            cruisevalue3 = cruisevalue3 - cruisechange;
        }
        if(cruisevalue3 == min_voltage )
        {
         // Serial.println("M3 off to off state");
          offRelay(motor3_IN1,motor3_IN2); 
          motor_current_state = 0;
        }
    }
    //analogWrite(motor3_PWM, cruisevalue3);
   // Serial.print("cruisechange = ");
    //Serial.println(cruisechange);
     Serial.print("3=");
    Serial.println(cruisevalue3);
  }
  void m4motor() //--------------------------------------------------------M4
  {
    if( DIRECTION == "MF")
    {
       Serial.println("4-");
      // Serial.println("MF of M4");
      if(motor_current_state == 0)  // ideal state
      {
       // Serial.println("M4 ideal to forward");
        motor_current_state = 1;    // forward state
        forwardRelay(motor4_IN1,motor4_IN2);
        
        if(cruisevalue4 < max_voltage)
          cruisevalue4 = cruisevalue4 + cruisechange;
          
      }
      else if(motor_current_state == 2 || motor_current_state == 1) // backward state
      {
      //  Serial.println("M4 backward to forward");
        if(cruisevalue4 >= min_voltage && motor_current_state == 2)
        {
          if(cruisevalue4 == min_voltage && motor_current_state == 2)
          {
              motor_current_state = 1;
              forwardRelay(motor4_IN1,motor4_IN2);
          }
          else if(cruisevalue4 > min_voltage)
                cruisevalue4 = cruisevalue4 - cruisechange;
        }
        else if(cruisevalue4 < max_voltage)
                cruisevalue4 = cruisevalue4 + cruisechange;
      }
      else     // already in forward loop
      {
      //  Serial.println("M4 forward to forward");
        motor_current_state = 1;
        if(cruisevalue4 < max_voltage)
          cruisevalue4 = cruisevalue4 + cruisechange;
      }
    }
    else if( DIRECTION == "MB")
    {
      Serial.println("D-");
      //Serial.println("MB of M4");
      if(motor_current_state == 0)  // ideal state
      {
       // Serial.println("M4 ideal to backward");
        motor_current_state = 2;    // backward
        backwardRelay(motor4_IN1,motor4_IN2);
        
        if(cruisevalue4 < max_voltage)
          cruisevalue4 = cruisevalue4 + cruisechange;
      }
      else if (motor_current_state == 1 ||  motor_current_state == 2) 
      { 
      //  Serial.println("M4 forward to backward");
        if(cruisevalue4 >= min_voltage && motor_current_state == 1)
        {
          if(cruisevalue4 == min_voltage && motor_current_state == 1)
          {
            motor_current_state = 2;
            backwardRelay(motor4_IN1,motor4_IN2);
          }
          else if(cruisevalue4 > min_voltage)
                cruisevalue4 = cruisevalue4 - cruisechange;
        }
        else if(cruisevalue4 < max_voltage)
                cruisevalue4 = cruisevalue4 + cruisechange;
      }
      else
      {
      //  Serial.println("M4 backward to backward");
        motor_current_state = 2; 
        if(cruisevalue4 < max_voltage)
          cruisevalue4 = cruisevalue4 + cruisechange;
      }
      
    }
    else if(DIRECTION == "MO")
    {
        Serial.println("d-");
        //Serial.println("MO of M4");
        if (motor_current_state == 1 || motor_current_state == 2) 
        {
        //  Serial.println("M4 for/backward to off state");
          if(cruisevalue4 > min_voltage)
            cruisevalue4 = cruisevalue4 - cruisechange;
        }
        if(cruisevalue4 == min_voltage )
        {
        //  Serial.println(" M4 off to off state");
          offRelay(motor4_IN1,motor4_IN2);
          motor_current_state = 0;
        }
    }
    //analogWrite(motor4_PWM, cruisevalue4);
    //Serial.print("cruisechange = ");
    //Serial.println(cruisechange);
     Serial.print("4=");
    Serial.println(cruisevalue4);
  }
  void m5motor()//------------------------------------------------------------M5
  {
    if( DIRECTION == "MF")
    {
      Serial.println("5-");
      //Serial.println("MF of M5");
      if(motor_current_state == 0)  // ideal state
      {
      //  Serial.println("M5 ideal to forward");
        motor_current_state = 1;    // forward state
        forwardRelay( motor5_IN1,motor5_IN2);

        if(cruisevalue5 < max_voltage)
          cruisevalue5 = cruisevalue5 + cruisechange;
          
      }
      else if(motor_current_state == 2 || motor_current_state == 1 ) // backward state
      {
      //  Serial.println("M5 backward to forward");
        if(cruisevalue5 >= min_voltage && motor_current_state == 2)
        {
          if(cruisevalue5 == min_voltage && motor_current_state == 2)
          {
              motor_current_state = 1;
              forwardRelay(motor5_IN1,motor5_IN2);
          }
          else if(cruisevalue5 > min_voltage)
                cruisevalue5 = cruisevalue5 - cruisechange;
        }
        else if(cruisevalue5 < max_voltage)
                cruisevalue5 = cruisevalue5 + cruisechange;
      }
      else     // already in forward loop
      {
      //  Serial.println("M5 forward to forward");
        motor_current_state = 1;
        if(cruisevalue5 < max_voltage)
          cruisevalue5 = cruisevalue5 + cruisechange;
      }
       
        //  Serial.println("M5 forward/backward to off state");
     //if(cruisevalue5 > min_voltage)
      //  cruisevalue5 = cruisevalue5 - cruisechange;
        
    }
    else if( DIRECTION == "MB")
    {
      Serial.println("E-");
      //Serial.println("MB of M5");
      if(motor_current_state == 0)  // ideal state
      {
     //   Serial.println("M5 ideal to backward");
        motor_current_state = 2;    // backward
        backwardRelay(motor5_IN1,motor5_IN2);
        
        if(cruisevalue5 < max_voltage)
          cruisevalue5 = cruisevalue5 + cruisechange;
      }
      else if (motor_current_state == 1 || motor_current_state == 2 ) 
      { 
     //   Serial.println("M5 forward to backward");
        if(cruisevalue5 >= min_voltage && motor_current_state == 1)
        {
          if(cruisevalue5 == min_voltage && motor_current_state == 1)
          {
            motor_current_state = 2;
            backwardRelay(motor5_IN1,motor5_IN2 );
          }
          else if(cruisevalue5 > min_voltage)
                cruisevalue5 = cruisevalue5 - cruisechange;
        }
        else if(cruisevalue5 < max_voltage)
                cruisevalue5 = cruisevalue5 + cruisechange;
      }
      else
      {
     //   Serial.println("M5 backward to backward");
        motor_current_state = 2; 
        if(cruisevalue5 < max_voltage)
          cruisevalue5 = cruisevalue5 + cruisechange;
      }
     
        //  Serial.println("M5 forward/backward to off state");
          
          
   // if(cruisevalue5 > min_voltage)
     // cruisevalue5 = cruisevalue5 - cruisechange;
      
    }
    else if(DIRECTION == "MO")
    {
        Serial.println("e-");
        //Serial.println("MO of M5");
        if (motor_current_state == 1 || motor_current_state == 2) 
        {
        //  Serial.println("M5 forward/backward to off state");
          if(cruisevalue5 > min_voltage)
            cruisevalue5 = cruisevalue5 - cruisechange;
        }
        if(cruisevalue5 == min_voltage )
        { 
        //  Serial.println("M5 off to off state");
          offRelay(motor5_IN1,motor5_IN2);
          motor_current_state = 0;
        }
    } 
   // analogWrite(motor5_PWM, cruisevalue5);
   // Serial.print("cruisechange = ");
   // Serial.println(cruisechange);
    Serial.print("5=");
    Serial.println(cruisevalue5);
  }

  void led_toggle()
  {
    //Serial.println("IND = LED");
   // Serial.println("LED select");
    if(led_state == 0)
    {
    //  Serial.println("LED off to on");
      digitalWrite(LED1, HIGH);
      led_state = 1;
      //delay(2000);
    }
    else if(led_state == 1)
    {  
    //  Serial.println("LED on to off");
      led_state = 0;                        
      digitalWrite(LED1, LOW);
      //delay(2000);
    }
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
    switch(data)
    {
      case '1':
        INDICATOR = "M1";
        DIRECTION = "MF";
        break;
      case 'A':
        INDICATOR = "M1";
        DIRECTION = "MB";
        break;
      case 'a':
        INDICATOR = "M1";
        DIRECTION = "MO";
        break;
      case '2':
        INDICATOR = "M2";
        DIRECTION = "MF";
        break;
      case 'B':
        INDICATOR = "M2";
        DIRECTION = "MB";
        break;
      case 'b':
        INDICATOR = "M2";
        DIRECTION = "MO";
        break;
      case '3':
        INDICATOR = "M3";
        DIRECTION = "MF";
        break;
      case 'C':
        INDICATOR = "M3";
        DIRECTION = "MB";
        break;
      case 'c':
        INDICATOR = "M3";
        DIRECTION = "MO";
        break;
      case '4':
        INDICATOR = "M4";
        DIRECTION = "MF";
        break;
      case 'D':
        INDICATOR = "M4";
        DIRECTION = "MB";
        break;
      case 'd':
        INDICATOR = "M4";
        DIRECTION = "MO";
        break;
      case '5':
        INDICATOR = "M5";
        DIRECTION = "MF";
        break;
      case 'E':
        INDICATOR = "M5";
        DIRECTION = "MB";
        break;
      case 'e':
        INDICATOR = "M5";
        DIRECTION = "MO";
        break;
      case 'L':
        INDICATOR = "L";
        break;
      
    }
    Serial.print(data);
  }
  


  if(INDICATOR == "M1") 
  {
    m1motor();
  }

   if(INDICATOR == "M2") 
  {
    m2motor();
  }

   if(INDICATOR == "M3")
  {
    m3motor();
  }

   if(INDICATOR == "M4") 
  {
    m4motor();
  }

   if(INDICATOR == "M5") 
  {
    m5motor();
  }
  
  if(INDICATOR == "L")
  {
    led_toggle();
  }
  analogWrite(motor1_PWM,cruisevalue1);
  analogWrite(motor2_PWM,cruisevalue2);
  analogWrite(motor3_PWM,cruisevalue3);
  analogWrite(motor4_PWM,cruisevalue4);
  analogWrite(motor5_PWM,cruisevalue5);
}




  /*else if(INDICATOR == "L")
  {
   // ledState = !ledState; // Toggle LED state
    digitalWrite(LED1, HIGH); 
    if(Serial.available() == 0 || INDICATOR != "L")
    {
      digitalWrite(LED1, LOW); 
    }
  }    */
   

  