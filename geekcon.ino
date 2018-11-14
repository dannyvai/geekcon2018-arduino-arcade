#include <TVout.h>
#include <fontALL.h>

#define BUTTON_PIN 4

TVout TV;
unsigned char x,y;
const int lEncoder = 2;    // interrupt 0                                  
volatile unsigned long lpulse = 121;      // width of left encoder pulses in mS
volatile unsigned long ltime;             // remembers time of left  encoders last state change in mS
volatile unsigned long count_pulses = 0;
#define runEvery(t) for (static typeof(t) _lasttime;(typeof(t))((typeof(t))millis() - _lasttime) > (t);_lasttime += (t))

void setup()  {
  x=0;
  y=0;
  TV.begin(PAL);  //for devices with only 1k sram(m168) use TV.begin(_NTSC,128,56)
  TV.select_font(font6x8);
  pinMode(BUTTON_PIN, INPUT);
  digitalWrite(lEncoder,1);                               // enable pullup resistor for left  encoder sensor
  attachInterrupt(0,Lencoder,CHANGE);                     // trigger left  encoder ISR on state change


}


char l1[] = "   __o";
char l2[] = " _ \<_";
char l3[] = "(_)/(_)";


int start_pos = 0;
int button_signal = 0;

void loop() {
  TV.clear_screen();
  x=0;
  y=0;



  for (int i=0; i<start_pos; i++)
  {
    TV.print_char(x*6,y*8,' ');
    x++;
  }
  for (int i=0; i<strlen(l1); i++)
  {
    TV.print_char(x*6,y*8,l1[i]);
    x++;
  }
  y += 1;
  x=0;
  for (int i=0; i<start_pos; i++)
  {
    TV.print_char(x*6,y*8,' ');
    x++;
  }
  for (int i=0; i<strlen(l2); i++)
  {
    TV.print_char(x*6,y*8,l2[i]);
    x++;
  }
  y += 1;
  x=0;
  for (int i=0; i<start_pos; i++)
  {
    TV.print_char(x*6,y*8,'.');
    x++;
  }
  for (int i=0; i<strlen(l3); i++)
  {
    TV.print_char(x*6,y*8,l3[i]);
    x++;
  }
  delay(20);
}


void Lencoder()
{
  lpulse=millis()-ltime;                               // time between last state change and this state change
  ltime=millis();  // update ltime with time of most recent state change
  start_pos = ((start_pos + 1) % 25 );


}
