#include "temps.h"

long unsigned decalage = 0;

long unsigned maintenant() { return decalage+clock(); }

void millisleep(unsigned long i) {
  struct timeval tim;
  tim.tv_sec = 0;
  tim.tv_usec =  i * 1000;
  decalage += i*une_milliseconde;
  select(0, NULL, NULL, NULL, &tim);
}
