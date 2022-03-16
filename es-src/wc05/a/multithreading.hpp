// 5.a multithreading

//TODO: juiste #ifndef en #define toevoegen
#ifndef _MULTITHREADING_HPP_
#define _MULTITHREADING_HPP_
  
  #include <cstdbool>
  #include <stdio.h>
  #include <time.h>
  //TODO: zorg dat headerfile pthread ook geladen wordt
  #include <pthread.h>
  
  // Maak #define voor handige delay-functie in msec
  #define thread_delay(nMSec) \
  { \
    struct timespec oTime, oTimeLeft; \
    oTime.tv_sec = 0; \
    oTime.tv_nsec = (nMSec) * 1000000L; \
    nanosleep(&oTime, &oTimeLeft); \
  };

  // Mijn threads
  extern bool _bRunning;
  void *ThreadLetters(void* pThreadData);
  void *ThreadOptellen(void* pThreadData);

#endif // _MULTITHREADING_HPP_