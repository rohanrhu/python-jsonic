# -*- coding: utf-8 -*-

import jsonic

from datetime import datetime
t0 = datetime.now()

root = jsonic.from_file("heroes.json")

print("Root Type: %d" % root.type)
print("Squad: %s" % root.iterKey("squadName"))
print("Hometown: %s" % root.iterKey("homeTown"))
print("Formed: %d" % root.iterKey("formed"))
print("Active: %d" % root.iterKey("active"))

members = root.iterKey("members")

print("Members: (%d total)" % members.len())
while True:
    member = members.iterItem()
    if not member: break

    name = member.iterKey("name")
    age = member.iterKey("age")
    powers = member.iterKey("powers")

    print("\tName: %s" % name)
    print("\tAge: %s" % age)
    print("\tPowers (%d total):" % powers.len())
    while True:
        power = powers.iterItem()
        if not power:break

        print("\t\t%s" % power)

    print()

t1 = datetime.now()
dt = t1 - t0
print("Time elapsed: %ds, %dus" % (dt.seconds, dt.microseconds))