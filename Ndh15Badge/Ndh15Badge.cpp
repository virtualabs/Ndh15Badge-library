/**
 * Ndh 2015 Badge
 *
 * Main library file.
 *
 * Defines everything required to have fun with the badge.
 **/

#include "Arduino.h"
#include "../Wire/Wire.h"
#include "Ndh15Badge.h"


/**
 * Constructor.
 *
 * Sets up the pin modes and ADC.
 *
 * Note that the accelerometer must be set in the setup() callback
 * instead of this routine, otherwise it will hang.
 */

Ndh15Badge::Ndh15Badge()
{
}


void Ndh15Badge::begin(void)
{
  /* Initialize I2C. */
  Wire.begin();

  /* Initialize buttons. */
  ADMUX  |= (1<<REFS0); //reference AVCC (5v)
  ADCSRA |= (1<<ADPS2)|(1<<ADPS1); //clockiv 64
  ADCSRA |= (1<<ADEN); //enable ADC

  /* Initialize RGB Led pins. */
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  digitalWrite(LED_RED, HIGH);
  digitalWrite(LED_BLUE, HIGH);
  digitalWrite(LED_GREEN, HIGH);


  /* Initialize buzzer. */
  pinMode(BUZZ, OUTPUT);

  /* Standby to be able to configure. */
  this->accelero_send(0x2A, 0x00);
  delay(10);

  /* 2G full range mode. */
  this->accelero_send(0x0E, B00000000);
  delay(1);

  /* Enable. */
  this->accelero_send(0x2A, B00000001);
  delay(1);

}


/**
 * play
 *
 * Plays a note based on its frequency and duration.
 * A custom Tone lib replacement, but works well.
 */

void Ndh15Badge::play(long freq, long duration)
{
  long delayValue = 1000000 / freq / 2; // calculate the delay value between transitions
  //// 1 second's worth of microseconds, divided by the frequency, then split in half since
  //// there are two phases to each cycle
  long numCycles = freq * duration / 1000; // calculate the number of cycles for proper timing
  //// multiply frequency, which is really cycles per second, by the number of seconds to
  //// get the total number of cycles to produce
  for (long i = 0; i < numCycles; i++) { // for the calculated length of time...
    digitalWrite(BUZZ, HIGH); // write the buzzer pin high to push out the diaphram
    delayMicroseconds(delayValue); // wait for the calculated delay value
    digitalWrite(BUZZ, LOW); // write the buzzer pin low to pull back the diaphram
    delayMicroseconds(delayValue); // wait again or the calculated delay value
  }
}

/**********************************************
 * Capacitive buttons routines
 *********************************************/

/**
 * adc_channel
 *
 * Select channel for ADC.
 **/

void Ndh15Badge::adc_channel(uint8_t channel)
{
  ADMUX &= ~(0b11111);
  ADMUX |=   0b11111 & channel;
}


/**
 * adc_get
 *
 * Get value from ADC for a selected channel.
 **/

uint16_t Ndh15Badge::adc_get(void)
{
    ADCSRA |= (1<<ADSC); //start conversion
    while(!(ADCSRA & (1<<ADIF))); //wait for conversion to finish
    ADCSRA |= (1<<ADIF); //reset the flag
    return ADC; //return value
}


/**
 * touch_measure
 *
 * Measure the capacitance of a given touch.
 **/

uint16_t Ndh15Badge::touch_measure(uint8_t pin)
{
  uint8_t i;
    uint16_t retval;

    retval = 0;

    //Do four measurements and average, just to smooth things out
    for (i=0 ; i<4 ; i++){
        PORTF |= (1 << pin);    // set pullup on
        delay(1);                             // wait (could probably be shorter)
        PORTF &= ~(1 << pin); // set pullup off

        this->adc_channel(0b11111); //set ADC mux to ground;
        this->adc_get();            //do a measurement (to discharge the sampling cap)

        this->adc_channel(pin); //set mux to right channel
        retval +=  adc_get(); //do a conversion
    }
    return retval /4;
}

/**
 * button
 *
 * Detect if a button is pressed or not. This is pure all or nothing logic.
 **/

int Ndh15Badge::button(int pin)
{
  if (pin == BTN_1)
      return (this->touch_measure(pin)<1015);
  else
      return (this->touch_measure(pin) >= 900);
}


/**
 * led
 *
 * Drives the RGB led.
 *
 * RGB values must be in 0-255 range.
 **/

void Ndh15Badge::led(byte red, byte green, byte blue)
{
  analogWrite(LED_RED, 255 - red);
  analogWrite(LED_GREEN, 255 - green);
  analogWrite(LED_BLUE, 255 - blue);
}

/**
 * writeByte
 *
 * Write a byte to the external flash memory at a given page address.
 **/

int Ndh15Badge::writeByte(uint8_t paddr, byte b)
{
  return this->writePage(paddr, &b, 1);
}


/**
 * readByte
 *
 * Read byte from the external flash memory at a given page address.
 **/

byte Ndh15Badge::readByte(uint8_t paddr)
{
  byte b;
  this->readPage(paddr, &b, 1);
  return b;
}

/**
 * writePage
 *
 * Write up to 8 bytes at a given page address to the ext. flash memory.
 **/

int Ndh15Badge::writePage(uint8_t paddr, byte *pdata, int length)
{
  /* Must write between 1 and 8 bytes. */
  if ((length <= 0) || (length > 8))
    return -1;

  /* Write page. */
  Wire.beginTransmission(0x50);
  Wire.write((int)(paddr & 0xFF));
  byte c;
  for (c=0; c<length; c++) {
    Wire.write(pdata[c]);
  }
  Wire.endTransmission();

  /* Wait 6 ms. */
  delay(10);

  return 0;
}


/**
 * readPage
 *
 * Read up to 8 bytes at a given page address to the ext. flash memory.
 **/

int Ndh15Badge::readPage(uint8_t paddr, byte *pdata, int length)
{
  /* Must read between 1 and 8 bytes. */
  if ((length <= 0) || (length > 8))
    return -1;
  Wire.beginTransmission(0x50);
  Wire.write((int)(paddr & 0xFF));  // LSB
  Wire.endTransmission();
  Wire.requestFrom(0x50,length);
  int c = 0;
  //for ( c = 0; c < length; c++ )
  while(c<length)
  {
    if (Wire.available())
      pdata[c++] = Wire.read();
  }
  return c;
}

int Ndh15Badge::readBytes(uint8_t paddr, byte *pdata, int length)
{
    int nb_blocks = length/8;
    int left = length - nb_blocks*8;
    int i;

    /* Read blocks of data. */
    for (i=0;i<(nb_blocks*8);i++)
        if (this->readPage(paddr+i*8, &pdata[i*8], 8) != 8)
            return -1;
    /* Read left bytes. */
    for (i=nb_blocks*8;i<(nb_blocks*8)+left;i++)
        pdata[i] = this->readByte(paddr+i);

    return length;
}

/**
 * accelero_send
 *
 * Internal routine to send commands to the accelerometer.
 **/

void Ndh15Badge::accelero_send(unsigned char reg_addr, unsigned char data)
{
  Wire.beginTransmission(ACCELERO);
  Wire.write(reg_addr);
  Wire.write(data);
  Wire.endTransmission();
}


/**
 * accelero_read
 *
 * Internal routine to get data from the accelerometer.
 **/

void Ndh15Badge::accelero_read(uint8_t reg_addr)
{
  byte ACC_STATUS[7];
  int accel[4];
  int i=0;

  /* Read status from acclerometer. */
  Wire.beginTransmission(ACCELERO);
  Wire.write(reg_addr);
  Wire.endTransmission();
  Wire.requestFrom(ACCELERO, 7);
  for (i=0; i<7; i++)
    ACC_STATUS[i] = Wire.read();

  /* Parse answer. */
  for (i=1; i<7; i=i+2)
  {
    accel[0] = (ACC_STATUS[i+1]|((int)ACC_STATUS[i]<<8))>>6; // X axis
    if (accel[0] > 0x01FF)
      accel[1] = (((~accel[0])+1)- 0xFC00);
    else
      accel[1] = accel[0];
    switch(i)
    {
      case 1:
        this->m_acc_x = accel[1];
        break;

      case 3:
        this->m_acc_y = accel[1];
        break;

      case 5:
        this->m_acc_z = accel[1];
        break;
    }
  }
}


/**
 * accelero_init
 *
 * Initialize the accelerometer. Must be called by the setup() callback.
 **/

/**
 * updateAccel
 *
 * Retrieve data from the accelerometer.
 **/

void Ndh15Badge::updateAccel(void)
{
  /* Read values from accelerometer. */
  this->accelero_read(0x00);
}


/**
 * readX
 *
 * Return the last X-axis value from the accelerometer.
 **/

int Ndh15Badge::readX(void)
{
  return this->m_acc_x;
}


/**
 * readY
 *
 * Return the last Y-axis value from the accelerometer.
 **/

int Ndh15Badge::readY(void)
{
  return this->m_acc_y;
}


/**
 * readZ
 *
 * Return the last Z-axis value from the accelerometer.
 **/

int Ndh15Badge::readZ(void)
{
  return this->m_acc_z;
}

Ndh15Badge Badge = Ndh15Badge();
