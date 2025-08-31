#ifndef CONFIG_H
#define CONFIG_H

class Lapesp
{
    public:
        //Objeto para envio
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

        virtual void setup();
        virtual void data(&LapespDTO data);
}
#endif