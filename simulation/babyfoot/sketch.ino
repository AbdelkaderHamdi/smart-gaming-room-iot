// Smart Gaming Room - Step 4: detect a coin and count games
// ESP32 + Coin Acceptor chip (SIGNAL -> GPIO 4)

#define COIN_PIN 4
const unsigned long DEBOUNCE_MS = 300;
const float PRICE_PER_GAME = 1.0;  // TND per game

volatile bool coinFlag = false;
unsigned long lastCoin = 0;
int games = 0;

void IRAM_ATTR onCoin() {
  coinFlag = true;
}

void setup() {
  Serial.begin(115200);
  pinMode(COIN_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(COIN_PIN), onCoin, FALLING);
  Serial.println("Baby-foot 01 ready. Insert a coin...");
}

void loop() {
  if (coinFlag) {
    coinFlag = false;
    if (millis() - lastCoin > DEBOUNCE_MS) {
      lastCoin = millis();
      games++;
      Serial.printf("Coin detected -> game #%d | revenue: %.2f TND\n",
                    games, games * PRICE_PER_GAME);
    }
  }
}
