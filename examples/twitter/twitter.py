# -*- coding: utf-8 -*-

import jsonic

from datetime import datetime
t0 = datetime.now()

root = jsonic.from_file("twitter.json")
statuses = root.iterKey("statuses")

print("Statuses: (%d total)\n" % statuses.len())
while True:
    status = statuses.iterItem()
    if not status: break

    sid = status.iterKey("id")
    text = status.iterKey("text")
    user = status.iterKey("user")

    name = user.iterKey("name")

    print("ID: %d" % sid)
    print("Name: %s" % name)
    print("Text: %s" % text)

    print()

t1 = datetime.now()
dt = t1 - t0
print("Time elapsed: %ds, %dus" % (dt.seconds, dt.microseconds))