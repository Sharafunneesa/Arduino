const int redLed = 48;    // Red LED connected to digital pin 9
const int greenLed = 5; // Green LED connected to digital pin 10
const int blueLed = 4; 
const int gnd = 49; 

void setup() {
  Serial.begin(9600);
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(blueLed, OUTPUT);
  pinMode(gnd,OUTPUT);
}

void loop()
{
  if (Serial.available() > 0) 
  {
    char color = Serial.read();
    switch (color) 
    {
      case 'R':
      digitalWrite(redLed,HIGH);
      digitalWrite(greenLed,LOW);
      digitalWrite(blueLed,LOW);
      delay(1000);
        break;
      case 'G':
      digitalWrite(redLed,LOW);
      digitalWrite(greenLed,HIGH);
      digitalWrite(blueLed,LOW);
      delay(1000);
        break;
      case 'B':
      digitalWrite(redLed,LOW);
      digitalWrite(greenLed,LOW);
      digitalWrite(blueLed,HIGH);
      delay(1000);
        break;
      default:
        Serial.println("Invalid color");
    }
  }
}

