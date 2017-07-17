
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"

#define OLED_DC     D3
#define OLED_CS     D4
#define OLED_RESET  D5

#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH  16

Adafruit_SSD1306 display(OLED_DC, OLED_RESET, OLED_CS);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2

#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH  16
static const unsigned char LOGO16_GLCD_BMP[] =
{ 0B00000000, 0B11000000,
  0B00000001, 0B11000000,
  0B00000001, 0B11000000,
  0B00000011, 0B11100000,
  0B11110011, 0B11100000,
  0B11111110, 0B11111000,
  0B01111110, 0B11111111,
  0B00110011, 0B10011111,
  0B00011111, 0B11111100,
  0B00001101, 0B01110000,
  0B00011011, 0B10100000,
  0B00111111, 0B11100000,
  0B00111111, 0B11110000,
  0B01111100, 0B11110000,
  0B01110000, 0B01110000,
  0B00000000, 0B00110000 };

void setup()
{
  Time.zone(-5);

  display.begin(SSD1306_SWITCHCAPVCC);

  display.clearDisplay();   // clears the screen and buffer
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Welcome");
  display.display();
  delay(2000);

  showExamples();

}


void loop()
{
  static int lastSecond = 61;
  if (Time.second() != lastSecond)
  {
    char myTimeString[125] = "";
    const int currentTime = Time.now();
    sprintf(myTimeString, "%02d:%02d:%02d", Time.hour(currentTime), Time.minute(currentTime), Time.second(currentTime));
    display.clearDisplay();   // clears the screen and buffer
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.println(myTimeString);
    display.display();
    lastSecond = Time.second(currentTime);
  }
}

// Examples from the original Adafruit library - https://github.com/pkourany/Adafruit_SSD1306/blob/master/ssd1306_128x64_i2c.ino

void showExamples()
{
  display.clearDisplay();   // clears the screen and buffer

 // draw a single pixel
 display.drawPixel(10, 10, WHITE);
 display.display();
 delay(2000);
 display.clearDisplay();

 // draw many lines
 testdrawline();
 display.display();
 delay(2000);
 display.clearDisplay();

 // draw rectangles
 testdrawrect();
 display.display();
 delay(2000);
 display.clearDisplay();

 // draw multiple rectangles
 testfillrect();
 display.display();
 delay(2000);
 display.clearDisplay();

 // draw mulitple circles
 testdrawcircle();
 display.display();
 delay(2000);
 display.clearDisplay();

 // draw a white circle, 10 pixel radius
 display.fillCircle(display.width()/2, display.height()/2, 10, WHITE);
 display.display();
 delay(2000);
 display.clearDisplay();

 testdrawroundrect();
 delay(2000);
 display.clearDisplay();

 testfillroundrect();
 delay(2000);
 display.clearDisplay();

 testdrawtriangle();
 delay(2000);
 display.clearDisplay();

 testfilltriangle();
 delay(2000);
 display.clearDisplay();

 // draw the first ~12 characters in the font
 testdrawchar();
 display.display();
 delay(2000);
 display.clearDisplay();

 // draw scrolling text
 testscrolltext();
 delay(2000);
 display.clearDisplay();

 // text display tests
 display.setTextSize(1);
 display.setTextColor(WHITE);
 display.setCursor(0,0);
 display.println("Hello, world!");
 display.setTextColor(BLACK, WHITE); // 'inverted' text
 display.println(3.141592);
 display.setTextSize(2);
 display.setTextColor(WHITE);
 display.print("0x"); display.println(0xDEADBEEF, HEX);
 display.display();
 delay(2000);

 // miniature bitmap display
 display.clearDisplay();
 display.drawBitmap(30, 16,  LOGO16_GLCD_BMP, 16, 16, 1);
 display.display();

 // invert the display
 display.invertDisplay(true);
 delay(1000);
 display.invertDisplay(false);
 delay(1000);

 // draw a bitmap icon and 'animate' movement
 //testdrawbitmap(LOGO16_GLCD_BMP, LOGO16_GLCD_HEIGHT, LOGO16_GLCD_WIDTH);
}



void testdrawbitmap(const uint8_t *bitmap, uint8_t w, uint8_t h) {
  uint8_t icons[NUMFLAKES][3];

  // initialize
  for (uint8_t f=0; f< NUMFLAKES; f++) {
    icons[f][XPOS] = random(display.width());
    icons[f][YPOS] = 0;
    icons[f][DELTAY] = random(5) + 1;

    Serial.print("x: ");
    Serial.print(icons[f][XPOS], DEC);
    Serial.print(" y: ");
    Serial.print(icons[f][YPOS], DEC);
    Serial.print(" dy: ");
    Serial.println(icons[f][DELTAY], DEC);
  }

  while (1) {
    // draw each icon
    for (uint8_t f=0; f< NUMFLAKES; f++) {
      display.drawBitmap(icons[f][XPOS], icons[f][YPOS], LOGO16_GLCD_BMP, w, h, WHITE);
    }
    display.display();
    delay(200);

    // then erase it + move it
    for (uint8_t f=0; f< NUMFLAKES; f++) {
      display.drawBitmap(icons[f][XPOS], icons[f][YPOS],  LOGO16_GLCD_BMP, w, h, BLACK);
      // move it
      icons[f][YPOS] += icons[f][DELTAY];
      // if its gone, reinit
      if (icons[f][YPOS] > display.height()) {
	icons[f][XPOS] = random(display.width());
	icons[f][YPOS] = 0;
	icons[f][DELTAY] = random(5) + 1;
      }
    }
   }
}


void testdrawchar(void) {
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);

  for (uint8_t i=0; i < 168; i++) {
    if (i == '\n') continue;
    display.write(i);
    if ((i > 0) && (i % 21 == 0))
      display.println();
  }
  display.display();
}

void testdrawcircle(void) {
  for (int16_t i=0; i<display.height(); i+=2) {
    display.drawCircle(display.width()/2, display.height()/2, i, WHITE);
    display.display();
  }
}

void testfillrect(void) {
  uint8_t color = 1;
  for (int16_t i=0; i<display.height()/2; i+=3) {
    // alternate colors
    display.fillRect(i, i, display.width()-i*2, display.height()-i*2, color%2);
    display.display();
    color++;
  }
}

void testdrawtriangle(void) {
  for (int16_t i=0; i<min(display.width(),display.height())/2; i+=5) {
    display.drawTriangle(display.width()/2, display.height()/2-i,
                     display.width()/2-i, display.height()/2+i,
                     display.width()/2+i, display.height()/2+i, WHITE);
    display.display();
  }
}

void testfilltriangle(void) {
  uint8_t color = WHITE;
  for (int16_t i=min(display.width(),display.height())/2; i>0; i-=5) {
    display.fillTriangle(display.width()/2, display.height()/2-i,
                     display.width()/2-i, display.height()/2+i,
                     display.width()/2+i, display.height()/2+i, WHITE);
    if (color == WHITE) color = BLACK;
    else color = WHITE;
    display.display();
  }
}

void testdrawroundrect(void) {
  for (int16_t i=0; i<display.height()/2-2; i+=2) {
    display.drawRoundRect(i, i, display.width()-2*i, display.height()-2*i, display.height()/4, WHITE);
    display.display();
  }
}

void testfillroundrect(void) {
  uint8_t color = WHITE;
  for (int16_t i=0; i<display.height()/2-2; i+=2) {
    display.fillRoundRect(i, i, display.width()-2*i, display.height()-2*i, display.height()/4, color);
    if (color == WHITE) color = BLACK;
    else color = WHITE;
    display.display();
  }
}

void testdrawrect(void) {
  for (int16_t i=0; i<display.height()/2; i+=2) {
    display.drawRect(i, i, display.width()-2*i, display.height()-2*i, WHITE);
    display.display();
  }
}

void testdrawline() {
  for (int16_t i=0; i<display.width(); i+=4) {
    display.drawLine(0, 0, i, display.height()-1, WHITE);
    display.display();
  }
  for (int16_t i=0; i<display.height(); i+=4) {
    display.drawLine(0, 0, display.width()-1, i, WHITE);
    display.display();
  }
  delay(250);

  display.clearDisplay();
  for (int16_t i=0; i<display.width(); i+=4) {
    display.drawLine(0, display.height()-1, i, 0, WHITE);
    display.display();
  }
  for (int16_t i=display.height()-1; i>=0; i-=4) {
    display.drawLine(0, display.height()-1, display.width()-1, i, WHITE);
    display.display();
  }
  delay(250);

  display.clearDisplay();
  for (int16_t i=display.width()-1; i>=0; i-=4) {
    display.drawLine(display.width()-1, display.height()-1, i, 0, WHITE);
    display.display();
  }
  for (int16_t i=display.height()-1; i>=0; i-=4) {
    display.drawLine(display.width()-1, display.height()-1, 0, i, WHITE);
    display.display();
  }
  delay(250);

  display.clearDisplay();
  for (int16_t i=0; i<display.height(); i+=4) {
    display.drawLine(display.width()-1, 0, 0, i, WHITE);
    display.display();
  }
  for (int16_t i=0; i<display.width(); i+=4) {
    display.drawLine(display.width()-1, 0, i, display.height()-1, WHITE);
    display.display();
  }
  delay(250);
}

void testscrolltext(void) {
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(10,0);
  display.clearDisplay();
  display.println("scroll");
  display.display();

  display.startscrollright(0x00, 0x0F);
  delay(2000);
  display.stopscroll();
  delay(1000);
  display.startscrollleft(0x00, 0x0F);
  delay(2000);
  display.stopscroll();
  delay(1000);
  display.startscrolldiagright(0x00, 0x07);
  delay(2000);
  display.startscrolldiagleft(0x00, 0x07);
  delay(2000);
  display.stopscroll();
}