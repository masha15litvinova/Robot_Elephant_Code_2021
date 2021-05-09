bool canListen = false;
int command = 50;
int counter = 0;
int maxMotorsCounter = 4;
int motors[] = {0, 0, 0, 0};
int m0 = 0;
int m1 = 0;
int m2 = 0;
int m3 = 0;
int oldTric = 50;

bool isCommandDetected = false;

bool calculateMotors(int value) {
  int new_value = map(value, 0, 250, -251, 251);
 // Serial.println("value = " + String(value));
  //Serial.println("new_value = " + String(new_value));

  //Serial.println("value = "+String(value));
  if (value == 0xff) {
    counter = 0;
    //Serial.println("return");
    return true;
  } else {
    if ((counter < maxMotorsCounter)) {
      if ((abs(new_value) > 250))
      {
        new_value = 0;
        motors[counter] = new_value;
      }
      else
      {
        motors[counter] = new_value;
        counter++;
      }
    }

    return false;
  }

}


void goMarker()
{
  oldTric = tric;
  while ((oldTric == tric) or (tric == 50))
  {
    /*Serial.println("oldTric = " + String(oldTric));
      Serial.println("tric = " + String(tric));*/
    if (Serial2.available())
    {

      int data = Serial2.read();

      if (calculateMotors(data)) {
        if (Serial1.available())
        {
          tric = Serial1.read();
        }

        motors[2] = motors[0];
        motors[3] = motors[1];
        /*m0 = map(motors[0], 0, 250, -250, 250);
          m1 = map(motors[1], 0, 250, -250, 250);
          m2 = map(motors[2], 0, 250, -250, 250);
          m3 = map(motors[3], 0, 250, -250, 250);*/
        Serial.print(motors[0]);
        Serial.print(", ");
        Serial.print(motors[1]);
        Serial.print(", ");
        Serial.print(motors[2]);
        Serial.print(", ");
        Serial.println(motors[3]);
        Serial.print("tric = ");
        Serial.println(tric);

        //      Serial.println(motors[3]);
        motorsMove(motors[0], motors[1], motors[2],  motors[3], true);
        //        Serial.print("canListen = ");
        //        Serial.println(canListen);


      }
    }
  }
   turn_angle(0);
}
