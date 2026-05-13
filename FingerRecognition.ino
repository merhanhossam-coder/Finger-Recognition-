#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>

// LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Fingerprint sensor
SoftwareSerial fingerSerial(2, 3);  // 2 = RX, 3 = TX
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&fingerSerial);

void setup()
{
  lcd.begin(16, 2);
  lcd.backlight();

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Fingerprint");
  lcd.setCursor(0, 1);
  lcd.print("System Start");
  delay(2000);

  finger.begin(57600);

  if (finger.verifyPassword()) {
    lcd.clear();
    lcd.print("Sensor Ready!");
  } else {
    lcd.clear();
    lcd.print("Sensor ERROR");
    while (1);
  }

  delay(1500);
}

void loop()
{
  lcd.clear();
  lcd.print("1)Enroll");
  lcd.setCursor(0, 1);
  lcd.print("2)Check");

  delay(2000);

  int id = 1; // البصمة اللي هنسجلها رقم 1

  lcd.clear();
  lcd.print("Enroll Finger");
  delay(1500);

  // تسجيل البصمة
  if (getFingerprintEnroll(id)) {
    lcd.clear();
    lcd.print("Enroll Done!");
  } else {
    lcd.clear();
    lcd.print("Enroll Failed");
  }

  delay(2000);

  // التحقق من البصمة
  lcd.clear();
  lcd.print("Place Finger");
  delay(2000);

  int result = getFingerprintID();

  if (result == id) {
    lcd.clear();
    lcd.print("Access Granted");
  } else {
    lcd.clear();
    lcd.print("Denied");
  }

  delay(2000);
}

// تسجيل البصمة
uint8_t getFingerprintEnroll(uint8_t id)
{
  int p = -1;
  lcd.clear();
  lcd.print("Put Finger...");
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
  }

  p = finger.image2Tz(1);
  if (p != FINGERPRINT_OK) return 0;

  lcd.clear();
  lcd.print("Remove Finger");
  delay(2000);

  p = 0;
  while (p != FINGERPRINT_NOFINGER) {
    p = finger.getImage();
  }

  lcd.clear();
  lcd.print("Place Again");
  p = -1;

  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
  }

  p = finger.image2Tz(2);
  if (p != FINGERPRINT_OK) return 0;

  p = finger.createModel();
  if (p != FINGERPRINT_OK) return 0;

  p = finger.storeModel(id);
  if (p == FINGERPRINT_OK)
    return 1;
  else
    return 0;
}

// قراءة البصمة
int getFingerprintID()
{
  int p = finger.getImage();
  if (p != FINGERPRINT_OK) return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK) return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK) return -1;

  return finger.fingerID;
}


