#!/usr/bin/env python
# -*- coding: utf-8 -*-

import urllib2
import paho.mqtt.client as mqtt


class MQTTSub():
    def __init__(self, host, topic, message_handler):
        self.__host = host
        self.__topic = topic
        self.__handle = message_handler
        self.__connected = False

        def on_connect(client, userdata, flags, rc):
            if rc == 0:
                print("Connected successfully.")
                self.__connected = True
                client.subscribe(self.__topic)
            else:
                print("Server refuse connection with code %d", rc)

        def on_disconnect(client, userdata, rc):
                print("Lost connection to MQTT broker, trying to repair")
                client.reconnect()

        def on_message(client, userdata, msg):
            self.__handle(msg.payload)

        self.__client = mqtt.Client(protocol=mqtt.MQTTv31)
        self.__client.on_connect = on_connect
        self.__client.on_disconnect = on_disconnect
        self.__client.on_message = on_message
        
        self.__client.connect(self.__host)

    def LoopForever(self):
        self.__client.loop_forever()

    def LoopStart(self):
        self.__client.loop_start()

    def LoopStop(self):
        self.__client.loop_stop(force=False)



def ack_value(did, value):
    URL_BASE = "http://168.63.82.20/server/income/?did=%s&action=ack&value=" % did
    url = URL_BASE + value
        try:
            urllib2.urlopen(url)
        except urllib2.HTTPError as e:
            if e.code == '404':
                print("URL not found: %s" % url)



DID = '8qek4h71fvco'

# How to use:
#
# 1. write the handler function. 
# It'll be invoke than new message arrive on topic

def handler(str_msg):
    msg_dict = dict()
    msg_list = str_msg.split(";")

    for item in msg_list:
        tmp = item.split("=")
        if len(tmp) == 2:
            msg_dict[tmp[0]] = tmp[1]
        else:
            print("Error in imcome msg: %s" % str_msg)
            return

    if not msg_dict.has_key('did'):
        print("No DID in income msg: %s" % str_msg)
        return
    if not msg_dict.has_key('action'):
        print("No action in income msg: %s" % str_msg)
        return

    if msg_dict['action'] == 'set':
        if not msg_dict.has_key('value'):
            print("No new value in income msg: %s" % str_msg)
            return
        if msg_dict['value'] == "1":
            # code for setting switch on
            ack_value(DID, "1")
            return
        elif msg_dict['value'] == "0":
            # code for setting switch off
            ack_value(DID, "0")
            return
        else:
            print("Unknown value: %s" % str_msg)
            return
    elif msg_dict['action'] == 'get':
        # return current value of switch need to be stored somethere
        # ack_value(DID, value)
        return
    else:
        print("Unknown action: %s" % str_ms)

# 2. Create exemplar of MQTTSub class.
# For initialization provide MQTT brocker adress, 
# needed topic and handler function

mqtt_con = MQTTSub("168.63.82.20", "thing/" + DID, handler)

# 3. Start MQTT client loop.
mqtt_con.LoopForever()