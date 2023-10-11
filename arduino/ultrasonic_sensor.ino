#define ECHO_PIN A0
#define TRIGGER_PIN 9

#define SECOND 1000
#define SOUND_SPEED 0.0343

void setup() {
    //! Coincidir con la velocidad de la RaspberryPi
    Serial.begin(115200);
    pinMode(TRIGGER_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
}

void loop() {
    generate_ultrasonic_pulse();
    long distance = measure_distance();
    Serial.println(distance);
    //Serial.write(distance);
    delay(SECOND);
}

void generate_ultrasonic_pulse(){
    digitalWrite(TRIGGER_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIGGER_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIGGER_PIN, LOW);
}

long measure_distance(){
  long duration, distance;
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = (duration * SOUND_SPEED) / 2;
  return distance;
}