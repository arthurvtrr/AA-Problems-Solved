n, v = map(int, raw_input().split())

prices = []
times = 0
sellers = []

for i in range(n):
	prices.append(map(int,raw_input().split()))
	prices[i].pop(0)

for lin in range(len(prices)):
	for col in range(len(prices[lin])):
		if prices[lin][col] < v:
			times += 1
			sellers.append(lin+1)
			break

print times

for num in sellers:
	print num, 
