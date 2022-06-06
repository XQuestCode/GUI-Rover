#include <SoftwareSerial.h>
SoftwareSerial mySerial(5,6);  //5 is Rx, 6 is Tx
void setup() {
  pinMode(11, OUTPUT);  //left motors forward
  pinMode(12, OUTPUT);  //left motors reverse
  pinMode(13, OUTPUT);  //right motors forward
  pinMode(10, OUTPUT);  //right motors reverse

  Serial.begin(9600);
  mySerial.begin(9600);
}
char first ="";
int times = -1;
char temp;
void loop() {
  while (Serial.available() > 0) {
    temp = Serial.read();
   if(temp>=65) {                 //as 65 is the ascii value for character a 
    first = (char)temp;
   }else {  
    times = (int)temp-48;            //as times is the number of steps to be taken.
   }
  }
  if(first != "" && times != -1) {
    Serial.print("Command is");
    Serial.println(first);
    Serial.print("times is");
    Serial.println(times);
    mySerial.println(first);
    mySerial.println(times);
  

  for (int i = 0; i < times*200; i++)
  {
    Serial.println(i);
                      //emitting out the data
    if (first == 'F') //move forward(all motors rotate in forward direction)
    {
      digitalWrite(13, HIGH);
      digitalWrite(11, HIGH);
    }

    else if (first == 'B') {    //move reverse (all motors rotate in reverse direction)
      digitalWrite(12, HIGH);
      digitalWrite(10, HIGH);
    }

    else if (first == 'L') {
      digitalWrite(13, HIGH); //turn left (right side motors rotate in forward direction, left side motors doesn't rotate)
    }

    else if (first == 'R') {    //turn right (left side motors rotate in forward direction, right side motors doesn't rotate)
      digitalWrite(11, HIGH);
    }
  }
  if (first == 'S') {    //STOP (all motors stop)
    digitalWrite(13, LOW);
    digitalWrite(12, LOW);
    digitalWrite(11, LOW);
    digitalWrite(10, LOW);
  }
  delay(100);
    digitalWrite(13, LOW);
    digitalWrite(12, LOW);
    digitalWrite(11, LOW);
    digitalWrite(10, LOW);

  first = "";
  times = -1;
  delay(100);
  }
}
