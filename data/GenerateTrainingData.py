#!/usr/bin/python
import random

print "topology: 2 4 1"

for x in range(0, 2000):
    n1 = random.randrange(0,2)
    n2 = random.randrange(0,2)
    t = n1 ^ n2

    print "in: %.1f %.1f" % (n1, n2)
    print "out: %.1f" % (t)



