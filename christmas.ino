#include <SPI.h> //  include the head file to enable the  library.

static uint8_t data[4] = {0x0, 0x0, 0x0, 0x0}; // defined a data matrix
const int CE = 10;                             // defined  the CE function pin

const int LINE_DELAY = 2; // delay bewtween line print in ms

// write_screen prints the content of line to the screen
void write_screen(uint8_t *lines, const int color) {
  int j;
  data[0] = 0xFF; // color red
  data[1] = 0xFF; // color green
  data[2] = 0xFF; // color blue

  for (j = 0; j < 8; j++) {
    if (color == 4) {
      // pseudo white
      data[0] = ~lines[j];
      data[1] = ~lines[j];
      data[2] = ~lines[j];
    } else if (color == 5) {
      // red - pseudo  white
      if (j % 2 == 0) {
        data[0] = ~lines[j];
        data[1] = ~lines[j];
        data[2] = ~lines[j];
      } else {
        data[0] = ~lines[j];
        data[1] = 0xFF;
        data[2] = 0xFF;
      }
    } else {
      data[color] = ~lines[j]; // set color
    }
    data[3] = 0x01 << j;    // choose the line to display data
    digitalWrite(CE, LOW);  // when CE is low, it begin to receive data.
    SPI.transfer(data[0]);  // transfer data[0] to the matrix(red)
    SPI.transfer(data[1]);  // transfer   data[1] to the matrix(green)
    SPI.transfer(data[2]);  // transfer data[2] to the matrix(blue)
    SPI.transfer(data[3]);  // tansfer data[3] to the matrix(active line)
    digitalWrite(CE, HIGH); // when CE is High data is displayed to matrix.
    delay(LINE_DELAY);      // let the led light visible for some time.
  }
}

// matrixoff clean up the screen
void matrixoff() {
  static uint8_t heart[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  write_screen(heart, 4);
}

// heartbig prints a big blue heart
void heartbig() {
  static uint8_t heart[8] = {0x00, 0x66, 0xFF, 0xFF, 0xFF, 0x7E, 0x3C, 0x18};
  write_screen(heart, 2);
}

// heartsmall prints a green heart
void heartsmall() {
  static uint8_t heart[8] = {0x00, 0x00, 0x24, 0x7E, 0x7E, 0x3C, 0x18, 0x00};
  write_screen(heart, 1);
}

// tree prints a tree of the given color
void tree(int color) {
  static uint8_t tree[8] = {0x20, 0x34, 0x3E, 0xFF, 0xFF, 0x3E, 0x34, 0x20};
  write_screen(tree, color);
}

// snow prints a piece of snow of the given color
void snow(int color) {
  static uint8_t snow[8] = {0x81, 0x24, 0x66, 0x18, 0x18, 0x66, 0x24, 0x81};
  write_screen(snow, color);
}

// cross prints a cross of the given color
void cross(int color) {
  static uint8_t cross[8] = {0x04, 0x0a, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40};
  write_screen(cross, color);
}

void setup() {
  pinMode(CE, OUTPUT); // initialized the pin's mode.
  SPI.begin();         // start spi function
}

void loop() // defined a loop function
{
  // number of time the figure will be shown
  const int PRINT_TIME = 100;
  const int OFF_TIME = 100;
  int m = 0;

  // show tree
  for (m = PRINT_TIME; m > 0; m--) {
    tree(2);
  };
  // clean up the screen
  matrixoff();
  // show the off screen
  delay(OFF_TIME);

  for (m = PRINT_TIME; m > 0; m--) {
    cross(5);
  };
  matrixoff();
  delay(OFF_TIME);

  for (m = PRINT_TIME; m > 0; m--) {
    tree(0);
  };
  matrixoff();
  delay(OFF_TIME);

  for (m = PRINT_TIME / 10; m > 0; m--) {
    snow(0);
    delay(2 * LINE_DELAY);
    snow(1);
    delay(2 * LINE_DELAY);
    snow(4);
    delay(2 * LINE_DELAY);
    snow(2);
    delay(2 * LINE_DELAY);
    snow(4);
    delay(2 * LINE_DELAY);
  };
  matrixoff();
  delay(OFF_TIME);
}
