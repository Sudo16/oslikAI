#include "GyverStepper2.h"
#include <Wire.h>
#include <HMC5883L.h>
GStepper2<STEPPER2WIRE> stepper1(200, 2, 5);
GStepper2<STEPPER2WIRE> stepper2(200, 3, 4);
HMC5883L compass;


MagnetometerScaled valueOffset;
static float l_cir = 0.3;//длинна окружности в метрах 
char str_read[250];
int counter;
byte count_subStr = 0;
long route[5] = {0,0,0,0,0};//id;distance;degree;speed;timeout
String num_subroute;
bool route_end = false;
int count_barrier = 0;
int current_angle;
void setup() {
  Serial.begin(9600);
  stepper1.setMaxSpeed(100);    
  stepper1.setAcceleration(200); 
  stepper1.setTarget(300);    
  stepper2.setMaxSpeed(100);    
  stepper2.setAcceleration(200); 
  stepper2.setTarget(300);   
  compass.setMeasurementMode(MEASUREMENT_CONTINUOUS);
  compassCalibrate();
  pinMode(6, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  stepper1.tick();
  stepper2.tick();
  parse_OPi();
  compas_handler();
  route_handler();
}

