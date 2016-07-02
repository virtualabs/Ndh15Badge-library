/* Wire is required because the badge uses I2C. */
#include <Wire.h>

/* Ndh15 badge library. */
#include <Ndh15Badge.h>

void setup()
{
  Badge.begin();
}

void loop() {
  uint16_t capa;
  
  while (1) {
    capa = Badge.touch_measure(BTN_2);
    if (capa >= 900) {
      capa = capa >> 6;
      Badge.led(capa&0xff,(0xff - capa&0xff),capa&0xff);
    } else {
      Badge.led(0,0,0);
    }
  }

}
