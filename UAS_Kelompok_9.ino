// FIXX UAS

#include <LiquidCrystal_I2C.h>
#define USE_ARDUINO_INTERRUPTS true
#include <PulseSensorPlayground.h>

#define pin_trig 9
#define pin_echo 10
float jarak = 200;
float tinggi;

LiquidCrystal_I2C lcd(0x27, 20, 4);

volatile float units;

const int PulseWire = 0;
int Threshold = 550;

PulseSensorPlayground pulseSensor;

void setup() {
  pinMode(pin_echo, INPUT);
  pinMode(pin_trig, OUTPUT);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(4, 0);
  lcd.print("Alat Pengukur");
  lcd.setCursor(0, 1);
  lcd.print("Denyut Jantung, Suhu");
  lcd.setCursor(2, 2);
  lcd.print("dan Tinggi Badan");
  lcd.setCursor(3, 3);
  lcd.print("~ Kelompok 9 ~");
  delay(5000);
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.println("1.Dimas Prasetyo");
  lcd.setCursor(16, 0);
  lcd.print("   ");
  lcd.setCursor(0, 1);
  lcd.println("2.Rizki Pangestu");
  lcd.setCursor(16, 1);
  lcd.print("  ");
  lcd.setCursor(0, 2);
  lcd.println("3.Saphira Azzahra");
  lcd.setCursor(17, 2);
  lcd.print("   ");
  lcd.setCursor(0, 3);
  lcd.println("4.Syifa Amelia");
  lcd.setCursor(14, 3);
  lcd.print("     ");
  delay(5000);
  lcd.clear();

  Serial.begin(9600);

  pulseSensor.analogInput(PulseWire);
  pulseSensor.setThreshold(Threshold);

  if (pulseSensor.begin()) {
  Serial.println(" ");
  }
}

void loop() {
  lcd.setCursor(4, 0);
  lcd.println("Kelompok 9");
  lcd.setCursor(14, 0);
  lcd.print("          ");

  // Suhu
  const float BETA = 3950;
  int suhu = analogRead(A1);
  float celsius = 1 / (log(1 / (1023. / suhu - 1)) / BETA + 1.0 / 298.15) - 273.15;
  lcd.setCursor(0, 2);
  lcd.print("Suhu   : ");
  lcd.setCursor(9, 2);
  lcd.print(celsius);
  lcd.setCursor(18, 2);
  lcd.print ((char)223);
  lcd.print("C");

  // Tinggi
  long duration, gape;
  digitalWrite(pin_trig, LOW);
  delayMicroseconds(2);
  digitalWrite(pin_trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(pin_trig, LOW);
  duration = pulseIn(pin_echo, HIGH);
  gape = (duration/2) / 29.0;
  tinggi = jarak - gape;

  lcd.setCursor(0, 3);
  lcd.print("Tinggi : ");
  lcd.setCursor(9, 3);
  lcd.print(tinggi);
  //lcd.print(distance / 58 - 1);
  lcd.setCursor(18, 3);
  lcd.print("cm");


  //Denyut Jantung
  int myBPM = pulseSensor.getBeatsPerMinute();

  if (pulseSensor.sawStartOfBeat()) {
    lcd.setCursor(0, 1);
    lcd.print("Denyut :  ");
    lcd.setCursor(9, 1);
  
    lcd.println(myBPM);
    lcd.setCursor(11, 1);
    lcd.print("             ");
    lcd.setCursor(17, 1);
    lcd.print("BPM");
  }

  delay(20);
}