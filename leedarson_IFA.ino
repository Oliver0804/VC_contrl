#define LED_1 11
#define LED_2 12

char buff[20] = {0x00};
int buff_flag = 0;
int mode = 0;
byte R = 0, G = 0, B = 0, W = 0;
byte SR = 0, SG = 0, SB = 0, SW = 0;
void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  Serial.println("!");

  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
            digitalWrite(LED_1, HIGH);
            digitalWrite(LED_2, HIGH);
}

void loop() { // run over and over
  buff_flag = 0;
  while (Serial.available()) {
    buff[buff_flag] = Serial.read();
    buff_flag++;
    delay(5);
  }
  /*
    Kitchen lights –(toggle for on/off) - 105
    Bedroom lights - (toggle for on/off) - 107
    Living room lights - (toggle for on/off) - 104
    All lights - (toggle for on/off) - 103
    Change Light to Red - 106
    Change Light to Green - 101
    Change light to Blue - 108
    TV power - 102
  */
  if (buff[0] != 0x00) {
    for (int x = 0; x < 20; x++) {
      //Serial.print(buff[x]);
      if (x == 2) {
        //Serial.print(buff[x]);
        if (buff[x] == '0') {
          Serial.print("!");
        } else if (buff[x] == '1') {
          Serial.print("Change Light to Green");
          SG = 200;
          SW = SR = SB = 0;
        } else if (buff[x] == '2') {
          Serial.print("TV power");
        } else if (buff[x] == '3') {
          Serial.print("All lights");
          if (SW != 0 || SR != 0 || SB != 0 || SG != 0) {
            digitalWrite(LED_1, HIGH);
            digitalWrite(LED_2, HIGH);
            SW = SG = SB = SR = 0;
          } else {
            digitalWrite(LED_1, LOW);
            digitalWrite(LED_2, LOW);
            SW = SG = SB = SR = 230;
          }

        } else if (buff[x] == '4') {
          Serial.print("Living room lights");
          digitalWrite(LED_2, !digitalRead(LED_2));
        } else if (buff[x] == '5') {
          Serial.print("Kitchen lights");
          digitalWrite(LED_1, !digitalRead(LED_1));
        } else if (buff[x] == '6') {
          Serial.print("Change Light to Red");
          SR = 200;
          SW = SB = SG = 0;
        } else if (buff[x] == '7') {
          Serial.print("Bedroom lights");
          if (SW != 0 || SR != 0 || SB != 0 || SG != 0) {
            SW = SR = SB = SR = 0;
          } else {
            SW = SR = SB = SR = 230;
          }
        } else if (buff[x] == '8') {
          Serial.print("Change light to Blue");
          SB = 200;
          SW = SR = SG = 0;
        }
      }
      buff[x] = 0x00;
    }
  }
  if (SR > R) {
    R++;
    analogWrite(3, R);
  } else if (SR < R) {
    R--;
    analogWrite(3, R);
  }

  if (SG > G) {
    G++;
    analogWrite(5, G);
  } else if (SG < G) {
    G--;
    analogWrite(5, G);
  }

  if (SB > B) {
    B++;
    analogWrite(6, B);
  } else if (SB < B) {
    B--;
    analogWrite(6, B);
  }

  if (SW > W) {
    W++;
    analogWrite(9, W);
  } else if (SW < W) {
    W--;
    analogWrite(9, W);
  }
  delay(5);
}

