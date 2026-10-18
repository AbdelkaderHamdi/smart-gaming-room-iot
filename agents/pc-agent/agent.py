"""PC agent: sends PC state (active / idle / off) to MQTT.

Install: pip install paho-mqtt
Run:     python agent.py
"""
import time
import paho.mqtt.client as mqtt

BROKER = "broker.hivemq.com"
TOPIC = "salle/pc01/status"
INTERVAL_S = 10


def get_state():
    # TODO: detect idle time (keyboard/mouse) for your OS.
    # For now the PC is always "active" while this script runs.
    return "active"


client = mqtt.Client()
client.will_set(TOPIC, "off", retain=True)  # sent by the broker if the PC dies
client.connect(BROKER, 1883)
client.loop_start()

while True:
    client.publish(TOPIC, get_state(), retain=True)
    time.sleep(INTERVAL_S)
