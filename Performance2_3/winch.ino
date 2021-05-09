#define MOTORw_EN 24
#define MOTORw_INA1 25
#define MOTORw_INB1 26
#define MOTORw_PWM 46

#define WINCH_ENC1 2
#define WINCH_ENC2 3

#define WINCH_CS A6
int winch_dir = 0;
int length1 = 0;
int stepsPerRevolution = 1500;
int winch_diameter = 32;
int max_height = 400;
float iu_old, err_old;
int target = 0;
boolean done = false;
int speed_m = 0;







void motor_winch(int pwm_value)
{
  if (pwm_value > 255)
  {
    pwm_value = 255;
    winch_dir = 1;
  }

  if (pwm_value < -255)
  {
    pwm_value = -255;
    winch_dir = -1;
  }

  if (pwm_value > 0)
  {
    digitalWrite(MOTORw_EN, HIGH);
    digitalWrite(MOTORw_INA1, HIGH);
    digitalWrite(MOTORw_INB1, LOW);
    analogWrite(MOTORw_PWM, pwm_value);
  }
  else if (pwm_value == 0)
  {
    digitalWrite(MOTORw_EN, HIGH);
    digitalWrite(MOTORw_INA1, HIGH);
    digitalWrite(MOTORw_INB1, HIGH);
    analogWrite(MOTORw_PWM, pwm_value);
  }
  else
  {
    pwm_value = pwm_value * (-1);
    digitalWrite(MOTORw_EN, HIGH);
    digitalWrite(MOTORw_INA1, LOW);
    digitalWrite(MOTORw_INB1, HIGH);
    analogWrite(MOTORw_PWM, pwm_value);
  }
}

// void winchEncoderEvent() {
//   if (digitalRead(WINCH_ENC1) == HIGH) {
//     if (digitalRead(WINCH_ENC2) == LOW) {
//       winch_enc++;
//     } else {
//       winch_enc--;
//     }
//   } else {
//     if (digitalRead(WINCH_ENC2) == HIGH) {
//       winch_enc--;
//     } else {
//       winch_enc++;
//     }
//   }
// }

void winchEncoderEvent1() {
  // look for a low-to-high on channel A
  if (digitalRead(WINCH_ENC1) == HIGH) {

    // check channel B to see which way encoder is turning
    if (digitalRead(WINCH_ENC2) == LOW) {
      winch_enc++;         // CW
    }
    else {
      winch_enc--;         // CCW
    }
  }

  else   // must be a high-to-low edge on channel A
  {
    // check channel B to see which way encoder is turning
    if (digitalRead(WINCH_ENC2) == HIGH) {
      winch_enc++;          // CW
    }
    else {
      winch_enc--;          // CCW
    }
  }

}

void winchEncoderEvent2() {
  // look for a low-to-high on channel B
  if (digitalRead(WINCH_ENC2) == HIGH) {

    // check channel A to see which way encoder is turning
    if (digitalRead(WINCH_ENC1) == HIGH) {
      winch_enc++;         // CW
    }
    else {
      winch_enc--;         // CCW
    }
  }

  // Look for a high-to-low on channel B

  else {
    // check channel B to see which way encoder is turning
    if (digitalRead(WINCH_ENC1) == LOW) {
      winch_enc++;          // CW
    }
    else {
      winch_enc--;          // CCW
    }
  }
}
float winchGetLength()
{
  length1 = ((3.1415 * winch_diameter) / stepsPerRevolution) * winch_enc;
  return length1;
}

void winch_homing()
{
  int winch_current;
  int start = millis();
  //motor_winch(50);
  //delay(50);
  Serial.println("winch_current:");
  do
  {
    Serial.print("winch_current: ");
    Serial.println(winch_current);
    Serial.print("winch_enc: ");
    Serial.println(winch_enc);
    winch_current = analogRead(WINCH_CS);
    Serial.println(winch_current);
    motor_winch(80);
    delay(100);
  } while (analogRead(WINCH_CS) < 115 );
  //|| 10000 < millis()-start
  motor_winch(0);// останавливаем мотор чтобы робот висел на месте
  winch_enc = 0; //обнуляем энкодер лебедки
}

int move_winch(float height, float max_speed)
{
  float p = 0.4, i = 0.075, d = 3, pu, du, iu, u = 100.0, err = 1000, cur_height;
  height = max_height - height;
  float u1 = 0;
  while (abs(err) > 10)
  {

    if (abs(height) > max_height)height = max_height;
    else height = abs(height);

    cur_height = winchGetLength();
    err = cur_height - height;
    Serial.print("cur_height: ");
    Serial.println(cur_height);
    Serial.print("err: ");
    Serial.println(err);
    err_old = err;
    pu = p * err;
    iu = iu_old + i * err;
    iu_old = iu;
    du = d * (err - err_old);
    u = pu + du + iu;

    Serial.print("u1: ");
    Serial.println(u1);
    Serial.print("u: ");
    Serial.println(u);
    Serial.print("max_speed: ");
    Serial.println(abs(max_speed));
    if (abs(u) > abs(max_speed))
    {
      Serial.println("yes");
      if (u > 0)
      {
        Serial.println(">0");
        u1 = max_speed;
      }
      else
      {
        Serial.println("<0");
        u1 = -max_speed;
      }


    }
    motor_winch(round(u1));
    // Serial.println(cur_height);

  }
  motor_winch(0);
}

void initialize_winch()
{
  pinMode(MOTORw_EN, OUTPUT);
  pinMode(MOTORw_INA1, OUTPUT);
  pinMode(MOTORw_INB1, OUTPUT);
  pinMode(MOTORw_PWM, OUTPUT);

  pinMode(WINCH_ENC1, INPUT);
  pinMode(WINCH_ENC2, INPUT);

  pinMode(WINCH_CS, INPUT);

  attachInterrupt(digitalPinToInterrupt(WINCH_ENC1), winchEncoderEvent1 , CHANGE);
  attachInterrupt(digitalPinToInterrupt(WINCH_ENC2), winchEncoderEvent2 , CHANGE);
}
