
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//#include <Fonts/FreeMono9pt7b.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define SSD1306_LCDHEIGHT 64

#define DISPLAY_I2C_ID 10

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

int distanceL = 0;
int distanceC = 0;
int distanceR = 0;
//int distanceCD = 0;

String sensorsDataI2C = "no data...";

void setup()   {
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  //display.setFont(&FreeMono9pt7b);

  Wire.begin(DISPLAY_I2C_ID);
  Wire.onReceive(receiveEvent);
}


void loop() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE, BLACK);
  display.setCursor(0, 0);
  display.println(sensorsDataI2C);
  display.display();
  delay(2000);
}

void receiveEvent(int bytesReceived) {
  sensorsDataI2C = "";
  while ( Wire.available()) {
    sensorsDataI2C += (char)Wire.read();
  }
}
