/*
Example for Gyro Click

    Date          : Sep 2018.
    Author        : Nenad Filipovic

Test configuration PIC :
    
    MCU             : P18F87K22
    Dev. Board      : EasyPIC PRO v7
    PIC Compiler ver : v7.2.0.0

---

Description :

The application is composed of three sections :

- System Initialization - Initializes I2C, set INT pin as input and RST as output.
- Application Initialization - Initialization driver enable's - I2C, initialize L3GD20 register and start write log.
- Application Task - (code snippet) This is a example which demonstrates the use of Gyro Click board.
     Measured Gyro coordinates ( X-axis, Y-axis, Z-axis ) and temperature in degrees C are being sent
     to the Usart Terminal where you can track their changes.
     All data logs on usb uart for every 2 sec.

Additional Functions :

- UART
- Conversions

*/

#include "Click_Gyro_types.h"
#include "Click_Gyro_config.h"

int16_t gyroX;
int16_t gyroY;
int16_t gyroZ;
float temperature;
char logText[ 15 ] = {0};

void systemInit()
{
    mikrobus_gpioInit( _MIKROBUS1, _MIKROBUS_INT_PIN, _GPIO_INPUT );
    mikrobus_gpioInit( _MIKROBUS1, _MIKROBUS_RST_PIN, _GPIO_OUTPUT );
    mikrobus_i2cInit( _MIKROBUS1, &_GYRO_I2C_CFG[0] );
    mikrobus_logInit( _MIKROBUS2, 9600 );
    Delay_100ms();
}

void applicationInit()
{
    gyro_i2cDriverInit( (T_GYRO_P)&_MIKROBUS1_GPIO, (T_GYRO_P)&_MIKROBUS1_I2C, _GYRO_L3GD20_I2C_ADDRESS );

    // Switch to normal mode and enable all three channels
    gyro_writeData( _GYRO_L3GD20_REGISTER_CTRL_REG1, _GYRO_L3GD20_REG1_NORMAL_MODE );
    // Adjust resolution if requested 250 dps
    gyro_writeData( _GYRO_L3GD20_REGISTER_CTRL_REG4, _GYRO_L3GD20_REG4_250DPS );
    // Set FIFO enable, select INT1
    gyro_writeData( _GYRO_L3GD20_REGISTER_CTRL_REG5, _GYRO_L3GD20_REG5_FIFO_ENABLE_INT1 );
    // Set FIFO is completely filled
    gyro_writeData( _GYRO_L3GD20_REGISTER_FIFO_CTRL_REG, _GYRO_L3GD20_FIFO_CTRL_REG_CONFIG );
    Delay_100ms();

    mikrobus_logWrite( "      GYRO           Temperature", _LOG_LINE );
    mikrobus_logWrite( "-------------------------------------", _LOG_LINE );
}

void applicationTask()
{
    gyro_readGyro(  &gyroX,  &gyroY, &gyroZ );
    Delay_10ms();

    temperature = gyro_readTemperature();
    Delay_10ms();

    mikrobus_logWrite( " Axis X :", _LOG_TEXT );
    IntToStr( gyroX, logText );
    mikrobus_logWrite( logText, _LOG_TEXT );
    mikrobus_logWrite( "  *", _LOG_TEXT );
    mikrobus_logWrite( "******************", _LOG_LINE );


    mikrobus_logWrite( " Axis Y :", _LOG_TEXT );
    IntToStr( gyroY, logText );
    mikrobus_logWrite( logText, _LOG_TEXT );
    mikrobus_logWrite( "  *  ", _LOG_TEXT );
    mikrobus_logWrite( "Temp.:", _LOG_TEXT );
    IntToStr( temperature, logText );
    mikrobus_logWrite( logText, _LOG_TEXT );
    mikrobus_logWrite( "�C *  ", _LOG_LINE );

    mikrobus_logWrite( " Axis Z :", _LOG_TEXT );
    IntToStr( gyroZ, logText );
    mikrobus_logWrite( logText, _LOG_TEXT );
    mikrobus_logWrite( "  *", _LOG_TEXT );
    mikrobus_logWrite( "******************", _LOG_LINE );
    mikrobus_logWrite( "-------------------------------------", _LOG_LINE );

    Delay_1sec();
    Delay_1sec();
}

void main()
{
    systemInit();
    applicationInit();

    while (1)
    {
            applicationTask();
    }
}