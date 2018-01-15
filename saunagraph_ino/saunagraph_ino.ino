

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);


int sensorValue;
int temp;
float tempVerlauf[29] = {10,11,12,13,14,15,16,17,18,19,10,11,12,13,14,15,16,17,18,19,10,12,13,14,15};
int count;


unsigned long currentMillis;
unsigned long previousMillis;  // Saves the last time, when the graph was updated
unsigned long interval = 200;  // update interval [ms]


// declaration of characters

byte blanko = {B00000};
byte charFuenf[8];
byte charVier[8];
byte charDrei[8];
byte charZwei[8];
byte charEins[8];

byte termometer[8] = {
    B00100,
    B01010,
    B01010,
    B01010,
    B01010,
    B10001,
    B10001,
    B01110};




////////////////////////////
///////   SETUP   //////////
////////////////////////////
void setup() {
  lcd.begin(16, 2);
  lcd.createChar(6, termometer);
}

////////////////////////////
///////  L O O P  //////////
////////////////////////////
void loop() {
    lcd.clear();

// Temp from Poti
int sensorValue = analogRead(A0);
temp = map(sensorValue,0,1023,0,115);


// Refresh Graph
currentMillis = millis();

if(currentMillis - previousMillis > interval) {
previousMillis = currentMillis;   
  

// Add new value to array
  for(count = 0 ; count < 29 ; count++){
   tempVerlauf[count] = tempVerlauf[count+1];
  }  
  tempVerlauf[28] = temp;
 
// delete the old custom Chars
 for(count = 0 ; count < 8; count++){
  charFuenf[count] = blanko; 
  charVier[count] = blanko;
  charDrei[count] = blanko; 
  charZwei[count] = blanko; 
  charEins[count] = blanko;      
 }

// write the new byte arrays
for(count = 0 ; count < 5 ; count++){
  bitSet( charFuenf[7 - funcMapTemp(tempVerlauf[28-count])],count );
  bitSet( charVier[7 - funcMapTemp(tempVerlauf[22-count])], count );
  bitSet( charDrei[7 - funcMapTemp(tempVerlauf[16-count])], count );
  bitSet( charZwei[7 - funcMapTemp(tempVerlauf[10-count])], count );
  bitSet( charEins[7 - funcMapTemp(tempVerlauf[4-count])], count );  
}

// create custom chars from the arrays
  lcd.createChar(5, charFuenf);
  lcd.createChar(4, charVier);
  lcd.createChar(3, charDrei);
  lcd.createChar(2, charZwei);
  lcd.createChar(1, charEins);

// update chars on display  
  lcd.setCursor(15, 1);
  lcd.write(5);
  lcd.setCursor(14, 1);
  lcd.write(4); 
  lcd.setCursor(13, 1);
  lcd.write(3);
  lcd.setCursor(12, 1);
  lcd.write(2);  
  lcd.setCursor(11, 1);
  lcd.write(1); 
}  

// Line one
  lcd.setCursor(0,0);
  lcd.write(6);
  lcd.setCursor(1,0);
  lcd.print("=");
  lcd.print(temp);
  lcd.print(char(223));
  lcd.print("C  "); 
  
// Line two
lcd.setCursor(0,1);
  lcd.print("Temp.Graph:");

  

delay(1000);
}





int funcMapTemp (int t){
  // returns 0 for inputs below 73
  // returns 7 for inputs above 99
  // maps 73-99 to 0-7 in between
  
  int ZeroToSeven;
  
  if(t > 97){
   ZeroToSeven = 7; 
              }
  else if(t > 72){
  ZeroToSeven = map(t,68,97,0,7);
                  }
  else{
    ZeroToSeven = 0;
      }
    
 return ZeroToSeven; 
}



