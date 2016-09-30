#include<LiquidCrystal.h>                //estou importando a biblioteca do lcd
LiquidCrystal lcd(12,11,5,4,3,2);        //aqui estou definindo os pinos do lcd
long int pinoTransistor = 6;         

/*Função para formatar os valeros analogicos dados pelo sensor de temperatura, 
retornando o valor da temperatura ambiente.*/
int convercaoTemp(){
      long int pinoSensor = 0;
      int temperatura;
      temperatura = map(analogRead(pinoSensor),0,102,0,50);
      return temperatura;
}



/* Função para formatar os valeros analogicos dados pelo potenciometro, 
retornando o valor da temperatura desejada.*/
int convercaoValorDesejado(){  
      int valorDesejado;
      long int pinoleituraPotenciometro = 5;
      valorDesejado = map(analogRead(pinoleituraPotenciometro), 1080,0,15,30);
      return valorDesejado;
}



/*    Função que reberá como parametro dois argumentos x e y para serem 
      impressos no LCD 16x2, 
      x será a temperatura abiente e sera impresso na parte superior do LCD
      y será a temperatura desejada e sera impresso na parte inferior do LCD
 */ 
int imprimir_valores_lcd(int x,int y){
      lcd.clear();               //Limpa a tela  do lcd
      lcd.setCursor(0,0);        // imprimi o conteúdo anterior na coluna 0 e na linha 0
      lcd.print("TempAmb: ");    // imprimi o conteúdo entre aspas
      lcd.print(x);              // imprimindo o valor de x,por  parametro a temperatura ambiente 
      lcd.setCursor(0,1); 
      lcd.print("TempDesej: ");        
      lcd.print(y);              //imprimi o valor de y, por  parametro a temperatura desejada
}



int serialImprimir(int x, int y){
      Serial.print("Tenperatura: ");
      Serial.println(x);
      Serial.print("Temperatura desejada: ");
      Serial.println(y);
}



/*Essa Função foi criada com intuito de abestrair o valor 
 * analogico dado pelo pino do arduino que esta ligado 
  a base do transistor, regulando a quantidade 
  de giros do motor. A função pega a diferença de temperatura 
  da temperatura ambiente e a 
  temperatura desejada, para ser dado o valor 
  analogico correspondente esse valor multiplicado 
  por 7,5 que é a constante tirado de uma 
  equação do primeiro grau simples, onde 
  pegamos a menor temperatura que podemos chegar 
  que 16 graus C*, com diferença da maior temp fornecida que 
  podemos obserar pelo o sensor que é 50 graus C
  tem multiplicado por x dando igual ao valor anoligico 5V que é 255.*/
int Vanalog_Diferenca_Temp(int x, int y){ 
      float j =  x - y;
      return j * 7.5;    
}





void setup(){
      Serial.begin(9600);
      lcd.begin(16,2); // aqui estou especificando a quantidade de lacunas e linhas do lcd
      pinMode(pinoTransistor, OUTPUT);
      
}



void loop(){ 
  
  //Este if limita o codigo de receber valores correspondentes as temperaturas acima de 50 
  if( convercaoTemp() > 50){
      lcd.clear();
      lcd.setCursor(2,0);
      lcd.print("Temperatura");
      lcd.setCursor(3,1);
      lcd.print("Perigosa!");
      Serial.println("!!!Temperatura Perigosa!!!");
      analogWrite(pinoTransistor, 255);
      delay(1000);}
      
  else{ 
      /*aqui estou chamando a função para printar os conteudos para o lcd, 
      passando por parametros valores das funçoes que retornam a 
      temperatura ambiente e temperatura desejada */
      imprimir_valores_lcd(convercaoTemp(),convercaoValorDesejado()); 
       
      /*aqui estou chamando a função para printar os conteudos por comunicação serial, 
      passando por parametros valores das funçoes que retornam a t
      emperatura ambiente e temperatura desejada */
      serialImprimir(convercaoTemp(), convercaoValorDesejado());  

      /*Nesse if verificamos se a temperatura deseja é menor que a temperatura ambiente, se caso for e pino 
       do transistor é ativado na intensidade desejada, se caso for menor o pino do transistor é desligado */
      if(convercaoValorDesejado() < convercaoTemp()){              
            analogWrite( pinoTransistor ,Vanalog_Diferenca_Temp( convercaoTemp(),convercaoValorDesejado() ) );  }
      else {               
            digitalWrite(pinoTransistor, LOW);  }
      }
}
