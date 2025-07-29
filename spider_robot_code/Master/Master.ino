#include <Wire.h>
#include <dht11.h>
// #include "DHT.h"
#include <SoftwareSerial.h>

int send = 0;
bool is_auto = false;
bool send_inf = false;
double t_b = 35;
double mq_2_b = 800;
double ul_b = 30;//The limitation of each item

SoftwareSerial BT(3, 4); 
//Set the connection port between Bluetooth and the board. pin 8 is connected to the TXD of Bluetooth and pin 9 is connected to the RXD of Bluetooth
char X; //Define a variable to store data.
// declare DHT11
#define DHT11PIN A2
// #define DHTTYPE DHT11
// DHT dht11(DHT11PIN, DHTTYPE);
dht11 DHT11;

// declare MQ-2 analog signal pin
#define MQ2_as_pin A0

// declare ultrasonic sensor pin
int trig_pin = 13, echo_pin = 7; 

void setup() {
  BT.begin(9600); //The default Bluetooth communication rate is generally 38400

  Wire.begin(); 
  Serial.begin(9600);

  // set MQ-2 pin
  pinMode(MQ2_as_pin, INPUT);

  // set ultrasonic sensor pin
  pinMode(trig_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
  digitalWrite(trig_pin, LOW);
}

int autoMove(float t, float mq2, float d){
  if(t >= 35.0 || mq2 >= 1000.0) return 0;
  else if(d < 30.0) return 2;
  else return 1;
}

void loop() {
  Serial.println(BT.available());
  if (BT.available()) //detect: if bluetooth input successfully, take the following steps
  {
    is_auto = false;
    X = BT.read(); //return the detected result to parameter X
    BT.println(X);
    Serial.println(X); //Show the information to the Serial port monitor
    if(X == 'f') send = 1;
    else if(X == 'l') send = 2;
    else if(X == 'r') send = 3;
    else if(X == 's') send = 0;
    else if(X == 'b') send = 4;
    else if(X == 'a'){
      // send = autoMove();
      is_auto = true;
    }
    else if(X == 'i') {
      if (send_inf) send_inf = false;
      else send_inf = true;
    }
    else {
      BT.print("error!");
    }
  }
  float t, mq2, d;

  t = get_dht();
  mq2 = get_mq2();
  d = get_distance();

  if(send_inf){
    BT.print(" temperature : ");
    BT.print(t);
    BT.print("mq2 : ");
    BT.print(mq2);
    BT.print("distance : ");
    BT.print(d);
    send_inf = false;
  }
  
  if (is_auto){
    send = autoMove(t, mq2, d);
  }

  if(t >= t_b){
    send = 0;
    is_auto = false;
    BT.print("Temparature Alarm!!! ");
    BT.print(" temperature : ");   BT.print(t);
  }
  if(mq2 >= mq_2_b){
    send = 0;
    is_auto = false;
    BT.print("Smoke Alarm!!! ");
    BT.print("mq2 : ");
    BT.print(mq2);
  }
  if(d < ul_b){
    if(!is_auto) send = 0;
    BT.print("Obstacle Alarm!!! ");
    BT.print("distance : ");
    BT.print(d);
  }

  Wire.beginTransmission(9);
  Wire.write(send);              
  Wire.endTransmission();
  // Serial.println(send);
  Serial.println(1);

  // delay(600);
}

float get_dht(){
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  // // get humidity
  // float h = dht11.readHumidity();
  // // get temperature as Celsius
  // float t = dht11.readTemperature();
  // // comput heat index in Celsius
  // float hic = dht11.computeHeatIndex(t, h, false);
  // Serial.println(t);
  // return t;

  int chk = DHT11.read(DHT11PIN);
  // char t_char = DHT11.temperature;
  delay(2000);
  float t = (float)DHT11.temperature;
  //Serial.println(t);
  return t;
}

float get_mq2(){
  float mq2_value = analogRead(MQ2_as_pin);
  //Serial.println(mq2_value);
  return mq2_value;
}

float get_distance(){
  //Send a 10μs high pulse to trigger the TrigPin
  digitalWrite(trig_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pin, LOW);

  float distance = pulseIn(echo_pin, HIGH) / 58.0; //Converting the distance into cm. The sound speed is 340m/s or 29us/cm. The sound will be emitted and received, thus the unit should be double as 29*2=58
  // Serial.println(distance);
  return distance;
}


