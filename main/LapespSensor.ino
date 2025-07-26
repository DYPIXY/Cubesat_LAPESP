#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Adafruit_BMP280.h>
#include <MPU9250_asukiaaa.h>

#define SEALEVELPRESSURE_HPA (1013.25)
#define SEALEVELPRESSURE (101325.0)

//Endereços 
#define BME_ADDRESS 0x76
#define MPU_ADDRESS 0x68
#define MPU_BMP_ADDRESS 0x77/0x68

#define SDA_PIN 21
#define SCL_PIN 22

Adafruit_BME280 bme; // I2C
Adafruit_BMP280 bmp; // I2C
MPU9250_asukiaaa mySens;

float aX, aY, aZ, aSqrt, gX, gY, gZ, mDirection, mX, mY, mZ, pressure;

void setup() 
{
  Serial.begin(115200);

  //BME280 SETUP
  bme.begin(BME_ADDRESS, &Wire);  

  //GY-91 (MPU9250 e BMP280) SETUP 
  Wire.begin(SDA_PIN, SCL_PIN);
  mySens.setWire(&Wire);
  bmp.begin(0x76);
  pressure = bmp.readPressure();
  mySens.beginAccel();
  mySens.beginGyro();
  mySens.beginMag();
}

void loop() 
{ 
  //BME Handler
  //bmeHandler();
  
  //GY-91 Handler
  gyHandler();
}


void bmeHandler() 
{
  Serial.print("Temperature = ");
  Serial.print(bme.readTemperature());
  Serial.println(" *C");
  
  Serial.print("Pressure = ");
  Serial.print(bme.readPressure() / 100.0F);
  Serial.println(" hPa");
  
  Serial.print("Approx. Altitude = ");
  Serial.print(bme.readAltitude(pressure)); //USANDO A PRESSAO DO BMP DO GY91 COMO REFERENCIA
  Serial.println(" m");
  
  Serial.print("Humidity = ");
  Serial.print(bme.readHumidity());
  Serial.println(" %");
  
  Serial.println();
}

void gyHandler()
{
  Serial.print("Temperature(°C): "); Serial.print(bmp.readTemperature() - 5.0);
  Serial.print("\tPressure: "); Serial.print(bmp.readPressure() / 100);
  Serial.print("\tAltitude: "); Serial.print(bmp.readAltitude(pressure));
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
  if (mySens.gyroUpdate() == 0) {
    gX = mySens.gyroX();
    gY = mySens.gyroY();
    gZ = mySens.gyroZ();
    Serial.print("\tgyroX: " + String(gX));
    Serial.print("\tgyroY: " + String(gY));
    Serial.print("\tgyroZ: " + String(gZ));
  }
  if (mySens.magUpdate() == 0) {
    mX = mySens.magX();
    mY = mySens.magY();
    mZ = mySens.magZ();
    mDirection = mySens.magHorizDirection();
    Serial.print("\tmagX: " + String(mX));
    Serial.print("\tmagY: " + String(mY));
    Serial.print("\tmagZ: " + String(mZ));
    Serial.print("\thorizontalDirection: " + String(mDirection));
  }
  Serial.println();
  delay(200);
}