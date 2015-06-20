#ifndef __INC_NDH15BADGE_H
#define __INC_NDH15BADGE_H

#include <inttypes.h>

/**
 * Ndh 2015 Badge Library header.
 *
 * Defines a single class called Ndh15Badge, implementing all the required
 * stuff to have fun with our improved Arduino Micro board.
 **/

#define byte uint8_t

#define ACCELERO  0x1D
#define BUZZ      5
#define LED_BLUE  11
#define LED_RED   9
#define LED_GREEN 10
#define BTN_3     PINF0
#define BTN_2     PINF1
#define BTN_1     PINF4

class Ndh15Badge
{
  public:

    /* Constructor. */
    Ndh15Badge();
    void begin(void);

    /* Capacitive buttons. */
    int button(int btn);
    uint16_t touch_measure(uint8_t pin);

    /* RGB LED */
    void led(byte red, byte green, byte blue);

    /* Buzzer (music). */
    void play(long freq, long duration);

    /* EEPROM management. */
    int writePage(uint8_t paddr, byte *pdata, int length);
    int readPage(uint8_t paddr, byte *pdata, int length);
    int writeByte(uint8_t paddr, byte b);
    byte readByte(uint8_t paddr);
    int readBytes(uint8_t paddr, byte *pdata, int length);
    
    /* Accelerometer. */
    void updateAccel(void);
    int readX(void);
    int readY(void);
    int readZ(void);

  private:

    /* Accelerometer internals. */
    void accelero_send(uint8_t reg_addr, byte data);
    void accelero_read(uint8_t reg_addr);
    int m_acc_x;
    int m_acc_y;
    int m_acc_z;

    /* Capacitive buttons internals. */
    void adc_channel(uint8_t channel);
    uint16_t adc_get(void);

};

extern Ndh15Badge Badge;

#endif /* __INC_NDH15BADGE_H */
