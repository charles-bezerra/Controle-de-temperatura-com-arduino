#include<LiquidCrystal.h>
LiquidCrystal lcd(12,11,5,4,6,2);
long int pino = 2;
long int pinoMotor = 3;

int convercaoTemp(){
      long int pinoSensor = 0;
      int temperatura;
      temperatura = map(analogRead(pinoSensor),0,102,0,50);
      return temperatura;
}
int convercaoValorDesejado(){
      int valorDesejado;
      long int pinoleituraPotenciometro = 5;
      valorDesejado = map(analogRead(pinoleituraPotenciometro), 1080,0,0,50);
      return valorDesejado;
}
void setup(){
      Serial.begin(9600);
      lcd.begin(16,2);
      pinMode(pino, OUTPUT);
      digitalWrite(pino, HIGH); //Pino do potenciomentro, onde a há a fonte de tenção
      pinMode(pinoMotor, OUTPUT);
      
}



void loop(){ 
  if( convercaoTemp() > 60){
      Serial.println("Temperatura inválida");  
  } 
  
  else{
      lcd.print("TempAmb: ", convercaoTemp()); 
      lcd.setCursor(0,1);
      lcd.print("TempDesej: ", convercaoValorDesejado()); 
      Serial.print("Tenperatura: ");
      Serial.println(convercaoTemp());
      Serial.print("Temperatura desejada: ");
      Serial.println(convercaoValorDesejado());
      
      if(convercaoValorDesejado() < convercaoTemp()){
        
               // a encrementação tem que ser aqui
                digitalWrite(pinoMotor,HIGH);
               
        }
      else {               
                digitalWrite(pinoMotor, LOW);
      }
      delay(900);
  }
 
}
