int led1 = 2;
int led2 = 16;
int val = 716;
int val2 = 1023;
int fadeamount = 25;
int fadeamount2 = 25;
void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
}


void loop() {
  analogWrite(led1, val);
  analogWrite(led2, val2);
  val = val - fadeamount;
  val2 = val2 - fadeamount2;

  if (val <= 0 || val >= 1023) {
    fadeamount = -fadeamount;
  }

  if (val2 <= 0 || val2 >= 1023) {
    fadeamount2 = -fadeamount2;
  }
  delay(30);
}
