#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include <Adafruit_Fingerprint.h>
#include <EEPROM.h>

SoftwareSerial FPSerial(2, 3);  // RX | TX

#if (defined(__AVR__) || defined(ESP8266)) && !defined(__AVR_ATmega2560__)

#else
#define FPSerial Serial1
#endif

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&FPSerial);

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define fifthLED 6
#define forthLED 7
#define thirdLED 8
#define secondLED 9
#define firstLED 10
#define greenLED 11
#define redLED 12
#define buzzer 13

int buttonPin = A0;
int keypadPin = A1;

int Outstanding = EEPROM.read(0);
int Excellent = EEPROM.read(1);
int Very_Good = EEPROM.read(2);
int Good = EEPROM.read(3);
int Fair = EEPROM.read(4);
int total = EEPROM.read(5);

int count=0;
int return_value;
int j;

int VoterListValidate[20];

void setup() {
  Serial.begin(9600);

  finger.begin(57600);

  pinMode(greenLED, OUTPUT);
  pinMode(firstLED, OUTPUT);
  pinMode(secondLED, OUTPUT);
  pinMode(thirdLED, OUTPUT);
  pinMode(forthLED, OUTPUT);
  pinMode(fifthLED, OUTPUT);

  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);

  pinMode(buzzer, OUTPUT);
  
  pinMode(buttonPin, INPUT);
  pinMode(keypadPin, INPUT);

  lcd.init();
  lcd.clear();
  lcd.backlight();
}
String Keypress() {
  int keypad = analogRead(keypadPin);
  if (keypad < 700) {
    digitalWrite(buzzer, HIGH);
    delay(200);
    digitalWrite(buzzer, LOW);

    if (keypad >= 406 && keypad <= 415)
      return "1";
    else if (keypad >= 416 && keypad <= 434)
      return "4";
    else if (keypad >= 435 && keypad <= 443)
      return "2";
    else if (keypad >= 442 && keypad <= 447)
      return "7";
    else if (keypad >= 448 && keypad <= 454)
      return "5";
    else if (keypad >= 454 && keypad <= 470)
      return "*";
    else if (keypad >= 471 && keypad <= 477)
      return "8";
    else if (keypad >= 478 && keypad <= 487)
      return "0";
    else if (keypad >= 504 && keypad <= 513)
      return "3";
    else if (keypad > 513 && keypad <= 523)
      return "6";
    else if (keypad >= 524 && keypad <= 539)
      return "9";
    else if (keypad >= 539 && keypad <= 551)
      return "#";
    else if (keypad >= 552 && keypad <= 557)
      return "A";
    else if (keypad > 557 && keypad <= 567)
      return "B";
    else if (keypad >= 572 && keypad <= 579)
      return "C";
    else if (keypad > 579 && keypad <= 588)
      return "D";
  } else
    return "-1";
}
int Buttonpress() {
  int button = 0;
  do {
    button = analogRead(buttonPin);
    digitalWrite(firstLED, LOW);
    digitalWrite(secondLED, LOW);
    digitalWrite(thirdLED, LOW);
    digitalWrite(forthLED, LOW);
    digitalWrite(fifthLED, LOW);
    if (button > 100) {
      if (button < 200)  // Fifth Button
      {
        lcd.clear();
        lcd.print("5th Button");
        digitalWrite(firstLED, LOW);
        digitalWrite(secondLED, LOW);
        digitalWrite(thirdLED, LOW);
        digitalWrite(forthLED, LOW);
        digitalWrite(fifthLED, HIGH);
        digitalWrite(buzzer, HIGH);
        delay(200);
        digitalWrite(buzzer, LOW);
        delay(100);
        digitalWrite(fifthLED, LOW);
        return 5;
      }

      else if (button < 400)  // Fourth Button
      {
        lcd.clear();
        lcd.print("4th Button");
        digitalWrite(firstLED, LOW);
        digitalWrite(secondLED, LOW);
        digitalWrite(thirdLED, LOW);
        digitalWrite(forthLED, HIGH);
        digitalWrite(fifthLED, LOW);
        digitalWrite(buzzer, HIGH);
        delay(200);
        digitalWrite(buzzer, LOW);
        delay(100);
        digitalWrite(forthLED, LOW);
        return 4;
      } else if (button < 600)  // Third Button
      {
        lcd.clear();
        lcd.print("3rd Button");
        digitalWrite(firstLED, LOW);
        digitalWrite(secondLED, LOW);
        digitalWrite(thirdLED, HIGH);
        digitalWrite(forthLED, LOW);
        digitalWrite(fifthLED, LOW);
        digitalWrite(buzzer, HIGH);
        delay(200);
        digitalWrite(buzzer, LOW);
        delay(100);
        digitalWrite(thirdLED, LOW);
        return 3;
      } else if (button < 800)  // Second Button
      {
        lcd.clear();
        lcd.print("2nd Button");
        digitalWrite(firstLED, LOW);
        digitalWrite(secondLED, HIGH);
        digitalWrite(thirdLED, LOW);
        digitalWrite(forthLED, LOW);
        digitalWrite(fifthLED, LOW);
        digitalWrite(buzzer, HIGH);
        delay(200);
        digitalWrite(buzzer, LOW);
        delay(100);
        digitalWrite(secondLED, LOW);
        return 2;
      } else  // First Button
      {
        lcd.clear();
        lcd.print("1st Button");
        digitalWrite(firstLED, HIGH);
        digitalWrite(secondLED, LOW);
        digitalWrite(thirdLED, LOW);
        digitalWrite(forthLED, LOW);
        digitalWrite(fifthLED, LOW);
        digitalWrite(buzzer, HIGH);
        delay(200);
        digitalWrite(buzzer, LOW);
        delay(100);
        digitalWrite(firstLED, LOW);
        return 1;
      }
    }
  } while (1);
}

void loop() {
  digitalWrite(redLED, HIGH);
  String mode = "";
  lcd.clear();
  lcd.print("Enter Mode: ");
  mode = Keypress();
  if (mode != "-1") {
    lcd.print(mode);
    delay(500);
  }
  delay(1000);
  if (mode == "A") {
    lcd.clear();
    lcd.print("Total Vote: ");
    lcd.print(EEPROM.read(5));
    lcd.setCursor(0, 1);
    lcd.print("Outstanding: ");
    lcd.print(EEPROM.read(0));
    delay(2000);
    lcd.clear();
    lcd.print("Excellent: ");
    lcd.print(EEPROM.read(1));
    lcd.setCursor(0, 1);
    lcd.print("Very Good: ");
    lcd.print(EEPROM.read(2));
    delay(2000);
    lcd.clear();
    lcd.print("Good: ");
    lcd.print(EEPROM.read(3));
    lcd.setCursor(0, 1);
    lcd.print("Fair: ");
    lcd.print(EEPROM.read(4));
    delay(1000);
  } else if (mode == "B") {
    Outstanding = 0;
    Excellent = 0;
    Very_Good = 0;
    Good = 0;
    Fair = 0;
    total = 0;
    count=0;
    EEPROM.update(0, 0);
    EEPROM.update(1, 0);
    EEPROM.update(2, 0);
    EEPROM.update(3, 0);
    EEPROM.update(4, 0);
    EEPROM.update(5, 0);
    lcd.clear();
    lcd.print("Votes Reseted");
    lcd.setCursor(0, 1);
    lcd.print("Successfully!!!");
    for (int i = 0; i < 20; i++) {
      VoterListValidate[i] = 0;
    }
    delay(1000);
  } else if (mode == "C") {
    String Ch = "";
    do {
      int flag = 0, vote;

      lcd.clear();
      lcd.print("Put Your Finger");
      lcd.setCursor(0, 1);
      lcd.print("Press D to Stop");
      Ch = Keypress();
      if (Ch == "B") {
        lcd.clear();
        lcd.print("Exited From");
        lcd.setCursor(0, 1);
        lcd.print("Voting Mode");
      }
      delay(1100);

      return_value = getFingerprintIDez();
      if ((return_value != -1) && (return_value != -3)) {
        digitalWrite(buzzer, HIGH);
        delay(200);
        digitalWrite(buzzer, LOW);
        delay(100);
        for (int i = 0; i < 20; i++) {
          lcd.clear();
          lcd.print("Authentication");
          lcd.setCursor(0, 1);
          lcd.print("In Progress.....");
          if (VoterListValidate[i] == return_value) {
            lcd.clear();
            lcd.print("You Have Already");
            lcd.setCursor(0, 1);
            lcd.print("Voted!!!");
            digitalWrite(buzzer, HIGH);
            digitalWrite(redLED, HIGH);
            delay(200);
            digitalWrite(buzzer, LOW);
            digitalWrite(redLED, LOW);
            delay(100);
            digitalWrite(buzzer, HIGH);
            digitalWrite(redLED, HIGH);
            delay(200);
            digitalWrite(buzzer, LOW);
            digitalWrite(redLED, LOW);
            delay(100);
            digitalWrite(buzzer, HIGH);
            digitalWrite(redLED, HIGH);
            delay(200);
            digitalWrite(buzzer, LOW);
            digitalWrite(redLED, LOW);
            delay(100);
            flag = 1;
            break;
          }
        }
        delay(600);
        if (flag == 1) {
          break;
        }
        lcd.clear();
        lcd.print("Authenticated");
        lcd.setCursor(0, 1);
        lcd.print("Successfully!!!");
        delay(500);
        lcd.clear();
        lcd.print("Give Your Vote");
        digitalWrite(redLED, LOW);
        digitalWrite(greenLED, HIGH);
        vote = Buttonpress();
        digitalWrite(redLED, HIGH);
        digitalWrite(greenLED, LOW);
        if (vote != (-1)) {
          if (vote == 1) {
            lcd.setCursor(0, 1);
            lcd.print("Outstanding");
            Outstanding += 1;
            total += 1;
            VoterListValidate[count] = return_value;
            count+=1;
          }
          if (vote == 2) {
            lcd.setCursor(0, 1);
            lcd.print("Excellent");
            Excellent += 1;
            total += 1;
            VoterListValidate[count] = return_value;
            count+=1;
          }
          if (vote == 3) {
            lcd.setCursor(0, 1);
            lcd.print("Very Good");
            Very_Good += 1;
            total += 1;
            VoterListValidate[count] = return_value;
            count+=1;
          }
          if (vote == 4) {
            lcd.setCursor(0, 1);
            lcd.print("Good");
            Good += 1;
            total += 1;
            VoterListValidate[count] = return_value;
            count+=1;
          }
          if (vote == 5) {
            lcd.setCursor(0, 1);
            lcd.print("Fair");
            Fair += 1;
            total += 1;
            VoterListValidate[count] = return_value;
            count+=1;
          }
          EEPROM.update(0, Outstanding);
          EEPROM.update(1, Excellent);
          EEPROM.update(2, Very_Good);
          EEPROM.update(3, Good);
          EEPROM.update(4, Fair);
          EEPROM.update(5, total);
          delay(1100);
          digitalWrite(redLED, HIGH);
          digitalWrite(greenLED, LOW);
        }
      } else if (return_value == -3) {
        lcd.clear();
        lcd.print("Voter Not Found!");
        delay(200);
        digitalWrite(buzzer, HIGH);
        digitalWrite(redLED, HIGH);
        delay(200);
        digitalWrite(buzzer, LOW);
        digitalWrite(redLED, LOW);
        delay(100);
        digitalWrite(buzzer, HIGH);
        digitalWrite(redLED, HIGH);
        delay(200);
        digitalWrite(buzzer, LOW);
        digitalWrite(redLED, LOW);
        delay(100);
        digitalWrite(buzzer, HIGH);
        digitalWrite(redLED, HIGH);
        delay(200);
        digitalWrite(buzzer, LOW);
        digitalWrite(redLED, LOW);
        delay(100);
      }

    } while (Ch != "D");
  }
}

int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p == FINGERPRINT_OK) {
    uint8_t q = finger.image2Tz();
    if (q == FINGERPRINT_OK) {
      uint8_t r = finger.fingerFastSearch();
      if (r == FINGERPRINT_NOTFOUND)
        return -3;
      if (r == FINGERPRINT_OK)
        return finger.fingerID;
      else
        return -1;
    } else if (q != FINGERPRINT_OK) {
      return -1;
    }
  } else if (p != FINGERPRINT_OK) {
    return -1;
  }
}
