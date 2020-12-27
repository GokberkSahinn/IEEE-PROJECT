#include <dht11.h>
#include<Keypad.h>  //libraries
#include <LiquidCrystal.h>
#define buzzer 22   ////buzzer pin
#define DHT11PIN 24  ///dht pin
dht11 DHT11;
int chk;
int pills = 30;
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);  //Lcd pin--> LiquidCrystal(rs, enable, d4, d5, d6, d7)

                                        
const int lock_relay=50; //Selenoid Lock System pin
const byte rows = 4;  //rows
const byte columbs = 4;  //columbs
char password[4] = {'1', '2', '3', '4'}; //default password we can change it from here and also change it int he void loop!
char password1[4];  //password that we will click on the keypad
char tus;   //char key 
int i = 0;
char key_pad[4][4] = {   
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rows_pins[4] = {30,31,32,33};  //rows_pins connected which pins
byte columb_pins[4] = {34,35,36,37};    //columb_pins connecting which pins

Keypad keyy_pad = Keypad(makeKeymap(key_pad), rows_pins, columb_pins, 4, 4);  // special code from Keypad library. basically create map usin name of keypad and row_pins,columb_pins


byte customChar9[8] = {  //in order to create animation LOADING EFFECT 
  
  0b11111, 
  0b11111,
  0b11111,   
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111
};
byte customChar8[8] = {
  0b11110,
  0b11110,
  0b11110,
  0b11110,
  0b11110,
  0b11110,
  0b11110,
  0b11110
};
byte customChar7[8] = {
  0b11100,
  0b11100,
  0b11100,
  0b11100,
  0b11100,
  0b11100,
  0b11100,
  0b11100
};
byte customChar6[8] = {
  0b11000,
  0b11000,
  0b11000,
  0b11000,
  0b11000,
  0b11000,
  0b11000,
  0b11000
};
byte customChar5[8] = {
  0b10000,
  0b10000,
  0b10000,
  0b10000,
  0b10000,
  0b10000,
  0b10000,
  0b10000
};
byte customChar4[8] = {
  0b00001,
  0b00011,
  0b00011,
  0b00111,
  0b00111,
  0b01111,
  0b01111,
  0b11111
};
byte customChar3[8] = {
  0b00000,
  0b00010,
  0b00010,
  0b00110,
  0b00110,
  0b01110,
  0b01110,
  0b11110
};
byte customChar2[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00100,
  0b00100,
  0b01100,
  0b01100,
  0b11100
};
byte customChar1[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b01000,
  0b01000,
  0b11000
};

byte customChar0[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b10000
};

void setup() {
  
  Serial.begin(9600);
  pinMode(lock_relay,OUTPUT);
  pinMode(buzzer, OUTPUT);
  
  lcd.createChar(0, customChar0);
  lcd.createChar(1, customChar1);
  lcd.createChar(2, customChar2);
  lcd.createChar(3, customChar3);
  lcd.createChar(4, customChar4);
  lcd.createChar(5, customChar5);
  lcd.createChar(6, customChar6);
  lcd.createChar(7, customChar7);
  lcd.createChar(8, customChar8);
  lcd.createChar(9, customChar9);
  lcd.begin(16, 2); // LCD BEGAN
  lcd.clear();  //Clear screen
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("LOADING");//Clear screen
  
  for (int i = 1; i <= 13; i++)  // used 2 for loop in order to create LOADING EFFECT
  {


    for (int k = 6; k <= 9; k++)
    {
      lcd.setCursor(i, 1); 
      lcd.write((uint8_t)k);
      delay(25);
  }
}
   lcd.clear();
  lcd.setCursor(0, 0); 
  lcd.print("ENTER PASSWORD:");    //YOU CAN PRINT HERE WHAT EVER YOU WANT ,THIS MEAN PASSWORD:
}

void loop() {
  if(pills==0){
    pills=30;
  }
  
  digitalWrite(lock_relay,HIGH);
if(i<=4){
  tus = keyy_pad.getKey();  
}
  if (tus && i<=4)   
  {
    password1[i++] = tus;  

    lcd.setCursor(i, 1); 
    lcd.print("*");    
    digitalWrite(buzzer,HIGH);
    delay(100);
    digitalWrite(buzzer,LOW);
  }  
  if (i == 4)
  {delay(200);
    char password[4] = {'1', '2', '3', '4'}; //default password u should write here like that 
    char temp_control[4]={'0','0','0','0'};
    
    
     if((strncmp(password1, temp_control, 4) == 0)){
      delay(2000);
      lcd.clear();
      chk = DHT11.read(DHT11PIN);
      lcd.setCursor(0,0);
      lcd.print("Temp:");
      lcd.print((float)DHT11.temperature, 13);
      delay(500);
      lcd.clear();
      lcd.setCursor(0, 0); 
      lcd.print("ENTER PASSWORD:");  
      i = 0;
      }
    else if ((strncmp(password1, password, 4) == 0))   //comparing these passwords if first 4 element correct then  process will be as follows
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      
      digitalWrite(lock_relay,LOW);
      pills=pills-1;
      lcd.print("PASSWORD CORRECT");
      delay(1500);
      lcd.clear(); 
      lcd.setCursor(0,0);
      lcd.print("Amount of pills : ");
      lcd.setCursor(0,1);
      lcd.print((float)pills); 
      digitalWrite(buzzer, HIGH);
      delay(100);
      digitalWrite(buzzer, LOW);
      delay(100);
      digitalWrite(buzzer, HIGH);
      delay(100);
      digitalWrite(buzzer, LOW);
      delay(3000);   ///////IMPORTANT---This delay that controls the selenoid closing time
      lcd.clear();
      lcd.setCursor(0, 0); 
      lcd.print("ENTER PASSWORD:");  
      i = 0;
    }

    else
    {
      lcd.clear();
      lcd.setCursor(0, 0); 
      lcd.print("WRONG PASSWORD!");  
      digitalWrite(buzzer, HIGH);
      delay(1000);
      digitalWrite(buzzer, LOW);
     
      delay(1000);
   lcd.clear();  
  lcd.setCursor(0, 0); 
  lcd.print("ENTER PASSWORD:");    
   delay(1000);

      i = 0;
    }
  }
}
