#include<SoftwareSerial.h>
#include<Servo.h>
#include"pitches.h"

int inPin = 7; 
int val=0;
int x=0;
Servo myservo;
SoftwareSerial dispositivo(10,11);
char estado[]="ABCDEFGHIJKLMN OPQRSTUVWXYZ";
char pos=' ';
//                 A   B     C       D      E      F   G      H    I      J      K
double letras[] = {3 , 7.4 , 11.87 , 16.2 , 20.6 , 25, 29.6 , 34 , 40 , 44.4 , 180};
//4.4 grados

int melody[] = {
  NOTE_E7, NOTE_E7, 0, NOTE_E7, 
  0, NOTE_C7, NOTE_E7, 0,
  NOTE_G7, 0, 0,  0,
  NOTE_G6, 0, 0, 0, 

  
};
//Mario main them tempo
int tempo[] = {
  12, 12, 12, 12, 
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12, 

 
};


void setup(){
 Serial.begin(9600);
 dispositivo.begin(9600);
 myservo.attach(9);
 pinMode(inPin,INPUT);
 myservo.write(0);
 delay(100);
  // tone(4,NOTE_D4,10000);
 //delay(10000);
 //noTone(4);
 for (int thisNote = 0; thisNote < 16; thisNote++) {
  
   int noteDuration = 1000/tempo[thisNote];

   tone(4, melody[thisNote],noteDuration);

   int pauseBetweenNotes = noteDuration * 1.30;
   delay(pauseBetweenNotes);
   tone(4,0,noteDuration);}
 
}
//15 = O
void loop(){
 while(val==1){
   val=digitalRead(inPin);
 
   
 }

 if(dispositivo.available()>0)
  {
    pos = dispositivo.read();
    for(int i=0;i<27;i++)
     {
       if(pos == estado[i]||pos == NULL){   
         Serial.println(i);
         Serial.println(estado[i]);
         double grado = (double)i*((double)180/27);
         Serial.println(grado);
         myservo.write(grado);
         delay(500);
         tone(4,NOTE_E7,1500);
             
         delay(500);
         noTone(4);
         val = 0;
         while(val==0)
         {
           val = digitalRead(inPin);
         }     
       }
     }
  }
 

  
}
