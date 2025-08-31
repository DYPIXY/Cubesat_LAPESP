#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Adafruit_BMP280.h>
#include <MPU9250_asukiaaa.h>
#include "config.h"

//Objeto para envio
struct esp2esp
{
  //BME
  double BME_TEMP;
  double BME_PRESSURE;
  double BME_ALTITUDE;
  double BME_HUMIDITY;

  //GY MPU9250
  double GY91_BMP_TEMP;
  double GY91_BMP_PRESSURE;
  double GY91_BMP_ALTITUDE;
  double GY91_BMP_;

  //GPS
  double GPS_LAT;
  double GPS_LONG;
  int GPS_COUNT
};


Adafruit_BME280 bme; 
Adafruit_BMP280 bmp; 
MPU9250_asukiaaa mySens;

static float aX, aY, aZ, aSqrt, gX, gY, gZ, mDirection, mX, mY, mZ, bmpInitialPressure, bmeInitialPressure;

void setup() 
{
  Serial.begin(115200);

  //BME280 SETUP
  bme.begin(BME_ADDRESS, &Wire);  
  bmeInitialPressure = bmp.readPressure();

  //GY-91 (MPU9250 e BMP280) SETUP 
  Wire.begin(SDA_PIN, SCL_PIN);
  mySens.setWire(&Wire);
  mySens.beginAccel();
  mySens.beginGyro();
  mySens.beginMag();

  bmp.begin(0x76);
  bmpInitialPressure = bmp.readPressure();
}

void loop() 
{ 
  //BME Handler
  bmeHandler();
  
  //GY-91 Handler
  gyHandler();
  Serial.println();

  //\todo Controle de ciclo

}


void bmeHandler() 
{
  Serial.print(BME_LOGGER);
  Serial.print("%s Temperature: ");
  Serial.print(bme.readTemperature());
  Serial.print(" *C\t");
  
  Serial.print(BME_LOGGER);
  Serial.print("Pressure: ");
  Serial.print(bme.readPressure() / 100.0F);
  Serial.print(" hPa\t");
  
  Serial.print(BME_LOGGER);
  Serial.print("Approx. Altitude: ");
  Serial.print(bme.readAltitude(bmeInitialPressure));
  Serial.println(" m\t");
  
  Serial.print(BME_LOGGER);
  Serial.print("Humidity: ");
  Serial.print(bme.readHumidity());
  Serial.println(" %\t");
}

void gyHandler()
{
  Serial.print(GY91_BMP_LOGGER + "Temperature(°C): " + String(bmp.readTemperature() - 5.0));
  Serial.print(GY91_BMP_LOGGER + "Pressure: " + String(bmp.readPressure() / 100));
  Serial.print(GY91_BMP_LOGGER + "Altitude: " + String(readAltitude(bmpInitialPressure)));
  Serial.print(GY91_MPU_LOGGER);
  if (mySens.accelUpdate() == 0) {
    aX = mySens.accelX();
    aY = mySens.accelY();
    aZ = mySens.accelZ();
    aSqrt = mySens.accelSqrt();
    Serial.print("\taccelX: " + String(aX));
    Serial.print("\taccelY: " + String(aY));
    Serial.print("\taccelZ: " + String(aZ));
    Serial.print("\taccelSqrt: " + String(aSqrt));
  }
  Serial.print(GY91_MPU_LOGGER);
  if (mySens.gyroUpdate() == 0) {
    gX = mySens.gyroX();
    gY = mySens.gyroY();
    gZ = mySens.gyroZ();
    Serial.print("\tgyroX: " + String(gX));
    Serial.print("\tgyroY: " + String(gY));
    Serial.print("\tgyroZ: " + String(gZ));
  }
  Serial.print(GY91_MPU_LOGGER);
  if (mySens.magUpdate() == 0) {
    mX = mySens.magX();
    mY = mySens.magY();
    mZ = mySens.magZ();
    mDirection = mySens.magHorizDirection();
    Serial.print("\tmagX: " + String(mX));
    Serial.print("\tmagY: " + String(mY));
    Serial.print("\tmagZ: " + String(mZ));
    Serial.print("\thorizontalDirection: " + String(mDirection));

    //\todo DMP do MPU
  }
}