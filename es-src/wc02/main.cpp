#include <bcm2835.h>
#include <stdio.h>
#include "rgbLed.hpp"
#include "knop.hpp"

int main(void){

    bcm2835_init();

    printf("Hi, als het goed is wordt er nu met rgb leds gespeeld");
    fflush(stdout);

    Knop stop;
    Knop red;
    Knop green;
    Knop blue;
    RgbLed rgb(RPI_BPLUS_GPIO_J8_11, RPI_BPLUS_GPIO_J8_13, RPI_BPLUS_GPIO_J8_15);

    stop.init(RPI_BPLUS_GPIO_J8_08);
    red.init(RPI_BPLUS_GPIO_J8_03);
    green.init(RPI_BPLUS_GPIO_J8_05);
    blue.init(RPI_BPLUS_GPIO_J8_07);

    while (1) {
        if (stop.pushed()) 
            break;

        if (red.pushed())
            rgb.setRed();
        else
            rgb.clrRed();
        
        if (green.pushed())
            rgb.setGreen();
        else
            rgb.clrGreen();

        if (blue.pushed())
            rgb.setBlue();
        else
            rgb.clrBlue();
    }
}