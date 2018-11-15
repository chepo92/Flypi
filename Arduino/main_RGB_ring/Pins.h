// Import libraries
#include <Adafruit_NeoPixel.h> // LED Ring
#include <Wire.h> // LED Matrix
#include <Adafruit_LEDBackpack.h> // LED Matrix
#include <Adafruit_GFX.h> // LED Matrix
#include <Servo.h> //servo motor controlling the autofocus
//************************************//
// Define Pin allocations on Arduino
//*********************************//


int LED1Pin = 10;
int LED2Pin = 11; // NOT CONFIGURED
int RedGBPin = 6;
int RGreenBPin = 4;
int RGBluePin = 5;
int RingPin = 7;
int servoPin = 8;
int servoOnPin = 9;
int peltierEnablePin = 13;
int peltierHeatPin1 = 3;//12
int peltierCoolPin1 = 2;//8
int tempSensorPin = A7;//A5


String token;
String term1;
String term2;
int intTerm2;

//String temporary;
int index;
//unsigned int incomingData = 0;
//unsigned int address=0;
unsigned int correction = 0;
//  int control_ledpin = 0;

int startFlag = 0;

//variables needed for peripherical functions
//ring
int ring_nPixels = 12;
int ringOn = 0;
int ringRedHue = 10;
int ringGreenHue = 10;
int ringBlueHue = 10;
//int ringWhiteHue=0;
int zapRed = 0;
int zapGreen = 0;
int zapBlue = 0;
int zapWhite = 0;
int ringBright = 0;
int matBright = 0;
int waitmils = 0;
//peltier
int peltOn = 0;
int tempToAnalog = 0;
int analogOut = 0;
float tempSensVolt = 0;
float temperature = 0;
float newTemp = 30.0;
unsigned long time1 = 0;
unsigned long time2 = 0;
//string incomingData1='';
//*********************************//
float TempTol = 0.5; // tolerance
float highLimit = 40.0; //in Celsius
float lowLimit = 13.0; //in Celsius




//create servo object ****************//
Servo focusServo;


//create function to control LED ring
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(ring_nPixels, RingPin, NEO_GRB + NEO_KHZ800);


