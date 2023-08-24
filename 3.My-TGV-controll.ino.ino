const int RIGHT_DIR = 4;
const int LEFT_DIR = 5;
const int RIGHT_PWM = 6;
const int LEFT_PWM = 7;

char data = 'I';
String INDICATOR = "00", DIRECTION = "01";
double leftCruise = 0.00, rightCruise = 0.00, leftChange, rightChange;
int max_voltage = 255;

bool firstforwardloop = true;
bool firstreverseloop = true;
bool firstidealloop = true;
bool forward_state = false;
bool reverse_state = false;
bool ideal_state = false; 

void rightForwardRelay()
{
  digitalWrite(RIGHT_DIR, HIGH);
}

void leftForwardRelay()
{
  digitalWrite(LEFT_DIR, HIGH);
}

void rightreverseRelay()
{
  digitalWrite(RIGHT_DIR,LOW);
}

void leftreverseRelay()
{
  digitalWrite(LEFT_DIR, LOW);
}

void setup()
{
     
  pinMode(RIGHT_DIR, OUTPUT);
  pinMode(LEFT_DIR, OUTPUT);
  
  pinMode(RIGHT_PWM, OUTPUT);
  pinMode(LEFT_PWM, OUTPUT);

}
void loop()
{
  if(Serial.available())
  {

    data = Serial.read();

    switch (data)
    {
      case 'I' :
        INDICATOR = "ID";
        DIRECTION = "00";
        break;
      case '1':
        INDICATOR = "R1";
        DIRECTION = "FF";
        break;
      case '2':
        INDICATOR = "R1";
        DIRECTION = "FL";
        break;
      case '3':
        INDICATOR = "R1";
        DIRECTION = "FR";
        break;
      case '4':
        INDICATOR = "L1";
        DIRECTION = "RF";
        break;
      case '5':
        INDICATOR = "L1";
        DIRECTION = "RL";
        break;
      case '6':
        INDICATOR = "L1";
        DIRECTION = "RR";
        break;
    }
  }
  if(INDICATOR == "R1")
  {
    if(firstforwardloop)
    {
      firstforwardloop = false;
      firstreverseloop = true;
      firstidealloop = true;
    }
    else if(ideal_state)
    {
      rightForwardRelay();
      leftForwardRelay();
     
      forward_state = true;  
      reverse_state = false;
      ideal_state = false; 
    }
    else if(reverse_state)
    {
       if(rightCruise >= rightChange)
          rightCruise = rightCruise - rightChange;
       
        if(leftCruise >= leftChange)
            leftCruise = leftCruise - leftChange;
      if( (rightCruise == rightChange) || (leftCruise = leftChange))
      {
       rightForwardRelay();
        leftForwardRelay();
        reverse_state = false;
        forward_state = true; 
      }
      
      
    }
    else
    {
      if((DIRECTION == "FL")
      {
        if(rightCruise < max_voltage)
          rightCruise = rightCruise + rightChange;
                    
        if(leftCruise >= leftChange)
          leftCruise = leftCruise - leftChange;
      }
      else if((DIRECTION == "FR")
      {
        if(rightCruise < max_voltage)
          rightCruise = rightCruise - rightChange;
                    
        if(leftCruise >= leftChange)
          leftCruise = leftCruise + leftChange;
      }
      else if((DIRECTION == "FF")
      {
        if(rightCruise < max_voltage)
          rightCruise = rightCruise + rightChange;
                    
        if(leftCruise >= max_voltage)
          leftCruise = leftCruise + leftChange;
      }
      else
      {
        if(rightCruise >= rightChange)
          rightCruise = rightCruise - rightChange;
  
        if(leftCruise >= leftChange)
          leftCruise = leftCruise - leftChange;
      }
    }
  }
  else if(INDICATOR == "L1")
  {
    if(firstreversloop)
    {
       firstreverseloop = false;
       firstforwardloop = true;
       firstidealloop = true;
    }
    else if(ideal_state)
    {
      rightreverseRelay();
      leftreverseRelay();
     
      reverse_state = true;
      forward_state = false;  
      ideal_state = false; 
    }
    else if(forward_state)
    {
      if( (rightCruise >= rightChange) || (leftCruise >= leftChange))
      {
        if(rightCruise >= rightChange)
          rightCruise = rightCruise - rightChange;
       
        if(leftCruise >= leftChange)
            leftCruise = leftCruise - leftChange;
      }
      else
      {
        rightreverseRelay();
        leftreverseRelay();
        reverse_state = true;
        forward_state = false; 
      }
    }
    else
    {
      if((DIRECTION == "RR")
      {
        if(rightCruise < max_voltage)
          rightCruise = rightCruise + rightChange;
                    
        if(leftCruise >= leftChange)
          leftCruise = leftCruise - leftChange;
      }
      else if((DIRECTION == "RL")
      {
        if(rightCruise < max_voltage)
          rightCruise = rightCruise - rightChange;
                    
        if(leftCruise >= leftChange)
          leftCruise = leftCruise + leftChange;
      }
      else if((DIRECTION == "RF")
      {
        if(rightCruise < max_voltage)
          rightCruise = rightCruise + rightChange;
                    
        if(leftCruise > max_voltage)
          leftCruise = leftCruise + leftChange;
      }
      else
      {
        if(rightCruise >= rightChange)
          rightCruise = rightCruise - rightChange;
  
        if(leftCruise >= leftChange)
          leftCruise = leftCruise - leftChange;
      }
    }
  }
  else if(INDICATOR == "IS")
  {
    if(firstidealloop)
    {
      firstidealloop = false;
      firstforwardloop = true;
      firstreverseloop = true;
    }
  }
  else
  {
    if(rightCruise >= rightChange)
      rightCruise = rightCruise - rightChange;

    if(leftCruise >= leftChange)
      leftCruise = leftCruise - leftChange;
  }
  analogWrite(RIGHT_PWM, rightCruise);
  analogWrite(LEF_PWMT, leftCruise);
}
    























