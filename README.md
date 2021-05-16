# Soft_I2C_With_FDC1004

### Soft I2C and FDC1004 Capacity Read Example

# Capacitive-Measurement
-----
### About FDC1004, Capacitance method for measuring the level of a fluid.

Capacitive fluid level sensors are measurement devices which typically consist of a single probe which acts as an immersed electrode inside a tank. This probe interacts with an opposite electrode, usually the wall of a tank, and the two are connected together to form a capacitor.

The fluid contents of the tank act as the dielectric medium, which will affect the capacitance created between the two electrodes. If the fluid level rises and falls, this will change the capacitance measured by the probe in a predictable way, and therefore it can be used very effectively as a measurement of fluid level.

-----
### Purpose of this Project

It is also designed to measure software I2C usability. Software I2C is designed as a software independent from hardware, portable, can be integrated to any desired pin. 
Fdc1004 communication is an example and test. 

### How To Use

The created C ++ classes are portable. After you design your own top layer specific to the hardware you want to use, it is enough to integrate the specified SoftI2C_Driver.cpp and SoftI2C_Driver.h into your project. The necessary functions and configurations to be used are specified.

-----
## USEFUL

    Example Sensor          : FDC1004
    Example MCU Architect   : Arm Cortex M3
    Language                : Embedded C++ 
    Communication Interface : Soft I2C
    IDE                     : Suitable for all
    
-----

ali_sahbaz@outlook.com
