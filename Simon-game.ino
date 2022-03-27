// > MoonMakers

// -> NeoDigito
#include <NeoDigito.h>

// Pin where the display will be attached
#define PIN_RED 8
#define PIN_BLUE 9
#define PIN_GREEN 10
#define PIN_YELLOW 11

// Number of NeoDigitos connected
#define DIGITS 1

// NeoPixel per segment
#define PIXPERSEG 2

// Once you have specified the number of displays
// and the number of neopixels per segment, some
// arguments of the neopixel strip used must be
// added. NeoDigito() also admits the number of
// delimiters and the number of pixels per delimiter.

NeoDigito display_red =  NeoDigito(DIGITS, PIXPERSEG, PIN_RED, NEO_RGB + NEO_KHZ800);
NeoDigito display_blue =  NeoDigito(DIGITS, PIXPERSEG, PIN_BLUE, NEO_RGB + NEO_KHZ800);
NeoDigito display_green =  NeoDigito(DIGITS, PIXPERSEG, PIN_GREEN, NEO_RGB + NEO_KHZ800);
NeoDigito display_yellow =  NeoDigito(DIGITS, PIXPERSEG, PIN_YELLOW, NEO_RGB + NEO_KHZ800);

// -> Buttons
int button_on = 13;
int button_red = 7;
int button_blue = 6;
int button_green = 5;
int button_yellow = 4;

const int pinBuzzer = 12;

int array_bottons[25] = {0};
byte level = 1;
byte button_click = 0; // 0, 1 - red, 2 - blue, 3 - green, 4 - yellow

void setup() {

  //Serial.begin(9600);

  pinMode(button_on, INPUT);
  pinMode(button_red, INPUT);
  pinMode(button_blue, INPUT);
  pinMode(button_green, INPUT);
  pinMode(button_yellow, INPUT);

  display_red.begin();
  display_blue.begin();
  display_green.begin();
  display_yellow.begin();
}

void loop() {
  int on = 1;
  on = digitalRead(button_on);
  if (on || level > 1)
  {
    ft_generate_number();
    delay(200);
    ft_check();
    delay(750);
  }
}
void  ft_check()
{
  int i;
  i = 0;
  while (array_bottons[i] != 0 && i < 25 )
  {
    //Serial.print("--> El boton a pretar :");
    //Serial.println(array_bottons[i]);
    if (!ft_check_number(array_bottons[i], 3000))
    {
      //Serial.println("No se apreto");
      ft_restart();
      break;
    }
    //Serial.println("Se apreto");
    i++;
  }
  level++;
}


bool  ft_check_number(int b, int limit_time)
{
  unsigned long my_time;
  unsigned long my_limit;

  my_time = millis();
  my_limit = millis() + limit_time;
  while (my_time <= my_limit)
  {
    button_click = ft_button_color(1000);
    //Serial.print("---> Valor de button_click: ");
    //Serial.println(button_click);
    if (button_click != 0 && button_click == b) return true;
    if (button_click != 0 && button_click != b) return false;
    my_time = millis();
  }
  button_click = 0;
  return false;
}

int ft_button_color(int color_time)
{
  int b_red = digitalRead(button_red);
  int b_blue = digitalRead(button_blue);
  int b_green = digitalRead(button_green);
  int b_yellow = digitalRead(button_yellow);

  if (b_red)
  {
    ft_neo_pixel_color_and_buzzer(1, color_time);
    return 1;
  }
  if (b_blue)
  {
    ft_neo_pixel_color_and_buzzer(2, color_time);
    return 2;
  }
  if (b_green)
  {
    ft_neo_pixel_color_and_buzzer(3, color_time);
    return 3;
  }
  if (b_yellow)
  {
    ft_neo_pixel_color_and_buzzer(4, color_time);
    return 4;
  }

  return 0;
}

void  ft_restart()
{
  int i = 0;
  while (array_bottons[i] > 0 && i < 25 )
  {
    array_bottons[i] = 0;
    i++;
  }
  level = 0;
  button_click = 0;
}

void  ft_generate_number()
{
  byte generate_number = random(1, 5);
  int i = 0;

  while (array_bottons[i] != 0 && i < 25 )
  {
    i++;
  }
  array_bottons[i] = generate_number;

  //Serial.print("Numero aleatorio: ");
  //Serial.println(generate_number);

  i = 0;
  while (array_bottons[i] != 0 && i < 25 )
  {
    //Serial.print("-> secuenci : ");
    //Serial.println(array_bottons[i]);
    ft_neo_pixel_color_and_buzzer(array_bottons[i], 1500);
    ft_neo_pixel_color_and_buzzer(0, 1000);
    i++;
  }
}

void  ft_neo_pixel_color_and_buzzer(byte color, int time_color)
{
  switch (color) {
    case 1:
      display_red.setPixelColor(0x008000);
      display_red.print("8");
      tone(pinBuzzer, 261);
      break;
    case 2:
      display_blue.setPixelColor(0x0000FF);
      display_blue.print("8");
      tone(pinBuzzer, 277);
      break;
    case 3:
      display_green.setPixelColor(0xFF0000);
      display_green.print("8");
      tone(pinBuzzer, 294);
      break;
    case 4:
      display_yellow.setPixelColor(0xFFFF00);
      display_yellow.print("8");
      tone(pinBuzzer, 311);
      break;
    default:
      break;
  }

  display_red.show();
  display_blue.show();
  display_green.show();
  display_yellow.show();

  delay(time_color);

  display_red.clear();
  display_red.show();

  display_blue.clear();
  display_blue.show();

  display_green.clear();
  display_green.show();

  display_yellow.clear();
  display_yellow.show();

  noTone(pinBuzzer);
}
