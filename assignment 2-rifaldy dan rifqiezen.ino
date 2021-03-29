
//deklarasi
int sensor1 =A0;
int sensor2 =A1;
int sensor3 =A2;
int sensor4 =A3;
int sensor5 =A4;
int sensor6 =A5;
int baca_sensor[6];

int led1 =8;
int led2 =7;
int i;
int pinEnable = 4;
int pinEnable2 = 2;

int motor_kiri1 = 5;
int motor_kiri2 = 6;

int motor_kanan1 = 3;
int motor_kanan2 = 11;
int lasterror = 0;

void setup(){
pinMode(sensor1,INPUT);
pinMode(sensor2,INPUT);
pinMode(sensor3,INPUT);
pinMode(sensor4,INPUT);
pinMode(sensor5,INPUT);
pinMode(sensor6,INPUT);

pinMode(pinEnable, OUTPUT);
pinMode(pinEnable2, OUTPUT);
pinMode(motor_kiri1, OUTPUT);
pinMode(motor_kiri2, OUTPUT);
pinMode(motor_kanan1, OUTPUT);
pinMode(motor_kanan2, OUTPUT);
pinMode(led1,OUTPUT); 
pinMode(led2,OUTPUT);

Serial.begin(9600);
}
void readsensor(){
baca_sensor[0] = analogRead(sensor1);
baca_sensor[1] = analogRead(sensor2);
baca_sensor[2] = analogRead(sensor3);
baca_sensor[3] = analogRead(sensor4);
baca_sensor[4] = analogRead(sensor5);
baca_sensor[5] = analogRead(sensor6); 
delay(500);
//untuk menampilkan data pada sensor
  for (int x=0; x<6; x++){
   Serial.print("Sensor");
   Serial.print(x+1);
   Serial.print(": ");
   Serial.print(baca_sensor[x]);
   Serial.print("\n");
  }
}
void loop(){
//untuk menapilkan data sensor last error
readsensor();
Serial.print("nilai last error : ");
Serial.print(lasterror);
Serial.print("\n");

//Sensor 1 dan 2 mendeteksi gelap, sisanya terang  Duty cycle 0 % motor 
//kiri, 50% motor kanan
if(baca_sensor[0] < 34 && baca_sensor[1] < 34 && baca_sensor[2] > 34 && baca_sensor[3] > 34 && baca_sensor[4] > 34 && baca_sensor[5] > 34 ){
digitalWrite(pinEnable, HIGH);
analogWrite(motor_kiri1, 20);
analogWrite(motor_kiri2, 0);
digitalWrite(pinEnable2, HIGH);
analogWrite(motor_kanan1, 185);
analogWrite(motor_kanan2, 0);
	}
//Sensor 2 dan 3 mendeteksi gelap, sisanya terang  Duty cycle 20% 
//motor kiri, 50% motor kanan
else if(baca_sensor[0] > 34 && baca_sensor[1] < 34 && baca_sensor[2] < 34 && baca_sensor[3] > 34 && baca_sensor[4] > 34 && baca_sensor[5] > 34 ){
digitalWrite(pinEnable, HIGH);
analogWrite(motor_kiri1, 85);
analogWrite(motor_kiri2, 0);
digitalWrite(pinEnable2, HIGH);
analogWrite(motor_kanan1, 185);
analogWrite(motor_kanan2, 0);
	}
//Sensor 3 dan 4 mendeteksi gelap, sisanya terang  Duty cycle 60% pada 
//kedua motor (kedua motor aktif)
else if(baca_sensor[0] > 34 && baca_sensor[1] > 34 && baca_sensor[2] < 34 && baca_sensor[3] < 34 && baca_sensor[4] > 34 && baca_sensor[5] > 34 ){
digitalWrite(pinEnable,HIGH);
analogWrite(motor_kiri1,220);
analogWrite(motor_kiri2,0);
digitalWrite(pinEnable2, HIGH);
analogWrite(motor_kanan1,220);
analogWrite(motor_kanan2,0);
	}
//Sensor 4 dan 5 mendeteksi gelap, sisanya terang  Duty cycle 50% 
//motor kiri, 20% motor kanan
else if(baca_sensor[0] > 34 && baca_sensor[1] > 34 && baca_sensor[2] > 34 && baca_sensor[3] < 34 && baca_sensor[4] < 34 && baca_sensor[5] > 34 ){
digitalWrite(pinEnable,HIGH);
analogWrite(motor_kiri1,185);
analogWrite(motor_kiri2,0);
digitalWrite(pinEnable2, HIGH);
analogWrite(motor_kanan1,85);
analogWrite(motor_kanan2,0);
	}
//Sensor 5 dan 6 mendeteksi gelap, sisanya terang  Duty cycle 50% 
//Motor kiri, 0% motor kanan
else if(baca_sensor[0] > 34 && baca_sensor[1] > 34 && baca_sensor[2] > 34 && baca_sensor[3] > 34 && baca_sensor[4] < 34 && baca_sensor[5] < 34 ){
digitalWrite(pinEnable,HIGH);
analogWrite(motor_kiri1,185);
analogWrite(motor_kiri2,0);
digitalWrite(pinEnable2, HIGH);
analogWrite(motor_kanan1,20);
analogWrite(motor_kanan2,0);
	}
//Semua sensor mendeteksi terang  Duty cycle kedua motor 0% (semua 
//motor mati) 
else if(baca_sensor[0] > 34 && baca_sensor[1] > 34 && baca_sensor[2] > 34 && baca_sensor[3] > 34 && baca_sensor[4] > 34 && baca_sensor[5] > 34 ){
digitalWrite(pinEnable,HIGH);
analogWrite(motor_kiri1,20);
analogWrite(motor_kiri2,0);
digitalWrite(pinEnable2, HIGH);
analogWrite(motor_kanan1,20);
analogWrite(motor_kanan2,0);
Serial.print("robot keluar lintasan");
Serial.print("\n");
for(i=0; i<=255; i+=255){
analogWrite(led1,i);
analogWrite(led2,i);
}
delay(50);
for(i=255; i>=0; i-=255){
analogWrite(led1,i);
analogWrite(led2,i);
  }
delay(50);

}//batas
else if(baca_sensor[0] < 34 && baca_sensor[1] > 34 && baca_sensor[2] > 34 && baca_sensor[3] > 34 && baca_sensor[4] > 34 && baca_sensor[5] > 34 ){
lasterror =-2;


}
else if(baca_sensor[0] > 34 && baca_sensor[1] < 34 && baca_sensor[2] > 34 && baca_sensor[3] > 34 && baca_sensor[4] > 34 && baca_sensor[5] > 34 ){
lasterror =-1;

  
}
else if(baca_sensor[0] > 34 && baca_sensor[1] > 34 && baca_sensor[2] < 34 && baca_sensor[3] < 34 && baca_sensor[4] > 34 && baca_sensor[5] > 34 ){
lasterror =0;

}
else if(baca_sensor[0] > 34 && baca_sensor[1] > 34 && baca_sensor[2] > 34 && baca_sensor[3] > 34 && baca_sensor[4] < 34 && baca_sensor[5] > 34 ){
lasterror =1;
}
else if(baca_sensor[0] > 34 && baca_sensor[1] > 34 && baca_sensor[2] > 34 && baca_sensor[3] > 34 && baca_sensor[4] > 34 && baca_sensor[5] < 34 ){
lasterror =2;

};
}