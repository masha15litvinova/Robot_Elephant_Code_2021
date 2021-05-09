int get_voice1()
{
  int tric = -1;
  long timer_begin = millis();
  long timer = 0;
  while (timer < 500)
  {
    timer = millis() - timer_begin;
    if (Serial2.available() > 0)
    {

      int data = Serial2.read();

      if (calculateMotors(data))
      {
        m0 = map(motors[0], 0, 255, -255, 255);
        m1 = map(motors[1], 0, 255, -255, 255);
        m2 = map(motors[2], 0, 255, -255, 255);
        m3 = map(motors[3], 0, 255, -255, 255);
        Serial.print(m0);
        Serial.print(", ");
        Serial.print(m1);
        Serial.print(", ");
        Serial.print(m2);
        Serial.print(", ");
        Serial.println(m3);

        //motorsMove(m0, m1, m2,  m3, false);
        Serial.print("canListen = ");
        Serial.println(canListen);
        delay(10);
      }

      Serial.println("waiting for voice...");
    }
  }
  timer = 0;
  timer_begin = millis();
  while ((!canListen) or (timer < 500))
  {
    timer = millis() - timer_begin;
    if (Serial2.available() > 0)
    {

      int data = Serial2.read();

      if (calculateMotors(data))
      {
        m0 = map(motors[0], 0, 255, -255, 255);
        m1 = map(motors[1], 0, 255, -255, 255);
        m2 = map(motors[2], 0, 255, -255, 255);
        m3 = map(motors[3], 0, 255, -255, 255);
        Serial.print(m0);
        Serial.print(", ");
        Serial.print(m1);
        Serial.print(", ");
        Serial.print(m2);
        Serial.print(", ");
        Serial.println(m3);

        motorsMove(m0, m1, m2,  m3, false);
        Serial.print("canListen = ");
        Serial.println(canListen);
        delay(10);
      }

      Serial.println("waiting for voice...");
    }

  }
  Serial.println("enter the tric");
  if (canListen)
  {
    while (digitalRead(39) == 0)
    {
      command = map(analogRead(A12), 0, 1023, 0, 5);
    }
    Serial.print("command = ");
    Serial.println(command);

    canListen = false;
    delay(500);
  }
  return command;

}
void high_five1()
{
  for (byte i = 0; i < 1; i++)
  {
    motorsGo(30,30,30,30);
    delay(400);
    motorsGo(0,0,0,0);
    delay(400);
    }
  Serial.println("high five");
  delay(1000);
  canListen = false;
  
}
void square1()
{
  for (byte i = 0; i < 2; i++)
  {
    motorsGo(30,30,30,30);
    delay(400);
    motorsGo(0,0,0,0);
    delay(400);
    }
  Serial.println("square");
  delay(1000);
  canListen = false;
}
void flight1()
{
  for (byte i = 0; i < 3; i++)
  {
    motorsGo(30,30,30,30);
    delay(400);
    motorsGo(0,0,0,0);
    delay(400);
    }
  Serial.println("flight");
  delay(1000);
  canListen = false;
}
void sit_lie_stand1()
{
  for (byte i = 0; i < 4; i++)
  {
    motorsGo(30,30,30,30);
    delay(400);
    motorsGo(0,0,0,0);
    delay(400);
    }
  Serial.println("sit lie stand");
  delay(1000);
  canListen = false;
}
void sing1()
{
  for (byte i = 0; i < 5; i++)
  {
    motorsGo(30,30,30,30);
    delay(400);
    motorsGo(0,0,0,0);
    delay(400);
    }
  Serial.println("sing");
  delay(1000);
  canListen = false;
}
void youla1()
{
  for (byte i = 0; i < 6; i++)
  {
    motorsGo(30,30,30,30);
    delay(400);
    motorsGo(0,0,0,0);
    delay(400);
    }
  Serial.println("youla");
  delay(1000);
  canListen = false;
}
