#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_GC9A01A.h"


#define TFT_DC  9
#define TFT_CS 10


Adafruit_GC9A01A tft(TFT_CS, TFT_DC);

void setup() {

  tft.begin();

  delay(1000);
  
  testFillScreen();
  delay(500);
  testFilledTriangles();
  delay(500);
  tft.fillScreen(GC9A01A_BLACK);
}
int iterator = 0;
void loop(void) {
  float angl = (float)iterator*2.0*PI/360;
  

  drawTriangleRot(0,-20,-30,-40,0,50,255,0,0,angl);
  drawTriangleRot(0,-20,30,-40,0,50,200,0,0,angl);
  
  drawTriangleRot(-45,-50,45,-50,0,-20,0,0,0,angl);
  drawTriangleRot(30,-40,45,-50,-10,80,0,0,0,angl);
  drawTriangleRot(-30,-40,-45,-50,10,80,0,0,0,angl);
  

  
  iterator = (iterator-4)%360;
  delay(20);
}

void drawTriangleRot(int x1,int y1,int x2,int y2,int x3,int y3,int r,int g,int b,float rotation){
  tft.fillTriangle( (cos(rotation)*x1)-(sin(rotation)*y1)+120, (sin(rotation)*x1)+(cos(rotation)*y1)+120,
                    (cos(rotation)*x2)-(sin(rotation)*y2)+120, (sin(rotation)*x2)+(cos(rotation)*y2)+120,
                    (cos(rotation)*x3)-(sin(rotation)*y3)+120, (sin(rotation)*x3)+(cos(rotation)*y3)+120,
                    tft.color565(r, g, b));
}




unsigned long testFillScreen() {
  unsigned long start = micros();
  tft.fillScreen(GC9A01A_BLACK);
  yield();
  tft.fillScreen(GC9A01A_RED);
  yield();
  tft.fillScreen(GC9A01A_GREEN);
  yield();
  tft.fillScreen(GC9A01A_BLUE);
  yield();
  tft.fillScreen(GC9A01A_BLACK);
  yield();
  return micros() - start;
}

unsigned long testFilledTriangles() {
  unsigned long start, t = 0;
  int           i, cx = tft.width()  / 2 - 1,
                   cy = tft.height() / 2 - 1;

  tft.fillScreen(GC9A01A_BLACK);
  start = micros();
  for(i=min(cx,cy); i>10; i-=5) {
    start = micros();
    tft.fillTriangle(cx, cy - i, cx - i, cy + i, cx + i, cy + i,
      tft.color565(0, i*10, i*10));
    t += micros() - start;
    tft.drawTriangle(cx, cy - i, cx - i, cy + i, cx + i, cy + i,
      tft.color565(i*10, i*10, 0));
    yield();
  }

  return t;
}
