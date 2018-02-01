import random

k = random.randint(1, 3000)

print "%d %d %d" % (3000, 3000, k)

for i in xrange(3000):
	for j in xrange(3000):
		print random.randint(1, 100000)
