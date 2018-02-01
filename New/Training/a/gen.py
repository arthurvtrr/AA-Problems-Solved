import random

n = random.randint(1, 100)
e = random.randint(0, n * (n-1) / 2)
b = 50

print 1
print "%d %d %d" % (n, e, b)

for i in range(n):
	print random.randint(1, 1000)
for i in range(b):
	print random.randint(1, 1000)

cont = 0
while True:
	if cont == e: 
		break
	
	x = random.randint(1, n)
        y = random.randint(1, n)
	while True:
		if x != y:
			break
		x = random.randint(1, n)
		y = random.randint(1, n)

	print "%d %d" % (x, y)
	cont += 1 
