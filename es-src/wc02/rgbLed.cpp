#include <bcm2835.h>
#include "rgbLed.hpp"

RgbLed::RgbLed(int pR, int pG, int pB) {
    red.init(pR);
    red.init(pG);
    red.init(pB);
}

RgbLed::~RgbLed() {

}

void RgbLed::setRed(void) {
    this->red.on();
}

void RgbLed::setGreen(void) {
    this->green.on();
}

void RgbLed::setBlue(void) {
    this->blue.on();
}

void RgbLed::clrRed(void) {
    this->red.off();
}

void RgbLed::clrGreen(void) {
    this->green.off();
}

void RgbLed::clrBlue(void) {
    this->blue.off();
}
