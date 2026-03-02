#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_LEDBackpack.h>
#include <happen.h>
#include <limit.h>
Adafruit_LEDBackpack matrix = Adafruit_LEDBackpack();
// vars 
unsigned long cmils;
bool rows_and_cols[8][8];
// structs
struct button{unsigned long mills;int prid = 10;bool current_button_sate;bool last_button_state;int pin;button(int button_pin) {pin = button_pin;pinMode(pin,INPUT_PULLUP);}};
struct dot {int r = 7;int c = 0;button left, up, down, right;dot(int l, int u, int d, int r): left(l), up(u), down(d), right(r){}}left(11,10,9,8),right(5,4,3,2);
// function declarations
void update(dot& z);
void toggle_led(int col,int row);
bool button_test(button &z);
void display();
void read_pin(button &z);
// setup and loop
void setup() {matrix.begin(0x70);matrix.setBrightness(1);}
void loop() {cmils = millis();update(left);update(right);}
// function definitions
void update(dot& z) {if (button_test(z.left)) {z.c--;}if (button_test(z.right)) {z.c++;}if (button_test(z.up)) {z.r++;}if (button_test(z.down)) {z.r--;}limit(z.r,7);limit(z.c,7);toggle_led(z.c,z.r);display();toggle_led(z.c,z.r);read_pin(z.left);read_pin(z.right);read_pin(z.up);read_pin(z.down);    }
void toggle_led(int col,int row) {rows_and_cols[col][row] = !rows_and_cols[col][row];}
bool button_test(button& z) {if(happen(cmils,z.mills,z.prid,false) && z.last_button_state == false && z.current_button_sate == true) {z.mills = cmils;z.last_button_state = true;return true;}z.last_button_state = z.current_button_sate;return false;}
void display() {for (int col = 0; col < 8; col++) {uint8_t value = 0;for (int row = 0; row < 8; row++) {value |= (rows_and_cols[col][row] << row);}matrix.displaybuffer[col] = value;}matrix.writeDisplay();}
void read_pin(button& z) {z.current_button_sate = !digitalRead(z.pin);}