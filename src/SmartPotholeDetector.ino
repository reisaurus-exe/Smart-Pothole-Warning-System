#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <MPU6050.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
MPU6050 mpu;

// LEFT sensor
#define trigL 2
#define echoL 3

// RIGHT sensor
#define trigR 11
#define echoR 12

// OUTPUTS
#define buzzer 7
#define LED1 4
#define LED2 5
#define LED3 6

// MPU values
int16_t ax, ay, az;
int16_t gx, gy, gz;

// previous distances
long prevDistL = 0;
long prevDistR = 0;

// Circle icon
byte bigCircle[8] = {
  B01110,B11111,B11111,B11111,
  B11111,B11111,B01110,B00000
};

// =============================
// DISTANCE FUNCTION
// =============================
long readDistance(int trig, int echo) {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);

  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  long duration = pulseIn(echo, HIGH, 30000);
  long distance = duration * 0.034 / 2;

  if (distance <= 0 || distance > 400) return 999;
  return distance;
}

// =============================
// SHOCK DETECTION
// =============================
bool detectShock() {
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  long totalAccel = abs(ax) + abs(ay) + abs(az);

  return (totalAccel > 20000);
}

// =============================
// POTHOLE DETECTION
// =============================
bool detectPothole(long current, long &prev) {
  long diff = prev - current;
  prev = current;

  return (diff > 15);
}

// =============================
// DISPLAY CIRCLES
// =============================
int showCircles(int centerPos, long distance, bool isLeft) {
  int count = 0;

  if (distance <= 15) count = 3;
  else if (distance <= 30) count = 2;
  else if (distance <= 50) count = 1;

  // clear area
  if (isLeft) {
    lcd.setCursor(0, 1);
    lcd.print("       ");
  } else {
    lcd.setCursor(8, 1);
    lcd.print("        ");
  }

  for (int i = 0; i < count; i++) {
    int pos;

    if (isLeft) {
      pos = centerPos - (i + 1) * 2 + 1;
    } else {
      pos = centerPos + (i * 2);
    }

    lcd.setCursor(pos, 1);
    lcd.write(byte(0));
  }

  return (count > 0);
}

// =============================
// SETUP
// =============================
void setup() {

  pinMode(trigL, OUTPUT);
  pinMode(echoL, INPUT);
  pinMode(trigR, OUTPUT);
  pinMode(echoR, INPUT);

  pinMode(buzzer, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);

  Serial.begin(9600);
  Wire.begin();

  lcd.init();
  lcd.backlight();
  lcd.createChar(0, bigCircle);

  lcd.print("POTHOLE ALERT");
  delay(1500);
  lcd.clear();

  mpu.initialize();

  if (!mpu.testConnection()) {
    lcd.print("MPU FAIL");
    while (1);
  }
}

// =============================
// LOOP
// =============================
void loop() {

  long distL = readDistance(trigL, echoL);
  long distR = readDistance(trigR, echoR);

  bool potholeL = detectPothole(distL, prevDistL);
  bool potholeR = detectPothole(distR, prevDistR);
  bool shock = detectShock();

  lcd.setCursor(0, 0);
  lcd.print("Pothole Detect ");

  lcd.setCursor(7, 1);
  lcd.print("|");

  int alertL = showCircles(7, distL, true);
  int alertR = showCircles(8, distR, false);

  long nearest = min(distL, distR);

  ////////////////////////////////
  // LED + BUZZER LOGIC
  ////////////////////////////////

  if (potholeL || potholeR) {
    //  POTHOLE MODE

    digitalWrite(LED2, HIGH);  // center LED ON

    // blink left & right LEDs
    digitalWrite(LED1, HIGH);
    digitalWrite(LED3, HIGH);
    delay(100);
    digitalWrite(LED1, LOW);
    digitalWrite(LED3, LOW);
    delay(100);

    // buzzer ON
    tone(buzzer, 1200);
  }
  else {
    // NORMAL MODE

    digitalWrite(LED2, LOW);
    noTone(buzzer);

    // left LED (no buzzer)
    digitalWrite(LED1, alertL ? HIGH : LOW);

    // right LED (no buzzer)
    digitalWrite(LED3, alertR ? HIGH : LOW);
  }

  ////////////////////////////////
  // SHOCK BOOST
  ////////////////////////////////
  if (shock) {
    tone(buzzer, 1500); // stronger alert
  }

  ////////////////////////////////
  // DEBUG
  ////////////////////////////////
  Serial.print("L: "); Serial.print(distL);
  Serial.print(" R: "); Serial.print(distR);
  Serial.print(" Pothole: ");
  Serial.print(potholeL || potholeR);
  Serial.print(" Shock: "); Serial.println(shock);

  delay(20);
}
