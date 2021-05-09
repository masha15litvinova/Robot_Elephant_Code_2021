bool is_started = false;

int val = 0;
int val_old = 0;
bool plus = false;
bool minus = false;
int val1 = 0;
int val2 = 0;
int val_start = 0;
bool gyro = false;
void gyro_init()
{
  int val1 = 0;
  long timer = millis();
  int f = 0;
  int f1 = 0;

  int old_f = 0;
  while ((millis() - timer) < 10000)
  {
    if (Serial3.available())
    {
      f = Serial3.read();
      Serial.println("val_read = " + String(f));

      Serial.println("doing init...");
    }
  }
  while (digitalRead(39) == 0)
  {
    if (Serial3.available())
    {
      Serial.println("button");
      f = Serial3.read();
      if (abs(f) > 10)
      {
        gyro = true;
      }
      old_f = f;
      f1 = map(f, 0, 255, 0, 360);
      Serial.println("val_read_map = " + String(f1));
      Serial.println("doing init...");

    }
  }
  val_start = f1;

  Serial.println("-----------");
  Serial.println("val_start = " + String(val_start));
  val2 = 0;
}
int convert_val(int x)
{
  Serial.println("x = " + String(x));

  x = x - val_start;

  //x= x-180;
  /*if ((x >= 0) and (x <= 180))
    {
    x = x;
    }
    else
    {
    x = x - 360;
    }*/
  //x = map(x, 0, 360, -180, 180);
  int x1 = x + 360;
  int x2 = x;
  int x3 = x - 360;
  if (abs(x1) < 180)
  {
    x = x1;
  }
  if (abs(x2) < 180)
  {
    x = x2;
  }
  if (abs(x3) < 180)
  {
    x = x3;
  }
  Serial.println("convert_x = " + String(x));
  return x ;
}
void go_angle(int new_angle, int m1, int m2, int m3, int m4)
{
  if (gyro)
  {
    turn_angle(new_angle);
    bool is_begin = false;
    while (!is_begin)
    {
      if (Serial3.available())
      {
        val = Serial3.read();
        val1 = map(val, 0, 255, 0, 360);
        val_old = val1;

        val2 = convert_val(val1);
        Serial.println("!!!!!!!!!!!!!!!!!");
        Serial.println("val_begin = " + String(val));
        Serial.println("!!!!!!!!!!!!!!!!!");

        is_begin = true;
      }

    }
    float up = 0;
    float ud = 0;
    float ui = 0.;
    float kp = 1.3;
    float kd = 3;
    float ki = 0.000000;
    int u_m = 0;
    int u = 0;
    int err = new_angle - val2;
    int errold = new_angle - val2;


    if (Serial3.available())
    {

      val = Serial3.read();
      val1 = map(val, 0, 255, 0, 360);

      val2 = convert_val(val1);

    }
    err = -new_angle + val2;
    up = err * kp;
    ud = (err - errold) * kd;
    ui = ui + ki * err;
    errold = err;
    u = up + ud + ui;
    u_m = round(u);

    motorsGo(u_m + m1, u_m + m2, u_m + m3, u_m + m4);
  }
}

void go_angle_msec(int msec, int new_angle, int m1, int m2, int m3, int m4)
{
  if (gyro)
  {
   turn_angle(new_angle);
    bool is_begin = false;
    while (!is_begin)
    {
      if (Serial3.available())
      {
        val = Serial3.read();
        val1 = map(val, 0, 255, 0, 360);
        val_old = val1;

        val2 = convert_val(val1);
        Serial.println("!!!!!!!!!!!!!!!!!");
        Serial.println("val_begin = " + String(val));
        Serial.println("!!!!!!!!!!!!!!!!!");

        is_begin = true;
      }

    }
    float up = 0;
    float ud = 0;
    float ui = 0.;
    float kp = 1.3;
    float kd = 3;
    float ki = 0.0000;
    int u_m = 0;
    int u = 0;
    int err = new_angle - val2;
    int errold = new_angle - val2;

    long time_begin = millis();
    while (millis() - time_begin < msec)
    {

       if (Serial3.available())
    {

      val = Serial3.read();
      val1 = map(val, 0, 255, 0, 360);

      val2 = convert_val(val1);

    }
    err = -new_angle + val2;
    up = err * kp;
    ud = (err - errold) * kd;
    ui = ui + ki * err;
    errold = err;
    u = up + ud + ui;
    u_m = round(u);

    motorsGo(u_m + m1, u_m + m2, u_m + m3, u_m + m4);
    }
    motorsGo(0, 0, 0, 0);
  }
}
void turn_angle(int new_angle)
{
  if (gyro)
  {
    Serial.println("val_begin = " + String(val));
    bool is_begin = false;
    while (!is_begin)
    {
      if (Serial3.available())
      {
        val = Serial3.read();
        val1 = map(val, 0, 255, 0, 360);
        val_old = val1;

        val2 = convert_val(val1);
        Serial.println("!!!!!!!!!!!!!!!!!");
        Serial.println("val_begin = " + String(val));
        Serial.println("!!!!!!!!!!!!!!!!!");

        is_begin = true;
      }

    }





    int err = new_angle - val2;
    int errold = new_angle - val2;
    float up = 0;
    float ud = 0;
    float ui = 0.;
    float kp = 0.6;
    float kd = 3;
    float ki = 0.01;
    int u = 0;
    int u_m = 0;

    while (abs(err) > 2)
    {

      if (Serial3.available())
      {

        val = Serial3.read();


        //Serial.println("val = " + String(val));
        val1 = map(val, 0, 255, 0, 360);

        val_old = val1;

        //Serial.println("val_read_map = " + String(val1));
        val2 = convert_val(val1);
        // Serial.println("val_start = " + String(val_start));
        Serial.println(val2);
      }
      err = -new_angle + val2;
      up = err * kp;
      ud = (err - errold) * kd;
      ui = ui + ki * err;
      errold = err;
      u = up + ud + ui;
      u_m = round(u);
      motorsGo(u_m, u_m, u_m, u_m);
      //Serial.println("val = "+String(val));
      //Serial.println("err = " + String(err));
      // Serial.println("target = "+String(new_angle));
      // Serial.println("u = " + String(u));
      delay(1);
    }
    motorsGo(0, 0, 0, 0);
    Serial.println("-----------------------------------------------");
    Serial.println("end turn");
    Serial.println("-----------------------------------------------");
  }
}
void test_gyro()
{
  delay(300);
  while(digitalRead(39) == 0)
  {
    go_angle(0,0,0,0,0);
    }
  }
