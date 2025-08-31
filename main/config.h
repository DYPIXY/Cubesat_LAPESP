#ifndef CONFIG_H
#define CONFIG_H

//ENDEREÇOS 
#define BME_ADDRESS 0x76
#define MPU_ADDRESS 0x68
#define MPU_BMP_ADDRESS 0x77/0x68

//GPIO, PINOUT, PINS
#define SDA_PIN 22
#define SCL_PIN 21
#define RXD2 16
#define TXD2 17

//CONSTS 
#define SEALEVELPRESSURE_HPA (1013.25) 

//CONFIGS
#define SAMPLES_PER_SECOND 10
#define GPS_BAUD 9600

//LOGGERS
#define BME_LOGGER "(BME)"
#define GY91_MPU_LOGGER "(MPU)"
#define GY91_BMP_LOGGER "(BMP)"

//DTO
struct LapespDTO
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

//END DEFINE
#endif
