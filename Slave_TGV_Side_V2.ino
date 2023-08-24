//#define BRAKE 9
//#define POWER_LOCK 8

#define DIR_RIGHT 7
#define PWM_RIGHT 6
#define DIR_LEFT 4
#define PWM_LEFT 5

#define DELAY_VOLTAGE 100
#define DELAY_VOLTAGE_IDEL 100

char code='I';

String INDICATOR = "00", DIRECTION = "01";

double leftCruise = 0.00, rightCruise = 0.00, leftChange, rightChange;

// Forward Max values
int MAX_VOLTAGE_LEFT_FORWARD = 33, MAX_VOLTAGE_RIGHT_FORWARD = 30;
double rightChangeForward = 1.00;
double leftChangeForward = MAX_VOLTAGE_LEFT_FORWARD/MAX_VOLTAGE_RIGHT_FORWARD;

// Reverse Max values
int MAX_VOLTAGE_LEFT_REVERSE = 33, MAX_VOLTAGE_RIGHT_REVERSE = 30;
double rightChangeReverse= 1.00;
double leftChangeReverse = MAX_VOLTAGE_LEFT_REVERSE/MAX_VOLTAGE_RIGHT_REVERSE;

bool idelLoopEntryOne=true;
bool forwardLoopEntryOne=true,reverseLoopEntryOne=true;
bool STATE_FORWARD=false, STATE_REVERSE=false, STATE_IDEL=false;

unsigned long loopCurrentMillis=0, PrevMillis;

void rightReverseRelay(){
  digitalWrite(DIR_RIGHT,LOW);
//  Serial.println("RIGHT DIRECTION is LOW");/
}
    
void rightForwardRelay(){
  digitalWrite(DIR_RIGHT,HIGH);
//  Serial.println("RIGHT DIRECTION is HIGH");/
}
    
void leftReverseRelay(){
  digitalWrite(DIR_LEFT,LOW);
//  Serial.println("LEFT DIRECTION is LOW");/
}

void leftForwardRelay(){
  digitalWrite(DIR_LEFT,HIGH);
//  Serial.println("LEFT  DIRECTION is HIGH");/
}

double increCruise(double x, double incre){
  return (x+incre);
}

double decreCruise(double x, double decre){
  return (x-decre);
}

double minAmong(double x, double y){
  if(x<y)
    return x;
  else
    return y;
}

//void brakesOn(){
//  digitalWrite(BRAKE, LOW);
//}
//
//void brakesOff(){
//  digitalWrite(BRAKE, HIGH);
//}
//
//void powerLocksOn(){
//  digitalWrite(POWER_LOCK, HIGH);  
//}
//
//void powerLocksOff(){
//  digitalWrite(POWER_LOCK, LOW);  
//}

void blinkLED(){
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
}

void setup() {
  
  Serial.begin(9600);

  rightChange = minAmong(rightChangeForward,rightChangeReverse);
  leftChange = minAmong(leftChangeForward,leftChangeReverse);
     
  pinMode(DIR_RIGHT, OUTPUT);
  pinMode(PWM_RIGHT, OUTPUT);

  pinMode(DIR_LEFT, OUTPUT);
  pinMode(PWM_LEFT, OUTPUT);
  
//  pinMode(BRAKE, OUTPUT);
//  pinMode(POWER_LOCK, OUTPUT);

  pinMode(LED_BUILTIN, OUTPUT); 

//  powerLocksOn();
//  brakesOff();
}

void loop() {
  // put your main code here, to run repeatedly:
  
  if(Serial.available()){

    code = Serial.read();

    switch (code){
      case 'I' :
        INDICATOR = "ID";
        DIRECTION = "00";
        break;
      case '1':
        INDICATOR = "R1";
        DIRECTION = "FF";
        break;
      case '3':
        INDICATOR = "R1";
        DIRECTION = "FL";
        break;
      case '5':
        INDICATOR = "R1";
        DIRECTION = "FR";
        break;
      case '2':
        INDICATOR = "L1";
        DIRECTION = "RF";
        break;
      case '4':
        INDICATOR = "L1";
        DIRECTION = "RL";
        break;
      case '6':
        INDICATOR = "L1";
        DIRECTION = "RR";
        break;
      
    }

    Serial.println(code);
  }

  loopCurrentMillis = millis();

//  if(INDICATOR == "B1"){
//    blinkLED();
////    Serial.println("Brakes Pressed");
//    brakesOn();
//    
//  }else{
//    blinkLED();
////    Serial.println("Brakes Released");
//    brakesOff();
//    
//  }
  
//  if(INDICATOR == "S1"){
//    blinkLED();
////    Serial.println("START of the Vehicle");
//    powerLocksOff();
//    
//  }else if(INDICATOR == "S0"){
//    blinkLED();
////    Serial.println("STOP of the Vehicle");
//    powerLocksOn();
//    
//  }else 

    if(INDICATOR == "R1")
    {
    
//    Serial.println("Forward Entry");

    if(forwardLoopEntryOne){
        
      PrevMillis = loopCurrentMillis;
      forwardLoopEntryOne = false;
      reverseLoopEntryOne = true;
      idelLoopEntryOne = true;
      
      }else if(STATE_IDEL){
  
        rightForwardRelay();
        leftForwardRelay();
        STATE_IDEL = false;    
        STATE_REVERSE = false;
        STATE_FORWARD = true;
          
        }else if(STATE_REVERSE)
        {
  
          if( (rightCruise >= rightChange) || (leftCruise >= leftChange)){

            if(rightCruise >= rightChange){
              rightCruise = decreCruise(rightCruise,rightChange);
            }
            
            if(leftCruise >= leftChange){
              leftCruise = decreCruise(leftCruise,leftChange);
            }
          
            }else if(loopCurrentMillis - PrevMillis > DELAY_VOLTAGE)
            {
            
              rightForwardRelay();
              leftForwardRelay();
              STATE_REVERSE = false;
              STATE_FORWARD = true;            
              
            }
          }else{
            
              if(DIRECTION == "FL")
              {
                blinkLED();
//                Serial.println("Moving Forward Left");
  
                if(rightCruise < MAX_VOLTAGE_RIGHT_FORWARD)
                  rightCruise = increCruise(rightCruise,rightChange);
                    
                if(leftCruise >= leftChange)
                  leftCruise = decreCruise(leftCruise,leftChange);

//                rightCruise = MAX_VOLTAGE_RIGHT_REVERSE;
//                leftCruise = 0;
  
              }else if(DIRECTION == "FR"){
                blinkLED();  
//                Serial.println("Moving Forward Right");
  
                if(leftCruise < MAX_VOLTAGE_LEFT_FORWARD)
                  leftCruise = increCruise(leftCruise,leftChange);
                    
                if(rightCruise >= rightChange)
                  rightCruise = decreCruise(rightCruise,rightChange);

//                rightCruise = 0;
//                leftCruise = MAX_VOLTAGE_LEFT_REVERSE;
  
              }else if(DIRECTION == "FF")
              {
                blinkLED();
//              Serial.println("Moving Forward Front");
  
              if(rightCruise < MAX_VOLTAGE_RIGHT_FORWARD)
                rightCruise = increCruise(rightCruise,rightChange);
                  
              if(leftCruise < MAX_VOLTAGE_LEFT_FORWARD)
                leftCruise = increCruise(leftCruise,leftChange);

//              rightCruise = MAX_VOLTAGE_RIGHT_REVERSE;
//              leftCruise = MAX_VOLTAGE_LEFT_REVERSE;
              }else
              {
                
                if(rightCruise >= rightChange)
                  rightCruise = decreCruise(rightCruise,rightChange);
  
                if(leftCruise >= leftChange)
                  leftCruise = decreCruise(leftCruise,leftChange);

//                rightCruise = 0;
//                leftCruise = 0;
              }
            }
  }else if(INDICATOR == "L1"){

//    Serial.println("Reverse Entry");

    if(reverseLoopEntryOne){
        
      PrevMillis = loopCurrentMillis;
      reverseLoopEntryOne = false;
      forwardLoopEntryOne = true;
      idelLoopEntryOne = true;
      
      }else if(STATE_IDEL){
  
        rightReverseRelay();
        leftReverseRelay();
        STATE_IDEL = false;
        STATE_FORWARD = false;
        STATE_REVERSE = true;
          
        }else if(STATE_FORWARD){
  
          if( (rightCruise >= rightChange) || (leftCruise >= leftChange)){

            if(rightCruise >= rightChange){
              rightCruise = decreCruise(rightCruise,rightChange);
            }
            
            if(leftCruise >= leftChange){
              leftCruise = decreCruise(leftCruise,leftChange);
            }
          
            }else if(loopCurrentMillis - PrevMillis > DELAY_VOLTAGE){
            
              rightReverseRelay();
              leftReverseRelay();
              STATE_FORWARD = false;
              STATE_REVERSE = true;          
              
              }
          }else{
            
            if(DIRECTION == "RR"){
                blinkLED();
//              Serial.println("Moving Reverse Right");

              if(rightCruise < MAX_VOLTAGE_RIGHT_REVERSE)
                rightCruise = increCruise(rightCruise,rightChange);
                  
              if(leftCruise >= leftChange)
                leftCruise = decreCruise(leftCruise,leftChange);

//              rightCruise = MAX_VOLTAGE_RIGHT_REVERSE;
//              leftCruise = 0;

            }else if(DIRECTION == "RL"){
              blinkLED();
//              Serial.println("Moving Reverse Left");

              if(leftCruise < MAX_VOLTAGE_LEFT_REVERSE)
                leftCruise = increCruise(leftCruise,leftChange);
                  
              if(rightCruise >= rightChange)
                rightCruise = decreCruise(rightCruise,rightChange);

//              rightCruise = 0;
//              leftCruise = MAX_VOLTAGE_LEFT_REVERSE;

            }else if(DIRECTION == "RF"){
              blinkLED();
//            Serial.println("Moving Reverse Front");

            if(rightCruise < MAX_VOLTAGE_RIGHT_REVERSE)
              rightCruise = increCruise(rightCruise,rightChange);
                
            if(leftCruise < MAX_VOLTAGE_LEFT_REVERSE)
              leftCruise = increCruise(leftCruise,leftChange);

//            rightCruise = MAX_VOLTAGE_RIGHT_REVERSE;
//            leftCruise = MAX_VOLTAGE_LEFT_REVERSE;
      
            }else {
              
              if(rightCruise >= rightChange)
                rightCruise = decreCruise(rightCruise,rightChange);

              if(leftCruise >= leftChange)
                leftCruise = decreCruise(leftCruise,leftChange);

//                rightCruise = 0;
//                leftCruise = 0;
            }
          }
  }else if(INDICATOR == "ID"){
      blinkLED();
//    Serial.println("Idel Loop");
    
    if(idelLoopEntryOne)
    {
      
      PrevMillis = loopCurrentMillis;
      idelLoopEntryOne = false;
      forwardLoopEntryOne = true;
      reverseLoopEntryOne = true;
        
      }else
      {

        if(rightCruise >= rightChange)
          rightCruise = decreCruise(rightCruise,rightChange);
//        rightCruise = 0;
          
        if(leftCruise >= leftChange)
          leftCruise = decreCruise(leftCruise,leftChange);
//        leftCruise = 0;
          
        if(loopCurrentMillis - PrevMillis > DELAY_VOLTAGE_IDEL)
          STATE_IDEL = true;
      }    
    }

  analogWrite(PWM_RIGHT, rightCruise);
  analogWrite(PWM_LEFT, leftCruise);

  Serial.print("  rightCruiseLast = ");
  Serial.print(rightCruise);
  Serial.print("  leftCruiseLast = ");
  Serial.println(leftCruise);
  delay(1000);
  
  digitalWrite(LED_BUILTIN, LOW);
  
}

