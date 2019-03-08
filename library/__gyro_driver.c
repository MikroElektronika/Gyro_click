/*
    __gyro_driver.c

-----------------------------------------------------------------------------

  This file is part of mikroSDK.

  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

----------------------------------------------------------------------------- */

#include "__gyro_driver.h"
#include "__gyro_hal.c"

/* ------------------------------------------------------------------- MACROS */



/* ---------------------------------------------------------------- VARIABLES */

#ifdef   __GYRO_DRV_I2C__
static uint8_t _slaveAddress;
#endif

// I2C device address
const uint8_t _GYRO_L3GD20_I2C_ADDRESS                        = 0x6B;

// Register address
/* Device identification register */
const uint8_t _GYRO_L3GD20_REGISTER_WHO_AM_I                  = 0x0F;

/* Set CTRL_REG1 (0x20)
 ====================================================================
 BIT  Symbol    Description                                   Default
 ---  ------    --------------------------------------------- -------
 7-6  DR1/0     Output data rate                                   00
 5-4  BW1/0     Bandwidth selection                                00
   3  PD        0 = Power-down mode, 1 = normal/sleep mode          0
   2  ZEN       Z-axis enable (0 = disabled, 1 = enabled)           1
   1  YEN       Y-axis enable (0 = disabled, 1 = enabled)           1
   0  XEN       X-axis enable (0 = disabled, 1 = enabled)           1 
*/
const uint8_t _GYRO_L3GD20_REGISTER_CTRL_REG1                 = 0x20;

/* Set CTRL_REG2 (0x21)
 ====================================================================
 BIT  Symbol    Description                                   Default
 ---  ------    --------------------------------------------- -------
 5-4  HPM1/0    High-pass filter mode selection                    00
 3-0  HPCF3..0  High-pass filter cutoff frequency selection      0000 
*/
const uint8_t _GYRO_L3GD20_REGISTER_CTRL_REG2                 = 0x21;

/* Set CTRL_REG3 (0x22)
 ====================================================================
 BIT  Symbol    Description                                   Default
 ---  ------    --------------------------------------------- -------
   7  I1_Int1   Interrupt enable on INT1 (0=disable,1=enable)       0
   6  I1_Boot   Boot status on INT1 (0=disable,1=enable)            0
   5  H-Lactive Interrupt active config on INT1 (0=high,1=low)      0
   4  PP_OD     Push-Pull/Open-Drain (0=PP, 1=OD)                   0
   3  I2_DRDY   Data ready on DRDY/INT2 (0=disable,1=enable)        0
   2  I2_WTM    FIFO wtrmrk int on DRDY/INT2 (0=dsbl,1=enbl)        0
   1  I2_ORun   FIFO overrun int on DRDY/INT2 (0=dsbl,1=enbl)       0
   0  I2_Empty  FIFI empty int on DRDY/INT2 (0=dsbl,1=enbl)         0 
*/
const uint8_t _GYRO_L3GD20_REGISTER_CTRL_REG3                 = 0x22;

/* Set CTRL_REG4 (0x23)
 ====================================================================
 BIT  Symbol    Description                                   Default
 ---  ------    --------------------------------------------- -------
   7  BDU       Block Data Update (0=continuous, 1=LSB/MSB)         0
   6  BLE       Big/Little-Endian (0=Data LSB, 1=Data MSB)          0
 5-4  FS1/0     Full scale selection                               00
                                00 = 250 dps
                                01 = 500 dps
                                10 = 2000 dps
                                11 = 2000 dps
   0  SIM       SPI Mode (0=4-wire, 1=3-wire)                       0
*/
const uint8_t _GYRO_L3GD20_REGISTER_CTRL_REG4                 = 0x23;

/* Set CTRL_REG5 (0x24)
 ====================================================================
 BIT  Symbol    Description                                   Default
 ---  ------    --------------------------------------------- -------
   7  BOOT      Reboot memory content (0=normal, 1=reboot)          0
   6  FIFO_EN   FIFO enable (0=FIFO disable, 1=enable)              0
   4  HPen      High-pass filter enable (0=disable,1=enable)        0
 3-2  INT1_SEL  INT1 Selection config                              00
 1-0  OUT_SEL   Out selection config                               00
*/
const uint8_t _GYRO_L3GD20_REGISTER_CTRL_REG5                 = 0x24;

/* REFERENCE register */
const uint8_t _GYRO_L3GD20_REGISTER_REFERENCE                 = 0x25;

/* Temperature data */
const uint8_t _GYRO_L3GD20_REGISTER_OUT_TEMP                  = 0x26;

/* Status register */
const uint8_t _GYRO_L3GD20_REGISTER_STATUS_REG                = 0x27;

/* X-axis angular rate data low */
const uint8_t _GYRO_L3GD20_REGISTER_OUT_X_L                   = 0x28;

/* X-axis angular rate data high */
const uint8_t _GYRO_L3GD20_REGISTER_OUT_X_H                   = 0x29;

/* Y-axis angular rate data low */
const uint8_t _GYRO_L3GD20_REGISTER_OUT_Y_L                   = 0x2A;

/* Y-axis angular rate data high */
const uint8_t _GYRO_L3GD20_REGISTER_OUT_Y_H                   = 0x2B;

/* Z-axis angular rate data low */
const uint8_t _GYRO_L3GD20_REGISTER_OUT_Z_L                   = 0x2C;

/* Z-axis angular rate data high */
const uint8_t _GYRO_L3GD20_REGISTER_OUT_Z_H                   = 0x2D;

/* FIFO mode configuration  */
const uint8_t _GYRO_L3GD20_REGISTER_FIFO_CTRL_REG             = 0x2E;

/* Set FIFO_SRC_REG (0x2F)
 ====================================================================
 BIT  Symbol    Description                                   Default
 ---  ------    --------------------------------------------- -------
   7  WTM       Watermark status (0=lower, 1=higher)                0
   6  OVRN      Overrun bit status (0=not, 1=completely)            0
   5  EMPTY     Empty bit                                           0
 4-0  FSS       FIFO stored data level                          00000
*/
const uint8_t _GYRO_L3GD20_REGISTER_FIFO_SRC_REG              = 0x2F;

/* Interrupt config register  */
const uint8_t _GYRO_L3GD20_REGISTER_INT1_CFG                  = 0x30;

/* Interrupt source register  */
const uint8_t _GYRO_L3GD20_REGISTER_INT1_SRC                  = 0x31;

/* Interrupt threshold X-axis high */
const uint8_t _GYRO_L3GD20_REGISTER_TSH_XH                    = 0x32;

/* Interrupt threshold X-axis low */
const uint8_t _GYRO_L3GD20_REGISTER_TSH_XL                    = 0x33;

/* Interrupt threshold Y-axis high */
const uint8_t _GYRO_L3GD20_REGISTER_TSH_YH                    = 0x34;

/* Interrupt threshold Y-axis low */
const uint8_t _GYRO_L3GD20_REGISTER_TSH_YL                    = 0x35;

/* Interrupt threshold Z-axis high */
const uint8_t _GYRO_L3GD20_REGISTER_TSH_ZH                    = 0x36;

/* Interrupt threshold Z-axis low */
const uint8_t _GYRO_L3GD20_REGISTER_TSH_ZL                    = 0x37;

/* Interrupt duration value */
const uint8_t _GYRO_L3GD20_REGISTER_INT1_DURATION             = 0x38;

// Configuration bits
/* Switch to normal mode and enable all three channels */
const uint8_t _GYRO_L3GD20_REG1_NORMAL_MODE                   = 0x0F;

/* Adjust resolution if requested 250 dps */
const uint8_t _GYRO_L3GD20_REG4_250DPS                        = 0x00;

/* Set FIFO enable, select INT1 */
const uint8_t _GYRO_L3GD20_REG5_FIFO_ENABLE_INT1              = 0x50;

/* Set FIFO is completely filled */
const uint8_t _GYRO_L3GD20_FIFO_CTRL_REG_CONFIG               = 0x40;

/* -------------------------------------------- PRIVATE FUNCTION DECLARATIONS */



/* --------------------------------------------- PRIVATE FUNCTION DEFINITIONS */



/* --------------------------------------------------------- PUBLIC FUNCTIONS */

#ifdef   __GYRO_DRV_SPI__

void gyro_spiDriverInit(T_GYRO_P gpioObj, T_GYRO_P spiObj)
{
    hal_spiMap( (T_HAL_P)spiObj );
    hal_gpioMap( (T_HAL_P)gpioObj );

    // ... power ON
    // ... configure CHIP
}

#endif
#ifdef   __GYRO_DRV_I2C__

void gyro_i2cDriverInit(T_GYRO_P gpioObj, T_GYRO_P i2cObj, uint8_t slave)
{
    _slaveAddress = slave;
    hal_i2cMap( (T_HAL_P)i2cObj );
    hal_gpioMap( (T_HAL_P)gpioObj );

    // ... power ON
    // ... configure CHIP
}

#endif
#ifdef   __GYRO_DRV_UART__

void gyro_uartDriverInit(T_GYRO_P gpioObj, T_GYRO_P uartObj)
{
    hal_uartMap( (T_HAL_P)uartObj );
    hal_gpioMap( (T_HAL_P)gpioObj );

    // ... power ON
    // ... configure CHIP
}

#endif


/* ----------------------------------------------------------- IMPLEMENTATION */


/* Generic write data function */
void gyro_writeData( uint8_t address, uint8_t writeCommand )
{
    uint8_t buffer[ 2 ];
    buffer[ 0 ] = address;
    buffer[ 1 ] = writeCommand;

    hal_i2cStart();
    hal_i2cWrite( _slaveAddress, buffer, 2, END_MODE_STOP );
}

/* Generic read data function */
uint8_t gyro_readData( uint8_t address )
{
    uint8_t writeReg[ 1 ];
    uint8_t readReg[ 1];

    writeReg[ 0 ] = address;

    hal_i2cStart();
    hal_i2cWrite( _slaveAddress, writeReg, 1, END_MODE_RESTART );
    hal_i2cRead( _slaveAddress, readReg, 1, END_MODE_STOP );

    return readReg[ 0 ];
}

/* Function get data from L3GD20 register */
int16_t gyro_getAxis( uint8_t adrRegLow )
{
    uint16_t result;
    uint8_t buffer[ 2 ];

    buffer[ 0 ] = gyro_readData( adrRegLow );
    buffer[ 1 ] = gyro_readData( adrRegLow + 1 );

    result = buffer[ 1 ];
    result <<= 8;
    result |= buffer[ 0 ];

    return result;
}

/* Function read Gyro X-axis, Y-axis and Z-axis axis */
void gyro_readGyro( int16_t *gyroX, int16_t *gyroY, int16_t *gyroZ )
{
    *gyroX = gyro_getAxis( _GYRO_L3GD20_REGISTER_OUT_X_L );
    *gyroY = gyro_getAxis( _GYRO_L3GD20_REGISTER_OUT_Y_L );
    *gyroZ = gyro_getAxis( _GYRO_L3GD20_REGISTER_OUT_Z_L );
}

/* Function read temperature */
uint8_t gyro_readTemperature()
{
    uint8_t hexValue;
    uint8_t buffer[ 2 ];
    uint8_t temperature;
    
    hexValue = gyro_getAxis( _GYRO_L3GD20_REGISTER_OUT_TEMP );
    
    buffer[ 0 ] = hexValue  / 10;
    buffer[ 1 ] = hexValue  % 10;
    
    temperature = 40 - ( buffer[ 0 ] * 16 + buffer[ 1 ] * 1 );
    
    return temperature;

}



/* -------------------------------------------------------------------------- */
/*
  __gyro_driver.c

  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.

3. All advertising materials mentioning features or use of this software
   must display the following acknowledgement:
   This product includes software developed by the MikroElektonika.

4. Neither the name of the MikroElektonika nor the
   names of its contributors may be used to endorse or promote products
   derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY MIKROELEKTRONIKA ''AS IS'' AND ANY
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL MIKROELEKTRONIKA BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

----------------------------------------------------------------------------- */