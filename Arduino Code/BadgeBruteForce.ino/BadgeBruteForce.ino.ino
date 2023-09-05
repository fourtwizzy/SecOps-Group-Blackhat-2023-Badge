void setup() {
  pinMode(2, OUTPUT);    // sets the digital pin 2 ("0" on pcb) as Output
  digitalWrite(2, LOW);  //ensure pin is low at run time

  pinMode(4, OUTPUT);    // sets the digital pin 4 ("1" on pcb) as Output
  digitalWrite(4, LOW);  //ensure pin is low at run time

  pinMode(7, OUTPUT);    // sets the digital pin 7 ("P" on pcb) as Output
  digitalWrite(7, LOW);  //ensure pin is low at run time

  Serial.begin(9600);//setup serial port
}

void pressProgramPin(){
  Serial.write( '\r' );  // Carriage Return
  //delay(5000);
  Serial.println("###Pressing Program Pin###");
  delay(200);
  digitalWrite(7, HIGH);  //Set pin 7 to high for transistor base
  delay(100);
  digitalWrite(7, LOW);  //Set pin 7 to low for transistor base
  delay(3000);
  return;
}

void pressZeroPin(){
  Serial.println("###Pressing Zero Pin###");
  delay(200);
  digitalWrite(2, HIGH);  //Set pin 2 to high for transistor base
  delay(160);
  digitalWrite(2, LOW);  //Set pin 2 to low for transistor base
  delay(3000);
  return;
}

void pressOnePin(){
  Serial.println("###Pressing One Pin###");
  delay(200);
  digitalWrite(4, HIGH);  //Set pin 4 to high for transistor base
  delay(160);
  digitalWrite(4, LOW);  //Set pin 4 to low for transistor base
  delay(3000);
  return;
}

void resetCode(){
  delay(1000);
  Serial.println("###Sending to pressProgramPin()###");
  pressProgramPin();
  for(int i = 0, mask = 128; i < 8; i++, mask = mask >> 1)
  {
      if (0 & mask) 
      {
          Serial.println("###resetCode press 1###");
          Serial.println("1");
          pressOnePin();
      }
      else
      {
          Serial.println("###resetCode press 0###");
          Serial.print("0");
          pressZeroPin();
      }
  }
  delay(1000);
  pressProgramPin();
  return;
}

// Prints out Binary value (1 or 0) of byte
void printOut1(int c) {
  for (int bits = 7; bits > -1; bits--) {
    // Compare bits 7-0 in byte
    if (c & (1 << bits)) {
      Serial.print("1");
      pressOnePin();
      delay(500);
    }
    else {
      Serial.print("0");
      pressZeroPin();
      delay(500);
    }
  }
  delay(500);
  pressProgramPin();
  Serial.println("");
  return;
}

void loop() {
  Serial.println(" ");
  Serial.println("Entering Programming Mode");
  for(int l = 0; l >= 0; l--){
    if(l == 187 || l == 185)
      {
        Serial.println("###Known Values###");
      }
    else
      {
        pressProgramPin();
        delay(500);
        printOut1(l);
        delay(7000);
      }
  }

}