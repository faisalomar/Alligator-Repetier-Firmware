#include "Repetier.h"

#if MOTHERBOARD == 501 || MOTHERBOARD == 5001
#include "ExternalDac.h"
#include "SPI.h"

ExternalDac::ExternalDac()
{
    return ;
}

void ExternalDac::begin()
{
    uint8_t externalDac_buf[2] = {0x20,0x00};//all off
    
    WRITE( DAC_SYNC , HIGH );
    WRITE( SPI_EEPROM1_CS , HIGH );
    WRITE( SPI_EEPROM2_CS , HIGH );
    WRITE( SPI_FLASH_CS , HIGH );
    WRITE( SDSS , HIGH );
    SET_OUTPUT(DAC_SYNC);
    HAL::spiBegin();
    
    HAL::delayMicroseconds(1);   
    HAL::delayMicroseconds(1); 
    WRITE( DAC_SYNC , HIGH );
    WRITE( DAC_SYNC , LOW );
    delay(1);
    WRITE( DAC_SYNC , HIGH );
    delay(1);
    WRITE( DAC_SYNC , LOW );
    
    HAL::spiSend(SPI_CHAN_DAC,externalDac_buf , 2);
    return;
}

void ExternalDac::setValueAll(uint8_t value)
{
    uint8_t externalDac_buf[2] = {0x20,0x00};
    
    externalDac_buf[0] |= (value>>4); 
    externalDac_buf[1] |= (value<<4); 
    
    WRITE( DAC_SYNC , HIGH );
    WRITE( SPI_EEPROM1_CS , HIGH );
    WRITE( SPI_EEPROM2_CS , HIGH );
    WRITE( SPI_FLASH_CS , HIGH );
    WRITE( SDSS , HIGH );
    
    HAL::delayMicroseconds(1);
    HAL::delayMicroseconds(1);
    
    WRITE( DAC_SYNC , HIGH );
    WRITE( DAC_SYNC , LOW );
    delay(1);
    WRITE( DAC_SYNC , HIGH );
    delay(1);
    WRITE( DAC_SYNC , LOW );
    
    HAL::spiSend(SPI_CHAN_DAC,externalDac_buf , 2);
    return;
}

void ExternalDac::setValue(uint8_t channel, uint8_t value)
{
    if(channel>=4)
        return;
    
    uint8_t externalDac_buf[2] = {0x10,0x00};
    
    externalDac_buf[0] |= (channel<<6);
    externalDac_buf[0] |= (value>>4); 
    externalDac_buf[1] |= (value<<4); 
    
    WRITE( DAC_SYNC , HIGH );
    WRITE( SPI_EEPROM1_CS , HIGH );
    WRITE( SPI_EEPROM2_CS , HIGH );
    WRITE( SPI_FLASH_CS , HIGH );
    WRITE( SDSS , HIGH );
    
    HAL::delayMicroseconds(1);
    HAL::delayMicroseconds(1);   

    WRITE( DAC_SYNC , HIGH );
    WRITE( DAC_SYNC , LOW );
    delay(1);
    WRITE( DAC_SYNC , HIGH );
    delay(1);
    WRITE( DAC_SYNC , LOW );
    
    HAL::spiSend(SPI_CHAN_DAC,externalDac_buf , 2);
    return;
}
#endif
