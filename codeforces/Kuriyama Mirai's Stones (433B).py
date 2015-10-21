n = int(raw_input())

prices = map(int, raw_input().split())
ordered = []
tot = 0
for val in prices:
        tot += val
        ordered.append(tot)

s = sorted(prices)
ordereds = []
tots = 0
for val in s:
	tots += val
	ordereds.append(tots)

m = int(raw_input())

for i in range(m):
	total = 0
	question = map(int, raw_input().split())
	typeq = question.pop(0)
	
	if (typeq == 1):
		if question[0] > 1:
                        total = ordered[question[1]-1] - ordered[question[0]-2]
                else:
                        total = ordered[question[1]-1]
	else:
		if question[0] > 1:
			total = ordereds[question[1]-1] - ordereds[question[0]-2]
		else:
			total = ordereds[question[1]-1]
	print total
