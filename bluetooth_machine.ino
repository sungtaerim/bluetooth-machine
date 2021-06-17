#include <SoftwareSerial.h>
SoftwareSerial btSerial(BT_TX, BT_RX);

#define JOY_MAX 40
#define SPEED_1      5
#define DIR_1        4
#define SPEED_2      6
#define DIR_2        7
#define BT_TX 13
#define BT_RX 12
#define PARSE_AMOUNT 2

int intData[PARSE_AMOUNT];
boolean recievedFlag;
int dataX, dataY;
boolean getStarted;
byte index;
String string_convert = "";

void setup()
{
  Serial.begin(9600);
  btSerial.begin(9600);
  for (int i = 4; i < 8; i++) {
    pinMode(i, OUTPUT);
  }
}

void loop()
{
  parsing();
  if (recievedFlag) {
    recievedFlag = false;
    dataX = intData[0];
    dataY = intData[1];
    for (byte i = 0; i < PARSE_AMOUNT; i++) {
      Serial.print(intData[i]); Serial.print(" ");
    }
    Serial.println();
    // stop
    if (dataX == 0 && dataY == 0) {
      run(1, 1, 0, 0);
    }

    // up
    if (dataY == 40 && dataX >= -20 && dataX <= 20) {
      run(0, 0, 255, 255);
    }

    // down
    else if (dataY == -40 && dataX >= -20 && dataX <= 20) {
      run(1, 1, 255, 255);
    }

    // right
    else if (dataX == 40 && dataY >= -20 && dataY <= 20) {
      run(1, 0, 250, 50);
    }

    // left
    else if (dataX == -40 && dataY >= -20 && dataY <= 20) {
      run(0, 1, 250, 50);
    }

    // left-down
    else if ((dataX == -40 && dataY <= -20) || (dataY == -40 && dataX <= -20)) {
      run(1, 0, 150, 100);
    }

    // left-up
    else if ((dataX == -40 && dataY <= 20) || (dataY == 40 && dataX <= -20)) {
      run(0, 1, 150, 100);
    }

    // right-up
    else if ((dataX == 40 && dataY >= 20) || (dataY == 40 && dataX >= 20)) {
      run(1, 0, 100, 150);
    }

    // right-down
    else if ((dataX == 40 && dataY <= -20) || (dataY == -40 && dataX >= 20)) {
      run(0, 1, 100, 150);
    }
  }
}

void run(int d1, int d2, int s1, int s2) {
  digitalWrite(DIR_1, d1);
  digitalWrite(DIR_2, d2);
  analogWrite(SPEED_1, s1);
  analogWrite(SPEED_2, s2);
}

void parsing() {
  if (btSerial.available() > 0) {
    char incomingByte = btSerial.read();
    if (getStarted) {
      if (incomingByte != ' ' && incomingByte != ';') {
        string_convert += incomingByte;
      } else {
        intData[index] = string_convert.toInt();
        string_convert = "";
        index++;
      }
    }
    if (incomingByte == '$') {
      getStarted = true;
      index = 0;
      string_convert = "";
    }
    Serial.println(string_convert);
    if (incomingByte == ';') {
      getStarted = false;
      recievedFlag = true;
    }
  }
}
