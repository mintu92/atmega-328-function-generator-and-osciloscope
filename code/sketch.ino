/*Arduino based 5 menue "FREQ-GENERTOR" programme
 * this code is written based on arduino uno capability and wriiten in arduino ide.
 * Developed and debuged by -MINTU NATH,APRIL 6,2020,KOLKATA,INDIA.
 * the details are provided into github...
*/

#include <TimerOne.h>
#include <LiquidCrystal.h>
const int rs = 7, en = 6, d4 = 5, d5 = 4, d6 =3 , d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int pwm_up = A2;
int pwm_down = 12;
int fw_up = 11;
int fw_down = 10;
int pin_a =9;
const int sw = 8;
float volt = 0;
//int buz = 11;


int pwm_counter = 0;
int pwm_up_state = 0;
int pwm_up_last_state = 0;
int pwm_down_state = 0;
int pwm_down_last_state = 0;

int fw_counter = 0;
int fw_up_state = 0;
int fw_up_last_state = 0;
int fw_down_state = 0;
int fw_down_last_state = 0;

int sw_state = 0;
int sw_last_state = 0;
int state = 0, Loadstate = 0;

void setup() 
{
  Serial.begin(9600);
  lcd.begin(16, 2); 
  Timer1.initialize();
  pinMode(pwm_up, INPUT);
  pinMode(pwm_down, INPUT);
  pinMode(fw_up, INPUT);
  pinMode(fw_down, INPUT);
  pinMode(sw,INPUT_PULLUP);
  pinMode(A0,INPUT);
//  pinMode(buz,OUTPUT);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("FREQ-GENERTOR");
  lcd.setCursor(0,1);
  lcd.print("wait...........");
  delay(2000);

}

void loop()
{
  lcd.clear();
  lcd.setCursor(0,0);
 if (state == 0 && digitalRead(sw) == HIGH) 
    {
    state = 1;
    Loadstate=!Loadstate;
 //   buzzer();
    }
    if (state == 1 && digitalRead(sw) == LOW) 
    {   
    state = 0;
    }
     if (Loadstate==HIGH)
    {
     freq_control();
     pwm_control();
     lcd.setCursor(0, 0);
     lcd.print("  DUTY   FREQ ");
     lcd.setCursor(3, 1);
     lcd.print(pwm_counter*10);
     lcd.print("%");
     lcd.setCursor(9, 1);
     lcd.print(fw_counter);
     lcd.print("KHz");
     Timer1.start();
     Timer1.initialize();
     Timer1.pwm( pin_a, (pwm_counter*100),(long(1000/fw_counter)));
    }
     else 
    {
    Timer1.stop();
    volt = ((analogRead(A0) * 5.00 )/1023 );
    lcd.setCursor(0, 0);
    lcd.print("  INPUT-VOLTAGE");
    lcd.setCursor(5, 1);
    lcd.print(volt*11.00);
    lcd.print(" V");
    }  
 delay(30);
}

void freq_control()
{
  fw_up_state = digitalRead(fw_up);
  fw_down_state = digitalRead(fw_down);
  if ( fw_up_state != fw_up_last_state )
  {
     if ((fw_up_state == HIGH ) &&  (fw_counter < 100 ))
     {
       fw_counter ++ ;
       
       Serial.println("freq state");
       Serial.print(fw_counter);
      // buzzer();
     }
     delay(1);
  }
     if ( fw_down_state != fw_down_last_state )
  {
     if ((fw_down_state == HIGH ) && ( 0 < fw_counter ))
     {
       fw_counter --;
       Serial.println("freq state");
       Serial.print(fw_counter);  
      // buzzer();
     }
     delay(1);
  }
  fw_up_last_state = fw_up_state;
  fw_down_last_state = fw_down_state; 
}

void pwm_control()
{
  pwm_up_state = digitalRead(pwm_up);
  pwm_down_state = digitalRead(pwm_down);
  if (pwm_up_state != pwm_up_last_state)
  {
    if((pwm_up_state == HIGH) && ( pwm_counter < 10))
    {
      pwm_counter++;
      Serial.println("pwm state");
      Serial.println(pwm_counter);
     // buzzer();
    }
   delay(1);
  }
   if (pwm_down_state != pwm_down_last_state)
  {
    if((pwm_down_state == HIGH) && (0 < pwm_counter ))
    {
      pwm_counter--;
      Serial.println("pwm state");
      Serial.println(pwm_counter);
     // buzzer();
    }
   delay(1);
  }
  pwm_up_last_state = pwm_up_state;
  pwm_down_last_state = pwm_down_state;
}

/*void buzzer()
{

  tone( buz, 750, 50);
  
}*/
