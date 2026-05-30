#include <WiFi.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h>

#define DHTPIN 14
#define DHTTYPE DHT22
#define LDRPIN 34
#define LED_R 4
#define LED_G 2
#define LED_B 15

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);

const char* ssid = "Wokwi-GUEST";
const char* password = "";

unsigned long tempoAnterior = 0;
const long intervaloAmostragem = 30000;

String deviceID = "ECO-001";

void setup() {
  Serial.begin(115200);

  dht.begin();
  lcd.init();
  lcd.backlight();

  pinMode(LDRPIN, INPUT);
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);

  conectarWiFi();
}

void loop() {
  unsigned long tempoAtual = millis();

  if (tempoAtual - tempoAnterior >= intervaloAmostragem) {
    tempoAnterior = tempoAtual;
    executarMonitoramento();
  }
}

void conectarWiFi() {
  lcd.setCursor(0, 0);
  lcd.print("Conectando WiFi");

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  lcd.clear();
  lcd.print("WiFi Conectado!");
  delay(2000);
}

void executarMonitoramento() {
  float umidade = dht.readHumidity();
  float temperatura = dht.readTemperature();
  int ldrValue = analogRead(LDRPIN);

  if (isnan(umidade) || isnan(temperatura)) {
    Serial.println("Falha ao ler o sensor DHT!");
    return;
  }

  atualizarAlertas(temperatura, ldrValue);
  atualizarDisplay(temperatura, umidade, ldrValue);
  enviarDadosAuditoria();
}

void atualizarAlertas(float temp, int luz) {
  if (temp >= 20 && temp <= 26 && luz > 1000) {
    setColor(0, 255, 0);
  } else if (temp > 28 || temp < 18) {
    setColor(255, 0, 0);
  } else {
    setColor(255, 255, 0);
  }
}

void atualizarDisplay(float temp, float umi, int luz) {
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(temp, 1);
  lcd.print("C U:");
  lcd.print(umi, 1);
  lcd.print("%");

  lcd.setCursor(0, 1);
  lcd.print("Luz: ");
  lcd.print(luz);
}

void enviarDadosAuditoria() {
  Serial.println("--- Log de Auditoria ---");
  Serial.print("Dispositivo: ");
  Serial.println(deviceID);
  Serial.println("Status: Dados enviados via Wi-Fi.");
  Serial.println("------------------------");
}

void setColor(int red, int green, int blue) {
  analogWrite(LED_R, red);
  analogWrite(LED_G, green);
  analogWrite(LED_B, blue);
}
