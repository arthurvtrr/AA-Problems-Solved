tasks = int(raw_input())
dif = raw_input().split()
ordem = range(1,len(dif)+1)

ord1 = []
ord2 = []
ord3 = []

for i in range(len(dif)):
        tup = (ordem[i],int(dif[i]))
        ord1.append(tup)

ord1.sort(key=lambda x: x[1])

i = 0
x = -1
while i < len(ord1) - 1:
	if ord1[i][1] == ord1[i+1][1]:
		ord2.append(ord1[i+1])
		ord2.append(ord1[i])
		i += 2
		x = i - 1
		while i < len(ord1):
			ord2.append(ord1[i])
			i += 1
		break
	else:
		ord2.append(ord1[i])
		i += 1

found = False
i = 0
while i < len(ord1) - 1:
	if i >= x and ord1[i][1] == ord1[i+1][1]:
                ord3.append(ord1[i+1])
                ord3.append(ord1[i])
                i += 2
		found = True
                while i < len(ord1):
                        ord3.append(ord1[i])
                        i += 1
                break
        else:
                ord3.append(ord1[i])
                i += 1

if found:
	print "YES"
	ordem1 = ""
	ordem2 = ""
	ordem3 = ""
	for i in range(len(ord1)):
		ordem1 += str(ord1[i][0]) + " "
		ordem2 += str(ord2[i][0]) + " "
		ordem3 += str(ord3[i][0]) + " "
	print ordem1
	print ordem2
	print ordem3
else:
	print "NO"
