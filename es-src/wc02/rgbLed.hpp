// 5.b hwdriver

#ifndef _RGB_LED_HPP_
#define _RGB_LED_HPP_

#include <bcm2835.h>
#include <stdbool.h>
#include <stdio.h>

#include "led.hpp"

// De rgb led class
class RgbLed {
    public:
        RgbLed(int pR, int pG, int pB);
        ~RgbLed();
        
        void setRed(void);
        void setGreen(void);
        void setBlue(void);
        void clrRed(void);
        void clrGreen(void);
        void clrBlue(void);
        

    private:
        Led red;
        Led green;
        Led blue;
};

#endif // _RGB_LED_HPP_