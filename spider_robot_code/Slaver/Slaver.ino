#include <Arduino.h>
#include <Servo.h>
#include <Wire.h>

int receive = 0, test=0;

// declare servo, 
/* 
l_f up45  down90  move90  back45
r_f up135 down90  move90  back135
l_h up180 down135 move135  back180
r_h up135 down180 move180  back135
*/
Servo left_front1, right_front1, left_hind1, right_hind1;
Servo left_front2, right_front2, left_hind2, right_hind2;
int l_f_up = 45, l_f_down = 90, l_f_move = 90, l_f_back = 45;
int r_f_up = 135, r_f_down = 90, r_f_move = 90, r_f_back = 135;
int l_h_up = 180, l_h_down = 135, l_h_move = 135, l_h_back = 180;
int r_h_up = 135, r_h_down = 180, r_h_move = 180, r_h_back = 135;

void setup() {
  Wire.begin(9); 
  Wire.onReceive(receiveEvent);

  Serial.begin(9600);

  // set servo pins
  left_front1.attach(6);
  left_front1.write(l_f_back);
  delay(200);
  right_front1.attach(7);
  right_front1.write(r_f_back);
  delay(200);
  left_hind1.attach(11);
  left_hind1.write(l_h_back);
  delay(200);
  right_hind1.attach(10);
  right_hind1.write(r_h_back);
  delay(200);
  left_front2.attach(4);
  left_front2.write(l_f_down);
  delay(200);
  right_front2.attach(5);
  right_hind2.write(r_f_down);
  delay(200);
  left_hind2.attach(9);
  left_hind2.write(l_h_down);
  delay(200);
  right_hind2.attach(8);
  right_hind2.write(r_h_down);
  delay(200);

  delay(500);
}

void receiveEvent(int bytes) 
{
  receive = Wire.read();
}

void loop() {
  // Serial.println(receive);
  if (receive == 1){
    walk();
    delay(200);
  }
  else if(receive == 2){
    turn_left();
  }
  else if(receive == 3){
    turn_right();
  }
  else if(receive == 4){
    back();
    delay(200);
  }
  else{
    delay(2600);
  }
}

/* 
l_f up45  down90  move90  back45
r_f up135 down90  move90  back135
l_h up180 down135 move135  back180
r_h up135 down180 move180  back135
*/
void walk(){
  // left hind leg and right front leg move together, legt front leg and right hind leg move together.
  // servo2 of front leg moves up and servo1 moves forward _after_ walk.
  // servo2 of hind leg moves up and servo1 moves forward _befor_ walk.
  // 2400
  
  left_hind2.write(l_h_up);
  delay(200);
  left_hind1.write(l_h_move);
  delay(200);
  left_hind2.write(l_h_down);
  delay(200);
  right_hind2.write(r_h_up);
  delay(200);
  for(int i=1; i<=45; i++){
    left_hind1.write(l_h_move+i);
    right_front1.write(r_f_back-i);
    right_hind1.write(r_h_back+i);
  }
  delay(200);
  right_hind2.write(r_h_down);
  delay(200);
  right_front2.write(r_f_up);
  delay(200);
  for(int i=1; i<=45; i++){
    right_hind1.write(r_h_move-i);
    left_front1.write(l_f_back+i);
    right_front1.write(r_f_move+i);
  }
  delay(200);
  right_front2.write(r_f_down);
  delay(200);
  left_front2.write(l_f_up);
  delay(200);
  left_front1.write(l_f_back);
  delay(200);
  left_front2.write(l_f_down);
  delay(200);

}

/* 
l_f up45  down90  move90  back45
r_f up135 down90  move90  back135
l_h up180 down135 move135  back180
r_h up135 down180 move180  back135
*/
void turn_left(){
  // 2600
  left_front2.write(l_f_up);
  delay(200);
  left_front1.write(l_f_move);
  delay(200);
  left_front2.write(l_f_down);
  delay(200);
  right_hind2.write(r_h_up);
  delay(200);
  right_hind1.write(r_h_move);
  delay(200);
  right_hind2.write(r_h_down);
  delay(200);
  for(int i=1; i<=45; i++){
    left_front1.write(l_f_move-i);
    right_front1.write(r_f_back-i);
    left_hind1.write(l_h_back-i);
    right_hind1.write(r_h_move-i);
  }
  delay(200);
  right_front2.write(r_f_up);
  delay(200);
  right_front1.write(r_f_back);
  delay(200);
  right_front2.write(r_f_down);
  delay(200);
  left_hind2.write(l_h_up);
  delay(200);
  left_hind1.write(l_h_back);
  delay(200);
  left_hind2.write(l_h_down);
  delay(200);
}

/* 
l_f up45  down90  move90  back45
r_f up135 down90  move90  back135
l_h up180 down135 move135  back180
r_h up135 down180 move180  back135
*/
void turn_right(){
  // 2600
  right_front2.write(r_f_up);
  delay(200);
  right_front1.write(r_f_move);
  delay(200);
  right_front2.write(r_f_down);
  delay(200);
  left_hind2.write(l_h_up);
  delay(200);
  left_hind1.write(l_h_move);
  delay(200);
  left_hind2.write(l_h_down);
  delay(200);
  for(int i=1; i<=45; i++){
    left_front1.write(l_f_back+i);
    right_front1.write(r_f_move+i);
    left_hind1.write(l_h_move+i);
    right_hind1.write(r_h_back+i);
  }
  delay(200);
  left_front2.write(l_f_up);
  delay(200);
  left_front1.write(l_f_back);
  delay(200);
  left_front2.write(l_f_down);
  delay(200);
  right_hind2.write(r_h_up);
  delay(200);
  right_hind1.write(r_h_back);
  delay(200);
  right_hind2.write(r_h_down);
  delay(200);

}

/* 
l_f up45  down90  move90  back45
r_f up135 down90  move90  back135
l_h up180 down135 move135  back180
r_h up135 down180 move180  back135
*/
void back(){
  // 2400
  left_front2.write(l_f_up);
  delay(200);
  left_front1.write(l_f_move);
  delay(200);
  left_front2.write(l_f_down);
  delay(200);
  right_front2.write(r_f_up);
  delay(200);
  for(int i=1; i<=45; i++){
    left_front1.write(l_f_move-i);
    right_hind1.write(r_h_back+i);
    right_front1.write(r_f_back-i);
  }
  delay(200);
  right_front2.write(r_f_down);
  delay(200);
  right_hind2.write(r_h_up);
  delay(200);
  for(int i=0; i<=45; i++){
    right_front1.write(r_f_move+i);
    left_hind1.write(l_h_back-i);
    right_hind1.write(r_h_move-i);
  }
  delay(200);
  right_hind2.write(r_h_down);
  delay(200);
  left_hind2.write(l_h_up);
  delay(200);
  left_hind1.write(l_h_back);
  delay(200);
  left_hind2.write(l_h_down);
  delay(200);
}
