#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#define BLYNK_PRINT Serial
#include <BlynkSimpleEsp8266.h>
#include <NTPClient.h>

char auth[] = ""; //blink auth token
char ssid[] = ""; //network name
char pass[] = ""; //internet password


int red = 16;
int green = 5;
int blue = 4;
int valorv0,valorv1,valorv2,manualMode,var;


int introducir_horas;
int introducir_minutos;
int pinCafetera = 13;


WiFiUDP ntpUDP;
BlynkTimer timer;

NTPClient timeClient(ntpUDP, "mx.pool.ntp.org", -18000, 60000);
char dayWeek [7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

BLYNK_WRITE(V0){
  valorv0 =  param.asInt();
  analogWrite(red,valorv0);
}
BLYNK_WRITE(V1){
  valorv1 =  param.asInt();
  analogWrite(green,valorv1);
}
BLYNK_WRITE(V2){
  valorv2 =  param.asInt();
  analogWrite(blue,valorv2);
}

BLIINK_WRITE(V3){
  manualMode = param.asInt();
  if(manualModer == 1){
    int on = 16;
    int off = 21;
    int var=0;
    while (on>var && off<var){
      var ++;
      delay(60000);
    }
  }
}

BLYNK_WRITE(V7){
  introducir_horas =  param.asInt();
}
BLYNK_WRITE(V8){
  introducir_minutos = param.asInt();
}

void setup() {
   Serial.begin(9600);
  WiFi.begin(ssid, pass);
  Blynk.begin(auth,ssid,pass);

  
  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }
  timeClient.begin();
  ///////////////RGB LEDS/////////////////////////
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);

}

 void loop(){
  Blynk.run();
   timer.run(); 
   timeClient.update();
  Serial.print(dayWeek[timeClient.getDay()]); 
  Serial.print(" ");
  Serial.println(timeClient.getFormattedTime());
  
  if(timeClient.getHours()==introducir_horas&&timeClient.getMinutes()==introducir_minutos){
    digitalWrite(pinCafetera, HIGH);
  }else{
    digitalWrite(pinCafetera,LOW);
  }
  delay(1000);
}
