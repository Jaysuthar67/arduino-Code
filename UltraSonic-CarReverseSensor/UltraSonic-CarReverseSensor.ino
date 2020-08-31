#define echoPin 2
#define trigPin 3
#define led 13

// defines variables
long duration;
int distance;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(led, OUTPUT);
  int i;
  for (i = 0; i < 3 ; i++) {
    digitalWrite(led, HIGH);
    delay(100);
    digitalWrite(led, LOW);
  }


}
void loop() {

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  distance = duration * 0.034 / 2;

  if (distance < 150 && distance > 100) {
    AlarmLOW();
  } else if (distance < 100 && distance > 30) {

  } else if (distance < 30) {

  } else {
    tone(11, 800, 10)
    delay(100);
  }
}

void AlarmHIGH() {
  int i;
  for (i = 0; i < 25; i++) {
    tone(11, 800, 100);
    delay(150);
  }
}

void AlarmMID() {
  int i;
  for (i = 0; i < 25; i++) {
    tone(11, 800, 100);
    delay(150);
  }
}

void AlarmLOW() {
  int i;
  for (i = 0; i < 25; i++) {
    tone(11, 800, 100);
    delay(500);
  }
}
