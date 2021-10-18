# arduino-nixie-clock

Hardware List:
- ATmega32U4 5V Pro Micro
- DS1307 RTC
- 2x SN74HC595N Shift Registers
- 4x 74141N Decimal to Binary Converters
- 4x IN-14 Nixie Tubes
- 4x 47K - 50k Resistors
- 12V to 170V Boost Converter
- 12V Power Supply

![Schematic_Nixie Tube Clock v5 0_2021-10-19](https://user-images.githubusercontent.com/34426591/137819292-68213273-f0b6-4289-bc2e-58dc04a71252.png)

In this image you can see how the nixie clock schematic. Missing from which is an RTC clock to keep time, in my case I am using a DS1307 in pins 2 and 3 .
Pins 2 and 3 must be used if using a Pro Micro (like me) as they are the only pins that support I2C.

Arduino pins:
- 2 - SDA on RTC
- 3 - SCL on RTC
- 4, 5, 6 - 1st Shift Register
- 7 ,8 ,9 - 2nd Shift Register
