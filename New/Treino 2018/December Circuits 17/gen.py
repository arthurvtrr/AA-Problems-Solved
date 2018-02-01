import random

print "200000 100000 232205"

let = ["a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"]
s = ""
for i in range(200000):
	s += let[random.randint(0, 25)]
print s
