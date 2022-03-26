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
int button_red = 7;
int button_blue = 6;
int button_green = 5;
int button_yellow = 4;

const int pinBuzzer = 12;

int array_bottons[255] = {0};
byte level = 1;
byte button_click = 0; // 0, 1 - red, 2 - blue, 3 - green, 4 - yellow

void setup() {

  Serial.begin(9600);
  
  pinMode(button_red, INPUT);
  pinMode(button_blue, INPUT);
  pinMode(button_green, INPUT);
  pinMode(button_yellow, INPUT);

  display_red.begin();
  display_blue.begin();
  display_green.begin();
  display_yellow.begin();

  display_red.setPixelColor(255, 0, 0);
  display_blue.setPixelColor(0, 0, 255);
  display_green.setPixelColor(0, 255, 0);
  display_yellow.setPixelColor(255, 255, 0);

}

void loop() {
  int i = level;
  while (i > 0)
  {
    ft_generate_number();
    i--;
  }


}

void  ft_generate_number()
{
  byte generate_number = random(1, 5);
  int i = 0;

  while (array_bottons[i] != 0 && i < 255 )
  {
    i++;
  }
  array_bottons[i] = generate_number;
  ft_neo_pixel_color_and_buzzer(generate_number, 1500);


}

void  ft_neo_pixel_color_and_buzzer(byte color, int time_color)
{
  switch(color){
    case 1:
      display_red.print("8");
      tone(pinBuzzer, 261);
      break;
    case 2:
      display_blue.print("8");
      tone(pinBuzzer, 277);
      break;
    case 3:
      display_green.print("8");
      tone(pinBuzzer, 294);
      break;
    case 4:
      display_yellow.print("8");
      tone(pinBuzzer, 311);
      break;
    default:
      Serial.print("Error en ft_neo_pixel_color_and_buzzer: ");
      Serial.println(color);
      break;
  }
  display_red.show();
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
