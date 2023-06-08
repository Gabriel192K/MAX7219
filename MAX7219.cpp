#include "MAX7219.h"

/*********************************************
Function: MAX7219()
Purpose:  Constructor to MAX7219 class
Input:    Reference to <SPI> class
          Reference to <Data Output Register> of <Slave Select>
          Bit of <Slave Select>
Return:   None
*********************************************/
MAX7219::MAX7219(__SPI__* spi, volatile uint8_t* dorSS, uint8_t bitSS)
{
    this->spi = spi;
    this->dorSS = dorSS;
    this->bitSS = bitSS;
}

/*********************************************
Function: ~MAX7219()
Purpose:  Destructor to MAX7219 class
Input:    None
Return:   None
*********************************************/
MAX7219::~MAX7219()
{
    this->spi = NULL;
    this->dorSS = NULL;
    this->bitSS = 0;
}

/*****************************************
Function: begin()
Purpose:  Initialize MAX7219
Input:    None
Return:   None
*****************************************/
void MAX7219::begin(void)
{
    this->spi->begin();         /* Initialize <SPI> bus */
    this->setDecodeMode(0x00);  /* Set decode mode to not decode data received */
    this->setIntensity(0x0F);   /* Set intensity to maximum */
    this->setScanLimit(0x07);   /* Set scan limit to all 7 segments */
    this->setDisplayTest(0x00); /* Set display test as disabled */
    this->turnOn();             /* Turn on the MAX7219 */
}

/*****************************************
Function: turnOn()
Purpose:  Turn on MAX7219
Input:    None
Return:   None
*****************************************/
void MAX7219::turnOn(void)
{
    this->write(MAX7219_REGISTER_SHUTDOWN, 0x01);
}

/*****************************************
Function: turnOff()
Purpose:  Turn off MAX7219
Input:    None
Return:   None
*****************************************/
void MAX7219::turnOff(void)
{
    this->write(MAX7219_REGISTER_SHUTDOWN, 0x00);
}

/*****************************************
Function: setDecodeMode()
Purpose:  Set decode mode
          0x00 for no decode
          0x01 for decoding digit 0, no decoding for the rest
          0x0F for decoding digits 0-3, no decoding for the rest
          0xFF for decoding all digits
Input:    Decode mode
Return:   None
*****************************************/
void MAX7219::setDecodeMode(uint8_t decodeMode)
{
    this->write(MAX7219_REGISTER_DECODE_MODE, decodeMode);
}

/*****************************************
Function: setIntensity()
Purpose:  Set intensity (max. value 0x0F)
Input:    Intensity
Return:   None
*****************************************/
void MAX7219::setIntensity(uint8_t intensity)
{
    intensity %= 0x10; /* Apply modulo 0x10 to enclose intensity between 0x00 and 0x0F */
    this->write(MAX7219_REGISTER_INTENSITY, intensity);
}

/*****************************************
Function: setScanLimit()
Purpose:  Set scan limit (max. value 0x07)
Input:    Scan limit
Return:   None
*****************************************/
void MAX7219::setScanLimit(uint8_t scanLimit)
{
    scanLimit %= 0x08; /* Apply modulo 0x08 to enclose scanLimit between 0x00 and 0x07 */
    this->write(MAX7219_REGISTER_SCAN_LIMIT, scanLimit);
}

/*****************************************
Function: setDisplayTest()
Purpose:  Set display test (max. value 0x01)
Input:    Display test flag
Return:   None
*****************************************/
void MAX7219::setDisplayTest(uint8_t displayTest)
{
    displayTest %= 0x02; /* Apply modulo 0x02 to enclose displayTest between 0x00 and 0x01 */
    this->write(MAX7219_REGISTER_DISPLAY_TEST, displayTest);
}

/*****************************************
Function: write()
Purpose:  Write data to an availabe register of MAX7219
Input:    Register and data
Return:   None
*****************************************/
void MAX7219::write(uint8_t reg, uint8_t data)
{
    reg %= 0x10;                                  /* Apply modulo 0x10 to enclose register between 0x00 and 0x0F */
    digitalWrite(this->dorSS, this->bitSS, LOW);  /* Hold the <SS> <LOW> */
    this->spi->write(reg);                        /* Write register (<MSB> first) */
    this->spi->write(data);                       /* Write data (<MSB> first) */
    digitalWrite(this->dorSS, this->bitSS, HIGH); /* Hold the <SS> <HIGH> */
}
