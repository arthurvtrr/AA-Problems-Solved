import random

print "4096 16384"

for i in range(4096):
        s = ""
        for j in range(4096):
                s += str(random.randint(0, 9))
        print s
