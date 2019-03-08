![MikroE](http://www.mikroe.com/img/designs/beta/logo_small.png)

---

# Gyro Click

---

- **CIC Prefix**  : GYRO
- **Author**      : Nenad Filipovic
- **Verison**     : 1.0.0
- **Date**        : Sep 2018.

---

### Software Support

We provide a library for the Gyro Click on our [LibStock](https://libstock.mikroe.com/projects/view/553/gyro-click-example) 
page, as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). The demo can run on all the main 
MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

**Library Description**

The library covers all the necessary functions to control Gyro Click.
Library performs the communication with the device via I2C driver by writting to registers and by reading from registers.
Library reads measurements for gyro X-axis, Y-axis & Z-axis coordinates and reads measured temperatuere data from L3GD20 sensor.

Key functions :

- ``` uint8_t gyro_readData( uint8_t address ) ``` - Generic read data function
- ``` void gyro_readGyro( int16_t *gyroX, int16_t *gyroY, int16_t *gyroZ ) ``` - Function read Gyro X-axis, Y-axis and Z-axis
- ``` uint8_t gyro_readTemperature() ``` - Function read temperature

**Examples Description**

The application is composed of three sections :

- System Initialization - Initializes I2C, set INT pin as input and RST as output.
- Application Initialization - Initialization driver enable's - I2C, initialize L3GD20 register and start write log.
- Application Task - (code snippet) This is a example which demonstrates the use of Gyro Click board.
     Measured Gyro coordinates ( X-axis, Y-axis, Z-axis ) and temperature in degrees C are being sent
     to the Usart Terminal where you can track their changes.
     All data logs on usb uart approximately for every 2 sec.


```.c

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
    mikrobus_logWrite( "°C *  ", _LOG_LINE );

    mikrobus_logWrite( " Axis Z :", _LOG_TEXT );
    IntToStr( gyroZ, logText );
    mikrobus_logWrite( logText, _LOG_TEXT );
    mikrobus_logWrite( "  *", _LOG_TEXT );
    mikrobus_logWrite( "******************", _LOG_LINE );
    mikrobus_logWrite( "-------------------------------------", _LOG_LINE );

    Delay_1sec();
    Delay_1sec();
}

```



The full application code, and ready to use projects can be found on our 
[LibStock](https://libstock.mikroe.com/projects/view/553/gyro-click-example) page.

Other mikroE Libraries used in the example:

- I2C
- UART
- Conversions

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](http://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](http://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.

---
---
