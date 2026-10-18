# Smart Gaming Room: Coin-Operated Baby-Foot Counter (ESP32 + MQTT, Simulated in Wokwi)

Count games, track revenue and see your game room in a dashboard, **without building any hardware**. Everything runs in your browser.

![System diagram: Coin acceptor -> ESP32 -> MQTT broker -> Node-RED -> Dashboard]

```
Coin Acceptor -> ESP32 -> Wi-Fi -> MQTT Broker -> Node-RED -> Database -> Dashboard
```

## Introduction

In a game room, every baby-foot, billiard table, console and PC makes money, but the owner often has no idea how much each one earns. This project fixes that.

In this tutorial (Steps 1 to 4) you build the first block: a **simulated baby-foot** where inserting a coin is detected and counted by an ESP32. In the next steps we add Wi-Fi, MQTT and a dashboard.

**What you will learn**
- How a coin acceptor talks to a microcontroller (one pulse = one coin)
- How to import a **custom component** into the Wokwi simulator
- How to detect pulses with an interrupt and count games

## Supplies

All free, no hardware needed:
- A web browser
- A free account on [wokwi.com](https://wokwi.com)
- (Later steps) a public MQTT broker such as `broker.hivemq.com`, and Node-RED

Files used in this tutorial:
- `coin-acceptor.chip.json`
- `coin-acceptor.chip.c`
- `sketch.ino`
- `diagram.json`

---

## Step 1: Create the Wokwi project

1. Go to **wokwi.com** and sign in.
2. Click **New Project**.
3. Choose **ESP32**, then the **Arduino** template.
4. You now see three main tabs: `sketch.ino`, `diagram.json` and the circuit view.

**Tip:** rename the project to "Smart Gaming Room - Babyfoot" so you find it easily.

## Step 2: Add the coin mechanism

**How a real coin acceptor works.** A coin acceptor (for example the CH-926) has 3 wires: power, ground and **signal**. When it accepts a valid coin, the signal wire gives **one short pulse**. The signal is normally HIGH and drops LOW for about 50 ms.

So for the ESP32: `1 pulse = 1 coin = 1 game`.

Wokwi has no coin acceptor, so we **create it as a custom chip**:

1. In the editor, use the **+** button next to the file tabs and choose to add a **new custom chip** (the exact menu name may change; see the *Custom Chips* page in the Wokwi docs if you cannot find it).
2. You get two files: a `.chip.json` and a `.chip.c`.
3. Name them `coin-acceptor.chip.json` and `coin-acceptor.chip.c`.
4. Replace their content with the files from this tutorial.
5. Wokwi builds the chip automatically. A part called **coin-acceptor** appears in the parts list.

What the chip does:
- Pin **INSERT**: connected to a button. Pressing it = dropping a coin.
- Pin **SIGNAL**: sends one 50 ms LOW pulse to the ESP32.
- While a pulse is running, a second coin is ignored (like a real coin lock).

Now add the button:
1. Click the blue **+** (add part) and choose **Pushbutton**.
2. Set its label to **Insert coin**.

## Step 3: Wire the circuit

Connect the parts like this:

| From | To | Wire color |
|---|---|---|
| Button pin `1.l` | Chip `INSERT` | green |
| Button pin `2.l` | ESP32 `GND` | black |
| Chip `SIGNAL` | ESP32 `GPIO 4` | orange |
| Chip `VCC` | ESP32 `3V3` | red |
| Chip `GND` | ESP32 `GND` | black |

**Shortcut:** open the `diagram.json` tab and paste the file from this tutorial. The wiring appears by itself. You can drag parts to tidy the layout.

## Step 4: Write the code and test

Open `sketch.ino` and paste the code:

```cpp
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
```

**How it works**
- `INPUT_PULLUP` keeps the pin HIGH when idle.
- The coin pulse makes the pin fall to LOW, which triggers the **interrupt** `onCoin`.
- The interrupt only raises a flag. The real work happens in `loop()`.
- The 300 ms **debounce** avoids counting one coin twice.
- Each valid coin adds 1 game and adds `PRICE_PER_GAME` to the revenue.

**Test it**
1. Click the green **Start simulation** button.
2. Wait for `Baby-foot 01 ready` in the serial monitor.
3. Click the **Insert coin** button.
4. You should see: `Coin detected -> game #1 | revenue: 1.00 TND`.
5. Click again: game #2, revenue 2.00 TND.

If nothing appears, check that the chip `SIGNAL` wire goes to **GPIO 4** and that the chip built without errors.

---

## Coming next

- **Step 5:** Connect to Wi-Fi (`Wokwi-GUEST`) and publish each coin to MQTT.
- **Step 6:** Check the messages with an MQTT client.
- **Step 7:** Build the Node-RED dashboard (games per day, revenue).
- **Step 8:** Add the PS/console timer and the PC status (simulated).
