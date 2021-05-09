uint32_t tmr;
boolean flag;
int servos_angles[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};  //текущие положения сервомоторов (в углах)
int servos_old_angles[] = {75, 75, 85, 75, 70, 75, 75, 75, 75, 85, 60, 75, 75, 75}; //положения серв на предыдущей позиции (в углах)
int AVG_angles[] = {70, 75, 85, 75, 70, 85, 75, 75, 75, 85, 55, 75, 155, 25}; //средние положение серв (в углах) -- слон стоит на 4 лапах


int speeds_default[] = {60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60};
long speeds[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
float accels_default[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
int module (int n)
{
  int k = 0;
  if (n > 0)
  {
    k = n;
  }
  else
  {
    k = (-1) * n;
  }
  return k;
}
void set_servos_speeds(long *speeds_array) //задание скоростей всем 12 сервам через массив
{
  Serial.println(" ");
  Serial.println("Speeds:");
  for (byte i = 0; i < 14; i++)
  {
    servos[i].setSpeed(speeds_array[i]);
    Serial.print(String(speeds_array[i]) + " ");
  }
  Serial.println(" ");

}

void set_servos_accels(float *accels_array) //задание ускорений всем 12 сервам через массив
{
  Serial.println(" ");
  Serial.println("Accels:");
  for (byte i = 0; i < 14; i++)
  {
    servos[i].setAccel(accels_array[i]);
    Serial.print(String(accels_array[i]) + " ");
  }


  Serial.println(" ");
}

void servos_begin() //инициализация всех сервомоторов
{


  //set_servos_speeds(speeds_default);
  //set_servos_accels(accels_default);
  /*for (byte i = 0; i < 12; i++)
    {
    servos[i].setSpeed(65);
    }*/
  Serial.println(" ");
  Serial.println("Servos begin!");
  for (byte i = 0; i < 14; i++)
  {
    Serial.println("delay");

    //servos[i].attach(i, MIN_real[i], MAX_real[i]);
    servos[i].attach(i, AVG_angles[i]);

   // servos[i].smoothStart();

    Serial.println("Servo " + String(i) + " start");
    //Serial.println("Servo " + String(i) + " attached on " + String(MIN_pwm[i]) + " = min " + String(MAX_pwm[i]) + " = max");

  }
}

void servos_go(int angles[], float sec)
{
  for (byte i = 0; i < 12; i++)
  {
    //Serial.println("Servos_old_angles[" + String(i) + "] = " + String(servos_old_angles[i]));

    //Serial.println("angles[" + String(i) + "] = " + String(angles[i]));
    long k = abs(angles[i] - servos_old_angles[i]);
    //Serial.println("k ="  + String(k));
    speeds[i] = round(k  / sec);
    //Serial.println("Speeds[" + String(i) + "] = " + String(speeds[i]));

  }
  set_servos_speeds(speeds);
  tmr = millis();
  flag = false;
  for (byte i = 0; i < 12; i++)
  {
    servos[i].setTargetDeg(flag ? 0 : angles[i]);
  }
  while (millis() - tmr < sec * 1000)
  {


    for (byte i = 0; i <= 11; i++)
    {

      servos[i].tickManual();
      delay(1);

      //Serial.println("tick()");
    }
    //Serial.println("moving");

  }

  for (byte i = 0; i < 12; i++)
  {
    servos[i].setCurrentDeg(angles[i]);
  }
  set_old_angles(servos_angles[0], servos_angles[1], servos_angles[2], servos_angles[3], servos_angles[4], servos_angles[5], servos_angles[6], servos_angles[7], servos_angles[8], servos_angles[9], servos_angles[10], servos_angles[11]);

}
void ears_move(int angles[], float sec)
{
  for (byte i = 12; i < 14; i++)
  {
    Serial.println("Servos_old_angles[" + String(i) + "] = " + String(servos_old_angles[i]));

    Serial.println("angles[" + String(i) + "] = " + String(angles[i]));
    long k = abs(angles[i] - servos_old_angles[i]);
    Serial.println("k ="  + String(k));
    speeds[i] = round(k  / sec);
    Serial.println("Speeds[" + String(i) + "] = " + String(speeds[i]));

  }
  set_servos_speeds(speeds);
  tmr = millis();
  flag = false;
  for (byte i = 12; i < 14; i++)
  {
    servos[i].setTargetDeg(flag ? 0 : angles[i]);
  }
  while (millis() - tmr < sec * 1000)
  {


    for (byte i = 12; i < 14 ; i++)
    {

      servos[i].tickManual();
      delay(5);

      //Serial.println("tick()");
    }
    //Serial.println("moving");

  }

  for (byte i = 12; i < 14; i++)
  {
    servos[i].setCurrentDeg(angles[i]);
  }
  set_old_ears(servos_angles[12], servos_angles[13]);

}
void all_servos_go(int angles[], float sec)
{
   for (byte i = 0; i < 14; i++)
  {
    //Serial.println("Servos_old_angles[" + String(i) + "] = " + String(servos_old_angles[i]));

    //Serial.println("angles[" + String(i) + "] = " + String(angles[i]));
    long k = abs(angles[i] - servos_old_angles[i]);
    //Serial.println("k ="  + String(k));
    speeds[i] = round(k  / sec);
    //Serial.println("Speeds[" + String(i) + "] = " + String(speeds[i]));

  }
  set_servos_speeds(speeds);
  tmr = millis();
  flag = false;
  for (byte i = 0; i < 14; i++)
  {
    servos[i].setTargetDeg(flag ? 0 : angles[i]);
  }
  while (millis() - tmr < sec * 1000)
  {


    for (byte i = 0; i <= 13; i++)
    {

      servos[i].tickManual();
      delay(1);

      //Serial.println("tick()");
    }
    //Serial.println("moving");

  }

  for (byte i = 0; i < 14; i++)
  {
    servos[i].setCurrentDeg(angles[i]);
  }
  set_old_all_angles(servos_angles[0], servos_angles[1], servos_angles[2], servos_angles[3], servos_angles[4], servos_angles[5], servos_angles[6], servos_angles[7], servos_angles[8], servos_angles[9], servos_angles[10], servos_angles[11], servos_angles[12], servos_angles[13]);
  }
void set_angles(int s0, int s1, int s2, int s3, int s4, int s5, int s6, int s7, int s8, int s9, int s10, int s11)
{

  servos_angles[0] = s0;
  servos_angles[1] = s1;
  servos_angles[2] = s2;
  servos_angles[3] = s3;
  servos_angles[4] = s4;
  servos_angles[5] = s5;
  servos_angles[6] = s6;
  servos_angles[7] = s7;
  servos_angles[8] = s8;
  servos_angles[9] = s9;
  servos_angles[10] = s10;
  servos_angles[11] = s11;
}
void set_all_angles(int s0, int s1, int s2, int s3, int s4, int s5, int s6, int s7, int s8, int s9, int s10, int s11, int s12, int s13)
{

  servos_angles[0] = s0;
  servos_angles[1] = s1;
  servos_angles[2] = s2;
  servos_angles[3] = s3;
  servos_angles[4] = s4;
  servos_angles[5] = s5;
  servos_angles[6] = s6;
  servos_angles[7] = s7;
  servos_angles[8] = s8;
  servos_angles[9] = s9;
  servos_angles[10] = s10;
  servos_angles[11] = s11;
  servos_angles[12] = s12;
  servos_angles[13] = s13;
}
void set_old_angles(int s0, int s1, int s2, int s3, int s4, int s5, int s6, int s7, int s8, int s9, int s10, int s11)
{

  servos_old_angles[0] = s0;
  servos_old_angles[1] = s1;
  servos_old_angles[2] = s2;
  servos_old_angles[3] = s3;
  servos_old_angles[4] = s4;
  servos_old_angles[5] = s5;
  servos_old_angles[6] = s6;
  servos_old_angles[7] = s7;
  servos_old_angles[8] = s8;
  servos_old_angles[9] = s9;
  servos_old_angles[10] = s10;
  servos_old_angles[11] = s11;
}
void set_old_all_angles(int s0, int s1, int s2, int s3, int s4, int s5, int s6, int s7, int s8, int s9, int s10, int s11, int s12, int s13)
{

  servos_old_angles[0] = s0;
  servos_old_angles[1] = s1;
  servos_old_angles[2] = s2;
  servos_old_angles[3] = s3;
  servos_old_angles[4] = s4;
  servos_old_angles[5] = s5;
  servos_old_angles[6] = s6;
  servos_old_angles[7] = s7;
  servos_old_angles[8] = s8;
  servos_old_angles[9] = s9;
  servos_old_angles[10] = s10;
  servos_old_angles[11] = s11;
  servos_old_angles[12] = s12;
  servos_old_angles[13] = s13;
}
void set_ears(int s12, int s13)
{
  servos_angles[12] = s12;
  servos_angles[13] = s13;
}
void set_old_ears(int s12, int s13)
{
  servos_old_angles[12] = s12;
  servos_old_angles[13] = s13;
}
