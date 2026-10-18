// Coin Acceptor custom chip for Wokwi
// Behaves like a real CH-926 style coin acceptor:
//   - SIGNAL idles HIGH
//   - one coin = one LOW pulse of 50 ms on SIGNAL
//   - the "INSERT" pin is driven by a pushbutton (= you dropping a coin)

#include "wokwi-api.h"
#include <stdio.h>
#include <stdlib.h>

#define PULSE_US 50000  // 50 ms pulse

typedef struct {
  pin_t insert;
  pin_t signal;
  timer_t timer;
  bool busy;
} chip_state_t;

static void on_timer(void *user_data) {
  chip_state_t *chip = (chip_state_t *)user_data;
  pin_write(chip->signal, HIGH);  // pulse over, back to idle
  chip->busy = false;
}

static void on_insert_change(void *user_data, pin_t pin, uint32_t value) {
  chip_state_t *chip = (chip_state_t *)user_data;
  if (value == LOW && !chip->busy) {  // button pressed
    chip->busy = true;
    pin_write(chip->signal, LOW);     // start pulse
    timer_start(chip->timer, PULSE_US, false);
    printf("Coin accepted\n");
  }
}

void chip_init(void) {
  chip_state_t *chip = malloc(sizeof(chip_state_t));
  chip->busy = false;

  chip->signal = pin_init("SIGNAL", OUTPUT);
  pin_write(chip->signal, HIGH);

  chip->insert = pin_init("INSERT", INPUT_PULLUP);

  const timer_config_t timer_config = {
    .callback = on_timer,
    .user_data = chip,
  };
  chip->timer = timer_init(&timer_config);

  const pin_watch_config_t watch_config = {
    .edge = FALLING,
    .pin_change = on_insert_change,
    .user_data = chip,
  };
  pin_watch(chip->insert, &watch_config);
}
