


**System Architecture :**
- Raspberrypi as main controler
- MCP3008 through SPI bus analog digital converter to record sound real time
- PCA9685 through I2C bus to control LEDs using a PWM signal

**Libraries :** 
- libPCA9685 by Edlins : https://github.com/edlins/libPCA9685
- libMCP3008 by endail : https://github.com/endail/MCP3008/tree/05e5eb6638db172df796fe11687f026a7c26f812



**What this program does :**
On a 30 (60?)Hz loop: 
- records a sample of N values (T ms)
- runs a FFT on the sample to evaluate the frequency content
- runs additional anaylises to detect :
    - Beat
    - Drops & Breaks
    - Stands by when the signal is not clear enough  
- Based on the real time  analysis, control LEDs following predefined patterns

**What it should eventually do :**
This paragraph only contains a High Level description of future Functionalities
The detailed TODO list should be developped in the TODO File.



- Add an ability to configure the program without recompiling it.
    --> The animation description should not be written in the code but passed to the programm using a config_file.
    the configuraiton shall be able to set :
        - the list of Animation the program will follow
        - the parameters & special values (loop freq, adc/PWM/DMX channels, etc.)
    --> The rprogram should accept the config_file, read it and extract the list of animation to display.
    --> The config_fil should be easy and comfortable to generate using a desktop application (EXCEL + VBA)

- Add a dual output (DMX AND PCA9685) for genericity with the other elements
