/* Wire is required because the badge uses I2C. */
#include <Wire.h>

/* Ndh15 badge library. */
#include <Ndh15Badge.h>


void setup()
{
  /*
  We must initialize the mouse (HID)
  and the badge hardware to work with
  the accelerometer.
  */
  Mouse.begin();
  Badge.begin();
}


void loop()
{
  int8_t x,y;

  /* Asks the accelerometer about the current X/Y/Z values. */
  Badge.updateAccel();

  /* Smooth them a bit while keeping signs. */
  x = (int8_t)(Badge.readX()/32);
  y = (int8_t)(Badge.readY()/32);

  /* Send the mouse move to the computer. */
  Mouse.move(-y,-x);

  /* If the button 1 is pressed, then click. */
  if (Badge.button(BTN_1))
  {
    /* Quick debounce. */
    delay(10);
    if (Badge.button(BTN_1))
      Mouse.click();
  }
}
