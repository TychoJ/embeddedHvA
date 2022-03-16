// 5.b hwdriver

#ifndef _LED_HPP_
#define _LED_HPP_

  #include <bcm2835.h>
  #include <stdbool.h>
  #include <stdio.h>

  // De led class
class Led {    
    public:
        Led();
        Led(int pin);
        ~Led();
        void init(int pin);
        int tgl(void);
        void on(void);
        void off(void);
    
    private:
        int pin;
        bool high;
};

#endif // _LED_HPP_