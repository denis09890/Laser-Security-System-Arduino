// Definiții simplificate pentru o alarmă standard
#define ALARM_FREQ 1000      // Frecvența alarmei în Hz (un sunet strident)
#define BEEP_DURATION 200    // Durata sunetului în milisecunde (beep)
#define SILENCE_DURATION 100 // Durata pauzei în milisecunde (pauza dintre beep-uri)

// Pinouts
byte ldr_sensor = 2;
byte laserPin = 5;
byte buzzer = 11;
byte ledPin_VCC = A4;
byte ledPin_GND = A5;

// Variabile de stare ale alarmei (Logica non-blocantă)
unsigned long stopAlarmTime = 0;    // Timpul când alarma se oprește complet (5 secunde)
unsigned long nextBeepTime = 0;     // Timpul când trebuie să schimbăm starea beep-ului (ON/OFF)
int alarmState = 0;                 // 0=Dezactivată, 1=Activă (Laser întrerupt), 2=Activă (Timp de așteptare)
bool isBuzzing = false;             // Starea curentă a buzzer-ului (Redă ton / Pauză)

const unsigned long HOLD_TIME = 5000; // 5 secunde de așteptare după restabilirea laserului

void setup()
{
  pinMode(ldr_sensor, INPUT);
  pinMode(laserPin, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(ledPin_VCC, OUTPUT);
  pinMode(ledPin_GND, OUTPUT);

  digitalWrite(laserPin, HIGH); // Pornim laserul
  digitalWrite(ledPin_GND, LOW); // Setăm GND la LOW pentru LED (dacă e necesar)
  digitalWrite(ledPin_VCC, LOW); // LED-ul este oprit inițial
}

void loop()
{
  int sensor_data = digitalRead(ldr_sensor);
  unsigned long currentTime = millis();

  // --- 1. DETECȚIE ȘI TRANZIȚIA DE STARE ---

  if (sensor_data == HIGH && alarmState == 0) // Fascicul întrerupt, alarma era oprită
  {
    alarmState = 1;
    stopAlarmTime = currentTime + HOLD_TIME;
    digitalWrite(ledPin_VCC, HIGH); // Pornim LED-ul de avertizare
    isBuzzing = false; // Resetăm starea beep-ului pentru a începe cu un ton
    nextBeepTime = currentTime; // Forțăm buzzer-ul să pornească imediat
  }
  else if (sensor_data == HIGH && alarmState == 2) // Fascicul întrerupt în timpul perioadei de așteptare (resetează HOLD_TIME)
  {
    alarmState = 1; // Trecem înapoi la starea 1
    stopAlarmTime = currentTime + HOLD_TIME;
  }
  else if (sensor_data == LOW && alarmState == 1) // Fascicul restabilit, începem numărătoarea inversă HOLD_TIME
  {
    alarmState = 2;
  }


  // --- 2. LOGICĂ ALARMĂ (NON-BLOCANTĂ) ---

  // Dacă alarma este activă (starea 1 sau starea 2 înainte de expirarea timpului)
  if (alarmState == 1 || (alarmState == 2 && currentTime < stopAlarmTime))
  {
    // Verificăm dacă a sosit timpul pentru următorul beep/pauză
    if (currentTime >= nextBeepTime)
    {
      if (isBuzzing)
      {
        // Alarma era ON, acum o Oprim (Pauză)
        noTone(buzzer);
        nextBeepTime = currentTime + SILENCE_DURATION;
        isBuzzing = false;
      }
      else
      {
        // Alarma era OFF, acum o Pornim (Beep)
        tone(buzzer, ALARM_FREQ, BEEP_DURATION); // tone() e non-blocant
        nextBeepTime = currentTime + BEEP_DURATION;
        isBuzzing = true;
      }
    }
  }

  // --- 3. LOGICĂ DE OPRIRE AUTOMATĂ ---

  // Dacă alarma este în starea 2 (așteptare) și timpul a expirat
  if (alarmState == 2 && currentTime >= stopAlarmTime)
  {
    alarmState = 0; // Oprim alarma
  }


  // --- 4. DEZACTIVARE FINALĂ ---

  if (alarmState == 0)
  {
    noTone(buzzer); // Asigură-te că buzzer-ul tace
    digitalWrite(buzzer, LOW); // Utile dacă buzzer-ul e conectat la un pin digital standard
    digitalWrite(ledPin_VCC, LOW);
    // Nu mai folosim delay(100) aici, pentru a menține bucla fluidă.
  }
}
