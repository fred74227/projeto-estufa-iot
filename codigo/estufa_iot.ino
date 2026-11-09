// ============================================================
// Projeto de Circuitos Eletrônicos - IoT
// Formação IoT Specialist - DIO
//
// Simulação de uma estufa de hortaliças no TinkerCad:
// (a) leitura da temperatura via sensor TMP36;
// (b) acionamento de um motor de ventilador quando a
//     temperatura for igual ou maior a 30 °C;
// (c) acima de 50 °C, LED vermelho e buzina disparam o
//     alarme de emergência.
// ============================================================

// ---------- Pinos do Arduino ----------
const int PINO_SENSOR = A0;   // saída do TMP36 (analógica)
const int PINO_MOTOR  = 9;    // base do transistor que liga o motor
const int PINO_LED    = 12;   // LED vermelho de emergência
const int PINO_BUZINA = 8;    // buzzer (buzina) de emergência

// ---------- Limites de temperatura ----------
const float TEMP_VENTILADOR = 30.0;  // liga o ventilador a partir daqui
const float TEMP_EMERGENCIA = 50.0;  // dispara o alarme acima daqui

void setup() {
  pinMode(PINO_MOTOR, OUTPUT);
  pinMode(PINO_LED, OUTPUT);
  pinMode(PINO_BUZINA, OUTPUT);
  Serial.begin(9600);  // monitor serial para acompanhar a temperatura
}

void loop() {
  // ---- (a) Leitura da temperatura ----
  // O TMP36 gera 0,5 V a 0 °C e aumenta 10 mV por grau Celsius.
  // O Arduino lê de 0 a 1023 para tensões de 0 a 5 V.
  int leitura = analogRead(PINO_SENSOR);
  float tensao = leitura * (5.0 / 1023.0);      // converte para volts
  float temperatura = (tensao - 0.5) * 100.0;   // fórmula do TMP36

  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.println(" °C");

  // ---- (b) Motor do ventilador: temperatura >= 30 °C ----
  if (temperatura >= TEMP_VENTILADOR) {
    digitalWrite(PINO_MOTOR, HIGH);  // liga o ventilador
  } else {
    digitalWrite(PINO_MOTOR, LOW);   // desliga
  }

  // ---- (c) Emergência: temperatura > 50 °C ----
  if (temperatura > TEMP_EMERGENCIA) {
    digitalWrite(PINO_LED, HIGH);    // LED vermelho aceso
    tone(PINO_BUZINA, 1000);         // buzina tocando (1 kHz)
  } else {
    digitalWrite(PINO_LED, LOW);     // LED apagado
    noTone(PINO_BUZINA);             // buzina silenciosa
  }

  delay(500);  // nova leitura a cada meio segundo
}
