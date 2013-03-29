//trackball arduino
//sending serial messages to openframeworks from arduino
//fuzzywobble.com

//pin config -----------------
//WHITE - ARDUINO 6
//PURPLE - ARDUINO 5
//BROWN - ARDUINO +5V
//ORANGE - ARDUINO GND
// ---------------------------

#include <ps2.h>
PS2 mouse1(6, 5);

void mouse1_init(){
  mouse1.write(0xff);  // reset
  mouse1.read();  // ack byte
  mouse1.read();  // blank */
  mouse1.read();  // blank */
  mouse1.write(0xf0);  // remote mode
  mouse1.read();  // ack
  delayMicroseconds(100);
}

void setup(){
  Serial.begin(57600);
  mouse1_init();
}

boolean send_flag = true;
int val = 0;
unsigned char buffer[2] = {0,0};

void loop(){ 
  
  char mstat1;
  char mx1;
  char my1;
  /* get a reading from the mouse */
  mouse1.write(0xeb);  // give me data!
  mouse1.read();      // ignore ack
  mstat1 = mouse1.read();
  mx1 = mouse1.read();
  my1 = mouse1.read();
  buffer[0] = mx1;
  buffer[1] = my1;
  
  val = Serial.read();  
  if(val=='a'){
    send_flag = true;  
  }
  
  if(send_flag==true){
    Serial.write("|");
    Serial.write(buffer[0]); //Serial.write(buf, len)
    Serial.write("|");
    Serial.write(buffer[1]); //Serial.write(buf, len)
    Serial.write("|");
    send_flag = false;  
  }
  
}
