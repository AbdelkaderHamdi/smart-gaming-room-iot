# Smart Gaming Room IoT

Simulated IoT system to track games, sessions, device status and revenue of a game room: baby-foot, billiards, consoles and PCs. Built with ESP32, MQTT and Node-RED. No hardware needed (Wokwi simulator).

## Architecture

```
Baby-foot / Billiard  -> coin acceptor -> ESP32 -+
Console (PS)          -> session timer -> ESP32 -+--> MQTT Broker -> Node-RED -> Database -> Dashboard
PC                    -> software agent ---------+
```

## Devices

| Device | How it is measured | Folder |
|---|---|---|
| Baby-foot | Coin pulse = 1 game | `simulation/babyfoot` |
| Billiard | Coin pulse = 1 game | `simulation/billiard` |
| Console (PS) | Fixed-length timed session | `simulation/console` |
| PC | Agent sends Active / Idle / Off | `agents/pc-agent` |

## Repository structure

```
docs/          Tutorial, architecture, MQTT topics, roadmap
simulation/    Wokwi projects (ESP32 code, wiring, custom chips)
agents/        PC monitoring agent
backend/       Mosquitto config and Node-RED flows
dashboard/     Dashboard screenshots and notes
```

## Roadmap

- [x] Phase 1: Baby-foot coin counter (Wokwi)
- [ ] Phase 1b: Wi-Fi + MQTT publish
- [ ] Phase 2: Console session timer
- [ ] Phase 3: Node-RED dashboard
- [ ] Phase 4: Billiard, PCs, reusable device template

See `docs/roadmap.md`.

## Quick start

1. Open `simulation/babyfoot` in [Wokwi](https://wokwi.com).
2. Follow `docs/tutorial.md`.

## License

MIT
