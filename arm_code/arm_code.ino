#include <Servo.h>

Servo base;
Servo dan_pas;
Servo bam_pas;

int nutral = 90;
int temp = 'x';
int i;

void setup() {
  Serial.begin(9600);
  base.attach(24);
  dan_pas.attach(25);
  bam_pas.attach(26);


  //////////////// Nutral///////////////////////
  base.write(nutral);
  dan_pas.write(175);
  bam_pas.write(5);
  //////////////////////////////////////////////

}

void loop() {
  if (Serial.available() > 0) {
    temp = Serial.read();
  }
  if (temp == 'o') {   //// open
    dan_pas.write(130);
    bam_pas.write(50);
  }
    if (temp == 'c') {   //// close
    dan_pas.write(175);
    bam_pas.write(5);
  }
  if (temp == 'd') {   /// niche namtese
    for(i = 50; i<= 110; i+= 5) {
      base.write(i);
      delay(100);
      }
  }
  if (temp == 'u') { ///// upore ut tese
    base.write(50);
  }
  if (temp == 'x') {
    base.write(nutral);
    dan_pas.write(175);
    bam_pas.write(5);
  }
}
