#ifndef __MAX7219_H__
#define __MAX7219_H__

/* Dependecies */
#include "SPI/SPI.h"
#include "MAX7219 Registers.h"

class MAX7219
{
    public:
        MAX7219(__SPI__* spi, volatile uint8_t* dorSS, uint8_t bitSS);
        ~MAX7219();
        void begin();
        void turnOn        (void);
        void turnOff       (void);
        void setDecodeMode (uint8_t decodeMode);
        void setIntensity  (uint8_t intensity);
        void setScanLimit  (uint8_t scanLimit);
        void setDisplayTest(uint8_t displayTest);
        void write         (uint8_t reg, uint8_t data);
    private:
        __SPI__* spi;
        volatile uint8_t* dorSS;
        uint8_t bitSS;
};

#endif
