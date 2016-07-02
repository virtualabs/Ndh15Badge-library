/* Wire is required because the badge uses I2C. */
#include <Wire.h>

/* Ndh15 badge library. */
#include <Ndh15Badge.h>
#include "notes.h"

void setup()
{
  Badge.begin();
}

/* Dirty port of an arduino code to Ndh15Badge lib. */
void tone(int pin, float freq, float duration) {
  Badge.play(freq, duration);
}

void loop()
{
    tone(8,LA3,Q); 
    delay(1+Q); //delay duration should always be 1 ms more than the note in order to separate them.
    tone(8,LA3,Q);
    delay(1+Q);
    tone(8,LA3,Q);
    delay(1+Q);
    tone(8,F3,E+S);
    delay(1+E+S);
    tone(8,C4,S);
    delay(1+S);
    
    tone(8,LA3,Q);
    delay(1+Q);
    tone(8,F3,E+S);
    delay(1+E+S);
    tone(8,C4,S);
    delay(1+S);
    tone(8,LA3,H);
    delay(1+H);
    
    tone(8,E4,Q); 
    delay(1+Q); 
    tone(8,E4,Q);
    delay(1+Q);
    tone(8,E4,Q);
    delay(1+Q);
    tone(8,F4,E+S);
    delay(1+E+S);
    tone(8,C4,S);
    delay(1+S);
    
    tone(8,Ab3,Q);
    delay(1+Q);
    tone(8,F3,E+S);
    delay(1+E+S);
    tone(8,C4,S);
    delay(1+S);
    tone(8,LA3,H);
    delay(1+H);
    
    tone(8,LA4,Q);
    delay(1+Q);
    tone(8,LA3,E+S);
    delay(1+E+S);
    tone(8,LA3,S);
    delay(1+S);
    tone(8,LA4,Q);
    delay(1+Q);
    tone(8,Ab4,E+S);
    delay(1+E+S);
    tone(8,G4,S);
    delay(1+S);
    
    tone(8,Gb4,S);
    delay(1+S);
    tone(8,E4,S);
    delay(1+S);
    tone(8,F4,E);
    delay(1+E);
    delay(1+E);//PAUSE
    tone(8,Bb3,E);
    delay(1+E);
    tone(8,Eb4,Q);
    delay(1+Q);
    tone(8,D4,E+S);
    delay(1+E+S);
    tone(8,Db4,S);
    delay(1+S);
    
    tone(8,C4,S);
    delay(1+S);
    tone(8,B3,S);
    delay(1+S);
    tone(8,C4,E);
    delay(1+E);
    delay(1+E);//PAUSE QUASI FINE RIGA
    tone(8,F3,E);
    delay(1+E);
    tone(8,Ab3,Q);
    delay(1+Q);
    tone(8,F3,E+S);
    delay(1+E+S);
    tone(8,LA3,S);
    delay(1+S);
    
    tone(8,C4,Q);
    delay(1+Q);
     tone(8,LA3,E+S);
    delay(1+E+S);
    tone(8,C4,S);
    delay(1+S);
    tone(8,E4,H);
    delay(1+H);
    
     tone(8,LA4,Q);
    delay(1+Q);
    tone(8,LA3,E+S);
    delay(1+E+S);
    tone(8,LA3,S);
    delay(1+S);
    tone(8,LA4,Q);
    delay(1+Q);
    tone(8,Ab4,E+S);
    delay(1+E+S);
    tone(8,G4,S);
    delay(1+S);
    
    tone(8,Gb4,S);
    delay(1+S);
    tone(8,E4,S);
    delay(1+S);
    tone(8,F4,E);
    delay(1+E);
    delay(1+E);//PAUSE
    tone(8,Bb3,E);
    delay(1+E);
    tone(8,Eb4,Q);
    delay(1+Q);
    tone(8,D4,E+S);
    delay(1+E+S);
    tone(8,Db4,S);
    delay(1+S);
    
    tone(8,C4,S);
    delay(1+S);
    tone(8,B3,S);
    delay(1+S);
    tone(8,C4,E);
    delay(1+E);
    delay(1+E);//PAUSE QUASI FINE RIGA
    tone(8,F3,E);
    delay(1+E);
    tone(8,Ab3,Q);
    delay(1+Q);
    tone(8,F3,E+S);
    delay(1+E+S);
    tone(8,C4,S);
    delay(1+S);
    
    tone(8,LA3,Q);
    delay(1+Q);
    tone(8,F3,E+S);
    delay(1+E+S);
    tone(8,C4,S);
    delay(1+S);
    tone(8,LA3,H);
    delay(1+H);
    
    delay(2*H);
}
