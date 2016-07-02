/* Wire is required because the badge uses I2C. */
#include <Wire.h>

/* Ndh15 badge library. */
#include <Ndh15Badge.h>

void setup()
{
  Badge.begin();
}

void loop() {
  int r=256,g=0,b=0;
  /* RED -> GREEN */
  while (r>0) {
    g++;
    r--;
    Badge.led(r,g,b);
    delay(3);
  }
  /* GREEN -> BLUE */
  while (g>0) {
    b++;
    g--;
    Badge.led(r,g,b);
    delay(3);
  }
  /* BLUE -> RED */
  while (b>0) {
    b--;
    r++;
    Badge.led(r,g,b);
    delay(3);
  }
  
}
