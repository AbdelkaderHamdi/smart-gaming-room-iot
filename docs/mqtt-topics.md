# MQTT Topics

Pattern: `salle/<device-type><id>/<data>`

| Topic | Payload | Sent by | Meaning |
|---|---|---|---|
| `salle/babyfoot01/coin` | `1` | ESP32 | One coin = one game |
| `salle/babyfoot01/total` | number | ESP32 | Games counted since start |
| `salle/babyfoot01/status` | `online` / `offline` | ESP32 | Device state (last will = `offline`) |
| `salle/billiard01/coin` | `1` | ESP32 | One coin = one game |
| `salle/ps01/session` | `start` / `end` | ESP32 | Console session |
| `salle/ps01/duration` | minutes | ESP32 | Session length (e.g. 10) |
| `salle/pc01/status` | `active` / `idle` / `off` | PC agent | PC state |

Use `retain` for `status` topics so the dashboard sees the last known state.
