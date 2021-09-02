

//#define BLYNK_TEMPLATE_ID           "TMPLlDw6igao"
//#define BLYNK_DEVICE_NAME           "DEVICE"
#define BLYNK_AUTH_TOKEN            "0e5944ff5aea475f94b5ed1483bed315"
#include "ACS712.h"

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);

//  // set the LCD address to 0x27 for a 16 chars and 2 line display

void lcdq(int x,int y, String data){
   lcd.setCursor(x,y);
  lcd.print(data); 
  }



float vOUT = 0.0;
float vIN = 0.0;
float R1 = 30000.0;
float R2 = 7500.0;
int value = 0;

float vOUT1 = 0.0;
float vIN1 = 0.0;
float R11 = 30000.0;
float R21 = 7500.0;
int value1 = 0;


// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial


#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>

char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "poco";
char pass[] = "shivamadappa@123.";

// Hardware Serial on Mega, Leonardo, Micro...
//#define EspSerial Serial1

// or Software Serial on Uno, Nano...
#include <SoftwareSerial.h>
SoftwareSerial EspSerial(3, 2); // RX, TX

// Your ESP8266 baud rate:
#define ESP8266_BAUD 9600

ESP8266 wifi(&EspSerial);
ACS712 sensor(ACS712_30A, A0);

 
void setup()
{
 lcd.init();
  // Print a message to the LCD.
 lcd.backlight();
  // Debug console
  Serial.begin(115200);

  // Set ESP8266 baud rate
  EspSerial.begin(ESP8266_BAUD);
  delay(10);
Serial.println(" im near befin");
  Blynk.begin(auth, wifi, ssid, pass);
  Serial.println(" im after befin");
  // You can also specify server:
  //Blynk.begin(auth, wifi, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(auth, wifi, ssid, pass, IPAddress(128.199.144.129), 8080);
  sensor.calibrate();
}
//LiquidCrystal_I2C lcd1(0x27,16,2);
void loop()
{
  value = analogRead(A1);
  vOUT = (value * 5.0) / 1024.0;
  vIN = vOUT / (R2/(R1+R2));
  Serial.print("Solar Pannel Volt = ");
  Serial.print(vIN);
  value1 = analogRead(A2);
  vOUT1 = (value1 * 5.0) / 1024.0;
  vIN1 = vOUT1 / (R2/(R1+R2));
  Serial.print("   Battery volt = ");
  Serial.print(vIN1);
   Blynk.virtualWrite(V0,vIN);
    float I = sensor.getCurrentDC();
  
  // Send it to serial
  I=((-1* I)+0.2);
  Serial.println(String("  I = ") + I + " A");
  lcdq(0,0,"Solar:");
  lcdq(6,0,String(vIN));
 // lcdq(7,0,"V");
  lcdq(10,0,"I=");
  lcdq(12,0,String(I));
   lcdq(0,1,"Bat:");
   lcdq(4,1,String(vIN1));
   lcdq(10,1,"V");
   delay(2000);
   lcd.clear();
   
   lcdq(0,0,"power:");
   lcdq(6,0,String(vIN*I));
   delay(2000);
   
    lcd.clear();
  
  // Wait one second before the new cycle
  
  Blynk.run();
  delay(1000);
  // You can inject your own code or combine it with other sketches.
  // Check other examples on how to communicate with Blynk. Remember
  // to avoid delay() function!
}
