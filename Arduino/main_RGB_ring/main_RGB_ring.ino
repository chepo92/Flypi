
#include "Pins.h"
//#include "SerialParsing.h"

void setup()
{ //start serial port
  Serial.begin(115200);
  //Serial.flush();
  //Serial.println("start.");
  //set digital pin modes
  pinMode(LED1Pin, OUTPUT);
  pinMode(LED2Pin, OUTPUT);
  pinMode(RedGBPin, OUTPUT);
  pinMode(RGreenBPin, OUTPUT);
  pinMode(RGBluePin, OUTPUT);
  pinMode(servoOnPin, OUTPUT);
  pinMode(peltierEnablePin, OUTPUT);
  pinMode(peltierHeatPin1, OUTPUT);
  //pinMode(peltierHeatPin2,OUTPUT);
  pinMode(peltierCoolPin1, OUTPUT);
  //pinMode(peltierCoolPin2,OUTPUT);
  focusServo.attach(servoPin);
  pixels.begin();

  Serial.println("<wtd>>");


}//end void setup

void loop() {

  if (Serial.available() > 0) {

    token = Serial.readStringUntil('>');
    ////Serial.println(sizeof(token));
    ////delay(5);
    index = token.indexOf('<');
    term1 = token.substring(0,index);
    ////Serial.println(term1);
    term2 = token.substring(index+1);
    intTerm2 = term2.toInt();
    ////Serial.println(term2);
    
    //term1,term2 = serialParser();
    //Serial.println(term1);
  }

  //timing
  if (term1 == "TIM") {

    waitmils = intTerm2;
    waiting(waitmils);
    Serial.println("<wtd>>");
    }

  //check temp sensor
  if (term1 == "TEM")
    {  temperature = checkTemp(tempSensorPin);
        if (intTerm2!=99){newTemp=intTerm2;}
       Serial.println(temperature);

       if (peltOn == 1) {
          HoldTemp(newTemp, tempSensorPin, peltierCoolPin1, peltierHeatPin1);
    }

    if (temperature >= highLimit || temperature <= lowLimit) {
      digitalWrite (peltierEnablePin, LOW);
      digitalWrite(peltierHeatPin1, LOW);
      digitalWrite(peltierCoolPin1, LOW);
      digitalWrite(RedGBPin, HIGH);
      digitalWrite(RGreenBPin, HIGH);
      digitalWrite(RGBluePin, HIGH);
      peltOn = 0;
    }//end if temperature >=...
    Serial.println("<wtd>>");
  }//end if "TEM"

  //***************SERVO******************////
  if (term1 == "SER") {
    if (intTerm2 == 90) {
      digitalWrite(servoOnPin, LOW);

    }
    else {
      digitalWrite(servoOnPin, HIGH);
      focusServo.write(intTerm2); //because this is a cont. servo,
      //this will set the velocity, not the pos.
      delay(15);
      //correction = 0;
    }//else
  Serial.println("<wtd>>");}//end servo

  //////////////////////////////////////////////////
  //LED1
  if (term1 == "LD1") {
    if (intTerm2==1){digitalWrite(LED1Pin, HIGH);}
    if (intTerm2 == 0) {digitalWrite(LED1Pin, LOW);}
  Serial.println("<wtd>>");}
  if (term1 == "LZ1"){
    digitalWrite(LED1Pin, HIGH);
    waiting(intTerm2);
    digitalWrite(LED1Pin, LOW);

    Serial.println("<wtd>>");

  }


  //LED2
  if (term1 == "LD2") {
    if (intTerm2 == 1){digitalWrite(LED2Pin, HIGH);}
    if (intTerm2 == 0) {digitalWrite(LED2Pin, LOW);}

  Serial.println("<wtd>>");}

    if (term1 == "LZ2"){
    digitalWrite(LED2Pin, HIGH);
    waiting(intTerm2);
    digitalWrite(LED2Pin, LOW);


    Serial.println("<wtd>>");
  }









  //RING
  if (term1=="RIN"){
    if (intTerm2 == 1) { //ring on
      ringOn = 1;
      updateRing(ringRedHue, ringGreenHue, ringBlueHue);
      pixels.show();}
    if (intTerm2 == 0) { //ring off
      //incomingData = 0;
      ringOn = 0;
      updateRing(0, 0, 0);
      pixels.show();}
  Serial.println("<wtd>>");}//end if "RIN"



  if (term1=="RRE"){
    //oldRed = ringRedHue;
    ringRedHue=intTerm2;
    updateRing(ringRedHue, ringGreenHue, ringBlueHue);

    if (ringOn == 1) {

      //if the ring is on
      //show the update
      pixels.show();}//end if ringOn==1
  Serial.println("<wtd>>");}//end if term1=="RRE"


  if (term1 == "RGR") { //ring green
    //oldGreen = ringGreenHue;
    //set the brightness of the green channel
    ringGreenHue=intTerm2;
    updateRing(ringRedHue, ringGreenHue, ringBlueHue);
    if (ringOn == 1) {
      pixels.show();}
  Serial.println("<wtd>>");}//end if term1== "RGR"

  if (term1 == "RBL") { //ring blue
    //oldBlue = ringBlueHue;
    ringBlueHue = intTerm2;
    updateRing(ringRedHue, ringGreenHue, ringBlueHue);
    if (ringOn == 1) {pixels.show();}

  Serial.println("<wtd>>");}//end if RBL

  if (term1 == "RAL") { //ring all together
    ringBlueHue = intTerm2;
    ringGreenHue = intTerm2;
    ringRedHue = intTerm2;
    updateRing(ringRedHue, ringGreenHue, ringBlueHue);
    if (ringOn == 1) {
      pixels.show();
    }
  Serial.println("<wtd>>");}

  if (term1=="RZAR") {zapRed = intTerm2;Serial.println("<wtd>>");}
  if (term1=="RZAG") {zapGreen = intTerm2;Serial.println("<wtd>>");}
  if (term1=="RZAB") {zapBlue = intTerm2;Serial.println("<wtd>>");}

  if (term1=="RZAT") {

    if (ringOn == 1) {
      updateRing(zapRed, zapGreen, zapBlue);
      pixels.show();
      waiting(intTerm2);
      updateRing(ringRedHue, ringGreenHue, ringBlueHue);

      pixels.show();
    }//end if ring on
  Serial.println("<wtd>>");}




  //PELTIER
  if (term1 == "PEL") { //Peltier on
  if (intTerm2==1){
    //incomingData = 0;
    digitalWrite(peltierEnablePin, HIGH);
    peltOn = 1;
  }

  if (intTerm2 == 0) { //Peltier off
//    incomingData = 0;
    digitalWrite(peltierEnablePin, LOW);
    digitalWrite(peltierHeatPin1, LOW);
    digitalWrite(peltierCoolPin1, LOW);
    digitalWrite(RedGBPin, LOW);
    digitalWrite(RGreenBPin, LOW);
    digitalWrite(RGBluePin, LOW);
    peltOn = 0;
  }
  Serial.println("<wtd>>");}

  if (term1 == "PET") {newTemp = intTerm2;
  Serial.println("<wtd>>");}
  
//term1=String("0");
//term2=String("0");
}//end void loop




// function to get the temperature in °C by reading the AD22100 output
//to the analog in
float checkTemp(int pinToRead) {
  float temps = 0;
  float volts;
  float baseLine;
  for (int i = 0; i < 6; i++) {
    baseLine = analogRead(pinToRead);
    //temps = ((baseLine*(5.0 / 1023.0)) - 1.375) / 0.0225;
    //convert the value into volts
    volts = baseLine * (4750.0 / 1024);
    //convert the volt value into temperature (celsius)
    // the AD22100 has 200°C span (-50 to 150) for 4.5 V
    //therefore we need to subtract -1.375 to compensate
    //for this -50° offset
    temps = temps + ((volts - 1375) / 22.5);
    //delay(15);
  }//end for loop

  temps = temps / 5.0;
  //return the result of the function
  return temps;
}

/////////////////////////////////////
/// MANUAL PELTIER Control

float HoldTemp(float finalTemp, int tempSensorPin,
               int peltierCoolPin1, int peltierHeatPin1) {
  float temperature, temps;


  temperature = checkTemp(tempSensorPin);
  //Serial.print("temp: ");
  //Serial.println(temperature);
  //Serial.println(temperature);

  if (temperature < (finalTemp - TempTol)) {
    //digitalWrite(peltierEnablePin,HIGH);
    digitalWrite(peltierHeatPin1, HIGH);
    digitalWrite(peltierCoolPin1, LOW);
    analogWrite(RedGBPin, 255);
    analogWrite(RGreenBPin, 0);
    analogWrite(RGBluePin, 0);
  }//end if temperature<finalTemp
  if (temperature > (finalTemp + TempTol)) {
    //digitalWrite(peltierEnablePin,HIGH);
    digitalWrite(peltierHeatPin1, LOW);
    digitalWrite(peltierCoolPin1, HIGH);
    analogWrite(RedGBPin, 0);
    analogWrite(RGreenBPin, 0);
    analogWrite(RGBluePin, 255);
  }//end if temperature > finaTemp

  if ((temperature <= (finalTemp + TempTol)) && (temperature >= (finalTemp - TempTol))) {
    //digitalWrite(peltierEnablePin,LOW);
    //Serial.println("temp reached!");

    digitalWrite(peltierHeatPin1, LOW);
    digitalWrite(peltierCoolPin1, LOW);
    analogWrite(RGreenBPin, 255);
    analogWrite(RedGBPin, 0);
    analogWrite(RGBluePin, 0);

  }// end if temperature < finalTemp && temperature>finalTemp



}

void updateRing(int hue1, int hue2, int hue3) {
  for (int i = 0; i < ring_nPixels; i++) {
    pixels.setPixelColor(i, pixels.Color(hue1, hue2, hue3));
  }//end for
}//end updateRing

void waiting(int millistowait) {
  long int time3=0;
  long int time4=0;
  int flag = 1;
  int index;
  String token1;
  time3 = millis();
  time4 = time3;
  //wait amount of time
  while ((time4 - time3) < millistowait) {
    //Serial.flush();
    //Serial.println("waiting");
    //Serial.println(millistowait);
    time4 = millis();
    //Serial.println(time4);
  } //done waiting

  //handshake
//  while(flag==1){
//    Serial.println("<wtd>>");
//    token1=Serial.readStringUntil('>');
//    index = token.indexOf('<');
//    if (token.substring(0,index)=="END"){flag=0;}
//  }
  //Serial.flush();
}//waiting
