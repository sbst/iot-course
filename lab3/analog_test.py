#!/usr/bin/env python
# -*- coding: utf-8 -*-

import mraa
import urllib2
import time

DID = '8qek4h71fvco'

URL_BASE = "http://168.63.82.20/server/income/?did=%s&action=put&value=" % DID

x = mraa.Aio(0)

while True:
    value = x.read()
    if value:
        url = URL_BASE + value
        try:
            urllib2.urlopen(url)
        except urllib2.HTTPError as e:
            if e.code == '404':
                print("URL not found: %s" % url)

    time.sleep(5)