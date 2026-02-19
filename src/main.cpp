#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_LEDBackpack.h>
#include <Servo.h>
bool a = false;
Servo servo;
Adafruit_LEDBackpack matrix = Adafruit_LEDBackpack();
bool rows_and_cols[8][8];
void toggle_led(int col,int row) {rows_and_cols[col][row] = !rows_and_cols[col][row];}
int get_final_val(int col) {return 128*rows_and_cols[col][0]+1*rows_and_cols[col][1]+2*rows_and_cols[col][2]+4*rows_and_cols[col][3]+8*rows_and_cols[col][4]+16*rows_and_cols[col][5]+32*rows_and_cols[col][6]+64*rows_and_cols[col][7];}
void display() {
    for (int i = 0;i<8;i++) {matrix.displaybuffer[i] = get_final_val(i);}
    matrix.writeDisplay();
}
void setup() {
    servo.attach (11);
    matrix.begin(0x70);
    matrix.setBrightness(1);
    
    for (int i = 0;i<9;i++) {toggle_led(i,3);}toggle_led(4,1);toggle_led(4,5);toggle_led(5,1);toggle_led(5,5);toggle_led(5,2);toggle_led(5,4);toggle_led(6,2);toggle_led(6,4); // arrow
    display();
}
void loop() {
    delay(1000);
    if (a) {
        servo.write(100);
        a = !a;
    }
    else {
        servo.write(0);
        a = !a;
    }
}