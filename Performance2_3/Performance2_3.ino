

#include <SoftwareSerial.h>
SoftwareSerial btSerial (22, 23); //rx,tx
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         #include <ServoDriverSmooth.h>
ServoDriverSmooth servos[14];
//ServoDriverSmooth servo(0x68);      // с указанием адреса драйвера
ServoDriverSmooth servo(0x68, 270); // с указанием адреса и макс. угла
#include <Elephant_Core.h>

Elephant_Core base(true);

int tric = 50;
volatile long winch_enc = 0;

void setup()
{
  Serial.begin(115200);


  Serial1.begin(115200);
  Serial2.begin(115200);
  Serial3.begin(115200);
  btSerial.begin(9600);
  pinMode(A12, INPUT);
  pinMode(40, INPUT);
  pinMode(A13, INPUT);
  pinMode(39, INPUT);

  initialize_motors();
  initialize_winch();


  //motorsGo(0,0,0,0);
winch_homing();
 servos_begin();
   
    gyro_init();

    
end_tric();
 // goMarker();

  Serial.println("setup");
  
}
void loop()
{

  
  
   
  // delay(30000);
  //delay(3000);
  //scare();
  //square();

  //end_tric();
 
  //goMarker();

  
    switch (tric)
    {
      case 0:
        sendSignal(0);
        high_five();

        break;
      case 1:
        sendSignal(1);
        square();
        break;
      case 2:
        sendSignal(2);
        flight();
        break;
      case 3:
        sendSignal(3);
        sit_lie_stand();
        break;
      case 4:
        sendSignal(4);
        sing();
        break;
      case 5:
        sendSignal(5);
        spin();
        break;
      case 6:
        sendSignal(6);
        scare();
        break;
      default:
        Serial.println("error");
        break;

    }
    delay(1000);


    //Serial.println("oldCommand = "+String(oldCommand));
    //Serial.println("Command = "+String(command));
  
}
