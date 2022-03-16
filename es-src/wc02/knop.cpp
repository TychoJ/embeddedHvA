// 5.b hwdriver 

#include <bcm2835.h>
#include "knop.hpp"

Knop::Knop() {

};

Knop::Knop(int pin) {
    this->init(pin);
};

Knop::~Knop() {

};

void Knop::init(int pin) {

  this->pin = pin;
  bcm2835_gpio_fsel(this->pin, BCM2835_GPIO_FSEL_INPT);
  bcm2835_gpio_set_pud(this->pin, BCM2835_GPIO_PUD_UP);
};

bool Knop::pushed() {

  // Knop ingesteld met pull-up, dus ingedrukt is laag
  return bcm2835_gpio_lev(this->pin) == LOW;
};