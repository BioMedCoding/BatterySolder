/*
const int pwmPin = 9;
const int potPin = A1;
const float voltage = 12.0;  // Tensione di alimentazione in Volt
const float resistance = 6.0;  // Resistenza della sonda riscaldante in Ohm (da misurare una volta)
const float massimoDC = 80;

void setup() {
  Serial.begin(9600);
  pinMode(pwmPin, OUTPUT);
  analogWrite(pwmPin, 0);  // Inizialmente PWM a 0
}

void loop() {
  int potValue = analogRead(potPin);  // Legge il valore del potenziometro
  //Serial.println(massimoDC);
  int pwmValue = map(potValue, 0, 1023, 0, (massimoDC/100)*255);  // Mappa il valore del potenziometro al range del PWM (0-80% di 255)
  analogWrite(pwmPin, pwmValue);  // Imposta il valore PWM

  float dutyCycle = pwmValue / 255.0;

  // Calcola la potenza media
  float power = voltage * voltage * dutyCycle / resistance;

  // Stampa i valori sulla porta seriale
  Serial.print("Potentiometer Value: ");
  Serial.print(potValue);
  Serial.print(" | Pwm value: ");
  Serial.print(pwmValue);
  Serial.print(" | Duty Cycle: ");
  Serial.print(dutyCycle * 100, 1);
  Serial.print("% | Power: ");
  Serial.print(power, 2);
  Serial.println(" W");

delay(100);  // Aggiornamento ogni 100 ms
}
*/

/* // Versione con LCD e calcolo tempo di ON
#include <LiquidCrystal.h>

const int pwmPin = 9;
const float voltage = 12.0;  // Tensione di alimentazione in Volt
const float resistance = 6.0;  // Resistenza della sonda riscaldante in Ohm (da misurare una volta)
const float massimoDC = 80;

// Pin assegnati all'LCD
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  Serial.begin(9600);
  lcd.begin(20, 4);  // Inizializza l'LCD con 20 colonne e 4 righe
  
  pinMode(pwmPin, OUTPUT);
  analogWrite(pwmPin, 0);  // Inizialmente PWM a 0
}

void loop() {
  unsigned long timeOn = millis();  // Tempo trascorso dall'accensione del sistema in millisecondi
  int pwmValue = map(timeOn % 1024, 0, 1023, 0, (massimoDC / 100) * 255);  // Mappa il tempo al range del PWM (0-80% di 255)
  analogWrite(pwmPin, pwmValue);  // Imposta il valore PWM

  float dutyCycle = pwmValue / 255.0;

  // Calcola la potenza media
  float power = voltage * voltage * dutyCycle / resistance;

  // Stampa i valori sulla porta seriale
  Serial.print("Time On: ");
  Serial.print(timeOn / 1000.0);  // Converti il tempo in secondi
  Serial.print(" s | Pwm value: ");
  Serial.print(pwmValue);
  Serial.print(" | Duty Cycle: ");
  Serial.print(dutyCycle * 100, 1);
  Serial.print("% | Power: ");
  Serial.print(power, 2);
  Serial.println(" W");

  // Visualizza i valori sull'LCD
  lcd.setCursor(0, 0);
  lcd.print("Time On: ");
  lcd.print(timeOn / 1000.0);
  lcd.print(" s");

  lcd.setCursor(0, 1);
  lcd.print("Pwm Value: ");
  lcd.print(pwmValue);

  lcd.setCursor(0, 2);
  lcd.print("Duty Cycle: ");
  lcd.print(dutyCycle * 100, 1);
  lcd.print("%");

  lcd.setCursor(0, 3);
  lcd.print("Power: ");
  lcd.print(power, 2);
  lcd.print(" W");

  delay(500);  // Aggiornamento ogni 100 ms
}
*/

// Versione con calcolo tempo di on e stampa eventuale minuti, ore
#include <LiquidCrystal.h>

const int pwmPin = 9;
const int potPin = A1;
const float voltage = 12.0;  // Tensione di alimentazione in Volt
const float resistance = 3.673;  // Resistenza della sonda riscaldante in Ohm (in un altra sonda, 3.465)
const float massimoDC = 90;

// Pin assegnati all'LCD
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  Serial.begin(9600);
  lcd.begin(20, 4);  // Inizializza l'LCD con 20 colonne e 4 righe
  
  pinMode(pwmPin, OUTPUT);
  analogWrite(pwmPin, 0);  // Inizialmente PWM a 0
}

void loop() {
  unsigned long timeOn = millis() / 1000;  // Tempo trascorso dall'accensione del sistema in secondi

  // Calcola ore, minuti e secondi
  unsigned long hours = timeOn / 3600;
  unsigned long minutes = (timeOn % 3600) / 60;
  unsigned long seconds = timeOn % 60;

  

  int potValue = analogRead(potPin);  // Legge il valore del potenziometro
  int pwmValue = map(potValue, 0, 1023, 0, (massimoDC / 100) * 255);  // Mappa il valore del potenziometro al range del PWM (0-80% di 255)
  analogWrite(pwmPin, pwmValue);  // Imposta il valore PWM

  float dutyCycle = pwmValue / 255.0;

  // Calcola la potenza media
  float power = voltage * voltage * dutyCycle / resistance;

  // Stampa i valori sulla porta seriale
  Serial.print("Time On: ");
  if (timeOn < 3600) {
    Serial.print(minutes);
    Serial.print(" m ");
    Serial.print(seconds);
    Serial.print(" s");
  } else {
    Serial.print(hours);
    Serial.print(" h ");
    Serial.print(minutes);
    Serial.print(" m ");
    Serial.print(seconds);
    Serial.print(" s");
  }
  Serial.print(" | Pwm value: ");
  Serial.print(pwmValue);
  Serial.print(" | Duty Cycle: ");
  Serial.print(dutyCycle * 100, 1);
  Serial.print("% | Power: ");
  Serial.print(power, 2);
  Serial.println(" W");

  // Visualizza i valori sull'LCD
  lcd.setCursor(0, 0);
  lcd.print("Time On: ");
  if (timeOn < 3600) {
    lcd.print(minutes);
    lcd.print("m ");
    lcd.print(seconds);
    lcd.print("s");
  } else {
    lcd.print(hours);
    lcd.print("h ");
    lcd.print(minutes);
    lcd.print("m ");
    lcd.print(seconds);
    lcd.print("s");
  }

  lcd.setCursor(0, 1);
  lcd.print("Pwm Value: ");
  lcd.print(pwmValue);

  lcd.setCursor(0, 2);
  lcd.print("Duty Cycle: ");
  lcd.print(dutyCycle * 100, 1);
  lcd.print("%");

  lcd.setCursor(0, 3);
  lcd.print("Power: ");
  lcd.print(power, 2);
  lcd.print(" W");

  delay(500);  // Aggiornamento ogni 100 ms
}
