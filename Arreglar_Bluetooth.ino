//Prototipo de plano de circuitos para coche :D
//Alan Ortiz Pérez 
#include <Servo.h>
#include <SoftwareSerial.h>
SoftwareSerial Bluetooth (A0,A1);
//#include <NewPing.h>   
const int ServoPIN =6;
Servo myservo;   
const int Echo= 13;
 const int Trigger= 12;
const int buzzerPin =10; 
const int ledsV=11;
const int ledsR=5;
const int MotorD1= 2;
const int MotorD2=3;
const int MotorI1= 7;
const int MotorI2= 9;
const int Derechos=4;
const int Izquierdos = 8;
const int Tx=0;
const int Rx=1;
#define MAX_DISTANCE 200 
//NewPing sonar(Trigger, Echo, MAX_DISTANCE); 
boolean goesForward=false;         
int distance = 100;               
int speedSet = 0;  
char valor;
void setup()

{
 //PWM
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledsV, OUTPUT);
  pinMode(ledsR, OUTPUT);
  pinMode(MotorD1,OUTPUT);
   pinMode(MotorD2, OUTPUT); //CONTROL DIGITAL -SENTIDO
  pinMode(MotorI1, OUTPUT);
  pinMode(MotorI2, OUTPUT); // ANALOGSPEED- VELOCIDAD ANALOGICA
  pinMode(Izquierdos, OUTPUT); //CONTROL DIGITAL -SENTIDO
  pinMode(Derechos, OUTPUT); //CONTROL DIGITAL -SENTIDO
  Serial.begin(9600);
  pinMode(Trigger, OUTPUT);
  pinMode(Echo, INPUT);  
 digitalWrite(Trigger, LOW);
    myservo.attach(ServoPIN);
  myservo.write(0);
}

void loop()

{
char valor;
 while (Serial.available() > 0)
  {
   valor = Serial.read();
  Serial.println(valor);
  
  if( valor == 'A')                   // Hacia adelante
    {
      Adelante();
    }
  else if(valor == 'K')              // Hacia atras
    {
      Atras();
    }
  
    else if(valor == 'I')             // Izquierda 
    {
    GiroIzq();
    }
    else if(valor == 'D')              //Derecha
    {
    GiroDer();
    }
      else if(valor == 'P')               //Stop - Pare, Carrito detenido
    {
    Alto();
    } 
       else if(valor == 'B')              //Bocina
    {
      tone(buzzerPin, 440, 200);
  delay(100);
  tone(buzzerPin, 466.164, 200);
  delay(100);
  tone(buzzerPin, 587.330, 200);
  delay(100);
  tone(buzzerPin, 554.365, 200);
  delay(100);
    tone(buzzerPin, 440, 200);
  delay(100);
  tone(buzzerPin, 466.164, 200);
  delay(100);
  tone(buzzerPin, 587.330, 200);
  delay(100);
  tone(buzzerPin, 554.365, 200);
  delay(100);
  noTone(buzzerPin);
    }
      else if(valor =='V')               //Stop - Pare, Carrito detenido
    {
    LucesV();
    digitalWrite(ledsR, LOW);
    } 
     else if(valor == 'R')               //Stop - Pare, Carrito detenido
    {
    digitalWrite(ledsR, HIGH);
digitalWrite(ledsV, LOW);    
    } 
         else if(valor == 'Q')               //Stop - Pare, Carrito detenido
    {
     long distanciaDer = 0;
 long distanciaIzq =  0;
delay(40); 
   long t; 
  long d; 
  digitalWrite(Trigger, HIGH);
  delayMicroseconds(10);          
  digitalWrite(Trigger, LOW);
  
  t = pulseIn(Echo, HIGH); 
  d = t/59;             
  

  Serial.print("Distancia: ");
  Serial.print(d);     
  Serial.print("cm");
  Serial.println();
  delay(1000); 
  if(d<15){
    digitalWrite(ledsV, LOW);
    Alto();
    delay(200);
    Advertencia();
    Atras();
    delay(800);
    Alto();
    delay(200);
   distanciaIzq = MiraIzq();
    delay(200);
   distanciaDer = MiraDer();
    delay(200);
    
    if(distanciaDer>= distanciaIzq){
      GiroDer();
      Alto();
    }        
    else
    {
      GiroIzq();
      Alto();
    }
  }
     else{
      Adelante();
      LucesV();
      delay(200);
  } 
    } 
  }
 

  }

int MiraDer()          
{
    myservo.write(50);    
    delay(500);
    int distance = readPing();
    delay(100);
    myservo.write(115);        
   
  digitalWrite(MotorD1, LOW);
digitalWrite(MotorD2, LOW);
  delay(1500);
analogWrite (Derechos, 255);
digitalWrite(MotorD1, LOW);
digitalWrite(MotorD2, HIGH);
delay(1000);
  digitalWrite(MotorD1, LOW);
digitalWrite(MotorD2, LOW);
Adelante();
   return distance;
}

int MiraIzq()
{
    myservo.write(170); 
    delay(500);
    int distance = readPing();
    delay(100);
    myservo.write(115); 
  digitalWrite(MotorI1, LOW);
digitalWrite(MotorI2, LOW);
  delay(1500);
  analogWrite (Izquierdos, 255);
digitalWrite(MotorI1, HIGH);
digitalWrite(MotorI2, LOW);
delay(1000);
  digitalWrite(MotorI1, LOW);
digitalWrite(MotorI2, LOW);
Adelante();
//  delay(1000);
    return distance;
}

int readPing() { 
  delay(70);
   long distanciaDer = 0;
 long distanciaIzq =  0;
delay(40); 
   long t; 
  long d; 
  digitalWrite(Trigger, HIGH);
  delayMicroseconds(10);          
  digitalWrite(Trigger, LOW);
  
  t = pulseIn(Echo, HIGH); 
  d = t/59; 
}


void Adelante(){
  analogWrite(Izquierdos, 255); //VELOCIDAD  64-lento 128-normal 255-rápido
 digitalWrite(MotorD2, HIGH);
 digitalWrite(MotorD1, LOW);
 analogWrite(Derechos, 255);
 digitalWrite(MotorI2, LOW);
 digitalWrite(MotorI1, HIGH);
}
void Alto(){
digitalWrite(MotorD2, LOW);
digitalWrite(MotorD1, LOW);
digitalWrite(MotorI1, LOW);
digitalWrite(MotorI2, LOW);
}
void Atras(){
  analogWrite(Izquierdos, 255); //VELOCIDAD  64-lento 128-normal 255-rápido
 digitalWrite(MotorD2, LOW);
 digitalWrite(MotorD1, HIGH);
 analogWrite(Derechos, 255);
 digitalWrite(MotorI2, HIGH);
 digitalWrite(MotorI1, LOW);
}
void Advertencia(){
 digitalWrite(ledsR, HIGH);
  tone(buzzerPin, 440, 200);
  delay(50);
  tone(buzzerPin, 466.164, 200);
  delay(50);
  tone(buzzerPin, 587.330, 200);
  delay(50);
  tone(buzzerPin, 554.365, 200);
  delay(50);
  noTone(buzzerPin);
}
void LucesV(){
 digitalWrite(ledsV, HIGH);
  noTone(buzzerPin);
  digitalWrite(ledsR, LOW);
}
void GiroIzq(){
    digitalWrite(MotorD1, LOW);
digitalWrite(MotorD2, LOW);
  delay(500);
analogWrite (Derechos, 255);
digitalWrite(MotorD1, LOW);
digitalWrite(MotorD2, HIGH);


}
void GiroDer(){
  digitalWrite(MotorD1, LOW);
digitalWrite(MotorD2, LOW);
  delay(500);
  analogWrite (Izquierdos, 255);
digitalWrite(MotorI1, HIGH);
digitalWrite(MotorI2, LOW);

}
//Bluetooh 
//B "bocina"
//A "arriba"
//K "abajo"
// D "derecha"
// I "izquierda"
// V "Leds verdes"
// R "leds rojos"
// S "cambios"
// P "parar
