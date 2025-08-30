#include <Wire.h>
#include <TinyGPS.h>
#include <string>

/*
  GY-GPS6mv2 Slave
  v1.0
*/

// Define the RX and TX pins for Serial 2
#define RXD2 16
#define TXD2 17
#define GPS_BAUD 9600

HardwareSerial gpsSerial(2); // Create an instance of the HardwareSerial class for Serial 2

TinyGPS gps;
float lat, lon;
boolean newData = false;

struct SensorData{
  float lat;
  float lon;
  int satCount;
};

void setup() {
  Wire.begin(8); // join i2c bus with address #8
  Serial.begin(115200);
  gpsSerial.begin(GPS_BAUD, SERIAL_8N1, RXD2, TXD2); // Start Serial 2 with the defined RX and TX pins and a baud rate of 9600

  Wire.onRequest(readGpsData);
  Serial.println("Starting slave I2C bus with address 8");
  Serial.println("Starting slave UART serial with a baud rate of 9600");
  Serial.println("---------------------------------------------------");
}

void loop() {
  delay(100);
}

template <typename T>
void floatToBytesLE(T value, uint8_t* dest) {
  // Organize bytes in LE - Little-endian
  // MSB byte store in the highest memory address
  uint8_t* p = reinterpret_cast<uint8_t*>(&value);
  dest[0] = p[0];
  dest[1] = p[1];
  dest[2] = p[2];
  dest[3] = p[3];
}

void packSensorData(const SensorData& s, uint8_t* buffer) {
    // Pack sensor data into buffer
    floatToBytesLE(s.lat, &buffer[0]);
    floatToBytesLE(s.lon, &buffer[4]);
    floatToBytesLE(s.satCount, &buffer[8]);
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void readGpsData () {
  SensorData s;
  uint8_t buffer[sizeof(SensorData)];

  while (gpsSerial.available() > 0){
    // get the byte data from the GPS
    char gpsData = gpsSerial.read();
    if (gps.encode(gpsData)) {
      newData = true;
    }
  }
  if (newData) {
      float lat, lon;
      int satCount;
      unsigned long age;
      gps.f_get_position(&lat, &lon, &age);

      s.lat = lat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : lat;
      s.lon = lon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : lon;
      s.satCount = gps.satellites() == TinyGPS::GPS_INVALID_SATELLITES ? 0 : gps.satellites();

      Serial.printf("Latitude: %f\n", s.lat);
      Serial.printf("Longitude: %f\n", s.lon);
      Serial.printf("Sats: %d\n", s.satCount);

      // Send bytes
      packSensorData(s, buffer);
      Wire.write(buffer, sizeof(buffer));
      newData = false;
    }
    delay(1000);
}