#include <bcm2835.h>
#include "led.hpp"

Led::Led() {

}

Led::Led(int pin) {
    this->pin = pin;
}

Led::~Led() {

}

void Led::init(int pin) {
    this->pin = pin;
    this->high = false;
    bcm2835_gpio_fsel(this->pin, BCM2835_GPIO_FSEL_OUTP);
}

int Led::tgl(void) {
    if (this->high)
        bcm2835_gpio_write(this->pin, LOW);
    else
        bcm2835_gpio_write(this->pin, HIGH);
    
    this->high = !this->high;
    return (int) this->high;
}

void Led::on(void) {
    bcm2835_gpio_set(this->pin);
}

void Led::off(void) {
    bcm2835_gpio_clr(this->pin);
}
