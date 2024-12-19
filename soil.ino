#define BLYNK_TEMPLATE_ID "TMPL3fDDgANLY"
#define BLYNK_TEMPLATE_NAME "Plant Health Monitoring"
#define BLYNK_AUTH_TOKEN "-OvYlkICloYRtdKp7hejh-6b2VMF4W1D"

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#define n1 D0


char auth[] = "-OvYlkICloYRtdKp7hejh-6b2VMF4W1D"; //Enter your Blynk auth token
char ssid[] = "FRIDAY"; //Enter your WIFI name
char pass[] = "ankan123";

const int sensor_pin = A0;
int Moisture;
double t;
int Max = 40;

void setup() {
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass, "blynk.cloud",80);
  pinMode(n1, OUTPUT) ;

}

void loop() {
  Blynk.virtualWrite(V0,1);
  Blynk.virtualWrite(V1,0);
  int data = analogRead(sensor_pin);
  int Moisture = ( 100 - ( (data/1024.00) * 100 ) );
  //Serial.println(data);
  Serial.println(Moisture);
  Blynk.virtualWrite(V2, Moisture);
  double fn = (Moisture/Max)*100;
  if (fn<=10){
    double time  = (Max-Moisture)/9;
    digitalWrite(n1, HIGH);
    Blynk.virtualWrite(V1,1);
    Blynk.virtualWrite(V0,0);
    Blynk.virtualWrite(V3,"motor running");
    delay(time*1000);
    digitalWrite(n1,LOW);
    Blynk.virtualWrite(V3,"motor stop");
    //delay(time*1000);
  }
    
  delay(500);
  Blynk.run(); 


}

void ON(){
  digitalWrite(n1, HIGH);
  Blynk.virtualWrite(V3,"motor running");
}

void OFF(){
  digitalWrite(n1,LOW);
  Blynk.virtualWrite(V3,"motor stop");
}
  

BLYNK_WRITE(V4) {
  if (param.asInt()==1){
    ON();
  }
  else if (param.asInt()==0){
    OFF();
  }
}
