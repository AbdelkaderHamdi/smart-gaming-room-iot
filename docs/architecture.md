# Architecture

## Layers
1. **Devices**: ESP32 boards (baby-foot, billiard, console) and the PC agent.
2. **Transport**: MQTT over Wi-Fi/LAN.
3. **Broker**: Mosquitto (local) or a public broker for the simulation.
4. **Backend**: Node-RED subscribes to `salle/#`, computes games, durations and revenue.
5. **Storage**: SQLite or InfluxDB.
6. **Dashboard**: Node-RED Dashboard or ThingsBoard.

## Rules
- One topic tree: see `mqtt-topics.md`.
- One device = one ID (`babyfoot01`, `ps01`, `pc01`).
- Prices live in one config, not in device code.
