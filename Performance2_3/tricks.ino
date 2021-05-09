void waiting_voice()
{

  ears_tric();


  delay(1200);
}

void end_tric()
{
  turn_angle(0);
   move_winch(130, 60);
  set_all_angles(AVG_angles[0], AVG_angles[1], AVG_angles[2], AVG_angles[3], AVG_angles[4], AVG_angles[5], AVG_angles[6], AVG_angles[7], AVG_angles[8], AVG_angles[9], AVG_angles[10], AVG_angles[11], AVG_angles[12], AVG_angles[13]);
  servos_go(servos_angles, 1);
  move_winch(120, 55);
  goMarker();

}
void spin()
{
  //go(35, 2500);
  move_winch(70, 75);
  set_angles(70, 75, 30, 75, 75, 35, 75, 75, 130, 85, 55, 135);
  servos_go(servos_angles, 2.0);
  delay(1000);
  int w_speed = 40;
  for (byte i = 0; i < 2; i++)
  {
    motorsGo(w_speed, w_speed, w_speed, w_speed);
    move_winch(230, 95);
    set_angles(70, 75, 30, 75, 75, 35, 75, 75, 130, 85, 55, 135);
    servos_go(servos_angles, 0.01);
    move_winch(100, 55);
    set_angles(70, 75, 30, 75, 75, 35, 75, 75, 130, 85, 55, 135);
    servos_go(servos_angles, 0.01);
    w_speed = w_speed + 65;
  }
  for (byte j = w_speed;  j > 0; j--)
  {
    motorsGo(j, j, j, j);
    delay(20);
  }
  turn_angle(0);
  motorsGo(0, 0, 0, 0);
  end_tric();

}
void flight()
{
  int v = 85;

  move_winch(120, 45);
  set_angles(AVG_angles[0], AVG_angles[1], AVG_angles[2], AVG_angles[3], AVG_angles[4], AVG_angles[5], AVG_angles[6], AVG_angles[7], AVG_angles[8], AVG_angles[9], AVG_angles[10], AVG_angles[11]);
  servos_go(servos_angles, 1.5);
  
  if (gyro)
  {
    turn_angle(90);
    go_angle_msec(1500, 90, -v, v, -v, v);
  }
  else
  {
    motorsGo(v, v, v, v);
    delay(2500);
    motorsGo(0, 0, 0, 0);
    motorsGo(-v, v, -v, v);
    delay(2500);
    motorsGo(0, 0, 0, 0);
  }
  move_winch(300, 85);
  for (byte i = 0; i < 2; i++)
  {
 set_angles(AVG_angles[0], AVG_angles[1]-60, AVG_angles[2], AVG_angles[3], AVG_angles[4]-60, AVG_angles[5], AVG_angles[6], AVG_angles[7]+60, AVG_angles[8], AVG_angles[9], AVG_angles[10]+60, AVG_angles[11]);
    
    servos_go(servos_angles, 0.8);
    //    go(-v, v, -v, v, 2000);
    motorsGo(0, 0, 0, 0);
    




    set_angles(AVG_angles[0], AVG_angles[1], AVG_angles[2], AVG_angles[3], AVG_angles[4], AVG_angles[5], AVG_angles[6], AVG_angles[7], AVG_angles[8], AVG_angles[9], AVG_angles[10], AVG_angles[11]);
    servos_go(servos_angles, 0.8);
  }
  move_winch(120, 45);
  set_angles(AVG_angles[0], AVG_angles[1], AVG_angles[2], AVG_angles[3], AVG_angles[4], AVG_angles[5], AVG_angles[6], AVG_angles[7], AVG_angles[8], AVG_angles[9], AVG_angles[10], AVG_angles[11]);
  servos_go(servos_angles, 1.0);
  /*if (gyro)
  {
    turn_angle(0);
    turn_angle(-90);
    go_angle_msec(1500, -90, -v, v, -v, v);
  }
  else
  {
    motorsGo(v, v, v, v);
    delay(2500);
    motorsGo(0, 0, 0, 0);
    motorsGo(-v, v, -v, v);
    delay(2500);
    motorsGo(0, 0, 0, 0);
  }*/
  /*move_winch(300, 85);
  for (byte i = 0; i < 2; i++)
  {

     set_angles(AVG_angles[0], AVG_angles[1]-60, AVG_angles[2], AVG_angles[3], AVG_angles[4]-60, AVG_angles[5], AVG_angles[6], AVG_angles[7]+60, AVG_angles[8], AVG_angles[9], AVG_angles[10]+60, AVG_angles[11]);
    
    servos_go(servos_angles, 2.0);
    //    go(-v, v, -v, v, 2000);
    motorsGo(0, 0, 0, 0);
    




    set_angles(AVG_angles[0], AVG_angles[1], AVG_angles[2], AVG_angles[3], AVG_angles[4], AVG_angles[5], AVG_angles[6], AVG_angles[7], AVG_angles[8], AVG_angles[9], AVG_angles[10], AVG_angles[11]);
    servos_go(servos_angles, 1.0);
  }*/
   move_winch(120, 45);
   if (gyro)
  {
    turn_angle(0);
    turn_angle(-90);
    go_angle_msec(1500, -90, -v, v, -v, v);
  }
  else
  {
    motorsGo(v, v, v, v);
    delay(2500);
    motorsGo(0, 0, 0, 0);
    motorsGo(-v, v, -v, v);
    delay(2500);
    motorsGo(0, 0, 0, 0);
  }
  turn_angle(0);
  motorsGo(0, 0, 0, 0);
  servos_begin();
  end_tric();

}
void sing()
{
  
  
  turn_angle(0);
  
  steps(10, 20, 50);
  int v = -70;
  turn_angle(30);
  delay(600);

  paw_hitting(6, 40);
  turn_angle(0);
  delay(600);
  motorsGo(0, 0, 0, 0);
  end_tric();
}
void steps(int count, float amplitude, int v)
{
  turn_angle(0);
 
  set_angles(AVG_angles[0], AVG_angles[1], AVG_angles[2], AVG_angles[3], AVG_angles[4], AVG_angles[5], AVG_angles[6], AVG_angles[7], AVG_angles[8], AVG_angles[9], AVG_angles[10], AVG_angles[11]);
  servos_go(servos_angles, 0.5);
  move_winch(135, 70);
  int const_value = 45;
  float time_s = amplitude / const_value;
  //min_speed = 15


  int ampl = round(amplitude);
  for (byte j = 0; j < count / 2; j++)
  {
    motorsGo(-v, v, -v, v);


    Serial.println("servos move");
    set_angles(AVG_angles[0], AVG_angles[1], AVG_angles[2], AVG_angles[3] - ampl, AVG_angles[4], AVG_angles[5] + ampl, AVG_angles[6], AVG_angles[7], AVG_angles[8], AVG_angles[9] + ampl, AVG_angles[10], AVG_angles[11] - ampl);

    servos_go(servos_angles, time_s);
    set_angles(AVG_angles[0] - ampl, AVG_angles[1], AVG_angles[2] + ampl, AVG_angles[3], AVG_angles[4], AVG_angles[5], AVG_angles[6] + ampl, AVG_angles[7], AVG_angles[8] - ampl, AVG_angles[9], AVG_angles[10], AVG_angles[11]);
    servos_go(servos_angles, time_s);
  }
  turn_angle(0);
  for (byte j = count / 2; j < count; j++)
  {
    motorsGo(v, -v, v, -v);

    Serial.println("servos move");
    set_angles(AVG_angles[0], AVG_angles[1], AVG_angles[2], AVG_angles[3] - ampl, AVG_angles[4], AVG_angles[5] + ampl, AVG_angles[6], AVG_angles[7], AVG_angles[8], AVG_angles[9] + ampl, AVG_angles[10], AVG_angles[11] - ampl);
    servos_go(servos_angles, time_s);
    set_angles(AVG_angles[0] - ampl, AVG_angles[1], AVG_angles[2] + ampl, AVG_angles[3], AVG_angles[4], AVG_angles[5], AVG_angles[6] + ampl, AVG_angles[7], AVG_angles[8] - ampl, AVG_angles[9], AVG_angles[10], AVG_angles[11]);
    servos_go(servos_angles, time_s);
  }
  motorsGo(0, 0, 0, 0);

}
void sit_lie_stand()
{
  turn_angle(0);
  int v4 = 80;
  if(gyro)
  {
    turn_angle(65);
    }
  /*if (gyro)
  {
    go_angle_msec(1300, 0, -v4, v4, -v4, v4);
    go_angle_msec(1900, 0, v4, -v4, -v4, v4);
  }
  else
  {
    motorsGo(-v4, v4, -v4, v4);
    delay(1500);
    motorsGo(0, 0, 0, 0);
    motorsGo(-v4, v4, v4, -v4);
    delay(2000);
    motorsGo(0, 0, 0, 0);
  }*/
  //70, 75, 85, 75, 70, 85, 75, 75, 75, 85, 60, 75, 75, 75
  move_winch(230, 55);
  set_angles(AVG_angles[0], AVG_angles[1], AVG_angles[2], AVG_angles[3], AVG_angles[4], AVG_angles[5], AVG_angles[6], AVG_angles[7], AVG_angles[8], AVG_angles[9], AVG_angles[10], AVG_angles[11]);
  servos_go(servos_angles, 1.5);
  move_winch(105, 55);
//delay(1000);
  move_winch(60, 45);
  set_angles(80, 75, 85, 115, 75, 15, 40, 75, 140, 80, 55, 75);
  servos_go(servos_angles, 1.5);
  ///delay(2000);
  move_winch(20, 55);
  set_angles(70, 75, 30, 75, 75, 35, 75, 75, 130, 85, 55, 135);
  servos_go(servos_angles, 1.0);
 // delay(1000);
  end_tric();
}
void scare()
{
  int v = 110;
  turn_angle(0);
  move_winch(170, 120);
  if (gyro)
  {
    go_angle_msec(1000, 0, -v, v, -v, v);
    go_angle_msec(2000, 0, v, -v, -v, v);
  }
  else
  {
    //motorsGo(0, 0, v, -v);
    delay(500);
     motorsGo(0, 0, 0, 0);
  }
  //go_angle_msec(2000, 0, v, -v, -v, v);
 
  motorsGo(0, 0, 0, 0);
  set_angles(AVG_angles[0], AVG_angles[1], AVG_angles[2], AVG_angles[3], AVG_angles[4], AVG_angles[5], AVG_angles[6], AVG_angles[7], AVG_angles[8], AVG_angles[9], AVG_angles[10], AVG_angles[11]);
  servos_go(servos_angles, 1);

  motorsGo(0, 0, 0, 0);
  move_winch(20, 120);


  set_angles(70, 75, 30, 75, 75, 30, 75, 75, 140, 85, 55, 140);
  servos_go(servos_angles, 1.5);

  set_ears(145, 25);
  ears_move(servos_angles, 0.5);
  set_ears(40, 125);
  ears_move(servos_angles, 0.5);
  for (byte i = 0; i < 40; i++)
  {
    int v = 55;
    motorsGo(v, v, v, v);
    //set_ears(55, 125);
    //ears_move(servos_angles, 0.1);
    delay(120);
    motorsGo(-v, -v, -v, -v);
    //set_ears(145, 25);
    //ears_move(servos_angles, 0.1);
    delay(120);
  }
  delay(1000);
  motorsGo(0, 0, 0, 0);
  move_winch(130, 55);
   paw_hitting(6, 40);
  paw_hitting(6, 40);
  end_tric();
}
void high_five()
{
  int v = 85;
  /*if (gyro)
  {
    go_angle_msec(1000, 0, -v, v, -v, v);
    go_angle_msec(1500, 0, -v, v, v, -v);
  }
  else
  {
    motorsGo(-v, v, -v, v);
    delay(2500);
    motorsGo(0, 0, 0, 0);
    motorsGo(-v, v, v, -v);
    delay(3000);
    motorsGo(0, 0, 0, 0);
  }*/
  if (gyro)
  {
    turn_angle(30);
  }
  else
  {
    motorsGo(v, v, v, v);
    delay(1800);
    motorsGo(0, 0, 0, 0);
  }
  move_winch(100, 35);
  set_angles(AVG_angles[0], AVG_angles[1], AVG_angles[2], AVG_angles[3], AVG_angles[4], AVG_angles[5], AVG_angles[6], AVG_angles[7], AVG_angles[8], AVG_angles[9], AVG_angles[10], AVG_angles[11]);
  servos_go(servos_angles, 1.7);
  move_winch(90, 60);
  move_winch(60, 50);
 set_angles(80, 75, 85, 115, 75, 15, 40, 75, 140, 80, 55, 75);
  servos_go(servos_angles, 2.0);


  set_angles(35, 75, 85, 115, 75, 15, 40, 75, 140, 80, 55, 75);
  servos_go(servos_angles, 1);

  set_angles(35, 75, 30, 115, 75, 15, 40, 75, 140, 80, 55, 75);
  servos_go(servos_angles, 1);
  set_angles(35, 75, 85, 115, 75, 15, 40, 75, 140, 80, 55, 75);
  servos_go(servos_angles, 1);
  set_angles(80, 75, 85, 115, 75, 15, 40, 75, 140, 80, 55, 75);
  servos_go(servos_angles, 1);
   int v3 = -70;
   go_angle_msec(1500, 0, -v3, v3, -v3, v3);
   


  end_tric();
}
void square()
{
  turn_angle(0);
  
  set_all_angles(AVG_angles[0], AVG_angles[1], AVG_angles[2], AVG_angles[3], AVG_angles[4], AVG_angles[5], AVG_angles[6], AVG_angles[7], AVG_angles[8], AVG_angles[9], AVG_angles[10], AVG_angles[11], AVG_angles[12], AVG_angles[13]);
  servos_go(servos_angles, 1);
  move_winch(130, 65);
  int v = 80;
  //move_winch(120, 50);
  //70, 75, 85, 75, 70, 85, 75, 75, 75, 85, 55, 75
  //set_angles(70, 5, 85, 75, 70, 85, 75, 75, 75, 85, 55, 75);
  //servos_go(servos_angles, 1.5);
  //delay(2000);
  

  set_angles(70, 75, 85, 130, 70, 85, 75, 65, 75, 85, 55, 75);
  servos_go(servos_angles, 1.0);
  //move_winch(110, 50);//backward
  if (gyro)
  {
    go_angle_msec(2000, 0, v, -v, v, -v);
  }
  else
  {
    motorsGo(v, -v, v, -v);
    delay(2000);
    motorsGo(0, 0, 0, 0);
  }
  set_angles(70, 75, 85, 75, 70, 85, 75, 75, 75, 85, 55, 75);
  servos_go(servos_angles, 0.6);

  set_angles(70, 75, 85, 75, 70, 85, 75, 145, 75, 85, 55, 75);
  servos_go(servos_angles, 1.0);                               //right
  if (gyro)
  {
    go_angle_msec(2500, 0, v, -v, -v, v);
  }
  else
  {
    motorsGo(v, -v, -v, v);
    delay(2000);
    motorsGo(0, 0, 0, 0);
  }
  set_angles(70, 75, 85, 75, 70, 85, 75, 75, 75, 85, 55, 75);
  servos_go(servos_angles, 0.6);




  set_angles(70, 75, 85, 75, 70, 85, 75, 75, 75, 130, 55, 75);
  servos_go(servos_angles, 1.0);
  if (gyro)
  {
    go_angle_msec(2500, 0, -v, v, -v, v);
  }
  else
  {
    motorsGo(-v, v, -v, v);
    delay(2000);
    motorsGo(0, 0, 0, 0);
  }

  set_angles(70, 75, 85, 75, 70, 85, 75, 75, 75, 85, 55, 75);
  servos_go(servos_angles, 0.6);                                 //forward



  set_angles(70, 5, 85, 75, 70, 85, 75, 75, 75, 85, 55, 75);
  servos_go(servos_angles, 1.0);                               //left
  if (gyro)
  {
    go_angle_msec(2000, 0, -v, v, v, -v);
  }
  else
  {
    motorsGo(-v, v, v, -v);
    delay(2000);
    motorsGo(0, 0, 0, 0);
  }
  set_angles(70, 75, 85, 75, 70, 85, 75, 75, 75, 85, 55, 75);
  servos_go(servos_angles, 0.6);
    int v3 = -70;
   go_angle_msec(1500, 0, -v3, v3, -v3, v3);
  end_tric();
}
void ears_tric()
{
  set_ears(55, 125);
  ears_move(servos_angles, 2.5);
  Serial.println("first");
  //delay(3000);
  set_ears(155, 25);
  ears_move(servos_angles, 2.5);
}
void paw_hitting(int count, float amplitude)
{
  servos_begin();
  int const_value = 45;
  float time_s = amplitude / const_value;
  int ampl = round(amplitude);
  for (byte j = 0; j < count / 2; j++)
  {


    set_angles(AVG_angles[0], AVG_angles[1], AVG_angles[2], AVG_angles[3], AVG_angles[4], AVG_angles[5], AVG_angles[6], AVG_angles[7], AVG_angles[8], AVG_angles[9] + ampl, AVG_angles[10], AVG_angles[11] - ampl);

    servos_go(servos_angles, time_s);
    set_angles(AVG_angles[0], AVG_angles[1], AVG_angles[2], AVG_angles[3], AVG_angles[4], AVG_angles[5], AVG_angles[6], AVG_angles[7], AVG_angles[8], AVG_angles[9], AVG_angles[10], AVG_angles[11]);
    servos_go(servos_angles, time_s);
  }
}
//void go_to_audience()
//{
//  int v = 70;
//   go(-v, v, -v, v, 3000);
//
//  }
