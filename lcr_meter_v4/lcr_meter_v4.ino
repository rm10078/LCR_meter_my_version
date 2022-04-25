#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);
                
                //declearation pi
const uint8_t r_sacal0=3,r_sacal1=4,r_sacal2=5,r_sacal3=6,r_check= A1,r_sacal00=13,res_power=12; //resistor_mes_pin
const uint8_t up_but=7,down_but=9,ok_but=8,back_but=2,bt_pin=A3;  //menu cont
const uint8_t ind_check=11,ind_charge=10;   //inductor
boolean debug=true;

boolean cap_ADC=false;

const int OUT_PIN = A2;
const int IN_PIN = A0;
const float IN_STRAY_CAP_TO_GND = 39.5362425;
const float IN_CAP_TO_GND  = IN_STRAY_CAP_TO_GND;
const float R_PULLUP = 34.8;  
const int MAX_ADC_VALUE = 1023;

int8_t count=1;
int dt=250;
float tem=0;

unsigned long tc=0,startTime=0;
      //default parameter
float sys_volt=5.0;

//const float r0=226,r1=2200-25,r2=(235-25E-3),r3=(470-25E-3),r00=(19.86-25E-3);

const float r0=226,r1=2200,r2=235,r3=470,r00=19.86;

//const float div0_volt=sys_volt,div1_volt=4.961,div2_volt=4.95,div3_volt=4.98;

const float div0_volt=sys_volt,div1_volt=sys_volt,div2_volt=sys_volt,div3_volt=sys_volt;

float cap=1.974E-6;

void display_mode();
void display_menu();
void menu_control();
void display_value(float val,String r);
void menu_back();
void battery_check();
float supply_voltage();

void setup() {
  pinMode(up_but,INPUT_PULLUP);
  pinMode(down_but,INPUT_PULLUP);
  pinMode(ok_but,INPUT_PULLUP);
  pinMode(back_but,INPUT_PULLUP);

  pinMode(r_sacal0,INPUT);
  pinMode(r_sacal1,INPUT);
  pinMode(r_sacal2,INPUT);
  pinMode(r_sacal00,INPUT);


  pinMode(OUT_PIN, OUTPUT);
  pinMode(IN_PIN, OUTPUT);
  pinMode(res_power,OUTPUT);

  pinMode(ind_charge,OUTPUT);
  pinMode(ind_check,INPUT);

  pinMode(bt_pin,INPUT);
  //sys_volt=supply_voltage();
  Serial.begin(9600);

  lcd.init();
  lcd.init();
  lcd.backlight();
   lcd.setCursor(0,0);
    lcd.print("Supply voltage");
    lcd.setCursor(0,1);
    lcd.print(supply_voltage());
    lcd.setCursor(12,1);
    lcd.print("V");
  delay(500);
  lcd.clear();
  display_menu();
  menu_control();
  display_mode();

}

void loop() {
  if(count==2){                         //resistor 0
    digitalWrite(res_power,HIGH);
    tem=0;
    pinMode(r_sacal00,OUTPUT);
    digitalWrite(r_sacal00,LOW);
    delay(dt);
    for(int i=0;i<150;i++){
      tem +=analogRead(r_check);
      delay(5);
      }
    float adc =tem/150;
    float a_volt=(adc*sys_volt)/1023;
    if(debug==true){
      Serial.print("vout = ");
      Serial.println(a_volt);
      Serial.print("ADB_V =");
      Serial.println(analogRead(r_check));
      }
    float temp=(div0_volt/a_volt)-1;//div0_volt
    float unknown_r=(temp*r00);
    display_value(unknown_r,"Kohm");
    
    pinMode(r_sacal00,INPUT);

    while(digitalRead(ok_but)==1){
  if(digitalRead(back_but)==0){
      menu_back();
      break;
  }
  
    if(digitalRead(back_but)==0){
      menu_back();
      }
    }
  }

  else if(count==0){
     tem=50;
     display_value(tem,"%");
     pinMode(r_sacal0,OUTPUT);
     TCCR2B = TCCR2B & B11111000 | B00000001; // frequency  31372.55 Hz  pin 3 & 11
     while(true){

      if(digitalRead(up_but)==0){
        while(digitalRead(up_but)==0){}
        tem++;
         if(tem>100){
        tem=0;
        }
      else if(tem<0){
        tem=100;
        }

        display_value(tem,"%");
        }

      else if(digitalRead(down_but)==0){
        while(digitalRead(down_but)==0){}
        tem--;
         if(tem>100){
        tem=0;
        }
      else if(tem<0){
        tem=100;
        }

        display_value(tem,"%");
        }

      else if(digitalRead(ok_but)==0){
        while(digitalRead(ok_but)==0){}
        int temm=map(tem,0,100,0,255);
        analogWrite(r_sacal0,temm);
        display_value(tem,"set");
        }
      else if(digitalRead(back_but)==0){
      pinMode(r_sacal0,INPUT);
      menu_back();
      break;
      }
      }
    }

  else if(count==1){                        //resistor 1
    digitalWrite(res_power,HIGH);
    tem=0;
    pinMode(r_sacal1,OUTPUT);
    digitalWrite(r_sacal1,LOW);
    delay(dt);
    for(int i=0;i<150;i++){
      tem +=analogRead(r_check);
      delay(5);
      }
    float adc =tem/150;
    float a_volt=(adc*sys_volt)/1023;
    if(debug==true){
      Serial.print("vout = ");
      Serial.println(a_volt);
      }
    float temp=(div1_volt/a_volt)-1;
    float unknown_r=(temp*r1);
    if(unknown_r<90){
    display_value(unknown_r-27,"ohm");
    }
    else if(unknown_r<1000){
    display_value(unknown_r-25,"ohm");
    }
    else{
      display_value((unknown_r-25)/1000,"Kohm");
      }
    
    pinMode(r_sacal1,INPUT);
    
   while(digitalRead(ok_but)==1){
  if(digitalRead(back_but)==0){
      menu_back();
      break;
  }
   
    if(digitalRead(back_but)==0){
      menu_back();
      }
    }
  }
    
  else if(count==3){                                  //resistor 2
    digitalWrite(res_power,HIGH);
    tem=0;
    pinMode(r_sacal2,OUTPUT);
    digitalWrite(r_sacal2,LOW);
    delay(dt);
    for(int i=0;i<50;i++){
      tem +=analogRead(r_check);
      delay(5);
      }
    float adc =tem/50;
    float a_volt=(adc*sys_volt)/1023;
    if(debug==true){
      Serial.print("vout = ");
      Serial.println(a_volt);
      }
    float temp=(div2_volt/a_volt)-1;
    float unknown_r=(temp*r2);
    display_value(unknown_r,"kohm");
    
    pinMode(r_sacal2,INPUT);
  
  while(digitalRead(ok_but)==1){
  if(digitalRead(back_but)==0){
      menu_back();
      break;
  }
  
    if(digitalRead(back_but)==0){
      menu_back();
      }
    }
  }
    
  else if(count==4){                                        //resistor 3
    digitalWrite(res_power,HIGH);
    tem=0;
    pinMode(r_sacal3,OUTPUT);
    digitalWrite(r_sacal3,LOW);
    delay(dt);
    
    for(int i=0;i<50;i++){
      tem +=analogRead(r_check);
      delay(5);
      }
    float adc =tem/50;
    float a_volt=(adc*sys_volt)/1023;
    if(debug==true){
      Serial.print("vout = ");
      Serial.println(a_volt);
      }
    float temp=(div3_volt/a_volt)-1;
    float unknown_r=(temp*r3);
    display_value(unknown_r,"kohm");
    
    pinMode(r_sacal3,INPUT);

while(digitalRead(ok_but)==1){
  if(digitalRead(back_but)==0){
      menu_back();
      break;
  }
  
    if(digitalRead(back_but)==0){
      menu_back();
      }
    }
  } 
  else if(count==5){                                    //inductor
  tem =0;
  pinMode(ind_charge,OUTPUT);
  digitalWrite(ind_charge, HIGH);
  delay(5);
  digitalWrite(ind_charge,LOW);
  pinMode(ind_charge,INPUT);
  delayMicroseconds(10);
  unsigned long pulse = pulseIn(ind_check,LOW,5000);

  float frequency = 1.E6/(2*pulse);
  float inductance = 1./(cap*frequency*frequency*4.*3.14159*3.14159);
  inductance *= 1E6;
  if(debug==true){
      Serial.print("frequency = ");
      Serial.println(frequency);
      Serial.print("pulse = ");
      Serial.println(pulse);
      }
  display_value(inductance,"uH");
  while(digitalRead(ok_but)==1){
  if(digitalRead(back_but)==0){
      menu_back();
      break;
  }
  
    if(digitalRead(back_but)==0){
      menu_back();
      }
      
    }
  }
   
  else if(count==6){

  pinMode(r_sacal0, OUTPUT);            
  digitalWrite(r_sacal0, LOW);        
  while(analogRead(r_check) > 0){
    delay(50);         
  }
  pinMode(r_sacal0, INPUT);
  //charge
  if(cap_ADC==0){
  pinMode(r_sacal2,OUTPUT);
  digitalWrite(r_sacal2, HIGH);  
  startTime = micros();
  while(digitalRead(bt_pin)==1){} //analogRead(r_check) < 648 && 
  tc= micros() - startTime;
  }
  else{
      pinMode(r_sacal2,OUTPUT);
  digitalWrite(r_sacal2, HIGH);  
  startTime = micros();
  while(analogRead(r_check) < 647){} 
  tc= micros() - startTime;
    }
  float mf = ((tc*1.0E-6) / r2*1E3 ) ;//    //259100

   if(mf<=1){
    display_value((mf*1000)-0.08,"nf");
    }
  else{
  display_value(mf,"uf");
  }

  if(debug==true){
      Serial.print("TC = ");
      Serial.println(tc);
      }
  //discharge
  digitalWrite(r_sacal2, LOW);            
  pinMode(r_sacal0, OUTPUT);            
  digitalWrite(r_sacal0, LOW);         
  while(analogRead(r_check) > 0){         
  delay(50);
  }
  pinMode(r_sacal0, INPUT);
  pinMode(r_sacal2, INPUT);
while(digitalRead(ok_but)==1){
  if(digitalRead(back_but)==0){
      menu_back();
      break;
  }
    if(digitalRead(back_but)==0){
      menu_back();
      }
    }
  }


    
  else if(count==7){
  pinMode(r_sacal0, OUTPUT);            
  digitalWrite(r_sacal0, LOW);        
  while(analogRead(r_check) > 0){
    delay(100);         
  }
  pinMode(r_sacal0, INPUT);
  //charge
  if(cap_ADC==0){
  pinMode(r_sacal1,OUTPUT);
  digitalWrite(r_sacal1, LOW);
  while(analogRead(r_check) > 0){
    delay(10);         
  }
  digitalWrite(r_sacal1, HIGH);  
  startTime = micros();
  while(digitalRead(bt_pin)==1){} //analogRead(r_check) < 648 && 
  tc= micros() - startTime;
  }
  else{
  pinMode(r_sacal1,OUTPUT);
  digitalWrite(r_sacal1, LOW);
  pinMode(r_sacal0, INPUT);
  digitalWrite(r_sacal1, HIGH); 
  startTime = micros();
  while(analogRead(r_check) < 634){} 
  tc= micros() - startTime;    
    }
    tc-=8;
  float mf = ((float)tc / 2200) ;// 2200
  if(mf<=1){
    display_value((mf*1000),"nf");
    }
  else{
  display_value(mf,"uf");
  }
  if(debug==true){
      Serial.print("TC = ");
      Serial.println(tc);
      }
  //discharge
  digitalWrite(r_sacal1, LOW);            
  pinMode(r_sacal0, OUTPUT);            
  digitalWrite(r_sacal0, LOW);         
  while(analogRead(r_check) > 0){         
  delay(50);
  }
  pinMode(r_sacal0, INPUT);
  pinMode(r_sacal2, INPUT);

while(digitalRead(ok_but)==1){
  if(digitalRead(back_but)==0){
      menu_back();
      break;
  }
  
    if(digitalRead(back_but)==0){
      menu_back();
      }
    
    }
}
    
  else if(count==8){
    
    int val=0;
    pinMode(IN_PIN, INPUT);
    digitalWrite(OUT_PIN, HIGH);
    val = analogRead(IN_PIN);
    digitalWrite(OUT_PIN, LOW);
    
    if (val < 1000)
    {
      long val0=0;
      for(int i=0;i<800;i++){
     pinMode(IN_PIN, INPUT);
    digitalWrite(OUT_PIN, HIGH);
    val0 += analogRead(IN_PIN);
    digitalWrite(OUT_PIN, LOW);
        }
        int val00 = val0/800;
        
      pinMode(IN_PIN, OUTPUT);

      if(debug==true){
        Serial.print("pf_analog value: ");
        Serial.println(val00);
        }
      
      float capacitance = (float)val00 * IN_CAP_TO_GND / (float)(MAX_ADC_VALUE - val);
      display_value(capacitance,"pF");
    }
    else
    {
      pinMode(IN_PIN, OUTPUT);
      delay(1);
      pinMode(OUT_PIN, INPUT_PULLUP);
      unsigned long u1 = micros();
      unsigned long t;
      int digVal;

      do
      {
        digVal = digitalRead(OUT_PIN);
        unsigned long u2 = micros();
        t = u2 > u1 ? u2 - u1 : u1 - u2;
      } 
      
      while ((digVal < 1) && (t < 400000L));

      pinMode(OUT_PIN, INPUT);  
      val = analogRead(OUT_PIN);
      digitalWrite(IN_PIN, HIGH);
      int dischargeTime = (int)(t / 1000L) * 5;
      delay(dischargeTime);   
      pinMode(OUT_PIN, OUTPUT);  
      digitalWrite(OUT_PIN, LOW);
      digitalWrite(IN_PIN, LOW);

      float capacitance = -(float)t / R_PULLUP / log(1.0 - (float)val / (float)MAX_ADC_VALUE);

       if(debug==true){
        Serial.print("analog value: ");
        Serial.println(val);
        }
      
      
      if (capacitance > 1000.0)
      {
        display_value(capacitance/1000.0,"uF");
      }
        
      else
      {
        display_value(capacitance,"nF");
      }
  }
    while (micros() % 1000 != 0);

while(digitalRead(ok_but)==1){
  if(digitalRead(back_but)==0){
      menu_back();
      break;
  }
      
    if(digitalRead(back_but)==0){
      menu_back();
      }
    }
  }



                        //resistor auto
  else if(count==9){

    digitalWrite(res_power,HIGH);
    tem=0;
    pinMode(r_sacal00,OUTPUT);
    digitalWrite(r_sacal00,LOW);
    delay(dt);
    for(int i=0;i<150;i++){
      tem +=analogRead(r_check);
      delay(5);
      }
    float adcc =tem/150;
    float a_voltt=(adcc*sys_volt)/1023;
    if(debug==true){
      Serial.print("vout = ");
      Serial.println(a_voltt);
      Serial.print("ADB_V =");
      Serial.println(analogRead(r_check));
      }
    float tempp=(div0_volt/a_voltt)-1;//div0_volt
    float unknown_rr=(tempp*r00);
  pinMode(r_sacal0,INPUT);
  pinMode(r_sacal1,INPUT);
  pinMode(r_sacal2,INPUT);
  pinMode(r_sacal00,INPUT);

   if(unknown_rr<20 && unknown_rr>2){                         //resistor 0
    digitalWrite(res_power,HIGH);
    tem=0;
    pinMode(r_sacal00,OUTPUT);
    digitalWrite(r_sacal00,LOW);
    delay(dt);
    for(int i=0;i<150;i++){
      tem +=analogRead(r_check);
      delay(5);
      }
    float adc =tem/150;
    float a_volt=(adc*sys_volt)/1023;
    if(debug==true){
      Serial.print("vout = ");
      Serial.println(a_volt);
      Serial.print("ADB_V =");
      Serial.println(analogRead(r_check));
      }
    float temp=(div0_volt/a_volt)-1;//div0_volt
    float unknown_r=(temp*r00);
    display_value(unknown_r,"Kohm");
    
    pinMode(r_sacal00,INPUT);  
    if(digitalRead(back_but)==0){
      menu_back();
      }
  }

  else if(unknown_rr<=2){                        //resistor 1
    digitalWrite(res_power,HIGH);
    tem=0;
    pinMode(r_sacal1,OUTPUT);
    digitalWrite(r_sacal1,LOW);
    delay(dt);
    for(int i=0;i<150;i++){
      tem +=analogRead(r_check);
      delay(5);
      }
    float adc =tem/150;
    float a_volt=(adc*sys_volt)/1023;
    if(debug==true){
      Serial.print("vout = ");
      Serial.println(a_volt);
      }
    float temp=(div1_volt/a_volt)-1;
    float unknown_r=(temp*r1);
    if(unknown_r<=90){
    display_value(unknown_r-27,"ohm");
    }
    else if(unknown_r<1000 && unknown_r>90){
    display_value(unknown_r-25,"ohm");
    }
    else{
      display_value((unknown_r-25)/1000,"Kohm");
      }
    
    pinMode(r_sacal1,INPUT);
   
    if(digitalRead(back_but)==0){
      menu_back();
      }
    
  }
    
  else if(unknown_rr<226 && unknown_rr>20){      
    digitalWrite(res_power,HIGH);
    tem=0;
    pinMode(r_sacal2,OUTPUT);
    digitalWrite(r_sacal2,LOW);
    delay(dt);
    for(int i=0;i<50;i++){
      tem +=analogRead(r_check);
      delay(5);
      }
    float adc =tem/50;
    float a_volt=(adc*sys_volt)/1023;
    if(debug==true){
      Serial.print("vout = ");
      Serial.println(a_volt);
      }
    float temp=(div2_volt/a_volt)-1;
    float unknown_r=(temp*r2);
    display_value(unknown_r,"kohm");
    
    pinMode(r_sacal2,INPUT);
  
    if(digitalRead(back_but)==0){
      menu_back();
      }
    
  }
    
  else if(unknown_rr>226){    
    digitalWrite(res_power,HIGH);
    tem=0;
    pinMode(r_sacal3,OUTPUT);
    digitalWrite(r_sacal3,LOW);
    delay(dt);
    
    for(int i=0;i<50;i++){
      tem +=analogRead(r_check);
      delay(5);
      }
    float adc =tem/50;
    float a_volt=(adc*sys_volt)/1023;
    if(debug==true){
      Serial.print("vout = ");
      Serial.println(a_volt);
      }
    float temp=(div3_volt/a_volt)-1;
    float unknown_r=(temp*r3);
    display_value(unknown_r,"kohm");
    
    pinMode(r_sacal3,INPUT);


  
    if(digitalRead(back_but)==0){
      menu_back();
      }
    
  }

while(digitalRead(ok_but)==1){
  if(digitalRead(back_but)==0){
      menu_back();
      break;
  }
  if(digitalRead(back_but)==0){
      menu_back();
    }

  }}
    
  else if(count==10){
   //led
   digitalWrite(res_power,HIGH);
    tem=0;
    pinMode(r_sacal0,OUTPUT);
    digitalWrite(r_sacal0,LOW);
    delay(dt);
    for(int i=0;i<50;i++){
      tem +=analogRead(r_check);
      delay(5);
      }
    float adc =tem/50;
    float a_volt=(adc*sys_volt)/1023;
    if((sys_volt*1000)-(a_volt*1000)<4900){
   display_value((sys_volt-a_volt),"V");
    }
   pinMode(r_sacal0,INPUT);

while(digitalRead(ok_but)==1){
  if(digitalRead(back_but)==0){
      menu_back();
      break;
  }
  }
  
   if(digitalRead(back_but)==0){
      menu_back();
      }
    
}


else if(count==11){
  battery_check();
  while(digitalRead(ok_but)==1){
  if(digitalRead(back_but)==0){
      menu_back();
      break;
  }
  }
  
   if(digitalRead(back_but)==0){
      menu_back();
      }
  }

else if(count==12){
  float tem_1=supply_voltage();
  display_value(tem_1,"V");
  
  while(digitalRead(ok_but)==1){
  if(digitalRead(back_but)==0){
      menu_back();
      break;
  }
  }
  
   if(digitalRead(back_but)==0){
      menu_back();
      }
  }
 else if(count==13){
  display_value(cap_ADC,"Cadc");
  boolean tem=0;
  while(true){
  if(digitalRead(up_but)==0){
    while(digitalRead(up_but)==0){}
    tem=true;
    display_value(tem,"Cadc");
    }
  else if(digitalRead(down_but)==0){
    while(digitalRead(up_but)==0){}
    tem=false;
    display_value(tem,"Cadc");
    }
  else if(digitalRead(ok_but)==0){
    while(digitalRead(up_but)==0){}
    display_value(tem,"set");
    cap_ADC=tem;
    break;
    }
  if(digitalRead(back_but)==0){
      menu_back();
      break;
      }
  }
 display_value(cap*1.E6,"indC");
 float temm=cap*1.E6;
 while(true){
    if(digitalRead(up_but)==0){
    while(digitalRead(up_but)==0){}
    temm +=0.01;
    display_value(temm,"icuF");
    }
  else if(digitalRead(down_but)==0){
    while(digitalRead(down_but)==0){}
    temm -=0.01;
    display_value(temm,"icuf");
    }
  else if(digitalRead(ok_but)==0){
    while(digitalRead(up_but)==0){}
    display_value(temm,"set");
    cap =temm*1.E-6;
    }

  if(digitalRead(back_but)==0){
      menu_back();
      break;
      }
  }
 }
 else if(count==14){
  
  }
}


void display_menu(){
  pinMode(r_sacal0,INPUT);
  pinMode(r_sacal1,INPUT);
  pinMode(r_sacal2,INPUT);
  pinMode(r_sacal00,INPUT);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(">>Select  mode<<");
  if(count==0){
    lcd.setCursor(0,1);
    lcd.print("<PWM generator>");
    }
  else if(count==1){
    lcd.setCursor(0,1);
    lcd.print("< Res 2.2k >");
    }
 else if(count==2){
    lcd.setCursor(0,1);
    lcd.print("< Res 20k >");
    }

  else if(count==3){
    lcd.setCursor(0,1);
    lcd.print("< Res 235k >");
  }
  else if(count==4){
    lcd.setCursor(0,1);
    lcd.print("< Res 470k >");
    }
  else if(count==5){
    lcd.setCursor(0,1);
    lcd.print("< Inductor >");
    }
  else if(count==6){
    lcd.setCursor(0,1);
    lcd.print("<Capacitor mid>");
    }
  else if(count==7){
    lcd.setCursor(0,1);
    lcd.print("<Capacitor larg>");
    }
  else if(count==8){
    lcd.setCursor(0,1);
    lcd.print("< Capacitor PF>");
    }
  else if(count==9){
    lcd.setCursor(0,1);
    lcd.print("< Resistor auto>");
    }
  else if(count==10){
    lcd.setCursor(0,1);
    lcd.print("< LED forward V >");
    }
  else if(count==11){
    lcd.setCursor(0,1);
    lcd.print("<Battery status>");
    }
 else if(count==12){
    lcd.setCursor(0,1);
    lcd.print("<Supply Voltage>");
    } 
 else if(count==13){
    lcd.setCursor(0,1);
    lcd.print("< Setting >");
    } 
  }

void display_mode(){
  if(count<5 && count>0){
    //resistor test mode
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Resistor test");
    }
  else if(count==0){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("PWM generator");
    }
  else if(count==5){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Inductor test");
    }
  else if(count<=7){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Capacitor test");
    }
  else if(count==8){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Disk cap test");
    }
  else if(count==9){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Resistor auto");
    }
  else if(count==10){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("LED forward volt");
    }
  else if(count==11){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Battery status");
    }
  else if(count==12){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Supply Voltage");
    }
  else if(count==13){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Setting");
    }
  }

void menu_control(){
  bool w=true;
  while(w){
    if(digitalRead(up_but)==0){
      while(digitalRead(up_but)==0){}
      if(count>13){
        count=0;
        }
      else{
        count++;
        }
        display_menu();
      }
    else if(digitalRead(down_but)==0){
      while(digitalRead(down_but)==0){}
      if(count<0){
        count=13;
        }
      else{
        count--;
        }
        display_menu();
      }
    else if(digitalRead(ok_but)==0){
      while(digitalRead(ok_but)==0){}
      display_mode();
      w=false;
      break;
      }
    }
  }


  void display_value(float val,String r){
    lcd.setCursor(0,1);
    lcd.print("                ");
    lcd.setCursor(0,1);
    lcd.print(val);
    lcd.setCursor(12,1);
    lcd.print(r);
    }
 
 

 void menu_back(){
  display_menu();
  delay(20);
  menu_control();
  display_mode();
  } 

void battery_check(){
  float temm=sys_volt*analogRead(bt_pin)/1023;
  float temmm;
  if(temm>3.6 && temm<4.2){
    temmm=(100/4.2)*temm;
    display_value(temmm,"%");
    }
  else{
    display_value(temm,"volt");
    }
  }

float supply_voltage(){
  tem=0;
  pinMode(r_sacal0,OUTPUT);
  pinMode(r_sacal1,OUTPUT);
  digitalWrite(r_sacal0,LOW);
  digitalWrite(r_sacal1,HIGH);
  delay(200);
  analogReference(INTERNAL);
  for(int i=0;i<100;i++){
    tem +=analogRead(r_check);
    }
  analogReference(DEFAULT);
  pinMode(r_sacal0,INPUT);
  pinMode(r_sacal1,INPUT);
  
  float tem_0= tem/100;
  float vout=(1.050*tem_0)/1023;
  float buf=(2200+226)/226;
  float vin=buf*vout;

  if(debug==true){
    Serial.print("Analog value : ");
    Serial.println(tem_0);
    Serial.print("V_out : ");
    Serial.println(vout);
    Serial.print("V_in : ");
    Serial.println(vin);
    }
  return vin;
  }
