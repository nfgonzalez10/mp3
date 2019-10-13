#include <Wire.h>
#include <ST7032.h>
#include <Keypad.h>
#include <SoftwareSerial.h>
#include <DFPlayer_Mini_Mp3.h>

const int Previous = 5;
const int Play_Pause = 14;
const int Volume_High = 15;
const int Volume_Low = 16;
const int Next = 6;
const int Busy = 4; 
boolean Play_Status = false;
boolean First_Time = false;
boolean screen = false;
boolean state;
int Volume;
String Song;
int PISTA ;
const byte Rows = 4;
const byte Cols = 3;
ST7032 lcd;
char Keys[Rows][Cols] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

byte RowPins[Rows] = {10, 9, 8, 7}; //connect to the row pinouts of the keypad
byte ColPins[Cols] = {13, 12, 11}; //connect to the column pinouts of the keypad

Keypad Teclado = Keypad(makeKeymap(Keys), RowPins, ColPins, Rows, Cols);


void setup() {
  //Configuración pantalla
  lcd.begin(16,2);
  lcd.setContrast(40);
  lcd.clear();
  lcd.setCursor(3,0);//donde poner la linea
  lcd.print("BIENVENIDO!");//linea a escribir
  
  pinMode(Previous, INPUT);
  pinMode(Play_Pause, INPUT);
  pinMode(Next, INPUT);
  pinMode(Volume_High, INPUT);
  pinMode(Volume_Low, INPUT);
  pinMode(Busy, INPUT);
  Volume = 28;
  Song = String();

  Serial.begin (9600);
  mp3_set_serial (Serial);  //set softwareSerial for DFPlayer-mini mp3 module 
  delay(1);                   //wait 1ms for mp3 module to set volume
  mp3_reset ();
  delay(500);
  mp3_set_volume (15);
  mp3_set_playback_mode (1);
  delay(5000);
  lcd.clear();
  lcd.setCursor(1,0);//donde poner la linea
  lcd.print("SELECCIONE LA");
  lcd.setCursor(6,1);
  lcd.print("PISTA ");

  
}

void loop() {  
  
  char Key = Teclado.getKey();

  if(Key){
    if(Key == '1'){Song = Song + "1"; PISTA = 1;}
    if(Key == '2'){Song = Song + "2"; PISTA = 2;}
    if(Key == '3'){Song = Song + "3"; PISTA = 3;}
    if(Key == '4'){Song = Song + "4"; PISTA = 4;}
    if(Key == '5'){Song = Song + "5"; PISTA = 5;}
    if(Key == '6'){Song = Song + "6"; PISTA = 6;}
    if(Key == '7'){Song = Song + "7"; PISTA = 7;}
    if(Key == '8'){Song = Song + "8"; PISTA = 8;}
    if(Key == '9'){Song = Song + "9"; PISTA = 9;}
    if(Key == '0'){Song = Song + "0"; PISTA = 10;}
  }
    
  if(digitalRead(Play_Pause) == HIGH){
    while(digitalRead(Play_Pause) == HIGH){}
    
    if(Song == "" && First_Time == true){
      if(Play_Status == false){
      Play_Status = true;
      mp3_pause();
      
      } else { 
      Play_Status = false;
      mp3_play ();
    
    }
    }
     if(Song != ""){
      mp3_play (Song.toInt());
      Song = "";
      First_Time = true;
      Play_Status = false;
      }    
  }

 if(digitalRead(Volume_High) == HIGH){
    while(digitalRead(Volume_High) == HIGH){}
    if(Volume < 30){
      Volume = Volume + 2;
      mp3_set_volume (Volume);
      lcd.clear();
      lcd.setCursor(1,0);//donde poner la linea
      lcd.print("Volumen ");
      lcd.setCursor(6,1);
      lcd.print(Volume);
      delay(1000);
      lcd.clear();
  lcd.setCursor(0,0);//donde poner la linea
  lcd.print("REPRODUCIENDO LA");
  lcd.setCursor(5,1);//donde poner la linea
  lcd.print("´PISTA");
    lcd.setCursor(11,1);//donde poner la linea
  lcd.print(PISTA);
    } else {
      Volume = 30;
      mp3_set_volume (Volume);
    }
    }

  if(digitalRead(Volume_Low) == HIGH){
    while(digitalRead(Volume_Low) == HIGH){}
    if(Volume > 0){
      Volume = Volume - 2;
      mp3_set_volume (Volume);
      lcd.clear();
      lcd.setCursor(1,0);//donde poner la linea
      lcd.print("Volumen ");
      lcd.setCursor(6,1);
      lcd.print(Volume);
      delay(1000);
      lcd.clear();
  lcd.setCursor(0,0);//donde poner la linea
  lcd.print("REPRODUCIENDO LA");
  lcd.setCursor(5,1);//donde poner la linea
  lcd.print("PISTA ");
    lcd.setCursor(11,1);//donde poner la linea
  lcd.print(PISTA);
    } else {
      Volume = 0;
      mp3_set_volume (Volume);
    }
  } 

  if(digitalRead(Previous) == HIGH){
    while(digitalRead(Previous) == HIGH){}
   
    if(PISTA == 1){
      PISTA = 10;
      mp3_play (PISTA);
      }
      else{
         mp3_prev ();
    PISTA = PISTA - 1;
      }
  }

  if(digitalRead(Next) == HIGH){
    while(digitalRead(Next) == HIGH){}
   if(PISTA == 10){
      PISTA = 1;
      mp3_play (PISTA);}
   else{ mp3_next ();
    PISTA = PISTA+1;
   }
  }
 
 mp3_get_state ();
  int estado = mp3_wait_state();

  if( estado == 510){
  lcd.clear();
  lcd.setCursor(1,0);//donde poner la linea
  lcd.print("SELECCIONE LA");
  lcd.setCursor(6,1);
  lcd.print("PISTA ");
  estado=0;
  }

  if( estado == 511){
  lcd.clear();
  lcd.setCursor(0,0);//donde poner la linea
  lcd.print("REPRODUCIENDO LA");
  lcd.setCursor(5,1);//donde poner la linea
  lcd.print("PISTA ");
  lcd.setCursor(11,1);//donde poner la linea
  lcd.print(PISTA);
  estado = 0;
  }
if( estado == 512){
  lcd.clear();
  lcd.setCursor(1,0);//donde poner la linea
  lcd.print("Seleccione la");
  lcd.setCursor(6,1);
  lcd.print("PISTA ");
  estado =0;
  }
  

}
