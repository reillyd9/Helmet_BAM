#include <DFRobot_sim808.h>
#include <sim808.h>

// Combined code for helmet
#include <DFRobot_sim808.h>
#include <sim808.h>
#include <Adafruit_NeoPixel.h>
#include "Wire.h"
#include <SoftwareSerial.h>

#define PHONE_NUMBER "0863986066"
#define MESSAGE_LENGTH 160
#define buzzer 5
#define PIN 6

Adafruit_NeoPixel strip = Adafruit_NeoPixel(16, PIN, NEO_GRB + NEO_KHZ800);
char MESSAGE [MESSAGE_LENGTH];
String locationstring, lati = "53.344401", longd = "-6.257599";

//test
DFRobot_SIM808 sim808(&Serial);
const int MPU_ADDR = 0x68;
int16_t accelerometer_x, accelerometer_y, accelerometer_z;
char tmp_str[7];
char* convert_int16_to_str(int16_t i) {
  sprintf(tmp_str, "%6d", i);
  return tmp_str;
}

int accel_x_read, accel_y_read, accel_z_read;
long int x_data[3], y_data[3], z_data[3];
long int changein_x, changein_y, changein_z, x_tot, y_tot, z_tot, x_avg, y_avg, z_avg;
int p, j, l, x, pix;
bool filled;

int fsrPin;    // the FSR and 10K pulldown are connected to a0
int fsrReading;     // the analog reading from the FSR resistor divider
unsigned long previousMillis;
unsigned long interval;
bool worn;


void setup() {
  Serial.begin(9600);

  Wire.begin();
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);

  pinMode(buzzer, OUTPUT);

  strip.begin();
  strip.setBrightness(30); //adjust brightness here
  strip.show(); // Initialize all pixels to 'off'
  x = 0;
  pix = 0;


  fsrPin = 0;
  previousMillis = 0;
  interval = 5000;
  worn = false;
  

  p = 0;
  l = 0;
  filled = false;
  x_tot = 0, y_tot = 0, z_tot = 0, x_avg = 0, y_avg = 0, z_avg = 0;


  while (!sim808.init()) {
    delay(1000);
    Serial.print("Sim808 init error\r\n");
  }

  Serial.println("Sim808 init success");






}
void loop() {

  //  unsigned long currentMillis = millis();
  //
  //  if (currentMillis - previousMillis > interval) {
  //    previousMillis = currentMillis;
  //    Read_Sensor();
  //    }
  //
  //  if (worn){
  
  if (x >= 0 && x < 144) {
    //colorWipe(strip.Color(255, 0, 0), 0); // Red
    if (x % 12 == 0) {
      strip.setPixelColor(pix, strip.Color(255, 0, 0));
      strip.show();
      pix++;
      if (pix >= 12) {
        pix = 0;
      }
    }
  }

  if (x >= 144 && x < 288) {
    //colorWipe(strip.Color(0, 0, 225), 0); // Blue
    if (x % 12 == 0) {
      strip.setPixelColor(pix, strip.Color(0, 0, 225));
      strip.show();
      pix++;
      if (pix >= 12) {
        pix = 0;
      }
    }
  }

  if (x >= 288 && x < 432) {
    //colorWipe(strip.Color(255, 180, 0), 0); // Yellow
    if (x % 12 == 0) {
      strip.setPixelColor(pix, strip.Color(255, 180, 0));
      strip.show();
      pix++;
      if (pix >= 12) {
        pix = 0;
      }
    }
  }

  if (x >= 432 && x < 576) {
    //colorWipe(strip.Color(225, 0, 225), 0); //pink
    if (x % 12 == 0) {
      strip.setPixelColor(pix, strip.Color(225, 0, 225));
      strip.show();
      pix++;
      if (pix >= 12) {
        pix = 0;
      }
    }
  }

  if (x >= 576 && x < 720) {
    //colorWipe(strip.Color(0, 150, 225), 0); // light blue
    if (x % 12 == 0) {
      strip.setPixelColor(pix, strip.Color(0, 150, 225));
      strip.show();
      pix++;
      if (pix >= 12) {
        pix = 0;
      }
    }
  }

  if (x >= 720 && x < 864) {
    // colorWipe(strip.Color(0, 255, 0), 0); // Green
    if (x % 12 == 0) {
      strip.setPixelColor(pix, strip.Color(0, 255, 0));
      strip.show();
      pix++;
      if (pix >= 12) {
        pix = 0;
      }
    }
  }

  if ( x == 864) {
    x = 0;
  }

  x++;





  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR, 7 * 2, true);

  accelerometer_x = Wire.read() << 8 | Wire.read();
  accelerometer_y = Wire.read() << 8 | Wire.read();
  accelerometer_z = Wire.read() << 8 | Wire.read();


  accel_x_read = abs(accelerometer_x / 10);
  accel_y_read = abs(accelerometer_y / 10);
  accel_z_read = abs(accelerometer_z / 10);

  x_data[p] = accel_x_read;
  y_data[p] = accel_y_read;
  z_data[p] = accel_z_read;
  p++;



  if (p == 3) {
    if (filled == false) {
      Serial.println("-------------------------------------- ");
    }
    filled = true;
    p = 0;
  }

  x_tot = 0; y_tot = 0; z_tot = 0;
  x_avg = 0; y_avg = 0; z_avg = 0;

  if (filled == true) {

    for (j = 0; j < 3; j++) {

      //      Serial.println("  ");
      //      Serial.print(x_data[j]);
      //      Serial.print("  ");
      //
      //      Serial.print("  ");
      //      Serial.print(y_data[j]);
      //      Serial.print("  ");
      //
      //      Serial.print("  ");
      //      Serial.print(z_data[j]);
      //      Serial.print("  ");

    }


    x_tot = x_data[0] + x_data[1] + x_data[2];
    y_tot = y_data[0] + y_data[1] + y_data[2];
    z_tot = z_data[0] + z_data[1] + z_data[2];


  }
  //      Serial.print(" xtot ");
  //      Serial.print(x_tot);
  //      Serial.print("  ");
  //
  //      Serial.print(" ytot ");
  //      Serial.print(y_tot);
  //      Serial.print("  ");
  //
  //      Serial.print(" ztot ");
  //      Serial.print(z_tot);
  //      Serial.print("  ");

  x_avg = x_tot / 3;
  y_avg = y_tot / 3;
  z_avg = z_tot / 3;

  //      Serial.print(" xavg ");
  //      Serial.print(x_avg);
  //      Serial.print("  ");
  //
  //      Serial.print(" yavg ");
  //      Serial.print(y_avg);
  //      Serial.print("  ");
  //
  //      Serial.print(" zavg ");
  //      Serial.print(z_avg);
  //      Serial.print("  ");

  changein_x = x_avg - (accel_x_read);
  changein_y = y_avg - (accel_y_read);
  changein_z = z_avg - (accel_z_read);


  //  Serial.print(".\t");
  //  Serial.print(l);
  //  Serial.print(".\t");
  //  l++;


  Serial.println();
  Serial.print("aX = ");
  Serial.print("\t");
  Serial.print(changein_x);
  Serial.print(" | aY = ");
  Serial.print("\t");
  Serial.print(changein_y);
  Serial.print(" | aZ = ");
  Serial.print("\t");
  Serial.print(changein_z);




  if ((abs(changein_x) > 1500 || abs(changein_y) > 1500 || abs(changein_z) > 1500) && filled) {
    Serial.println("\nIMPACT DETECTED ");
    Emergency_Protocol();
  }


  Serial.println();


  delay(10);
}







void Emergency_Protocol() {


  tone(buzzer, 10000); // Send 1KHz sound signal...
  delay(10000);        // ...for 1 sec
  noTone(buzzer);     // Stop sound...




  Serial.println("Locating Device... :)");

  if ( sim808.attachGPS())
    Serial.println("GPS power success");
  else
    Serial.println("GPS power failure");


  if (sim808.getGPS()) {
    Serial.print(sim808.GPSdata.year);
    Serial.print("/");
    Serial.print(sim808.GPSdata.month);
    Serial.print("/");
    Serial.print(sim808.GPSdata.day);
    Serial.print(" ");
    Serial.print(sim808.GPSdata.hour);
    Serial.print(":");
    Serial.print(sim808.GPSdata.minute);
    Serial.print(":");
    Serial.print(sim808.GPSdata.second);
    Serial.print(":");
    Serial.println(sim808.GPSdata.centisecond);

    Serial.print("latitude :");
    Serial.println(sim808.GPSdata.lat, 6);

    sim808.latitudeConverToDMS();
    Serial.print("latitude :");

    Serial.print("longitude :");
    Serial.println(sim808.GPSdata.lon, 6);
    sim808.LongitudeConverToDMS();
    Serial.print("longitude :");
    Serial.print(sim808.longDMS.degrees);
    Serial.print("\'");
    Serial.print(sim808.longDMS.minutes);
    Serial.print("\'");
    Serial.print(sim808.longDMS.seconeds, 6);
    Serial.println("\"");

    Serial.print("speed_kph :");
    Serial.println(sim808.GPSdata.speed_kph);
    Serial.print("heading :");
    Serial.println(sim808.GPSdata.heading);

    //************* Turn off the GPS power ************
    sim808.detachGPS();
  }

  Serial.println("Sending message ...");


  //locationstring = "longditude:" + String(sim808.GPSdata.lon) + "latitude:" + String(sim808.GPSdata.lat);

  locationstring = "lat:" + lati +  "lon:" + longd;
  locationstring.toCharArray(MESSAGE, 53);

  sim808.sendSMS(PHONE_NUMBER, MESSAGE);
  delay(1000);
  Serial.println("Message Sent.");



  delay(10000);


}





void Read_Sensor() {
  fsrReading = analogRead(fsrPin);

  Serial.print("Analog reading = ");
  Serial.print(fsrReading);     // the raw analog reading

  if (fsrReading < 100) {
    Serial.println(" - No pressure");
    worn = false;
  }

  if (fsrReading < 100) {
    worn =  true;
    Serial.println(" - Pussure on sensor");
  }



}
