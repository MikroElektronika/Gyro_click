/*
    __gyro_driver.h

-----------------------------------------------------------------------------

  This file is part of mikroSDK.
  
  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

----------------------------------------------------------------------------- */

/**
@file   __gyro_driver.h
@brief    Gyro Driver
@mainpage Gyro Click
@{

@image html libstock_fb_view.jpg

@}

@defgroup   GYRO
@brief      Gyro Click Driver
@{

| Global Library Prefix | **GYRO** |
|:---------------------:|:-----------------:|
| Version               | **1.0.0**    |
| Date                  | **Sep 2018.**      |
| Developer             | **Nenad Filipovic**     |

*/
/* -------------------------------------------------------------------------- */

#include "stdint.h"

#ifndef _GYRO_H_
#define _GYRO_H_

/** 
 * @macro T_GYRO_P
 * @brief Driver Abstract type 
 */
#define T_GYRO_P    const uint8_t*

/** @defgroup GYRO_COMPILE Compilation Config */              /** @{ */

//  #define   __GYRO_DRV_SPI__                            /**<     @macro __GYRO_DRV_SPI__  @brief SPI driver selector */
   #define   __GYRO_DRV_I2C__                            /**<     @macro __GYRO_DRV_I2C__  @brief I2C driver selector */                                          
// #define   __GYRO_DRV_UART__                           /**<     @macro __GYRO_DRV_UART__ @brief UART driver selector */ 

                                                                       /** @} */
/** @defgroup GYRO_VAR Variables */                           /** @{ */

extern const uint8_t _GYRO_L3GD20_I2C_ADDRESS;

extern const uint8_t _GYRO_L3GD20_REGISTER_WHO_AM_I;
extern const uint8_t _GYRO_L3GD20_REGISTER_CTRL_REG1;
extern const uint8_t _GYRO_L3GD20_REGISTER_CTRL_REG2;
extern const uint8_t _GYRO_L3GD20_REGISTER_CTRL_REG3;
extern const uint8_t _GYRO_L3GD20_REGISTER_CTRL_REG4;
extern const uint8_t _GYRO_L3GD20_REGISTER_CTRL_REG5;
extern const uint8_t _GYRO_L3GD20_REGISTER_REFERENCE;
extern const uint8_t _GYRO_L3GD20_REGISTER_OUT_TEMP;
extern const uint8_t _GYRO_L3GD20_REGISTER_STATUS_REG;
extern const uint8_t _GYRO_L3GD20_REGISTER_OUT_X_L;
extern const uint8_t _GYRO_L3GD20_REGISTER_OUT_X_H;
extern const uint8_t _GYRO_L3GD20_REGISTER_OUT_Y_L;
extern const uint8_t _GYRO_L3GD20_REGISTER_OUT_Y_H;
extern const uint8_t _GYRO_L3GD20_REGISTER_OUT_Z_L;
extern const uint8_t _GYRO_L3GD20_REGISTER_OUT_Z_H;
extern const uint8_t _GYRO_L3GD20_REGISTER_FIFO_CTRL_REG;
extern const uint8_t _GYRO_L3GD20_REGISTER_FIFO_SRC_REG;
extern const uint8_t _GYRO_L3GD20_REGISTER_INT1_CFG;
extern const uint8_t _GYRO_L3GD20_REGISTER_INT1_SRC;
extern const uint8_t _GYRO_L3GD20_REGISTER_TSH_XH;
extern const uint8_t _GYRO_L3GD20_REGISTER_TSH_XL;
extern const uint8_t _GYRO_L3GD20_REGISTER_TSH_YH;
extern const uint8_t _GYRO_L3GD20_REGISTER_TSH_YL;
extern const uint8_t _GYRO_L3GD20_REGISTER_TSH_ZH;
extern const uint8_t _GYRO_L3GD20_REGISTER_TSH_ZL;
extern const uint8_t _GYRO_L3GD20_REGISTER_INT1_DURATION;
extern const uint8_t _GYRO_L3GD20_REG1_NORMAL_MODE;
extern const uint8_t _GYRO_L3GD20_REG4_250DPS;
extern const uint8_t _GYRO_L3GD20_REG5_FIFO_ENABLE_INT1;
extern const uint8_t _GYRO_L3GD20_FIFO_CTRL_REG_CONFIG;

                                                                       /** @} */
/** @defgroup GYRO_TYPES Types */                             /** @{ */



                                                                       /** @} */
#ifdef __cplusplus
extern "C"{
#endif

/** @defgroup GYRO_INIT Driver Initialization */              /** @{ */

#ifdef   __GYRO_DRV_SPI__
void gyro_spiDriverInit(T_GYRO_P gpioObj, T_GYRO_P spiObj);
#endif
#ifdef   __GYRO_DRV_I2C__
void gyro_i2cDriverInit(T_GYRO_P gpioObj, T_GYRO_P i2cObj, uint8_t slave);
#endif
#ifdef   __GYRO_DRV_UART__
void gyro_uartDriverInit(T_GYRO_P gpioObj, T_GYRO_P uartObj);
#endif


/** @defgroup GYRO_FUNC Driver Functions */                   /** @{ */


/**
 * @brief Generic write data function
 *
 * @param[in] address         Register address
 *
 * @param[in] writeCommand    Command to write
 *
 * Function write byte of data to L3GD20.
 */
void gyro_writeData( uint8_t address, uint8_t writeCommand );

/**
 * @brief Generic read data function
 *
 * @param[in] address         Register address
 *
 * @return    Data from addressed register in L3GD20
 *
 * Function read byte of data from register address of L3GD20.
 */
uint8_t gyro_readData( uint8_t address );

/**
 * @brief Function get low and high register data
 *
 * @param[in] adrRegLow         low data register address
 *
 * @param[in] adrRegHigh         high data register address
 *
 * @return         16-bit value ( low and high data )
 *
 * Function get data from two L3GD20 register.
 */
int16_t gyro_getAxis( uint8_t adrRegHigh );

/**
 * @brief Function read axis
 *
 * @param[out] gyroX             pointer to read Gyro X-axis data
 * @param[out] gyroY             pointer to read Gyro Y-axis data
 * @param[out] gyroZ             pointer to read Gyro Z-axis data
 *
 * Function read Gyro X-axis, Y-axis and Z-axis axis.
 *
 */
void gyro_readGyro( int16_t *gyroX, int16_t *gyroY, int16_t *gyroZ );

/**
 * @brief Function read temperature data in degrees [ °C ]
 *
 * @return         temperature in degrees [ °C ]
 *
 * Function read temperature data.
 */
uint8_t gyro_readTemperature();




                                                                       /** @} */
#ifdef __cplusplus
} // extern "C"
#endif
#endif

/**
    @example Click_Gyro_STM.c
    @example Click_Gyro_TIVA.c
    @example Click_Gyro_CEC.c
    @example Click_Gyro_KINETIS.c
    @example Click_Gyro_MSP.c
    @example Click_Gyro_PIC.c
    @example Click_Gyro_PIC32.c
    @example Click_Gyro_DSPIC.c
    @example Click_Gyro_AVR.c
    @example Click_Gyro_FT90x.c
    @example Click_Gyro_STM.mbas
    @example Click_Gyro_TIVA.mbas
    @example Click_Gyro_CEC.mbas
    @example Click_Gyro_KINETIS.mbas
    @example Click_Gyro_MSP.mbas
    @example Click_Gyro_PIC.mbas
    @example Click_Gyro_PIC32.mbas
    @example Click_Gyro_DSPIC.mbas
    @example Click_Gyro_AVR.mbas
    @example Click_Gyro_FT90x.mbas
    @example Click_Gyro_STM.mpas
    @example Click_Gyro_TIVA.mpas
    @example Click_Gyro_CEC.mpas
    @example Click_Gyro_KINETIS.mpas
    @example Click_Gyro_MSP.mpas
    @example Click_Gyro_PIC.mpas
    @example Click_Gyro_PIC32.mpas
    @example Click_Gyro_DSPIC.mpas
    @example Click_Gyro_AVR.mpas
    @example Click_Gyro_FT90x.mpas
*/                                                                     /** @} */
/* -------------------------------------------------------------------------- */
/*
  __gyro_driver.h

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