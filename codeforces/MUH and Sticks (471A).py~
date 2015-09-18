sticks = raw_input().split()

equals = [0,0,0,0,0,0,0,0,0,0]
for length in sticks:
	equals[int(length)-1] += 1 

if max(equals) == 4:
	rest = []
	for j in range(len(equals)):
		if equals[j] == max(equals):
			index = j	
	for i in sticks:
		if int(i) != index:
			rest.append(int(i))

	if rest[0] != rest[1]:
		print "Bear"
	else:
		print "Elephant"
elif max(equals) == 5:
	print "Bear"
elif max(equals) == 6:
	print "Elephant"
else:
	print "Alien"
