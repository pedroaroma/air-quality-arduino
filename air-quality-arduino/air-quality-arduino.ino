#include <Arduino.h> 
#include <Wire.h> 
#include <MQUnifiedsensor.h>

#include <SD.h>
#include <SPI.h>

#define         Board                   ("Arduino NANO")
#define         Pin3                     (A0)  //Analog input 0 of your arduino
#define         Pin4                     (A1)  //Analog input 1 of your arduino
#define         Pin135                   (A2)  //Analog input 2 of your arduino
#define         Pin7                     (A3)  //Analog input 3 of your arduino
#define         Pin8                     (A4)  //Analog input 6 of your arduino
#define         Pin9                     (A5)  //Analog input 7 of your arduino

#define         RatioMQ3CleanAir          (60) //RS / R0 = 60 ppm 
#define         RatioMQ4CleanAir          (4.4) //RS / R0 = 4.4 ppm 
#define         RatioMQ135CleanAir        (3.6) //RS / R0 = 10 ppm 
#define         RatioMQ7CleanAir          (27.5) //RS / R0 = 27.5 ppm  
#define         RatioMQ8CleanAir          (70) //RS / R0 = 70 ppm   
#define         RatioMQ9CleanAir          (9.6) //RS / R0 = 9.6 ppm 
#define         ADC_Bit_Resolution        (10) // 10 bit ADC 
#define         Voltage_Resolution        (5) // Volt resolution to calc the voltage
#define         Type                      ("Arduino UNO") //Board used
//Declare Sensor
MQUnifiedsensor MQ3(Board, Voltage_Resolution, ADC_Bit_Resolution, Pin3, Type);
MQUnifiedsensor MQ4(Board, Voltage_Resolution, ADC_Bit_Resolution, Pin4, Type);
MQUnifiedsensor MQ135(Board, Voltage_Resolution, ADC_Bit_Resolution, Pin135, Type);
MQUnifiedsensor MQ7(Board, Voltage_Resolution, ADC_Bit_Resolution, Pin7, Type);
MQUnifiedsensor MQ8(Board, Voltage_Resolution, ADC_Bit_Resolution, Pin8, Type);
MQUnifiedsensor MQ9(Board, Voltage_Resolution, ADC_Bit_Resolution, Pin9, Type);


File myFile;
float Alcohol;
int pinoSS = 10;

void setup() {
  
  Serial.begin(9600);

  pinMode(pinoSS, OUTPUT);


  if (SD.begin()) { // Inicializa o SD Card
    Serial.println("SD Inicializado com sucesso."); // Imprime na tela
    myFile = SD.open("sensors.txt", FILE_WRITE);
  }
  else {
      Serial.println("Falha na inicialização do SD Card.");
  //return;
} 
  MQ3.init();
  MQ3.setRegressionMethod(1); //_PPM =  a*ratio^b
  MQ3.setR0(0.45);

  MQ4.init();
  MQ4.setRegressionMethod(1); //_PPM =  a*ratio^b
  MQ4.setR0(14.23);

  MQ135.init();
  MQ135.setRegressionMethod(1); //_PPM =  a*ratio^b
  MQ135.setR0(9.03);

  MQ7.init();
  MQ7.setRegressionMethod(1); //_PPM =  a*ratio^b
  MQ7.setR0(5.90);

  MQ8.init();
  MQ8.setRegressionMethod(1); //_PPM =  a*ratio^b
  MQ8.setR0(0.91);

  MQ9.init();
  MQ9.setRegressionMethod(1); //_PPM =  a*ratio^b
  MQ9.setR0(13.93);


/**
  Serial.print("Calibrating please wait.");
  float  MQ3calcR0 = 0,
         MQ4calcR0 = 0,
         MQ135calcR0 = 0,
         MQ7calcR0 = 0,
         MQ8calcR0 = 0,
         MQ9calcR0 = 0;
  for (int i = 1; i <= 10; i ++)
  {
    //Update the voltage lectures
    MQ3.update();
    MQ4.update();
    MQ135.update();
    MQ7.update();
    MQ8.update();
    MQ9.update();

    MQ3calcR0 += MQ3.calibrate(RatioMQ3CleanAir);
    MQ4calcR0 += MQ4.calibrate(RatioMQ4CleanAir);
    MQ135calcR0 += MQ135.calibrate(RatioMQ135CleanAir);
    MQ7calcR0 += MQ7.calibrate(RatioMQ7CleanAir);
    MQ8calcR0 += MQ8.calibrate(RatioMQ8CleanAir);
    MQ9calcR0 += MQ9.calibrate(RatioMQ9CleanAir);

    Serial.print(".");
  }
  MQ3.setR0(MQ3calcR0 / 10);
  MQ4.setR0(MQ4calcR0 / 10);
  MQ135.setR0(MQ135calcR0 / 10);
  MQ7.setR0(MQ7calcR0 / 10);
  MQ8.setR0(MQ8calcR0 / 10);
  MQ9.setR0(MQ9calcR0 / 10);
  Serial.println("  done!.");

  Serial.print("(MQ3 - MQ9):");
  Serial.print(MQ3calcR0 / 10); Serial.print(" | ");
  Serial.print(MQ4calcR0 / 10); Serial.print(" | ");
  Serial.print(MQ135calcR0 / 10); Serial.print(" | ");
  Serial.print(MQ7calcR0 / 10); Serial.print(" | ");
  Serial.print(MQ8calcR0 / 10); Serial.print(" | ");
  Serial.print(MQ9calcR0 / 10); Serial.println(" |");

  **/

}
void loop() {
  //Update the voltage lectures
  MQ3.update();
  MQ4.update();
  MQ135.update();  
  MQ7.update();
  MQ8.update();
  MQ9.update();


  //MQ3.setA(0.3934); MQ3.setB(-1.504); //Alcohol
//float Alcohol = MQ3.readSensor(); 
Alcohol = analogRead(A0); 

  MQ3.setA(4.8387); MQ3.setB(-2.68); //Benzene
float Benzene = MQ3.readSensor(); 
  
  MQ3.setA(7585.3); MQ3.setB(-2.849); //Hexane
float Hexane = MQ3.readSensor(); 

  MQ4.setA(1012.7); MQ4.setB(-2.786); //CH4
float CH4 = MQ4.readSensor(); 

  MQ4.setA(30000000); MQ4.setB(-8.308); //smoke 
float smoke = MQ4.readSensor(); 
 
  MQ135.setA(110.47); MQ135.setB(-2.862); //CO2 
float CO2 = MQ135.readSensor(); 
  
  MQ135.setA(44.947); MQ135.setB(-3.445); // Toluene
float Toluene = MQ135.readSensor(); 
  
  MQ135.setA(102.2 ); MQ135.setB(-2.473); //NH4 
float NH4 = MQ135.readSensor(); 
  
  MQ135.setA(34.668); MQ135.setB(-3.369); //Acetone
float Acetone = MQ135.readSensor(); 
 
  MQ7.setA(99.042); MQ7.setB(-1.518); //CO
float CO = MQ7.readSensor(); 

  MQ8.setA(976.97); MQ8.setB(-0.688); // H2
float H2 = MQ8.readSensor();

  MQ9.setA(1000.5); MQ9.setB(-2.186); //flamable gas
float FG = MQ9.readSensor();


/**
  Serial.print("Alcool:  "); Serial.println(Alcohol);
  Serial.print("Benzeno:  "); Serial.println(Benzene);
  Serial.print("Hexano:   "); Serial.println(Hexane);
  Serial.print("Metano:  "); Serial.println(CH4);
  Serial.print("Smoke:    "); Serial.println(smoke);
  Serial.print("Dioxido de carbono:      "); Serial.println(CO2);
  Serial.print("Tolueno:  "); Serial.println(Toluene);
  Serial.print("Amonia:      "); Serial.println(NH4);
  Serial.print("Acetona:  "); Serial.println(Acetone);  
  Serial.print("Monoxido de carbono:       "); Serial.println(CO);
  Serial.print("Hidrogenio:       "); Serial.println(H2);
  Serial.print("Gas inflamavel:       "); Serial.println(FG);
  Serial.println("--------------------------------------------------------");
*/
  if (myFile) {

   myFile.println("Escrevendo Alcool :");myFile.println(Alcohol);
   myFile.flush();
   delay(1000);
   myFile.println("Escrevendo Benzeno :"); myFile.println(Benzene);
   myFile.flush();
   delay(1000);
   myFile.println("Escrevendo Hexano :"); myFile.println(Hexane);
   myFile.flush();
   delay(1000);
   myFile.println("Escrevendo Metano :"); myFile.println(CH4);
   myFile.flush();
   delay(1000);
   /*
   myFile.println("Escrevendo Smoke :"); myFile.println(smoke);
   myFile.flush();
   delay(1000);
   myFile.println("Escrevendo Dióxido de carbono :"); myFile.println(CO2);
   myFile.flush();
   delay(1000);
   myFile.println("Escrevendo Tolueno :"); myFile.println(Toluene);
   myFile.flush();
   delay(1000);
   myFile.println("Escrevendo Amônia :"); myFile.println(NH4);
   myFile.flush();
   delay(1000);
   myFile.println("Escrevendo Acetona :"); myFile.println(Acetone);
   myFile.flush();
   delay(1000);
   myFile.println("Escrevendo Monóxido de carbono :"); myFile.println(CO);
   myFile.flush();
   delay(1000);
   myFile.println("Escrevendo Hidrogênio :"); myFile.println(H2);
   myFile.flush();
   myFile.println("Escrevendo Gas inflamavel :"); myFile.println(FG);
   delay(1000);
/*

    Serial.println("Escrevendo Alcool : ");
    myFile.println("Escrevendo Alcool :"); myFile.println(Alcohol);
    
    Serial.println("Escrevendo Benzeno : ");
    myFile.println("Escrevendo Benzeno :"); myFile.println(Benzene);

    Serial.println("Escrevendo Hexano : ");
    myFile.println("Escrevendo Hexano :"); myFile.println(Hexane);

    Serial.println("Escrevendo Metano : ");
    myFile.println("Escrevendo Metano :"); myFile.println(CH4);

    Serial.println("Escrevendo Smoke : ");
    myFile.println("Escrevendo Smoke :"); myFile.println(smoke);
 
    Serial.println("Escrevendo Dióxido de carbono : ");
    myFile.println("Escrevendo Dióxido de carbono :"); myFile.println(CO2);   
    
    Serial.println("Escrevendo Tolueno : ");
    myFile.println("Escrevendo Tolueno :"); myFile.println(Toluene);

    Serial.println("Escrevendo Amônia : ");
    myFile.println("Escrevendo Amônia :"); myFile.println(NH4);

    Serial.println("Escrevendo Acetona : ");
    myFile.println("Escrevendo Acetona :"); myFile.println(Acetone);
    
    //Serial.println("Escrevendo Monóxido de carbono : ");
    myFile.println("Escrevendo Monóxido de carbono :"); myFile.println(CO);
    
    //Serial.println("Escrevendo Hidrogênio : ");
    myFile.println("Escrevendo Hidrogênio :"); myFile.println(H2);

    //Serial.println("Escrevendo Gas inflamavel : ");
    myFile.println("Escrevendo Gas inflamavel :"); myFile.println(FG);

    myFile.flush();
*/
  }

  delay(2000);

}