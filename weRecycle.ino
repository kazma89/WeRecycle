//------------------------------ Importe de librerias ------------------------------------//
#include <LiquidCrystal.h>
#include <Servo.h>
#include <Wire.h>

//------------------------------ Seteando valores --------------------------------------//

// Arduino Pi
#define I2C_ADDRESS 0x04

//Servos para puerta
Servo puertaIzq;  
Servo puertaDer;
int posPuertaIzq = 0; 
int posPuertaDer = 0;
bool stopper = true;
int contadorPuertaIzq = 174;
int contadorPuertaDer = 0;


//LCD
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);


//Carrilera
Servo carrilera;
int interruptor = 46;
int entrada = 0;

//Deposito
int ncTrig = 51;
int ncEcho = 50;
int plasticoTrig;
int plasticoEcho;
int aluminioTrig;
int aluminioEcho;
long duracion, distancia;
int ledMedidor1 = 35;
int ledMedidor2 = 31;
int ledMedidor3 = 32;

void setup() {
  //----------------- Arduino Pi ---------------------//
  Serial.begin(9600);
  Serial.println("initialize");
  Wire.begin(I2C_ADDRESS);
  Wire.onReceive(dataReceive);
  Wire.onRequest(dataRequest);
  Serial.println(".");
  
  //----------------- Puertas ------------------------//
  puertaIzq.attach(9); 
  puertaDer.attach(6);
  puertaIzq.write(174);
   puertaDer.write(0);
  //------------------- LCD ---------------------------//
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("We Recycler");

  //Detecta Movimiento
  pinMode(interruptor,INPUT);

  //Carrilera
  carrilera.attach(10);

  //Nivel de Deposito
  pinMode(ncTrig, OUTPUT);
  pinMode(ncEcho, INPUT);
}

void loop() {
  inicio();
  detectaMovimiento();

  lcd.setCursor(0,1);
  lcd.print("              ");
  lcd.print("Proceso completo");
}

void inicio(){ //listo
  lcd.setCursor(0, 1); //Posiciona el curso columna,fila
  lcd.print("Introduce el");
  delay(2000);
  lcd.setCursor(0, 1);
  lcd.print("                 ");
  lcd.setCursor(0, 1);
  lcd.print("objeto.");
  delay(2000);
  lcd.setCursor(0, 1);
  lcd.print("                 ");
}

void abreDeposito(){ //listo
  lcd.setCursor(0,1);
  lcd.print("                  ");
  lcd.print("Procesando...");
  while(stopper){
    for (posPuertaIzq = contadorPuertaIzq; posPuertaIzq >= 94; posPuertaIzq -= 1) { // goes from 180 degrees to 0 degrees
      puertaIzq.write(posPuertaIzq);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
      break;
    }
    for(posPuertaDer = contadorPuertaDer; posPuertaDer <= 85; posPuertaDer += 1) { // goes from 180 degrees to 0 degrees
      puertaDer.write(posPuertaDer);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
      break;
    }
    Serial.println("Puerta izq "+contadorPuertaIzq);
    Serial.println("Puerta der "+contadorPuertaDer);
    contadorPuertaIzq --;
    contadorPuertaDer ++;
    if(posPuertaIzq >= 94 && posPuertaDer <= 85){
      stopper=true;  
    }
    else{
      stopper=false;  
    }
  }
    delay(2000);
    puertaIzq.write(174);
    puertaDer.write(0);
}

void carrilera(){ //listo
  int contador = 0;
  lcd.setCursor(0,1);
  lcd.print("                    ");
  lcd.setCursor("Procesando...");
  carrilera.write(70);
  delay();
  abreDeposito();
  carrilera.write(110);
  delay();
  // Mueve la carrilera hacia la posicion adecuada por medio de un contador que lo aumenta el interruptor
  if(interruptor == HIGH){
    contador ++;
    if(contador == posicion){
      carrilera.write(90);
      abreDeposito();
    }
  }
}

void detectaMovimiento(){  //listo
  //Este es para que prenda las luces, envie info al RPi por medio de un if usando el infrarojo como 
  //condicional, se conectara al RPi y le enviara un parametro por Serial para iniciar operacion
  entrada = digitalRead(interruptor);
  if(entrada == HIGH){
    lcd.setCursor(0,1);
    lcd.print("                   ");
    lcd.print("Objeto detectado");
    delay("2000");
    lcd.setCursor(0,1);
    lcd.print("                   ");
    lcd.print("Escaneando objeto...");
    carrilera(parametro que se recibe);
  }
  /*else{
    lcd.setCursor(0,1);
    lcd.print("                   ");
    lcd.print("Error!!!");
    delay("2000");
    lcd.setCursor(0,1);
    lcd.print("                   ");
    lcd.print("Vuelva a introducir");
    delay("2000");
    lcd.setCursor(0,1);
    lcd.print("                   ");
    lcd.print("el objeto.");
    delay("2000");
  }*/
}

void nivelDeposito(){
  digitalWrite(ncTrig, LOW);
  delayMicroseconds(2);
  digitalWrite(ncTrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(ncTrig, LOW);

  duracion = pulseIn(ncEcho, HIGH);
  distancia = ((duracion/2)/29);


  if(distancia > 10 || distancia <=0){
    digitalWrite(ledMedidor1,LOW);
    digitalWrite(ledMedidor2,LOW);
    digitalWrite(ledMedidor3,LOW);
    Serial.println("0");
  }
  else if(distancia <= 10 && distancia > 6){
    digitalWrite(ledMedidor1,HIGH);
    digitalWrite(ledMedidor2,LOW);
    digitalWrite(ledMedidor3,LOW);
    Serial.println("25");
  }
  else if(distancia <= 6 && distancia > 3){
    digitalWrite(ledMedidor1,HIGH);
    digitalWrite(ledMedidor2,HIGH);
    digitalWrite(ledMedidor3,LOW);
    Serial.println("65");
  }
  else{
    digitalWrite(ledMedidor1,HIGH);
    digitalWrite(ledMedidor2,HIGH);
    digitalWrite(ledMedidor3,HIGH);
    Serial.println("90");
  }
  
}

void dataRequest(){
  byte b[32];
  int availableBytes = Wire.available;
}
