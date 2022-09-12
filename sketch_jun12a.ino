#include <Wire.h> 
#include <LCD_1602_RUS.h>
#include <OneButton.h>
LCD_1602_RUS lcd(0x27,16,2);  // Устанавливаем дисплей
uint32_t myTimer1;
int val = 0;
int val_one = 0;
int tim = 5;
const int PIN_BUTTON = 2;
const int PIN_TWO_BUTTON = 3;
OneButton button1 = OneButton(PIN_BUTTON,true,true);//Подтягивающий внутренний резистор +
OneButton button2 = OneButton(PIN_TWO_BUTTON,true,true);
void(* resetFunc) (void) = 0;//Программный сброс

void setup()
{ Serial.begin(9600);
  pinMode(PIN_BUTTON, INPUT_PULLUP);// Подключение внутреннего подтягивающего резистора
  pinMode(PIN_TWO_BUTTON, INPUT_PULLUP);
  lcd.init(); //Инициализация дисплея                    
  lcd.backlight();// Включаем подсветку дисплея
  button1.attachClick(myClickFunction1);//Инициализация функции для одиночного нажатия
  button1.setDebounceTicks(40);//Настройки для антидребезга
  button1.setClickTicks(800);
  button1.setPressTicks(1000);  
  button2.attachClick(myClickFunction2);
  button2.setDebounceTicks(40);
  button2.setClickTicks(800);
  button2.setPressTicks(1000);  
}
  void myClickFunction1()
  { val++; 
    }
  void myClickFunction2()
  { val_one++;
    }
  void game ()//Собственная функция
  { lcd.setCursor(1, 0);
    lcd.print("Игра началась!");
    lcd.setCursor(8, 1);
    lcd.print(tim);
    if (millis() - myTimer1 >= 1000) {   
    myTimer1 = millis();            
    tim = tim-1;}
    if(tim == -1){
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("Кто-то неуспел!");
    delay(1000);
    lcd.clear();
    tim = 5;
    }
    }  
void loop()
 {  
  game();
  
  if (tim==0) {
  button2.tick(); }
  if (val>=5)
   {
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("Маша пенёк !");
    delay(2000);
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("Конец игры !");
    delay(3000);
    val=0;
    val_one=0;
    resetFunc();
    }
  if (tim==0) {
    button1.tick();} 
  if (val_one>=5)
  { lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("Андрей пенёк !");
    delay(2000);
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("Конец игры !");
    delay(3000); 
    val_one=0; 
    val=0;
    resetFunc();
    }
 }
