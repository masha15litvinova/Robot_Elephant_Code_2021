int getVoice()
{
  oldTric = tric;
while ((oldTric == tric)or(tric == 50))
  {
    if (Serial2.available() > 0)
    {

      int data = Serial2.read();

      if (calculateMotors(data)) {


        m0 = map(motors[0], 0, 255, -255, 255);
        m1 = map(motors[1], 0, 255, -255, 255);
        m2 = map(motors[2], 0, 255, -255, 255);
        m3 = map(motors[3], 0, 255, -255, 255);
//        Serial.print(m0);
//        Serial.print(", ");
//        Serial.print(m1);
//        Serial.print(", ");
//        Serial.print(m2);
//        Serial.print(", ");
//        Serial.println(m3);
//        Serial.print("tric = ");
//        Serial.println(tric);
        
        //      Serial.println(motors[3]);
        motorsMove(m0, m1, m2,  m3, false);
//        Serial.print("canListen = ");
//        Serial.println(canListen);
        delay(1);
        
      }
    }
  }
  return tric;
}
