
#include <Keyboard.h>
#include <Joystick.h>

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_GAMEPAD,
  1, 0,                 
  true, true, false,     
  false, false, false,   
  false, false,         
  false, false, false);  


//Порт, подключенный к ST_CP
int latchPin = 15;
//Порт, подключенный к SH_CP
int clockPin = 14;
//Порт, подключенный к DS
int dataPin = 16;

int lights_status = 0, 
prestart_status = 0, 
parking_status = 1, 
battery_status = 0, 
engine_status = 0, 
system_status = 0, 
free_status = 0, 
flaps_status = 2, 
flaps_mode_status = 0, 
toggle_status = 2, 
toggle_mode_status = 0, 
mix_status = 2, 
mix_mode_status = 0,
pedals_mode = 0, 
carb_status = 1,
current_led_code = 0b00000000,
preparing_complete_status = 0;

int pot1,pot2;

void setup() {
  //Подключение внутренних резисторов на всех кнопках
  for (int i=17; i <= 53; i++){
    pinMode(i, INPUT_PULLUP);
  }
  pinMode(0, INPUT_PULLUP);
  pinMode(1, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(A1, INPUT);
  pinMode(A0, INPUT);

  Joystick.begin();
  Joystick.setXAxisRange(1024,0);
  Joystick.setYAxisRange(400,550);
  Keyboard.begin();

}


void leds(int code, bool complain, bool reset) {
  if (reset == true) {
    current_led_code = 0;
  }
  if (complain == true) {
    current_led_code = current_led_code+code;
  } else {
    current_led_code = current_led_code-code;
  }
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, current_led_code);  
  digitalWrite(latchPin, HIGH);

}

void loop() {
    if (digitalRead(21) == 0) {
    if (digitalRead(24) == 0) { } else { preparing_complete_status = preparing_complete_status + 1; }
    if (digitalRead(23) == 0) { } else { preparing_complete_status = preparing_complete_status + 1; }
    if (digitalRead(27) == 0) { } else { preparing_complete_status = preparing_complete_status + 1; }
    if (digitalRead(31) == 0) { } else { preparing_complete_status = preparing_complete_status + 1; }
    if (digitalRead(37) == 0) { } else { preparing_complete_status = preparing_complete_status + 1; }
    if (digitalRead(50) == 0) { } else { preparing_complete_status = preparing_complete_status + 1; }
    if (digitalRead(38) == 0) { } else { preparing_complete_status = preparing_complete_status + 1; }
    if (digitalRead(42) == 0) { } else { preparing_complete_status = preparing_complete_status + 1; }
    if (digitalRead(46) == 0) { } else { preparing_complete_status = preparing_complete_status + 1; }
    if (digitalRead(1) == 0) { } else { preparing_complete_status = preparing_complete_status + 1; }
    if (digitalRead(0) == 0) { } else { preparing_complete_status = preparing_complete_status + 1; }
    if (digitalRead(22) == 1) { } else { preparing_complete_status = preparing_complete_status + 1; }
    if (digitalRead(25) == 1) { } else { preparing_complete_status = preparing_complete_status + 1; }
    if (digitalRead(29) == 1) { } else { preparing_complete_status = preparing_complete_status + 1; }
    if (digitalRead(33) == 1) { } else { preparing_complete_status = preparing_complete_status + 1; }
    if (digitalRead(35) == 1) { } else { preparing_complete_status = preparing_complete_status + 1; }
    if (digitalRead(52) == 1) { } else { preparing_complete_status = preparing_complete_status + 1; }
    if (digitalRead(40) == 1) { } else { preparing_complete_status = preparing_complete_status + 1; }
    if (digitalRead(44) == 1) { } else { preparing_complete_status = preparing_complete_status + 1; }
    if (digitalRead(48) == 1) { } else { preparing_complete_status = preparing_complete_status + 1; }
    if (digitalRead(17) == 1) { } else { preparing_complete_status = preparing_complete_status + 1; }
    if (digitalRead(18) == 1) { } else { preparing_complete_status = preparing_complete_status + 1; }
    if (digitalRead(39) == 1) { } else { preparing_complete_status = preparing_complete_status + 1; }
    if (digitalRead(41) == 1) { } else { preparing_complete_status = preparing_complete_status + 1; }
    if (digitalRead(19) == 1) { } else { preparing_complete_status = preparing_complete_status + 1; }
    if (digitalRead(20) == 1) { } else { preparing_complete_status = preparing_complete_status + 1; }
    if (digitalRead(53) == 1) { } else { preparing_complete_status = preparing_complete_status + 1; }
    if (digitalRead(51) == 1) { } else { preparing_complete_status = preparing_complete_status + 1; }
    if (digitalRead(49) == 1) { } else { preparing_complete_status = preparing_complete_status + 1; }
    if (digitalRead(43) == 1) { } else { preparing_complete_status = preparing_complete_status + 1; }
    if (digitalRead(45) == 1) { } else { preparing_complete_status = preparing_complete_status + 1; }
    if (digitalRead(47) == 1) { } else { preparing_complete_status = preparing_complete_status + 1; }
    if (digitalRead(32) == 1) { } else { preparing_complete_status = preparing_complete_status + 1; }
    if (digitalRead(30) == 1) { } else { preparing_complete_status = preparing_complete_status + 1; }
    if (digitalRead(28) == 1) { } else { preparing_complete_status = preparing_complete_status + 1; }
    if (digitalRead(26) == 1) { } else { preparing_complete_status = preparing_complete_status + 1; }
    if (digitalRead(34) == 1) { } else { preparing_complete_status = preparing_complete_status + 1; }
    if (digitalRead(36) == 1) { } else { preparing_complete_status = preparing_complete_status + 1; }
    
    if (prestart_status == 0) { //Если нужна инициализация    
      if (preparing_complete_status == 0) { //При проверке нет ошибок
        Keyboard.write('j');
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.write('.'); //Включаем тормоз стояночный
        Keyboard.release(KEY_LEFT_CTRL); 
        Keyboard.press(KEY_LEFT_SHIFT);
        Keyboard.write('m'); //выключаем питание
        Keyboard.release(KEY_LEFT_SHIFT);   
        leds(0b00001000,false,false);
        prestart_status = 1;
      } else {
        preparing_complete_status = 0; //Если есть ошибка 
        leds(0b00001000,true,true);
      }
    }     

  if (prestart_status == 1 ) {
    Joystick.setYAxis(analogRead(A1));
    Joystick.setXAxis(analogRead(A0));
  
  //Педали
  if (digitalRead(1) == 1 and pedals_mode == 1) {
    Keyboard.write('8');
    delay(300);
  }
  if (digitalRead(0) == 1 and pedals_mode == 1) {
    Keyboard.write('9');
    delay(300);
  }
  
  //Режим педалей
  if (digitalRead(27) == 0 and pedals_mode == 0) {
    pedals_mode = 1;
  } 
  if (digitalRead(29) == 0 and pedals_mode == 1) {
    pedals_mode = 0;
  }   
  if (digitalRead(1) == 1 and pedals_mode == 0 and digitalRead(0) == 1) {
    Keyboard.write('.');
    delay(300);
  }
  
  //Питание
  if (digitalRead(25) == 0 and battery_status == 0) {
    Keyboard.press(KEY_LEFT_SHIFT);
    Keyboard.write('m');
    Keyboard.release(KEY_LEFT_SHIFT);
    battery_status = 1;

  } 
  if (digitalRead(23) == 0 and battery_status == 1) {
    Keyboard.press(KEY_LEFT_SHIFT);
    Keyboard.write('m');
    Keyboard.release(KEY_LEFT_SHIFT);
    battery_status = 0; 
  }
    
  //Навигационные огни
  if (digitalRead(35) == 0 and lights_status != 1 and battery_status == 1) {
    Keyboard.write('l'); //Выкл.
    lights_status = 1;
  }
  if (digitalRead(37) == 0 and lights_status != 0 and battery_status == 1) {
    Keyboard.write('l'); //Вкл.
    lights_status = 0;
  }


  //Стояночный тормоз
  if (digitalRead(31) == 0 and parking_status != 1) {
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.write('.'); //Выкл.
    Keyboard.release(KEY_LEFT_CTRL);
    parking_status = 1;

  } 
  if (digitalRead(33) == 0 and parking_status != 0) {
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.write('.'); //Вкл.
    Keyboard.release(KEY_LEFT_CTRL);
    parking_status = 0;
  }

   //Карбюратор
  if (digitalRead(50) == 0 and carb_status != 1) {
    Keyboard.write('k'); //Холодный.
    carb_status = 1;
  } 
  if (digitalRead(52) == 0 and carb_status != 0) {
    Keyboard.write('k'); //Теплый.
    carb_status = 0;
  }

  //Навигатор
  if (digitalRead(32) == 0) {
    Keyboard.press(KEY_LEFT_SHIFT);
    Keyboard.write('3'); 
    delay(300);
    Keyboard.release(KEY_LEFT_SHIFT); 
  }

  //Пауза
  if (digitalRead(26) == 0) {
    Keyboard.write('p'); 
    delay(300);
  }

  //Отдалить вид
  if (digitalRead(34) == 0) {
    Keyboard.write('-');
    delay(500);  
  }
    
   //Приблизить вид
  if (digitalRead(30) == 0) {
    Keyboard.write('='); 
    delay(500); 
  }
  
  //Правый элерон - триммер
  if (digitalRead(53) == 0) {
    Keyboard.press(KEY_TAB);
    Keyboard.write('3'); 
    Keyboard.release(KEY_TAB);
    delay(500); 
  }
  
  //Правый элерон - триммер
  if (digitalRead(43) == 0) {
    Keyboard.press(KEY_TAB);
    Keyboard.write('4'); 
    Keyboard.release(KEY_TAB);
    delay(500); 
  }
  
  //Высота вверх - триммер
  if (digitalRead(51) == 0) {
    Keyboard.press(KEY_TAB);
    Keyboard.write('1');
    Keyboard.release(KEY_TAB);
    delay(500); 
  }

  
  //Высота вниз - триммер
  if (digitalRead(45) == 0) {
    Keyboard.press(KEY_TAB);
    Keyboard.write('2'); 
    Keyboard.release(KEY_TAB);
    delay(500); 
  }


  //Направление влево - триммер
  if (digitalRead(49) == 0) {
    Keyboard.press(KEY_TAB);
    Keyboard.write('5');
    Keyboard.release(KEY_TAB);
    delay(500);  
  }

  
   //Направление вправо - триммер
  if (digitalRead(47) == 0) {
    Keyboard.press(KEY_TAB);
    Keyboard.write('6'); 
    Keyboard.release(KEY_TAB);
    delay(500); 
  }


  //Двигатель
  if (digitalRead(48) == 0 and engine_status != 1 and battery_status == 1) {
    Keyboard.write('o'); //Вкл.
    engine_status = 1;
  } 
  if (digitalRead(46) == 0 and engine_status != 0) {
    Keyboard.write('j'); //Выкл.
    engine_status = 0;
  }

  
  //Закрылки
  if (digitalRead(24) == 0 and flaps_mode_status == 0) {
   //Режим "Авто"
    flaps_mode_status = 1;
  } 
  if (digitalRead(22) == 0 and flaps_mode_status == 1) {
    //Режим "Ручной"
    flaps_mode_status = 0;
  }
  
  if (digitalRead(41) == 0 and flaps_mode_status == 1) {
    Keyboard.write(KEY_F7);
    delay(1000);
  }
  if (digitalRead(39) == 0 and flaps_mode_status == 0 and (flaps_status == 1 or flaps_status == 2)) {
    Keyboard.write(KEY_F5);
    flaps_status = 0;
  }  
  if (digitalRead(41) == 0 and flaps_mode_status == 0 and (flaps_status == 0 or flaps_status == 2 )) {
    Keyboard.write(KEY_F8);
    flaps_status = 1;
  }
  if (digitalRead(39) == 0 and flaps_mode_status == 1) {
    Keyboard.write(KEY_F6);
    delay(1000);   
  }


  //Дроссель
  if (digitalRead(38) == 0 and toggle_mode_status == 0) {
   //Режим "Авто"
    toggle_mode_status = 1;
  } 
  if (digitalRead(40) == 0 and toggle_mode_status == 1) {
    //Режим "Ручной"
    toggle_mode_status = 0;
  }
  
  if (digitalRead(17) == 0 and toggle_mode_status == 1) {
    Keyboard.write(KEY_F2);
    delay(300);
  }
  if (digitalRead(18) == 0 and toggle_mode_status == 0 and (toggle_status == 1 or toggle_status == 2)) {
    Keyboard.write(KEY_F4);
    toggle_status = 0;
  }  
  if (digitalRead(17) == 0 and toggle_mode_status == 0 and (toggle_status == 0 or toggle_status == 2 )) {
    Keyboard.write(KEY_F1);
    toggle_status = 1;
  }
  if (digitalRead(18) == 0 and toggle_mode_status == 1) {
    Keyboard.write(KEY_F3);
    delay(300);
  }


   //Топливо
  if (digitalRead(42) == 0 and mix_mode_status == 0) {
   //Режим "Авто"
    mix_mode_status = 1;
  } 
  if (digitalRead(44) == 0 and mix_mode_status == 1) {
    //Режим "Ручной"
    mix_mode_status = 0;
  }
  
  if (digitalRead(19) == 0 and mix_mode_status == 1) {
    Keyboard.write(KEY_F10);
    delay(300);
  }
  if (digitalRead(20) == 0 and mix_mode_status == 0 and (mix_status == 1 or mix_status == 2)) {
    Keyboard.write(KEY_F12);
    mix_status = 0;
  }  
  if (digitalRead(19) == 0 and mix_mode_status == 0 and (mix_status == 0 or mix_status == 2 )) {
    Keyboard.write(KEY_F9);
    mix_status = 1;
  }
  if (digitalRead(20) == 0 and mix_mode_status == 1) {
    Keyboard.write(KEY_F11);
    delay(300);
  }
  //Управление индикаторами
  if (battery_status == 1){
    leds(0b00000000,true,true);
    if (parking_status == 1) { leds(0b00010000,true,false); }
    if (lights_status == 1) { leds(0b01000000,true,false); }
    if (battery_status == 1 and engine_status == 0) { leds(0b00000001,true,false); } 
    if (engine_status == 0) { leds(0b00100000,true,false); }  
  } else {
    leds(0b00000000,true,true);
  }
  }
  
  } else {
    //Если панель выключена
      lights_status = 0; 
      prestart_status = 0; 
      parking_status = 1; 
      battery_status = 0; 
      engine_status = 0; 
      system_status = 0; 
      free_status = 0; 
      flaps_status = 2; 
      flaps_mode_status = 0;
      toggle_status = 2; 
      toggle_mode_status = 0;
      mix_status = 2, 
      mix_mode_status = 0;
      pedals_mode = 0;
      carb_status = 1;
      preparing_complete_status = 0;
      leds(0b00000100,true, true);
      delay(1000);
      leds(0b00000100,false, false);
      delay(1000);
  } 
}
