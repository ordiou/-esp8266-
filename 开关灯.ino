#define BLINKER_WIFI
#include <Blinker.h>

#include <U8g2lib.h>
#include <Wire.h>

#include <Servo.h>

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R2, U8X8_PIN_NONE);
char auth[] = "34cbeb331e38";
char ssid[] = "nova 6 (5G)-m";
char pswd[] = "qwertyuiop";
volatile int state;
Servo servo_16;
BlinkerButton Button1("dd");
BlinkerButton Button2("ddd");
BlinkerButton Button3("dddd");
BlinkerButton Button4("ddddd");

void page1() {
  u8g2.setFont(u8g2_font_timR08_tf);
  u8g2.setFontPosTop();
  u8g2.setCursor(20,20);
  u8g2.print("conncetion succeeded");
}

void page2() {
  u8g2.setFont(u8g2_font_timR14_tf);
  u8g2.setFontPosTop();
  u8g2.setCursor(10,5);
  u8g2.print(String(Blinker.year()) + String("/") + String(Blinker.month()) + String("/") + String(Blinker.mday()) + String("   ") + String("XM"));
  u8g2.setFont(u8g2_font_ncenB18_tf);
  u8g2.setFontPosTop();
  u8g2.setCursor(20,20);
  u8g2.print(String(Blinker.hour()) + String(":") + String(Blinker.minute()) + String(":") + String(Blinker.second()));
  u8g2.setFont(u8g2_font_timB14_tf);
  u8g2.setFontPosTop();
  switch (state) {
   case 1:
    u8g2.setFont(u8g2_font_timB14_tf);
    u8g2.setFontPosTop();
    u8g2.setCursor(30,50);
    u8g2.print("State:on");
    break;
   case 2:
    u8g2.setFont(u8g2_font_timB14_tf);
    u8g2.setFontPosTop();
    u8g2.setCursor(30,50);
    u8g2.print("State:off");
    break;
   default:
    u8g2.setCursor(10,50);
    u8g2.print("I don't know");
    break;
  }
}

void Button1_callback(const String & blmc) {
  // 关灯
  state = 2;
  Blinker.print("灯已关");
  servo_16.write(0);
  delay(200);
  servo_16.write(90);
  delay(150);
  servo_16.write(180);
  delay(20);
  servo_16.write(90);
  delay(0);
}
void Button2_callback(const String & blmc) {
  servo_16.write(180);
  delay(20);
  servo_16.write(90);
  delay(0);
}
void Button3_callback(const String & blmc) {
  servo_16.write(0);
  delay(20);
  servo_16.write(90);
  delay(0);
}
void Button4_callback(const String & blmc) {
  // 开灯
  state = 1;
  Blinker.print("灯已开");
  servo_16.write(180);
  delay(200);
  servo_16.write(90);
  delay(150);
  servo_16.write(0);
  delay(20);
  servo_16.write(90);
  delay(0);
}

void setup(){
  Serial.begin(115200);
  u8g2.setI2CAddress(0x3C*2);
  u8g2.begin();
  u8g2.firstPage();
  do
  {
    page1();
  }while(u8g2.nextPage());
  delay(1000);
  u8g2.enableUTF8Print();

  Blinker.setTimezone(8.0);
  state = 0;
  Blinker.begin(auth,ssid,pswd);

  servo_16.attach(16);
  Button1.attach(Button1_callback);
  Button2.attach(Button2_callback);
  Button3.attach(Button3_callback);
  Button4.attach(Button4_callback);
}

void loop(){
  Blinker.run();
  u8g2.firstPage();
  do
  {
    page2();
  }while(u8g2.nextPage());

}
