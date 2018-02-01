import random

print 1000

points = set()
while len(points) != 1000:
	points.add((random.randint(-2000, 2000), random.randint(-2000, 2000)))

for x in points:
	print "%d %d" % (x[0], x[1])

print -1	
