# Console / PS (planned)

A session has a fixed length set in config (e.g. 10 minutes).

1. Staff presses Start (button in the simulation).
2. ESP32 starts a timer and publishes `salle/ps01/session start`.
3. When time is over, it publishes `end` and the duration.
