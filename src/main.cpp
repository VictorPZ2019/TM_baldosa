#include <Arduino.h>

#define R1 100000
//#define Vsal A0 
#define B 3950
#define T0 25
#define R2nominal 100000
float R2 = 0.0;
float T;

//megamux
int S[5] = {13, 12, 11, 10, 9}; // A0, A1, A2, A3, A4

int CS = 8;
int WR = 7;
int EN = 6;
int INPIN = A0; // I0

void pinSelect(int pinnum);

void setup() {
    for (int x = 0; x < 5; x ++) {
        pinMode(S[x],OUTPUT);
        digitalWrite(S[x], LOW);
    }
    pinMode(CS, OUTPUT);
    digitalWrite(CS, LOW);
    pinMode(WR, OUTPUT);
    digitalWrite(WR, LOW);
    pinMode(EN, OUTPUT);
    digitalWrite(EN, LOW);
    pinMode(A1, OUTPUT);
    digitalWrite(A1, HIGH);
    pinMode(INPIN, INPUT);
    Serial.begin(115200);
    analogReference(EXTERNAL);
}

void loop() {
    for(int i = 0; i < 16; i++){
        char buffer[60];
        pinSelect(i);
        //R2 = ((float)analogRead(INPIN)*R1)/(1023-(float)analogRead(INPIN));
        R2 = R1*(1023-(float)analogRead(INPIN))/((float)analogRead(INPIN));
        T = 1.0/(1.0/(T0+273.15)+(1.0/(B))*log(R2/R2nominal));
        T -= 273.15;
        unsigned int analog_val = analogRead(INPIN);
        snprintf(buffer, sizeof(buffer), "Temperature {%d}: %d.%d *C", i, (int)T, abs((int)(T*10 - (int)T)));
        Serial.println(buffer);
        Serial.println(analog_val);
        delay(1000);
    }

}
void pinSelect(int pinnum){
    digitalWrite(WR, LOW);
    delay(10);
    for (int x = 0; x<5; x++){
        byte state = bitRead(pinnum, x);
        digitalWrite(S[x], state);
    }
    digitalWrite(WR, HIGH);

}