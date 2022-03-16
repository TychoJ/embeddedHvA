// 5.b hwdriver

#ifndef _KNOP_HPP_
#define _KNOP_HPP_

  #include <bcm2835.h>
  #include <stdbool.h>
  #include <stdio.h>

  // De drukknop class
  class Knop {
    public:
      Knop();
      Knop(int pin);
      ~Knop();
      void init(int pin);
      bool pushed();

    private:
      int pin;
  };

#endif // _KNOP_HPP_