//motorul stepper, in varianta lui originala unipolar specificat ca e de 5V, modificat in varianta bipolara

//dozator hrana catei, pisici
// Pini MX1508 conectați la Arduino
#define A1_PIN 2
#define A2_PIN 3
#define B1_PIN 4
#define B2_PIN 5
#define BUZZER 6

#define STEPS_PER_REV 2048// 28BYJ-48 full-step
#define STEP_DELAY_US 3500// viteză mică, cuplu maxim

// Secvență FULL STEP corectă pentru MX1508
int stepSequence[4][4] = {
  {HIGH, LOW,  HIGH, LOW},   // pas 0
  {HIGH, LOW,  LOW,  HIGH},  // pas 1
  {LOW,  HIGH, LOW,  HIGH},  // pas 2
  {LOW,  HIGH, HIGH, LOW}    // pas 3
};

void setup() {
  ADCSRA &= ~(1 << ADEN);  // ADC off pentru reducerea consumului
  pinMode(A1_PIN, OUTPUT);
  pinMode(A2_PIN, OUTPUT);
  pinMode(B1_PIN, OUTPUT);
  pinMode(B2_PIN, OUTPUT);

  // inițial toate LOW
  allPinsLow();
}

void buzz() {
  for (int i = 0; i<2; i++){

    tone(BUZZER, 262);   // Do
    delay(150);
    noTone(BUZZER);
    delay(50);

    tone(BUZZER, 330);   // Mi
    delay(150);
    noTone(BUZZER);
    delay(50);

    tone(BUZZER, 392);   // Sol
    delay(150);
    noTone(BUZZER);
    delay(50);

    tone(BUZZER, 523);   // Do
    delay(150);
    noTone(BUZZER);
    delay(50);

    tone(BUZZER, 392);   // Sol
    delay(350);
    noTone(BUZZER);

    delay(500);

  }

}

void allPinsLow() {
  digitalWrite(A1_PIN, LOW);
  digitalWrite(A2_PIN, LOW);
  digitalWrite(B1_PIN, LOW);
  digitalWrite(B2_PIN, LOW);
}

void stepMotorForward(long steps) {
  for (long i = 0; i < steps; i++) {
    int seq = i % 4;
    digitalWrite(A1_PIN, stepSequence[seq][0]);
    digitalWrite(A2_PIN, stepSequence[seq][1]);
    digitalWrite(B1_PIN, stepSequence[seq][2]);
    digitalWrite(B2_PIN, stepSequence[seq][3]);
    delayMicroseconds(STEP_DELAY_US);
  }
  allPinsLow(); // bobinele în repaus după rotație
}

void stepMotorBackward(long steps) {
  for (long i = 0; i < steps; i++) {
    int seq = 3 - (i % 4); // inversează secvența
    digitalWrite(A1_PIN, stepSequence[seq][0]);
    digitalWrite(A2_PIN, stepSequence[seq][1]);
    digitalWrite(B1_PIN, stepSequence[seq][2]);
    digitalWrite(B2_PIN, stepSequence[seq][3]);
    delayMicroseconds(STEP_DELAY_US);
  }
  allPinsLow(); // bobinele în repaus după rotație
}

void loop() {
  // o tură înainte
  //stepMotorForward(STEPS_PER_REV);

  //delay(28800000UL); // pauză 8 ore cu bobinele în repaus UL(unsigned long)

  // o tură înapoi
  buzz();
  stepMotorBackward(STEPS_PER_REV);
  delay(28800000UL); // pauză 8 ore cu bobinele în repaus
}