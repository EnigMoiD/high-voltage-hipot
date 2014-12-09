//Controls a Hipot tester
boolean running = HIGH;
byte outputPin = 6;
byte vmeas = A0; 
int signal = 0;

void setup() {
  //increase the pwm frequency for pin 6
  TCCR0B |= 0b00000001; //CS00 -> 1
  TCCR0B &= ~0b00000110; //CS02, CS01 -> 0, No clk prescalar
  Serial.begin(9600);
  Serial.println("Begin!");
  pinMode(outputPin, OUTPUT);
  pinMode(13, OUTPUT);
  attachInterrupt(0, shutoff, RISING); //interrupt pin 2
  digitalWrite(13, LOW);
  delay(100000);
}

void loop() {
  if (running) {
    analogWrite(outputPin, signal);
    signal+=1;
    if (signal >= 250) {
      closed();
    }
    delay(5000);
  }
}

void shutoff() {
  Serial.println("Shutting off");
  running = LOW;
  analogWrite(outputPin, 0);
  digitalWrite(13, HIGH);
}

void closed() {
  Serial.println("Reached 255, shutting off");
  running = LOW;
  analogWrite(outputPin, 0);
}



