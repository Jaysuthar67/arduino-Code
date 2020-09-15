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

  while (distance < 150 && distance > 100) {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    duration = pulseIn(echoPin, HIGH);

    distance = duration * 0.034 / 2;
    tone(11, 800, 100);
    delay(300);
  }

  while (distance < 100 && distance > 30) {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    duration = pulseIn(echoPin, HIGH);

    distance = duration * 0.034 / 2;
    tone(11, 800, 100);
    delay(150);
  }

  while (distance < 30) {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    duration = pulseIn(echoPin, HIGH);

    distance = duration * 0.034 / 2;
    tone(11, 800, 80);
    delay(110);
  }

  while (distance > 150) {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    duration = pulseIn(echoPin, HIGH);

    distance = duration * 0.034 / 2;
    tone(11, 800, 10);
    delay(500);
  }
}
