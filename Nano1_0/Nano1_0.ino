#include <Elephant_Core.h>
#include <Elephant_Utils.h>



#include <SoftwareSerial.h>
SoftwareSerial mySerial(7, 8); // RX, TX
SoftwareSerial mySerial1(5, 6); // RX, TX
// Screen dimentsions
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 128
#define SCLK_PIN 12
#define MOSI_PIN 11
#define DC_PIN   9
#define CS_PIN   10
#define RST_PIN  4


#define  BLACK           0x0000
#define BLUE            0x001F
#define RED             0xF800
#define GREEN           0x07E0
#define CYAN            0x07FF
#define MAGENTA         0xF81F
#define YELLOW          0xFFE0
#define WHITE           0xFFFF

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1351.h>
#include <SPI.h>


Adafruit_SSD1351 tft = Adafruit_SSD1351(SCREEN_WIDTH, SCREEN_HEIGHT, CS_PIN, DC_PIN, MOSI_PIN, SCLK_PIN, RST_PIN);

#include <Elephant_Core.h>
Elephant_Core base(true);

uint16_t markerColors[] = {WHITE, WHITE, GREEN, RED, BLUE};
String markerNames[] = {"Offline", "No marker", "Move", "Stop", "Listen"};
String trics[] = {"High five", "Square", "Flight", "Sit-lie-stand", "Sing", "Youla", "Scare"};
int textSize = 2;

int oldCX = 50;
int oldCY = 50;
int oldSide = 50;
int tric = 50;
long oldTime = 0;
int tric_new = 50;
int oldState = 1;
int m0 = 0;
int m1 = 0;
int m2 = 0;
int m3 = 0;
int old_m0 = 0;
int old_m1 = 0;
int old_m2 = 0;
int old_m3 = 0;
int oldCommand = 0;
int newCommand = 50;
void printText(int xText, int yText, uint16_t color, String str)
{
  int str_len = str.length() + 1;
  char char_array[str_len];
  str.toCharArray(char_array, str_len);
  tft.setCursor(xText, yText);
  tft.setTextColor(color);
  tft.print(char_array);
}

void eraseSymbol(int x, int y)
{
  tft.fillRect(x, y, x + textSize * 5, y + textSize * 8, BLACK);
}

void changeText(int oldN, int newN)
{
  if (oldN != newN) {
    printText(0, 0, BLACK, markerNames[oldN]);
    printText(0, 0, markerColors[newN], markerNames[newN]);
  }
  if (oldCommand != newCommand)
  {
    if (oldCommand == 50)
    {
      printText(0, 25, BLACK, "No command");
    }
    else
    {
      printText(0, 25, BLACK, trics[oldCommand]);
    }
    if (newCommand == 50)
    {
      printText(0, 25, BLUE, "No command");
    }
    else
    {
      printText(0, 25, BLUE, trics[newCommand]);
    }

  }
}
void changeTextNew(int oldN, int newN, int oldM0, int newM0, int oldM1, int newM1, int oldM2, int newM2, int oldM3, int newM3)
{
  if (oldN != newN)
  {
    printText(0, 0, BLACK, markerNames[oldN]);
    printText(0, 0, markerColors[newN], markerNames[newN]);
  }
  printText(20, 20, BLACK, String(oldM0)/*+String(" ")+String(oldM1)+String(" ")+String(oldM2)+String(" ")+String(oldM3)*/);
  delay(5);

  printText(20, 20, YELLOW, String(newM0)/*+String(" ")+String(oldM1)+String(" ")+String(oldM2)+String(" ")+String(oldM3)*/);

}

void marker(int state, int command, int c_x, int c_y, int side) {
  c_x = map(c_x, 0, 240, 0, 128);
  c_y = map(c_y, 0, 240, 0, 128);
  //changeTextNew(oldState, state, old_m0, m0, old_m1, m1, old_m2, m2, old_m3, m3);
  changeText(oldState, state);
  switch (state) {
    case 1:
      if (oldState > 1) {
        tft.drawRect(oldCX - oldSide / 2, oldCY - oldSide / 2, oldSide, oldSide, BLACK);
      }
      break;
    case 2:
      tft.drawRect(oldCX - oldSide / 2, oldCY - oldSide / 2, oldSide, oldSide, BLACK);
      tft.drawRect(c_x - side / 2, c_y - side / 2, side, side, markerColors[state]);
      break;
    case 3:
      tft.drawRect(oldCX - oldSide / 2, oldCY - oldSide / 2, oldSide, oldSide, BLACK);
      tft.drawRect(c_x - side / 2, c_y - side / 2, side, side, markerColors[state]);
      break;
    case 4:
      tft.drawRect(oldCX - oldSide / 2, oldCY - oldSide / 2, oldSide, oldSide, BLACK);
      tft.drawRect(c_x - side / 2, c_y - side / 2, side, side, markerColors[state]);
      break;
  }
  oldCX = c_x;
  oldCY = c_y;
  oldSide = side;
  oldState = state;
}
int convert_x(int x)
{
  return map(x, 0, 128, -64, 64);
}
void getMotors(int num, int x_coord, int side)
{
  int screen_width = 128;
  int u_turn = 0;
  int u_straight = 0;
  int u = 0;
  int ud_s = 0;
  int ud_t = 0;
  float k_turn = 2.0;
  float k_straight = 2.5;
  float kd_s = 0.0;
  float kd_t = 0.0;
  int e_straight = 0;
  int e_turn = 0;
  int errold_s = 0;
  int errold_t = 0;
  
  int motors[] = {0, 0, 0, 0};

  //printText(0, 20, BLACK, String(u_turn));


  old_m0 = m0;
  old_m1 = m1;
  old_m2 = m2;
  old_m3 = m3;
  if (num == 0)
  {
    motors[0] = 0;
    motors[1] = 0;
    motors[2] = 0;
    motors[3] = 0;
  }
  if (num == 1)
  {
    motors[0] = 0;
    motors[1] = 0;
    motors[2] = 0;
    motors[3] = 0;
  }
  if (num == 2)
  {
    newCommand = 50;
    e_turn = convert_x(x_coord);
    //printText(0, 30, WHITE, String(e_turn));
    //delay(10);
    //printText(0, 30, BLACK,String(e_turn));
    e_straight = -55 + side;
    
    ud_s = (e_straight - errold_s)*kd_s;
    ud_t = (e_turn - errold_t)*kd_t;
    u_straight = e_straight * k_straight+ud_s;
    u_turn = e_turn * k_turn+ud_t;
    errold_s = e_straight;
    errold_t = e_turn;
    //u = u_straight + u_turn;

    //u_curr = u_turn;
    //u_turn = 0;
    motors[0] = u_turn + u_straight;
    motors[1] = u_turn - u_straight;
    motors[2] = u_turn + u_straight;
    motors[3] = u_turn - u_straight;
    for (byte i = 0; i < 4; i++)
    {
      
      if (motors[i] < -250)
      {
        motors[i] = -250;
      }
      if (motors[i] > 250)
      {
        motors[i] = 250;
      }

      //old_u = u_turn;
    }
    if (num == 3)
    {
      motors[0] = 0;
      motors[1] = 0;
      motors[2] = 0;
      motors[3] = 0;

    }




  }
  if (num == 4)
  {
    motors[0] = 0;
    motors[1] = 0;
    motors[2] = 0;
    motors[3] = 0;
  }
  
  
  m0 = motors[0];
  m1 = motors[1];
  m2 = motors[2];
  m3 = motors[3];
  motors[0] = map(m0, -250, 250, 0, 250);
  motors[1] = map(m1, -250, 250, 0, 250);
  motors[2] = map(m2, -250, 250, 0, 250);
  motors[3] = map(m3, -250, 250, 0, 250);
  
  mySerial.write(motors[0]);
  mySerial.write(motors[1]);
  mySerial.write(motors[2]);
  mySerial.write(motors[3]);
  mySerial1.write(tric);
  mySerial.write(255);

  //delay(20);
}
int x = 0;
int w = 0;
int target = 0;
int old_u = 0;
int u_curr  = 0;
int voice = 50;
void setup(void) {
  //tft.init(240, 240);   // initialize a ST7789 chip, 240x240 pixels
  tft.begin();        // initialize a SSD1351 chip, 128x128 pixels
  tft.fillScreen(BLACK);
  Serial.begin(115200);
  tft.setTextSize(textSize);
  marker(0, 50, 0, 0, 50);
  delay(1000);
  mySerial.begin(115200);
  mySerial1.begin(115200);
}

void loop() {
  if (Serial.available() > 0)
  {
    oldTime = millis();
    int data = Serial.read();
    if (base.detectCommand(data, COMMAND_RPI_COLOR_BOX))
    {
      printText(60, 60, BLACK, String(oldCommand));
     
      newCommand = base.getVoice();
      tric = newCommand;
      printText(60, 60, YELLOW, String(newCommand));
      marker(base.getColor(), newCommand, base.getX(), base.getY(), base.getSide());

      Serial.write(newCommand);
      target = base.getColor();

      w = base.getSide();
      x = map(base.getX(), 0, 240, 0, 128);
    }
  }
  if (oldTime > 0 && (millis() - oldTime > 1000)) {
    marker(0, 50, 0, 0, 50);
  }
  getMotors(target, x, w);

  oldCommand = newCommand;
}
