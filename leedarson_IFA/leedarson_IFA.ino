#define LED_1 11
#define LED_2 12
#define PWM_VAL 100
char buff[20] = {0x00};
int buff_flag = 0;
int mode = 0;
#define GPIO_R  3
#define GPIO_G  5
#define GPIO_B  6
#define GPIO_W  9

byte R = 0, G = 0, B = 0, W = 0;
byte SR = 0, SG = 0, SB = 0, SW = 0;
void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  Serial.println("Ok");

  pinMode(GPIO_R, OUTPUT);
  pinMode(GPIO_G, OUTPUT);
  pinMode(GPIO_B, OUTPUT);
  pinMode(GPIO_W, OUTPUT);
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  digitalWrite(LED_1, HIGH);
  digitalWrite(LED_2, HIGH);
}

void loop() { // run over and over
  buff_flag = 0;
  while (Serial.available()) {
    buff[buff_flag] = Serial.read();
    Serial.print((char)buff[buff_flag]);
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
      if (x == 0) {
        if (buff[x] == '1' && buff[x + 1] != '0' && buff_flag < 3 ) {
          Serial.println("!");
          for (int color = 0; color < 10; color++) {
            analogWrite(GPIO_R, color);
            analogWrite(GPIO_G, color);
            analogWrite(GPIO_B, color);
            analogWrite(GPIO_W, color);
            delay(20);
          }
          for (int color = 20; color > -1; color--) {
            analogWrite(GPIO_R, color);
            analogWrite(GPIO_G, color);
            analogWrite(GPIO_B, color);
            analogWrite(GPIO_W, color);
            delay(20);
          }
          analogWrite(GPIO_R, SR);
          analogWrite(GPIO_G, SG);
          analogWrite(GPIO_B, SB);
          analogWrite(GPIO_W, SW);
        }
      }
      if (x == 2) {
        Serial.println("");
        //Serial.print(buff[x]);
        if (buff[x] == '0') {
          Serial.print("!");
        } else if (buff[x] == '1') {
          Serial.print("Change Light to Green");
          SG = PWM_VAL;
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
            SW = SG = SB = SR = PWM_VAL;
          }

        } else if (buff[x] == '4') {
          Serial.print("Living room lights");
          digitalWrite(LED_2, !digitalRead(LED_2));
        } else if (buff[x] == '5') {
          Serial.print("Kitchen lights");
          digitalWrite(LED_1, !digitalRead(LED_1));
        } else if (buff[x] == '6') {
          Serial.print("Change Light to Red");
          SR = PWM_VAL;
          SW = SB = SG = 0;
        } else if (buff[x] == '7') {
          Serial.print("Bedroom lights");
          if (SW != 0 || SR != 0 || SB != 0 || SG != 0) {
            SW = SR = SB = SR = 0;
          } else {
            SW = SR = SB = SR = PWM_VAL;
          }
        } else if (buff[x] == '8') {
          Serial.print("Change light to Blue");
          SB = PWM_VAL;
          SW = SR = SG = 0;
        }
      }

      buff[x] = 0x00;
    }
  }
  if (SR > R) {
    R++;
    analogWrite(GPIO_R, R);
  } else if (SR < R) {
    R--;
    analogWrite(GPIO_R, R);
  }

  if (SG > G) {
    G++;
    analogWrite(GPIO_G, G);
  } else if (SG < G) {
    G--;
    analogWrite(GPIO_G, G);
  }

  if (SB > B) {
    B++;
    analogWrite(GPIO_B, B);
  } else if (SB < B) {
    B--;
    analogWrite(GPIO_B, B);
  }

  if (SW > W) {
    W++;
    analogWrite(GPIO_W, W);
  } else if (SW < W) {
    W--;
    analogWrite(GPIO_W, W);
  }
  delay(5);
}

