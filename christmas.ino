#include <SPI.h>                  //  include the head file to enable the  library.

static uint8_t data[4] = {0x0, 0x0, 0x0, 0x0};         // defined a data matrix
static uint8_t i = 1;                                                    // defined a variable vector
const int CE = 10;                                                      // defined  the CE function pin

const int LINE_DELAY = 2; // delay bewtween line print in ms

void write_screen(uint8_t* lines,const int color)                                                  // defined a function called "heart big".
{
  int j;                                                                  
  data[0] = 0xFF;             // color red
  data[1] = 0xFF;             // color green
  data[2] = 0xFF;             // color blue
     
  for ( j = 0; j < 8; j++)
  {
    data[color] = ~lines[j];    // set color 
    data[3] = 0x01 << j ;    // display the data on matrix.
    digitalWrite(CE, LOW);     // when CE is low, it begin to receive data.
    SPI.transfer(data[0]);         //transfer data[0] to the matrix(red)
    SPI.transfer(data[2]);         //transfer data[2] to the matrix(green)
    SPI.transfer(data[1]);        // transfer   data[1] to the matrix(blue)
    SPI.transfer(data[3]);      // tansfer data[3] to the matrix( scanning and display the data on matrix)
    digitalWrite(CE, HIGH);    // when CE is High, means that matrix begin to display the array's information to the matrix.
    delay(LINE_DELAY);                          // a little bit delay, let the led light up and stay for a while so that it looks like it brightness.
  }
};

void matrixoff()
{
  int j;
  for ( j = 0; j < 8; j++)
  {
    data[0] = 0xFF;
    data[1] = 0xFF;
    data[2] = 0xFF;
    data[3] = 0x01 << j ;
    digitalWrite(CE, LOW);
    SPI.transfer(data[0]);
    SPI.transfer(data[2]);
    SPI.transfer(data[1]);
    SPI.transfer(data[3]);
    digitalWrite(CE, HIGH);
    delay(LINE_DELAY);
  }
};

void heartbig()                                                  // defined a function called "heart big".
{                                                                 
  static uint8_t heart[8] = {0x00, 0x66, 0xFF, 0xFF, 0xFF, 0x7E, 0x3C, 0x18};    // you need to calculate which led should be light up by this array, it defined line by line on your matrix, for example , 0x00 means the led of the first line is off,  and the 0x66 means the second line's first led will go off and the fourth led will go off and fifth led will go off and eight led will go off. others will turn on....and so on.
  write_screen(heart,2);
};



void heartsmall()
{
  static uint8_t heart[8] = {0x00, 0x00, 0x24, 0x7E, 0x7E, 0x3C, 0x18, 0x00};          // change the hard to be the smaller one, all you need to do is change this parameter.
  write_screen(heart,1);
};

void tree(int color)
{

  // 00011000
  // 00111100 
  // 01111110
  // 00111100
  // --------
  // 01111110
  // 11111111
  // 00011000
  // 00011000
  static uint8_t tree[8] = {0x20, 0x34, 0x3E, 0xFF, 0xFF, 0x3E, 0x34, 0x20};          // change the hard to be the smaller one, all you need to do is change this parameter.
  write_screen(tree,color);
};


void setup() {
  pinMode(CE, OUTPUT);                          //initialized the pin's mode.
  SPI.begin();                                              // start spi function
}

void loop()                                                  //defined a loop function
{
  const int PRINT_TIME = 100;
  const int OFF_TIME = 100;
  int m = 0;
 
  for ( m = PRINT_TIME; m > 0; m--) {
    tree(0);
  };
  matrixoff();                                          
  delay(OFF_TIME);
  for ( m = PRINT_TIME; m > 0; m--) {
    tree(1);
  };
  matrixoff();
  delay(OFF_TIME);
}
