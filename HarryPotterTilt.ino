#include <Servo.h>Servo myServo;int angle = map(100, 00, 1023, 0, 179);const int switchPin = 9;const int motorPin = 10;unsigned long previousTime = 0;int switchState = 0;int prevSwitchState = 0;int led = 4;long interval = 2000;int buzzer_pin = 8;struct MusicStruct {  int A = 550;  int As = 582;  int B = 617;  int C = 654;  int Cs = 693;  int D = 734;  int Ds = 777;  int E = 824;  int F = 873;  int Fs = 925;  int G = 980;  int Gs = 1003;  int A2 = 1100;  int A2s = 1165;  int B2 = 1234;  int C3 = 1308;  int C3s = 1385;  int D3 = 1555;}Music;struct LengthStruct {  float half = 0.5;  float one = 1.0;  float one_half = 1.5;  float two = 2.0;  float two_half = 2.5;}Length;int tempo = 400;void setup() {  myServo.attach(motorPin);  for(int x = 4; x < 9; x++){    pinMode(x, OUTPUT);  }  pinMode(switchPin, INPUT);  Serial.begin(9600);}void setTone(int pin, int note, int duration) {  tone(pin, note, duration);  delay(duration);  noTone(pin);}void loop() {  unsigned long currentTime = millis();  int pitch = 1000;  switchState = digitalRead(switchPin);  angle = map(100, 00, 1023, 0, 179);    if(currentTime - previousTime > interval && switchState > 0) {    previousTime = currentTime;      setTone(buzzer_pin, Music.B, tempo * Length.one);    digitalWrite(4, HIGH);    digitalWrite(5, LOW);    digitalWrite(6, LOW);    digitalWrite(7, LOW);    setTone(buzzer_pin, Music.E, tempo * Length.one_half);    digitalWrite(4, LOW);    digitalWrite(5, HIGH);    digitalWrite(6, LOW);    digitalWrite(7, LOW);    setTone(buzzer_pin, Music.G, tempo * Length.half);    digitalWrite(4, LOW);    digitalWrite(5, LOW);    digitalWrite(6, HIGH);    digitalWrite(7, LOW);    setTone(buzzer_pin, Music.F, tempo * Length.one);    digitalWrite(4, HIGH);    digitalWrite(5, LOW);    digitalWrite(6, LOW);    digitalWrite(7, LOW);    setTone(buzzer_pin, Music.E, tempo * Length.two);    digitalWrite(4, LOW);    digitalWrite(5, LOW);    digitalWrite(6, LOW);    digitalWrite(7, HIGH);    setTone(buzzer_pin, Music.B2, tempo * Length.one);    digitalWrite(4, HIGH);    digitalWrite(5, LOW);    digitalWrite(6, LOW);    digitalWrite(7, LOW);    setTone(buzzer_pin, Music.A2, tempo * Length.two_half);    digitalWrite(4, HIGH);    digitalWrite(5, LOW);    digitalWrite(6, HIGH);    digitalWrite(7, LOW);    setTone(buzzer_pin, Music.Fs, tempo * Length.two_half);    digitalWrite(4, LOW);    digitalWrite(5, HIGH);    digitalWrite(6, LOW);    digitalWrite(7, HIGH);    setTone(buzzer_pin, Music.E, tempo * Length.one_half);    digitalWrite(4, LOW);    digitalWrite(5, HIGH);    digitalWrite(6, LOW);    digitalWrite(7, LOW);    setTone(buzzer_pin, Music.G, tempo * Length.half);    digitalWrite(4, LOW);    digitalWrite(5, LOW);    digitalWrite(6, HIGH);    digitalWrite(7, LOW);    setTone(buzzer_pin, Music.F, tempo * Length.one);    digitalWrite(4, HIGH);    digitalWrite(5, LOW);    digitalWrite(6, LOW);    digitalWrite(7, LOW);    setTone(buzzer_pin, Music.Ds, tempo * Length.two);    digitalWrite(4, LOW);    digitalWrite(5, LOW);    digitalWrite(6, LOW);    digitalWrite(7, HIGH);    setTone(buzzer_pin, Music.F, tempo * Length.one);    digitalWrite(4, HIGH);    digitalWrite(5, LOW);    digitalWrite(6, LOW);    digitalWrite(7, LOW);    setTone(buzzer_pin, Music.B, tempo * Length.two_half);    digitalWrite(4, HIGH);    digitalWrite(5, LOW);    digitalWrite(6, HIGH);    digitalWrite(7, LOW);      digitalWrite(4, HIGH);    digitalWrite(5, HIGH);    digitalWrite(6, HIGH);    digitalWrite(7, HIGH);        myServo.write(angle);    angle = map(400, 0, 179, 0, 1079);    myServo.write(angle);  } else {      for(int x = 4; x < 9; x++){        digitalWrite(x, LOW);      }  }}