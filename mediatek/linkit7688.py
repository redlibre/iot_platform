import paho.mqtt.client as mqtt
import json, time
import mraa

rele0 = mraa.Gpio(0)
rele1 = mraa.Gpio(1)
rele2 = mraa.Gpio(2)
rele3 = mraa.Gpio(3)
rele0.dir(mraa.DIR_OUT)
rele1.dir(mraa.DIR_OUT)
rele2.dir(mraa.DIR_OUT)
rele3.dir(mraa.DIR_OUT)


# ----- CHANGE THESE FOR YOUR SETUP -----
MQTT_HOST = "a.redlibre.cl"
MQTT_PORT = 1883
USERNAME = "username"
DEVPASSWORD = "devpassword"
IOTUSERNAME = "iotusername"
IOTDEVICE = "iotdevice"

# ---------------------------------------

def on_connect(client, userdata, rc):
    print("\nConnected with result code " + str(rc) + "\n")

    client.subscribe("redlibre/iot/{0}/{1}/{2}/iot/control/".format(USERNAME,IOTDEVICE,IOTUSERNAME))  
    print("Subscribed to redlibre")

def on_message_iotrl(client, userdata, msg):
    print("\n\t* Linkit UPDATED ("+msg.topic+"): " + str(msg.payload))
    if msg.payload == "gpio0on": 
	rele2.write(1)
	client.publish("redlibre/iot/{0}/{1}/{2}/status/".format(USERNAME,IOTDEVICE,IOTUSERNAME), "gpio0ON", 2)
    if msg.payload == "gpio0off":
	rele2.write(0)
	client.publish("redlibre/iot/{0}/{1}/{2}/status/".format(USERNAME,IOTDEVICE,IOTUSERNAME), "gpio0OFF", 2)
    if msg.payload == "gpio1on":
        rele3.write(1)                                                                                         
        client.publish("redlibre/iot/{0}/{1}/{2}/status/".format(USERNAME,IOTDEVICE,IOTUSERNAME), "gpio1ON", 2)
    if msg.payload == "gpio1off":                                                                              
        rele3.write(0)                                                                                          
        client.publish("redlibre/iot/{0}/{1}/{2}/status/".format(USERNAME,IOTDEVICE,IOTUSERNAME), "gpio1OFF", 2)
    if msg.payload == "gpio2on":
        rele1.write(1)                                                                                         
        client.publish("redlibre/iot/{0}/{1}/{2}/status/".format(USERNAME,IOTDEVICE,IOTUSERNAME), "gpio2ON", 2)
    if msg.payload == "gpio2off":                                                                              
        rele1.write(0)                                                                                          
        client.publish("redlibre/iot/{0}/{1}/{2}/status/".format(USERNAME,IOTDEVICE,IOTUSERNAME), "gpio2OFF", 2)
    if msg.payload == "gpio3on":
        rele0.write(1)                                                                                         
        client.publish("redlibre/iot/{0}/{1}/{2}/status/".format(USERNAME,IOTDEVICE,IOTUSERNAME), "gpio3ON", 2)
    if msg.payload == "gpio3off":                                                                              
        rele0.write(0)                                                                                          
        client.publish("redlibre/iot/{0}/{1}/{2}/status/".format(USERNAME,IOTDEVICE,IOTUSERNAME), "gpio3OFF", 2)

def command_error():
    print("Error: Unknown command")

client = mqtt.Client(client_id="linkit7688-test")

client.will_set("redlibre/iot/{0}/{1}/{2}/iot/control/".format(USERNAME,IOTDEVICE,IOTUSERNAME),"gpio2on", 1, True)

client.on_connect = on_connect
client.message_callback_add("redlibre/iot/{0}/{1}/{2}/iot/control/".format(USERNAME,IOTDEVICE,IOTUSERNAME), on_message_iotrl)

client.username_pw_set(IOTUSERNAME, DEVPASSWORD)
client.connect(MQTT_HOST, MQTT_PORT, 60)
client.loop_start()  # Background thread to call loop() automatically

while True:
    time.sleep(10) 
