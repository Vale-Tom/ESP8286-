#include <SoftwareSerial.h>

SoftwareSerial seriale(9,10);

String termine="\r\n";
int flag=0;

void setup() {
  Serial.begin(9600);
  //Serial.println("test");
  // put your setup code here, to run once:
  seriale.begin(9600);

  seriale.print("AT\r\n");

}

void loop() {
  // put your main code here, to run repeatedly:
if(Serial.available()>0){
  seriale.write(Serial.read());
}

if(seriale.available()>0){
  Serial.write(seriale.read());
}


}
