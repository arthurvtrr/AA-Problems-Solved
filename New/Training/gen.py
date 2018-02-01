import random

print 300000
ini = 726056455
for i in range(300000):
	print "%d %d" % (ini, ini)
	x = random.randint(1, 9)
	ini += x
